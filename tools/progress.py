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
    python tools/progress.py --bar    # Show with progress bar
    python tools/progress.py --csv    # Output CSV for automated tracking
"""

import csv
import sys
from pathlib import Path
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"


def load_functions() -> list[dict]:
    """Load the function database."""
    functions = []
    with open(FUNCTIONS_CSV) as f:
        reader = csv.DictReader(f)
        for row in reader:
            functions.append(row)
    return functions


def print_bar(label: str, count: int, total: int, width: int = 40, color: str = "") -> str:
    """Generate a progress bar string."""
    pct = count / total * 100 if total > 0 else 0
    filled = int(width * count / total) if total > 0 else 0
    bar = "#" * filled + "-" * (width - filled)
    return f"  {label:<22} {bar} {count:>6} / {total:>6}  ({pct:>5.2f}%)"


def main():
    functions = load_functions()
    total = len(functions)

    if total == 0:
        print("No functions found in data/functions.csv")
        sys.exit(1)

    # Count by status
    status_counts = Counter(f["Status"] for f in functions)
    matching = status_counts.get("M", 0)
    equivalent = status_counts.get("E", 0)
    non_matching = status_counts.get("N", 0)
    undecompiled = status_counts.get("U", 0)
    decompiled = matching + equivalent + non_matching

    # Count named vs unnamed
    named = sum(1 for f in functions if not f["Name"].startswith("FUN_"))
    unnamed = total - named

    # Text size approximation (from .text section: ~60 MB)
    text_size = 0x39bfa8f  # .text end - .text start (from Ghidra)

    show_bar = "--bar" in sys.argv
    show_csv = "--csv" in sys.argv

    if show_csv:
        import datetime
        now = datetime.datetime.now().isoformat()
        print(f"{now},{total},{matching},{equivalent},{non_matching},{decompiled},{decompiled*100/total:.4f}")
        return

    print()
    print("=" * 72)
    print("  SSBU Decomp Progress -- Super Smash Bros. Ultimate v13.0.4")
    print("=" * 72)
    print()
    print(f"  Total functions:    {total:>6}")
    print(f"  Named (community): {named:>6}  ({named*100/total:.1f}%)")
    print(f"  Unnamed:            {unnamed:>6}  ({unnamed*100/total:.1f}%)")
    print()
    print("-" * 72)
    print()

    # Overall progress
    print(print_bar("Decompiled", decompiled, total))
    print()

    # Breakdown
    print(print_bar("Matching", matching, total))
    print(print_bar("Equivalent", equivalent, total))
    print(print_bar("Non-matching (WIP)", non_matching, total))
    print(print_bar("Undecompiled", undecompiled, total))

    print()
    print("-" * 72)

    # Code size estimate
    # Average ~15 instructions per function, 4 bytes each = ~60 bytes
    avg_func_size = text_size / total if total > 0 else 0
    decomp_bytes = decompiled * avg_func_size
    print()
    print(f"  Estimated code size:  {text_size / 1024 / 1024:.1f} MB")
    print(f"  Avg function size:    {avg_func_size:.0f} bytes")
    print(f"  Decompiled (est):     {decomp_bytes / 1024:.1f} KB / {text_size / 1024 / 1024:.1f} MB")
    print()


if __name__ == "__main__":
    main()
