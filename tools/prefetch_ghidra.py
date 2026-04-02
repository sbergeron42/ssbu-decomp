#!/usr/bin/env python3
"""
Pre-fetch Ghidra decompilations into a JSON cache for token-efficient batch decomp.

Run this from an orchestrator session (has MCP access). Workers then read
the cache via write_from_cache.py without needing Ghidra MCP.

Usage:
    python tools/prefetch_ghidra.py --limit 50     # Prefetch 50 functions
    python tools/prefetch_ghidra.py --limit 500    # Prefetch 500
    python tools/prefetch_ghidra.py --range 0x7100  # Specific range
"""

import csv
import json
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
TRIAGE_CSV = PROJECT_ROOT / "data" / "fun_triage.csv"
CACHE_FILE = PROJECT_ROOT / "data" / "ghidra_cache.json"
BUILD_DIR = PROJECT_ROOT / "build"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"


def ghidra_c_to_cpp(ghidra_code, func_addr, func_name, func_size):
    """Convert Ghidra C to compilable C++."""
    code = ghidra_code.strip()
    needs_review = False

    type_map = {
        'undefined8': 'u64', 'undefined4': 'u32', 'undefined2': 'u16',
        'undefined1': 'u8', 'undefined': 'u8', 'uint': 'u32',
        'int': 's32', 'long': 's64', 'ulong': 'u64', 'ushort': 'u16',
        'short': 's16', 'byte': 'u8', 'bool': 'u8',
        'longlong': 's64', 'ulonglong': 'u64',
    }

    for ghidra_type, cpp_type in type_map.items():
        code = re.sub(r'\b' + ghidra_type + r'\b', cpp_type, code)

    code = re.sub(r'\([^)]*\s*\*\)\s*0x0\b', 'nullptr', code)
    code = re.sub(r'\(\s*void\s*\*\)\s*0\b', 'nullptr', code)

    if 'CONCAT' in code or 'switchD' in code or '__stack_chk' in code:
        needs_review = True

    code = re.sub(r'SUB\d+\(([^,]+),\s*0\)', r'(u8)(\1)', code)
    code = re.sub(r'ZEXT(\d+)\(([^)]+)\)', r'(u\1)(\2)', code)
    code = re.sub(r'SEXT(\d+)\(([^)]+)\)', r'(s\1)(\2)', code)

    # Rename FUN_ to include address suffix
    m = re.match(r'(\w+)\s+(FUN_[0-9a-f]+)\s*\(', code)
    if m:
        old_name = m.group(2)
        addr_suffix = '%x' % (func_addr & 0xFFFFFFFF)
        new_name = '%s_%s' % (old_name, addr_suffix)
        code = code.replace(old_name, new_name, 1)

    return code, needs_review


def get_compiled_addrs():
    """Get set of already-compiled function addresses."""
    compiled = set()
    for fn in os.listdir(BUILD_DIR):
        if not fn.endswith('.o'):
            continue
        try:
            with open(BUILD_DIR / fn, 'rb') as f:
                ident = f.read(16)
                if ident[:4] != b'\x7fELF':
                    continue
                f.seek(0x28)
                shoff = struct.unpack('<Q', f.read(8))[0]
                f.seek(0x3a)
                shentsize = struct.unpack('<H', f.read(2))[0]
                shnum = struct.unpack('<H', f.read(2))[0]
                shstrndx = struct.unpack('<H', f.read(2))[0]
                f.seek(shoff + shstrndx * shentsize + 0x18)
                strtab_off = struct.unpack('<Q', f.read(8))[0]
                strtab_sz = struct.unpack('<Q', f.read(8))[0]
                f.seek(strtab_off)
                strtab = f.read(strtab_sz)
                for i in range(shnum):
                    f.seek(shoff + i * shentsize)
                    sh_name_idx = struct.unpack('<I', f.read(4))[0]
                    sh_type = struct.unpack('<I', f.read(4))[0]
                    if sh_type != 1:
                        continue
                    end = strtab.index(b'\0', sh_name_idx)
                    sec_name = strtab[sh_name_idx:end].decode('ascii', errors='replace')
                    if sec_name.startswith('.text.'):
                        # Extract address from function name if possible
                        name = sec_name[6:]
                        m = re.search(r'([0-9a-f]{5,8})E?[A-Z]', name)
                        # Just mark the name as compiled
                        compiled.add(name)
        except:
            pass
    return compiled


def main():
    limit = 50
    addr_range = None
    tier = 'MEDIUM'

    for i, arg in enumerate(sys.argv):
        if arg == '--limit' and i + 1 < len(sys.argv):
            limit = int(sys.argv[i + 1])
        if arg == '--range' and i + 1 < len(sys.argv):
            addr_range = sys.argv[i + 1]
        if arg == '--tier' and i + 1 < len(sys.argv):
            tier = sys.argv[i + 1]

    # Load existing cache
    cache = {}
    if CACHE_FILE.exists():
        with open(CACHE_FILE) as f:
            cache = json.load(f)
        print("Loaded existing cache: %d entries" % len(cache))

    # Get targets
    compiled = get_compiled_addrs()
    targets = []
    with open(TRIAGE_CSV) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if tier and row.get('Tier') != tier:
                continue
            addr_str = row['Address']
            addr = int(addr_str, 16)
            if addr_range and not addr_str.startswith(addr_range):
                continue
            # Skip if already in cache
            if addr_str in cache:
                continue
            size = int(row['Size'])
            name = row.get('Name', 'FUN_%x' % addr)
            targets.append((addr_str, addr, name, size))
            if len(targets) >= limit:
                break

    print("Targets to prefetch: %d (limit=%d, tier=%s)" % (
        len(targets), limit, tier))

    if not targets:
        print("Nothing to prefetch.")
        return

    # This function is meant to be called from a session with MCP access.
    # Output the targets as a JSON list for the caller to process.
    out = PROJECT_ROOT / "build" / "prefetch_targets.json"
    with open(out, 'w') as f:
        json.dump([{"address": a, "name": n, "size": s}
                   for a, _, n, s in targets], f, indent=2)

    print("Wrote %d targets to %s" % (len(targets), out))
    print()
    print("To prefetch, call mcp__ghidra__decompile_function_by_address for each")
    print("and save results to %s" % CACHE_FILE)


if __name__ == '__main__':
    main()
