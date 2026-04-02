#!/usr/bin/env python3
"""Generate whitelist of mangled function names that need epilogue swap."""

import struct
import sys
import re
import glob
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from verify_all import (
    get_all_compiled_functions, build_csv_lookup, build_source_addr_map,
    load_elf_segments, read_bytes_at, resolve_addr, extract_short_name,
    patch_relocations, ORIGINAL_ELF, ELF_BASE, PROJECT_ROOT
)

LDP_MASK = 0xFFC07FFF
LDP_BITS = 0xA8C00000 | (30 << 10) | (31 << 5) | 29
RET = 0xd65f03c0


def main():
    all_funcs = get_all_compiled_functions()
    csv_lookup = build_csv_lookup()
    source_addr_map = build_source_addr_map()
    orig_segments = load_elf_segments(ORIGINAL_ELF)

    # Get batch_c/d function names from source
    my_files = sorted(
        glob.glob(str(PROJECT_ROOT / 'src' / 'app' / 'fun_batch_c_*.cpp')) +
        glob.glob(str(PROJECT_ROOT / 'src' / 'app' / 'fun_batch_d_*.cpp'))
    )
    my_funcs = set()
    for f in my_files:
        with open(f) as fh:
            for line in fh:
                m = re.match(r'\S+\s+(FUN_\w+)\s*\(', line)
                if m:
                    my_funcs.add(m.group(1))

    # Build mangled name -> short name map
    func_data = {}
    for mangled, size, decomp_bytes, relocs in all_funcs:
        short_name = extract_short_name(mangled)
        if short_name in my_funcs:
            func_data[short_name] = (mangled, size)

    needs_swap = []
    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for fn in my_funcs:
            if fn not in func_data:
                continue
            mangled, size = func_data[fn]
            orig_addr = resolve_addr(csv_lookup, source_addr_map, mangled, fn, size)
            if orig_addr is None:
                continue
            orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr
            orig_bytes = read_bytes_at(orig_f, orig_segments, orig_vaddr, size)
            if orig_bytes is None:
                continue
            num = size // 4
            if num < 3:
                continue
            insns = [struct.unpack('<I', orig_bytes[i*4:i*4+4])[0] for i in range(num)]

            # Check: original has [ldp x29,x30,[sp],#N] [mov w0/x0,...] [ret]
            if (insns[-1] == RET and
                (insns[-3] & LDP_MASK) == LDP_BITS and
                (insns[-2] & 0x1F) == 0):
                needs_swap.append(mangled)

    out = PROJECT_ROOT / 'build' / 'epilogue_swap_list.txt'
    out.parent.mkdir(exist_ok=True)
    with open(out, 'w') as f:
        for name in sorted(needs_swap):
            f.write(name + '\n')


if __name__ == '__main__':
    main()
