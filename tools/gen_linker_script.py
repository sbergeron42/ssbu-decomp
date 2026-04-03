#!/usr/bin/env python3
"""
Generate a linker script that places decomped functions at their original addresses
and defines external symbols at their correct addresses.

This enables byte-matching for functions with PC-relative branches (b/bl) to external
targets and adrp references to global data.
"""
import csv
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000


def extract_short_name(mangled):
    """Extract the short function name from any Itanium ABI mangled symbol."""
    if not mangled.startswith('_Z'):
        return mangled
    prefix = "_ZN3app8lua_bind"
    if mangled.startswith(prefix):
        rest = mangled[len(prefix):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i > 0:
            length = int(rest[:i])
            name = rest[i:i + length]
            if len(name) == length:
                return name
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
    rest = mangled[2:]
    i = 0
    while i < len(rest) and rest[i].isdigit():
        i += 1
    if i > 0:
        length = int(rest[:i])
        name = rest[i:i + length]
        if len(name) == length:
            return name
    return mangled


def build_csv_lookup():
    """Build name -> list of (address, size) from functions.csv."""
    lookup = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            csv_size = int(row[2])
            name = row[3]
            lookup.setdefault(name, []).append((addr, csv_size))
            short = extract_short_name(name)
            if short != name:
                lookup.setdefault(short, []).append((addr, csv_size))
    return lookup


def build_source_addr_map():
    """Parse source files for address comments preceding function defs."""
    addr_map = {}
    src_dir = PROJECT_ROOT / "src"
    for root, dirs, files in os.walk(src_dir):
        for fn in files:
            if not fn.endswith('.cpp'):
                continue
            path = os.path.join(root, fn)
            with open(path, encoding='utf-8', errors='replace') as f:
                lines = f.readlines()
            for i, line in enumerate(lines):
                m = re.search(r'//\s*(?:0x)?(71[0-9a-fA-F]{6,10})\b', line)
                if m:
                    addr = int(m.group(1), 16)
                    for j in range(i + 1, min(i + 3, len(lines))):
                        fm = re.match(
                            r'(?:void\*?|bool|u8|u16|u32|u64|s8|s16|s32|s64|'
                            r'int|float|double|long|unsigned|char|f32|f64|'
                            r'struct\s+\w+\*?)\s+(\w+)\s*\(',
                            lines[j]
                        )
                        if fm:
                            addr_map[fm.group(1)] = addr
                            break
    return addr_map


def resolve_addr(csv_lookup, source_addr_map, mangled, short_name, decomp_size):
    """Resolve the original address and CSV size for a compiled function.
    Returns (addr, csv_size) or (None, 0)."""
    for name in [mangled, short_name]:
        if not name:
            continue
        entries = csv_lookup.get(name)
        if entries:
            if len(entries) == 1:
                return entries[0]
            for addr, csv_size in entries:
                if csv_size == decomp_size:
                    return (addr, csv_size)
            best = min(entries, key=lambda e: e[1])
            return best
    if short_name and short_name in source_addr_map:
        return (source_addr_map[short_name], decomp_size)
    return (None, 0)


def read_o_file_functions(obj_path):
    """Read function symbols and sizes from a .o file.
    Returns list of (mangled_name, size)."""
    functions = []
    try:
        with open(obj_path, 'rb') as f:
            ident = f.read(16)
            if ident[:4] != b'\x7fELF':
                return functions
            f.seek(0x28)
            shoff = struct.unpack('<Q', f.read(8))[0]
            f.seek(0x3a)
            shentsize = struct.unpack('<H', f.read(2))[0]
            shnum = struct.unpack('<H', f.read(2))[0]
            shstrndx = struct.unpack('<H', f.read(2))[0]
            if shnum == 0:
                return functions
            f.seek(shoff + shstrndx * shentsize + 0x18)
            strtab_off = struct.unpack('<Q', f.read(8))[0]
            strtab_sz = struct.unpack('<Q', f.read(8))[0]
            f.seek(strtab_off)
            strtab = f.read(strtab_sz)
            for i in range(shnum):
                f.seek(shoff + i * shentsize)
                sh_name_idx = struct.unpack('<I', f.read(4))[0]
                sh_type = struct.unpack('<I', f.read(4))[0]
                end = strtab.index(b'\0', sh_name_idx)
                sec_name = strtab[sh_name_idx:end].decode('ascii', errors='replace')
                if sh_type == 1 and sec_name.startswith('.text.'):
                    mangled = sec_name[6:]
                    if not mangled:
                        continue
                    f.seek(shoff + i * shentsize + 0x18)
                    sh_offset = struct.unpack('<Q', f.read(8))[0]
                    sh_size = struct.unpack('<Q', f.read(8))[0]
                    if sh_size == 0:
                        continue
                    functions.append((mangled, sh_size))
    except (OSError, struct.error):
        pass
    return functions


def main():
    csv_lookup = build_csv_lookup()
    source_addr_map = build_source_addr_map()

    # Collect all compiled functions from .o files
    obj_files = sorted(BUILD_DIR.glob("*.o"))
    seen = set()
    all_resolved = []  # (mangled, compiled_size, original_addr, csv_size)

    for obj in obj_files:
        for mangled, size in read_o_file_functions(obj):
            if mangled in seen:
                continue
            seen.add(mangled)
            short = extract_short_name(mangled)
            addr, csv_size = resolve_addr(csv_lookup, source_addr_map, mangled, short, size)
            if addr is not None:
                all_resolved.append((mangled, size, addr, csv_size))

    # Deduplicate: only one function per original address (prefer first seen)
    addr_to_func = {}
    for mangled, size, addr, csv_size in all_resolved:
        if addr not in addr_to_func:
            addr_to_func[addr] = (mangled, size, csv_size)

    # Sort by address and remove overlaps
    # Skip functions whose decomp size exceeds CSV size (they'd overflow into neighbors)
    sorted_by_addr = sorted(addr_to_func.items())
    func_sections = {}
    prev_end = 0
    skipped = 0
    for addr, (mangled, size, csv_size) in sorted_by_addr:
        if addr < prev_end:
            skipped += 1
            continue
        if csv_size > 0 and size > csv_size:
            skipped += 1
            continue
        func_sections[mangled] = addr
        prev_end = addr + (csv_size if csv_size > 0 else size)

    # Get undefined symbols from all .o files
    undefined = set()
    for obj in obj_files:
        result = subprocess.run([OBJDUMP, "-t", str(obj)], capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if '*UND*' in line:
                parts = line.split()
                if parts:
                    sym = parts[-1]
                    if sym not in func_sections:
                        undefined.add(sym)

    # Generate linker script
    out = PROJECT_ROOT / "build" / "decomp.ld"

    lines = []
    lines.append("/* Auto-generated linker script for SSBU decomp */")
    lines.append("/* Places functions at original addresses for byte-matching */")
    lines.append("")

    # Define external symbols at their original addresses
    lines.append("/* External symbol definitions */")
    ext_count = 0
    for sym in sorted(undefined):
        m = re.match(r'(FUN|DAT|PTR_DAT)_([0-9a-fA-F]+)', sym)
        if m:
            addr = int(m.group(2), 16)
            lines.append("PROVIDE(%s = 0x%x);" % (sym, addr))
            ext_count += 1

    lines.append("")
    lines.append("SECTIONS {")

    # Sort functions by original address
    sorted_funcs = sorted(func_sections.items(), key=lambda x: x[1])

    for mangled, orig_addr in sorted_funcs:
        short = extract_short_name(mangled)
        section_name = ".text.%s" % mangled
        lines.append("  /* %s */" % short)
        lines.append("  . = 0x%x;" % orig_addr)
        lines.append("  %s : { *(%s) }" % (section_name, section_name))

    # Catch-all for remaining sections (after all addressed functions)
    lines.append("")
    lines.append("  /* Remaining sections */")
    lines.append("  .text : { *(.text .text.*) }")
    lines.append("  .rodata : { *(.rodata .rodata.*) }")
    lines.append("  .data : { *(.data .data.*) }")
    lines.append("  .bss : { *(.bss .bss.*) }")
    lines.append("  /DISCARD/ : { *(.dynsym) *(.gnu.hash) *(.dynstr) *(.hash)")
    lines.append("               *(.dynamic) *(.rela.dyn) *(.got) *(.got.plt)")
    lines.append("               *(.comment) *(.note*) *(.eh_frame*) }")
    lines.append("}")

    with open(out, 'w') as f:
        f.write('\n'.join(lines) + '\n')

    print("Generated %s" % out)
    print("  %d function sections placed at original addresses" % len(func_sections))
    print("  %d skipped (address overlap/duplicate)" % skipped)
    print("  %d external symbols defined" % ext_count)
    print("  %d total undefined symbols" % len(undefined))

    return str(out)


if __name__ == '__main__':
    main()
