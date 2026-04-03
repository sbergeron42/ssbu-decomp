#!/usr/bin/env python3
"""
Analyze register allocation divergences in non-matching functions.

Compares compiled .o files (per-function .text sections) against the original
ELF binary to categorize instruction-level differences.

Patterns detected:
  1. RETURN_ZERO_WIDTH: mov w0,wzr vs mov x0,xzr (or vice versa)
  2. TAIL_CALL_REG: br xN vs br xM (different register for indirect branch)
  3. SCRATCH_REG: Same instruction but different scratch register choice
  4. EPILOGUE_ORDER: ldp/mov ordering at function end
  5. PROLOGUE_ORDER: instruction ordering after stp in prologue
  6. PCREL_ONLY: Only PC-relative differences (addresses, not codegen)
  7. MOVZ_ORR: movz vs orr immediate encoding
  8. INSN_REORDER: Same instructions, different order (scheduling)
  9. X8_DISPATCH: x8 used as first arg instead of x0 (ABI difference)
  10. OTHER: Unclassified

Usage:
    python tools/analyze_regalloc.py [--limit N] [--verbose]
"""

import struct
import csv
import sys
import os
from pathlib import Path
from collections import Counter, defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000


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
    """Extract short function name from mangled C++ symbol.

    Handles:
      _ZN3app8lua_bind26SomeModule__some_func_implE... -> SomeModule__some_func_impl
      _Z14FUN_71000067e0Pyy -> FUN_71000067e0
      FUN_71000067e0 -> FUN_71000067e0
    """
    # lua_bind style
    prefix = "_ZN3app8lua_bind"
    if mangled.startswith(prefix):
        rest = mangled[len(prefix):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i == 0:
            return None
        length = int(rest[:i])
        name = rest[i:i + length]
        return name if len(name) == length else None

    # _Z<len><name><params> style (simple C++ mangled names like FUN_*)
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

    # Already a plain name
    if mangled.startswith("FUN_") or mangled.startswith("initalize"):
        return mangled

    return None


def parse_elf_sections(data):
    """Parse ELF .o file, return dict of section_name -> (offset, size, sec_idx)."""
    if data[:4] != b'\x7fELF' or data[4] != 2 or data[5] != 1:
        return {}, {}

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    shstrtab_off = struct.unpack_from('<Q', data,
                                       e_shoff + e_shstrndx * e_shentsize + 0x18)[0]

    text_sections = {}  # mangled_name -> (offset, size)

    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_type = struct.unpack_from('<I', data, sh_off + 4)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        name_end = data.index(0, shstrtab_off + sh_name_idx)
        name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        if sh_type == 1 and name.startswith('.text.'):
            mangled = name[6:]  # strip ".text."
            text_sections[mangled] = (sh_offset, sh_size)

    return text_sections


# ============= Instruction classification helpers =============

def is_branch_reg(insn):
    """br xN -> returns N, else -1"""
    if (insn & 0xFFFFFC1F) == 0xD61F0000:
        return (insn >> 5) & 0x1F
    return -1


def is_blr(insn):
    """blr xN -> returns N, else -1"""
    if (insn & 0xFFFFFC1F) == 0xD63F0000:
        return (insn >> 5) & 0x1F
    return -1


def is_ret(insn):
    return insn == 0xD65F03C0


def is_nop(insn):
    return insn == 0xD503201F


def is_mov_reg_zero(insn):
    """Check mov wN,wzr / mov xN,xzr. Returns (rd, is_64bit) or None."""
    # mov wN, wzr = orr wN, wzr, wzr = 0x2A1F03E0 | Rd
    if (insn & 0xFFFFFFE0) == 0x2A1F03E0:
        return (insn & 0x1F, False)
    # mov xN, xzr = orr xN, xzr, xzr = 0xAA1F03E0 | Rd
    if (insn & 0xFFFFFFE0) == 0xAA1F03E0:
        return (insn & 0x1F, True)
    return None


def is_movz(insn):
    """movz Wd/Xd, #imm, lsl #N"""
    if (insn & 0x7F800000) == 0x52800000:
        is_64 = (insn >> 31) & 1
        rd = insn & 0x1F
        imm16 = (insn >> 5) & 0xFFFF
        hw = (insn >> 21) & 3
        return (rd, imm16, hw, bool(is_64))
    return None


def is_orr_imm(insn):
    """orr Wd/Xd, WZR/XZR, #imm"""
    opc_mask = 0x7F800000
    if (insn & opc_mask) == 0x32000000 or (insn & opc_mask) == 0xB2000000:
        rn = (insn >> 5) & 0x1F
        if rn == 31:
            return True
    return False


def is_pcrel(insn):
    """b/bl or adrp"""
    top6 = insn >> 26
    if top6 == 0x05 or top6 == 0x25:  # b or bl
        return True
    if (insn & 0x9F000000) == 0x90000000:  # adrp
        return True
    return False


def is_stp_x29_x30(insn):
    """stp x29, x30, [sp, #imm]! (pre-index)"""
    mask = 0xFFC07FFF
    bits = 0xA9800000 | (30 << 10) | (31 << 5) | 29
    return (insn & mask) == bits


def is_ldp_x29_x30(insn):
    """ldp x29, x30, [sp], #imm (post-index)"""
    mask = 0xFFC07FFF
    bits = 0xA8C00000 | (30 << 10) | (31 << 5) | 29
    return (insn & mask) == bits


def get_rd(insn):
    """Get destination register (bits 4:0)."""
    return insn & 0x1F


def get_rn(insn):
    """Get first source register (bits 9:5)."""
    return (insn >> 5) & 0x1F


def get_rm(insn):
    """Get second source register (bits 20:16)."""
    return (insn >> 16) & 0x1F


def insn_without_regs(insn):
    """Zero out register fields to compare instruction shape."""
    # Zero rd (4:0), rn (9:5), rm (20:16)
    return insn & ~(0x1F | (0x1F << 5) | (0x1F << 16))


def classify_single_diff(orig, decomp):
    """Classify a single instruction difference."""
    # PC-relative (b/bl/adrp offset difference)
    if is_pcrel(orig) and is_pcrel(decomp):
        # Same instruction type?
        if (orig >> 26) == (decomp >> 26):
            return "PCREL"
        if (orig & 0x9F000000) == 0x90000000 and (decomp & 0x9F000000) == 0x90000000:
            return "PCREL"

    # Return zero width: mov w0,wzr vs mov x0,xzr
    o_zero = is_mov_reg_zero(orig)
    d_zero = is_mov_reg_zero(decomp)
    if o_zero and d_zero:
        if o_zero[0] == d_zero[0] and o_zero[1] != d_zero[1]:
            return "RETURN_ZERO_WIDTH"

    # Tail call register: br xN vs br xM
    o_br = is_branch_reg(orig)
    d_br = is_branch_reg(decomp)
    if o_br >= 0 and d_br >= 0 and o_br != d_br:
        return "TAIL_CALL_REG"

    # blr register: blr xN vs blr xM
    o_blr = is_blr(orig)
    d_blr = is_blr(decomp)
    if o_blr >= 0 and d_blr >= 0 and o_blr != d_blr:
        return "SCRATCH_REG"  # register choice for function pointer

    # movz vs orr immediate
    if is_movz(orig) is not None and is_orr_imm(decomp):
        return "MOVZ_ORR"
    if is_orr_imm(orig) and is_movz(decomp) is not None:
        return "MOVZ_ORR"

    # Same opcode shape, different registers = scratch register diff
    o_shape = insn_without_regs(orig)
    d_shape = insn_without_regs(decomp)
    if o_shape == d_shape and orig != decomp:
        return "SCRATCH_REG"

    return "OTHER"


def classify_function(orig_words, decomp_words, n, verbose=False):
    """Classify the mismatch pattern of a function.
    Returns (primary_category, detail_dict)."""

    diff_indices = []
    for i in range(n):
        if orig_words[i] != decomp_words[i]:
            diff_indices.append(i)

    if not diff_indices:
        return "MATCH", {}

    # Classify each differing instruction
    cats = Counter()
    details = []
    for i in diff_indices:
        cat = classify_single_diff(orig_words[i], decomp_words[i])
        cats[cat] += 1
        details.append((i, cat, orig_words[i], decomp_words[i]))

    # Check for reordering: same set of instructions in different order
    if len(diff_indices) >= 2:
        orig_set = Counter(orig_words[i] for i in diff_indices)
        decomp_set = Counter(decomp_words[i] for i in diff_indices)
        if orig_set == decomp_set:
            # Check if this is epilogue reordering
            if diff_indices[-1] == n - 2 and is_ret(orig_words[n - 1]):
                o_last2 = (orig_words[n - 3], orig_words[n - 2])
                if is_ldp_x29_x30(o_last2[0]) or is_ldp_x29_x30(o_last2[1]):
                    return "EPILOGUE_ORDER", {"diffs": len(diff_indices), "details": details}

            # Check if prologue reordering
            if diff_indices[0] <= 2 and is_stp_x29_x30(orig_words[0]):
                return "PROLOGUE_ORDER", {"diffs": len(diff_indices), "details": details}

            return "INSN_REORDER", {"diffs": len(diff_indices), "details": details}

    # Check for x8 dispatch pattern: orig uses x8 as source but decomp uses x0
    has_x8_orig = False
    for i in range(min(3, n)):
        rn = get_rn(orig_words[i])
        if rn == 8:
            has_x8_orig = True
            break
    if has_x8_orig:
        # Check if decomp uses x0 where orig uses x8
        for i in diff_indices:
            if get_rn(orig_words[i]) == 8 and get_rn(decomp_words[i]) == 0:
                return "X8_DISPATCH", {"diffs": len(diff_indices), "details": details}

    # Primary category = most common non-PCREL category
    non_pcrel = {k: v for k, v in cats.items() if k != "PCREL"}
    if not non_pcrel:
        return "PCREL_ONLY", {"diffs": len(diff_indices), "details": details}

    primary = max(non_pcrel, key=non_pcrel.get)

    # If mixed, combine
    if len(non_pcrel) > 1:
        detail_str = "+".join(f"{k}({v})" for k, v in sorted(non_pcrel.items(), key=lambda x: -x[1]))
        return "MIXED:" + detail_str, {"diffs": len(diff_indices), "details": details, "cats": dict(cats)}

    if "PCREL" in cats and cats["PCREL"] > 0:
        return primary + "+PCREL", {"diffs": len(diff_indices), "details": details}

    return primary, {"diffs": len(diff_indices), "details": details}


def main():
    import argparse
    parser = argparse.ArgumentParser(description='Analyze register allocation divergences')
    parser.add_argument('--limit', type=int, default=0, help='Limit number of functions to analyze (0=all)')
    parser.add_argument('--verbose', '-v', action='store_true', help='Show per-function details')
    parser.add_argument('--category', '-c', type=str, help='Only show functions of this category')
    parser.add_argument('--output', '-o', type=str, help='Write results to CSV file')
    args = parser.parse_args()

    # Load CSV: build lookups by full mangled name AND short name
    csv_data = {}  # mangled_name -> (address, quality, size)
    csv_by_short = {}  # short_name -> (address, quality, size)
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            quality = row[1]
            size = int(row[2])
            name = row[3]
            csv_data[name] = (addr, quality, size)
            short = extract_func_name(name)
            if short and short not in csv_by_short:
                csv_by_short[short] = (addr, quality, size)

    # Scan all .o files in build/
    o_files = sorted(BUILD_DIR.glob("*.o"))
    if not o_files:
        print("No .o files found in build/")
        return

    print(f"Scanning {len(o_files)} object files...")

    orig_segs = load_elf_segments(ORIGINAL_ELF)
    results = []  # (func_name, category, num_insns, num_diffs, detail)
    skipped = 0

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for o_path in o_files:
            data = o_path.read_bytes()
            sections = parse_elf_sections(data)

            for mangled, (sec_off, sec_size) in sections.items():
                if sec_size < 4:
                    continue

                # Look up in CSV: try full mangled name first, then short name
                if mangled in csv_data:
                    addr, quality, csv_size = csv_data[mangled]
                else:
                    short_name = extract_func_name(mangled)
                    if short_name and short_name in csv_by_short:
                        addr, quality, csv_size = csv_by_short[short_name]
                    else:
                        skipped += 1
                        continue

                # Only analyze non-matching
                if quality != 'N':
                    continue

                # Read compiled bytes from .o section
                decomp_bytes = data[sec_off:sec_off + sec_size]

                # Read original bytes
                vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
                orig_bytes = read_elf_bytes(orig_f, orig_segs, vaddr, sec_size)

                if orig_bytes is None or len(orig_bytes) < sec_size:
                    skipped += 1
                    continue

                # Compare
                n = sec_size // 4
                orig_words = [struct.unpack_from('<I', orig_bytes, i * 4)[0] for i in range(n)]
                decomp_words = [struct.unpack_from('<I', decomp_bytes, i * 4)[0] for i in range(n)]

                cat, detail = classify_function(orig_words, decomp_words, n, args.verbose)

                if cat == "MATCH":
                    continue  # CSV says N but bytes match (maybe post-processing would fix it)

                display_name = extract_func_name(mangled) or mangled
                num_diffs = detail.get("diffs", 0)
                results.append((display_name, cat, n, num_diffs, detail))

                if args.limit and len(results) >= args.limit:
                    break

            if args.limit and len(results) >= args.limit:
                break

    # Summarize
    print(f"\nAnalyzed {len(results)} non-matching functions (skipped {skipped})")
    print()

    # Category counts
    cat_counts = Counter(r[1] for r in results)
    print("=" * 70)
    print(f"{'Category':<45} {'Count':>6} {'%':>6}")
    print("=" * 70)
    for cat, count in cat_counts.most_common():
        pct = 100 * count / len(results) if results else 0
        print(f"  {cat:<43} {count:>6} {pct:>5.1f}%")
    print(f"  {'TOTAL':<43} {len(results):>6}")
    print()

    # Detail per category
    if args.verbose:
        for cat in sorted(cat_counts.keys()):
            if args.category and args.category not in cat:
                continue
            print(f"\n--- {cat} ---")
            funcs = [r for r in results if r[1] == cat]
            for name, _, n_insns, n_diffs, detail in funcs[:20]:
                print(f"  {name}: {n_insns} insns, {n_diffs} diffs")
                if "details" in detail:
                    for idx, dcat, orig_w, decomp_w in detail["details"][:5]:
                        print(f"    [{idx:3d}] {dcat:<20} orig={orig_w:08x} decomp={decomp_w:08x}")
            if len(funcs) > 20:
                print(f"  ... and {len(funcs) - 20} more")

    if args.category:
        funcs = [r for r in results if args.category in r[1]]
        print(f"\nFunctions matching '{args.category}':")
        for name, cat, n_insns, n_diffs, detail in funcs:
            print(f"  {name}: {n_insns} insns, {n_diffs} diffs — {cat}")

    # Write CSV output if requested
    if args.output:
        with open(args.output, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['Function', 'Category', 'NumInsns', 'NumDiffs'])
            for name, cat, n_insns, n_diffs, _ in results:
                writer.writerow([name, cat, n_insns, n_diffs])
        print(f"\nWrote {len(results)} entries to {args.output}")


if __name__ == '__main__':
    main()
