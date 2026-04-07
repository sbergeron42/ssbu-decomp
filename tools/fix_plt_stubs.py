#!/usr/bin/env python3
"""
Post-processing script to fix PLT stub calling convention for NX matching.

The original SSBU binary uses the NX PLT stub pattern to call through GOT entries:
    adrp x16, <symbol>
    ldr  x17, [x16, :lo12:<symbol>]
    add  x16, x16, :lo12:<symbol>
    br   x17

Upstream Clang 8.0.0 with -fPIC emits GOT-relative indirect calls:
    adrp xN, :got:<symbol>
    ldr  xN, [xN, :got_lo12:<symbol>]
    ldr  xM, [xN]
    br   xM

This script patches compiled ELF .o files to transform the GOT-relative pattern
into the NX PLT pattern by rewriting both instructions and relocations.

Relocation changes:
    R_AARCH64_ADR_GOT_PAGE (311)       -> R_AARCH64_ADR_PREL_PG_HI21 (275)
    R_AARCH64_LD64_GOT_LO12_NC (312)  -> R_AARCH64_LDST64_ABS_LO12_NC (286)
    (new)                              -> R_AARCH64_ADD_ABS_LO12_NC (277)
"""

import struct
import glob
import sys
from pathlib import Path

# AArch64 relocation types
R_AARCH64_ADR_PREL_PG_HI21 = 275
R_AARCH64_ADD_ABS_LO12_NC = 277
R_AARCH64_LDST64_ABS_LO12_NC = 286
R_AARCH64_ADR_GOT_PAGE = 311
R_AARCH64_LD64_GOT_LO12_NC = 312

# Fixed instruction encodings (immediates are 0; relocations fill them)
ADRP_X16   = 0x90000010  # adrp x16, #0
LDR_X17_X16 = 0xF9400211  # ldr x17, [x16]
ADD_X16_X16 = 0x91000210  # add x16, x16, #0
BR_X17     = 0xD61F0220  # br x17


def is_adrp(insn):
    """Check if instruction is ADRP. Returns (True, Rd) or (False, -1)."""
    if (insn & 0x9F000000) == 0x90000000:
        return True, insn & 0x1F
    return False, -1


def is_ldr_64_uoff(insn):
    """Check if instruction is LDR Xt, [Xn, #uimm]. Returns (True, Rt, Rn) or (False, -1, -1)."""
    # LDR (64-bit, unsigned offset): 0xF9400000 mask 0xFFC00000
    if (insn & 0xFFC00000) == 0xF9400000:
        rt = insn & 0x1F
        rn = (insn >> 5) & 0x1F
        return True, rt, rn
    return False, -1, -1


def is_br(insn):
    """Check if instruction is BR Xn. Returns (True, Rn) or (False, -1)."""
    if (insn & 0xFFFFFC1F) == 0xD61F0000:
        return True, (insn >> 5) & 0x1F
    return False, -1


def parse_elf_header(data):
    """Parse ELF64 header. Returns dict of header fields."""
    if data[:4] != b'\x7fELF' or data[4] != 2 or data[5] != 1:
        return None
    return {
        'e_shoff': struct.unpack_from('<Q', data, 0x28)[0],
        'e_shentsize': struct.unpack_from('<H', data, 0x3A)[0],
        'e_shnum': struct.unpack_from('<H', data, 0x3C)[0],
        'e_shstrndx': struct.unpack_from('<H', data, 0x3E)[0],
    }


def parse_sections(data, hdr):
    """Parse all section headers. Returns list of section info dicts."""
    shstrtab_hdr_off = hdr['e_shoff'] + hdr['e_shstrndx'] * hdr['e_shentsize']
    shstrtab_off = struct.unpack_from('<Q', data, shstrtab_hdr_off + 0x18)[0]

    sections = []
    for i in range(hdr['e_shnum']):
        off = hdr['e_shoff'] + i * hdr['e_shentsize']
        sh_name_idx = struct.unpack_from('<I', data, off)[0]
        name_end = data.index(0, shstrtab_off + sh_name_idx)
        name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        sections.append({
            'idx': i,
            'name': name,
            'sh_type': struct.unpack_from('<I', data, off + 4)[0],
            'sh_flags': struct.unpack_from('<Q', data, off + 8)[0],
            'sh_addr': struct.unpack_from('<Q', data, off + 0x10)[0],
            'sh_offset': struct.unpack_from('<Q', data, off + 0x18)[0],
            'sh_size': struct.unpack_from('<Q', data, off + 0x20)[0],
            'sh_link': struct.unpack_from('<I', data, off + 0x28)[0],
            'sh_info': struct.unpack_from('<I', data, off + 0x2C)[0],
            'sh_addralign': struct.unpack_from('<Q', data, off + 0x30)[0],
            'sh_entsize': struct.unpack_from('<Q', data, off + 0x38)[0],
            'hdr_offset': off,
        })
    return sections


def read_rela_entries(data, sec):
    """Read RELA entries from a section. Returns list of (offset, info, addend) tuples."""
    entries = []
    for i in range(0, sec['sh_size'], 24):
        base = sec['sh_offset'] + i
        r_offset = struct.unpack_from('<Q', data, base)[0]
        r_info = struct.unpack_from('<Q', data, base + 8)[0]
        r_addend = struct.unpack_from('<q', data, base + 16)[0]
        entries.append((r_offset, r_info, r_addend))
    return entries


def rela_type(info):
    return info & 0xFFFFFFFF


def rela_sym(info):
    return info >> 32


def make_rela_info(sym, typ):
    return (sym << 32) | typ


def detect_got_plt_pattern(data, text_sec, rela_entries):
    """
    Detect the GOT-relative PLT pattern in a text section.
    Returns the symbol index if matched, or None.

    Pattern (4 instructions, 2 GOT relocations):
      [+0] ADRP xN, :got:SYM          R_AARCH64_ADR_GOT_PAGE
      [+4] LDR  xN, [xN, :got_lo12:]  R_AARCH64_LD64_GOT_LO12_NC
      [+8] LDR  xM, [xN]              (no reloc)
      [+12] BR  xM                     (no reloc)
    """
    # Must be exactly 16 bytes (4 instructions)
    if text_sec['sh_size'] != 16:
        return None

    # Must have exactly 2 relocations
    if len(rela_entries) != 2:
        return None

    r0_off, r0_info, r0_add = rela_entries[0]
    r1_off, r1_info, r1_add = rela_entries[1]

    # Check relocation types and offsets
    if r0_off != 0 or rela_type(r0_info) != R_AARCH64_ADR_GOT_PAGE:
        return None
    if r1_off != 4 or rela_type(r1_info) != R_AARCH64_LD64_GOT_LO12_NC:
        return None

    # Both must reference same symbol
    sym0 = rela_sym(r0_info)
    sym1 = rela_sym(r1_info)
    if sym0 != sym1:
        return None

    # Decode instructions
    base = text_sec['sh_offset']
    insn0 = struct.unpack_from('<I', data, base)[0]
    insn1 = struct.unpack_from('<I', data, base + 4)[0]
    insn2 = struct.unpack_from('<I', data, base + 8)[0]
    insn3 = struct.unpack_from('<I', data, base + 12)[0]

    ok0, rd0 = is_adrp(insn0)
    if not ok0:
        return None

    ok1, rt1, rn1 = is_ldr_64_uoff(insn1)
    if not ok1 or rn1 != rd0:
        return None

    ok2, rt2, rn2 = is_ldr_64_uoff(insn2)
    if not ok2 or rn2 != rt1:
        return None

    # The dereference LDR must have offset 0 (just [xN], no displacement)
    imm12_2 = (insn2 >> 10) & 0xFFF
    if imm12_2 != 0:
        return None

    ok3, rn3 = is_br(insn3)
    if not ok3 or rn3 != rt2:
        return None

    return sym0


def apply_plt_fix(data, text_sec, rela_sec, rela_entries, sym_idx):
    """
    Rewrite a GOT-relative PLT stub to the NX direct pattern.
    Returns new RELA entries (3 entries instead of 2).
    """
    base = text_sec['sh_offset']

    # Rewrite instructions
    struct.pack_into('<I', data, base, ADRP_X16)
    struct.pack_into('<I', data, base + 4, LDR_X17_X16)
    struct.pack_into('<I', data, base + 8, ADD_X16_X16)
    struct.pack_into('<I', data, base + 12, BR_X17)

    # Build new RELA entries
    addend = rela_entries[0][2]  # preserve original addend
    new_entries = [
        (0, make_rela_info(sym_idx, R_AARCH64_ADR_PREL_PG_HI21), addend),
        (4, make_rela_info(sym_idx, R_AARCH64_LDST64_ABS_LO12_NC), addend),
        (8, make_rela_info(sym_idx, R_AARCH64_ADD_ABS_LO12_NC), addend),
    ]
    return new_entries


def write_rela_entries(entries):
    """Serialize RELA entries to bytes."""
    buf = bytearray(len(entries) * 24)
    for i, (off, info, addend) in enumerate(entries):
        struct.pack_into('<Q', buf, i * 24, off)
        struct.pack_into('<Q', buf, i * 24 + 8, info)
        struct.pack_into('<q', buf, i * 24 + 16, addend)
    return buf


def process_elf(filepath, dry_run=False):
    """Process an ELF .o file and patch GOT-relative PLT stubs to NX direct pattern."""
    path = Path(filepath)
    data = bytearray(path.read_bytes())

    hdr = parse_elf_header(data)
    if hdr is None:
        print(f"Error: {filepath} is not a 64-bit LE ELF file")
        return 0

    sections = parse_sections(data, hdr)

    # Build map: text section name -> rela section
    # .rela.text.XXX corresponds to .text.XXX
    text_by_name = {}
    rela_by_name = {}
    for sec in sections:
        if sec['name'].startswith('.text.') and (sec['sh_flags'] & 0x4):
            text_by_name[sec['name']] = sec
        elif sec['name'].startswith('.rela.text.') and sec['sh_type'] == 4:  # SHT_RELA
            # The corresponding text section name is everything after '.rela.'
            text_name = sec['name'][5:]  # strip '.rela' prefix -> '.text.XXX'
            rela_by_name[text_name] = sec

    patches = 0
    pending_rela_updates = []  # (rela_sec, new_rela_bytes)

    for text_name, text_sec in text_by_name.items():
        rela_sec = rela_by_name.get(text_name)
        if rela_sec is None:
            continue

        rela_entries = read_rela_entries(data, rela_sec)
        sym_idx = detect_got_plt_pattern(data, text_sec, rela_entries)
        if sym_idx is None:
            continue

        if dry_run:
            print(f"  Would patch: {text_name}")
            patches += 1
            continue

        new_entries = apply_plt_fix(data, text_sec, rela_sec, rela_entries, sym_idx)
        new_rela_bytes = write_rela_entries(new_entries)
        pending_rela_updates.append((rela_sec, new_rela_bytes))
        patches += 1

    if patches > 0 and not dry_run:
        # Apply rela updates: append new rela data at end of file, update section headers
        for rela_sec, new_bytes in pending_rela_updates:
            new_offset = len(data)
            data.extend(new_bytes)
            # Update section header: sh_offset and sh_size
            sh_off = rela_sec['hdr_offset']
            struct.pack_into('<Q', data, sh_off + 0x18, new_offset)  # sh_offset
            struct.pack_into('<Q', data, sh_off + 0x20, len(new_bytes))  # sh_size

        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(description='Patch GOT-relative PLT stubs to NX direct pattern in AArch64 ELF objects')
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
            print(f"{action} {count} PLT stub(s) in {f}")
        total += count

    if total == 0:
        print("No GOT-relative PLT stubs found to patch.")


if __name__ == '__main__':
    main()
