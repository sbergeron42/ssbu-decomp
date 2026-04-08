#!/usr/bin/env python3
"""
Match compiled library code against the original SSBU binary.

Compiles a library's .c files with the project's Clang flags, extracts each
function's bytes, and searches for identical byte sequences in the binary.
Relocations are masked during comparison (ADRP/BL/ADD sites skipped).

Usage:
    python tools/match_library.py lib/zstd/decompress/zstd_decompress.c
    python tools/match_library.py lib/zstd/ --recursive
    python tools/match_library.py lib/jemalloc/src/arena.c --extra-flags="-DJEMALLOC_NO_RENAME"
"""

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
BUILD_DIR = PROJECT_ROOT / "build" / "libmatch"
CLANG = r"C:\llvm-8.0.0\bin\clang.exe"  # C compiler for library code
CLANGPP = r"C:\llvm-8.0.0\bin\clang++.exe"
ELF_BASE = 0x7100000000

# Compile flags matching the original build
# Note: libraries are C, not C++, so use clang not clang++
BASE_CFLAGS = [
    "-target", "aarch64-none-elf",
    "-mcpu=cortex-a57",
    "-O2",
    "-fno-exceptions",
    "-ffunction-sections", "-fdata-sections",
    "-fno-common", "-fno-short-enums",
    "-fPIC",
    "-mno-implicit-float",
    "-fno-strict-aliasing",
    "-fno-slp-vectorize",
]

# AArch64 relocation types to mask during comparison
_RELOC_TYPES = {
    275, 311,  # ADRP
    277,       # ADD_ABS_LO12_NC
    278,       # LDST8
    282,       # JUMP26
    283,       # CALL26
    284,       # LDST16
    285,       # LDST32
    286, 312,  # LDST64
    299,       # LDST128
}


def load_elf_text(path):
    """Load the .text segment from the original ELF. Returns (vaddr, bytes)."""
    with open(path, 'rb') as f:
        f.seek(0x20)
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)
        phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]

        # Find the executable LOAD segment (contains .text)
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]
            p_flags = struct.unpack('<I', f.read(4))[0]
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]
            f.read(8)  # p_paddr
            p_filesz = struct.unpack('<Q', f.read(8))[0]

            # PF_X = 1 (executable)
            if p_type == 1 and (p_flags & 1):
                f.seek(p_offset)
                data = f.read(p_filesz)
                return (p_vaddr, data)
    return None


def read_o_functions(obj_path):
    """Read functions from a .o file. Returns list of (name, size, code, reloc_offsets)."""
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

            # Read section name string table
            f.seek(shoff + shstrndx * shentsize + 0x18)
            strtab_off = struct.unpack('<Q', f.read(8))[0]
            strtab_sz = struct.unpack('<Q', f.read(8))[0]
            f.seek(strtab_off)
            strtab = f.read(strtab_sz)

            # Collect .text sections and their .rela sections
            text_secs = {}  # sec_idx -> (name, offset, size)
            rela_targets = {}  # target_sec_idx -> set of offsets to mask

            for i in range(shnum):
                f.seek(shoff + i * shentsize)
                sh_name_idx = struct.unpack('<I', f.read(4))[0]
                sh_type = struct.unpack('<I', f.read(4))[0]
                end = strtab.index(b'\0', sh_name_idx)
                sec_name = strtab[sh_name_idx:end].decode('ascii', errors='replace')

                if sh_type == 1 and sec_name.startswith('.text.'):
                    func_name = sec_name[6:]
                    if not func_name:
                        continue
                    f.seek(shoff + i * shentsize + 0x18)
                    sh_offset = struct.unpack('<Q', f.read(8))[0]
                    sh_size = struct.unpack('<Q', f.read(8))[0]
                    if sh_size == 0:
                        continue
                    text_secs[i] = (func_name, sh_offset, sh_size)

                elif sh_type == 4:  # SHT_RELA
                    f.seek(shoff + i * shentsize + 0x18)
                    sh_offset = struct.unpack('<Q', f.read(8))[0]
                    sh_size = struct.unpack('<Q', f.read(8))[0]
                    f.seek(shoff + i * shentsize + 0x28)
                    f.read(4)  # sh_link
                    sh_info = struct.unpack('<I', f.read(4))[0]
                    offsets = set()
                    num_entries = sh_size // 24
                    for j in range(num_entries):
                        f.seek(sh_offset + j * 24)
                        r_offset = struct.unpack('<Q', f.read(8))[0]
                        r_info = struct.unpack('<Q', f.read(8))[0]
                        r_type = r_info & 0xFFFFFFFF
                        if r_type in _RELOC_TYPES:
                            offsets.add(r_offset)
                    rela_targets[sh_info] = offsets

            for sec_idx, (name, offset, size) in text_secs.items():
                f.seek(offset)
                code = f.read(size)
                reloc_offsets = rela_targets.get(sec_idx, set())
                functions.append((name, size, code, reloc_offsets))
    except (OSError, struct.error):
        pass
    return functions


def build_insn_index(text_data):
    """Build a dict mapping each 4-byte instruction to list of offsets where it appears."""
    index = {}
    for i in range(0, len(text_data) - 3, 4):
        insn = text_data[i:i + 4]
        key = bytes(insn)
        if key not in index:
            index[key] = []
        index[key].append(i)
    return index


def find_in_binary(func_bytes, reloc_offsets, text_vaddr, text_data, func_size,
                   insn_index=None):
    """Search for func_bytes in the binary, masking relocation sites.
    Uses instruction index for fast candidate lookup.
    Returns list of matching virtual addresses."""
    if func_size < 4:
        return []

    matches = []

    # Find the first non-reloc instruction to use as search key
    key_offset = None
    for off in range(0, func_size, 4):
        if off not in reloc_offsets:
            key_offset = off
            break
    if key_offset is None:
        return []  # all instructions are relocations

    key = func_bytes[key_offset:key_offset + 4]
    if len(key) < 4:
        return []

    # Get candidate positions from index
    if insn_index is not None:
        candidates = insn_index.get(bytes(key), [])
    else:
        # Fallback: linear scan
        candidates = []
        for i in range(0, len(text_data) - func_size, 4):
            if text_data[i + key_offset:i + key_offset + 4] == key:
                candidates.append(i + key_offset)

    for cand_pos in candidates:
        # cand_pos is where the key instruction is; adjust to function start
        func_start = cand_pos - key_offset
        if func_start < 0 or func_start + func_size > len(text_data):
            continue

        # Compare all non-reloc instructions
        match = True
        for off in range(0, func_size, 4):
            if off in reloc_offsets:
                continue
            if text_data[func_start + off:func_start + off + 4] != func_bytes[off:off + 4]:
                match = False
                break

        if match:
            matches.append(text_vaddr + func_start)

    return matches


def compile_source(src_path, extra_flags=None):
    """Compile a C/C++ source file and return path to .o file."""
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    o_name = src_path.stem + ".o"
    o_path = BUILD_DIR / o_name

    is_cpp = src_path.suffix in ('.cpp', '.cc', '.cxx')
    compiler = CLANGPP if is_cpp else CLANG
    flags = list(BASE_CFLAGS)
    if is_cpp:
        flags.extend(["-std=c++17", "-fno-rtti"])
    else:
        flags.extend(["-std=c11"])

    if extra_flags:
        flags.extend(extra_flags)

    cmd = [compiler] + flags + ["-c", str(src_path), "-o", str(o_path)]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print("  COMPILE ERROR: %s" % src_path.name)
        # Show first few lines of errors
        for line in result.stderr.split('\n')[:5]:
            print("    %s" % line)
        return None
    return o_path


def load_csv_by_addr():
    """Load functions.csv keyed by address."""
    by_addr = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            by_addr[addr] = {"quality": row[1], "size": int(row[2]), "name": row[3]}
    return by_addr


def main():
    args = sys.argv[1:]
    if not args:
        print("Usage: python tools/match_library.py <source_file_or_dir> [--recursive] [--extra-flags=...]")
        sys.exit(1)

    # Parse args
    sources = []
    recursive = False
    extra_flags = []
    for arg in args:
        if arg == '--recursive':
            recursive = True
        elif arg.startswith('--extra-flags='):
            extra_flags = arg[len('--extra-flags='):].split()
        elif arg.startswith('--include='):
            extra_flags.extend(["-I", arg[len('--include='):]])
        else:
            sources.append(arg)

    # Collect source files
    src_files = []
    for src in sources:
        p = Path(src)
        if p.is_dir():
            pattern = "**/*.c" if recursive else "*.c"
            src_files.extend(p.glob(pattern))
            if recursive:
                src_files.extend(p.glob("**/*.cpp"))
        elif p.is_file():
            src_files.append(p)
        else:
            print("Not found: %s" % src)

    if not src_files:
        print("No source files found.")
        sys.exit(1)

    print("Loading binary...")
    text_info = load_elf_text(ORIGINAL_ELF)
    if not text_info:
        print("ERROR: Could not load .text from %s" % ORIGINAL_ELF)
        sys.exit(1)
    text_vaddr, text_data = text_info
    print("  .text: 0x%x, %d MB" % (text_vaddr, len(text_data) // (1024 * 1024)))

    print("Building instruction index...")
    insn_index = build_insn_index(text_data)
    print("  %d unique instructions indexed" % len(insn_index))

    csv_by_addr = load_csv_by_addr()

    total_matched = 0
    total_bytes = 0
    all_matches = []

    for src_file in sorted(src_files):
        print()
        print("=== %s ===" % src_file.name)
        o_path = compile_source(src_file, extra_flags)
        if o_path is None:
            continue

        funcs = read_o_functions(o_path)
        print("  %d functions compiled" % len(funcs))

        for name, size, code, reloc_offsets in funcs:
            if size < 32:  # skip trivial (< 8 instructions)
                continue

            matches = find_in_binary(code, reloc_offsets, text_vaddr, text_data, size,
                                    insn_index)

            if matches:
                for vaddr in matches:
                    real_addr = vaddr + ELF_BASE
                    csv_entry = csv_by_addr.get(real_addr)
                    csv_name = csv_entry["name"] if csv_entry else "???"
                    csv_quality = csv_entry["quality"] if csv_entry else "?"
                    status = "[%s]" % csv_quality
                    print("  MATCH: %-40s %4d bytes @ 0x%x  %s %s" % (
                        name, size, real_addr, status, csv_name))
                    all_matches.append((name, size, real_addr, csv_name, csv_quality))

                total_matched += 1
                total_bytes += size

    print()
    print("=" * 70)
    print("Summary:")
    print("  Functions matched: %d" % total_matched)
    print("  Total bytes: %d (%d KB)" % (total_bytes, total_bytes // 1024))
    print()
    if all_matches:
        already = sum(1 for _, _, _, _, q in all_matches if q in ('M', 'N'))
        new = sum(1 for _, _, _, _, q in all_matches if q == 'U')
        print("  Already compiled (M/N): %d" % already)
        print("  New identifications (U): %d" % new)
        new_bytes = sum(sz for _, sz, _, _, q in all_matches if q == 'U')
        print("  New bytes: %d (%d KB)" % (new_bytes, new_bytes // 1024))


if __name__ == '__main__':
    main()
