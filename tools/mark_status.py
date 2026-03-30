#!/usr/bin/env python3
"""
Mark function status in the function database.

Usage:
    python tools/mark_status.py M FighterAreaModuleImpl__enable_fix_jostle_area_impl
    python tools/mark_status.py M --file data/matched.txt
    python tools/mark_status.py E FighterControlModuleImpl__get_param_attack_hi4_flick_y_impl

Status values: M (matching), E (equivalent), N (non-matching), U (undecompiled)
"""

import csv
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"


def update_status(names: list[str], status: str):
    """Update status for the given function names."""
    rows = []
    updated = 0
    with open(FUNCTIONS_CSV) as f:
        reader = csv.DictReader(f)
        fieldnames = reader.fieldnames
        for row in reader:
            # Match by substring — function names in the CSV may have namespace prefixes
            for name in names:
                if name in row["Name"]:
                    row["Status"] = status
                    updated += 1
                    break
            rows.append(row)

    with open(FUNCTIONS_CSV, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)

    print(f"Updated {updated} function(s) to status '{status}'")


def main():
    if len(sys.argv) < 3:
        print("Usage: python tools/mark_status.py <status> <name> [name2 ...]")
        print("       python tools/mark_status.py <status> --file <file>")
        sys.exit(1)

    status = sys.argv[1].upper()
    if status not in ("M", "E", "N", "U"):
        print(f"Invalid status '{status}'. Use M, E, N, or U.")
        sys.exit(1)

    if sys.argv[2] == "--file":
        filepath = sys.argv[3]
        with open(filepath) as f:
            names = [line.strip() for line in f if line.strip() and not line.startswith("#")]
    else:
        names = sys.argv[2:]

    update_status(names, status)


if __name__ == "__main__":
    main()
