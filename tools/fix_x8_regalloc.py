#!/usr/bin/env python3
"""
Post-processing script to fix x8-dispatch register allocation in .o files.

Many SSBU vtable dispatch functions receive the module pointer in x8 and
do a vtable call. The original binary (NX Clang) uses x9 as the scratch
register for the vtable chain, while upstream Clang 8.0.0 reuses x8.

Original (NX Clang):
    stp x29, x30, [sp, #-0x10]!
    mov x29, sp
    [str x10, [x0, #0x10]]     ; optional side-store
    ldr x9, [x8, #0x0]         ; vtable ptr via x9
    ldr x9, [x9, #OFFSET]      ; vfunc via x9
    mov x0, x8                  ; self = x8
    blr x9                      ; call via x9
    ldp x29, x30, [sp], #0x10
    mov w0, wzr
    ret

Decomp (upstream Clang 8):
    stp x29, x30, [sp, #-0x10]!
    mov x29, sp
    [str x10, [x0, #0x10]]     ; optional side-store
    mov x0, x8                  ; self = x8 (moved earlier)
    ldr x8, [x8, #0x0]         ; vtable ptr via x8
    ldr x8, [x8, #OFFSET]      ; vfunc via x8
    blr x8                      ; call via x8
    ldp x29, x30, [sp], #0x10
    mov w0, wzr
    ret

This script detects the decomp pattern and rewrites to match the original.
"""

import struct
import glob
import csv
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000

# Instruction constants
MOV_X29_SP = 0x910003FD
MOV_X0_X8 = 0xAA0803E0
MOV_W0_WZR = 0x2A1F03E0
RET = 0xD65F03C0
BLR_X8 = 0xD63F0100
BLR_X9 = 0xD63F0120


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


def read_elf_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


def extract_func_name(mangled):
    if mangled.startswith("_ZN3app8lua_bind"):
        rest = mangled[len("_ZN3app8lua_bind"):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i == 0:
            return None
        length = int(rest[:i])
        name = rest[i:i + length]
        return name if len(name) == length else None
    if mangled.startswith("_Z"):
        rest = mangled[2:]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i == 0:
            return None
        length = int(rest[:i])
        name = rest[i:i + length]
        return name if len(name) == length else None
    if mangled.startswith("FUN_"):
        return mangled
    return None


def is_stp_x29_x30(insn):
    mask = 0xFFC07FFF
    bits = 0xA9800000 | (30 << 10) | (31 << 5) | 29
    return (insn & mask) == bits


def is_ldp_x29_x30(insn):
    mask = 0xFFC07FFF
    bits = 0xA8C00000 | (30 << 10) | (31 << 5) | 29
    return (insn & mask) == bits


def is_ldr_x8_x8_imm(insn):
    """ldr x8, [x8, #imm]"""
    # LDR (unsigned offset): 1111 1001 01 imm12 Rn Rt
    # Rt=x8 (bits 0-4 = 01000), Rn=x8 (bits 5-9 = 01000)
    return (insn & 0xFFC003FF) == (0xF9400000 | (8 << 5) | 8)


def is_ldr_x8_from_x8_0(insn):
    """ldr x8, [x8, #0x0] — exact match"""
    return insn == 0xF9400108


def ldr_change_regs(insn, new_rt, new_rn):
    """Change Rt and Rn in an LDR instruction."""
    return (insn & 0xFFFFFC00) | (new_rn << 5) | new_rt


def detect_and_fix_pattern(data, sec_off, sec_size, orig_f, orig_segs, vaddr):
    """Detect x8-dispatch decomp pattern and rewrite to match original.
    Returns number of patches applied."""

    n = sec_size // 4
    if n < 7:  # Minimum: stp, mov x29, mov x0, ldr, ldr, blr, ldp, ret (but some are smaller)
        return 0

    words = [struct.unpack_from('<I', data, sec_off + i * 4)[0] for i in range(n)]

    # Read original to verify we should patch
    orig_bytes = read_elf_bytes(orig_f, orig_segs, vaddr, sec_size)
    if orig_bytes is None or len(orig_bytes) < sec_size:
        return 0

    orig_words = [struct.unpack_from('<I', orig_bytes, i * 4)[0] for i in range(n)]

    # Check if already matching
    if words == orig_words:
        return 0

    # Check if original uses x8-dispatch pattern (x8 as source in early LDR)
    orig_uses_x8 = False
    for i in range(min(5, n)):
        if (orig_words[i] & 0xFFC003E0) == 0xF9400100:  # ldr xN, [x8, ...]
            orig_uses_x8 = True
            break
    if not orig_uses_x8:
        return 0

    # Pattern A (9 insns, no str x10):
    # Decomp: stp, mov x29, mov x0 x8, ldr x8 [x8 #0], ldr x8 [x8 #off], blr x8, ldp, mov w0 wzr, ret
    # Target: stp, mov x29, ldr x9 [x8 #0], ldr x9 [x9 #off], mov x0 x8, blr x9, ldp, mov w0 wzr, ret

    if n == 9:
        if (is_stp_x29_x30(words[0]) and words[1] == MOV_X29_SP and
            words[2] == MOV_X0_X8 and
            is_ldr_x8_from_x8_0(words[3]) and  # ldr x8, [x8, #0]
            is_ldr_x8_x8_imm(words[4]) and  # ldr x8, [x8, #off]
            words[5] == BLR_X8 and
            is_ldp_x29_x30(words[6]) and words[7] == MOV_W0_WZR and words[8] == RET):

            # Rewrite instructions 2-5:
            new_words = list(words)
            new_words[2] = ldr_change_regs(words[3], 9, 8)   # ldr x9, [x8, #0]
            new_words[3] = ldr_change_regs(words[4], 9, 9)   # ldr x9, [x9, #off]
            new_words[4] = MOV_X0_X8                          # mov x0, x8
            new_words[5] = BLR_X9                             # blr x9

            # Verify against original
            if new_words == orig_words:
                for i in range(n):
                    struct.pack_into('<I', data, sec_off + i * 4, new_words[i])
                return 1

    # Pattern B (10 insns, with str x10):
    # Decomp: stp, mov x29, str x10, mov x0 x8, ldr x8 [x8 #0], ldr x8 [x8 #off], blr x8, ldp, mov w0, ret
    # Target: stp, mov x29, str x10, ldr x9 [x8 #0], ldr x9 [x9 #off], mov x0 x8, blr x9, ldp, mov w0, ret

    if n == 10:
        # Check for str x10 at position 2
        has_str_x10 = (words[2] & 0xFFC003FF) == 0xF900000A  # str x10, [x0, #imm]

        if (is_stp_x29_x30(words[0]) and words[1] == MOV_X29_SP and
            has_str_x10 and
            words[3] == MOV_X0_X8 and
            is_ldr_x8_from_x8_0(words[4]) and
            is_ldr_x8_x8_imm(words[5]) and
            words[6] == BLR_X8 and
            is_ldp_x29_x30(words[7]) and words[8] == MOV_W0_WZR and words[9] == RET):

            new_words = list(words)
            new_words[3] = ldr_change_regs(words[4], 9, 8)   # ldr x9, [x8, #0]
            new_words[4] = ldr_change_regs(words[5], 9, 9)   # ldr x9, [x9, #off]
            new_words[5] = MOV_X0_X8                          # mov x0, x8
            new_words[6] = BLR_X9                             # blr x9

            if new_words == orig_words:
                for i in range(n):
                    struct.pack_into('<I', data, sec_off + i * 4, new_words[i])
                return 1

    # Pattern C (8 insns, direct bl call with str x10):
    # Decomp: stp, mov x29, str x10, mov x0 x8, bl <func>, mov w0 wzr, ldp, ret
    # Target: stp, mov x29, str x10, mov x0 x8, bl <func>, mov w0 wzr, ldp, ret
    # (These may already match if the only diff is relocation)

    return 0


def process_elf(filepath, csv_by_short, orig_f, orig_segs, dry_run=False):
    """Process an ELF .o file and fix x8-dispatch register allocation."""
    path = Path(filepath)
    data = bytearray(path.read_bytes())

    if data[:4] != b'\x7fELF' or data[4] != 2 or data[5] != 1:
        return 0

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    shstrtab_off = struct.unpack_from('<Q', data,
                                       e_shoff + e_shstrndx * e_shentsize + 0x18)[0]

    patches = 0

    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_type = struct.unpack_from('<I', data, sh_off + 4)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        if sh_type != 1 or sh_size < 16:
            continue

        name_end = data.index(0, shstrtab_off + sh_name_idx)
        sec_name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        if not sec_name.startswith('.text.'):
            continue

        mangled = sec_name[6:]
        short = extract_func_name(mangled)
        if not short:
            if mangled in csv_by_short:
                short = mangled
            else:
                continue

        if short not in csv_by_short:
            continue

        addr, quality, csv_size = csv_by_short[short]
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr

        if dry_run:
            # Make a copy to test without modifying
            test_data = bytearray(data)
            count = detect_and_fix_pattern(test_data, sh_offset, sh_size,
                                          orig_f, orig_segs, vaddr)
            if count > 0:
                print(f"  Would fix: {sec_name} ({sh_size // 4} insns)")
                patches += count
        else:
            count = detect_and_fix_pattern(data, sh_offset, sh_size,
                                          orig_f, orig_segs, vaddr)
            patches += count

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    import argparse
    parser = argparse.ArgumentParser(
        description='Fix x8-dispatch register allocation (x8->x9 scratch) in AArch64 .o files')
    parser.add_argument('files', nargs='+', help='ELF object files to patch')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be patched without modifying')
    args = parser.parse_args()
    # Expand globs for Windows cmd.exe compatibility
    import glob as _glob
    expanded = []
    for pattern in args.files:
        matched = _glob.glob(pattern)
        expanded.extend(matched if matched else [pattern])
    args.files = expanded

    # Load CSV lookup
    csv_by_short = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            quality = row[1]
            size = int(row[2])
            name = row[3]
            csv_by_short[name] = (addr, quality, size)
            short = extract_func_name(name)
            if short and short not in csv_by_short:
                csv_by_short[short] = (addr, quality, size)

    orig_segs = load_elf_segments(ORIGINAL_ELF)

    total = 0
    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for filepath in args.files:
            if filepath.startswith('--'):
                continue
            count = process_elf(filepath, csv_by_short, orig_f, orig_segs,
                              dry_run=args.dry_run)
            if count > 0:
                action = "Would fix" if args.dry_run else "Fixed"
                print(f"{action} {count} x8-dispatch function(s) in {filepath}")
            total += count

    if total == 0:
        print("No x8-dispatch register allocation mismatches found.")
    else:
        action = "Would fix" if args.dry_run else "Fixed"
        print(f"\nTotal: {action} {total} x8-dispatch function(s)")


if __name__ == '__main__':
    main()
