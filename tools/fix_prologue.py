#!/usr/bin/env python3
"""
Post-processing script to fix NX Clang prologue frame-pointer scheduling.

The NX Clang fork places `mov x29, sp` immediately after `stp x29, x30, [sp, #-N]!`
in the prologue. Upstream Clang 8.0.0 may schedule it later (after loads/computation)
as an optimization.

This script scans .text sections in ELF .o files. For each function that starts with
`stp x29, x30, [sp, #-N]!` and has `mov x29, sp` somewhere later, it moves that
instruction to right after the stp, shifting intermediate instructions down.

Relocation offsets are adjusted accordingly.
"""

import struct
import sys
from pathlib import Path

# stp x29, x30, [sp, #-0x10]! = 0xa9bf7bfd
# stp x29, x30, [sp, #-0x20]! = 0xa9be7bfd
# stp x29, x30, [sp, #-0x30]! = 0xa9bd7bfd
# etc. Mask for stp x29, x30, [sp, #imm]! pre-index:
#   bits[31:22] = 1010100110 (STP, pre-index, 64-bit)
#   Rt2 = x30 (bits 14:10 = 11110)
#   Rn = sp  (bits 9:5 = 11111)
#   Rt  = x29 (bits 4:0 = 11101)
STP_X29_X30_MASK = 0xFFC07FFF
STP_X29_X30_BITS = 0xA9800000 | (30 << 10) | (31 << 5) | 29  # a9xx7bfd

# mov x29, sp = 0x910003fd
MOV_X29_SP = 0x910003fd

# Also handle: add x29, sp, #imm (for functions with larger stack frames)
# add x29, sp, #imm = 0x910003fd when imm=0, or 0x91XXXX1D with Rn=sp(31)
# We only match the exact mov x29, sp (imm=0) case
ADD_X29_SP_MASK = 0xFFC003FF
ADD_X29_SP_BITS = 0x910003FD  # Only exact mov x29, sp


def is_stp_x29_x30_preindex(insn):
    """Check if instruction is stp x29, x30, [sp, #imm]! (pre-index)."""
    return (insn & STP_X29_X30_MASK) == STP_X29_X30_BITS


def process_elf(filepath, dry_run=False):
    """Process an ELF .o file and fix prologue scheduling."""
    path = Path(filepath)
    data = bytearray(path.read_bytes())

    if data[:4] != b'\x7fELF':
        return 0
    if data[4] != 2 or data[5] != 1:  # 64-bit LE
        return 0

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    shstrtab_off = struct.unpack_from('<Q', data,
                                       e_shoff + e_shstrndx * e_shentsize + 0x18)[0]

    # First pass: find .text sections and their rela sections
    text_sections = {}  # section_index -> (name, sh_offset, sh_size)
    rela_sections = {}  # target_section_index -> (rela_sh_offset, rela_sh_size)

    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_type = struct.unpack_from('<I', data, sh_off + 4)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        name_end = data.index(0, shstrtab_off + sh_name_idx)
        name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        if sh_type == 1 and name.startswith('.text.'):  # SHT_PROGBITS
            text_sections[i] = (name, sh_offset, sh_size)
        elif sh_type == 4:  # SHT_RELA
            sh_info = struct.unpack_from('<I', data, sh_off + 0x2C)[0]
            rela_sections[sh_info] = (sh_offset, sh_size)

    patches = 0
    for sec_idx, (sec_name, sec_off, sec_size) in text_sections.items():
        if sec_size < 12:  # Need at least 3 instructions
            continue

        first = struct.unpack_from('<I', data, sec_off)[0]
        if not is_stp_x29_x30_preindex(first):
            continue

        second = struct.unpack_from('<I', data, sec_off + 4)[0]
        if second == MOV_X29_SP:
            continue  # Already in the right place

        # Find mov x29, sp later in the function
        mov_pos = None
        for off in range(8, sec_size, 4):
            insn = struct.unpack_from('<I', data, sec_off + off)[0]
            if insn == MOV_X29_SP:
                mov_pos = off
                break

        if mov_pos is None:
            continue

        if dry_run:
            print(f"  Would fix: {sec_name} (mov x29,sp at +{mov_pos:#x} -> +0x4)")
            patches += 1
            continue

        # Move: remove instruction at mov_pos, insert at offset 4
        # Save the mov instruction
        mov_insn_bytes = data[sec_off + mov_pos:sec_off + mov_pos + 4]

        # Shift instructions from [4, mov_pos) down by 4 bytes
        # (move them to [8, mov_pos+4))
        chunk = bytes(data[sec_off + 4:sec_off + mov_pos])
        data[sec_off + 8:sec_off + mov_pos + 4] = chunk

        # Place mov x29, sp at offset 4
        data[sec_off + 4:sec_off + 8] = mov_insn_bytes

        # Fix relocations: entries pointing into [4, mov_pos) need offset += 4
        # Entry at mov_pos needs offset = 4 (but mov x29,sp has no relocs)
        if sec_idx in rela_sections:
            rela_off, rela_size = rela_sections[sec_idx]
            num_entries = rela_size // 24
            for j in range(num_entries):
                entry_off = rela_off + j * 24
                r_offset = struct.unpack_from('<Q', data, entry_off)[0]
                if 4 <= r_offset < mov_pos:
                    struct.pack_into('<Q', data, entry_off, r_offset + 4)
                elif r_offset == mov_pos:
                    # mov x29, sp shouldn't have relocations, but handle it
                    struct.pack_into('<Q', data, entry_off, 4)

        patches += 1

    # Note: epilogue scheduling (mov w0 vs ldp order) varies per function
    # in the original binary, so we do NOT fix it globally here.

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(
        description='Fix NX Clang prologue frame-pointer scheduling in AArch64 .o files')
    parser.add_argument('files', nargs='+', help='ELF object files to patch')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be patched without modifying')
    args = parser.parse_args()

    total = 0
    for f in args.files:
        count = process_elf(f, dry_run=args.dry_run)
        if count > 0:
            action = "Would fix" if args.dry_run else "Fixed"
            print(f"{action} {count} prologue(s) in {f}")
        total += count

    if total == 0:
        print("No prologue scheduling issues found.")


if __name__ == '__main__':
    main()
