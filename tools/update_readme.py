#!/usr/bin/env python3
"""
Update README.md progress section with current verification numbers.
Reads from functions.csv and counts compiled symbols from the ELF.

Usage:
    python tools/update_readme.py              # Update README.md in place
    python tools/update_readme.py --check      # Just print numbers, don't update
"""

import csv
import os
import subprocess
import sys
import re
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
README = PROJECT_ROOT / "README.md"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
BUILD_DIR = PROJECT_ROOT / "build"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
TOTAL_FUNCTIONS = 39635


def get_compiled_count():
    """Count unique function symbols across all .o files in build/."""
    seen = set()
    for obj_name in os.listdir(BUILD_DIR):
        if not obj_name.endswith('.o'):
            continue
        result = subprocess.run([OBJDUMP, "-t", str(BUILD_DIR / obj_name)],
                              capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'F .text' in line:
                name = line.split()[-1]
                seen.add(name)
    return len(seen)


def get_verify_stats():
    """Run verify_all.py --summary and parse the output."""
    result = subprocess.run(['python', str(PROJECT_ROOT / 'tools' / 'verify_all.py'), '--summary'],
                          capture_output=True, text=True, timeout=300)
    verified = 0
    non_matching = 0
    for line in result.stdout.split('\n'):
        if 'BYTE-IDENTICAL' in line:
            verified = int(line.split(':')[1].split('(')[0].strip())
        if 'Non-matching' in line and ':' in line:
            try:
                non_matching = int(line.split(':')[1].split('(')[0].strip())
            except ValueError:
                pass
    return verified, non_matching


def main():
    check_only = '--check' in sys.argv

    compiled = get_compiled_count()
    verified, non_matching = get_verify_stats()
    total_decomp = compiled
    match_rate = verified * 100 / (verified + non_matching) if (verified + non_matching) > 0 else 0

    print("Compiled: %d (%.2f%%)" % (compiled, compiled * 100 / TOTAL_FUNCTIONS))
    print("Verified: %d (%.2f%%)" % (verified, verified * 100 / TOTAL_FUNCTIONS))
    print("Non-matching: %d" % non_matching)
    print("Match rate: %.1f%%" % match_rate)

    if check_only:
        return

    # Update README
    content = README.read_text()

    # Build new progress section
    undecomp_count = TOTAL_FUNCTIONS - total_decomp
    verified_pct = verified * 100 / TOTAL_FUNCTIONS
    compiled_pct = total_decomp * 100 / TOTAL_FUNCTIONS
    non_match_count = total_decomp - verified

    bar_w = 40
    v_bar = '#' * int(verified_pct / 100 * bar_w)
    c_bar = '#' * int(compiled_pct / 100 * bar_w)

    new_table = """| **Total functions** | 39,635 | |
| Verified byte-identical | {:,} | {:.2f}% |
| Compiled (non-matching) | {:,} | {:.2f}% |
| **Total decompiled** | **{:,}** | **{:.2f}%** |
| Undecompiled | {:,} | {:.2f}% |""".format(
        verified, verified_pct,
        non_match_count, non_match_count * 100 / TOTAL_FUNCTIONS,
        total_decomp, compiled_pct,
        undecomp_count, undecomp_count * 100 / TOTAL_FUNCTIONS)

    new_bars = """```
Verified  [{:<40s}]  {:,} / 39,635  ({:.2f}%)
Compiled  [{:<40s}]  {:,} / 39,635  ({:.2f}%)
```""".format(v_bar, verified, verified_pct, c_bar, total_decomp, compiled_pct)

    new_quote = """> **{:,} functions verified byte-identical** against the real 13.0.4 binary.
> {:.1f}% match rate on verified functions. Autonomous multi-agent orchestrator operational.""".format(
        verified, match_rate)

    # Replace sections using regex
    content = re.sub(
        r'\| \*\*Total functions\*\*.*?\| Undecompiled \|[^\n]*',
        new_table, content, flags=re.DOTALL)
    content = re.sub(
        r'```\nVerified.*?Compiled.*?```',
        new_bars, content, flags=re.DOTALL)
    content = re.sub(
        r'> \*\*[\d,]+ functions verified.*?operational\.',
        new_quote, content, flags=re.DOTALL)

    README.write_text(content)
    print("Updated README.md")


if __name__ == '__main__':
    main()
