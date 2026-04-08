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

# STP x29, x30 detection — matches both pre-indexed and signed-offset forms:
#   Pre-index:     stp x29, x30, [sp, #imm]!  (bits 25:23 = 011)
#   Signed offset: stp x29, x30, [sp, #imm]   (bits 25:23 = 010)
# Both have: opc=10 (64-bit), V=0, Rt2=x30, Rn=sp, Rt=x29
# Mask clears bit 23 to match both forms, and bits 21:15 (imm7)
STP_X29_X30_MASK = 0xFF407FFF
STP_X29_X30_BITS = 0xA9007BFD

# add x29, sp, #imm (includes mov x29, sp which is add x29, sp, #0)
# Mask checks sf=1, op=00, 10001, shift=00, Rn=sp(31), Rd=x29(29)
ADD_X29_SP_MASK = 0xFFC003FF
ADD_X29_SP_BITS = 0x910003FD


def is_stp_x29_x30(insn):
    """Check if instruction is stp x29, x30, [sp, #imm] (pre-index or signed offset)."""
    return (insn & STP_X29_X30_MASK) == STP_X29_X30_BITS


def is_add_x29_sp(insn):
    """Check if instruction is add x29, sp, #imm (or mov x29, sp)."""
    return (insn & ADD_X29_SP_MASK) == ADD_X29_SP_BITS


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

        # Find STP x29, x30 in first 2 instructions (may be at pos 0 or pos 1)
        stp_byte_off = None  # byte offset of STP within section
        for pos in range(min(2, sec_size // 4)):
            insn = struct.unpack_from('<I', data, sec_off + pos * 4)[0]
            if is_stp_x29_x30(insn):
                stp_byte_off = pos * 4
                break

        if stp_byte_off is None:
            continue

        # Check if add x29, sp, #imm is already right after STP
        insert_off = stp_byte_off + 4  # where the add should go
        next_insn = struct.unpack_from('<I', data, sec_off + insert_off)[0]
        if is_add_x29_sp(next_insn):
            continue  # Already in the right place

        # Find add x29, sp, #imm later in the function (before first BLR/BL)
        mov_byte_off = None
        for off in range(insert_off + 4, sec_size, 4):
            insn = struct.unpack_from('<I', data, sec_off + off)[0]
            if is_add_x29_sp(insn):
                mov_byte_off = off
                break

        if mov_byte_off is None:
            continue

        if dry_run:
            print(f"  Would fix: {sec_name} (add x29,sp at +{mov_byte_off:#x} -> +{insert_off:#x})")
            patches += 1
            continue

        # Move: remove instruction at mov_byte_off, insert at insert_off
        mov_insn_bytes = data[sec_off + mov_byte_off:sec_off + mov_byte_off + 4]

        # Shift instructions from [insert_off, mov_byte_off) down by 4 bytes
        chunk = bytes(data[sec_off + insert_off:sec_off + mov_byte_off])
        data[sec_off + insert_off + 4:sec_off + mov_byte_off + 4] = chunk

        # Place add x29, sp, #imm at insert_off
        data[sec_off + insert_off:sec_off + insert_off + 4] = mov_insn_bytes

        # Fix relocations: entries in [insert_off, mov_byte_off) need offset += 4
        if sec_idx in rela_sections:
            rela_off, rela_size = rela_sections[sec_idx]
            num_entries = rela_size // 24
            for j in range(num_entries):
                entry_off = rela_off + j * 24
                r_offset = struct.unpack_from('<Q', data, entry_off)[0]
                if insert_off <= r_offset < mov_byte_off:
                    struct.pack_into('<Q', data, entry_off, r_offset + 4)
                elif r_offset == mov_byte_off:
                    struct.pack_into('<Q', data, entry_off, insert_off)

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
