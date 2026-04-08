#!/usr/bin/env python3
"""
SSBU Decomp progress tracker.

Reads data/functions.csv and reports decompilation status.
Status values:
  U  = Undecompiled
  M  = Matching (byte-identical after post-processing)
  E  = Equivalent (correct logic, minor scheduling/encoding diffs)
  N  = Non-matching (work in progress)

Usage:
    python tools/progress.py          # Show progress summary
    python tools/progress.py --csv    # Output CSV for automated tracking
"""

import csv
import os
import re
import sys
from pathlib import Path
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
SRC_DIR = PROJECT_ROOT / "src"


def load_functions():
    """Load the function database."""
    functions = []
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)  # skip header
        for row in reader:
            functions.append({
                "Address": row[0],
                "Quality": row[1],
                "Size": int(row[2]),
                "Name": row[3],
            })
    return functions


def count_naked_asm():
    """Count functions using __attribute__((naked)) in source files."""
    naked_re = re.compile(r'__attribute__\s*\(\s*\(\s*naked\s*\)\s*\)')
    count = 0
    for root, dirs, files in os.walk(SRC_DIR):
        for fn in files:
            if not fn.endswith('.cpp'):
                continue
            path = os.path.join(root, fn)
            with open(path, encoding='utf-8', errors='replace') as f:
                for line in f:
                    if naked_re.search(line):
                        count += 1
    return count


def print_bar(label, count, total, width=40):
    """Generate a progress bar string."""
    pct = count / total * 100 if total > 0 else 0
    filled = int(width * count / total) if total > 0 else 0
    bar = "#" * filled + "-" * (width - filled)
    return "  %-22s %s %6d / %6d  (%5.2f%%)" % (label, bar, count, total, pct)


def main():
    functions = load_functions()
    total = len(functions)

    if total == 0:
        print("No functions found in data/functions.csv")
        sys.exit(1)

    # Count by status
    status_counts = Counter(f["Quality"] for f in functions)
    matching = status_counts.get("M", 0)
    equivalent = status_counts.get("E", 0)
    non_matching = status_counts.get("N", 0)
    undecompiled = status_counts.get("U", 0)
    decompiled = matching + equivalent + non_matching

    # Byte-weighted totals
    bytes_by_quality = {"M": 0, "N": 0, "U": 0, "E": 0}
    for f in functions:
        q = f["Quality"]
        bytes_by_quality[q] = bytes_by_quality.get(q, 0) + f["Size"]

    total_bytes = sum(bytes_by_quality.values())
    compiled_bytes = bytes_by_quality["M"] + bytes_by_quality["N"] + bytes_by_quality.get("E", 0)
    matched_bytes = bytes_by_quality["M"]

    # Average sizes per quality
    avg_m = bytes_by_quality["M"] / matching if matching else 0
    avg_n = bytes_by_quality["N"] / non_matching if non_matching else 0
    avg_u = bytes_by_quality["U"] / undecompiled if undecompiled else 0

    # Count named vs unnamed
    named = sum(1 for f in functions if not f["Name"].startswith("FUN_"))
    unnamed = total - named

    # Count naked asm (tracked separately from real C++ decomp)
    naked_count = count_naked_asm()

    show_csv = "--csv" in sys.argv

    if show_csv:
        import datetime
        now = datetime.datetime.now().isoformat()
        print("%s,%d,%d,%d,%d,%d,%.4f,%.4f" % (
            now, total, matching, equivalent, non_matching, decompiled,
            decompiled * 100 / total, matched_bytes * 100 / total_bytes))
        return

    print()
    print("=" * 72)
    print("  SSBU Decomp Progress -- Super Smash Bros. Ultimate v13.0.4")
    print("=" * 72)
    print()
    print("  Total functions:    %6d" % total)
    print("  Named (community): %6d  (%.1f%%)" % (named, named * 100 / total))
    print("  Unnamed:            %6d  (%.1f%%)" % (unnamed, unnamed * 100 / total))
    print()
    print("-" * 72)
    print()

    # === By function count ===
    print("  BY FUNCTION COUNT")
    print()
    print(print_bar("Decompiled", decompiled, total))
    print()
    print(print_bar("Matching", matching, total))
    print(print_bar("Equivalent", equivalent, total))
    print(print_bar("Non-matching (WIP)", non_matching, total))
    print(print_bar("Undecompiled", undecompiled, total))

    print()
    print("-" * 72)
    print()

    # === By bytes ===
    print("  BY BYTES (.text = %.1f MB)" % (total_bytes / 1024 / 1024))
    print()
    print("  Compiled:  %.2f MB / %.1f MB  (%.2f%%)" % (
        compiled_bytes / 1e6, total_bytes / 1e6, compiled_bytes * 100 / total_bytes))
    print("  Matched:   %.2f MB / %.1f MB  (%.2f%%)" % (
        matched_bytes / 1e6, total_bytes / 1e6, matched_bytes * 100 / total_bytes))

    print()
    print("  Avg function size by quality:")
    print("    Matched (M):      %4d bytes" % avg_m)
    print("    Non-matching (N): %4d bytes" % avg_n)
    print("    Undecompiled (U): %4d bytes" % avg_u)
    print()
    print("  Note: Progress skews toward small functions (avg matched: %d bytes" % avg_m)
    print("  vs avg undecompiled: %d bytes). Byte-weighted progress is the" % avg_u)
    print("  more accurate measure of source recovery.")

    print()
    print("-" * 72)
    print()

    # === Naked asm separation ===
    real_cpp = matching - naked_count
    if real_cpp < 0:
        real_cpp = 0  # safety
    print("  DECOMP QUALITY BREAKDOWN")
    print()
    print("  Verified (real C++):    %6d" % real_cpp)
    print("  Verified (naked asm):   %6d  (binary-identical, not source recovery)" % naked_count)
    print("  Non-matching (WIP):     %6d" % non_matching)
    print()


if __name__ == "__main__":
    main()
