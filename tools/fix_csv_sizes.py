#!/usr/bin/env python3
"""
Fix function sizes in functions.csv using control flow analysis.

Ghidra's auto-analysis overestimates function sizes for ~38% of entries by
including alignment padding (0x00000000) and adjacent function code. This
script walks the original binary's control flow from each function's entry
point to find the last reachable instruction, then updates the CSV.

Algorithm:
  1. For each function, read bytes from the original ELF
  2. Walk control flow from instruction 0 (BFS over basic blocks)
  3. Follow: fall-through, b, b.cond, cbz/cbnz, tbz/tbnz, bl (call + return)
  4. Stop at: ret, br Xn (indirect), udf (0x00000000)
  5. New size = (max reachable instruction index + 1) * 4
  6. Update CSV if new_size < original size

Usage:
    python tools/fix_csv_sizes.py [--dry-run] [--verbose]
"""
import csv
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000

dry_run = "--dry-run" in sys.argv
verbose = "--verbose" in sys.argv


def load_elf_segments(path):
    segs = []
    with open(path, 'rb') as f:
        f.seek(0x20)
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)
        phes = struct.unpack('<H', f.read(2))[0]
        phn = struct.unpack('<H', f.read(2))[0]
        for i in range(phn):
            f.seek(phoff + i * phes)
            pt = struct.unpack('<I', f.read(4))[0]
            f.read(4)
            po = struct.unpack('<Q', f.read(8))[0]
            pv = struct.unpack('<Q', f.read(8))[0]
            f.read(8)
            pf = struct.unpack('<Q', f.read(8))[0]
            if pt == 1:
                segs.append((pv, po, pf))
    return segs


def read_bytes(f, segs, va, sz):
    for sv, so, sf in segs:
        if sv <= va < sv + sf:
            f.seek(so + (va - sv))
            return f.read(sz)
    return None


def find_reachable_end(data, max_insns):
    """Walk control flow from instruction 0 and return (byte_size, has_br).

    byte_size: the byte size of the reachable portion of the function.
    has_br: True if the reachable code contains a br Xn instruction
            (potential switch table — unsafe to shrink).
    """
    if max_insns == 0:
        return 0, False

    reachable = set()
    worklist = [0]
    has_br = False

    while worklist:
        idx = worklist.pop()
        if idx < 0 or idx >= max_insns or idx in reachable:
            continue
        reachable.add(idx)

        w = struct.unpack_from('<I', data, idx * 4)[0]

        # ret — function returns, no fallthrough
        if w == 0xd65f03c0:
            continue

        # udf / alignment padding — dead code
        if w == 0x00000000:
            continue

        # br Xn — indirect branch (vtable dispatch or switch table), no fallthrough
        # Encoding: 1101011_0000_11111_000000_Rn_00000
        if (w & 0xFFFFFC1F) == 0xD61F0000:
            has_br = True
            continue

        # blr Xn — indirect call, fallthrough continues
        if (w & 0xFFFFFC1F) == 0xD63F0000:
            worklist.append(idx + 1)
            continue

        # b imm26 — unconditional branch, no fallthrough
        if (w >> 26) == 0x05:
            imm = w & 0x3FFFFFF
            if imm & 0x2000000:
                imm -= 0x4000000
            target = idx + imm
            worklist.append(target)
            continue

        # bl imm26 — call with return, fallthrough continues
        if (w >> 26) == 0x25:
            worklist.append(idx + 1)
            continue

        # b.cond imm19
        if (w & 0xFF000010) == 0x54000000:
            imm = (w >> 5) & 0x7FFFF
            if imm & 0x40000:
                imm -= 0x80000
            worklist.append(idx + imm)
            worklist.append(idx + 1)
            continue

        # cbz/cbnz imm19
        if (w & 0x7E000000) == 0x34000000:
            imm = (w >> 5) & 0x7FFFF
            if imm & 0x40000:
                imm -= 0x80000
            worklist.append(idx + imm)
            worklist.append(idx + 1)
            continue

        # tbz/tbnz imm14
        if (w & 0x7E000000) == 0x36000000:
            imm = (w >> 5) & 0x3FFF
            if imm & 0x2000:
                imm -= 0x4000
            worklist.append(idx + imm)
            worklist.append(idx + 1)
            continue

        # Default: fallthrough
        worklist.append(idx + 1)

    if not reachable:
        return 4, False
    return (max(reachable) + 1) * 4, has_br


def main():
    segments = load_elf_segments(ORIGINAL_ELF)

    rows = []
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        header = next(reader)
        for row in reader:
            rows.append(row)

    fixed = 0
    total_trimmed = 0
    skipped_br = 0

    with open(ORIGINAL_ELF, 'rb') as ef:
        for row in rows:
            addr = int(row[0], 16)
            size = int(row[2])
            if size < 8:
                continue
            if size % 4 != 0:
                continue

            va = addr - ELF_BASE if addr >= ELF_BASE else addr
            data = read_bytes(ef, segments, va, size)
            if data is None:
                continue

            max_insns = size // 4
            new_size, has_br = find_reachable_end(data, max_insns)

            if new_size >= size:
                continue  # no change
            if new_size == 0:
                continue  # skip empty

            # Skip functions with br Xn — could be switch tables where
            # case handlers are unreachable from our simple CFG analysis
            if has_br:
                skipped_br += 1
                continue

            trimmed = size - new_size
            total_trimmed += trimmed
            fixed += 1

            if verbose:
                print("  %s: %d -> %d (-%d)" % (row[3], size, new_size, trimmed))

            if not dry_run:
                row[2] = "%06d" % new_size

    print("Functions with oversized entries: %d" % fixed)
    print("Skipped (br Xn / switch table risk): %d" % skipped_br)
    print("Total bytes trimmed: %s" % "{:,}".format(total_trimmed))

    if not dry_run and fixed > 0:
        out_path = FUNCTIONS_CSV
        with open(out_path, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(header)
            writer.writerows(rows)
        print("Updated %s" % out_path)
    elif dry_run:
        print("(dry run, no changes written)")


if __name__ == '__main__':
    main()
