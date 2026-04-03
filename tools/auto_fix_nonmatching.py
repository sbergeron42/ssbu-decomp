#!/usr/bin/env python3
"""
Auto-fix non-matching functions by detecting mismatch patterns and applying
source-level fixes.

Patterns detected and fixed:
  1. Register width (sf bit): u32/s32 <-> u64/s64 in params/return
  2. Bool truncation: extra `and wN, wN, #1` → change bool to u8
  3. Return type mismatch: try void, u32, u64, void*, f32
  4. Parameter count (BR register): vtable dispatch using wrong number of params

Usage:
    python tools/auto_fix_nonmatching.py                # Analyze only (dry run)
    python tools/auto_fix_nonmatching.py --fix           # Apply fixes
    python tools/auto_fix_nonmatching.py --fix --pattern sf_bit   # Fix one pattern
    python tools/auto_fix_nonmatching.py --fix --limit 10         # Fix at most 10
"""

import argparse
import csv
import os
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
SRC_DIR = PROJECT_ROOT / "src"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000

CLANG = r"C:\llvm-8.0.0\bin\clang++.exe"
CFLAGS = (
    "-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 "
    "-fno-exceptions -fno-rtti -ffunction-sections -fdata-sections "
    "-fno-common -fno-short-enums -fPIC -mno-implicit-float "
    "-fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG "
    "-Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs"
).split()

# Import shared infrastructure from verify_all
sys.path.insert(0, str(Path(__file__).parent))
from verify_all import (
    load_elf_segments, read_bytes_at, read_o_file_functions,
    extract_short_name, patch_relocations, build_csv_lookup,
    build_source_addr_map, resolve_addr,
)


# ---------------------------------------------------------------------------
# AArch64 instruction helpers
# ---------------------------------------------------------------------------

def is_br(insn):
    """BR Xn: 1101011_0000_11111_000000_NNNNN_00000"""
    return (insn & 0xFFFFFC1F) == 0xD61F0000

def br_reg(insn):
    return (insn >> 5) & 0x1F

def is_ret(insn):
    return insn == 0xD65F03C0

def is_and_imm1(insn):
    """and wN, wM, #1 (32-bit AND immediate with value 1)."""
    # Encoding: sf=0 opc=00 100100 N=0 immr=000000 imms=000000 Rn Rd
    # = 0x12000000 | (Rn << 5) | Rd
    return (insn & 0xFFFFFC00) == 0x12000000

def and_imm1_regs(insn):
    """Return (Rd, Rn) for `and wRd, wRn, #1`."""
    return (insn & 0x1F, (insn >> 5) & 0x1F)

def sf_bit(insn):
    """Return bit 31 (size flag)."""
    return (insn >> 31) & 1


# ---------------------------------------------------------------------------
# Source file mapping
# ---------------------------------------------------------------------------

_obj_to_src_cache = {}

def build_obj_to_src_map():
    """Map .o basename (without ext) -> source .cpp path."""
    if _obj_to_src_cache:
        return _obj_to_src_cache
    for root, _, files in os.walk(SRC_DIR):
        for f in files:
            if f.endswith('.cpp'):
                stem = Path(f).stem
                _obj_to_src_cache[stem] = Path(root) / f
    return _obj_to_src_cache


def find_source_for_obj(obj_name):
    """Given an .o filename like 'AreaModule.o', find the source .cpp."""
    mapping = build_obj_to_src_map()
    stem = Path(obj_name).stem
    return mapping.get(stem)


def find_function_in_source(src_path, func_name, orig_addr=None):
    """Find the line number of a function definition in a source file.
    Returns (line_index, line_text) or None."""
    try:
        lines = src_path.read_text().splitlines()
    except OSError:
        return None

    # Try exact function name match first
    for i, line in enumerate(lines):
        if func_name + '(' in line and not line.strip().startswith('//'):
            return (i, line)

    # Try address comment match for FUN_* functions
    if orig_addr is not None:
        addr_hex = f"0x{orig_addr:x}"
        addr_hex2 = f"{orig_addr:x}"
        for i, line in enumerate(lines):
            if addr_hex in line or addr_hex2 in line:
                # The function def should be on the next non-comment line
                for j in range(i + 1, min(i + 3, len(lines))):
                    if func_name + '(' in lines[j] or (
                        not lines[j].strip().startswith('//') and '(' in lines[j]
                    ):
                        return (j, lines[j])
                # The address comment might be on the same line
                if '(' in line and not line.strip().startswith('//'):
                    return (i, line)
    return None


# ---------------------------------------------------------------------------
# Pattern detection
# ---------------------------------------------------------------------------

class MismatchInfo:
    """Info about a non-matching function."""
    __slots__ = (
        'mangled', 'short_name', 'num_insns', 'orig_addr',
        'orig_words', 'decomp_words', 'diff_indices',
        'obj_file', 'size', 'relocs', 'decomp_bytes_raw',
    )

    def __init__(self, **kw):
        for k, v in kw.items():
            setattr(self, k, v)

    @property
    def num_diffs(self):
        return len(self.diff_indices)


def classify_mismatch(info: MismatchInfo):
    """Classify the mismatch pattern. Returns a list of applicable patterns."""
    patterns = []
    ow = info.orig_words
    dw = info.decomp_words
    diffs = info.diff_indices
    n = info.num_insns

    if not diffs:
        return []

    # --- Pattern: sf_bit (register width) ---
    sf_diffs = [i for i in diffs if (ow[i] ^ dw[i]) == 0x80000000]
    if sf_diffs and len(sf_diffs) == len(diffs):
        patterns.append(('sf_bit', sf_diffs))

    # --- Pattern: bool_truncation ---
    # Decomp has extra `and wN, wN, #1` that original doesn't, or vice versa
    bool_diffs = []
    for i in diffs:
        if is_and_imm1(dw[i]) and not is_and_imm1(ow[i]):
            rd, rn = and_imm1_regs(dw[i])
            if rd == rn:
                bool_diffs.append(('decomp_extra', i, rd))
        elif is_and_imm1(ow[i]) and not is_and_imm1(dw[i]):
            rd, rn = and_imm1_regs(ow[i])
            if rd == rn:
                bool_diffs.append(('orig_extra', i, rd))
    if bool_diffs:
        patterns.append(('bool_trunc', bool_diffs))

    # --- Pattern: br_reg_diff (parameter count) ---
    br_diffs = []
    ldr_rt_diffs = []
    for i in diffs:
        if is_br(ow[i]) and is_br(dw[i]) and br_reg(ow[i]) != br_reg(dw[i]):
            br_diffs.append((i, br_reg(ow[i]), br_reg(dw[i])))
        # LDR with different Rt (bits 4:0), same everything else
        elif (ow[i] & 0xFFFFFFE0) == (dw[i] & 0xFFFFFFE0):
            ldr_rt_diffs.append(i)
    if br_diffs:
        all_accounted = len(br_diffs) + len(ldr_rt_diffs) + len(sf_diffs) + len(bool_diffs)
        patterns.append(('br_reg', br_diffs))

    # --- Pattern: return type (sf bit on last few instructions near return) ---
    # If the only sf diffs are near the end (return value register width)
    if sf_diffs and not (len(sf_diffs) == len(diffs)):
        # Check if sf diffs are near the return
        near_end = [i for i in sf_diffs if i >= n - 3]
        if near_end:
            patterns.append(('return_type_sf', near_end))

    return patterns


# ---------------------------------------------------------------------------
# Fix application
# ---------------------------------------------------------------------------

def _parse_vtable_func_sig(line):
    """Parse a vtable dispatch function signature.
    Returns dict with ret_type, func_name, params (list of (type, name)), body
    or None if not parseable."""
    # Match: ret_type func_name(params) { body }
    m = re.match(
        r'^(\w[\w*\s]*?)\s+(\w+)\s*\(([^)]*)\)\s*\{(.+)\}\s*$',
        line.strip()
    )
    if not m:
        return None
    ret_type = m.group(1).strip()
    func_name = m.group(2)
    params_str = m.group(3).strip()
    body = m.group(4).strip()

    params = []
    if params_str:
        for p in params_str.split(','):
            p = p.strip()
            # Split "type name" — handle pointer types like "void*"
            parts = p.rsplit(None, 1)
            if len(parts) == 2:
                params.append((parts[0].strip(), parts[1].strip()))
            else:
                params.append((p, ''))

    return {
        'ret_type': ret_type,
        'func_name': func_name,
        'params': params,
        'body': body,
        'raw': line,
    }


def fix_sf_bit(info: MismatchInfo, src_path, patterns):
    """Fix register width mismatches by changing param/return types."""
    fixes = []
    for pat_type, pat_data in patterns:
        if pat_type != 'sf_bit':
            continue
        for diff_idx in pat_data:
            o = info.orig_words[diff_idx]
            d = info.decomp_words[diff_idx]
            # Original has sf=0 (32-bit), decomp has sf=1 (64-bit)
            # → we need to narrow a type from 64-bit to 32-bit
            if sf_bit(o) == 0 and sf_bit(d) == 1:
                fixes.append(('narrow', diff_idx))
            else:
                fixes.append(('widen', diff_idx))

    if not fixes:
        return None

    loc = find_function_in_source(src_path, info.short_name, info.orig_addr)
    if loc is None:
        return None
    line_idx, line = loc
    parsed = _parse_vtable_func_sig(line)
    if not parsed:
        return None

    # For a simple function with all sf diffs being "narrow",
    # the return type likely needs narrowing (void* → u32, u64 → u32)
    direction = fixes[0][0]
    new_line = line
    if direction == 'narrow':
        if parsed['ret_type'] in ('void*', 'u64', 's64'):
            new_ret = 'u32'
            new_line = line.replace(parsed['ret_type'] + ' ' + parsed['func_name'],
                                    new_ret + ' ' + parsed['func_name'], 1)
            # Also fix cast in body
            if parsed['ret_type'] == 'void*':
                new_line = new_line.replace('return reinterpret_cast<void*(*)',
                                           'return reinterpret_cast<u32(*)', 1)
                new_line = new_line.replace('reinterpret_cast<void*(*)(',
                                           'reinterpret_cast<u32(*)(', 1)
    elif direction == 'widen':
        if parsed['ret_type'] in ('u32', 's32'):
            new_ret = 'u64'
            new_line = line.replace(parsed['ret_type'] + ' ' + parsed['func_name'],
                                    new_ret + ' ' + parsed['func_name'], 1)

    if new_line == line:
        return None
    return (line_idx, line, new_line)


def fix_bool_trunc(info: MismatchInfo, src_path, patterns):
    """Fix bool truncation by changing bool to u8 in params."""
    fixes = []
    for pat_type, pat_data in patterns:
        if pat_type != 'bool_trunc':
            continue
        for direction, diff_idx, reg in pat_data:
            fixes.append((direction, reg))

    if not fixes:
        return None

    loc = find_function_in_source(src_path, info.short_name, info.orig_addr)
    if loc is None:
        return None
    line_idx, line = loc

    new_line = line
    for direction, reg in fixes:
        if direction == 'decomp_extra':
            # Decomp has extra bool truncation → param is bool but should be u8
            new_line = re.sub(r'\bbool\b', 'u8', new_line, count=1)
        elif direction == 'orig_extra':
            # Original has bool truncation, decomp doesn't → param should be bool
            new_line = re.sub(r'\bu8\b', 'bool', new_line, count=1)

    if new_line == line:
        return None
    return (line_idx, line, new_line)


def fix_br_reg(info: MismatchInfo, src_path, patterns):
    """Fix parameter count by adjusting vtable dispatch function params.

    When decomp uses BR x2 but original uses BR x1, the decomp has one extra
    param that shouldn't be there. The BR register = next free after all live
    param registers (x0=module, x1..xN=params).
    """
    br_data = None
    for pat_type, pat_data in patterns:
        if pat_type == 'br_reg':
            br_data = pat_data
            break
    if not br_data:
        return None

    # Use the first BR diff
    _, orig_br, decomp_br = br_data[0]

    loc = find_function_in_source(src_path, info.short_name, info.orig_addr)
    if loc is None:
        return None
    line_idx, line = loc
    parsed = _parse_vtable_func_sig(line)
    if not parsed:
        return None

    # Original BR reg tells us the true parameter count
    # x0 = module pointer, x1..x(br-1) = params to vtable call
    # Params to the lua_bind wrapper: x0 = accessor, x1..xN forwarded
    # The module pointer loaded from accessor goes in x0 for the vtable call
    # So orig_br = number of params to vtable call = module + forwarded params
    # The wrapper's params: accessor + forwarded params
    # orig_br = 1 + num_forwarded → num_forwarded = orig_br - 1
    target_forwarded = orig_br - 1
    current_forwarded = decomp_br - 1

    if target_forwarded == current_forwarded:
        return None

    # Rebuild the function signature with the correct number of params
    # Keep the first param (accessor) and adjust the rest
    if len(parsed['params']) < 1:
        return None

    first_param = parsed['params'][0]

    # Determine the parameter types and names for forwarded params
    # from the original if available, otherwise use u64
    new_params = [first_param]
    old_forwarded = parsed['params'][1:]

    if target_forwarded < current_forwarded:
        # Remove extra params
        new_params.extend(old_forwarded[:target_forwarded])
    else:
        # Add missing params
        new_params.extend(old_forwarded)
        for i in range(len(old_forwarded), target_forwarded):
            new_params.append((f'u64', f'p{i+1}'))

    # Rebuild the function line
    params_str = ','.join(f'{t} {n}' for t, n in new_params)

    # Also need to fix the body's cast and call
    body = parsed['body']

    # Fix the cast parameter types in the body
    # Pattern: reinterpret_cast<ret_type(*)(void*,type1,type2,...)>(VT(m)[...]))(m,p1,p2,...)
    # We need to adjust both the cast types and the call args

    # Build new call args
    call_args = ['m']
    for i in range(target_forwarded):
        if i < len(old_forwarded):
            call_args.append(old_forwarded[i][1])
        else:
            call_args.append(f'p{i+1}')
    call_args_str = ','.join(call_args)

    # Build new cast param types
    cast_types = ['void*']
    for i in range(target_forwarded):
        if i < len(old_forwarded):
            cast_types.append(old_forwarded[i][0])
        else:
            cast_types.append('u64')
    cast_types_str = ','.join(cast_types)

    # Replace the cast types in body
    # Match: reinterpret_cast<RET(*)(...TYPES...)>
    new_body = re.sub(
        r'(reinterpret_cast<\w[\w*]*\s*\(\*\)\()([^)]*)\)',
        lambda m: m.group(1) + cast_types_str + ')',
        body,
        count=1,
    )
    # Replace call args: the pattern ])(args) is unique — ] closes VT[off/8]
    new_body = re.sub(
        r'\]\)\(([^)]*)\)',
        lambda m: '])(' + call_args_str + ')',
        new_body,
        count=1,
    )

    new_line = f"{parsed['ret_type']} {parsed['func_name']}({params_str}) {{ {new_body} }}"

    if new_line.strip() == line.strip():
        return None
    return (line_idx, line, new_line)


def fix_return_type(info: MismatchInfo, src_path, patterns):
    """Try different return types to find a match."""
    loc = find_function_in_source(src_path, info.short_name, info.orig_addr)
    if loc is None:
        return None
    line_idx, line = loc
    parsed = _parse_vtable_func_sig(line)
    if not parsed:
        return None

    # Only try if we have return type sf diffs or general mismatches
    # Build candidate return types to try
    current_ret = parsed['ret_type']
    candidates = []
    if current_ret == 'void*':
        candidates = ['u64', 'u32', 'f32']
    elif current_ret == 'u32':
        candidates = ['void*', 'u64', 'f32']
    elif current_ret == 'u64':
        candidates = ['void*', 'u32', 'f32']
    elif current_ret == 'bool':
        candidates = ['u8', 'u32']
    elif current_ret == 'f32':
        candidates = ['u32', 'void*']
    elif current_ret == 'void':
        candidates = ['u32', 'u64', 'void*']
    else:
        candidates = ['void', 'u32', 'u64', 'void*']

    return ('try_return_types', line_idx, line, parsed, candidates)


def infer_vtable_signature(info: MismatchInfo):
    """Infer the correct vtable dispatch signature from the original binary.

    Decodes the original instructions to determine:
    - Module offset (from accessor load)
    - Vtable offset (from vtable load)
    - Parameter count (from BR register)
    - Bool parameters (from AND masking)
    - Whether function is leaf (tail call) or non-leaf (call + ret)

    Returns dict with inferred params or None if not a vtable dispatch.
    """
    ow = info.orig_words
    n = info.num_insns
    if n < 3 or n > 8:
        return None

    # Detect leaf vtable dispatch pattern:
    #   ldr x0, [x0, #mod_off]     - load module from accessor
    #   ldr x8, [x0]               - load vtable pointer
    #   [and wN, wN, #1 ...]       - optional bool masking
    #   ldr xBR, [x8, #vt_off]     - load function pointer
    #   br xBR                      - tail call

    # Check for BR at end
    if not is_br(ow[-1]):
        return None
    br_r = br_reg(ow[-1])

    # Find module load: ldr x0, [x0, #imm]  (64-bit load, Rn=x0, Rt=x0)
    # Encoding: 1111100101 imm12 00000 00000
    mod_off = None
    if (ow[0] & 0xFFC003FF) == 0xF9400000:
        mod_off = ((ow[0] >> 10) & 0xFFF) * 8

    if mod_off is None:
        return None

    # Find vtable load: ldr x8, [x0]  (load vtable pointer)
    # Encoding: F9400008 = ldr x8, [x0, #0]
    if n >= 2 and (ow[1] & 0xFFFFFFFF) == 0xF9400008:
        pass  # vtable in x8
    else:
        return None

    # Find vtable function pointer load: ldr xBR, [x8, #vt_off]
    # Encoding: F94xxxxx with Rn=x8, Rt=br_r
    vt_off = None
    for i in range(2, n):
        insn = ow[i]
        if (insn & 0xFFC003E0) == 0xF9400100:  # ldr Xt, [x8, #imm]
            rt = insn & 0x1F
            if rt == br_r:
                vt_off = ((insn >> 10) & 0xFFF) * 8
                break

    if vt_off is None:
        return None

    # Detect bool params: and wN, wN, #1
    bool_regs = set()
    for i in range(2, n):
        if is_and_imm1(ow[i]):
            rd, rn = and_imm1_regs(ow[i])
            if rd == rn:
                bool_regs.add(rd)

    # Parameter count: BR register = 1 + num_forwarded
    num_forwarded = br_r - 1

    # Build param list
    params = []
    for i in range(num_forwarded):
        reg = i + 1  # x1, x2, ...
        if reg in bool_regs:
            params.append(('bool', f'p{i+1}'))
        else:
            params.append(('u64', f'p{i+1}'))

    return {
        'mod_off': mod_off,
        'vt_off': vt_off,
        'num_forwarded': num_forwarded,
        'params': params,
        'br_reg': br_r,
        'bool_regs': bool_regs,
    }


def fix_vtable_comprehensive(info: MismatchInfo, src_path):
    """Comprehensive fix: infer correct signature from original and rebuild.

    This handles all vtable dispatch patterns at once:
    - Wrong param count
    - Wrong param types (bool vs u64)
    - Works for single-line vtable dispatch functions
    """
    inferred = infer_vtable_signature(info)
    if inferred is None:
        return None

    loc = find_function_in_source(src_path, info.short_name, info.orig_addr)
    if loc is None:
        return None
    line_idx, line = loc
    parsed = _parse_vtable_func_sig(line)
    if not parsed:
        return None

    # Check if there's a module macro in the source
    # Look for AM(a), CAMERA_MODULE(a), etc. in the line
    module_expr = None
    m = re.search(r'auto\*\s*m\s*=\s*([^;]+);', parsed['body'])
    if m:
        module_expr = m.group(1).strip()

    if module_expr is None:
        return None

    # Build new function
    first_param = parsed['params'][0] if parsed['params'] else ('BattleObjectModuleAccessor*', 'a')
    new_params = [first_param] + inferred['params']
    params_str = ','.join(f'{t} {n}' for t, n in new_params)

    # Build cast types and call args
    cast_types = ['void*'] + [t for t, _ in inferred['params']]
    call_args = ['m'] + [n for _, n in inferred['params']]
    cast_types_str = ','.join(cast_types)
    call_args_str = ','.join(call_args)

    vt_idx = inferred['vt_off'] // 8
    vt_expr = f"0x{inferred['vt_off']:x}/8"

    ret_type = parsed['ret_type']
    ret_prefix = 'return ' if ret_type != 'void' else ''

    new_line = (
        f"{ret_type} {parsed['func_name']}({params_str}) {{ "
        f"auto* m={module_expr}; "
        f"{ret_prefix}reinterpret_cast<{ret_type}(*)({cast_types_str})>"
        f"(VT(m)[{vt_expr}])({call_args_str}); }}"
    )

    if new_line.strip() == line.strip():
        return None
    return (line_idx, line, new_line)


# ---------------------------------------------------------------------------
# Compile and verify
# ---------------------------------------------------------------------------

def compile_source(src_path):
    """Compile a single source file. Returns True on success."""
    obj_name = src_path.stem + '.o'
    obj_path = BUILD_DIR / obj_name
    cmd = [CLANG] + CFLAGS + ['-c', str(src_path), '-o', str(obj_path)]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        return False

    # Run post-processors
    subprocess.run([sys.executable, str(PROJECT_ROOT / 'tools' / 'fix_movz_to_orr.py'),
                    str(obj_path)], capture_output=True)
    subprocess.run([sys.executable, str(PROJECT_ROOT / 'tools' / 'fix_prologue.py'),
                    str(obj_path)], capture_output=True)

    # Epilogue fix only for batch_c/d/e2 files
    stem = src_path.stem
    if stem.startswith('fun_batch_c_') or stem.startswith('fun_batch_d_') or stem.startswith('fun_batch_e2_'):
        subprocess.run([sys.executable, str(PROJECT_ROOT / 'tools' / 'fix_epilogue.py'),
                        str(obj_path)], capture_output=True)

    # PLT stubs fix only for fun_region_039
    if stem == 'fun_region_039':
        subprocess.run([sys.executable, str(PROJECT_ROOT / 'tools' / 'fix_plt_stubs.py'),
                        str(obj_path)], capture_output=True)

    return True


def verify_function(func_name, orig_addr, obj_path, csv_lookup):
    """Verify a single function from its .o file against the original.
    Returns True if bytes match."""
    orig_segments = load_elf_segments(ORIGINAL_ELF)
    orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr

    for mangled, size, code, relocs in read_o_file_functions(obj_path):
        short = extract_short_name(mangled)
        if short != func_name and mangled != func_name:
            continue

        with open(ORIGINAL_ELF, 'rb') as f:
            orig_bytes = read_bytes_at(f, orig_segments, orig_vaddr, size)
        if orig_bytes is None:
            return False

        decomp = bytearray(code)
        if relocs:
            patch_relocations(decomp, relocs, orig_addr, csv_lookup, orig_bytes)

        return bytes(decomp) == orig_bytes

    return False


# ---------------------------------------------------------------------------
# Main analysis and fix pipeline
# ---------------------------------------------------------------------------

def collect_non_matching():
    """Collect all non-matching functions with mismatch details.
    Returns list of MismatchInfo, keyed by (obj_file, func_name)."""
    csv_lookup = build_csv_lookup()
    source_addr_map = build_source_addr_map()
    orig_segments = load_elf_segments(ORIGINAL_ELF)

    results = []

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for obj_name in sorted(os.listdir(BUILD_DIR)):
            if not obj_name.endswith('.o'):
                continue
            obj_path = BUILD_DIR / obj_name
            for mangled, size, code, relocs in read_o_file_functions(obj_path):
                short_name = extract_short_name(mangled)
                orig_addr = resolve_addr(
                    csv_lookup, source_addr_map, mangled, short_name, size)
                if orig_addr is None:
                    continue

                orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr
                orig_bytes = read_bytes_at(orig_f, orig_segments, orig_vaddr, size)
                if orig_bytes is None:
                    continue

                decomp = bytearray(code)
                if relocs:
                    patch_relocations(decomp, relocs, orig_addr, csv_lookup, orig_bytes)
                decomp_bytes = bytes(decomp)

                num_insns = size // 4
                orig_words = []
                decomp_words = []
                diff_indices = []

                for i in range(num_insns):
                    o = struct.unpack_from('<I', orig_bytes, i * 4)[0]
                    d = struct.unpack_from('<I', decomp_bytes, i * 4)[0]
                    orig_words.append(o)
                    decomp_words.append(d)
                    if o != d:
                        diff_indices.append(i)

                if not diff_indices:
                    continue

                results.append(MismatchInfo(
                    mangled=mangled,
                    short_name=short_name,
                    num_insns=num_insns,
                    orig_addr=orig_addr,
                    orig_words=orig_words,
                    decomp_words=decomp_words,
                    diff_indices=diff_indices,
                    obj_file=obj_name,
                    size=size,
                    relocs=relocs,
                    decomp_bytes_raw=code,
                ))

    return results, csv_lookup


def apply_and_verify_fix(info, fix_result, src_path, csv_lookup, dry_run=False):
    """Apply a fix, recompile, verify. Returns True if function now matches.
    Reverts on failure."""
    if fix_result is None:
        return False

    lines = src_path.read_text().splitlines()
    obj_path = BUILD_DIR / info.obj_file

    # Handle try_return_types (multiple candidates)
    if isinstance(fix_result, tuple) and fix_result[0] == 'try_return_types':
        _, line_idx, orig_line, parsed, candidates = fix_result
        if dry_run:
            print(f"    Would try return types: {candidates}")
            return False

        original_content = src_path.read_text()
        backup_obj = None
        if obj_path.exists():
            backup_obj = obj_path.read_bytes()

        for candidate_ret in candidates:
            new_line = orig_line.replace(
                parsed['ret_type'] + ' ' + parsed['func_name'],
                candidate_ret + ' ' + parsed['func_name'], 1)
            # Also fix cast return type in body
            old_cast = f"reinterpret_cast<{parsed['ret_type']}(*)("
            new_cast = f"reinterpret_cast<{candidate_ret}(*)("
            new_line = new_line.replace(old_cast, new_cast, 1)

            if new_line == orig_line:
                continue

            test_lines = list(lines)
            test_lines[line_idx] = new_line
            src_path.write_text('\n'.join(test_lines) + '\n')

            if not compile_source(src_path):
                src_path.write_text(original_content)
                continue

            if verify_function(info.short_name, info.orig_addr, obj_path, csv_lookup):
                print(f"    FIXED with return type: {candidate_ret}")
                return True

        # Revert
        src_path.write_text(original_content)
        if backup_obj:
            obj_path.write_bytes(backup_obj)
        return False

    # Standard single-fix
    line_idx, orig_line, new_line = fix_result

    if dry_run:
        print(f"    Would change line {line_idx + 1}:")
        print(f"      - {orig_line.strip()}")
        print(f"      + {new_line.strip()}")
        return False

    original_content = src_path.read_text()
    backup_obj = None
    if obj_path.exists():
        backup_obj = obj_path.read_bytes()

    lines[line_idx] = new_line
    src_path.write_text('\n'.join(lines) + '\n')

    if not compile_source(src_path):
        print(f"    Compile failed, reverting")
        src_path.write_text(original_content)
        return False

    if verify_function(info.short_name, info.orig_addr, obj_path, csv_lookup):
        print(f"    FIXED!")
        return True

    # Revert
    print(f"    Still non-matching, reverting")
    src_path.write_text(original_content)
    if backup_obj:
        obj_path.write_bytes(backup_obj)
    return False


def main():
    parser = argparse.ArgumentParser(description='Auto-fix non-matching functions')
    parser.add_argument('--fix', action='store_true', help='Actually apply fixes')
    parser.add_argument('--pattern', choices=['sf_bit', 'bool_trunc', 'br_reg', 'return_type', 'vtable_infer', 'all'],
                        default='all', help='Which pattern to fix')
    parser.add_argument('--limit', type=int, default=0, help='Max functions to fix (0=unlimited)')
    parser.add_argument('--short-only', action='store_true', default=True,
                        help='Only fix short functions (<=10 insns)')
    parser.add_argument('--max-insns', type=int, default=10,
                        help='Max instruction count for fixable functions')
    args = parser.parse_args()

    print("Collecting non-matching functions...")
    all_mismatches, csv_lookup = collect_non_matching()
    print(f"Found {len(all_mismatches)} non-matching functions")

    # Classify
    obj_to_src = build_obj_to_src_map()
    by_pattern = {
        'sf_bit': [],
        'bool_trunc': [],
        'br_reg': [],
        'return_type': [],
        'vtable_infer': [],
        'unclassified': [],
    }

    for info in all_mismatches:
        if args.short_only and info.num_insns > args.max_insns:
            continue

        pats = classify_mismatch(info)
        if not pats:
            # Try vtable inference for unclassified functions
            inferred = infer_vtable_signature(info)
            if inferred is not None:
                by_pattern['vtable_infer'].append((info, pats))
            else:
                by_pattern['unclassified'].append((info, []))
            continue

        classified = False
        for pat_type, _ in pats:
            if pat_type in by_pattern:
                by_pattern[pat_type].append((info, pats))
                classified = True
                break
        if not classified:
            # Also try vtable inference for classified but complex patterns
            inferred = infer_vtable_signature(info)
            if inferred is not None:
                by_pattern['vtable_infer'].append((info, pats))
            else:
                by_pattern['unclassified'].append((info, pats))

    print()
    print("Pattern distribution (short functions):")
    for pat, items in by_pattern.items():
        print(f"  {pat}: {len(items)}")
    print()

    # Count BL-only (reloc) mismatches for reporting
    bl_only_count = 0
    bl_symbols = {}
    for info, _ in by_pattern['unclassified']:
        all_bl = all(
            (info.orig_words[i] >> 26) == (info.decomp_words[i] >> 26) == 0x25
            for i in info.diff_indices
        )
        if all_bl:
            bl_only_count += 1

    if not args.fix:
        # Show details for each pattern
        for pat, items in by_pattern.items():
            if not items or pat == 'unclassified':
                continue
            print(f"=== {pat} ({len(items)} functions) ===")
            for info, pats in items[:10]:
                src_path = find_source_for_obj(info.obj_file)
                src_name = src_path.name if src_path else '?'
                print(f"  {info.short_name} ({info.num_insns}i, {info.num_diffs}d) [{src_name}]")
                for pt, pd in pats:
                    if pt == 'sf_bit':
                        for di in pd:
                            o = info.orig_words[di]
                            d = info.decomp_words[di]
                            direction = 'narrow' if sf_bit(o) == 0 else 'widen'
                            print(f"    sf_bit[{di}]: {direction} (orig=0x{o:08x} decomp=0x{d:08x})")
                    elif pt == 'bool_trunc':
                        for direction, di, reg in pd:
                            print(f"    bool[{di}]: {direction} w{reg}")
                    elif pt == 'br_reg':
                        for di, ob, db in pd:
                            print(f"    br[{di}]: orig=x{ob} decomp=x{db} (delta={ob-db})")
            if len(items) > 10:
                print(f"  ... and {len(items) - 10} more")
            print()

        if bl_only_count:
            print(f"NOTE: {bl_only_count} functions have BL-only mismatches (relocation issue,")
            print(f"  likely wrong 'abort' address in functions.csv - not a source code problem)")
            print()
        return

    # Apply fixes
    fix_count = 0
    fail_count = 0
    skip_count = 0
    patterns_to_try = ['sf_bit', 'bool_trunc', 'br_reg', 'return_type', 'vtable_infer'] if args.pattern == 'all' else [args.pattern]

    # Group by source file for efficient recompilation
    for pat in patterns_to_try:
        items = by_pattern.get(pat, [])
        if not items:
            continue

        print(f"=== Fixing {pat} ({len(items)} candidates) ===")

        for info, pats in items:
            if args.limit > 0 and fix_count >= args.limit:
                print(f"Reached limit of {args.limit} fixes")
                break

            src_path = find_source_for_obj(info.obj_file)
            if src_path is None:
                skip_count += 1
                continue

            print(f"  {info.short_name} ({info.num_insns}i, {info.num_diffs}d)...")

            fix_result = None
            if pat == 'sf_bit':
                fix_result = fix_sf_bit(info, src_path, pats)
            elif pat == 'bool_trunc':
                fix_result = fix_bool_trunc(info, src_path, pats)
            elif pat == 'br_reg':
                fix_result = fix_br_reg(info, src_path, pats)
            elif pat == 'return_type':
                fix_result = fix_return_type(info, src_path, pats)
            elif pat == 'vtable_infer':
                fix_result = fix_vtable_comprehensive(info, src_path)

            if fix_result is None:
                skip_count += 1
                print(f"    No applicable fix found")
                continue

            if apply_and_verify_fix(info, fix_result, src_path, csv_lookup, dry_run=not args.fix):
                fix_count += 1
            else:
                fail_count += 1

    # Second pass: try return_type brute-force on remaining failures
    if args.fix and args.pattern == 'all':
        # Re-collect to find what's still non-matching
        print()
        print("=== Second pass: trying return type variations ===")
        remaining, csv_lookup = collect_non_matching()
        second_pass_fixes = 0
        for info in remaining:
            if args.limit > 0 and fix_count >= args.limit:
                break
            if info.num_insns > args.max_insns:
                continue
            src_path = find_source_for_obj(info.obj_file)
            if src_path is None:
                continue
            fix_result = fix_return_type(info, src_path, classify_mismatch(info))
            if fix_result is None:
                continue
            print(f"  {info.short_name} ({info.num_insns}i, {info.num_diffs}d)...")
            if apply_and_verify_fix(info, fix_result, src_path, csv_lookup):
                fix_count += 1
                second_pass_fixes += 1
        if second_pass_fixes:
            print(f"  Second pass fixed {second_pass_fixes} more functions")

    print()
    print(f"Results: {fix_count} fixed, {fail_count} failed, {skip_count} skipped")


if __name__ == '__main__':
    main()
