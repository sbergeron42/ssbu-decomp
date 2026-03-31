#!/usr/bin/env python3
"""
Verify all compiled functions against the original 13.0.4 binary.

Reads the linked ELF's symbol table, maps each function to its original
address via data/functions.csv, and compares bytes instruction-by-instruction.

Usage:
    python tools/verify_all.py              # Full report
    python tools/verify_all.py --summary    # Summary only
    python tools/verify_all.py --update     # Update functions.csv with results
"""

import csv
import struct
import subprocess
import sys
import re
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "original" / "main.elf"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
ELF_BASE = 0x7100000000


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


def read_bytes(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None


def get_decomp_symbols():
    """Get all function symbols from the decomp ELF."""
    result = subprocess.run(
        [OBJDUMP, "-t", str(DECOMP_ELF)],
        capture_output=True, text=True
    )
    symbols = []
    for line in result.stdout.split('\n'):
        if 'F .text' in line:
            parts = line.split()
            addr = int(parts[0], 16)
            size = int(parts[4], 16) if len(parts) > 4 else 0
            name = parts[-1] if parts else ''
            if size > 0 and name:
                symbols.append((name, addr, size))
    return symbols


def demangle(name):
    """Simple C++ demangling — extract the function name."""
    # Try to use c++filt or llvm-cxxfilt
    try:
        result = subprocess.run(
            [r"C:\llvm-8.0.0\bin\llvm-cxxfilt.exe", name],
            capture_output=True, text=True, timeout=2
        )
        if result.returncode == 0:
            return result.stdout.strip()
    except:
        pass
    return name


def build_csv_lookup():
    """Build a lookup from function name substrings to CSV addresses."""
    lookup = {}
    with open(FUNCTIONS_CSV) as f:
        for row in csv.DictReader(f):
            name = row['Name']
            addr = int(row['Address'], 16)
            lookup[name] = addr
    return lookup


def match_symbol_to_csv(mangled_name, demangled, csv_lookup):
    """Try to match a decomp symbol to a CSV entry."""
    # Extract the impl function name from demangled name
    # e.g. "app::lua_bind::WorkModule__get_float_impl(app::BattleObjectModuleAccessor*, int)"
    # -> "WorkModule__get_float_impl"
    if '::' in demangled:
        parts = demangled.split('::')
        for part in parts:
            if '__' in part:
                func_name = part.split('(')[0]
                if func_name in csv_lookup:
                    return csv_lookup[func_name]

    # Try matching the mangled name directly
    for csv_name, csv_addr in csv_lookup.items():
        if csv_name in mangled_name:
            return csv_addr

    return None


def main():
    summary_only = '--summary' in sys.argv
    update_csv = '--update' in sys.argv

    # Get decomp symbols
    symbols = get_decomp_symbols()
    csv_lookup = build_csv_lookup()

    # Load ELF segments
    orig_segments = load_elf_segments(ORIGINAL_ELF)
    decomp_segments = load_elf_segments(DECOMP_ELF)

    perfect = 0
    equivalent = 0
    mismatch = 0
    unmatched = 0
    total_bytes_matched = 0
    total_bytes_compared = 0

    results = {}  # csv_name -> (status, match_pct)
    details = []

    with open(ORIGINAL_ELF, 'rb') as orig_f, open(DECOMP_ELF, 'rb') as decomp_f:
        for mangled, decomp_addr, size in symbols:
            demangled = demangle(mangled)
            orig_addr = match_symbol_to_csv(mangled, demangled, csv_lookup)

            if orig_addr is None:
                unmatched += 1
                continue

            # Convert Ghidra address to ELF vaddr
            orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr

            # Read both
            orig_bytes = read_bytes(orig_f, orig_segments, orig_vaddr, size)
            decomp_bytes = read_bytes(decomp_f, decomp_segments, decomp_addr, size)

            if orig_bytes is None or decomp_bytes is None:
                unmatched += 1
                continue

            # Compare instruction by instruction (4 bytes each)
            num_insns = size // 4
            match_count = 0
            for i in range(0, min(len(orig_bytes), len(decomp_bytes)), 4):
                if orig_bytes[i:i+4] == decomp_bytes[i:i+4]:
                    match_count += 1

            total_bytes_compared += size
            matched_bytes = match_count * 4
            total_bytes_matched += matched_bytes

            # Extract short name for display
            short_name = demangled.split('(')[0].split('::')[-1] if '::' in demangled else demangled

            if match_count == num_insns:
                perfect += 1
                status = 'M'
            elif match_count >= num_insns * 0.9:
                equivalent += 1
                status = 'E'
                if not summary_only:
                    details.append((short_name, match_count, num_insns))
            else:
                mismatch += 1
                status = 'N'
                if not summary_only:
                    details.append((short_name, match_count, num_insns))

            # Find CSV name for update
            for csv_name, csv_addr in csv_lookup.items():
                if csv_addr == orig_addr:
                    results[csv_name] = (status, match_count * 100 // num_insns if num_insns else 0)
                    break

    total = perfect + equivalent + mismatch
    total_funcs = len(symbols)

    print()
    print("=" * 70)
    print("  SSBU Decomp — Verified Binary Comparison (13.0.4)")
    print("=" * 70)
    print()
    print(f"  Total compiled functions:  {total_funcs}")
    print(f"  Matched to CSV address:    {total}")
    print(f"  Unmatched (no CSV entry):  {unmatched}")
    print()

    if total > 0:
        bar_w = 40
        pf = perfect * bar_w // total
        eq = equivalent * bar_w // total
        mm = max(0, bar_w - pf - eq)
        bar = '#' * pf + '~' * eq + '-' * mm
        print(f"  [{bar}]")
        print()
        print(f"  PERFECT MATCH:    {perfect:>5}  ({perfect*100/total:.1f}%)")
        print(f"  Equivalent (>90%): {equivalent:>4}  ({equivalent*100/total:.1f}%)")
        print(f"  Non-matching:     {mismatch:>5}  ({mismatch*100/total:.1f}%)")
        print()
        print(f"  Bytes: {total_bytes_matched:,} / {total_bytes_compared:,} match ({total_bytes_matched*100//total_bytes_compared}%)")
    print()

    if details and not summary_only:
        print("  Non-perfect functions:")
        for name, mc, tc in sorted(details, key=lambda x: -x[1]/x[2] if x[2] else 0)[:30]:
            pct = mc * 100 // tc if tc else 0
            print(f"    {name}: {mc}/{tc} ({pct}%)")
        if len(details) > 30:
            print(f"    ... and {len(details) - 30} more")

    print()

    # Update CSV if requested
    if update_csv and results:
        rows = []
        with open(FUNCTIONS_CSV) as f:
            reader = csv.DictReader(f)
            fieldnames = reader.fieldnames
            for row in reader:
                name = row['Name']
                if name in results:
                    status, _ = results[name]
                    row['Status'] = status
                rows.append(row)
        with open(FUNCTIONS_CSV, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames, extrasaction='ignore')
            writer.writeheader()
            writer.writerows(rows)
        print(f"  Updated {len(results)} entries in functions.csv")


if __name__ == '__main__':
    main()
