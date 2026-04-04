#!/usr/bin/env python3
"""
Compare compiled function bytes against the original binary.
Simpler/faster alternative to show_diff.py for quick checks.

Usage:
    python tools/compare_bytes.py FUN_71000007c0
    python tools/compare_bytes.py 0x71000007c0
    python tools/compare_bytes.py FUN_71000007c0_7c0
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


def find_in_o_files(name_query):
    """Find a function in .o files by name substring."""
    for fn in sorted(os.listdir(BUILD_DIR)):
        if not fn.endswith('.o'):
            continue
        try:
            with open(BUILD_DIR / fn, 'rb') as f:
                ident = f.read(16)
                if ident[:4] != b'\x7fELF':
                    continue
                f.seek(0x28)
                shoff = struct.unpack('<Q', f.read(8))[0]
                f.seek(0x3a)
                shentsize = struct.unpack('<H', f.read(2))[0]
                shnum = struct.unpack('<H', f.read(2))[0]
                shstrndx = struct.unpack('<H', f.read(2))[0]
                f.seek(shoff + shstrndx * shentsize + 0x18)
                strtab_off = struct.unpack('<Q', f.read(8))[0]
                strtab_sz = struct.unpack('<Q', f.read(8))[0]
                f.seek(strtab_off)
                strtab = f.read(strtab_sz)
                for i in range(shnum):
                    f.seek(shoff + i * shentsize)
                    sh_name_idx = struct.unpack('<I', f.read(4))[0]
                    sh_type = struct.unpack('<I', f.read(4))[0]
                    if sh_type != 1:
                        continue
                    end = strtab.index(b'\0', sh_name_idx)
                    sec_name = strtab[sh_name_idx:end].decode('ascii', errors='replace')
                    if not sec_name.startswith('.text.'):
                        continue
                    if name_query in sec_name:
                        f.seek(shoff + i * shentsize + 0x18)
                        sh_offset = struct.unpack('<Q', f.read(8))[0]
                        sh_size = struct.unpack('<Q', f.read(8))[0]
                        if sh_size == 0:
                            continue
                        f.seek(sh_offset)
                        code = f.read(sh_size)
                        return sec_name[6:], code, fn
        except (OSError, struct.error):
            pass
    return None, None, None


def main():
    if len(sys.argv) < 2 or sys.argv[1] == '--help':
        print(__doc__)
        return

    query = sys.argv[1]

    # Try to extract address from query
    addr = None
    m = re.search(r'(?:0x)?(71[0-9a-fA-F]{6,10})', query)
    if m:
        addr = int(m.group(1), 16)

    # Find in .o files
    mangled, decomp_bytes, o_file = find_in_o_files(query)
    if decomp_bytes is None:
        print("Function '%s' not found in build/*.o" % query)
        return

    print("Found: %s in %s (%d bytes)" % (mangled[:60], o_file, len(decomp_bytes)))

    # Find original address from CSV
    if addr is None:
        # Try to extract from function name
        m = re.search(r'([0-9a-f]{5,8})E?[A-Z]', mangled)
        if m:
            addr = 0x7100000000 + int(m.group(1), 16)

    if addr is None:
        print("Cannot determine original address")
        return

    # Read original bytes
    segments = load_elf_segments(ORIGINAL_ELF)
    vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
    with open(ORIGINAL_ELF, 'rb') as f:
        for seg_vaddr, seg_offset, seg_filesz in segments:
            if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
                f.seek(seg_offset + (vaddr - seg_vaddr))
                orig_bytes = f.read(len(decomp_bytes))
                break
        else:
            print("Address 0x%x not found in original ELF" % addr)
            return

    # Compare
    num_insns = len(decomp_bytes) // 4
    match = 0
    diff = 0
    for i in range(0, min(len(orig_bytes), len(decomp_bytes)), 4):
        o = orig_bytes[i:i + 4]
        d = decomp_bytes[i:i + 4]
        oi = struct.unpack('<I', o)[0]
        di = struct.unpack('<I', d)[0]
        status = "OK  " if o == d else "DIFF"
        if o == d:
            match += 1
        else:
            diff += 1
        print("  %3d  0x%08x  0x%08x  %s" % (i // 4, oi, di, status))

    print()
    print("%d/%d match (%.0f%%)" % (match, num_insns, match * 100 / num_insns if num_insns else 0))


if __name__ == '__main__':
    main()
