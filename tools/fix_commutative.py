#!/usr/bin/env python3
"""
Post-processing: fix commutative operand ordering to match NX Clang.

NX Clang orders operands of commutative instructions (ADD, AND, ORR, EOR,
ANDS/ADDS) differently from upstream Clang 8.0.0.  This is an IR-level
canonicalization difference that cannot be fixed in the backend.

This script compares each instruction against the original binary.  When the
ONLY difference is that Rn and Rm are swapped on a commutative instruction
(with zero shift), it patches the .o file to match the original ordering.

Safe because ADD(a,b) == ADD(b,a), AND(a,b) == AND(b,a), etc.

AArch64 shifted-register encoding (ADD/SUB/logic):
  [31]     sf
  [30:21]  opcode
  [20:16]  Rm
  [15:10]  imm6 (shift amount)
  [9:5]    Rn
  [4:0]    Rd

Usage:
    python tools/fix_commutative.py [--dry-run] [--verbose] build/*.o
"""

import csv
import glob
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000


# ─── AArch64 instruction classification ──────────────────────────────

def is_commutative_shifted_reg(insn):
    """Check if instruction is a commutative shifted-register op with shift=0.

    Returns True for: ADD, ADDS, AND, ANDS, ORR, EOR (shifted register)
    when the shift amount (imm6) is zero.

    Does NOT match SUB/SUBS (not commutative), BIC/ORN/EON (inverted),
    or any instruction with a non-zero shift (shift applies to Rm only).
    """
    imm6 = (insn >> 10) & 0x3F
    if imm6 != 0:
        return False  # shift applied to Rm — swapping would change semantics

    # Extract opcode fields
    # Bits [30:24] for major classification, bit [21] for N flag
    top8 = (insn >> 24) & 0xFF
    n_bit = (insn >> 21) & 1

    # ADD shifted register:  x0001011 sh 0 Rm imm6 Rn Rd  (sf=x, op=0, S=0)
    # ADDS shifted register: x0101011 sh 0 Rm imm6 Rn Rd  (sf=x, op=0, S=1)
    # SUB shifted register:  x1001011 — NOT commutative
    # SUBS shifted register: x1101011 — NOT commutative (but CMP alias is)
    if (top8 & 0x7F) == 0x0B and n_bit == 0:  # ADD
        return True
    if (top8 & 0x7F) == 0x2B and n_bit == 0:  # ADDS
        return True

    # Logical shifted register: sf opc 01010 sh N Rm imm6 Rn Rd
    # AND:  x00 01010 sh 0 — commutative
    # ORR:  x01 01010 sh 0 — commutative
    # EOR:  x10 01010 sh 0 — commutative
    # ANDS: x11 01010 sh 0 — commutative
    # BIC:  x00 01010 sh 1 — NOT commutative (inverted Rm)
    # ORN:  x01 01010 sh 1 — NOT commutative
    # EON:  x10 01010 sh 1 — NOT commutative
    # BICS: x11 01010 sh 1 — NOT commutative
    if (top8 & 0x1F) == 0x0A and n_bit == 0:  # AND/ORR/EOR/ANDS
        return True

    return False


def swap_rn_rm(insn):
    """Swap Rn [9:5] and Rm [20:16] fields."""
    rn = (insn >> 5) & 0x1F
    rm = (insn >> 16) & 0x1F
    result = insn & ~(0x1F << 5) & ~(0x1F << 16)
    result |= (rm << 5) | (rn << 16)
    return result


def is_commutative_swap(orig, decomp):
    """Check if two instructions differ ONLY by Rn/Rm swap on a commutative op."""
    if orig == decomp:
        return False
    if not is_commutative_shifted_reg(orig):
        return False
    if not is_commutative_shifted_reg(decomp):
        return False
    # Same opcode (everything except Rn/Rm)?
    mask = ~((0x1F << 5) | (0x1F << 16))
    if (orig & mask) != (decomp & mask):
        return False
    # Rn/Rm swapped?
    return swap_rn_rm(decomp) == orig


# ─── ELF helpers ──────────────────────────────────────────────────────

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


def read_bytes_at(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None


def extract_func_name(mangled):
    if not mangled.startswith('_Z'):
        return mangled
    # Nested name: _ZN<len><name><len><name>...E<params>
    if mangled.startswith('_ZN'):
        rest = mangled[3:]
        last_name = None
        while rest and rest[0] != 'E':
            i = 0
            while i < len(rest) and rest[i].isdigit():
                i += 1
            if i == 0:
                break
            length = int(rest[:i])
            name = rest[i:i + length]
            if len(name) < length:
                break
            last_name = name
            rest = rest[i + length:]
        if last_name:
            return last_name
    # Non-nested: _Z<len><name><params>
    rest = mangled[2:]
    i = 0
    while i < len(rest) and rest[i].isdigit():
        i += 1
    if i > 0:
        length = int(rest[:i])
        name = rest[i:i + length]
        if len(name) >= length:
            return name
    return mangled


# ─── Main ─────────────────────────────────────────────────────────────

def process_file(o_path, csv_lookup, csv_by_short, orig_segments, orig_f, dry_run, verbose):
    """Process one .o file. Returns (patched_count, checked_count)."""
    data = bytearray(o_path.read_bytes())
    if data[:4] != b'\x7fELF':
        return 0, 0

    try:
        shoff = struct.unpack_from('<Q', data, 0x28)[0]
        shentsize = struct.unpack_from('<H', data, 0x3a)[0]
        shnum = struct.unpack_from('<H', data, 0x3c)[0]
        shstrndx = struct.unpack_from('<H', data, 0x3e)[0]
        str_off = struct.unpack_from('<Q', data, shoff + shstrndx * shentsize + 0x18)[0]
        str_sz = struct.unpack_from('<Q', data, shoff + shstrndx * shentsize + 0x20)[0]
        strtab = bytes(data[str_off:str_off + str_sz])
    except Exception:
        return 0, 0

    patched = 0
    checked = 0

    for i in range(shnum):
        base = shoff + i * shentsize
        sh_name_off = struct.unpack_from('<I', data, base)[0]
        sh_type = struct.unpack_from('<I', data, base + 4)[0]
        end = strtab.index(b'\0', sh_name_off)
        sec_name = strtab[sh_name_off:end].decode('ascii', errors='replace')

        if not sec_name.startswith('.text.') or sh_type != 1:
            continue

        sh_offset = struct.unpack_from('<Q', data, base + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, base + 0x20)[0]
        if sh_size < 4:
            continue

        mangled = sec_name[6:]

        # Look up in CSV: try full mangled name, then short name
        if mangled in csv_lookup:
            addr, csv_size = csv_lookup[mangled]
        else:
            short = extract_func_name(mangled)
            if short in csv_lookup:
                addr, csv_size = csv_lookup[short]
            elif short in csv_by_short:
                addr, csv_size = csv_by_short[short]
            else:
                continue

        if csv_size != sh_size:
            continue

        checked += 1

        # Read original bytes
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
        orig_bytes = read_bytes_at(orig_f, orig_segments, vaddr, sh_size)
        if orig_bytes is None or len(orig_bytes) != sh_size:
            continue

        # Compare instruction by instruction
        n = sh_size // 4
        func_patched = 0
        for j in range(n):
            orig_w = struct.unpack_from('<I', orig_bytes, j * 4)[0]
            decomp_w = struct.unpack_from('<I', data, sh_offset + j * 4)[0]

            if orig_w == decomp_w:
                continue

            if is_commutative_swap(orig_w, decomp_w):
                if not dry_run:
                    struct.pack_into('<I', data, sh_offset + j * 4, orig_w)
                func_patched += 1

        if func_patched > 0:
            patched += func_patched
            if verbose:
                display = extract_func_name(mangled)
                print("  %s: %d commutative swap(s) fixed" % (display, func_patched))

    if patched > 0 and not dry_run:
        o_path.write_bytes(bytes(data))

    return patched, checked


def main():
    dry_run = '--dry-run' in sys.argv
    verbose = '--verbose' in sys.argv or '-v' in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith('-')]

    if not args:
        print("Usage: python tools/fix_commutative.py [--dry-run] [--verbose] build/*.o")
        return

    # Expand globs
    o_files = []
    for pattern in args:
        o_files.extend(glob.glob(pattern))
    if not o_files:
        print("No .o files matched")
        return

    # Load CSV — index by full name and short name
    csv_lookup = {}
    csv_by_short = {}
    with open(FUNCTIONS_CSV) as f:
        for row in csv.DictReader(f):
            addr = int(row['Address'], 16)
            size = int(row['Size'])
            name = row['Name']
            csv_lookup[name] = (addr, size)
            short = extract_func_name(name)
            if short and short not in csv_by_short:
                csv_by_short[short] = (addr, size)

    # Load original ELF
    orig_segments = load_elf_segments(str(ORIGINAL_ELF))

    total_patched = 0
    total_checked = 0

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for o_path in sorted(set(o_files)):
            p = Path(o_path)
            patched, checked = process_file(
                p, csv_lookup, csv_by_short, orig_segments, orig_f, dry_run, verbose)
            total_patched += patched
            total_checked += checked

    action = "Would patch" if dry_run else "Patched"
    print("%s %d commutative swap(s) across %d functions checked" % (
        action, total_patched, total_checked))


if __name__ == '__main__':
    main()
