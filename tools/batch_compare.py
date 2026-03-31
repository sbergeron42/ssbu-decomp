#!/usr/bin/env python3
"""
Batch compare all compiled functions against the original 13.0.4 binary.

Reads data/functions.csv for addresses, scans compiled .o files for functions,
and compares bytes against original/main.elf.
"""

import csv
import struct
import subprocess
import sys
import re
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "original" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
ELF_BASE = 0x7100000000


def load_elf_segments():
    """Parse ELF program headers once."""
    segments = []
    with open(ORIGINAL_ELF, 'rb') as f:
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


def get_object_functions(obj_path):
    """Get all functions from an object file with their raw bytes."""
    result = subprocess.run(
        [OBJDUMP, "-d", obj_path],
        capture_output=True, text=True
    )

    functions = []
    current_name = None
    current_bytes = bytearray()

    for line in result.stdout.split('\n'):
        # New section = new function
        if line.startswith('Disassembly of section .text.'):
            if current_name and current_bytes:
                functions.append((current_name, bytes(current_bytes)))
            current_name = line.split('.text.')[1].rstrip(':')
            current_bytes = bytearray()
            continue

        # Parse instruction bytes
        match = re.match(r'\s+[0-9a-f]+:\s+((?:[0-9a-f]{2} )+)', line)
        if match and current_name:
            hex_str = match.group(1).strip().replace(' ', '')
            current_bytes.extend(bytes.fromhex(hex_str))

    if current_name and current_bytes:
        functions.append((current_name, bytes(current_bytes)))

    return functions


def main():
    # Load function database
    addr_map = {}
    with open(PROJECT_ROOT / "data" / "functions.csv") as f:
        for row in csv.DictReader(f):
            name = row['Name']
            addr = int(row['Address'], 16)
            addr_map[name] = addr

    segments = load_elf_segments()

    perfect = 0
    partial = 0
    failed = 0
    skipped = 0
    total_insns = 0
    matching_insns = 0

    results = []

    with open(ORIGINAL_ELF, 'rb') as elf_f:
        for obj_file in sorted(BUILD_DIR.glob("*.o")):
            functions = get_object_functions(str(obj_file))

            for func_name, compiled_bytes in functions:
                # Try to find address in CSV by matching function name substrings
                addr = None
                matched_csv_name = None
                for csv_name, csv_addr in addr_map.items():
                    if csv_name in func_name or func_name.endswith(csv_name):
                        addr = csv_addr
                        matched_csv_name = csv_name
                        break

                if addr is None:
                    skipped += 1
                    continue

                # Convert Ghidra address to ELF vaddr
                vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr

                # Read original bytes
                orig_bytes = read_bytes(elf_f, segments, vaddr, len(compiled_bytes))
                if orig_bytes is None:
                    skipped += 1
                    continue

                # Compare 4 bytes at a time (instruction-level)
                num_insns = len(compiled_bytes) // 4
                match_count = 0
                for i in range(0, len(compiled_bytes), 4):
                    if compiled_bytes[i:i+4] == orig_bytes[i:i+4]:
                        match_count += 1

                total_insns += num_insns
                matching_insns += match_count

                if match_count == num_insns:
                    perfect += 1
                elif match_count > 0:
                    partial += 1
                    results.append((matched_csv_name, match_count, num_insns))
                else:
                    failed += 1
                    results.append((matched_csv_name, 0, num_insns))

    total = perfect + partial + failed

    print("=" * 70)
    print("  SSBU Decomp — Binary Comparison Results (13.0.4)")
    print("=" * 70)
    print()
    print(f"  Functions compared:  {total}")
    print(f"  Skipped (no addr):   {skipped}")
    print()
    print(f"  PERFECT MATCH:       {perfect:>5}  ({perfect*100//total:.1f}%)" if total else "")
    print(f"  Partial match:       {partial:>5}  ({partial*100//total:.1f}%)" if total else "")
    print(f"  No match:            {failed:>5}  ({failed*100//total:.1f}%)" if total else "")
    print()
    print(f"  Instructions: {matching_insns}/{total_insns} match ({matching_insns*100//total_insns:.1f}%)" if total_insns else "")
    print()

    if partial > 0 or failed > 0:
        print("  Non-perfect functions:")
        for name, mc, tc in sorted(results, key=lambda x: x[1]/x[2] if x[2] else 0):
            pct = mc * 100 // tc if tc else 0
            print(f"    {name}: {mc}/{tc} ({pct}%)")

    print()


if __name__ == '__main__':
    main()
