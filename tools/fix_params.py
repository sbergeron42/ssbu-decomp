#!/usr/bin/env python3
"""
Fix parameter counts in vtable dispatch functions by reading the original
binary's branch register to determine the correct number of parameters.
"""

import struct, subprocess, csv, re, sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
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


def extract_func_name(mangled):
    prefix = "_ZN3app8lua_bind"
    if not mangled.startswith(prefix): return None
    rest = mangled[len(prefix):]
    i = 0
    while i < len(rest) and rest[i].isdigit(): i += 1
    if i == 0: return None
    length = int(rest[:i]); name = rest[i:i+length]
    return name if len(name) == length else None


def guess_return_type(func_name):
    short = func_name.split('__')[1] if '__' in func_name else func_name
    if short.startswith('is_') or short.startswith('can_') or short.startswith('chk_'):
        return 'bool'
    if short.startswith('get_') and any(w in short for w in
            ['pos', 'speed', 'normal', 'scale', 'rotation', 'offset', 'movement']):
        return 'void*'
    if short.startswith('get_') and any(w in short for w in
            ['kind', 'flag', 'count', 'num', 'id', 'no', 'type', 'shape']):
        return 'u32'
    if short.startswith('get_') and any(w in short for w in ['radius']):
        return 'f32'
    if short.startswith('set_') or short.startswith('clear_') or \
       short.startswith('reset_') or short.startswith('enable_') or \
       short.startswith('unable_') or short.startswith('add_') or \
       short.startswith('entry_') or short.startswith('leave_') or \
       short.startswith('update_') or short.startswith('modify_'):
        return 'void'
    if short.startswith('get_'): return 'void*'
    return 'void*'


def main():
    dry_run = '--dry-run' in sys.argv

    csv_lookup = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f); next(reader)
        for row in reader:
            addr = int(row[0], 16); name = row[3]
            if name not in csv_lookup: csv_lookup[name] = addr
            if name.startswith('_ZN3app8lua_bind'):
                short = extract_func_name(name)
                if short and short not in csv_lookup: csv_lookup[short] = addr

    result = subprocess.run([OBJDUMP, '-t', str(DECOMP_ELF)], capture_output=True, text=True)
    symbols = []
    for line in result.stdout.split('\n'):
        if 'F .text' in line:
            parts = line.split()
            symbols.append((parts[-1], int(parts[0], 16), int(parts[4], 16)))

    orig_segs = load_elf_segments(ORIGINAL_ELF)
    decomp_segs = load_elf_segments(DECOMP_ELF)

    # Find fixable functions
    fixes = {}  # func_name -> (module_name, correct_line)

    with open(ORIGINAL_ELF, 'rb') as of_, open(DECOMP_ELF, 'rb') as df_:
        for mangled, daddr, size in symbols:
            fn = extract_func_name(mangled)
            if not fn or fn not in csv_lookup: continue
            oaddr = csv_lookup[fn]
            ovaddr = oaddr - ELF_BASE if oaddr >= ELF_BASE else oaddr
            ob = read_bytes(of_, orig_segs, ovaddr, size)
            db = read_bytes(df_, decomp_segs, daddr, size)
            if not ob or not db: continue
            if ob == db: continue  # already matching

            # Read original instructions to determine correct code
            orig_insns = [struct.unpack('<I', ob[i:i+4])[0] for i in range(0, len(ob), 4)]

            # Only handle tail-call patterns (4-5 insns)
            n = len(orig_insns)
            if n > 5: continue

            # Find the br instruction
            br_reg = None
            for insn in orig_insns:
                if (insn & 0xFFFFFC1F) == 0xD61F0000:
                    br_reg = (insn >> 5) & 0x1F
                    break
            if br_reg is None: continue

            # Find vtable LDR (3rd instruction typically)
            vt_off = None
            for insn in orig_insns:
                if (insn & 0xFFC00000) == 0xF9400000:
                    rn = (insn >> 5) & 0x1F
                    if rn == 8:  # ldr xN, [x8, #off] — vtable access
                        vt_off = ((insn >> 10) & 0xFFF) * 8
            if vt_off is None: continue

            # Find module offset (first LDR from x0)
            mod_off = None
            for insn in orig_insns:
                if (insn & 0xFFC00000) == 0xF9400000:
                    rn = (insn >> 5) & 0x1F
                    rt = insn & 0x1F
                    if rn == 0 and rt == 0:
                        mod_off = ((insn >> 10) & 0xFFF) * 8
                        break
            if mod_off is None: continue

            # Determine params from br register
            num_params = br_reg - 1  # x0=module, x1..x(br_reg-1)=params

            # Check for bool masking (and wN, wN, #1)
            bool_params = set()
            for insn in orig_insns:
                if (insn & 0xFFFFFC00) == 0x12000000:
                    rd = insn & 0x1F
                    bool_params.add(rd)

            # Get module name from function name
            module = fn.split('__')[0]

            # Build correct C++ line
            ret_type = guess_return_type(fn)
            ret = 'return ' if ret_type != 'void' else ''

            params = []
            args = []
            cast_params = ['void*']

            # Determine first param type based on module
            first_param = 'BattleObjectModuleAccessor* a'
            macro = f'reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+{mod_off:#x}))'

            params.append(first_param)
            args.append('m')

            for i in range(num_params):
                reg = i + 1
                if reg in bool_params:
                    params.append(f'bool p{i+1}')
                    cast_params.append('bool')
                else:
                    params.append(f'u64 p{i+1}')
                    cast_params.append('u64')
                args.append(f'p{i+1}')

            params_str = ','.join(params)
            args_str = ','.join(args)
            cast_params_str = ','.join(cast_params)
            cast_ret = ret_type if ret_type != 'void' else 'void'

            fixes[fn] = f'{ret_type} {fn}({params_str}) {{ auto* m={macro}; {ret}reinterpret_cast<{cast_ret}(*)({cast_params_str})>(VT(m)[{vt_off:#x}/8])({args_str}); }}'

    print(f"Found {len(fixes)} fixable functions")

    if dry_run:
        for fn, line in sorted(fixes.items()):
            print(line)
        return

    # Apply fixes to source files
    src_dir = PROJECT_ROOT / "src" / "app"
    fixed_count = 0

    for src_file in list(src_dir.rglob("*.cpp")):
        content = src_file.read_text()
        lines = content.split('\n')
        changed = False

        for i, line in enumerate(lines):
            # Find function definitions
            for fn, new_line in fixes.items():
                if fn + '(' in line and 'VT(m)' in line:
                    if lines[i].strip() != new_line.strip():
                        lines[i] = new_line
                        changed = True
                        fixed_count += 1

        if changed:
            src_file.write_text('\n'.join(lines))
            print(f"  Updated {src_file.name}")

    print(f"Fixed {fixed_count} functions")


if __name__ == '__main__':
    main()
