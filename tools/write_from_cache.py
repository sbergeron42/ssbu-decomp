#!/usr/bin/env python3
"""
Write C++ source files from pre-fetched Ghidra cache. No MCP needed.

Usage:
    python tools/write_from_cache.py --prefix fun_cache_test --batch-size 30
    python tools/write_from_cache.py --prefix fun_batch_d3 --batch-size 40 --range 0x7100
"""

import csv
import json
import os
import re
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
CACHE_FILE = PROJECT_ROOT / "data" / "ghidra_cache.json"
BUILD_DIR = PROJECT_ROOT / "build"
SRC_DIR = PROJECT_ROOT / "src" / "app"


def ghidra_c_to_cpp(ghidra_code, func_addr, func_name):
    """Convert Ghidra C to compilable C++."""
    code = ghidra_code.strip()

    type_map = {
        'undefined8': 'u64', 'undefined4': 'u32', 'undefined2': 'u16',
        'undefined1': 'u8', 'undefined': 'u8', 'uint': 'u32',
        'int': 's32', 'long': 's64', 'ulong': 'u64', 'ushort': 'u16',
        'short': 's16', 'byte': 'u8', 'bool': 'u8',
        'longlong': 's64', 'ulonglong': 'u64',
    }

    for gt, ct in type_map.items():
        code = re.sub(r'\b' + gt + r'\b', ct, code)

    code = re.sub(r'\([^)]*\s*\*\)\s*0x0\b', 'nullptr', code)
    code = re.sub(r'\(\s*void\s*\*\)\s*0\b', 'nullptr', code)
    code = re.sub(r'SUB\d+\(([^,]+),\s*0\)', r'(u8)(\1)', code)
    code = re.sub(r'ZEXT(\d+)\(([^)]+)\)', r'(u\1)(\2)', code)
    code = re.sub(r'SEXT(\d+)\(([^)]+)\)', r'(s\1)(\2)', code)

    # Rename function
    m = re.match(r'(\w+)\s+(FUN_[0-9a-f]+)\s*\(', code)
    if m:
        old_name = m.group(2)
        addr_suffix = '%x' % (func_addr & 0xFFFFFFFF)
        new_name = '%s_%s' % (old_name, addr_suffix)
        code = code.replace(old_name, new_name, 1)

    # Extract extern references (FUN_* and DAT_* calls)
    externs = set()
    for ref in re.findall(r'\b(FUN_[0-9a-fA-F]+)\s*\(', code):
        externs.add(ref)
    for ref in re.findall(r'\b(DAT_[0-9a-fA-F]+)\b', code):
        externs.add(ref)

    has_warning = 'CONCAT' in code or 'switchD' in code or '__stack_chk' in code
    return code, externs, has_warning


def get_compiled_names():
    """Get set of compiled mangled names from .o files."""
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
                        compiled.add(sec_name[6:])
        except:
            pass
    return compiled


def main():
    prefix = 'fun_cache'
    batch_size = 30
    addr_range = None

    for i, arg in enumerate(sys.argv):
        if arg == '--prefix' and i + 1 < len(sys.argv):
            prefix = sys.argv[i + 1]
        if arg == '--batch-size' and i + 1 < len(sys.argv):
            batch_size = int(sys.argv[i + 1])
        if arg == '--range' and i + 1 < len(sys.argv):
            addr_range = sys.argv[i + 1]

    if not CACHE_FILE.exists():
        print("ERROR: No cache at %s" % CACHE_FILE)
        print("Run prefetch_ghidra.py first.")
        return

    with open(CACHE_FILE) as f:
        cache = json.load(f)

    print("Cache entries: %d" % len(cache))

    compiled = get_compiled_names()

    # Filter cache to usable entries
    usable = []
    for addr_str, entry in sorted(cache.items()):
        if entry.get('skipped'):
            continue
        raw = entry.get('ghidra_raw', '')
        if not raw:
            continue
        if addr_range and not addr_str.startswith(addr_range):
            continue
        addr = int(addr_str, 16)
        # Check if already compiled (rough check by address in name)
        addr_suffix = '%x' % (addr & 0xFFFFFFFF)
        already = any(addr_suffix in name for name in compiled)
        if already:
            continue
        usable.append((addr_str, addr, raw))

    print("Usable (not skipped, not compiled): %d" % len(usable))

    if not usable:
        print("Nothing to write.")
        return

    # Write batches
    batch_num = 1
    written = 0
    for start in range(0, len(usable), batch_size):
        batch = usable[start:start + batch_size]
        filename = '%s_%03d.cpp' % (prefix, batch_num)
        filepath = SRC_DIR / filename

        all_externs = set()
        functions = []

        for addr_str, addr, raw in batch:
            name = 'FUN_%x' % addr
            code, externs, has_warning = ghidra_c_to_cpp(raw, addr, name)
            if has_warning:
                continue
            all_externs.update(externs)
            functions.append((addr_str, code))

        if not functions:
            batch_num += 1
            continue

        # Build file content
        lines = ['#include "types.h"', '']

        # Add extern declarations
        for ext in sorted(all_externs):
            if ext.startswith('FUN_'):
                lines.append('extern "C" void %s();' % ext)
            elif ext.startswith('DAT_'):
                lines.append('extern "C" u64 %s;' % ext)
        if all_externs:
            lines.append('')

        # Add functions
        for addr_str, code in functions:
            lines.append('// %s' % addr_str)
            lines.append(code)
            lines.append('')

        filepath.write_text('\n'.join(lines))
        print("  %s: %d functions" % (filename, len(functions)))
        written += len(functions)
        batch_num += 1

    print()
    print("Total written: %d functions in %d files" % (written, batch_num - 1))


if __name__ == '__main__':
    main()
