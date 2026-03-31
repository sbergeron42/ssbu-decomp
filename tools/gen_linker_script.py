#!/usr/bin/env python3
"""
Generate a linker script that places decomped functions at their original addresses
and defines external symbols at their correct addresses.

This enables byte-matching for functions with PC-relative branches (b/bl) to external
targets and adrp references to global data.
"""
import csv
import re
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000


def extract_func_name(mangled):
    prefix = "_ZN3app8lua_bind"
    if not mangled.startswith(prefix):
        return None
    rest = mangled[len(prefix):]
    i = 0
    while i < len(rest) and rest[i].isdigit():
        i += 1
    if i == 0:
        return None
    length = int(rest[:i])
    name = rest[i:i + length]
    return name if len(name) == length else None


def main():
    # Build CSV lookup: short_name -> original address
    csv_lookup = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            name = row[3]
            short = extract_func_name(name) if name.startswith('_ZN3app8lua_bind') else name
            if short:
                csv_lookup[short] = addr

    # Get defined symbols from all .o files to find mangled names
    obj_files = list(BUILD_DIR.glob("*.o"))
    func_sections = {}  # mangled_name -> (short_name, original_addr)

    for obj in obj_files:
        result = subprocess.run([OBJDUMP, "-t", str(obj)], capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'F .text' in line:
                parts = line.split()
                mangled = parts[-1]
                short = extract_func_name(mangled)
                if short and short in csv_lookup:
                    func_sections[mangled] = (short, csv_lookup[short])

    # Get undefined symbols from all .o files
    undefined = set()
    for obj in obj_files:
        result = subprocess.run([OBJDUMP, "-t", str(obj)], capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if '*UND*' in line:
                parts = line.split()
                if parts:
                    sym = parts[-1]
                    if sym not in func_sections:  # Only truly external
                        undefined.add(sym)

    # Generate linker script
    out = PROJECT_ROOT / "build" / "decomp.ld"

    lines = []
    lines.append("/* Auto-generated linker script for SSBU decomp */")
    lines.append("/* Places functions at original addresses for byte-matching */")
    lines.append("")

    # Define external symbols at their original addresses
    lines.append("/* External symbol definitions */")
    for sym in sorted(undefined):
        # Extract address from symbol name
        m = re.match(r'(FUN|DAT|PTR_DAT)_([0-9a-fA-F]+)', sym)
        if m:
            addr = int(m.group(2), 16)
            lines.append(f"PROVIDE({sym} = 0x{addr:x});")

    lines.append("")
    lines.append("SECTIONS {")

    # Sort functions by original address
    sorted_funcs = sorted(func_sections.items(), key=lambda x: x[1][1])

    for mangled, (short, orig_addr) in sorted_funcs:
        section_name = f".text.{mangled}"
        lines.append(f"  /* {short} */")
        lines.append(f"  . = 0x{orig_addr:x};")
        lines.append(f"  {section_name} : {{ *({section_name}) }}")

    # Catch-all for remaining sections
    lines.append("")
    lines.append("  /* Remaining sections */")
    lines.append("  .text : { *(.text .text.*) }")
    lines.append("  .rodata : { *(.rodata .rodata.*) }")
    lines.append("  .data : { *(.data .data.*) }")
    lines.append("  .bss : { *(.bss .bss.*) }")
    lines.append("  /DISCARD/ : { *(.comment) *(.note*) *(.eh_frame*) }")
    lines.append("}")

    with open(out, 'w') as f:
        f.write('\n'.join(lines) + '\n')

    print(f"Generated {out}")
    print(f"  {len(func_sections)} function sections placed at original addresses")
    print(f"  {len([s for s in undefined if re.match(r'(FUN|DAT|PTR_DAT)_', s)])} external symbols defined")
    print(f"  {len(undefined)} total undefined symbols")

    return str(out)


if __name__ == '__main__':
    main()
