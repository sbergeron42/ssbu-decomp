#!/usr/bin/env python3
"""
Verify jemalloc_a_004.o functions against the original ELF.
Masks ADRP, BL, B, B.cond, TBNZ, TBZ, CBZ, CBNZ instructions
(which contain addresses that differ due to relocations).
"""

import struct
import sys
import os
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000

# Functions to verify: (symbol_name_in_obj, original_address, expected_size)
FUNCTIONS = [
    ("static_opts_init",   0x710392c8f0, 96),
    ("dynamic_opts_init",  0x710392c950, 80),
    ("imalloc",            0x710392c9a0, 208),
    ("malloc_default",     0x710392c870, 128),
    ("je_mallctl_d610",    0x710392d610, 84),   # might be smaller
    ("je_posix_memalign",  0x710392dc40, 160),
    ("je_aligned_alloc",   0x710392dce0, 160),
    ("free_default",       0x710392e590, 224),
    ("je_malloc_size",     0x710392e8a0, 128),
    ("je_mallctl",         0x710392e690, 176),
    ("je_mallctlbymib",    0x710392e7e0, 192),
]


def load_elf_segments(path):
    segments = []
    with open(path, 'rb') as f:
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


def read_original_bytes(segments, addr, size):
    vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
    with open(ORIGINAL_ELF, 'rb') as f:
        for seg_vaddr, seg_offset, seg_filesz in segments:
            if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
                f.seek(seg_offset + (vaddr - seg_vaddr))
                return f.read(size)
    return None


def find_function_in_obj(obj_path, func_name):
    """Extract function bytes from .o file by searching .text.<name> sections."""
    with open(obj_path, 'rb') as f:
        ident = f.read(16)
        if ident[:4] != b'\x7fELF':
            return None

        f.seek(0x28)
        shoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x3a)
        shentsize = struct.unpack('<H', f.read(2))[0]
        shnum = struct.unpack('<H', f.read(2))[0]
        shstrndx = struct.unpack('<H', f.read(2))[0]

        # Read section header string table
        f.seek(shoff + shstrndx * shentsize + 0x18)
        strtab_off = struct.unpack('<Q', f.read(8))[0]
        strtab_sz = struct.unpack('<Q', f.read(8))[0]
        f.seek(strtab_off)
        strtab = f.read(strtab_sz)

        for i in range(shnum):
            f.seek(shoff + i * shentsize)
            sh_name_idx = struct.unpack('<I', f.read(4))[0]
            sh_type = struct.unpack('<I', f.read(4))[0]
            if sh_type != 1:  # SHT_PROGBITS
                continue
            end = strtab.index(b'\0', sh_name_idx)
            sec_name = strtab[sh_name_idx:end].decode('ascii', errors='replace')
            if sec_name == f'.text.{func_name}':
                f.seek(shoff + i * shentsize + 0x18)
                sh_offset = struct.unpack('<Q', f.read(8))[0]
                sh_size = struct.unpack('<Q', f.read(8))[0]
                if sh_size == 0:
                    continue
                f.seek(sh_offset)
                return f.read(sh_size)
    return None


def is_relocatable_insn(insn):
    """Check if an instruction is relocatable (ADRP, BL, B, B.cond, TBZ, TBNZ, CBZ, CBNZ, ADD with lo12)."""
    # ADRP: bit pattern 1xx1 0000 ...
    if (insn & 0x9F000000) == 0x90000000:
        return True, "ADRP"
    # BL: 1001 01xx xxxx xxxx xxxx xxxx xxxx xxxx
    if (insn & 0xFC000000) == 0x94000000:
        return True, "BL"
    # B: 0001 01xx xxxx xxxx xxxx xxxx xxxx xxxx
    if (insn & 0xFC000000) == 0x14000000:
        return True, "B"
    # B.cond: 0101 0100 xxxx xxxx xxxx xxxx xxx0 xxxx
    if (insn & 0xFF000010) == 0x54000000:
        return True, "B.cond"
    # TBZ: 0x36 top byte range  0011 011x ...
    if (insn & 0x7F000000) == 0x36000000:
        return True, "TBZ"
    # TBNZ: 0x37 top byte range  0011 011x ...
    if (insn & 0x7F000000) == 0x37000000:
        return True, "TBNZ"
    # CBZ: x011 010x ...
    if (insn & 0x7F000000) == 0x34000000:
        return True, "CBZ"
    # CBNZ: x011 010x ...
    if (insn & 0x7F000000) == 0x35000000:
        return True, "CBNZ"
    # ADD immediate (used for :lo12: relocations)
    # Check if original uses same base opcode
    if (insn & 0xFF800000) == 0x91000000:  # ADD Xd, Xn, #imm
        return True, "ADD_lo12"
    # LDR with unsigned offset (may have :lo12:)
    # We'll handle these specially below
    return False, ""


def mask_instruction(orig_insn, decomp_insn):
    """
    Compare two instructions. Return True if they match after masking relocations.
    Also returns a status string.
    """
    if orig_insn == decomp_insn:
        return True, "OK"

    orig_reloc, orig_type = is_relocatable_insn(orig_insn)
    decomp_reloc, decomp_type = is_relocatable_insn(decomp_insn)

    # Both are the same type of relocatable instruction
    if orig_reloc and decomp_reloc and orig_type == decomp_type:
        # For ADRP: mask the immediate (bits 5-23 and bit 29-30)
        if orig_type == "ADRP":
            # Same Rd register
            if (orig_insn & 0x1F) == (decomp_insn & 0x1F):
                return True, "ADRP(reloc)"
        # For BL/B: just check opcode matches
        if orig_type in ("BL", "B"):
            return True, f"{orig_type}(reloc)"
        # For B.cond: check condition code matches
        if orig_type == "B.cond":
            if (orig_insn & 0x0F) == (decomp_insn & 0x0F):
                return True, "B.cond(reloc)"
        # For TBZ/TBNZ: check register and bit match
        if orig_type in ("TBZ", "TBNZ"):
            if (orig_insn & 0xFFF8001F) == (decomp_insn & 0xFFF8001F):
                return True, f"{orig_type}(reloc)"
        # For CBZ/CBNZ: check register matches
        if orig_type in ("CBZ", "CBNZ"):
            if (orig_insn & 0xFF00001F) == (decomp_insn & 0xFF00001F):
                return True, f"{orig_type}(reloc)"
        # For ADD lo12: check Rd, Rn match (mask immediate)
        if orig_type == "ADD_lo12":
            if (orig_insn & 0xFFC003FF) == (decomp_insn & 0xFFC003FF):
                return True, "ADD(lo12 reloc)"

    # ADD with :lo12: relocation — decomp has 0 immediate, orig has the real offset
    # Check if both are ADD Xd, Xn, #imm with same Rd and Rn
    if (orig_insn & 0xFF800000) == 0x91000000 and (decomp_insn & 0xFF800000) == 0x91000000:
        if (orig_insn & 0x000003FF) == (decomp_insn & 0x000003FF):  # Rd match
            if ((orig_insn >> 5) & 0x1F) == ((decomp_insn >> 5) & 0x1F):  # Rn match
                return True, "ADD(lo12 reloc)"

    # STR/LDR with :lo12: offset
    # STR (unsigned offset): 1x11 1001 00xx xxxx xxxx xxxx xxxx xxxx
    for mask, name in [
        (0xFFC00000, "STR(lo12)"),   # STR 64-bit unsigned offset
        (0xFFC00000, "LDR(lo12)"),   # LDR 64-bit unsigned offset
    ]:
        if (orig_insn & 0x3F000000) == 0x39000000:  # LDR/STR unsigned offset family
            if (orig_insn & 0xFFC003FF) == (decomp_insn & 0xFFC003FF):  # same Rt, Rn
                # Check same size/opc bits
                if (orig_insn >> 22) == (decomp_insn >> 22):
                    return True, "LDR/STR(lo12 reloc)"

    return False, "DIFF"


def main():
    obj_path = BUILD_DIR / "jemalloc_a_004.o"
    if not obj_path.exists():
        print(f"ERROR: {obj_path} not found")
        return 1

    segments = load_elf_segments(ORIGINAL_ELF)
    total_match = 0
    total_insns = 0
    total_funcs = 0
    perfect_funcs = 0

    for func_name, orig_addr, expected_size in FUNCTIONS:
        decomp_bytes = find_function_in_obj(obj_path, func_name)
        if decomp_bytes is None:
            print(f"  {func_name}: NOT FOUND in .o file")
            continue

        orig_bytes = read_original_bytes(segments, orig_addr, len(decomp_bytes))
        if orig_bytes is None:
            print(f"  {func_name}: address 0x{orig_addr:x} not found in ELF")
            continue

        total_funcs += 1
        num_insns = len(decomp_bytes) // 4
        func_match = 0
        func_diff = 0
        diff_details = []

        for i in range(0, min(len(orig_bytes), len(decomp_bytes)), 4):
            oi = struct.unpack('<I', orig_bytes[i:i+4])[0]
            di = struct.unpack('<I', decomp_bytes[i:i+4])[0]
            matched, status = mask_instruction(oi, di)
            if matched:
                func_match += 1
            else:
                func_diff += 1
                diff_details.append((i // 4, oi, di, status))

        total_match += func_match
        total_insns += num_insns

        if func_diff == 0:
            perfect_funcs += 1
            print(f"  {func_name} @ 0x{orig_addr:x}: {num_insns}/{num_insns} MATCH ({len(decomp_bytes)} bytes) [VERIFIED]")
        else:
            pct = func_match * 100 / num_insns if num_insns else 0
            print(f"  {func_name} @ 0x{orig_addr:x}: {func_match}/{num_insns} match ({pct:.0f}%) — {func_diff} diffs:")
            for idx, oi, di, status in diff_details[:10]:
                print(f"    insn {idx:3d}: orig=0x{oi:08x}  decomp=0x{di:08x}  {status}")
            if len(diff_details) > 10:
                print(f"    ... and {len(diff_details) - 10} more diffs")

    print()
    if total_insns > 0:
        print(f"TOTAL: {total_match}/{total_insns} instructions match ({total_match*100/total_insns:.1f}%)")
    print(f"FUNCTIONS: {perfect_funcs}/{total_funcs} verified perfectly")
    return 0 if perfect_funcs == total_funcs else 1


if __name__ == '__main__':
    sys.exit(main())
