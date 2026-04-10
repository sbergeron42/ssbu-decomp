#!/usr/bin/env python3
"""
name_audit.py — Find the most-referenced unnamed FUN_ symbols across the codebase.

These are Ghidra default names that should be replaced with descriptive names
based on what the function does. Higher frequency = higher priority to name.

Usage:
    python tools/name_audit.py           # Top 30 unnamed functions
    python tools/name_audit.py --top 50  # Top 50
    python tools/name_audit.py --all     # All FUN_ references
"""

import argparse
import glob
import re
from collections import Counter

RE_FUN = re.compile(r'\bFUN_([0-9a-fA-F]{8,})\b')


def main():
    parser = argparse.ArgumentParser(description="Audit unnamed FUN_ references")
    parser.add_argument("--top", type=int, default=30, help="Show top N (default 30)")
    parser.add_argument("--all", action="store_true", help="Show all")
    args = parser.parse_args()

    # Count FUN_ references across all source files
    refs = Counter()       # FUN_addr → total reference count
    file_refs = {}         # FUN_addr → set of files that reference it

    for path in glob.glob("src/**/*.cpp", recursive=True):
        with open(path, encoding="utf-8", errors="replace") as f:
            content = f.read()
        for m in RE_FUN.finditer(content):
            name = f"FUN_{m.group(1).lower()}"
            refs[name] += 1
            if name not in file_refs:
                file_refs[name] = set()
            file_refs[name].add(path.replace("\\", "/"))

    if not refs:
        print("No FUN_ references found.")
        return

    # Sort by frequency
    ranked = refs.most_common(None if args.all else args.top)

    print(f"{'FUN_ name':30s} {'Refs':>5s} {'Files':>5s}  Sample files")
    print("-" * 90)
    for name, count in ranked:
        files = file_refs[name]
        samples = sorted(files)[:3]
        sample_str = ", ".join(s.replace("src/app/", "").replace("src/resource/", "res/") for s in samples)
        if len(files) > 3:
            sample_str += f" (+{len(files)-3} more)"
        print(f"{name:30s} {count:5d} {len(files):5d}  {sample_str}")

    total_refs = sum(refs.values())
    total_unique = len(refs)
    print(f"\nTotal: {total_refs} references to {total_unique} unique FUN_ names")
    print(f"Top 10 account for {sum(c for _, c in ranked[:10])} references "
          f"({sum(c for _, c in ranked[:10]) * 100 // total_refs}%)")


if __name__ == "__main__":
    main()
