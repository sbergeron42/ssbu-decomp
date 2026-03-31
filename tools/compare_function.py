#!/usr/bin/env python3
"""
Compare a compiled function against the original binary.

Extracts bytes from the original ELF at a given address and compares
against the compiled object file's function bytes.

Usage:
    python tools/compare_function.py <address> <object_file> [function_symbol]

Example:
    python tools/compare_function.py 71020ae240 build/FighterAreaModuleImpl.o enable_fix_jostle_area
"""

import struct
import subprocess
import sys
import re
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "original" / "main.elf"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"

# The original ELF is loaded at base 0x7100000000
ELF_BASE = 0x7100000000


def read_original_bytes(address: int, size: int) -> bytes:
    """Read bytes from the original ELF at the given virtual address."""
    # Parse ELF to find the file offset for this virtual address
    with open(ORIGINAL_ELF, 'rb') as f:
        # ELF header
        f.seek(0x20)  # e_phoff
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)  # e_phentsize
        phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]

        # Find the segment containing our address
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]
            f.read(4)  # flags
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]
            f.read(8)  # p_paddr
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            p_memsz = struct.unpack('<Q', f.read(8))[0]

            if p_type == 1 and p_vaddr <= address < p_vaddr + p_filesz:
                file_offset = p_offset + (address - p_vaddr)
                f.seek(file_offset)
                return f.read(size)

    return b''


def disassemble_object(obj_path: str, symbol_filter: str = None) -> list[tuple[int, bytes, str]]:
    """Disassemble an object file. Returns list of (offset, raw_bytes, mnemonic)."""
    result = subprocess.run(
        [OBJDUMP, "-d", obj_path],
        capture_output=True, text=True
    )

    instructions = []
    in_function = False

    for line in result.stdout.split('\n'):
        if symbol_filter and symbol_filter in line and ':' in line and not line.startswith(' '):
            in_function = True
            continue
        elif not symbol_filter:
            in_function = True

        if in_function:
            if line.strip() == '' or (not line.startswith(' ') and ':' in line and not line.startswith('Disassembly')):
                if instructions:
                    break
                continue

            # Format: "       0:	08 60 40 f9 	ldr	x8, [x0, #192]"
            match = re.match(r'\s+([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s*(.+)', line)
            if match:
                offset = int(match.group(1), 16)
                raw_hex = match.group(2).strip().replace(' ', '')
                raw_bytes = bytes.fromhex(raw_hex)
                mnemonic = match.group(3).strip()
                instructions.append((offset, raw_bytes, mnemonic))

    return instructions


def compare(address_str: str, obj_path: str, symbol_filter: str = None):
    address = int(address_str, 16)
    # Ghidra shows addresses with 0x7100000000 base, but ELF vaddr starts at 0
    if address >= ELF_BASE:
        address -= ELF_BASE

    # Get compiled instructions
    compiled = disassemble_object(obj_path, symbol_filter)
    if not compiled:
        print(f"ERROR: No function found in {obj_path}" +
              (f" matching '{symbol_filter}'" if symbol_filter else ""))
        return False

    num_bytes = sum(len(b) for _, b, _ in compiled)

    # Get original bytes
    original_bytes = read_original_bytes(address, num_bytes)
    if not original_bytes:
        print(f"ERROR: Could not read {num_bytes} bytes from original at 0x{address:x}")
        return False

    # Compare instruction by instruction
    offset = 0
    matches = 0
    total = len(compiled)

    print(f"Function at 0x{address:x} — {total} instructions, {num_bytes} bytes")
    print(f"{'Offset':<8} {'Original':<12} {'Compiled':<12} {'Match':<6} {'Instruction'}")
    print("-" * 70)

    for comp_offset, comp_bytes, mnemonic in compiled:
        orig_chunk = original_bytes[offset:offset + len(comp_bytes)]
        match = orig_chunk == comp_bytes

        orig_hex = orig_chunk.hex() if orig_chunk else "????????"
        comp_hex = comp_bytes.hex()

        status = "OK" if match else "DIFF"
        if match:
            matches += 1

        print(f"  +{offset:<5x} {orig_hex:<12} {comp_hex:<12} {status:<6} {mnemonic}")
        offset += len(comp_bytes)

    print()
    pct = matches * 100 // total if total > 0 else 0
    print(f"Result: {matches}/{total} instructions match ({pct}%)")
    if matches == total:
        print("PERFECT MATCH!")
    return matches == total


def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <address> <object_file> [symbol_filter]")
        print(f"Example: {sys.argv[0]} 71020ae240 build/FighterAreaModuleImpl.o enable_fix_jostle_area")
        sys.exit(1)

    address = sys.argv[1]
    obj_path = sys.argv[2]
    symbol_filter = sys.argv[3] if len(sys.argv) > 3 else None

    compare(address, obj_path, symbol_filter)


if __name__ == '__main__':
    main()
