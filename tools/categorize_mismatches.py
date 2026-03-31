#!/usr/bin/env python3
"""Categorize non-matching functions by mismatch type."""
import csv, struct, subprocess, sys
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

def is_branch(word):
    """Check if instruction is b or bl (PC-relative)."""
    top6 = word >> 26
    return top6 == 0x05 or top6 == 0x25  # b or bl

def is_adrp(word):
    """Check if instruction is adrp (PC-relative page)."""
    return (word & 0x9F000000) == 0x90000000

def is_pcrel(word):
    """Check if instruction uses PC-relative addressing."""
    return is_branch(word) or is_adrp(word)

def classify_mismatch(orig_words, decomp_words, n):
    """Classify the type of mismatch."""
    mismatches = []
    for i in range(n):
        if orig_words[i] != decomp_words[i]:
            mismatches.append(i)

    if not mismatches:
        return "MATCH", mismatches

    # Check if all mismatches are PC-relative instructions
    all_pcrel = True
    has_pcrel = False
    has_codegen = False

    for i in mismatches:
        o = orig_words[i]
        d = decomp_words[i]
        o_pcrel = is_pcrel(o)
        d_pcrel = is_pcrel(d)

        if o_pcrel or d_pcrel:
            has_pcrel = True
            # Check if it's the SAME type of instruction with different offset
            if is_branch(o) and is_branch(d) and (o >> 26) == (d >> 26):
                continue  # Same branch type, just different offset
            elif is_adrp(o) and is_adrp(d):
                continue  # Same adrp, different page
            elif is_adrp(o) or is_adrp(d):
                # One is adrp, other is not - could be paired ldr difference
                all_pcrel = False
                has_codegen = True
            else:
                all_pcrel = False
                has_codegen = True
        else:
            all_pcrel = False
            has_codegen = True

    if all_pcrel and not has_codegen:
        return "PCREL_ONLY", mismatches
    elif has_pcrel and has_codegen:
        return "MIXED", mismatches
    else:
        return "CODEGEN", mismatches

# Load CSV
csv_lookup = {}
with open(FUNCTIONS_CSV) as f:
    reader = csv.reader(f); next(reader)
    for row in reader:
        addr = int(row[0], 16)
        name = row[3]
        if name not in csv_lookup: csv_lookup[name] = addr
        short = extract_func_name(name)
        if short and short not in csv_lookup: csv_lookup[short] = addr

# Get decomp symbols
result = subprocess.run([OBJDUMP, "-t", str(DECOMP_ELF)], capture_output=True, text=True)
symbols = []
for line in result.stdout.split('\n'):
    if 'F .text' in line:
        parts = line.split()
        addr = int(parts[0], 16)
        size = int(parts[4], 16) if len(parts) > 4 else 0
        name = parts[-1] if parts else ''
        if size > 0 and name:
            fn = extract_func_name(name)
            if fn: symbols.append((name, fn, addr, size))

orig_segs = load_elf_segments(ORIGINAL_ELF)
decomp_segs = load_elf_segments(DECOMP_ELF)

pcrel_only = []
codegen = []
mixed = []

with open(ORIGINAL_ELF, 'rb') as of_, open(DECOMP_ELF, 'rb') as df_:
    for mangled, func_name, decomp_addr, size in symbols:
        if func_name not in csv_lookup: continue
        orig_addr = csv_lookup[func_name]
        orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr

        ob = read_bytes(of_, orig_segs, orig_vaddr, size)
        db = read_bytes(df_, decomp_segs, decomp_addr, size)
        if ob is None or db is None: continue

        n = size // 4
        ow = [struct.unpack('<I', ob[i*4:(i+1)*4])[0] for i in range(n)]
        dw = [struct.unpack('<I', db[i*4:(i+1)*4])[0] for i in range(n)]

        match_count = sum(1 for i in range(n) if ow[i] == dw[i])
        if match_count == n: continue

        cat, mis = classify_mismatch(ow, dw, n)
        entry = (func_name, match_count, n, mis)
        if cat == "PCREL_ONLY": pcrel_only.append(entry)
        elif cat == "CODEGEN": codegen.append(entry)
        elif cat == "MIXED": mixed.append(entry)

print("=" * 70)
print(f"PCREL_ONLY (fixable with linker script): {len(pcrel_only)}")
print("=" * 70)
for name, mc, tc, _ in sorted(pcrel_only, key=lambda x: x[0]):
    print(f"  {name}: {mc}/{tc}")

print()
print("=" * 70)
print(f"CODEGEN (fixable with source changes): {len(codegen)}")
print("=" * 70)
for name, mc, tc, _ in sorted(codegen, key=lambda x: x[0]):
    print(f"  {name}: {mc}/{tc}")

print()
print("=" * 70)
print(f"MIXED (needs both): {len(mixed)}")
print("=" * 70)
for name, mc, tc, _ in sorted(mixed, key=lambda x: x[0]):
    print(f"  {name}: {mc}/{tc}")

print(f"\nTotal: {len(pcrel_only) + len(codegen) + len(mixed)}")
