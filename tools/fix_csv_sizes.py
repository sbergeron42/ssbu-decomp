#!/usr/bin/env python3
"""
Fix function sizes in functions.csv by stripping alignment padding.

The original binary pads functions with `udf #0` (0x00000000) for alignment.
Ghidra/analysis tools often include this padding in the function size, which
causes byte-matching functions to appear as SIZE_DIFF mismatches.

This script:
1. For each function in the CSV, reads the bytes at [addr, addr+size)
2. Trims trailing UDF (0x00000000) instructions from the size
3. Updates the CSV with the corrected size

Usage:
    python tools/fix_csv_sizes.py [--dry-run]
"""
import csv, struct, sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000
UDF_INSN = 0x00000000

dry_run = "--dry-run" in sys.argv

def load_elf_segments(path):
    segs = []
    with open(path, 'rb') as f:
        f.seek(0x20); phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36); phes = struct.unpack('<H', f.read(2))[0]
        phn = struct.unpack('<H', f.read(2))[0]
        for i in range(phn):
            f.seek(phoff + i * phes)
            pt = struct.unpack('<I', f.read(4))[0]; f.read(4)
            po = struct.unpack('<Q', f.read(8))[0]
            pv = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            pf = struct.unpack('<Q', f.read(8))[0]
            if pt == 1: segs.append((pv, po, pf))
    return segs

def read_bytes(f, segs, va, sz):
    for sv, so, sf in segs:
        if sv <= va < sv + sf:
            f.seek(so + (va - sv)); return f.read(sz)
    return None

segments = load_elf_segments(ORIGINAL_ELF)

# Read CSV
rows = []
with open(FUNCTIONS_CSV) as f:
    reader = csv.reader(f)
    header = next(reader)
    for row in reader:
        rows.append(row)

fixed = 0
total_bytes_trimmed = 0

with open(ORIGINAL_ELF, 'rb') as ef:
    for row in rows:
        addr = int(row[0], 16)
        size = int(row[2])
        if size < 8: continue  # too small to have padding
        if size % 4 != 0: continue  # not instruction-aligned

        va = addr - ELF_BASE if addr >= ELF_BASE else addr
        data = read_bytes(ef, segments, va, size)
        if data is None: continue

        # Trim trailing UDF instructions
        n = size // 4
        words = [struct.unpack('<I', data[i*4:(i+1)*4])[0] for i in range(n)]

        # Walk backwards, trimming UDF padding
        new_n = n
        while new_n > 0 and words[new_n - 1] == UDF_INSN:
            new_n -= 1

        if new_n == n: continue  # no padding found
        if new_n == 0: continue  # all UDF? skip

        new_size = new_n * 4
        trimmed = size - new_size
        total_bytes_trimmed += trimmed
        fixed += 1

        if not dry_run:
            row[2] = f"{new_size:06d}"

print(f"Functions with trailing UDF padding: {fixed}")
print(f"Total bytes trimmed: {total_bytes_trimmed}")

if not dry_run:
    out_path = FUNCTIONS_CSV
    with open(out_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(header)
        writer.writerows(rows)
    print(f"Updated {out_path}")
else:
    print("(dry run, no changes written)")
