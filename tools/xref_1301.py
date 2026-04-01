#!/usr/bin/env python3
"""
Cross-reference named functions from 13.0.1 Ghidra project against 13.0.4.

Uses the exported ghidra_1301_named.csv (15K+ named functions) and matches
them against our 13.0.4 functions.csv by checking which 13.0.4 FUN_* entries
share the same name patterns or can be mapped by address offset.

Between 13.0.1 and 13.0.4, most functions exist at shifted addresses.
We find the shift by matching known functions that exist in both CSVs.
"""

import csv
import sys
from pathlib import Path
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
NAMED_1301 = PROJECT_ROOT / "data" / "ghidra_1301_named.csv"
SSBU_CSV = PROJECT_ROOT / "data" / "functions.csv"


def main():
    dry_run = '--dry-run' in sys.argv

    # Load 13.0.1 named functions
    named_1301 = {}  # addr -> name
    with open(NAMED_1301) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            name = row[1]
            named_1301[addr] = name

    print("13.0.1 named functions: %d" % len(named_1301))

    # Load 13.0.4 functions
    funcs_1304 = {}  # addr -> (quality, size, name)
    with open(SSBU_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            funcs_1304[addr] = (row[1], row[2], row[3])

    print("13.0.4 functions: %d" % len(funcs_1304))

    # Step 1: Find address offset between versions
    # Match functions that have the same name in both
    offsets = Counter()
    for addr_1301, name_1301 in named_1301.items():
        for addr_1304, (q, s, name_1304) in funcs_1304.items():
            if name_1301 == name_1304 and not name_1301.startswith('FUN_'):
                offset = addr_1304 - addr_1301
                offsets[offset] += 1
                if offsets[offset] == 1 and len(offsets) < 5:
                    print("  Match: %s @ 1301:%x -> 1304:%x (offset %+x)" % (name_1301, addr_1301, addr_1304, offset))
                break

    if not offsets:
        print("ERROR: No matching functions found between versions")
        return

    # The most common offset is the global shift
    main_offset, match_count = offsets.most_common(1)[0]
    print()
    print("Primary address offset: %+x (%d matches)" % (main_offset, match_count))
    print("Other offsets: %s" % dict(offsets.most_common(5)))
    print()

    # Step 2: For each named 13.0.1 function, check if 13.0.4 has a FUN_* at the shifted address
    transferred = []
    already_named = 0
    no_match = 0

    for addr_1301, name_1301 in named_1301.items():
        if name_1301.startswith('FUN_'):
            continue

        # Try primary offset
        addr_1304 = addr_1301 + main_offset
        if addr_1304 in funcs_1304:
            q, s, name_1304 = funcs_1304[addr_1304]
            if name_1304.startswith('FUN_'):
                transferred.append((addr_1304, name_1301, name_1304))
            else:
                already_named += 1
        else:
            # Try nearby addresses (function might have shifted slightly)
            found = False
            for delta in range(-0x100, 0x100, 0x10):
                test_addr = addr_1304 + delta
                if test_addr in funcs_1304:
                    q, s, name_test = funcs_1304[test_addr]
                    if name_test.startswith('FUN_'):
                        transferred.append((test_addr, name_1301, name_test))
                        found = True
                        break
            if not found:
                no_match += 1

    print("Results:")
    print("  Transferable names (FUN_* -> named): %d" % len(transferred))
    print("  Already named in 13.0.4: %d" % already_named)
    print("  No match in 13.0.4: %d" % no_match)
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


if __name__ == '__main__':
    main()
