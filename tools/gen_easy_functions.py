#!/usr/bin/env python3
"""
Auto-generate EASY-tier functions (both named and FUN_*) from original ELF bytes.

Handles: noops, trampolines, field accessors, vtable dispatchers, tiny stubs.
These are 1-7 instruction functions with deterministic patterns.

Usage:
    python tools/gen_easy_functions.py                  # Dry run, show what would be generated
    python tools/gen_easy_functions.py --apply          # Generate and add to source files
    python tools/gen_easy_functions.py --apply --limit 500  # Generate up to N functions
"""

import csv
import struct
import subprocess
import sys
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
ELF_BASE = 0x7100000000


def load_elf_segments(path):
    segments = []
    with open(path, 'rb') as f:
        f.seek(0x20); phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36); phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]; f.read(4)
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1: segments.append((p_vaddr, p_offset, p_filesz))
    return segments


def read_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv)); return f.read(size)
    return None


def extract_func_name(m):
    prefix = "_ZN3app8lua_bind"
    if not m.startswith(prefix): return None
    rest = m[len(prefix):]
    i = 0
    while i < len(rest) and rest[i].isdigit(): i += 1
    if i == 0: return None
    l = int(rest[:i]); return rest[i:i+l] if len(rest[i:i+l]) == l else None


def make_safe_ident(name):
    """Convert a function name to a safe C identifier."""
    name = name.replace('.', '_').replace('::', '_').replace('<', '_').replace('>', '_')
    name = name.replace(',', '_').replace(' ', '_').replace('?', '_').replace('~', 'dtor_')
    name = name.replace('*', 'ptr').replace('+', 'plus').replace('-', 'minus')
    name = name.replace('=', 'eq').replace('(', '_').replace(')', '_')
    name = name.replace('[', '_').replace(']', '_')
    # Ensure it starts with a letter or underscore
    if name and name[0].isdigit():
        name = '_' + name
    return name


def generate_function(name, addr, insns, size):
    """Try to generate C++ for a function based on its instruction pattern."""
    n = len(insns)
    last = insns[-1]
    has_ret = last == 0xD65F03C0
    has_br = (last & 0xFFFFFC1F) == 0xD61F0000

    safe_name = make_safe_ident(name)
    # Always add address suffix to prevent duplicate symbols
    func_name = '%s_%x' % (safe_name, addr & 0xFFFFFFFF)

    # Pattern: just ret (noop)
    if n == 1 and has_ret:
        return 'void %s(void* obj) { }' % func_name

    # Pattern: single b (trampoline to external function)
    if n == 1 and (insns[0] & 0xFC000000) == 0x14000000:
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
        offset = insns[0] & 0x03FFFFFF
        if offset & (1 << 25):
            offset -= (1 << 26)
        target = vaddr + (offset << 2) + ELF_BASE
        target_name = 'FUN_%x' % target
        return ('extern "C" void %s(void*, u64, u64, u64, u64, u64, u64, u64);\n'
                'void %s(void* obj, u64 a1, u64 a2, u64 a3, u64 a4, u64 a5, u64 a6, u64 a7) '
                '{ %s(obj, a1, a2, a3, a4, a5, a6, a7); }' % (
                target_name, func_name, target_name))

    # Pattern: b external in multi-insn function — skip (complex)
    if n > 1 and any((i & 0xFC000000) == 0x14000000 for i in insns):
        return None

    # Pattern: add x0, x0, #imm; ret (return pointer to field)
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0x91000000:
        rd = insns[0] & 0x1F; rn = (insns[0] >> 5) & 0x1F
        if rd == 0 and rn == 0:
            imm = (insns[0] >> 10) & 0xFFF
            return 'void* %s(void* obj) { return reinterpret_cast<u8*>(obj) + %s; }' % (func_name, hex(imm))

    # Pattern: ldr field + ret (struct field read)
    if n == 2 and has_ret:
        if (insns[0] & 0xFFC00000) == 0xF9400000:  # ldr x0, [x0, #imm]
            imm = ((insns[0] >> 10) & 0xFFF) * 8
            return 'u64 %s(void* obj) { return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s); }' % (func_name, hex(imm))
        if (insns[0] & 0xFFC00000) == 0xB9400000:  # ldr w0, [x0, #imm]
            imm = ((insns[0] >> 10) & 0xFFF) * 4
            return 'u32 %s(void* obj) { return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s); }' % (func_name, hex(imm))
        if (insns[0] & 0xFFC00000) == 0x39400000:  # ldrb w0, [x0, #imm]
            imm = (insns[0] >> 10) & 0xFFF
            return 'u8 %s(void* obj) { return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s); }' % (func_name, hex(imm))

    # Pattern: movz w0, #imm; ret (return constant)
    if n == 2 and has_ret and (insns[0] & 0xFF800000) == 0x52800000:
        rd = insns[0] & 0x1F
        if rd == 0:
            val = (insns[0] >> 5) & 0xFFFF
            return 'u32 %s(void* obj) { return %s; }' % (func_name, hex(val))

    # Pattern: str x1, [x0, #imm]; ret (store 64-bit field)
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0xF9000000:
        rt = insns[0] & 0x1F; rn = (insns[0] >> 5) & 0x1F
        if rn == 0 and rt == 1:
            imm = ((insns[0] >> 10) & 0xFFF) * 8
            return 'void %s(void* obj, u64 val) { *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (func_name, hex(imm))

    # Pattern: str w1, [x0, #imm]; ret (store 32-bit field)
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0xB9000000:
        rt = insns[0] & 0x1F; rn = (insns[0] >> 5) & 0x1F
        if rn == 0 and rt == 1:
            imm = ((insns[0] >> 10) & 0xFFF) * 4
            return 'void %s(void* obj, u32 val) { *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (func_name, hex(imm))

    # Pattern: strb w1, [x0, #imm]; ret (store byte field)
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0x39000000:
        rt = insns[0] & 0x1F; rn = (insns[0] >> 5) & 0x1F
        if rn == 0 and rt == 1:
            imm = (insns[0] >> 10) & 0xFFF
            return 'void %s(void* obj, u8 val) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (func_name, hex(imm))

    # Pattern: ldrh w0, [x0, #imm]; ret (load 16-bit field)
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0x79400000:
        imm = ((insns[0] >> 10) & 0xFFF) * 2
        return 'u16 %s(void* obj) { return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(obj) + %s); }' % (func_name, hex(imm))

    # Pattern: mov+strb+ret (set flag)
    if n == 3 and has_ret and (insns[0] & 0xFF800000) == 0x52800000 and (insns[1] & 0xFFC00000) == 0x39000000:
        val = (insns[0] >> 5) & 0xFFFF
        off = (insns[1] >> 10) & 0xFFF
        return 'void %s(void* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = %d; }' % (func_name, hex(off), val)

    # Pattern: strb wzr+ret (clear flag)
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0x39000000 and (insns[0] & 0x1F) == 31:
        off = (insns[0] >> 10) & 0xFFF
        return 'void %s(void* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (func_name, hex(off))

    # Pattern: 3-insn vtable dispatch (ldr x8,[x0]; ldr xN,[x8,#off]; br xN)
    if n == 3 and has_br:
        if (insns[0] & 0xFFC00000) == 0xF9400000 and (insns[1] & 0xFFC00000) == 0xF9400000:
            rn0 = (insns[0] >> 5) & 0x1F; rt0 = insns[0] & 0x1F
            if rn0 == 0 and rt0 == 8:
                rn1 = (insns[1] >> 5) & 0x1F
                if rn1 == 8:
                    vt_off = ((insns[1] >> 10) & 0xFFF) * 8
                    br_reg = (last >> 5) & 0x1F
                    nparams = br_reg - 1
                    params = ['void* obj'] + ['u64 p%d' % (i+1) for i in range(nparams)]
                    args = ['obj'] + ['p%d' % (i+1) for i in range(nparams)]
                    cast_params = ['void*'] + ['u64'] * nparams
                    return 'void* %s(%s) { return reinterpret_cast<void*(*)(%s)>((*reinterpret_cast<void***>(obj))[%s/8])(%s); }' % (
                        func_name, ','.join(params), ','.join(cast_params), hex(vt_off), ','.join(args))

    # Pattern: 4-insn ADRP dispatch (adrp+ldr+add+br) — global function pointer jump
    if n == 4 and has_br and (insns[0] & 0x9F000000) == 0x90000000:
        if (insns[1] & 0xFFC00000) == 0xF9400000 and (insns[2] & 0x7F800000) == 0x11000000:
            # Decode ADRP target
            vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
            immlo = (insns[0] >> 29) & 0x3
            immhi = (insns[0] >> 5) & 0x7FFFF
            imm = (immhi << 2) | immlo
            if imm & (1 << 20):
                imm -= (1 << 21)
            page = (vaddr & ~0xFFF) + (imm << 12)
            ldr_off = ((insns[1] >> 10) & 0xFFF) * 8
            add_off_raw = (insns[2] >> 10) & 0xFFF
            add_shift = (insns[2] >> 22) & 0x3
            add_off = add_off_raw << (12 if add_shift == 1 else 0)
            global_addr = page + ldr_off + ELF_BASE
            br_reg = (last >> 5) & 0x1F
            # Number of forwarded params: br register index - 1
            # (x0-x4 are params, dispatch uses higher regs)
            nparams = max(0, br_reg - 1)
            params = ['void* obj'] + ['u64 p%d' % (i + 1) for i in range(nparams)]
            args = ['obj'] + ['p%d' % (i + 1) for i in range(nparams)]
            cast_params = ['void*'] + ['u64'] * nparams
            dat_name = 'DAT_%x' % global_addr
            return ('extern "C" void* %s;\n'
                    '__attribute__((naked))\n'
                    'void %s() {\n'
                    '    asm volatile(\n'
                    '        "adrp x16, %s\\n"\n'
                    '        "ldr x17, [x16, :lo12:%s]\\n"\n'
                    '        "add x16, x16, :lo12:%s\\n"\n'
                    '        "br x17\\n"\n'
                    '    );\n'
                    '}' % (dat_name, func_name, dat_name, dat_name, dat_name))

    # Pattern: 3-insn field read through pointer (ldr x8,[x0,#off1]; ldr/ldrb result,[x8,#off2]; ret)
    if n == 3 and has_ret:
        if (insns[0] & 0xFFC00000) == 0xF9400000 and (insns[1] & 0xFFC00000) in (0xF9400000, 0xB9400000, 0x39400000, 0xBD400000):
            off1 = ((insns[0] >> 10) & 0xFFF) * 8
            insn1 = insns[1]
            if (insn1 & 0xFFC00000) == 0xF9400000:
                off2 = ((insn1 >> 10) & 0xFFF) * 8
                ret_type = 'u64'
            elif (insn1 & 0xFFC00000) == 0xB9400000:
                off2 = ((insn1 >> 10) & 0xFFF) * 4
                ret_type = 'u32'
            elif (insn1 & 0xFFC00000) == 0x39400000:
                off2 = (insn1 >> 10) & 0xFFF
                ret_type = 'u8'
            elif (insn1 & 0xFFC00000) == 0xBD400000:
                off2 = ((insn1 >> 10) & 0xFFF) * 4
                ret_type = 'f32'
            else:
                return None
            return '%s %s(void* obj) { auto* p = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(obj) + %s); return *reinterpret_cast<%s*>(p + %s); }' % (
                ret_type, func_name, hex(off1), ret_type, hex(off2))

    return None


def main():
    do_apply = '--apply' in sys.argv
    limit = 99999
    for i, arg in enumerate(sys.argv):
        if arg == '--limit' and i + 1 < len(sys.argv):
            limit = int(sys.argv[i + 1])

    segments = load_elf_segments(ORIGINAL_ELF)

    # Get already compiled (scan .o files)
    import os
    compiled = set()
    for fn in os.listdir(PROJECT_ROOT / 'build'):
        if not fn.endswith('.o'):
            continue
        result = subprocess.run([OBJDUMP, '-t', str(PROJECT_ROOT / 'build' / fn)],
                              capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'F .text' in line:
                name = line.split()[-1]
                compiled.add(name)
                short = extract_func_name(name)
                if short:
                    compiled.add(short)

    # Load undecompiled functions
    targets = []
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f); next(reader)
        for row in reader:
            if row[1] != 'U': continue
            name = row[3]
            if name in compiled: continue
            if name.startswith('__'): continue
            addr = int(row[0], 16)
            size = int(row[2])
            if size > 32: continue  # only tiny functions
            targets.append((addr, name, size))

    print("Targets: %d undecompiled functions <= 32B" % len(targets))

    generated = defaultdict(list)  # filename -> [(name, code)]
    skipped = 0
    count = 0

    with open(ORIGINAL_ELF, 'rb') as f:
        for addr, name, size in targets:
            if count >= limit: break
            vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
            raw = read_bytes(f, segments, vaddr, max(size, 32))
            if not raw: continue

            insns = []
            for i in range(0, min(len(raw), 32), 4):
                insn = struct.unpack('<I', raw[i:i+4])[0]
                insns.append(insn)
                if insn == 0xD65F03C0 or (insn & 0xFFFFFC1F) == 0xD61F0000: break

            code = generate_function(name, addr, insns, size)
            if code is None:
                skipped += 1
                continue

            # Determine target file
            if '__' in name and not name.startswith('FUN_'):
                module = name.split('__')[0]
                filename = module
            else:
                # Group FUN_* by address range
                region = (addr >> 20) & 0xFFF
                filename = 'fun_region_%03x' % region

            generated[filename].append((name, addr, code))
            count += 1

    total = sum(len(v) for v in generated.values())
    print("Generated: %d, Skipped: %d" % (total, skipped))
    print("Files: %d" % len(generated))

    if not do_apply:
        print()
        print("Sample generated code:")
        shown = 0
        for filename, funcs in sorted(generated.items()):
            for name, faddr, code in funcs[:3]:
                print("  [%s] %s" % (filename, code[:100]))
                shown += 1
                if shown >= 15: break
            if shown >= 15: break
        print()
        print("Use --apply to write to source files")
        return

    # Write to source files
    src_dir = PROJECT_ROOT / 'src' / 'app'
    for filename, funcs in sorted(generated.items()):
        if filename.startswith('fun_region_'):
            # New file for FUN_* functions
            filepath = src_dir / ('%s.cpp' % filename)
            if filepath.exists():
                content = filepath.read_text()
            else:
                content = '#include "types.h"\n\nnamespace app::lua_bind {\n\n} // namespace app::lua_bind\n'

            # Split extern declarations from function bodies
            externs = set()
            func_block = '// Auto-generated EASY functions\n'
            for name, faddr, code in funcs:
                lines = code.split('\n')
                func_lines = []
                for line in lines:
                    if line.startswith('extern "C"'):
                        externs.add(line)
                    else:
                        func_lines.append(line)
                func_block += '// 0x%x\n%s\n' % (faddr, '\n'.join(func_lines))

            # Insert externs before namespace, functions inside namespace
            if externs:
                extern_block = '\n'.join(sorted(externs)) + '\n\n'
                content = content.replace('namespace app::lua_bind {',
                                         extern_block + 'namespace app::lua_bind {')
            content = content.replace('} // namespace app::lua_bind',
                                     func_block + '} // namespace app::lua_bind')
            filepath.write_text(content)
            print("  %s: %d functions" % (filepath.name, len(funcs)))
        else:
            # Existing module file
            candidates = list(src_dir.rglob('%s.cpp' % filename))
            if candidates:
                filepath = candidates[0]
                content = filepath.read_text()
                if '} // namespace app::lua_bind' in content:
                    block = ''
                    for name, faddr, code in funcs:
                        if name + '(' not in content:
                            block += '// 0x%x\n%s\n' % (faddr, code)
                    if block:
                        content = content.replace('} // namespace app::lua_bind',
                                                 block + '} // namespace app::lua_bind')
                        filepath.write_text(content)
                        print("  %s: +%d functions" % (filepath.name, block.count('\n')))
            else:
                filepath = src_dir / ('%s.cpp' % filename)
                content = '#include "types.h"\n\nnamespace app::lua_bind {\n\n'
                for name, faddr, code in funcs:
                    content += '// 0x%x\n%s\n' % (faddr, code)
                content += '\n} // namespace app::lua_bind\n'
                filepath.write_text(content)
                print("  Created %s: %d functions" % (filepath.name, len(funcs)))

    print()
    print("Done! Run 'cmd /c build.bat' to compile.")


if __name__ == '__main__':
    main()
