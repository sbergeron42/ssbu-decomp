#!/usr/bin/env python3
"""
LLVM flag fuzzer for NX Clang compatibility.

Systematically tests -mllvm flags against non-matching functions to find
heuristic differences between NX Clang and upstream Clang 8.0.0.

Phase 1: Single-flag sweep — test each flag individually, measure delta.
Phase 2: Combine top winners, hill-climb to optimal flag set.

Usage:
    python tools/fuzz_flags.py                          # Full sweep
    python tools/fuzz_flags.py --phase2                 # Combine winners
    python tools/fuzz_flags.py --test-flag "flag=value" # Test one flag
    python tools/fuzz_flags.py --src src/app/FighterManager.cpp  # Single file
"""

import argparse
import csv
import glob
import os
import struct
import subprocess
import sys
import time
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000

CLANG = os.environ.get("DECOMP_CLANG",
                       r"C:\llvm-8.0.0-custom\bin\clang++.exe")
CFLAGS_BASE = (
    "-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 "
    "-fno-exceptions -fno-rtti -ffunction-sections -fdata-sections "
    "-fno-common -fno-short-enums -fPIC -mno-implicit-float "
    "-fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG "
    "-Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs "
    "-mllvm -aarch64-nx-prologue"
)

# ─── Flags to test ────────────────────────────────────────────────────

# Boolean flags: test toggling from default
BOOL_FLAGS = [
    # Scheduling
    ("-misched-topdown", [True, False]),
    ("-misched-bottomup", [True, False]),
    ("-misched-regpressure", [False]),  # default true
    ("-misched-cyclicpath", [False]),   # default true
    ("-misched-cluster", [False]),      # default true
    ("-misched-fusion", [False]),       # default true
    ("-enable-post-misched", [True, False]),
    ("-disable-sched-hazard", [True]),
    ("-disable-sched-critical-path", [True]),
    ("-disable-sched-height", [True]),
    ("-disable-sched-reg-pressure", [True]),
    ("-disable-sched-stalls", [False]),  # default true
    ("-disable-sched-live-uses", [False]),  # default true
    ("-disable-sched-vrcycle", [True]),
    ("-disable-sched-physreg-join", [True]),

    # Register allocation
    ("-enable-local-reassign", [True]),
    ("-enable-deferred-spilling", [True]),
    ("-exhaustive-register-search", [True]),
    ("-terminal-rule", [True]),
    ("-join-liveintervals", [False]),   # default true
    ("-enable-shrink-wrap", [True, False]),

    # AArch64-specific
    ("-aarch64-enable-ccmp", [False]),
    ("-aarch64-enable-early-ifcvt", [False]),
    ("-aarch64-enable-condopt", [False]),
    ("-aarch64-enable-stp-suppress", [False]),
    ("-aarch64-enable-ldst-opt", [False]),
    ("-aarch64-enable-copyelim", [False]),
    ("-aarch64-enable-dead-defs", [False]),
    ("-aarch64-enable-mcr", [False]),
    ("-aarch64-enable-simd-scalar", [True]),
    ("-aarch64-enable-cond-br-tune", [False]),
    ("-reverse-csr-restore-seq", [True]),

    # If-conversion
    ("-disable-ifcvt-simple", [True]),
    ("-disable-ifcvt-triangle", [True]),
    ("-disable-ifcvt-diamond", [True]),
    ("-disable-early-ifcvt", [True]),

    # Block placement / tail dup
    ("-disable-block-placement", [True]),
    ("-disable-tail-duplicate", [True]),
    ("-precise-rotation-cost", [True]),

    # Sinking / hoisting
    ("-machine-sink-split", [False]),
    ("-disable-machine-sink", [True]),
    ("-disable-machine-licm", [True]),
    ("-disable-machine-cse", [True]),
    ("-hoist-cheap-insts", [True]),
    ("-sink-insts-to-avoid-spills", [True]),
    ("-avoid-speculation", [False]),    # default true

    # Passes
    ("-disable-peephole", [True]),
    ("-aggressive-ext-opt", [True]),
    ("-disable-branch-fold", [True]),
    ("-disable-machine-dce", [True]),
    ("-disable-post-ra", [True]),
    ("-disable-postra-machine-licm", [True]),
    ("-disable-postra-machine-sink", [True]),
    ("-enable-ipra", [True]),

    # DAG combiner
    ("-combiner-global-alias-analysis", [True]),
    ("-jump-is-expensive", [True]),
]

# Numeric flags: test a few values
NUMERIC_FLAGS = [
    ("-max-sched-reorder", [1, 2, 4, 8, 12]),
    ("-aarch64-load-store-scan-limit", [5, 10, 40, 100]),
    ("-aarch64-update-scan-limit", [20, 50, 200]),
    ("-tail-dup-size", [0, 1, 4, 6]),
    ("-regalloc-csr-first-time-cost", [1, 5, 10, 50]),
    ("-lcr-max-depth", [1, 3, 10]),
    ("-lcr-max-interf", [2, 4, 16]),
    ("-huge-size-for-split", [500, 2000, 10000]),
    ("-early-ifcvt-limit", [10, 20, 50]),
    ("-aarch64-ccmp-limit", [10, 20, 50]),
    ("-machine-combiner-inc-threshold", [100, 200, 1000]),
    ("-min-jump-table-entries", [2, 6, 8]),
    ("-loop-to-cold-block-ratio", [2, 3, 10]),
    ("-sched-high-latency-cycles", [5, 15, 20]),
]

# ─── ELF helpers (from verify_all.py) ────────────────────────────────

def load_elf_segments(path):
    segments = []
    with open(path, 'rb') as f:
        f.seek(0x20)
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)
        phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]
            f.read(4)
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]
            f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1:
                segments.append((p_vaddr, p_offset, p_filesz))
    return segments


def read_bytes_at(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None


def load_csv():
    """Load functions.csv into a dict: short_name -> (addr, size, quality)."""
    lookup = {}
    with open(FUNCTIONS_CSV) as f:
        for row in csv.DictReader(f):
            addr = int(row['Address'], 16)
            size = int(row['Size'])
            quality = row['Quality']
            name = row['Name']
            lookup[name] = (addr, size, quality)
    return lookup


def extract_short_name(mangled):
    if not mangled.startswith('_Z'):
        return mangled
    prefix = "_ZN3app8lua_bind"
    if mangled.startswith(prefix):
        rest = mangled[len(prefix):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i > 0:
            length = int(rest[:i])
            name = rest[i:i + length]
            if len(name) == length:
                return name
    if mangled.startswith('_ZN'):
        rest = mangled[3:]
        last_name = None
        while rest and rest[0] != 'E':
            i = 0
            while i < len(rest) and rest[i].isdigit():
                i += 1
            if i == 0:
                break
            length = int(rest[:i])
            name = rest[i:i + length]
            if len(name) < length:
                break
            last_name = name
            rest = rest[i + length:]
        if last_name:
            return last_name
    return mangled


def read_o_sections(obj_path):
    """Read .text sections from .o file. Returns list of (mangled_name, code_bytes)."""
    funcs = []
    try:
        with open(obj_path, 'rb') as f:
            ident = f.read(16)
            if ident[:4] != b'\x7fELF':
                return funcs
            f.seek(0x28)
            shoff = struct.unpack('<Q', f.read(8))[0]
            f.seek(0x3a)
            shentsize = struct.unpack('<H', f.read(2))[0]
            shnum = struct.unpack('<H', f.read(2))[0]
            shstrndx = struct.unpack('<H', f.read(2))[0]
            if shnum == 0:
                return funcs
            # Read section name string table
            f.seek(shoff + shstrndx * shentsize + 0x18)
            strtab_off = struct.unpack('<Q', f.read(8))[0]
            strtab_sz = struct.unpack('<Q', f.read(8))[0]
            f.seek(strtab_off)
            strtab = f.read(strtab_sz)
            # Read all sections
            for i in range(shnum):
                f.seek(shoff + i * shentsize)
                sh_name_off = struct.unpack('<I', f.read(4))[0]
                sh_type = struct.unpack('<I', f.read(4))[0]
                f.read(8)  # sh_flags
                f.read(8)  # sh_addr
                sh_offset = struct.unpack('<Q', f.read(8))[0]
                sh_size = struct.unpack('<Q', f.read(8))[0]
                # Get section name
                end = strtab.index(b'\0', sh_name_off)
                sec_name = strtab[sh_name_off:end].decode('ascii', errors='replace')
                if sec_name.startswith('.text.') and sh_type == 1 and sh_size > 0:
                    mangled = sec_name[6:]
                    f.seek(sh_offset)
                    code = f.read(sh_size)
                    funcs.append((mangled, code))
    except Exception:
        pass
    return funcs


# ─── Comparison engine ────────────────────────────────────────────────

def compare_function_quick(decomp_words, orig_words):
    """Quick compare: count matching instructions (ignoring relocations).
    Returns (match_count, total_count)."""
    n = min(len(decomp_words), len(orig_words))
    matches = sum(1 for i in range(n) if decomp_words[i] == orig_words[i])
    return matches, n


def compile_and_score(src_file, extra_flags, csv_lookup, orig_segments, orig_f):
    """Compile one source file with extra flags, return match score.
    Returns (verified_count, total_compared, details)."""
    o_path = BUILD_DIR / "fuzz_test.o"
    cmd = '%s %s %s -c "%s" -o "%s"' % (
        CLANG, CFLAGS_BASE, extra_flags, src_file, o_path)
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True,
                      cwd=str(PROJECT_ROOT), timeout=60)
    if r.returncode != 0:
        return -1, 0, "compile error"

    funcs = read_o_sections(str(o_path))
    verified = 0
    total = 0
    for mangled, code in funcs:
        size = len(code)
        if size < 4:
            continue
        # Look up in CSV
        if mangled in csv_lookup:
            addr, csv_size, quality = csv_lookup[mangled]
        else:
            short = extract_short_name(mangled)
            found = False
            for name, (addr, csv_size, quality) in csv_lookup.items():
                if extract_short_name(name) == short and csv_size == size:
                    found = True
                    break
            if not found:
                continue

        if csv_size != size:
            continue

        # Read original bytes
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
        orig_bytes = read_bytes_at(orig_f, orig_segments, vaddr, size)
        if orig_bytes is None or len(orig_bytes) != size:
            continue

        # Compare instruction-by-instruction (no relocation patching for speed)
        n = size // 4
        decomp_words = [struct.unpack_from('<I', code, i * 4)[0] for i in range(n)]
        orig_words = [struct.unpack_from('<I', orig_bytes, i * 4)[0] for i in range(n)]
        matches, total_insns = compare_function_quick(decomp_words, orig_words)

        total += 1
        if matches == total_insns:
            verified += 1

    return verified, total, ""


# ─── Main fuzzer ──────────────────────────────────────────────────────

def run_sweep(src_files, csv_lookup, orig_segments, orig_f):
    """Phase 1: Test each flag individually."""
    # Get baseline
    print("=== BASELINE (no extra flags) ===")
    baseline_v = 0
    baseline_t = 0
    for src in src_files:
        v, t, _ = compile_and_score(src, "", csv_lookup, orig_segments, orig_f)
        if v >= 0:
            baseline_v += v
            baseline_t += t
    print("  Baseline: %d/%d verified (%.1f%%)" % (
        baseline_v, baseline_t, baseline_v * 100 / baseline_t if baseline_t else 0))
    print()

    results = []

    # Test boolean flags
    total_tests = sum(len(vals) for _, vals in BOOL_FLAGS) + \
                  sum(len(vals) for _, vals in NUMERIC_FLAGS)
    test_num = 0

    for flag_name, values in BOOL_FLAGS:
        for val in values:
            test_num += 1
            flag_str = "-mllvm %s=%s" % (flag_name, "true" if val else "false")
            sys.stdout.write("\r[%d/%d] Testing: %s ...       " % (
                test_num, total_tests, flag_str))
            sys.stdout.flush()

            total_v = 0
            total_t = 0
            ok = True
            for src in src_files:
                v, t, err = compile_and_score(
                    src, flag_str, csv_lookup, orig_segments, orig_f)
                if v < 0:
                    ok = False
                    break
                total_v += v
                total_t += t

            if ok and total_t > 0:
                delta = total_v - baseline_v
                results.append((flag_str, total_v, total_t, delta))

    # Test numeric flags
    for flag_name, values in NUMERIC_FLAGS:
        for val in values:
            test_num += 1
            flag_str = "-mllvm %s=%d" % (flag_name, val)
            sys.stdout.write("\r[%d/%d] Testing: %s ...       " % (
                test_num, total_tests, flag_str))
            sys.stdout.flush()

            total_v = 0
            total_t = 0
            ok = True
            for src in src_files:
                v, t, err = compile_and_score(
                    src, flag_str, csv_lookup, orig_segments, orig_f)
                if v < 0:
                    ok = False
                    break
                total_v += v
                total_t += t

            if ok and total_t > 0:
                delta = total_v - baseline_v
                results.append((flag_str, total_v, total_t, delta))

    print("\r" + " " * 80)
    print()

    # Sort by delta (most improvement first)
    results.sort(key=lambda x: -x[3])

    print("=== RESULTS (sorted by delta) ===")
    print("%-55s  %6s  %6s  %6s" % ("Flag", "Match", "Total", "Delta"))
    print("-" * 80)
    for flag_str, v, t, delta in results[:40]:
        marker = " <<<" if delta > 0 else ""
        print("%-55s  %6d  %6d  %+5d%s" % (flag_str, v, t, delta, marker))
    print()
    print("Baseline: %d/%d" % (baseline_v, baseline_t))

    # Report winners
    winners = [r for r in results if r[3] > 0]
    if winners:
        print()
        print("=== WINNERS (%d flags improve matches) ===" % len(winners))
        for flag_str, v, t, delta in winners:
            print("  %+d  %s" % (delta, flag_str))
    else:
        print()
        print("No individual flag improved matches.")

    return results, baseline_v, baseline_t


def run_phase2(winners, src_files, csv_lookup, orig_segments, orig_f, baseline_v):
    """Phase 2: Combine winning flags greedily."""
    if not winners:
        print("No winners to combine.")
        return

    print()
    print("=== PHASE 2: Greedy combination ===")
    current_flags = []
    current_v = baseline_v

    for flag_str, _, _, _ in winners:
        # Try adding this flag to the current set
        combined = " ".join(current_flags + [flag_str])
        total_v = 0
        total_t = 0
        ok = True
        for src in src_files:
            v, t, _ = compile_and_score(
                src, combined, csv_lookup, orig_segments, orig_f)
            if v < 0:
                ok = False
                break
            total_v += v
            total_t += t

        if ok and total_v > current_v:
            current_flags.append(flag_str)
            delta = total_v - current_v
            current_v = total_v
            print("  ADD %s  (+%d, total: %d)" % (flag_str, delta, current_v))
        else:
            print("  skip %s  (no improvement or compile error)" % flag_str)

    print()
    print("=== FINAL FLAG SET ===")
    if current_flags:
        print("  Matches: %d (baseline was %d, +%d)" % (
            current_v, baseline_v, current_v - baseline_v))
        print("  Flags:")
        for f in current_flags:
            print("    %s" % f)
    else:
        print("  No combination improved over baseline.")


def main():
    parser = argparse.ArgumentParser(description='LLVM flag fuzzer')
    parser.add_argument('--src', nargs='*', default=None,
                       help='Source files to test (default: auto-select)')
    parser.add_argument('--phase2', action='store_true',
                       help='Run phase 2 (combine winners)')
    parser.add_argument('--test-flag', default=None,
                       help='Test a single flag')
    parser.add_argument('--all-src', action='store_true',
                       help='Test all source files (slow)')
    args = parser.parse_args()

    # Select source files to test
    if args.src:
        src_files = [Path(s) for s in args.src]
    elif args.all_src:
        src_files = sorted(Path(PROJECT_ROOT / "src").rglob("*.cpp"))
    else:
        # Default: pick a representative sample of files with non-matching functions
        candidates = [
            "src/app/FighterManager.cpp",
            "src/app/fighter_status.cpp",
            "src/app/fighter_motion.cpp",
            "src/app/FighterInformation.cpp",
            "src/app/fighter_effects.cpp",
            "src/app/fighter_attack.cpp",
            "src/app/BattleObjectManager.cpp",
            "src/app/DamageInfo.cpp",
        ]
        src_files = [PROJECT_ROOT / c for c in candidates if (PROJECT_ROOT / c).exists()]

    print("Testing with %d source files" % len(src_files))
    for s in src_files:
        print("  %s" % s.name)
    print()

    # Load data
    csv_lookup = load_csv()
    orig_segments = load_elf_segments(str(ORIGINAL_ELF))

    BUILD_DIR.mkdir(exist_ok=True)

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        if args.test_flag:
            # Quick test of a single flag
            flag_str = "-mllvm " + args.test_flag
            print("Testing: %s" % flag_str)
            total_v = 0
            total_t = 0
            for src in src_files:
                v, t, err = compile_and_score(
                    src, flag_str, csv_lookup, orig_segments, orig_f)
                if v >= 0:
                    total_v += v
                    total_t += t
                else:
                    print("  ERROR on %s: %s" % (src.name, err))
            print("  Result: %d/%d verified" % (total_v, total_t))
            return

        results, baseline_v, baseline_t = run_sweep(
            src_files, csv_lookup, orig_segments, orig_f)

        if args.phase2:
            winners = [(r[0], r[1], r[2], r[3]) for r in results if r[3] > 0]
            run_phase2(winners, src_files, csv_lookup, orig_segments, orig_f,
                      baseline_v)


if __name__ == '__main__':
    main()
