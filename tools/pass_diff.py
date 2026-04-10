#!/usr/bin/env python3
"""
Pass-level differential analysis for NX Clang divergences.

Compiles a source file with -print-after-all to dump MachineIR after every
pass, then compares the final assembly against the original NX binary to
identify which pass introduced each divergence.

Usage:
    python tools/pass_diff.py src/app/FighterManager.cpp FUN_7100154c60
    python tools/pass_diff.py --disasm FUN_7103441ae0  # Just show orig vs decomp
    python tools/pass_diff.py --passes src/app/fighter_status.cpp FUN_710007c310
"""

import argparse
import csv
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"

CLANG = os.environ.get("DECOMP_CLANG",
                       r"C:\llvm-8.0.0-custom\bin\clang++.exe")
CFLAGS_BASE = (
    "-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 "
    "-fno-exceptions -fno-rtti -ffunction-sections -fdata-sections "
    "-fno-common -fno-short-enums -fPIC -mno-implicit-float "
    "-fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG "
    "-Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs "
    "-mllvm -aarch64-nx-prologue"
)


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


def load_csv():
    lookup = {}
    with open(FUNCTIONS_CSV) as f:
        for row in csv.DictReader(f):
            addr = int(row['Address'], 16)
            size = int(row['Size'])
            name = row['Name']
            lookup[name] = (addr, size)
    return lookup


def find_function_addr(func_name, csv_lookup):
    """Find a function's address and size by name or address pattern."""
    # Direct match
    if func_name in csv_lookup:
        return csv_lookup[func_name]
    # FUN_XXXX pattern → extract address
    if func_name.startswith("FUN_"):
        try:
            addr = int(func_name[4:], 16)
            for name, (a, s) in csv_lookup.items():
                if a == addr:
                    return (a, s)
        except ValueError:
            pass
    # Short name search
    for name, (a, s) in csv_lookup.items():
        if name.endswith(func_name) or func_name in name:
            return (a, s)
    return None


def find_function_source(func_name, csv_lookup):
    """Try to find which source file contains a function."""
    # Look through .o files for a matching section
    for o_path in BUILD_DIR.glob("*.o"):
        r = subprocess.run(
            [OBJDUMP, "-t", str(o_path)],
            capture_output=True, text=True, timeout=10
        )
        if func_name in r.stdout:
            # Extract source file name from .o filename
            return o_path.stem
    return None


# ─── Disassembly helpers ──────────────────────────────────────────────

def disasm_bytes(raw_bytes, base_addr=0):
    """Disassemble raw AArch64 bytes into instruction list."""
    insns = []
    for i in range(0, len(raw_bytes), 4):
        word = struct.unpack_from('<I', raw_bytes, i)[0]
        insns.append((base_addr + i, word))
    return insns


def disasm_o_function(o_path, func_name):
    """Disassemble a specific function from a .o file using llvm-objdump."""
    r = subprocess.run(
        [OBJDUMP, "-d", str(o_path)],
        capture_output=True, text=True, timeout=30
    )
    lines = r.stdout.split('\n')
    in_func = False
    insns = []
    for line in lines:
        if func_name in line and ':' in line and 'Disassembly' not in line:
            # Check if this is a section header like "0000000 <func>:"
            in_func = True
            continue
        if in_func:
            if line.strip() == '' or 'Disassembly of section' in line:
                if insns:
                    break
                in_func = False
                continue
            # Parse instruction line: "       0:       encoding        mnemonic"
            m = re.match(r'\s+([0-9a-f]+):\s+([0-9a-f]+)\s+(.*)', line)
            if m:
                offset = int(m.group(1), 16)
                encoding = int(m.group(2), 16)
                mnemonic = m.group(3).strip()
                insns.append((offset, encoding, mnemonic))
    return insns


def format_insn(word):
    """Basic AArch64 instruction classifier for display."""
    # This is simplified — use objdump for full disassembly
    top8 = (word >> 24) & 0xFF
    if word == 0xd65f03c0:
        return "ret"
    if (word & 0x7FE0FFE0) == 0x2A0003E0:
        rd = word & 0x1F
        rm = (word >> 16) & 0x1F
        sf = (word >> 31) & 1
        w = "x" if sf else "w"
        return f"mov {w}{rd}, {w}{rm}"
    if (word & 0xFFE0FFE0) == 0xAA0003E0 or (word & 0xFFE0FFE0) == 0x2A0003E0:
        rd = word & 0x1F
        rm = (word >> 16) & 0x1F
        sf = (word >> 31) & 1
        w = "x" if sf else "w"
        return f"mov {w}{rd}, {w}{rm}"
    return f"<{word:08x}>"


# ─── Pass analysis ────────────────────────────────────────────────────

def compile_with_pass_dumps(src_file, extra_flags=""):
    """Compile with -print-after-all and return the output."""
    o_path = BUILD_DIR / "pass_diff_test.o"
    cmd = '%s %s %s -mllvm -print-after-all -c "%s" -o "%s"' % (
        CLANG, CFLAGS_BASE, extra_flags, src_file, o_path)
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True,
                      cwd=str(PROJECT_ROOT), timeout=120)
    return r.stderr, o_path  # -print-after-all goes to stderr


def parse_pass_dumps(dump_text, func_name):
    """Parse -print-after-all output to extract per-pass MachineIR for a function.
    Returns list of (pass_name, machine_ir_text)."""
    passes = []
    current_pass = None
    current_func = None
    current_lines = []
    in_func = False

    for line in dump_text.split('\n'):
        # Detect pass header: "# *** IR Dump After PASSNAME ***:"
        m = re.match(r'# \*\*\* IR Dump After (.+?) \*\*\*', line)
        if not m:
            m = re.match(r'\*\*\* IR Dump After (.+?) \*\*\*', line)
        if m:
            if current_pass and current_lines and in_func:
                passes.append((current_pass, '\n'.join(current_lines)))
            current_pass = m.group(1).strip()
            current_lines = []
            in_func = False
            continue

        # Detect function header: "# Machine code for function XXXX:"
        if 'Machine code for function' in line and func_name in line:
            in_func = True
            current_lines = [line]
            continue

        # Detect end of function
        if in_func and line.startswith('# End machine code for function'):
            current_lines.append(line)
            if current_pass:
                passes.append((current_pass, '\n'.join(current_lines)))
            in_func = False
            continue

        if in_func:
            current_lines.append(line)

    return passes


def extract_mir_instructions(mir_text):
    """Extract machine instructions from MachineIR dump text.
    Returns list of instruction strings (simplified)."""
    insns = []
    for line in mir_text.split('\n'):
        line = line.strip()
        # Skip comments, labels, etc.
        if not line or line.startswith('#') or line.startswith(';'):
            continue
        if line.startswith('bb.') or line.startswith('BB#'):
            insns.append(line)  # basic block headers
            continue
        # Machine instruction lines typically contain register defs
        if any(x in line for x in ['$', 'killed', 'dead', 'renamable',
                                     'frame-setup', 'frame-destroy']):
            # Clean up for readability
            clean = re.sub(r'\s+', ' ', line)
            insns.append(clean)
    return insns


# ─── Main commands ────────────────────────────────────────────────────

def cmd_disasm(func_name, csv_lookup):
    """Show side-by-side disassembly of original vs decomp."""
    result = find_function_addr(func_name, csv_lookup)
    if not result:
        print(f"Function {func_name} not found in CSV")
        return

    addr, size = result
    print(f"Function: {func_name}")
    print(f"Address:  0x{addr:x}")
    print(f"Size:     {size} bytes ({size // 4} instructions)")
    print()

    # Read original bytes
    segments = load_elf_segments(str(ORIGINAL_ELF))
    with open(ORIGINAL_ELF, 'rb') as f:
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
        orig_bytes = read_bytes_at(f, segments, vaddr, size)

    if not orig_bytes:
        print("Could not read original bytes")
        return

    # Find the .o file containing this function
    decomp_bytes = None
    for o_path in BUILD_DIR.glob("*.o"):
        data = o_path.read_bytes()
        if b'\x7fELF' != data[:4]:
            continue
        # Quick search for the function name in the file
        if func_name.encode() not in data:
            continue
        # Parse sections to find the function
        try:
            shoff = struct.unpack_from('<Q', data, 0x28)[0]
            shentsize = struct.unpack_from('<H', data, 0x3a)[0]
            shnum = struct.unpack_from('<H', data, 0x3c)[0]
            shstrndx = struct.unpack_from('<H', data, 0x3e)[0]
            str_off = struct.unpack_from('<Q', data, shoff + shstrndx * shentsize + 0x18)[0]
            str_sz = struct.unpack_from('<Q', data, shoff + shstrndx * shentsize + 0x20)[0]
            strtab = data[str_off:str_off + str_sz]
            for i in range(shnum):
                base = shoff + i * shentsize
                sh_name_off = struct.unpack_from('<I', data, base)[0]
                sh_type = struct.unpack_from('<I', data, base + 4)[0]
                end = strtab.index(b'\0', sh_name_off)
                sec_name = strtab[sh_name_off:end].decode('ascii', errors='replace')
                if func_name in sec_name and sh_type == 1:
                    sh_offset = struct.unpack_from('<Q', data, base + 0x18)[0]
                    sh_size = struct.unpack_from('<Q', data, base + 0x20)[0]
                    if sh_size == size:
                        decomp_bytes = data[sh_offset:sh_offset + sh_size]
                        print(f"Found in: {o_path.name}")
                        break
        except Exception:
            continue
        if decomp_bytes:
            break

    if not decomp_bytes:
        print("Could not find decomp bytes in any .o file")
        print("(The function may not be compiled, or name doesn't match)")
        return

    # Side-by-side comparison
    n = size // 4
    print(f"{'Off':>4}  {'Original':>10}  {'Decomp':>10}  {'Match':^5}  Note")
    print("-" * 70)
    diff_count = 0
    for i in range(n):
        orig_w = struct.unpack_from('<I', orig_bytes, i * 4)[0]
        decomp_w = struct.unpack_from('<I', decomp_bytes, i * 4)[0]
        match = orig_w == decomp_w
        if not match:
            diff_count += 1

        # Classify the difference
        note = ""
        if not match:
            # Check if only PC-relative (branch/adrp)
            if (orig_w >> 26) == (decomp_w >> 26):
                top6 = orig_w >> 26
                if top6 in (0x05, 0x25):  # b, bl
                    note = "BRANCH (PC-rel)"
                elif (orig_w & 0x9F000000) == 0x90000000:  # adrp
                    note = "ADRP (PC-rel)"
            # Check if just register difference
            if not note:
                xor = orig_w ^ decomp_w
                if xor & 0x1F and not (xor & ~0x1F):
                    note = "Rd differs"
                elif (xor >> 5) & 0x1F and not (xor & ~(0x1F << 5)):
                    note = "Rn differs"
                elif (xor >> 16) & 0x1F and not (xor & ~(0x1F << 16)):
                    note = "Rm differs"
            # Check width bit (bit 31)
            if not note and (orig_w ^ decomp_w) == 0x80000000:
                note = "WIDTH (32/64-bit)"
            # Check movz vs orr
            if not note:
                if (orig_w & 0xFF800000) in (0x52800000, 0xD2800000) and \
                   (decomp_w & 0xFFC00000) in (0x32000000, 0xB2000000):
                    note = "MOVZ vs ORR"
                elif (decomp_w & 0xFF800000) in (0x52800000, 0xD2800000) and \
                     (orig_w & 0xFFC00000) in (0x32000000, 0xB2000000):
                    note = "ORR vs MOVZ"

        marker = "  " if match else ">>"
        print(f"{i*4:4x}  {orig_w:08x}    {decomp_w:08x}    {marker:^5}  {note}")

    print()
    print(f"Total: {n} instructions, {diff_count} differences")


def cmd_passes(src_file, func_name, csv_lookup):
    """Compile with -print-after-all and show per-pass MIR for a function."""
    print(f"Compiling {src_file} with -print-after-all...")
    dump_text, o_path = compile_with_pass_dumps(src_file)

    # Find the function's mangled name by searching the dump
    # The func_name might be a short name; we need the mangled version
    candidates = set()
    for line in dump_text.split('\n'):
        if 'Machine code for function' in line and func_name in line:
            m = re.search(r'function (\S+):', line)
            if m:
                candidates.add(m.group(1))

    if not candidates:
        print(f"Function '{func_name}' not found in pass dumps.")
        print("(Try using the mangled C++ name)")
        return

    mangled = sorted(candidates)[0]
    if len(candidates) > 1:
        print(f"Multiple matches: {candidates}")
    print(f"Using mangled name: {mangled}")
    print()

    passes = parse_pass_dumps(dump_text, mangled)
    if not passes:
        print("No pass data found for this function.")
        return

    print(f"Found {len(passes)} pass dumps for {mangled}")
    print()

    # Show summary: pass name, instruction count, key changes
    prev_insns = None
    for pass_name, mir_text in passes:
        insns = extract_mir_instructions(mir_text)
        n_insns = len([i for i in insns if not i.startswith('bb.')])

        if prev_insns is not None:
            # Count changes from previous pass
            added = len(insns) - len(prev_insns)
            changed = sum(1 for a, b in zip(insns, prev_insns) if a != b)
            if changed > 0 or added != 0:
                print(f"  [{n_insns:3d} insns] {pass_name}  (+{changed} changed, {added:+d} size)")
            else:
                print(f"  [{n_insns:3d} insns] {pass_name}")
        else:
            print(f"  [{n_insns:3d} insns] {pass_name}")

        prev_insns = insns

    # Show the final MIR
    if passes:
        print()
        print(f"=== Final MIR after: {passes[-1][0]} ===")
        final_insns = extract_mir_instructions(passes[-1][1])
        for insn in final_insns:
            print(f"  {insn}")


def main():
    parser = argparse.ArgumentParser(description='Pass-level differential analysis')
    parser.add_argument('src', nargs='?', help='Source file to compile')
    parser.add_argument('func', help='Function name or FUN_XXXX address')
    parser.add_argument('--disasm', action='store_true',
                       help='Just show orig vs decomp disassembly')
    parser.add_argument('--passes', action='store_true',
                       help='Show per-pass MachineIR progression')
    args = parser.parse_args()

    csv_lookup = load_csv()

    if args.disasm:
        cmd_disasm(args.func, csv_lookup)
    elif args.passes and args.src:
        cmd_passes(args.src, args.func, csv_lookup)
    elif args.src:
        # Default: disasm first, then passes if source provided
        cmd_disasm(args.func, csv_lookup)
    else:
        cmd_disasm(args.func, csv_lookup)


if __name__ == '__main__':
    main()
