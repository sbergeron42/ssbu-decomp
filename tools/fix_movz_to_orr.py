#!/usr/bin/env python3
"""
Post-processing script to fix movz→orr divergence for NX matching.

The original SSBU binary (compiled with NX Clang) uses `orr Wd, wzr, #imm`
for bitmask-representable immediates. Upstream Clang 8.0.0 emits `movz Wd, #imm`
for the same values.

This script patches compiled ELF object files to replace movz instructions
with the equivalent orr-with-wzr encoding where the immediate is representable
as a logical immediate.

AArch64 encoding reference:
  movz Wd, #imm      → 0x52800000 | (hw << 21) | (imm16 << 5) | Rd
  movz Xd, #imm      → 0xD2800000 | (hw << 21) | (imm16 << 5) | Rd

  orr Wd, WZR, #imm  → 0x32 | N:immr:imms fields | (31 << 5) | Rd
  orr Xd, XZR, #imm  → 0xB2 | N:immr:imms fields | (31 << 5) | Rd
"""

import struct
import glob
import sys
from pathlib import Path


def decode_logical_imm(n: int, imms: int, immr: int, is_64bit: bool) -> int | None:
    """Decode an AArch64 logical immediate. Returns the immediate value or None if invalid."""
    if is_64bit:
        if n == 1:
            element_size = 64
        else:
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

    pattern = (1 << s) - 1
    if r != 0:
        pattern = ((pattern >> r) | (pattern << (element_size - r))) & ((1 << element_size) - 1)

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


def encode_logical_imm(value: int, is_64bit: bool) -> int | None:
    """Encode a value as an AArch64 logical immediate.
    Returns the encoded N:immr:imms fields (bits 22:10) or None if not encodable."""
    reg_size = 64 if is_64bit else 32

    if value == 0 or (not is_64bit and value == 0xFFFFFFFF) or (is_64bit and value == 0xFFFFFFFFFFFFFFFF):
        return None  # all-zeros and all-ones not encodable

    # Try each element size
    for element_size in [2, 4, 8, 16, 32, 64]:
        if element_size > reg_size:
            break

        # Check that the value is a repeating pattern of this element size
        mask = (1 << element_size) - 1
        element = value & mask
        replicated = 0
        for i in range(reg_size // element_size):
            replicated |= element << (i * element_size)

        if not is_64bit:
            replicated &= 0xFFFFFFFF

        if replicated != value:
            continue

        # Now we need to find rotation and number of set bits
        # The element must be a rotated run of ones
        # Try all rotations
        for rotation in range(element_size):
            # Rotate element right by 'rotation'
            rotated = ((element >> rotation) | (element << (element_size - rotation))) & mask

            # Check if rotated is a contiguous run of ones starting from bit 0
            if rotated == 0:
                continue
            ones = 0
            tmp = rotated
            while tmp & 1:
                ones += 1
                tmp >>= 1
            if tmp != 0:
                continue  # not a contiguous run

            # Found valid encoding
            # immr is the right-rotation applied TO the pattern to GET the value
            # We found: ROR(value, rotation) = pattern
            # So: ROR(pattern, element_size - rotation) = value
            immr = (element_size - rotation) % element_size
            if element_size == 64:
                n = 1
                imms = (ones - 1) & 0x3F
            else:
                # imms has a pattern that encodes element_size:
                # element_size=2:  imms = 0b111100 | (ones-1)
                # element_size=4:  imms = 0b111000 | (ones-1)
                # element_size=8:  imms = 0b110000 | (ones-1)
                # element_size=16: imms = 0b100000 | (ones-1)
                # element_size=32: imms = 0b000000 | (ones-1) (N=0)
                n = 0
                size_bits = {
                    2:  0b111100,
                    4:  0b111000,
                    8:  0b110000,
                    16: 0b100000,
                    32: 0b000000,
                }
                imms = size_bits[element_size] | (ones - 1)

            return (n << 12) | (immr << 6) | imms

    return None


def encode_orr_imm(rd: int, value: int, is_64bit: bool) -> int | None:
    """Encode an ORR Rd, WZR/XZR, #imm instruction. Returns encoded instruction or None."""
    fields = encode_logical_imm(value, is_64bit)
    if fields is None:
        return None

    n = (fields >> 12) & 1
    immr = (fields >> 6) & 0x3F
    imms = fields & 0x3F

    if is_64bit:
        insn = 0xB2000000
    else:
        insn = 0x32000000
        if n != 0:
            return None  # N must be 0 for 32-bit

    insn |= (n << 22) | (immr << 16) | (imms << 10) | (31 << 5) | rd
    return insn


def is_movk(insn: int) -> tuple[bool, int]:
    """Check if instruction is MOVK. Returns (is_movk, rd)."""
    # 32-bit MOVK: 0x72800000 mask 0xFF800000
    # 64-bit MOVK: 0xF2800000 mask 0xFF800000
    if (insn & 0xFF800000) == 0x72800000 or (insn & 0xFF800000) == 0xF2800000:
        return True, insn & 0x1F
    return False, -1


def is_orr_wzr(insn: int) -> tuple[bool, bool, int, int]:
    """Check if instruction is ORR Rd, WZR/XZR, #imm. Returns (match, is_64bit, rd, value)."""
    opc_mask = 0x7F800000
    opc_32 = 0x32000000
    opc_64 = 0xB2000000

    if (insn & opc_mask) == opc_32:
        is_64bit = False
    elif (insn & opc_mask) == opc_64:
        is_64bit = True
    else:
        return False, False, -1, -1

    rn = (insn >> 5) & 0x1F
    if rn != 31:
        return False, False, -1, -1

    rd = insn & 0x1F
    n = (insn >> 22) & 1
    immr = (insn >> 16) & 0x3F
    imms = (insn >> 10) & 0x3F

    # Import decode logic inline
    value = decode_logical_imm(n, imms, immr, is_64bit)
    if value is None:
        return False, False, -1, -1

    return True, is_64bit, rd, value


def patch_insn(data: bytearray, offset: int, sec_end: int) -> int:
    """Patch instruction at offset. Returns number of patches applied (0 or 1)."""
    if offset + 4 > len(data):
        return 0

    insn = struct.unpack_from('<I', data, offset)[0]

    # Check next instruction for movk context
    next_insn = None
    if offset + 8 <= sec_end:
        next_insn = struct.unpack_from('<I', data, offset + 4)[0]

    # Case 1: MOVZ not followed by MOVK → convert to ORR
    is_movz_32 = (insn & 0xFF800000) == 0x52800000
    is_movz_64 = (insn & 0xFF800000) == 0xD2800000
    if is_movz_32 or is_movz_64:
        is_64bit = is_movz_64
        rd = insn & 0x1F
        hw = (insn >> 21) & 0x3
        imm16 = (insn >> 5) & 0xFFFF
        value = imm16 << (hw * 16)

        # Skip if any of the next few instructions is MOVK targeting same register
        # (the compiler may interleave other-register ops between movz and movk)
        for lookahead in range(1, 5):
            peek_off = offset + lookahead * 4
            if peek_off + 4 > sec_end:
                break
            peek_insn = struct.unpack_from('<I', data, peek_off)[0]
            peek_is_movk, movk_rd = is_movk(peek_insn)
            if peek_is_movk and movk_rd == rd:
                return 0

        new_insn = encode_orr_imm(rd, value, is_64bit)
        if new_insn is not None:
            struct.pack_into('<I', data, offset, new_insn)
            return 1

    # Case 2: ORR Rd, WZR, #imm followed by MOVK Rd → convert to MOVZ
    opc_mask = 0x7F800000
    is_orr_32 = (insn & opc_mask) == 0x32000000
    is_orr_64 = (insn & opc_mask) == 0xB2000000
    if is_orr_32 or is_orr_64:
        is_64bit = is_orr_64
        rn = (insn >> 5) & 0x1F
        if rn == 31:  # source is WZR/XZR
            rd = insn & 0x1F
            n = (insn >> 22) & 1
            immr = (insn >> 16) & 0x3F
            imms = (insn >> 10) & 0x3F

            if next_insn is not None:
                next_is_movk, movk_rd = is_movk(next_insn)
                if next_is_movk and movk_rd == rd:
                    # Decode the logical immediate value
                    value = decode_logical_imm(n, imms, immr, is_64bit)
                    if value is not None:
                        # Check value fits in movz with hw=0
                        if 0 <= value <= 0xFFFF:
                            sf = 1 if is_64bit else 0
                            new_insn = (sf << 31) | 0x52800000 | (value << 5) | rd
                            struct.pack_into('<I', data, offset, new_insn)
                            return 1

    return 0


def process_elf(filepath: str, dry_run: bool = False) -> int:
    """Process an ELF file and patch movz→orr instructions in .text sections."""
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
        sec_end = sh_offset + sh_size
        for off in range(sh_offset, sec_end, 4):
            count = patch_insn(data, off, sec_end)
            if count > 0:
                patches += count
                if dry_run:
                    insn_addr = off - sh_offset
                    print(f"  Would patch: {section_name}+0x{insn_addr:x}")

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(description='Patch movz to orr-with-wzr in AArch64 ELF objects')
    parser.add_argument('files', nargs='+', help='ELF object files to patch')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be patched without modifying')
    args = parser.parse_args()
    # Expand globs for Windows cmd.exe compatibility
    import glob as _glob
    expanded = []
    for pattern in args.files:
        matched = _glob.glob(pattern)
        expanded.extend(matched if matched else [pattern])
    args.files = expanded

    total = 0
    for f in args.files:
        count = process_elf(f, dry_run=args.dry_run)
        if count > 0:
            action = "Would patch" if args.dry_run else "Patched"
            print(f"{action} {count} instruction(s) in {f}")
        total += count

    if total == 0:
        print("No movz instructions found to patch.")


if __name__ == '__main__':
    main()
