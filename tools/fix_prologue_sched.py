#!/usr/bin/env python3
"""
Post-processing script to fix the NX Clang prologue scheduling divergence.

Upstream Clang 8.0.0 schedules loads BEFORE `mov x29, sp` in non-leaf function
prologues, but the NX Clang fork (used for the original SSBU build) keeps
`mov x29, sp` immediately after `stp x29, x30, [sp, #imm]!`.

Upstream Clang output:
    a9bf7bfd  stp x29, x30, [sp, #-16]!
    f9401c00  ldr x0, [x0, #56]          <- loads scheduled before fp setup
    f9400008  ldr x8, [x0]
    f9403108  ldr x8, [x8, #96]
    910003fd  mov x29, sp                 <- fp setup delayed
    d63f0100  blr x8

Desired (original binary) output:
    a9bf7bfd  stp x29, x30, [sp, #-16]!
    910003fd  mov x29, sp                 <- fp setup right after stp
    f9401c00  ldr x0, [x0, #56]
    f9400008  ldr x8, [x0]
    f9403108  ldr x8, [x8, #96]
    d63f0100  blr x8

AArch64 encoding reference:
    stp x29, x30, [sp, #imm]!  (pre-indexed)
        Fixed bits: Rt=x29 (0x1d), Rt2=x30 (0x1e), Rn=sp (0x1f)
        Mask: (insn & 0x7FC07FFF) == 0x29807BFD
        Common forms: 0xa9bf7bfd (#-16), 0xa9be7bfd (#-32), 0xa9bd7bfd (#-48)

    mov x29, sp  (alias for add x29, sp, #0)
        Encoding: 0x910003FD (always this exact value)
"""

import argparse
import glob
import struct
import sys
from pathlib import Path

# mov x29, sp  =  add x29, sp, #0
MOV_X29_SP = 0x910003FD

# add x29, sp, #imm  (any immediate, including mov x29, sp when imm=0)
# Mask out imm12 (bits 21:10) to match any immediate:
ADD_X29_SP_MASK  = 0xFFC003FF
ADD_X29_SP_MATCH = 0x910003FD

# stp x29, x30, [sp, #imm]!  (pre-indexed, signed offset)
# Encoding: 1 01 0 1001 10 imm7 11110 11111 11101
#   opc=10 (64-bit), V=0, L=0 (store), Rt2=30(0x1e), Rn=31(sp), Rt=29(0x1d)
#   bits [31]=1, [30]=0, [29:27]=101, [26]=0, [25:23]=011, [22]=0 (store)
#   Rt2 [14:10]=11110, Rn [9:5]=11111, Rt [4:0]=11101
# Mask out the imm7 field (bits 21:15) and bit 23 (pre-indexed vs offset):
STP_MASK  = 0x7F407FFF
STP_MATCH = 0x29007BFD

# Maximum number of instructions between stp and mov x29, sp to consider.
# If the gap is larger than this, it's not a simple prologue reorder.
MAX_GAP = 8


def is_stp_x29_x30_preindex(insn: int) -> bool:
    """Check if instruction is `stp x29, x30, [sp, #imm]!` (pre-indexed store pair)."""
    return (insn & STP_MASK) == STP_MATCH


def decode_stp_imm(insn: int) -> int:
    """Extract the signed immediate offset from stp (pre-indexed). Returns byte offset."""
    imm7 = (insn >> 15) & 0x7F
    # Sign-extend 7-bit value
    if imm7 & 0x40:
        imm7 -= 0x80
    # Scale by 8 for 64-bit stp
    return imm7 * 8


def read_u32_le(data: bytearray, offset: int) -> int:
    """Read a little-endian 32-bit word."""
    return struct.unpack_from('<I', data, offset)[0]


def write_u32_le(data: bytearray, offset: int, value: int) -> None:
    """Write a little-endian 32-bit word."""
    struct.pack_into('<I', data, offset, value)


def find_text_sections(data: bytearray) -> list[tuple[str, int, int]]:
    """Parse ELF headers and return a list of (name, file_offset, size) for executable sections."""
    if data[:4] != b'\x7fELF':
        return []

    ei_class = data[4]
    ei_data = data[5]

    if ei_class != 2 or ei_data != 1:
        # Not a 64-bit little-endian ELF
        return []

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    if e_shnum == 0 or e_shstrndx >= e_shnum:
        return []

    # Section header string table offset
    shstrtab_hdr = e_shoff + e_shstrndx * e_shentsize
    shstrtab_off = struct.unpack_from('<Q', data, shstrtab_hdr + 0x18)[0]

    sections = []
    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_flags = struct.unpack_from('<Q', data, sh_off + 0x08)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        # SHF_EXECINSTR = 0x4
        if not (sh_flags & 0x4):
            continue

        # Read section name from string table
        name_start = shstrtab_off + sh_name_idx
        name_end = data.index(0, name_start)
        name = data[name_start:name_end].decode('ascii', errors='replace')

        if not name.startswith('.text'):
            continue

        sections.append((name, sh_offset, sh_size))

    return sections


def find_reloc_info(data: bytearray,
                    text_sections: list[tuple[str, int, int]]
                    ) -> tuple[set[int], list[tuple[int, int, int, int]]]:
    """Find relocation info for .text sections.

    Returns:
      reloc_offsets: set of file offsets within .text that have RELA entries
      rela_sections: list of (rela_file_off, entsize, nentries, text_sec_file_off)
                     for RELA sections targeting our .text sections — used to
                     update r_offset values when instructions are rotated.
    """
    if data[:4] != b'\x7fELF':
        return set(), []

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]

    # Map section index -> file_offset for our executable text sections
    text_by_index: dict[int, int] = {}
    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_flags = struct.unpack_from('<Q', data, sh_off + 0x08)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]
        if (sh_flags & 0x4):
            for name, t_off, t_size in text_sections:
                if t_off == sh_offset and t_size == sh_size:
                    text_by_index[i] = t_off

    reloc_offsets: set[int] = set()
    rela_sections: list[tuple[int, int, int, int]] = []

    SHT_RELA = 4
    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_type = struct.unpack_from('<I', data, sh_off + 0x04)[0]
        if sh_type != SHT_RELA:
            continue

        sh_info = struct.unpack_from('<I', data, sh_off + 0x2C)[0]
        if sh_info not in text_by_index:
            continue

        text_file_off = text_by_index[sh_info]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]
        sh_entsize = struct.unpack_from('<Q', data, sh_off + 0x38)[0]
        if sh_entsize == 0:
            sh_entsize = 24

        num_entries = sh_size // sh_entsize
        rela_sections.append((sh_offset, sh_entsize, num_entries, text_file_off))

        for j in range(num_entries):
            rela_off = sh_offset + j * sh_entsize
            r_offset = struct.unpack_from('<Q', data, rela_off)[0]
            file_off = text_file_off + (r_offset & ~3)
            reloc_offsets.add(file_off)

    return reloc_offsets, rela_sections


# Keep old name as alias for callers that pass only reloc_offsets
def find_reloc_offsets(data: bytearray, text_sections: list[tuple[str, int, int]]) -> set[int]:
    return find_reloc_info(data, text_sections)[0]


def shift_rela_entries(data: bytearray,
                       rela_sections: list[tuple[int, int, int, int]],
                       text_sec_file_off: int,
                       gap_start_file_off: int,
                       gap_end_file_off: int) -> None:
    """Increment r_offset by 4 for any RELA entry in [gap_start, gap_end] (file offsets).

    Called after rotating gap instructions forward by one slot so that the
    linker's recorded fixup positions stay correct.
    """
    for (rela_off, entsize, nentries, t_off) in rela_sections:
        if t_off != text_sec_file_off:
            continue
        sec_lo = gap_start_file_off - t_off   # section-relative
        sec_hi = gap_end_file_off - t_off
        for j in range(nentries):
            entry = rela_off + j * entsize
            r_offset = struct.unpack_from('<Q', data, entry)[0]
            if sec_lo <= (r_offset & ~3) <= sec_hi:
                struct.pack_into('<Q', data, entry, r_offset + 4)


def patch_prologue_sched(data: bytearray, sec_name: str, sec_offset: int,
                         sec_size: int, reloc_offsets: set[int],
                         rela_sections: list[tuple[int, int, int, int]] | None = None,
                         verbose: bool = False) -> list[str]:
    """Scan a .text section for the prologue scheduling pattern and patch it.

    Returns a list of human-readable descriptions of each patch applied.
    """
    patches = []
    end = sec_offset + sec_size
    off = sec_offset

    while off < end - 4:
        insn = read_u32_le(data, off)

        if not is_stp_x29_x30_preindex(insn):
            off += 4
            continue

        stp_off = off
        imm = decode_stp_imm(insn)

        # Look ahead for add x29, sp, #imm (includes mov x29, sp) within MAX_GAP instructions
        mov_off = None
        gap_count = 0
        for k in range(1, MAX_GAP + 2):  # +2: check up to MAX_GAP+1 to detect gap size
            check_off = stp_off + k * 4
            if check_off >= end:
                break
            candidate = read_u32_le(data, check_off)
            if (candidate & ADD_X29_SP_MASK) == ADD_X29_SP_MATCH:
                gap_count = k - 1  # number of instructions between stp and mov/add
                if 1 <= gap_count <= MAX_GAP:
                    mov_off = check_off
                break

        if mov_off is None:
            off += 4
            continue

        # Verify: none of the instructions in the gap have relocations.
        # If any do, the linker has recorded a fixup at that position, and
        # moving instructions would break it.
        gap_has_reloc = False
        for k in range(1, gap_count + 1):
            if (stp_off + k * 4) in reloc_offsets:
                gap_has_reloc = True
                break

        if gap_has_reloc and not rela_sections:
            if verbose:
                sec_rel = stp_off - sec_offset
                print(f"  SKIP {sec_name}+0x{sec_rel:x}: gap has relocations and no rela_sections provided")
            off += 4
            continue

        # Also check that the mov x29, sp itself doesn't have a relocation
        # (it shouldn't, since it has no immediate operand that needs fixing up,
        # but be safe).
        if mov_off in reloc_offsets:
            off += 4
            continue

        # Perform the patch: move mov x29, sp to right after stp x29, x30.
        # Shift the gap instructions down by one slot.
        #
        # Before: [stp] [A] [B] [C] [mov]
        # After:  [stp] [mov] [A] [B] [C]
        gap_insns = []
        for k in range(1, gap_count + 1):
            gap_insns.append(read_u32_le(data, stp_off + k * 4))

        # Write add x29, sp, #imm (or mov x29, sp) right after stp
        mov_insn = read_u32_le(data, mov_off)
        write_u32_le(data, stp_off + 4, mov_insn)

        # Write the original gap instructions shifted down by one
        for k, gi in enumerate(gap_insns):
            write_u32_le(data, stp_off + (k + 2) * 4, gi)

        # If gap instructions had relocations, update RELA r_offset values so
        # the linker still finds the fixup sites at their new positions.
        if gap_has_reloc and rela_sections:
            gap_start = stp_off + 4
            gap_end   = stp_off + gap_count * 4
            shift_rela_entries(data, rela_sections, sec_offset,
                               gap_start, gap_end)

        sec_rel = stp_off - sec_offset
        reloc_note = " (with RELA update)" if gap_has_reloc else ""
        desc = (f"{sec_name}+0x{sec_rel:x}: moved mov x29, sp over "
                f"{gap_count} instruction(s) (stp offset {imm}){reloc_note}")
        patches.append(desc)

        # Advance past the patched region
        off = mov_off + 4
        continue

    return patches


def process_elf(filepath: str, dry_run: bool = False, verbose: bool = False) -> int:
    """Process an ELF object file and patch prologue scheduling. Returns patch count."""
    path = Path(filepath)

    if not path.exists():
        print(f"Error: {filepath} not found")
        return 0

    data = bytearray(path.read_bytes())

    if data[:4] != b'\x7fELF':
        print(f"Error: {filepath} is not an ELF file")
        return 0

    if data[4] != 2 or data[5] != 1:
        print(f"Error: {filepath} is not a 64-bit little-endian ELF")
        return 0

    text_sections = find_text_sections(data)
    if not text_sections:
        if verbose:
            print(f"  {filepath}: no .text sections found")
        return 0

    reloc_offsets, rela_sections = find_reloc_info(data, text_sections)

    total_patches = 0
    all_descs: list[str] = []

    for sec_name, sec_offset, sec_size in text_sections:
        descs = patch_prologue_sched(data, sec_name, sec_offset, sec_size,
                                     reloc_offsets, rela_sections=rela_sections,
                                     verbose=verbose)
        all_descs.extend(descs)
        total_patches += len(descs)

    if total_patches > 0:
        if dry_run:
            for d in all_descs:
                print(f"  [dry-run] {d}")
        else:
            path.write_bytes(data)
            if verbose:
                for d in all_descs:
                    print(f"  {d}")

    return total_patches


def main():
    parser = argparse.ArgumentParser(
        description='Patch AArch64 ELF objects to fix NX Clang prologue scheduling divergence.\n'
                    'Moves `mov x29, sp` to immediately after `stp x29, x30, [sp, #imm]!`\n'
                    'in non-leaf function prologues.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument('files', nargs='+', help='ELF object files to patch (supports shell glob)')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be patched without modifying files')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Print details for each patch site')
    args = parser.parse_args()
    # Expand globs for Windows cmd.exe compatibility
    import glob as _glob
    expanded = []
    for pattern in args.files:
        matched = _glob.glob(pattern)
        expanded.extend(matched if matched else [pattern])
    args.files = expanded

    total = 0
    files_patched = 0

    for filepath in args.files:
        count = process_elf(filepath, dry_run=args.dry_run, verbose=args.verbose)
        if count > 0:
            action = "Would patch" if args.dry_run else "Patched"
            print(f"{action} {count} prologue(s) in {filepath}")
            files_patched += 1
        total += count

    # Summary
    print()
    if total == 0:
        print("No prologue scheduling divergences found.")
    else:
        action = "would be patched" if args.dry_run else "patched"
        print(f"Summary: {total} prologue(s) {action} across {files_patched} file(s).")


if __name__ == '__main__':
    main()
