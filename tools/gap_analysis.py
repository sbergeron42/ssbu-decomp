#!/usr/bin/env python3
"""
Gap analysis v4: Address-based, filtered to correctly-placed functions only.

Compares decomp ELF functions against original ELF, but ONLY for functions
whose decomp address matches a known CSV entry (meaning the linker placed
them at their original address).
"""
import csv, struct, subprocess, sys, re
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
ELF_BASE = 0x7100000000

def load_elf_segments(path):
    segments = []
    with open(path, 'rb') as f:
        f.seek(0x20); phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36); phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]; f.read(4)
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1: segments.append((p_vaddr, p_offset, p_filesz))
    return segments

def read_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv)); return f.read(size)
    return None

def extract_func_name(mangled):
    prefix = "_ZN3app8lua_bind"
    if not mangled.startswith(prefix): return None
    rest = mangled[len(prefix):]
    i = 0
    while i < len(rest) and rest[i].isdigit(): i += 1
    if i == 0: return None
    length = int(rest[:i])
    name = rest[i:i + length]
    return name if len(name) == length else None

def classify_insn_diff(ow, dw):
    """Classify a single instruction mismatch."""
    def itype(w):
        top6 = w >> 26
        if top6 == 0x05: return "b"
        if top6 == 0x25: return "bl"
        if (w & 0x9F000000) == 0x90000000: return "adrp"
        if (w & 0x9F000000) == 0x10000000: return "adr"
        if (w & 0x3B000000) == 0x18000000: return "ldr_lit"
        if (w & 0x7E000000) == 0x34000000: return "cbz"
        if (w & 0x7E000000) == 0x36000000: return "tbz"
        if (w & 0xFF000010) == 0x54000000: return "bcond"
        return "other"

    ot, dt = itype(ow), itype(dw)
    pcrel = {"b", "bl", "adrp", "adr", "ldr_lit", "cbz", "tbz", "bcond"}

    if ot == dt:
        if ot in ("b", "bl"):
            return "RELOC"
        if ot in ("adrp", "adr", "ldr_lit"):
            return "RELOC" if (ow & 0x1F) == (dw & 0x1F) else "REG_ALLOC"
        if ot in ("cbz", "tbz"):
            return "RELOC" if (ow & ~0x00FFFFE0) == (dw & ~0x00FFFFE0) else "REG_ALLOC"
        if ot == "bcond":
            return "RELOC" if (ow & 0xF) == (dw & 0xF) else "BRANCH_COND"

    if ot == "other" and dt == "other":
        # movz vs orr
        is_movz_o = (ow & 0x7F800000) == 0x52800000
        is_orr_o = (ow & 0x7F800000) == 0x32000000
        is_movz_d = (dw & 0x7F800000) == 0x52800000
        is_orr_d = (dw & 0x7F800000) == 0x32000000
        if (is_movz_o and is_orr_d) or (is_orr_o and is_movz_d):
            return "MOVZ_ORR"
        if (ow >> 21) == (dw >> 21):
            return "REG_ALLOC"
        return "CODEGEN_DIFF"

    if ot in pcrel or dt in pcrel:
        return "REORDER_WITH_BRANCH"
    return "CODEGEN_DIFF"

def check_prologue(ow, dw, n):
    if n < 3: return None
    plen = min(6, n)
    op, dp = ow[:plen], dw[:plen]
    if op == dp: return None
    if sorted(op) == sorted(dp): return "PROLOGUE_REORDER"
    return "PROLOGUE_DIFF"

def check_swap_pairs(ow, dw, n):
    mis = [i for i in range(n) if ow[i] != dw[i]]
    pairs = 0; visited = set()
    for i in mis:
        if i in visited: continue
        for j in range(i+1, min(i+5, n)):
            if j in visited or j not in mis: continue
            if ow[i] == dw[j] and ow[j] == dw[i]:
                pairs += 1; visited.add(i); visited.add(j); break
    return pairs

def main():
    # CSV: addr → (name, size, quality)
    csv_entries = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f); next(reader)
        for row in reader:
            addr = int(row[0], 16)
            csv_entries[addr] = (row[3], int(row[2]), row[1])

    # Decomp symbols
    result = subprocess.run([OBJDUMP, "-t", str(DECOMP_ELF)], capture_output=True, text=True)
    symbols = []
    for line in result.stdout.split('\n'):
        if 'F .text' in line:
            parts = line.split()
            addr = int(parts[0], 16)
            size = int(parts[4], 16) if len(parts) > 4 else 0
            name = parts[-1] if parts else ''
            if size > 0 and name:
                symbols.append((name, addr, size))

    orig_segs = load_elf_segments(ORIGINAL_ELF)
    decomp_segs = load_elf_segments(DECOMP_ELF)

    perfect = 0
    mismatches = []
    not_in_csv = 0
    size_differs = 0
    no_bytes = 0
    reloc_only_count = 0

    global_patterns = defaultdict(int)
    global_funcs = defaultdict(list)

    with open(ORIGINAL_ELF, 'rb') as of_, open(DECOMP_ELF, 'rb') as df_:
        for mangled, decomp_addr, decomp_size in symbols:
            # Only compare if this address is a known CSV entry
            if decomp_addr not in csv_entries:
                not_in_csv += 1
                continue

            csv_name, csv_size, csv_qual = csv_entries[decomp_addr]

            # Size sanity check
            if decomp_size != csv_size:
                size_differs += 1
                # Still compare — size difference IS a real mismatch

            orig_vaddr = decomp_addr - ELF_BASE if decomp_addr >= ELF_BASE else decomp_addr
            compare_size = min(decomp_size, csv_size)  # compare the smaller

            db = read_bytes(df_, decomp_segs, decomp_addr, compare_size)
            ob = read_bytes(of_, orig_segs, orig_vaddr, compare_size)
            if ob is None or db is None:
                no_bytes += 1; continue

            n = compare_size // 4
            if n == 0: continue
            ow = [struct.unpack('<I', ob[i*4:(i+1)*4])[0] for i in range(n)]
            dw = [struct.unpack('<I', db[i*4:(i+1)*4])[0] for i in range(n)]

            match_count = sum(1 for i in range(n) if ow[i] == dw[i])
            if match_count == n and decomp_size == csv_size:
                perfect += 1
                continue

            patterns = defaultdict(int)
            for i in range(n):
                if ow[i] != dw[i]:
                    patterns[classify_insn_diff(ow[i], dw[i])] += 1

            prologue = check_prologue(ow, dw, n)
            if prologue: patterns[prologue] = 1
            sp = check_swap_pairs(ow, dw, n)
            if sp: patterns["SWAP_PAIRS"] = sp
            if decomp_size != csv_size:
                patterns["SIZE_DIFF"] = abs(decomp_size - csv_size)

            # Determine category
            non_meta = {k: v for k, v in patterns.items()
                       if k not in ("PROLOGUE_REORDER", "PROLOGUE_DIFF", "SWAP_PAIRS", "SIZE_DIFF")}
            if non_meta:
                dominant = max(non_meta, key=non_meta.get)
            elif "SIZE_DIFF" in patterns:
                dominant = "SIZE_DIFF"
            else:
                dominant = "PROLOGUE_ONLY"

            # Check if reloc-only (all diffs are RELOC)
            real_diffs = {k: v for k, v in non_meta.items() if k != "RELOC"}
            is_reloc_only = (not real_diffs) and ("SIZE_DIFF" not in patterns)
            if is_reloc_only:
                reloc_only_count += 1
                dominant = "RELOC_ONLY"

            for pat, count in patterns.items():
                if pat not in ("PROLOGUE_REORDER", "PROLOGUE_DIFF", "SWAP_PAIRS", "SIZE_DIFF"):
                    global_patterns[pat] += count
                    global_funcs[pat].append(csv_name)

            mismatches.append({
                "name": csv_name,
                "addr": decomp_addr,
                "size_decomp": decomp_size,
                "size_orig": csv_size,
                "n": n,
                "match": match_count,
                "diff": n - match_count,
                "pct": match_count * 100 // n if n else 0,
                "patterns": dict(patterns),
                "dominant": dominant,
                "qual": csv_qual,
            })

    print("=" * 80)
    print("GAP ANALYSIS v4: Correctly-Placed Functions Only")
    print("=" * 80)
    print(f"\nTotal decomp symbols:      {len(symbols)}")
    print(f"At known CSV address:      {len(symbols) - not_in_csv}")
    print(f"At unknown address (skip): {not_in_csv}")
    print(f"No bytes readable:         {no_bytes}")
    print(f"Perfect match:             {perfect}")
    print(f"Non-matching:              {len(mismatches)}")
    print(f"  of which reloc-only:     {reloc_only_count}")
    print(f"  of which size differs:   {size_differs}")
    print(f"Real codegen mismatches:   {len(mismatches) - reloc_only_count}")

    # By dominant pattern
    dominant_groups = defaultdict(list)
    for m in mismatches:
        dominant_groups[m["dominant"]].append(m)

    print()
    print("=" * 80)
    print("PATTERN BREAKDOWN")
    print("=" * 80)
    for pat in sorted(dominant_groups, key=lambda p: len(dominant_groups[p]), reverse=True):
        funcs = dominant_groups[pat]
        total_diff = sum(f["diff"] for f in funcs)
        print(f"\n  {pat}: {len(funcs)} functions, {total_diff} differing instructions")
        # Show a few examples
        for fr in sorted(funcs, key=lambda x: x["diff"])[:5]:
            pats = ", ".join(f"{k}={v}" for k, v in sorted(fr["patterns"].items()))
            sz = f" SIZE:{fr['size_decomp']}vs{fr['size_orig']}" if fr['size_decomp'] != fr['size_orig'] else ""
            print(f"    {fr['name']}: {fr['match']}/{fr['n']} ({fr['pct']}%)  [{pats}]{sz}")
        if len(funcs) > 5:
            # Show distribution of diff counts
            diffs = sorted(f["diff"] for f in funcs)
            print(f"    ... and {len(funcs) - 5} more (diff range: {diffs[0]}-{diffs[-1]})")

    print()
    print("=" * 80)
    print("GLOBAL INSTRUCTION-LEVEL COUNTS (excluding prologue/meta)")
    print("=" * 80)
    total_insns = sum(v for v in global_patterns.values())
    for pat in sorted(global_patterns, key=global_patterns.get, reverse=True):
        cnt = global_patterns[pat]
        nfuncs = len(set(global_funcs[pat]))
        pct = cnt * 100 // total_insns if total_insns else 0
        print(f"  {pat:25s}: {cnt:6d} insns  {nfuncs:4d} funcs  ({pct:2d}%)")

    print()
    print("=" * 80)
    print("RELOC-ONLY FUNCTIONS (matchable with just linker script fix)")
    print("=" * 80)
    reloc_funcs = dominant_groups.get("RELOC_ONLY", [])
    for fr in sorted(reloc_funcs, key=lambda x: x["name"])[:30]:
        pats = ", ".join(f"{k}={v}" for k, v in sorted(fr["patterns"].items()))
        print(f"  {fr['name']}: {fr['match']}/{fr['n']} ({fr['pct']}%)  [{pats}]")
    if len(reloc_funcs) > 30:
        print(f"  ... and {len(reloc_funcs) - 30} more")

    print()
    print("=" * 80)
    print("MOVZ/ORR PATTERN (fixable with fix_orr_movz.py)")
    print("=" * 80)
    movz_funcs = [m for m in mismatches if "MOVZ_ORR" in m["patterns"]]
    for fr in sorted(movz_funcs, key=lambda x: x["name"]):
        print(f"  {fr['name']}: {fr['patterns'].get('MOVZ_ORR',0)} MOVZ_ORR diffs")

    # Summary actionable items
    print()
    print("=" * 80)
    print("ACTIONABLE SUMMARY")
    print("=" * 80)
    print(f"  1. SIZE_DIFF:   {size_differs} funcs -- decomp compiles to wrong size")
    print(f"  2. RELOC_ONLY:  {reloc_only_count} funcs -- fix linker script -> instant M")
    print(f"  3. MOVZ_ORR:    {len(movz_funcs)} funcs -- apply fix_orr_movz.py post-processing")
    print(f"  4. PROLOGUE:    {len([m for m in mismatches if 'PROLOGUE_REORDER' in m['patterns']])} funcs have reorderable prologues")
    print(f"  5. SWAP_PAIRS:  {len([m for m in mismatches if 'SWAP_PAIRS' in m['patterns']])} funcs have adjacent-swap pairs")
    print(f"  6. REG_ALLOC:   {global_patterns.get('REG_ALLOC',0)} insns -- compiler register choice")
    print(f"  7. CODEGEN_DIFF:{global_patterns.get('CODEGEN_DIFF',0)} insns -- source-level fixes needed")

    # SIZE_DIFF breakdown
    print()
    print("=" * 80)
    print("SIZE_DIFF BREAKDOWN")
    print("=" * 80)
    size_diff_funcs = [m for m in mismatches if "SIZE_DIFF" in m["patterns"]]
    shorter = [m for m in size_diff_funcs if m["size_decomp"] < m["size_orig"]]
    longer = [m for m in size_diff_funcs if m["size_decomp"] > m["size_orig"]]
    same_but_diff = [m for m in size_diff_funcs if m["size_decomp"] == m["size_orig"]]
    bytes_match_fully = [m for m in size_diff_funcs if m["diff"] == 0]
    print(f"  Decomp shorter than original: {len(shorter)}")
    print(f"  Decomp longer than original:  {len(longer)}")
    print(f"  Overlapping bytes all match:  {len(bytes_match_fully)}")
    print(f"  Overlapping bytes differ:     {len(size_diff_funcs) - len(bytes_match_fully)}")


if __name__ == "__main__":
    main()
