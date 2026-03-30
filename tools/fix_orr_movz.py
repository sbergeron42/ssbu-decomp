#!/usr/bin/env python3
"""
Post-processing script to fix the NX Clang orr→movz divergence.

Upstream Clang uses `orr Wd, wzr, #imm` (encoding 0x32xxxxxx) for loading
bitmask-representable immediates. Nintendo's NX Clang fork uses `movz Wd, #imm`
(encoding 0x52xxxxxx) for the same values.

This script patches compiled ELF object files to replace orr-with-wzr instructions
with the equivalent movz encoding where possible.

AArch64 encoding reference:
  orr Wd, WZR, #imm  → 0x32 | immr:imms:N fields
  movz Wd, #imm      → 0x52800000 | (imm16 << 5) | Rd

  orr Xd, XZR, #imm  → 0xB2 | immr:imms:N fields
  movz Xd, #imm      → 0xD2800000 | (imm16 << 5) | Rd

Only patches cases where:
  - Source register is WZR/XZR (bits 5-9 = 0b11111 = 31)
  - The logical immediate value fits in a 16-bit movz (no shift needed)
"""

import struct
import sys
from pathlib import Path


def decode_logical_imm(n: int, imms: int, immr: int, is_64bit: bool) -> int | None:
    """Decode an AArch64 logical immediate. Returns the immediate value or None if invalid."""
    if is_64bit:
        if n == 1:
            element_size = 64
        else:
            # Determine element size from top bits of imms
            sizes = [2, 4, 8, 16, 32]
            element_size = None
            for s in sizes:
                if (imms & ~(s - 1)) == (~s & 0x3f):
                    element_size = s
                    break
            if element_size is None:
                return None
    else:
        if n != 0:
            return None
        sizes = [2, 4, 8, 16, 32]
        element_size = None
        for s in sizes:
            mask = ~(s - 1) & 0x3f
            if (imms & mask) == (mask & ~(s - 1)):
                element_size = s
                break
        if element_size is None:
            element_size = 32

    s = (imms & (element_size - 1)) + 1
    r = immr & (element_size - 1)

    # Build the element pattern
    pattern = (1 << s) - 1
    if r != 0:
        pattern = ((pattern >> r) | (pattern << (element_size - r))) & ((1 << element_size) - 1)

    # Replicate the pattern
    if is_64bit:
        result = 0
        for i in range(64 // element_size):
            result |= pattern << (i * element_size)
        return result
    else:
        result = 0
        for i in range(32 // element_size):
            result |= pattern << (i * element_size)
        return result & 0xFFFFFFFF


def can_movz(value: int, is_64bit: bool) -> tuple[int, int] | None:
    """Check if value can be encoded as movz (16-bit immediate with optional shift).
    Returns (imm16, hw_shift) or None."""
    if is_64bit:
        for hw in range(4):
            shifted = value >> (hw * 16)
            if shifted <= 0xFFFF and (shifted << (hw * 16)) == value:
                return (shifted, hw)
    else:
        for hw in range(2):
            shifted = value >> (hw * 16)
            if shifted <= 0xFFFF and (shifted << (hw * 16)) == (value & 0xFFFFFFFF):
                return (shifted, hw)
    return None


def encode_movz(rd: int, imm16: int, hw: int, is_64bit: bool) -> int:
    """Encode a movz instruction."""
    sf = 1 if is_64bit else 0
    return (sf << 31) | (0x52800000 & 0x7FFFFFFF) | (hw << 21) | (imm16 << 5) | rd


def patch_orr_to_movz(data: bytearray, offset: int) -> bool:
    """Try to patch an orr-with-wzr instruction at offset to movz. Returns True if patched."""
    if offset + 4 > len(data):
        return False

    insn = struct.unpack_from('<I', data, offset)[0]

    # Check if this is ORR (immediate) with Rn=WZR/XZR
    # 32-bit: 0x32 prefix (bits 31=0, 30:29=01, 28:23=100100)
    # 64-bit: 0xB2 prefix (bits 31=1, 30:29=01, 28:23=100100)
    opc_mask = 0x7F800000
    opc_32 = 0x32000000
    opc_64 = 0xB2000000

    if (insn & opc_mask) == opc_32:
        is_64bit = False
    elif (insn & opc_mask) == opc_64:
        is_64bit = True
    else:
        return False

    # Check Rn field (bits 9:5) is WZR/XZR (31)
    rn = (insn >> 5) & 0x1F
    if rn != 31:
        return False

    # Decode the logical immediate
    rd = insn & 0x1F
    n = (insn >> 22) & 1
    immr = (insn >> 16) & 0x3F
    imms = (insn >> 10) & 0x3F

    value = decode_logical_imm(n, imms, immr, is_64bit)
    if value is None:
        return False

    # Check if this value can be encoded as movz
    result = can_movz(value, is_64bit)
    if result is None:
        return False

    imm16, hw = result

    # Encode and patch
    new_insn = encode_movz(rd, imm16, hw, is_64bit)
    struct.pack_into('<I', data, offset, new_insn)
    return True


def process_elf(filepath: str, dry_run: bool = False) -> int:
    """Process an ELF file and patch orr→movz instructions in .text sections."""
    path = Path(filepath)
    data = bytearray(path.read_bytes())

    # Simple ELF parsing - find .text sections
    if data[:4] != b'\x7fELF':
        print(f"Error: {filepath} is not an ELF file")
        return 0

    is_64bit_elf = data[4] == 2
    is_le = data[5] == 1

    if not is_64bit_elf or not is_le:
        print(f"Error: expected 64-bit little-endian ELF")
        return 0

    # Parse ELF header
    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    # Get section header string table
    shstrtab_off = struct.unpack_from('<Q', data, e_shoff + e_shstrndx * e_shentsize + 0x18)[0]

    patches = 0
    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_type = struct.unpack_from('<I', data, sh_off + 4)[0]
        sh_flags = struct.unpack_from('<Q', data, sh_off + 8)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        # Get section name
        name_end = data.index(0, shstrtab_off + sh_name_idx)
        section_name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        # Only process executable sections (SHF_EXECINSTR = 0x4)
        if not (sh_flags & 0x4):
            continue

        if not section_name.startswith('.text'):
            continue

        # Scan every 4-byte aligned position in this section
        for off in range(sh_offset, sh_offset + sh_size, 4):
            if patch_orr_to_movz(data, off):
                patches += 1
                if dry_run:
                    insn_addr = off - sh_offset
                    print(f"  Would patch: {section_name}+0x{insn_addr:x}")

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(description='Patch orr-with-wzr to movz in AArch64 ELF objects')
    parser.add_argument('files', nargs='+', help='ELF object files to patch')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be patched without modifying')
    args = parser.parse_args()

    total = 0
    for f in args.files:
        count = process_elf(f, dry_run=args.dry_run)
        if count > 0:
            action = "Would patch" if args.dry_run else "Patched"
            print(f"{action} {count} instruction(s) in {f}")
        total += count

    if total == 0:
        print("No orr-with-wzr instructions found to patch.")


if __name__ == '__main__':
    main()
