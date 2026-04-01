#!/usr/bin/env python3
"""
Verify all compiled functions against the original 13.0.4 binary.

Reads the linked ELF's symbol table, maps each function to its original
address via data/functions.csv, and compares bytes instruction-by-instruction.

Usage:
    python tools/verify_all.py              # Full report
    python tools/verify_all.py --summary    # Summary only
    python tools/verify_all.py --update     # Update functions.csv with results
"""

import csv
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
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


def read_bytes(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None


def is_adrp(insn):
    """Check if a 32-bit AArch64 instruction is ADRP."""
    return (insn & 0x9F000000) == 0x90000000


def is_add_imm(insn):
    """Check if a 32-bit AArch64 instruction is ADD immediate."""
    return (insn & 0x7F800000) == 0x11000000


def insn_match_semantic(a, b):
    """Compare two instructions, treating ADRP/ADD-imm page offsets as equivalent."""
    if a == b:
        return True
    ai = struct.unpack('<I', a)[0]
    bi = struct.unpack('<I', b)[0]
    # ADRP: compare only Rd (bits 4:0), ignore page immediate
    if is_adrp(ai) and is_adrp(bi):
        return (ai & 0x1F) == (bi & 0x1F)
    # ADD immediate: compare Rd, Rn, shift — ignore imm12 (bits 21:10)
    if is_add_imm(ai) and is_add_imm(bi):
        mask = 0xFFC003FF  # keep sf, op, S, shift, Rn, Rd — mask out imm12
        return (ai & mask) == (bi & mask)
    return False


def get_decomp_symbols():
    """Get all function symbols from the decomp ELF."""
    result = subprocess.run(
        [OBJDUMP, "-t", str(DECOMP_ELF)],
        capture_output=True, text=True
    )
    symbols = []
    for line in result.stdout.split('\n'):
        if 'F .text' in line:
            parts = line.split()
            addr = int(parts[0], 16)
            size = int(parts[4], 16) if len(parts) > 4 else 0
            name = parts[-1] if parts else ''
            if size > 0 and name:
                symbols.append((name, addr, size))
    return symbols


def extract_func_name(mangled):
    """Extract the function name from an Itanium ABI mangled symbol.

    All our symbols are _ZN3app8lua_bind<len><name>E<params>.
    Parse the length-prefixed name directly — no demangler needed.
    """
    prefix = "_ZN3app8lua_bind"
    if not mangled.startswith(prefix):
        return None
    rest = mangled[len(prefix):]
    # Read decimal length prefix
    i = 0
    while i < len(rest) and rest[i].isdigit():
        i += 1
    if i == 0:
        return None
    length = int(rest[:i])
    name = rest[i:i + length]
    return name if len(name) == length else None


def build_csv_lookup():
    """Build name → (address, size) lookups from functions.csv (viking 4-column format).
    Returns dict mapping name → list of (addr, csv_size) tuples to handle duplicates."""
    lookup = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)  # skip header: Address,Quality,Size,Name
        for row in reader:
            addr = int(row[0], 16)
            csv_size = int(row[2])
            name = row[3]
            # Index by full name (may be mangled or short)
            lookup.setdefault(name, []).append((addr, csv_size))
            # Also index by short name extracted from mangled names
            if name.startswith('_ZN3app8lua_bind'):
                short = extract_func_name(name)
                if short:
                    lookup.setdefault(short, []).append((addr, csv_size))
    return lookup


def resolve_addr(csv_lookup, name, decomp_size):
    """Resolve the best matching address for a function name.
    Prefers exact size match, then smallest CSV entry."""
    entries = csv_lookup.get(name, [])
    if not entries:
        return None
    if len(entries) == 1:
        return entries[0][0]
    # Prefer entry whose size matches decomp
    for addr, csv_size in entries:
        if csv_size == decomp_size:
            return addr
    # Fallback: smallest entry (more likely to be the dispatcher)
    return min(entries, key=lambda e: e[1])[0]


def main():
    summary_only = '--summary' in sys.argv
    update_csv = '--update' in sys.argv

    # Get decomp symbols
    symbols = get_decomp_symbols()
    csv_lookup = build_csv_lookup()

    # Load ELF segments
    orig_segments = load_elf_segments(ORIGINAL_ELF)
    decomp_segments = load_elf_segments(DECOMP_ELF)

    perfect = 0
    semantic = 0  # matches when ignoring ADRP/ADD-imm relocations
    mismatch = 0
    unmatched = 0
    total_bytes_matched = 0
    total_bytes_compared = 0

    results = {}  # func_name -> (status, match_pct)
    details = []
    unmatched_names = []

    with open(ORIGINAL_ELF, 'rb') as orig_f, open(DECOMP_ELF, 'rb') as decomp_f:
        for mangled, decomp_addr, size in symbols:
            func_name = extract_func_name(mangled)

            # Prefer full mangled name match, then short name.
            # resolve_addr picks the CSV entry whose size best matches decomp.
            orig_addr = resolve_addr(csv_lookup, mangled, size)
            if orig_addr is None and func_name is not None:
                orig_addr = resolve_addr(csv_lookup, func_name, size)
            if orig_addr is None:
                unmatched += 1
                if not summary_only and func_name:
                    unmatched_names.append(func_name)
                continue

            # Convert Ghidra address to ELF vaddr
            orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr

            # Read both
            orig_bytes = read_bytes(orig_f, orig_segments, orig_vaddr, size)
            decomp_bytes = read_bytes(decomp_f, decomp_segments, decomp_addr, size)

            if orig_bytes is None or decomp_bytes is None:
                unmatched += 1
                if not summary_only:
                    unmatched_names.append(f"{func_name} (bad address {orig_addr:#x})")
                continue

            # Compare instruction by instruction (4 bytes each)
            num_insns = size // 4
            strict_count = 0
            semantic_count = 0
            for i in range(0, min(len(orig_bytes), len(decomp_bytes)), 4):
                a = orig_bytes[i:i+4]
                b = decomp_bytes[i:i+4]
                if a == b:
                    strict_count += 1
                    semantic_count += 1
                elif insn_match_semantic(a, b):
                    semantic_count += 1

            total_bytes_compared += size
            total_bytes_matched += strict_count * 4

            if strict_count == num_insns:
                perfect += 1
                status = 'M'
            elif semantic_count == num_insns:
                semantic += 1
                status = 'E'  # equivalent — differs only in relocations
            else:
                mismatch += 1
                status = 'N'
                if not summary_only:
                    details.append((func_name, strict_count, semantic_count, num_insns))

            results[func_name] = (status, strict_count * 100 // num_insns if num_insns else 0)

    total = perfect + semantic + mismatch
    total_funcs = len(symbols)

    print()
    print("=" * 70)
    print("  SSBU Decomp — Verified Binary Comparison (13.0.4)")
    print("=" * 70)
    print()
    print(f"  Total compiled functions:  {total_funcs}")
    print(f"  Matched to CSV address:    {total}")
    print(f"  Unmatched (no CSV entry):  {unmatched}")
    print()

    if total > 0:
        bar_w = 40
        pf = perfect * bar_w // total
        sm = semantic * bar_w // total
        mm = max(0, bar_w - pf - sm)
        bar = '#' * pf + '~' * sm + '-' * mm
        print(f"  [{bar}]")
        print()
        print(f"  BYTE-IDENTICAL:   {perfect:>5}  ({perfect*100/total:.1f}%)")
        print(f"  SEMANTIC MATCH:   {semantic:>5}  ({semantic*100/total:.1f}%)  (ADRP/ADD reloc only)")
        print(f"  Non-matching:     {mismatch:>5}  ({mismatch*100/total:.1f}%)")
        print(f"                    -----")
        print(f"  TOTAL MATCHING:   {perfect+semantic:>5}  ({(perfect+semantic)*100/total:.1f}%)")
        print()
        print(f"  Bytes: {total_bytes_matched:,} / {total_bytes_compared:,} strict match ({total_bytes_matched*100//total_bytes_compared}%)")
    print()

    if details and not summary_only:
        print("  Non-matching functions:")
        for name, sc, smc, tc in sorted(details, key=lambda x: -x[2]/x[3] if x[3] else 0)[:30]:
            pct = sc * 100 // tc if tc else 0
            print(f"    {name}: {sc}/{tc} strict, {smc}/{tc} semantic")
        if len(details) > 30:
            print(f"    ... and {len(details) - 30} more")

    if unmatched_names and not summary_only:
        print()
        print("  Unmatched symbols (no CSV entry):")
        for name in unmatched_names[:20]:
            print(f"    {name}")
        if len(unmatched_names) > 20:
            print(f"    ... and {len(unmatched_names) - 20} more")

    print()

    # Update CSV if requested
    if update_csv and results:
        rows = []
        with open(FUNCTIONS_CSV) as f:
            reader = csv.DictReader(f)
            fieldnames = reader.fieldnames
            for row in reader:
                name = row['Name']
                if name in results:
                    status, _ = results[name]
                    row['Status'] = status
                rows.append(row)
        with open(FUNCTIONS_CSV, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames, extrasaction='ignore')
            writer.writeheader()
            writer.writerows(rows)
        print(f"  Updated {len(results)} entries in functions.csv")


if __name__ == '__main__':
    main()
