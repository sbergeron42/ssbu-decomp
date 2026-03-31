#!/usr/bin/env python3
"""Show instruction-level diff between original and decomp for a function."""
import csv, struct, subprocess, sys, re
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

def decode_insn(word, pc):
    """Decode AArch64 instruction to a readable form (simplified)."""
    if (word >> 26) == 0x05:  # b imm26
        imm = word & 0x3ffffff
        if imm & 0x2000000: imm -= 0x4000000
        target = pc + imm * 4
        return f"b 0x{target:x}"
    if (word >> 26) == 0x25:  # bl imm26
        imm = word & 0x3ffffff
        if imm & 0x2000000: imm -= 0x4000000
        target = pc + imm * 4
        return f"bl 0x{target:x}"
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

func_name = sys.argv[1] if len(sys.argv) > 1 else None
if not func_name:
    print("Usage: python tools/show_diff.py <function_name>"); sys.exit(1)

# Find address in CSV
csv_addr = None
with open(FUNCTIONS_CSV) as f:
    reader = csv.reader(f); next(reader)
    for row in reader:
        name = row[3]
        short = extract_func_name(name) if name.startswith('_ZN3app8lua_bind') else name
        if short == func_name or name == func_name:
            csv_addr = int(row[0], 16); break

if csv_addr is None:
    print(f"Function {func_name} not found in CSV"); sys.exit(1)

orig_vaddr = csv_addr - ELF_BASE if csv_addr >= ELF_BASE else csv_addr

# Find decomp address and size
result = subprocess.run([OBJDUMP, "-t", str(DECOMP_ELF)], capture_output=True, text=True)
decomp_addr = None; size = 0
for line in result.stdout.split('\n'):
    if 'F .text' in line and func_name in line:
        parts = line.split()
        decomp_addr = int(parts[0], 16)
        size = int(parts[4], 16)
        break

if decomp_addr is None:
    print(f"Function {func_name} not found in decomp ELF"); sys.exit(1)

# Get CSV size info
csv_size = None
with open(FUNCTIONS_CSV) as f:
    reader = csv.reader(f); next(reader)
    for row in reader:
        if int(row[0], 16) == csv_addr:
            csv_size = int(row[2])
            break

print(f"Function: {func_name}")
print(f"Original: 0x{csv_addr:x} (vaddr 0x{orig_vaddr:x}), CSV size: {csv_size}")
print(f"Decomp:   0x{decomp_addr:x}, size: {size}")
print()

orig_segments = load_elf_segments(ORIGINAL_ELF)
decomp_segments = load_elf_segments(DECOMP_ELF)

with open(ORIGINAL_ELF, 'rb') as of, open(DECOMP_ELF, 'rb') as df:
    orig_bytes = read_bytes(of, orig_segments, orig_vaddr, size)
    decomp_bytes = read_bytes(df, decomp_segments, decomp_addr, size)

if orig_bytes is None or decomp_bytes is None:
    print("ERROR: Could not read bytes"); sys.exit(1)

num_insns = size // 4
matching = 0
print(f"{'#':>3} {'Orig':>10} {'Decomp':>10} {'Match':>5}  {'Orig Insn':30} {'Decomp Insn':30}")
print("-" * 100)
for i in range(num_insns):
    o = struct.unpack('<I', orig_bytes[i*4:(i+1)*4])[0]
    d = struct.unpack('<I', decomp_bytes[i*4:(i+1)*4])[0]
    match = "  OK" if o == d else " DIFF"
    if o == d: matching += 1

    orig_pc = orig_vaddr + i * 4
    decomp_pc = decomp_addr + i * 4
    oi = decode_insn(o, orig_pc) or f"0x{o:08x}"
    di = decode_insn(d, decomp_pc) or f"0x{d:08x}"

    print(f"{i:3} 0x{o:08x} 0x{d:08x} {match}  {oi:30} {di:30}")

print(f"\n{matching}/{num_insns} instructions match")
