#!/usr/bin/env python3
"""
Byte-matching cross-reference between 13.0.1 and 13.0.4 ELFs.

For each named function in 13.0.1, extracts its bytes, masks relocations
(ADRP, B/BL, ADD immediate), and searches for a unique match in 13.0.4.
Transfers names to FUN_* entries in functions.csv.

This is much more accurate than offset-based matching (xref_1301.py)
because it validates that the actual code is identical.

Usage:
    python tools/xref_1301_bytes.py --dry-run    # Preview
    python tools/xref_1301_bytes.py              # Apply to functions.csv
"""

import csv
import struct
import sys
from pathlib import Path
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
ELF_1301 = PROJECT_ROOT / "data" / "main_1301.elf"
ELF_1304 = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
NAMED_1301 = PROJECT_ROOT / "data" / "ghidra_1301_named.csv"
ELF_BASE = 0x7100000000

MIN_SIZE = 8  # minimum function size in bytes (skip tiny stubs)


def load_elf_text(path):
    """Load .text segment from ELF. Returns (base_vaddr, bytes)."""
    with open(path, 'rb') as f:
        f.seek(0x20)
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)
        phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        # First LOAD segment with execute permission is .text
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]
            p_flags = struct.unpack('<I', f.read(4))[0]
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]
            f.read(8)  # p_paddr
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1 and (p_flags & 1):  # PT_LOAD + PF_X
                f.seek(p_offset)
                data = f.read(p_filesz)
                return (p_vaddr, data)
    return None


def mask_instructions(data):
    """Mask position-dependent instruction fields for fuzzy matching.
    Returns masked copy of the data."""
    result = bytearray(data)
    for i in range(0, len(result) - 3, 4):
        insn = struct.unpack_from('<I', result, i)[0]

        # ADRP: mask all except Rd (bits 4:0) and opcode id
        if (insn & 0x9F000000) == 0x90000000:
            masked = 0x90000000 | (insn & 0x1F)
            struct.pack_into('<I', result, i, masked)

        # B / BL: mask offset (bits 25:0)
        elif (insn & 0x7C000000) == 0x14000000:
            masked = insn & 0xFC000000
            struct.pack_into('<I', result, i, masked)

        # ADD immediate (often after ADRP): mask imm12 (bits 21:10)
        elif (insn & 0x7F800000) == 0x11000000:
            masked = insn & 0xFFC003FF
            struct.pack_into('<I', result, i, masked)

        # LDR/STR unsigned offset: mask imm12 (bits 21:10)
        elif (insn & 0x3B000000) == 0x39000000:
            masked = insn & 0xFFC003FF
            struct.pack_into('<I', result, i, masked)

    return bytes(result)


def build_1304_index(text_vaddr, text_data):
    """Build an index of masked 8-byte sequences -> list of offsets in 13.0.4 .text.
    Uses first 8 bytes (2 instructions) as the key for fast lookup."""
    index = {}
    masked = mask_instructions(text_data)
    for off in range(0, len(masked) - 7, 4):
        key = masked[off:off + 8]
        if key not in index:
            index[key] = []
        index[key].append(off)
    return index, masked


def main():
    dry_run = '--dry-run' in sys.argv

    print("Loading 13.0.1 ELF...")
    text_1301 = load_elf_text(ELF_1301)
    if not text_1301:
        print("ERROR: Could not load .text from 13.0.1 ELF")
        return
    vaddr_1301, data_1301 = text_1301

    print("Loading 13.0.4 ELF...")
    text_1304 = load_elf_text(ELF_1304)
    if not text_1304:
        print("ERROR: Could not load .text from 13.0.4 ELF")
        return
    vaddr_1304, data_1304 = text_1304

    print("  13.0.1 .text: %d bytes at 0x%x" % (len(data_1301), vaddr_1301))
    print("  13.0.4 .text: %d bytes at 0x%x" % (len(data_1304), vaddr_1304))

    # Load 13.0.1 named functions with sizes
    print("Loading 13.0.1 function names...")
    named_1301 = {}
    with open(NAMED_1301) as f:
        reader = csv.reader(f)
        next(reader)
        rows = list(reader)

    # Sort by address to compute sizes
    rows.sort(key=lambda r: int(r[0], 16))
    for i, row in enumerate(rows):
        addr = int(row[0], 16)
        name = row[1]
        if name.startswith('FUN_'):
            continue
        # Estimate size: distance to next function
        if i + 1 < len(rows):
            next_addr = int(rows[i + 1][0], 16)
            size = min(next_addr - addr, 0x10000)  # cap at 64KB
        else:
            size = 0x100
        if size >= MIN_SIZE:
            named_1301[addr] = (name, size)

    print("  Named functions with size >= %d: %d" % (MIN_SIZE, len(named_1301)))

    # Filter to unique names only
    name_counts = Counter(n for n, s in named_1301.values())
    unique_names = {n for n, c in name_counts.items() if c == 1}
    named_unique = {a: (n, s) for a, (n, s) in named_1301.items()
                    if n in unique_names}
    print("  With unique names: %d" % len(named_unique))

    # Load 13.0.4 functions.csv
    funcs_1304 = {}
    names_1304 = set()
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            funcs_1304[addr] = (row[1], int(row[2]), row[3])
            names_1304.add(row[3])

    # Build anchor offset map for disambiguation
    # (same name in both -> known offset at that address)
    anchor_offsets = []
    for addr_1301, (name, _) in sorted(named_1301.items()):
        if name in names_1304:
            # Find the 13.0.4 address for this name
            for a1304, (q, sz, n) in funcs_1304.items():
                if n == name:
                    anchor_offsets.append((addr_1301, a1304 - addr_1301))
                    break
    anchor_offsets.sort()

    def get_expected_addr(addr_1301):
        """Get expected 13.0.4 address based on nearest anchor offset."""
        lo, hi = 0, len(anchor_offsets) - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if anchor_offsets[mid][0] < addr_1301:
                lo = mid + 1
            else:
                hi = mid
        best_off = None
        best_dist = float('inf')
        for idx in range(max(0, lo - 1), min(len(anchor_offsets), lo + 2)):
            dist = abs(anchor_offsets[idx][0] - addr_1301)
            if dist < best_dist:
                best_dist = dist
                best_off = anchor_offsets[idx][1]
        return addr_1301 + best_off if best_off is not None else None

    print("  Anchor offsets for disambiguation: %d" % len(anchor_offsets))

    # Build search index for 13.0.4
    print("Building 13.0.4 search index...")
    index_1304, masked_1304 = build_1304_index(vaddr_1304, data_1304)

    # Search for each 13.0.1 function in 13.0.4
    print("Searching...")
    transferred = []
    already_named = 0
    no_match = 0
    multi_match = 0
    too_small = 0
    claimed = set()

    for addr_1301, (name, est_size) in sorted(named_unique.items()):
        # Skip if already in 13.0.4
        if name in names_1304:
            already_named += 1
            continue

        # Read function bytes from 13.0.1
        # Ghidra addresses include ELF_BASE, ELF vaddrs don't
        off_1301 = addr_1301 - vaddr_1301 - ELF_BASE
        if off_1301 < 0 or off_1301 + MIN_SIZE > len(data_1301):
            no_match += 1
            continue

        # Use first 8 bytes as index key
        func_bytes = data_1301[off_1301:off_1301 + est_size]
        masked_func = mask_instructions(func_bytes)
        key = masked_func[:8]

        if key not in index_1304:
            no_match += 1
            continue

        # Check candidates: compare full masked function bytes
        matches = []
        for cand_off in index_1304[key]:
            if cand_off + len(masked_func) > len(masked_1304):
                continue
            cand_masked = masked_1304[cand_off:cand_off + len(masked_func)]
            if cand_masked == masked_func:
                cand_addr = vaddr_1304 + cand_off + ELF_BASE  # convert to Ghidra addr
                matches.append(cand_addr)

        if len(matches) == 0:
            no_match += 1
            continue

        # Filter to FUN_* entries not yet claimed
        viable = [a for a in matches
                  if a in funcs_1304 and a not in claimed
                  and funcs_1304[a][2].startswith('FUN_')]

        if len(viable) == 0:
            # All matches are already named or claimed
            already_named += 1
            continue

        target = None
        if len(viable) == 1:
            target = viable[0]
        else:
            # Disambiguate: try CSV size match
            size_matches = [a for a in viable
                           if funcs_1304[a][1] == est_size]
            if len(size_matches) == 1:
                target = size_matches[0]
            else:
                # Disambiguate: pick candidate closest to expected offset
                expected = get_expected_addr(addr_1301)
                if expected is not None:
                    viable_sorted = sorted(viable,
                                          key=lambda a: abs(a - expected))
                    best = viable_sorted[0]
                    # Only accept if within 0x1000 of expected
                    if abs(best - expected) <= 0x1000:
                        target = best

        if target is not None:
            transferred.append((target, name, funcs_1304[target][2]))
            claimed.add(target)
        else:
            multi_match += 1

    print()
    print("Results:")
    print("  Byte-matched transfers: %d" % len(transferred))
    print("  Already named: %d" % already_named)
    print("  Multiple matches (skipped): %d" % multi_match)
    print("  No match: %d" % no_match)
    print()

    print("Sample transfers:")
    for addr, new_name, old_name in transferred[:20]:
        print("  0x%x: %s -> %s" % (addr, old_name, new_name))

    if not dry_run and transferred:
        print()
        print("Updating functions.csv with %d new names..." % len(transferred))
        rows = []
        transfer_map = {addr: name for addr, name, _ in transferred}
        updated = 0
        with open(FUNCTIONS_CSV) as f:
            reader = csv.reader(f)
            header = next(reader)
            for row in reader:
                addr = int(row[0], 16)
                if addr in transfer_map:
                    row[3] = transfer_map[addr]
                    updated += 1
                rows.append(row)

        with open(FUNCTIONS_CSV, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(header)
            writer.writerows(rows)

        print("Updated %d function names" % updated)
    elif dry_run:
        print("(dry run)")


if __name__ == '__main__':
    main()
