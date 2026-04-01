#!/usr/bin/env python3
"""
Batch decompile functions via Ghidra MCP and auto-convert to compilable C++.

Pulls Ghidra's decompilation for uncompiled functions, performs type fixups,
and writes compilable C++ source files.

Usage:
    python tools/batch_ghidra_decomp.py --tier MEDIUM --limit 50 --dry-run
    python tools/batch_ghidra_decomp.py --tier MEDIUM --limit 50 --apply
    python tools/batch_ghidra_decomp.py --tier MEDIUM --addr-range 0x7100000000-0x7100FFFFFF --apply
"""

import csv
import json
import os
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
TRIAGE_CSV = PROJECT_ROOT / "data" / "fun_triage.csv"
BUILD_DIR = PROJECT_ROOT / "build"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"

# Ghidra MCP is accessed via the claude MCP protocol — we can't call it directly
# from a script. Instead, this tool prepares the work and outputs a script that
# a Claude session can execute.
#
# For direct batch use, we output the function list and let the caller
# handle the Ghidra MCP calls.


def get_compiled_functions():
    """Get set of already-compiled function addresses."""
    compiled_addrs = set()
    # Check CSV for non-U quality
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            if row[1] != 'U':
                compiled_addrs.add(int(row[0], 16))

    # Also check .o files for compiled symbols
    compiled_names = set()
    for fn in os.listdir(BUILD_DIR):
        if not fn.endswith('.o'):
            continue
        result = subprocess.run([OBJDUMP, '-t', str(BUILD_DIR / fn)],
                              capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'F .text' in line:
                compiled_names.add(line.split()[-1])
    return compiled_addrs, compiled_names


def ghidra_c_to_cpp(ghidra_code, func_addr, func_name, func_size):
    """Convert Ghidra's decompiled C to compilable C++ for matching decomp.

    Performs type conversions, fixes casts, and wraps appropriately.
    Returns (code, needs_review) tuple.
    """
    code = ghidra_code.strip()
    needs_review = False

    # Type replacements
    type_map = {
        'undefined8': 'u64',
        'undefined4': 'u32',
        'undefined2': 'u16',
        'undefined1': 'u8',
        'undefined': 'u8',
        'uint': 'u32',
        'int': 's32',
        'long': 's64',
        'ulong': 'u64',
        'ushort': 'u16',
        'short': 's16',
        'byte': 'u8',
        'bool': 'u8',  # NX Clang treats bool as u8 for matching
        'longlong': 's64',
        'ulonglong': 'u64',
    }

    # Replace types in declarations and casts
    for ghidra_type, cpp_type in type_map.items():
        # Word-boundary replacement to avoid partial matches
        code = re.sub(r'\b' + ghidra_type + r'\b', cpp_type, code)

    # Fix Ghidra's (type *)0x0 -> nullptr or (type*)0
    code = re.sub(r'\([^)]*\s*\*\)\s*0x0\b', 'nullptr', code)
    code = re.sub(r'\(\s*void\s*\*\)\s*0\b', 'nullptr', code)

    # Fix Ghidra's SUB81/SUB41 etc (these are type narrowing)
    code = re.sub(r'SUB\d+\(([^,]+),\s*0\)', r'(u8)(\1)', code)

    # Fix CONCAT patterns
    if 'CONCAT' in code:
        needs_review = True

    # Fix ZEXT/SEXT patterns
    code = re.sub(r'ZEXT(\d+)\(([^)]+)\)', r'(u\1)(\2)', code)
    code = re.sub(r'SEXT(\d+)\(([^)]+)\)', r'(s\1)(\2)', code)

    # Replace function name with our naming convention
    # Ghidra uses FUN_ADDR format
    m = re.match(r'(\w+)\s+(FUN_[0-9a-f]+)\s*\(', code)
    if m:
        ret_type = m.group(1)
        old_name = m.group(2)
        # Use the CSV name or generate one
        new_name = func_name
        if new_name.startswith('FUN_'):
            # Add address suffix for uniqueness in lua_bind namespace
            addr_suffix = '%x' % (func_addr & 0xFFFFFFFF)
            new_name = '%s_%s' % (new_name, addr_suffix)
        code = code.replace(old_name, new_name, 1)

    # Check for unsupported patterns
    if 'switchD' in code or 'caseD' in code:
        needs_review = True
    if '__stack_chk' in code:
        needs_review = True
    if 'in_' in code and 'in_stack' not in code:
        # Ghidra register references like in_x8
        needs_review = True

    return code, needs_review


def get_targets(tier, addr_range, limit, compiled_addrs):
    """Get list of target functions to decompile."""
    targets = []
    addr_min, addr_max = 0, 0xFFFFFFFFFFFFFFFF
    if addr_range:
        parts = addr_range.split('-')
        addr_min = int(parts[0], 16)
        addr_max = int(parts[1], 16)

    with open(TRIAGE_CSV) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if tier and row.get('Tier') != tier:
                continue
            addr = int(row['Address'], 16)
            if addr < addr_min or addr > addr_max:
                continue
            if addr in compiled_addrs:
                continue
            size = int(row['Size'])
            targets.append((addr, row.get('Name', 'FUN_%x' % addr), size))
            if len(targets) >= limit:
                break

    return targets


def main():
    dry_run = '--dry-run' in sys.argv
    do_apply = '--apply' in sys.argv
    tier = None
    addr_range = None
    limit = 50

    for i, arg in enumerate(sys.argv):
        if arg == '--tier' and i + 1 < len(sys.argv):
            tier = sys.argv[i + 1]
        if arg == '--addr-range' and i + 1 < len(sys.argv):
            addr_range = sys.argv[i + 1]
        if arg == '--limit' and i + 1 < len(sys.argv):
            limit = int(sys.argv[i + 1])

    compiled_addrs, compiled_names = get_compiled_functions()
    targets = get_targets(tier, addr_range, limit, compiled_addrs)

    print("Targets: %d functions (tier=%s, limit=%d)" % (
        len(targets), tier or 'all', limit))

    if not targets:
        print("No targets found.")
        return

    # Output the target list for Ghidra MCP batch processing
    out_file = PROJECT_ROOT / "build" / "batch_targets.json"
    target_data = [{"address": "0x%x" % addr, "name": name, "size": size}
                   for addr, name, size in targets]

    with open(out_file, 'w') as f:
        json.dump(target_data, f, indent=2)

    print("Wrote %d targets to %s" % (len(targets), out_file))
    print()
    print("Sample targets:")
    for addr, name, size in targets[:10]:
        print("  0x%x  %s  (%d bytes)" % (addr, name, size))

    if dry_run:
        print()
        print("To process these, a Claude session should:")
        print("  1. Read build/batch_targets.json")
        print("  2. For each target, call mcp__ghidra__decompile_function_by_address")
        print("  3. Run ghidra_c_to_cpp() on each result")
        print("  4. Write to source files")
        return

    if do_apply:
        print()
        print("Batch apply mode: this requires Ghidra MCP access.")
        print("Use this script from within a Claude session that has MCP tools.")
        print("Or use --dry-run to generate the target list for manual processing.")


if __name__ == '__main__':
    main()
