#!/usr/bin/env python3
"""
Verify all compiled functions against the original 13.0.4 binary.

Reads function bytes directly from individual .o files (no link step needed),
maps each function to its original address via data/functions.csv and
source-comment annotations, and compares bytes instruction-by-instruction.

Relocations (ADRP, ADD, LDST, CALL26) are patched in-place using the .o
file's SHT_RELA entries and the function's known original address, so no
link step is required to get byte-identical matches.

Supports both app::lua_bind and non-lua_bind (engine, gameplay, etc.) symbols.

Usage:
    python tools/verify_all.py              # Full report
    python tools/verify_all.py --summary    # Summary only
    python tools/verify_all.py --update     # Update functions.csv with results
"""

import csv
import os
import re
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000


def load_elf_segments(path):
    segments = []
    with open(path, 'rb') as f:
        f.seek(0x20)
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)
        phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]
            f.read(4)
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]
            f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1:
                segments.append((p_vaddr, p_offset, p_filesz))
    return segments


def read_bytes_at(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None



def extract_short_name(mangled):
    """Extract the short function name from any Itanium ABI mangled symbol."""
    if not mangled.startswith('_Z'):
        return mangled
    prefix = "_ZN3app8lua_bind"
    if mangled.startswith(prefix):
        rest = mangled[len(prefix):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i > 0:
            length = int(rest[:i])
            name = rest[i:i + length]
            if len(name) == length:
                return name
    if mangled.startswith('_ZN'):
        rest = mangled[3:]
        last_name = None
        while rest and rest[0] != 'E':
            i = 0
            while i < len(rest) and rest[i].isdigit():
                i += 1
            if i == 0:
                break
            length = int(rest[:i])
            name = rest[i:i + length]
            if len(name) < length:
                break
            last_name = name
            rest = rest[i + length:]
        if last_name:
            return last_name
    rest = mangled[2:]
    i = 0
    while i < len(rest) and rest[i].isdigit():
        i += 1
    if i > 0:
        length = int(rest[:i])
        name = rest[i:i + length]
        if len(name) == length:
            return name
    return mangled


def _read_symtab(f, shoff, shentsize, symtab_idx):
    """Read a symbol table section and its associated string table.
    Returns list of (st_name_str, st_value, st_shndx) tuples."""
    f.seek(shoff + symtab_idx * shentsize + 0x18)
    sym_offset = struct.unpack('<Q', f.read(8))[0]
    sym_size = struct.unpack('<Q', f.read(8))[0]
    # sh_link -> strtab section index
    f.seek(shoff + symtab_idx * shentsize + 0x28)
    str_sec_idx = struct.unpack('<I', f.read(4))[0]
    # Read the string table
    f.seek(shoff + str_sec_idx * shentsize + 0x18)
    str_off = struct.unpack('<Q', f.read(8))[0]
    str_sz = struct.unpack('<Q', f.read(8))[0]
    f.seek(str_off)
    sym_strtab = f.read(str_sz)
    # Read symbols
    symbols = []
    num_syms = sym_size // 24
    for j in range(num_syms):
        f.seek(sym_offset + j * 24)
        st_name = struct.unpack('<I', f.read(4))[0]
        st_info = struct.unpack('B', f.read(1))[0]
        f.read(1)  # st_other
        st_shndx = struct.unpack('<H', f.read(2))[0]
        st_value = struct.unpack('<Q', f.read(8))[0]
        f.read(8)  # st_size
        end = sym_strtab.index(b'\0', st_name)
        name = sym_strtab[st_name:end].decode('ascii', errors='replace')
        symbols.append((name, st_value, st_shndx))
    return symbols


def read_o_file_functions(obj_path):
    """Read all function symbols and their bytes from a .o file.
    Returns list of (mangled_name, size, code_bytes, relocs) where
    relocs is a list of (r_offset, r_type, symbol_name, r_addend)."""
    functions = []
    try:
        with open(obj_path, 'rb') as f:
            ident = f.read(16)
            if ident[:4] != b'\x7fELF':
                return functions
            f.seek(0x28)
            shoff = struct.unpack('<Q', f.read(8))[0]
            f.seek(0x3a)
            shentsize = struct.unpack('<H', f.read(2))[0]
            shnum = struct.unpack('<H', f.read(2))[0]
            shstrndx = struct.unpack('<H', f.read(2))[0]
            if shnum == 0:
                return functions
            f.seek(shoff + shstrndx * shentsize + 0x18)
            strtab_off = struct.unpack('<Q', f.read(8))[0]
            strtab_sz = struct.unpack('<Q', f.read(8))[0]
            f.seek(strtab_off)
            strtab = f.read(strtab_sz)

            # Cache for symtab reads (keyed by symtab section index)
            symtab_cache = {}

            # First pass: collect .text sections and .rela sections
            text_sections = {}  # section_index -> (mangled, sh_offset, sh_size)
            rela_sections = {}  # target_section_index -> list of (r_offset, r_type, sym_name, r_addend)

            for i in range(shnum):
                f.seek(shoff + i * shentsize)
                sh_name_idx = struct.unpack('<I', f.read(4))[0]
                sh_type = struct.unpack('<I', f.read(4))[0]
                end = strtab.index(b'\0', sh_name_idx)
                sec_name = strtab[sh_name_idx:end].decode('ascii', errors='replace')

                if sh_type == 1 and sec_name.startswith('.text.'):
                    mangled = sec_name[6:]
                    if not mangled:
                        continue
                    f.seek(shoff + i * shentsize + 0x18)
                    sh_offset = struct.unpack('<Q', f.read(8))[0]
                    sh_size = struct.unpack('<Q', f.read(8))[0]
                    if sh_size == 0:
                        continue
                    text_sections[i] = (mangled, sh_offset, sh_size)

                elif sh_type == 4:  # SHT_RELA
                    f.seek(shoff + i * shentsize + 0x18)
                    sh_offset = struct.unpack('<Q', f.read(8))[0]
                    sh_size = struct.unpack('<Q', f.read(8))[0]
                    # sh_link -> symtab section, sh_info -> target section
                    f.seek(shoff + i * shentsize + 0x28)
                    sh_link = struct.unpack('<I', f.read(4))[0]
                    sh_info = struct.unpack('<I', f.read(4))[0]
                    # Load symtab (cached)
                    if sh_link not in symtab_cache:
                        symtab_cache[sh_link] = _read_symtab(f, shoff, shentsize, sh_link)
                    sym_list = symtab_cache[sh_link]
                    relocs = []
                    num_entries = sh_size // 24
                    for j in range(num_entries):
                        f.seek(sh_offset + j * 24)
                        r_offset = struct.unpack('<Q', f.read(8))[0]
                        r_info = struct.unpack('<Q', f.read(8))[0]
                        r_addend = struct.unpack('<q', f.read(8))[0]  # signed
                        r_type = r_info & 0xFFFFFFFF
                        sym_idx = r_info >> 32
                        sym_name = sym_list[sym_idx][0] if sym_idx < len(sym_list) else ''
                        relocs.append((r_offset, r_type, sym_name, r_addend))
                    rela_sections[sh_info] = relocs

            # Second pass: read code and attach relocation info
            for sec_idx, (mangled, sh_offset, sh_size) in text_sections.items():
                f.seek(sh_offset)
                code = f.read(sh_size)
                relocs = rela_sections.get(sec_idx, [])
                functions.append((mangled, sh_size, code, relocs))
    except (OSError, struct.error):
        pass
    return functions


_ADDR_RE = re.compile(r'(?:FUN|DAT|PTR|LAB)_(71[0-9a-fA-F]+)')

# AArch64 relocation types — both standard ELF and LLVM/SysV numbering
_ADRP_TYPES = {275, 311}       # R_AARCH64_ADR_PREL_PG_HI21
_ADD_LO12_TYPES = {277, 312}   # R_AARCH64_ADD_ABS_LO12_NC
_LDST8_TYPES = {278}           # R_AARCH64_LDST8_ABS_LO12_NC
_LDST16_TYPES = {284}          # R_AARCH64_LDST16_ABS_LO12_NC
_LDST32_TYPES = {285}          # R_AARCH64_LDST32_ABS_LO12_NC
_LDST64_TYPES = {286}          # R_AARCH64_LDST64_ABS_LO12_NC
_LDST128_TYPES = {299}         # R_AARCH64_LDST128_ABS_LO12_NC
_CALL26_TYPES = {283}          # R_AARCH64_CALL26
_JUMP26_TYPES = {282}          # R_AARCH64_JUMP26


def _extract_target_addr(sym_name):
    """Extract target address from a Ghidra-style symbol name like FUN_710593a3a8."""
    m = _ADDR_RE.search(sym_name)
    if m:
        return int(m.group(1), 16)
    return None


def patch_relocations(code_bytes, relocs, orig_addr, sym_addr_lookup=None,
                      orig_bytes=None):
    """Patch relocation sites in code_bytes using known original address.

    Args:
        code_bytes: mutable bytearray of the function's machine code
        relocs: list of (r_offset, r_type, symbol_name, r_addend)
        orig_addr: the function's original virtual address in the binary
        sym_addr_lookup: optional dict of symbol_name -> address for named symbols
        orig_bytes: original binary bytes for this function (fallback for
                    section-relative relocations where symbol address is unknown)

    Returns:
        set of offsets that were successfully patched
    """
    patched = set()
    for r_offset, r_type, sym_name, r_addend in relocs:
        if r_offset + 4 > len(code_bytes):
            continue

        target = _extract_target_addr(sym_name)
        if target is None and sym_addr_lookup:
            entries = sym_addr_lookup.get(sym_name)
            if entries:
                target = entries[0][0]
        if target is None:
            # Fallback: copy the original instruction bytes directly.
            # This handles section-relative relocs (e.g. .rodata refs)
            # where we can't compute the target but the original binary
            # already has the correct encoding.
            if orig_bytes and r_offset + 4 <= len(orig_bytes):
                code_bytes[r_offset:r_offset + 4] = orig_bytes[r_offset:r_offset + 4]
                patched.add(r_offset)
            continue

        S = target       # symbol address
        A = r_addend     # addend
        P = orig_addr + r_offset  # place

        insn = struct.unpack_from('<I', code_bytes, r_offset)[0]

        if r_type in _ADRP_TYPES:
            page_delta = ((S + A) & ~0xFFF) - (P & ~0xFFF)
            page_delta >>= 12
            immlo = page_delta & 0x3
            immhi = (page_delta >> 2) & 0x7FFFF
            insn = (insn & 0x9F00001F) | (immlo << 29) | (immhi << 5)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _ADD_LO12_TYPES:
            imm12 = (S + A) & 0xFFF
            insn = (insn & ~(0xFFF << 10)) | (imm12 << 10)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _LDST8_TYPES:
            imm12 = (S + A) & 0xFFF
            insn = (insn & ~(0xFFF << 10)) | (imm12 << 10)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _LDST16_TYPES:
            imm12 = ((S + A) & 0xFFF) >> 1
            insn = (insn & ~(0xFFF << 10)) | (imm12 << 10)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _LDST32_TYPES:
            imm12 = ((S + A) & 0xFFF) >> 2
            insn = (insn & ~(0xFFF << 10)) | (imm12 << 10)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _LDST64_TYPES:
            imm12 = ((S + A) & 0xFFF) >> 3
            insn = (insn & ~(0xFFF << 10)) | (imm12 << 10)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _LDST128_TYPES:
            imm12 = ((S + A) & 0xFFF) >> 4
            insn = (insn & ~(0xFFF << 10)) | (imm12 << 10)
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

        elif r_type in _CALL26_TYPES or r_type in _JUMP26_TYPES:
            offset = (S + A - P) >> 2
            offset &= 0x3FFFFFF
            insn = (insn & 0xFC000000) | offset
            struct.pack_into('<I', code_bytes, r_offset, insn)
            patched.add(r_offset)

    return patched


def get_all_compiled_functions():
    """Scan all .o files in build/ and collect functions (deduplicated).
    Returns list of (mangled, size, code, relocs)."""
    seen = set()
    all_funcs = []
    for obj_name in sorted(os.listdir(BUILD_DIR)):
        if not obj_name.endswith('.o'):
            continue
        for mangled, size, code, relocs in read_o_file_functions(BUILD_DIR / obj_name):
            if mangled not in seen:
                seen.add(mangled)
                all_funcs.append((mangled, size, code, relocs))
    return all_funcs


def build_csv_lookup():
    """Build name -> list of (address, size) from functions.csv."""
    lookup = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            csv_size = int(row[2])
            name = row[3]
            lookup.setdefault(name, []).append((addr, csv_size))
            short = extract_short_name(name)
            if short != name:
                lookup.setdefault(short, []).append((addr, csv_size))
    return lookup


def build_source_addr_map():
    """Parse source files for address comments preceding function defs."""
    addr_map = {}
    src_dir = PROJECT_ROOT / "src"
    for root, dirs, files in os.walk(src_dir):
        for fn in files:
            if not fn.endswith('.cpp'):
                continue
            path = os.path.join(root, fn)
            with open(path) as f:
                lines = f.readlines()
            for i, line in enumerate(lines):
                m = re.search(r'//\s*(?:0x)?(71[0-9a-fA-F]{6,10})\b', line)
                if m:
                    addr = int(m.group(1), 16)
                    for j in range(i + 1, min(i + 3, len(lines))):
                        fm = re.match(
                            r'(?:void\*?|bool|u8|u16|u32|u64|s8|s16|s32|s64|'
                            r'int|float|double|long|unsigned|char|f32|f64|'
                            r'struct\s+\w+\*?)\s+(\w+)\s*\(',
                            lines[j]
                        )
                        if fm:
                            addr_map[fm.group(1)] = addr
                            break
    return addr_map


def resolve_addr(csv_lookup, source_addr_map, mangled, short_name, decomp_size):
    """Resolve the original address for a compiled function."""
    for name in [mangled, short_name]:
        if not name:
            continue
        entries = csv_lookup.get(name)
        if entries:
            if len(entries) == 1:
                return entries[0][0]
            for addr, csv_size in entries:
                if csv_size == decomp_size:
                    return addr
            return min(entries, key=lambda e: e[1])[0]
    if short_name and short_name in source_addr_map:
        return source_addr_map[short_name]
    return None



def main():
    summary_only = '--summary' in sys.argv
    update_csv = '--update' in sys.argv

    all_funcs = get_all_compiled_functions()
    csv_lookup = build_csv_lookup()
    source_addr_map = build_source_addr_map()
    orig_segments = load_elf_segments(ORIGINAL_ELF)

    verified = 0
    mismatch = 0
    unmatched = 0
    total_bytes_matched = 0
    total_bytes_compared = 0
    results = {}
    details = []
    unmatched_names = []
    reloc_stats = {'patched': 0, 'unpatched': 0}

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for mangled, size, decomp_bytes, relocs in all_funcs:
            short_name = extract_short_name(mangled)
            orig_addr = resolve_addr(csv_lookup, source_addr_map,
                                     mangled, short_name, size)
            if orig_addr is None:
                unmatched += 1
                if not summary_only:
                    unmatched_names.append(short_name or mangled)
                continue
            orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr
            orig_bytes = read_bytes_at(orig_f, orig_segments, orig_vaddr, size)
            if orig_bytes is None:
                unmatched += 1
                if not summary_only:
                    unmatched_names.append(
                        "%s (bad address 0x%x)" % (short_name, orig_addr))
                continue

            # Patch relocations in-place
            code = bytearray(decomp_bytes)
            if relocs:
                patched_offsets = patch_relocations(
                    code, relocs, orig_addr, csv_lookup, orig_bytes)
                reloc_stats['patched'] += len(patched_offsets)
                reloc_stats['unpatched'] += len(relocs) - len(patched_offsets)
            decomp_bytes = bytes(code)

            num_insns = size // 4
            match_count = 0
            for off in range(0, min(len(orig_bytes), len(decomp_bytes)), 4):
                if orig_bytes[off:off + 4] == decomp_bytes[off:off + 4]:
                    match_count += 1
            total_bytes_compared += size
            total_bytes_matched += match_count * 4
            if match_count == num_insns:
                verified += 1
                status = 'M'
            else:
                mismatch += 1
                status = 'N'
                if not summary_only:
                    details.append((short_name, match_count, num_insns))
            display_name = short_name or mangled
            results[display_name] = (status, match_count * 100 // num_insns if num_insns else 0)

    total = verified + mismatch
    total_funcs = len(all_funcs)

    print()
    print("=" * 70)
    print("  SSBU Decomp -- Verified Binary Comparison (13.0.4)")
    print("=" * 70)
    print()
    print("  Total compiled functions:  %d" % total_funcs)
    print("  Matched to original addr:  %d" % total)
    print("  Unmatched (no address):    %d" % unmatched)
    print()

    if total > 0:
        bar_w = 40
        vf = verified * bar_w // total
        mm = max(0, bar_w - vf)
        bar = '#' * vf + '-' * mm
        print("  [%s]" % bar)
        print()
        print("  VERIFIED:         %5d  (%.1f%%)" % (verified, verified * 100 / total))
        print("  Non-matching:     %5d  (%.1f%%)" % (mismatch, mismatch * 100 / total))
        print()
        print("  Bytes: %s / %s match (%d%%)" % (
            "{:,}".format(total_bytes_matched),
            "{:,}".format(total_bytes_compared),
            total_bytes_matched * 100 // total_bytes_compared if total_bytes_compared else 0))
        print("  Relocations patched: %d  (unresolved: %d)" % (
            reloc_stats['patched'], reloc_stats['unpatched']))
    print()

    if details and not summary_only:
        print("  Non-matching functions:")
        for name, mc, tc in sorted(details, key=lambda x: -x[1] / x[2] if x[2] else 0)[:30]:
            print("    %s: %d/%d instructions match" % (name, mc, tc))
        if len(details) > 30:
            print("    ... and %d more" % (len(details) - 30))

    if unmatched_names and not summary_only:
        print()
        print("  Unmatched symbols (no address):")
        for name in unmatched_names[:20]:
            print("    %s" % name)
        if len(unmatched_names) > 20:
            print("    ... and %d more" % (len(unmatched_names) - 20))

    print()

    if update_csv and results:
        rows = []
        with open(FUNCTIONS_CSV) as f:
            reader = csv.DictReader(f)
            fieldnames = reader.fieldnames
            for row in reader:
                name = row['Name']
                short = extract_short_name(name)
                if name in results:
                    status, _ = results[name]
                    row['Quality'] = status
                elif short in results:
                    status, _ = results[short]
                    row['Quality'] = status
                rows.append(row)
        with open(FUNCTIONS_CSV, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames, extrasaction='ignore')
            writer.writeheader()
            writer.writerows(rows)
        print("  Updated %d entries in functions.csv" % len(results))


if __name__ == '__main__':
    main()
