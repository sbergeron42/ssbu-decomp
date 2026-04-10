#!/usr/bin/env python3
"""
Compiler regression testing for LLVM NX patches.

Compares match results between stock and patched LLVM builds to detect
regressions (previously-matching functions that stop matching) and gains
(previously non-matching functions that now match).

Usage:
    python tools/compiler_regression.py --stock C:\\llvm-8.0.0 --patched C:\\llvm-8.0.0-custom
    python tools/compiler_regression.py --patched C:\\llvm-8.0.0-custom   # stock defaults to C:\\llvm-8.0.0

The script:
  1. Builds all source with stock compiler + full post-processing
  2. Runs verify_all.py, captures per-function match results
  3. Builds all source with patched compiler + NX flags + post-processing
  4. Runs verify_all.py, captures per-function match results
  5. Reports gained/lost/stable functions
"""

import argparse
import csv
import glob
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
SRC_DIR = PROJECT_ROOT / "src"
BUILD_DIR = PROJECT_ROOT / "build"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"

CFLAGS_BASE = (
    "-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 "
    "-fno-exceptions -fno-rtti -ffunction-sections -fdata-sections "
    "-fno-common -fno-short-enums -fPIC -mno-implicit-float "
    "-fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG "
    "-Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs"
)

NX_FLAGS = (
    "-mllvm -aarch64-nx-prologue "
    "-mllvm -aarch64-nx-movz "
    "-mllvm -aarch64-nx-return-width "
    "-mllvm -aarch64-nx-epilogue"
)

POST_PROCESS_SCRIPTS = [
    "fix_plt_stubs.py",
    "fix_movz_to_orr.py",
    "fix_prologue_sched.py",
    "fix_return_width.py",
    "fix_x8_regalloc.py",
    "fix_insn_reorder.py",
]


def compile_all(clang_path, extra_flags=""):
    """Compile all .cpp files."""
    clang = str(Path(clang_path) / "bin" / "clang++.exe")
    cflags = CFLAGS_BASE
    if extra_flags:
        cflags += " " + extra_flags

    cpp_files = list(SRC_DIR.rglob("*.cpp"))
    errors = 0
    for cpp in cpp_files:
        o_path = BUILD_DIR / (cpp.stem + ".o")
        cmd = '%s %s -c "%s" -o "%s"' % (clang, cflags, cpp, o_path)
        r = subprocess.run(cmd, shell=True, capture_output=True, text=True,
                          cwd=str(PROJECT_ROOT))
        if r.returncode != 0:
            errors += 1
    return errors


def run_postprocess():
    """Run all post-processing scripts."""
    for script in POST_PROCESS_SCRIPTS:
        tool_path = PROJECT_ROOT / "tools" / script
        if not tool_path.exists():
            continue
        matching = glob.glob("build/*.o", root_dir=str(PROJECT_ROOT))
        if not matching:
            continue
        subprocess.run(
            ['python', str(tool_path)] + matching,
            cwd=str(PROJECT_ROOT),
            capture_output=True
        )
    # Epilogue has special handling
    gen_path = PROJECT_ROOT / "tools" / "gen_epilogue_list.py"
    if gen_path.exists():
        subprocess.run(['python', str(gen_path)],
                      cwd=str(PROJECT_ROOT), capture_output=True)
    fix_epi = PROJECT_ROOT / "tools" / "fix_epilogue.py"
    if fix_epi.exists():
        for pattern in ["build/fun_batch_c_*.o", "build/fun_batch_d_*.o",
                       "build/fun_batch_e2_*.o"]:
            matching = glob.glob(pattern, root_dir=str(PROJECT_ROOT))
            if matching:
                subprocess.run(
                    ['python', str(fix_epi)] + matching,
                    cwd=str(PROJECT_ROOT), capture_output=True
                )


def run_verify():
    """Run verify_all.py and capture stdout. Returns (verified_count, output_text)."""
    r = subprocess.run(
        ['python', str(PROJECT_ROOT / "tools" / "verify_all.py"), "--summary"],
        capture_output=True, text=True, cwd=str(PROJECT_ROOT)
    )
    return r.stdout


def parse_verify_output(output):
    """Extract verified and non-matching counts from verify_all.py output."""
    verified = 0
    mismatch = 0
    m = re.search(r'VERIFIED:\s+(\d+)', output)
    if m:
        verified = int(m.group(1))
    m = re.search(r'Non-matching:\s+(\d+)', output)
    if m:
        mismatch = int(m.group(1))
    return verified, mismatch


def collect_match_set():
    """
    After building + verifying, read functions.csv to get the set of
    matched addresses. Returns set of hex address strings that are 'M'.
    """
    matches = set()
    with open(FUNCTIONS_CSV) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row.get('Quality') == 'M':
                matches.add(row['Address'])
    return matches


def main():
    parser = argparse.ArgumentParser(description='Compiler regression test')
    parser.add_argument('--stock', default=r'C:\llvm-8.0.0',
                       help='Path to stock LLVM 8.0.0 install')
    parser.add_argument('--patched', required=True,
                       help='Path to patched LLVM install')
    parser.add_argument('--nx-flags', default=NX_FLAGS,
                       help='NX compat flags for patched compiler')
    parser.add_argument('--report', default=None,
                       help='Write report to file')
    parser.add_argument('--skip-stock', action='store_true',
                       help='Skip stock build (use current CSV as baseline)')
    args = parser.parse_args()

    BUILD_DIR.mkdir(exist_ok=True)
    lines = []

    def log(msg):
        print(msg)
        lines.append(msg)

    log("=== Compiler Regression Report ===")
    log("Stock:   %s" % args.stock)
    log("Patched: %s" % args.patched)
    log("")

    # Step 1: Stock build
    if not args.skip_stock:
        log("--- Building with STOCK compiler ---")
        errors = compile_all(args.stock)
        log("  Compile errors: %d" % errors)
        log("  Running post-processing...")
        run_postprocess()
        log("  Running verification...")
        output = run_verify()
        stock_v, stock_m = parse_verify_output(output)
        log("  Stock: %d verified, %d non-matching" % (stock_v, stock_m))
        stock_matches = collect_match_set()
    else:
        log("--- Skipping stock build, using current CSV as baseline ---")
        stock_matches = collect_match_set()
        stock_v = len(stock_matches)
        stock_m = 0
        log("  Baseline: %d matched addresses in CSV" % stock_v)

    log("")

    # Step 2: Patched build
    log("--- Building with PATCHED compiler ---")
    errors = compile_all(args.patched, extra_flags=args.nx_flags)
    log("  Compile errors: %d" % errors)
    log("  Running post-processing...")
    run_postprocess()
    log("  Running verification...")
    output = run_verify()
    patched_v, patched_m = parse_verify_output(output)
    log("  Patched: %d verified, %d non-matching" % (patched_v, patched_m))
    patched_matches = collect_match_set()

    log("")

    # Step 3: Delta
    gained = patched_matches - stock_matches
    lost = stock_matches - patched_matches
    stable = stock_matches & patched_matches

    log("--- RESULTS ---")
    log("Baseline matches:  %d" % len(stock_matches))
    log("Patched matches:   %d" % len(patched_matches))
    log("")
    log("GAINED (+%d):" % len(gained))
    if gained:
        # Load CSV to get names for gained addresses
        addr_to_name = {}
        with open(FUNCTIONS_CSV) as f:
            for row in csv.DictReader(f):
                addr_to_name[row['Address']] = row.get('Name', '???')
        for addr in sorted(gained):
            log("  %s  %s" % (addr, addr_to_name.get(addr, '???')))
    else:
        log("  (none)")

    log("")
    log("LOST (-%d):" % len(lost))
    if lost:
        addr_to_name = {}
        with open(FUNCTIONS_CSV) as f:
            for row in csv.DictReader(f):
                addr_to_name[row['Address']] = row.get('Name', '???')
        for addr in sorted(lost):
            log("  %s  %s" % (addr, addr_to_name.get(addr, '???')))
    else:
        log("  (none)")

    log("")
    log("Net delta: %+d functions" % (len(gained) - len(lost)))

    if lost:
        log("")
        log("WARNING: %d REGRESSIONS DETECTED" % len(lost))
    else:
        log("")
        log("OK: No regressions.")

    if args.report:
        with open(args.report, 'w') as f:
            f.write('\n'.join(lines) + '\n')
        print("\nReport written to %s" % args.report)

    return 1 if lost else 0


if __name__ == '__main__':
    sys.exit(main())
