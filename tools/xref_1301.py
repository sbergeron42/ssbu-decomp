#!/usr/bin/env python3
"""
Cross-reference named functions from 13.0.1 Ghidra project against 13.0.4.

Uses ghidra_1301_named.csv and matches against functions.csv by:
  1. Building address offset map using 5,838 anchor functions (same name in both)
  2. Grouping offsets by address region (different .text regions may shift differently)
  3. Transferring names from 13.0.1 to FUN_* entries in 13.0.4

Usage:
    python tools/xref_1301.py --dry-run    # Preview transfers
    python tools/xref_1301.py              # Apply transfers to functions.csv
"""

import csv
import sys
from pathlib import Path
from collections import Counter, defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
NAMED_1301 = PROJECT_ROOT / "data" / "ghidra_1301_named.csv"
SSBU_CSV = PROJECT_ROOT / "data" / "functions.csv"


def main():
    dry_run = '--dry-run' in sys.argv

    # Load 13.0.1 named functions: addr -> name
    named_1301 = {}
    with open(NAMED_1301) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            name = row[1]
            if not name.startswith('FUN_'):
                named_1301[addr] = name

    print("13.0.1 named functions: %d" % len(named_1301))

    # Load 13.0.4 functions: addr -> (quality, size, name)
    funcs_1304 = {}
    names_1304 = {}  # name -> addr (for anchor matching)
    with open(SSBU_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            funcs_1304[addr] = (row[1], row[2], row[3])
            names_1304[row[3]] = addr

    print("13.0.4 functions: %d" % len(funcs_1304))

    # Also build set of 13.0.4 addresses for fast lookup
    addrs_1304 = set(funcs_1304.keys())

    # Step 1: Find address offsets using anchor functions (same name in both)
    # Use name-based lookup (O(n) instead of O(n*m))
    anchor_offsets = []  # (addr_1301, offset)
    for addr_1301, name_1301 in named_1301.items():
        if name_1301 in names_1304:
            addr_1304 = names_1304[name_1301]
            offset = addr_1304 - addr_1301
            anchor_offsets.append((addr_1301, offset))

    print("Anchor matches: %d" % len(anchor_offsets))

    if not anchor_offsets:
        print("ERROR: No anchor functions found")
        return

    # Step 2: Group offsets by address region
    # Sort anchors by 13.0.1 address and detect offset changes
    anchor_offsets.sort()
    offset_counts = Counter(off for _, off in anchor_offsets)

    # Show top offsets
    print()
    print("Offset distribution (top 10):")
    for off, count in offset_counts.most_common(10):
        print("  %+#x: %d anchors" % (off, count))

    # Build region-based offset map:
    # For each 13.0.1 address, find the nearest anchor's offset
    # This handles cases where different regions shift by different amounts
    anchor_by_addr = sorted(anchor_offsets)  # sorted by 1301 addr

    def get_best_offset(addr_1301):
        """Find the offset from the nearest anchor function."""
        # Binary search for nearest anchor
        lo, hi = 0, len(anchor_by_addr) - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if anchor_by_addr[mid][0] < addr_1301:
                lo = mid + 1
            else:
                hi = mid
        # Check neighbors
        best_off = None
        best_dist = float('inf')
        for idx in range(max(0, lo - 1), min(len(anchor_by_addr), lo + 2)):
            dist = abs(anchor_by_addr[idx][0] - addr_1301)
            if dist < best_dist:
                best_dist = dist
                best_off = anchor_by_addr[idx][1]
        return best_off

    # Step 3: Transfer names
    # Skip non-unique names (e.g. "pre_update" appears 186 times in 13.0.1)
    name_counts = Counter(named_1301.values())
    unique_names = {n for n, c in name_counts.items() if c == 1}
    print("Unique 13.0.1 names: %d / %d" % (len(unique_names), len(named_1301)))

    transferred = []
    already_named = 0
    no_match = 0
    skipped_dup = 0

    # Track which 13.0.4 addresses we've already assigned
    claimed_addrs = set()

    for addr_1301, name_1301 in sorted(named_1301.items()):
        if name_1301 not in unique_names:
            skipped_dup += 1
            continue
        # Skip if already in 13.0.4
        if name_1301 in names_1304:
            already_named += 1
            continue

        offset = get_best_offset(addr_1301)
        if offset is None:
            no_match += 1
            continue

        # Try exact shifted address first, then nearby
        addr_1304 = addr_1301 + offset
        candidates = [addr_1304] + [addr_1304 + d for d in
                      [0x10, -0x10, 0x20, -0x20, 0x30, -0x30, 0x40, -0x40,
                       0x50, -0x50, 0x60, -0x60, 0x80, -0x80,
                       0x100, -0x100, 0x200, -0x200, 0x400, -0x400]]

        found = False
        for test_addr in candidates:
            if test_addr not in addrs_1304 or test_addr in claimed_addrs:
                continue
            q, s, name_test = funcs_1304[test_addr]
            if name_test.startswith('FUN_'):
                transferred.append((test_addr, name_1301, name_test))
                claimed_addrs.add(test_addr)
                found = True
                break
            elif test_addr == addr_1304:
                # Exact match but already named
                already_named += 1
                found = True
                break
        if not found:
            no_match += 1

    print()
    print("Results:")
    print("  Transferable (FUN_* -> named): %d" % len(transferred))
    print("  Already named in 13.0.4: %d" % already_named)
    print("  Skipped (duplicate name): %d" % skipped_dup)
    print("  No match found: %d" % no_match)
    print()

    # Show samples
    print("Sample transfers:")
    for addr, new_name, old_name in transferred[:20]:
        print("  0x%x: %s -> %s" % (addr, old_name, new_name))

    if not dry_run and transferred:
        print()
        print("Updating functions.csv with %d new names..." % len(transferred))
        rows = []
        transfer_map = {addr: name for addr, name, _ in transferred}
        updated = 0
        with open(SSBU_CSV) as f:
            reader = csv.reader(f)
            header = next(reader)
            for row in reader:
                addr = int(row[0], 16)
                if addr in transfer_map:
                    row[3] = transfer_map[addr]
                    updated += 1
                rows.append(row)

        with open(SSBU_CSV, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(header)
            writer.writerows(rows)

        print("Updated %d function names" % updated)
    elif dry_run:
        print()
        print("(dry run — no changes written)")


if __name__ == '__main__':
    main()
