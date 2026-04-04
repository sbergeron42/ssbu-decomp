#!/usr/bin/env python3
"""
Find the next batch of uncompiled functions to decomp.
Replaces the inline Python that workers write hundreds of times.

Usage:
    python tools/next_batch.py                              # Show 30 uncompiled MEDIUM
    python tools/next_batch.py --tier HARD --limit 20       # 20 HARD functions
    python tools/next_batch.py --range 0x7100 --limit 50    # 50 in 0x7100 range
    python tools/next_batch.py --tier EASY                  # Remaining EASY
"""

import csv
import os
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
TRIAGE_CSV = PROJECT_ROOT / "data" / "fun_triage.csv"
BUILD_DIR = PROJECT_ROOT / "build"


def get_compiled_suffixes():
    """Get address suffixes of all compiled functions from .o files."""
    suffixes = set()
    for fn in os.listdir(BUILD_DIR):
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
                    if sec_name.startswith('.text.'):
                        suffixes.add(sec_name[6:])
        except (OSError, struct.error):
            pass
    return suffixes


def main():
    tier = 'MEDIUM'
    limit = 30
    addr_range = None

    for i, arg in enumerate(sys.argv):
        if arg == '--tier' and i + 1 < len(sys.argv):
            tier = sys.argv[i + 1]
        if arg == '--limit' and i + 1 < len(sys.argv):
            limit = int(sys.argv[i + 1])
        if arg == '--range' and i + 1 < len(sys.argv):
            addr_range = sys.argv[i + 1]
        if arg == '--help':
            print(__doc__)
            return

    compiled = get_compiled_suffixes()
    targets = []

    with open(TRIAGE_CSV) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row.get('Tier') != tier:
                continue
            addr_str = row['Address'].strip()
            addr = int(addr_str, 16)
            if addr_range and not ("0x%x" % addr).startswith(addr_range):
                continue
            addr_suffix = '%x' % (addr & 0xFFFFFFFF)
            if any(addr_suffix in name for name in compiled):
                continue
            size = int(row['Size'])
            name = row.get('Name', 'FUN_%x' % addr)
            targets.append((addr_str, name, size))
            if len(targets) >= limit:
                break

    print("Uncompiled %s targets (showing %d):" % (tier, len(targets)))
    print()
    for addr_str, name, size in targets:
        print("  %s  %s  %d bytes" % (addr_str, name, size))

    if not targets:
        print("  (none found)")


if __name__ == '__main__':
    main()
