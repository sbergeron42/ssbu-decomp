#!/usr/bin/env python3
"""
Post-processing script to fix return-register width divergence.

NX Clang sometimes uses `mov x0, xzr` (64-bit) where upstream Clang 8.0.0
emits `mov w0, wzr` (32-bit) for zeroing the return value, or vice versa.
Both are semantically equivalent for return values, but byte-differ.

This script compares each function's epilogue against the original binary
and patches the zero-return instruction to match.

Specifically patches:
  mov w0, wzr  (0x2A1F03E0) <-> mov x0, xzr (0xAA1F03E0)
  mov wN, wzr  (0x2A1F03E0|N) <-> mov xN, xzr (0xAA1F03E0|N)

Only patches when:
  - The function exists in the original binary (address known from CSV)
  - The ONLY difference at that instruction position is the width bit (bit 31)
  - The rest of the instruction is identical
"""

import struct
import csv
import sys
from pathlib import Path

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
    """Extract short function name from mangled C++ symbol."""
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


def is_mov_zero(insn):
    """Check if instruction is mov wN, wzr or mov xN, xzr.
    Returns (True, rd, is_64bit) or (False, -1, False)."""
    # mov wN, wzr = orr wN, wzr, wzr = 0x2A1F03E0 | Rd
    if (insn & 0xFFFFFFE0) == 0x2A1F03E0:
        return True, insn & 0x1F, False
    # mov xN, xzr = orr xN, xzr, xzr = 0xAA1F03E0 | Rd
    if (insn & 0xFFFFFFE0) == 0xAA1F03E0:
        return True, insn & 0x1F, True
    return False, -1, False


def process_elf(filepath, csv_by_short, orig_f, orig_segs, dry_run=False):
    """Process an ELF .o file and fix return-width mismatches."""
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

        if sh_type != 1 or sh_size < 4:
            continue

        name_end = data.index(0, shstrtab_off + sh_name_idx)
        sec_name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        if not sec_name.startswith('.text.'):
            continue

        mangled = sec_name[6:]
        short = extract_func_name(mangled)
        if not short:
            # Try full mangled name
            if mangled in csv_by_short:
                short = mangled
            else:
                continue

        if short not in csv_by_short:
            continue

        addr, quality, csv_size = csv_by_short[short]

        # Read original bytes
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
        orig_bytes = read_elf_bytes(orig_f, orig_segs, vaddr, sh_size)
        if orig_bytes is None or len(orig_bytes) < sh_size:
            continue

        # Scan for mov-zero instructions that differ only in width
        n = sh_size // 4
        for j in range(n):
            file_off = sh_offset + j * 4
            decomp_insn = struct.unpack_from('<I', data, file_off)[0]
            orig_insn = struct.unpack_from('<I', orig_bytes, j * 4)[0]

            if decomp_insn == orig_insn:
                continue

            # Check if both are mov-zero and differ only in width bit
            d_is_mov, d_rd, d_64 = is_mov_zero(decomp_insn)
            o_is_mov, o_rd, o_64 = is_mov_zero(orig_insn)

            if d_is_mov and o_is_mov and d_rd == o_rd and d_64 != o_64:
                if dry_run:
                    width_from = "x" if d_64 else "w"
                    width_to = "x" if o_64 else "w"
                    print(f"  Would fix: {sec_name}+{j*4:#x}: "
                          f"mov {width_from}{d_rd},{'xzr' if d_64 else 'wzr'} -> "
                          f"mov {width_to}{o_rd},{'xzr' if o_64 else 'wzr'}")
                    patches += 1
                else:
                    struct.pack_into('<I', data, file_off, orig_insn)
                    patches += 1

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(
        description='Fix return-register width (mov w0,wzr vs mov x0,xzr) in AArch64 .o files')
    parser.add_argument('files', nargs='+', help='ELF object files to patch')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be patched without modifying')
    args = parser.parse_args()

    # Load CSV lookup
    csv_by_short = {}
    csv_by_mangled = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            quality = row[1]
            size = int(row[2])
            name = row[3]
            csv_by_mangled[name] = (addr, quality, size)
            short = extract_func_name(name)
            if short and short not in csv_by_short:
                csv_by_short[short] = (addr, quality, size)

    # Merge: prefer short name lookup but also support full mangled
    merged = dict(csv_by_short)
    merged.update(csv_by_mangled)

    orig_segs = load_elf_segments(ORIGINAL_ELF)

    total = 0
    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for filepath in args.files:
            if filepath.startswith('--'):
                continue
            count = process_elf(filepath, merged, orig_f, orig_segs,
                              dry_run=args.dry_run)
            if count > 0:
                action = "Would fix" if args.dry_run else "Fixed"
                print(f"{action} {count} return-width mismatch(es) in {filepath}")
            total += count

    if total == 0:
        print("No return-width mismatches found.")
    else:
        action = "Would fix" if args.dry_run else "Fixed"
        print(f"\nTotal: {action} {total} return-width mismatch(es)")


if __name__ == '__main__':
    main()
