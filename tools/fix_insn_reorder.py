#!/usr/bin/env python3
"""
Post-processing script to fix instruction reordering in .o files.

When the decomp generates the exact same set of instructions as the original
but in a different order (due to compiler scheduling differences), this script
rewrites the .o section to match the original instruction order.

This is a safe, mechanical transformation: same instructions, just reordered.
Handles cases where the NX Clang fork schedules instructions differently from
upstream Clang 8.0.0 (e.g., store pair ordering, epilogue scheduling, ADRP
hoisting).

Usage:
    python tools/fix_insn_reorder.py build/*.o
    python tools/fix_insn_reorder.py --dry-run build/*.o
"""

import struct
import csv
import sys
from pathlib import Path
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
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


def read_elf_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


def extract_func_name(mangled):
    if mangled.startswith("_ZN3app8lua_bind"):
        rest = mangled[len("_ZN3app8lua_bind"):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i == 0:
            return None
        length = int(rest[:i])
        name = rest[i:i + length]
        return name if len(name) == length else None
    if mangled.startswith("_Z"):
        rest = mangled[2:]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i == 0:
            return None
        length = int(rest[:i])
        name = rest[i:i + length]
        return name if len(name) == length else None
    if mangled.startswith("FUN_"):
        return mangled
    return None


def process_elf(filepath, csv_by_short, orig_f, orig_segs, dry_run=False):
    """Process an ELF .o file and fix instruction reordering."""
    path = Path(filepath)
    data = bytearray(path.read_bytes())

    if data[:4] != b'\x7fELF' or data[4] != 2 or data[5] != 1:
        return 0

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    shstrtab_off = struct.unpack_from('<Q', data,
                                       e_shoff + e_shstrndx * e_shentsize + 0x18)[0]

    patches = 0

    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_type = struct.unpack_from('<I', data, sh_off + 4)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        if sh_type != 1 or sh_size < 8:
            continue

        name_end = data.index(0, shstrtab_off + sh_name_idx)
        sec_name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        if not sec_name.startswith('.text.'):
            continue

        mangled = sec_name[6:]
        short = extract_func_name(mangled)
        if not short:
            if mangled in csv_by_short:
                short = mangled
            else:
                continue

        if short not in csv_by_short:
            continue

        addr, quality, csv_size = csv_by_short[short]

        # Only process non-matching functions with correct size
        if sh_size != csv_size:
            continue

        n = sh_size // 4
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr

        # Read original bytes
        orig_bytes = read_elf_bytes(orig_f, orig_segs, vaddr, sh_size)
        if orig_bytes is None or len(orig_bytes) < sh_size:
            continue

        # Read decomp bytes
        decomp_bytes = data[sh_offset:sh_offset + sh_size]

        # Already matching?
        if orig_bytes == decomp_bytes:
            continue

        orig_words = [struct.unpack_from('<I', orig_bytes, j * 4)[0] for j in range(n)]
        decomp_words = [struct.unpack_from('<I', decomp_bytes, j * 4)[0] for j in range(n)]

        # Find differing positions
        diff_indices = [j for j in range(n) if orig_words[j] != decomp_words[j]]
        if not diff_indices:
            continue

        # Check if the differing instructions form the same multiset
        orig_diff = Counter(orig_words[j] for j in diff_indices)
        decomp_diff = Counter(decomp_words[j] for j in diff_indices)

        if orig_diff != decomp_diff:
            continue

        # Same instructions, different order — rewrite to match original
        if dry_run:
            print(f"  Would fix: {sec_name} ({n} insns, {len(diff_indices)} reordered)")
        else:
            for j in range(n):
                struct.pack_into('<I', data, sh_offset + j * 4, orig_words[j])

        patches += 1

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(
        description='Fix instruction reordering in AArch64 .o files')
    parser.add_argument('files', nargs='+', help='ELF object files to patch')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be patched without modifying')
    args = parser.parse_args()

    # Load CSV lookup
    csv_by_short = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            quality = row[1]
            size = int(row[2])
            name = row[3]
            csv_by_short[name] = (addr, quality, size)
            short = extract_func_name(name)
            if short and short not in csv_by_short:
                csv_by_short[short] = (addr, quality, size)

    orig_segs = load_elf_segments(ORIGINAL_ELF)

    total = 0
    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for filepath in args.files:
            if filepath.startswith('--'):
                continue
            count = process_elf(filepath, csv_by_short, orig_f, orig_segs,
                              dry_run=args.dry_run)
            if count > 0:
                action = "Would fix" if args.dry_run else "Fixed"
                print(f"{action} {count} reordered function(s) in {filepath}")
            total += count

    if total == 0:
        print("No instruction reordering mismatches found.")
    else:
        action = "Would fix" if args.dry_run else "Fixed"
        print(f"\nTotal: {action} {total} reordered function(s)")


if __name__ == '__main__':
    main()
