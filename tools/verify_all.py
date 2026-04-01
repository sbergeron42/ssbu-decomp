#!/usr/bin/env python3
"""
Verify all compiled functions against the original 13.0.4 binary.

Reads function bytes directly from individual .o files (no link step needed),
maps each function to its original address via data/functions.csv and
source-comment annotations, and compares bytes instruction-by-instruction.

Supports both app::lua_bind and non-lua_bind (engine, gameplay, etc.) symbols.

Usage:
    python tools/verify_all.py              # Full report
    python tools/verify_all.py --summary    # Summary only
    python tools/verify_all.py --update     # Update functions.csv with results
    python tools/verify_all.py --elf build/ssbu-decomp.elf  # Use linked ELF for byte comparison
"""

import csv
import os
import re
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
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


def read_bytes_at(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None


def is_adrp(insn):
    return (insn & 0x9F000000) == 0x90000000


def is_add_imm(insn):
    return (insn & 0x7F800000) == 0x11000000


def insn_match_semantic(a, b):
    if a == b:
        return True
    ai = struct.unpack('<I', a)[0]
    bi = struct.unpack('<I', b)[0]
    if is_adrp(ai) and is_adrp(bi):
        return (ai & 0x1F) == (bi & 0x1F)
    if is_add_imm(ai) and is_add_imm(bi):
        mask = 0xFFC003FF
        return (ai & mask) == (bi & mask)
    return False


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


def read_o_file_functions(obj_path):
    """Read all function symbols and their bytes from a .o file.
    Returns list of (mangled_name, size, code_bytes, reloc_offsets_set)."""
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

            # First pass: collect .text sections and .rela sections
            text_sections = {}  # section_index -> (mangled, sh_offset, sh_size)
            rela_sections = {}  # target_section_index -> list of reloc offsets

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
                    text_sections[i] = (mangled, sh_offset, sh_size)

                elif sh_type == 4:  # SHT_RELA
                    f.seek(shoff + i * shentsize + 0x18)
                    sh_offset = struct.unpack('<Q', f.read(8))[0]
                    sh_size = struct.unpack('<Q', f.read(8))[0]
                    f.seek(shoff + i * shentsize + 0x2c)  # sh_info at 0x2c
                    sh_info = struct.unpack('<I', f.read(4))[0]
                    offsets = []
                    num_entries = sh_size // 24
                    for j in range(num_entries):
                        f.seek(sh_offset + j * 24)
                        r_offset = struct.unpack('<Q', f.read(8))[0]
                        offsets.append(r_offset)
                    rela_sections[sh_info] = offsets

            # Second pass: read code and attach relocation info
            for sec_idx, (mangled, sh_offset, sh_size) in text_sections.items():
                f.seek(sh_offset)
                code = f.read(sh_size)
                reloc_offsets = set(rela_sections.get(sec_idx, []))
                functions.append((mangled, sh_size, code, reloc_offsets))
    except (OSError, struct.error):
        pass
    return functions


def get_all_compiled_functions():
    """Scan all .o files in build/ and collect functions (deduplicated).
    Returns list of (mangled, size, code, reloc_offsets)."""
    seen = set()
    all_funcs = []
    for obj_name in sorted(os.listdir(BUILD_DIR)):
        if not obj_name.endswith('.o'):
            continue
        for mangled, size, code, reloc_offsets in read_o_file_functions(BUILD_DIR / obj_name):
            if mangled not in seen:
                seen.add(mangled)
                all_funcs.append((mangled, size, code, reloc_offsets))
    return all_funcs


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
            with open(path) as f:
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
    """Resolve the original address for a compiled function."""
    for name in [mangled, short_name]:
        if not name:
            continue
        entries = csv_lookup.get(name)
        if entries:
            if len(entries) == 1:
                return entries[0][0]
            for addr, csv_size in entries:
                if csv_size == decomp_size:
                    return addr
            return min(entries, key=lambda e: e[1])[0]
    if short_name and short_name in source_addr_map:
        return source_addr_map[short_name]
    return None


def get_linked_elf_path():
    """Parse --elf argument from sys.argv."""
    for i, arg in enumerate(sys.argv):
        if arg == '--elf' and i + 1 < len(sys.argv):
            return Path(sys.argv[i + 1])
    return None


def load_elf_symbols(path):
    """Read symbol table from ELF, returning dict of name -> vaddr for defined functions."""
    symbols = {}
    try:
        with open(path, 'rb') as f:
            ident = f.read(16)
            if ident[:4] != b'\x7fELF':
                return symbols
            f.seek(0x28)
            shoff = struct.unpack('<Q', f.read(8))[0]
            f.seek(0x3a)
            shentsize = struct.unpack('<H', f.read(2))[0]
            shnum = struct.unpack('<H', f.read(2))[0]
            for i in range(shnum):
                f.seek(shoff + i * shentsize)
                sh_name_idx = struct.unpack('<I', f.read(4))[0]
                sh_type = struct.unpack('<I', f.read(4))[0]
                if sh_type != 2:  # SHT_SYMTAB
                    continue
                f.seek(shoff + i * shentsize + 0x18)
                sh_offset = struct.unpack('<Q', f.read(8))[0]
                sh_size = struct.unpack('<Q', f.read(8))[0]
                f.seek(shoff + i * shentsize + 0x28)
                sh_link = struct.unpack('<I', f.read(4))[0]
                f.seek(shoff + sh_link * shentsize + 0x18)
                str_offset = struct.unpack('<Q', f.read(8))[0]
                str_size = struct.unpack('<Q', f.read(8))[0]
                f.seek(str_offset)
                strtab = f.read(str_size)
                num_syms = sh_size // 24
                for j in range(num_syms):
                    f.seek(sh_offset + j * 24)
                    st_name = struct.unpack('<I', f.read(4))[0]
                    st_info = struct.unpack('B', f.read(1))[0]
                    f.read(1)
                    st_shndx = struct.unpack('<H', f.read(2))[0]
                    st_value = struct.unpack('<Q', f.read(8))[0]
                    st_size_val = struct.unpack('<Q', f.read(8))[0]
                    if (st_info & 0xf) == 2 and st_shndx != 0 and st_value != 0:
                        end = strtab.index(b'\0', st_name)
                        name = strtab[st_name:end].decode('ascii', errors='replace')
                        symbols[name] = st_value
                break
    except (OSError, struct.error):
        pass
    return symbols


def main():
    summary_only = '--summary' in sys.argv
    update_csv = '--update' in sys.argv
    linked_elf_path = get_linked_elf_path()

    all_funcs = get_all_compiled_functions()
    csv_lookup = build_csv_lookup()
    source_addr_map = build_source_addr_map()
    orig_segments = load_elf_segments(ORIGINAL_ELF)

    # If a linked ELF is provided, load its segments for reading resolved bytes
    linked_segments = None
    linked_f = None
    linked_syms = set()
    if linked_elf_path and linked_elf_path.exists():
        linked_segments = load_elf_segments(linked_elf_path)
        linked_syms = load_elf_symbols(linked_elf_path)
        linked_f = open(linked_elf_path, 'rb')

    perfect = 0
    semantic = 0
    mismatch = 0
    unmatched = 0
    total_bytes_matched = 0
    total_bytes_compared = 0
    results = {}
    details = []
    unmatched_names = []

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for mangled, size, decomp_bytes, reloc_offsets in all_funcs:
            short_name = extract_short_name(mangled)
            orig_addr = resolve_addr(csv_lookup, source_addr_map,
                                     mangled, short_name, size)
            if orig_addr is None:
                unmatched += 1
                if not summary_only:
                    unmatched_names.append(short_name or mangled)
                continue
            orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr
            orig_bytes = read_bytes_at(orig_f, orig_segments, orig_vaddr, size)
            if orig_bytes is None:
                unmatched += 1
                if not summary_only:
                    unmatched_names.append(
                        "%s (bad address 0x%x)" % (short_name, orig_addr))
                continue

            # At relocation offsets, use linked ELF bytes only if they match the original
            # (avoids replacing with wrong values from unresolved or misplaced targets)
            if linked_f and linked_segments and linked_syms.get(mangled) == orig_addr and reloc_offsets:
                linked_bytes = read_bytes_at(linked_f, linked_segments,
                                             orig_addr, size)
                if linked_bytes and len(linked_bytes) == size:
                    merged = bytearray(decomp_bytes)
                    resolved_offsets = set()
                    for off in reloc_offsets:
                        if off + 4 <= size:
                            if linked_bytes[off:off + 4] == orig_bytes[off:off + 4]:
                                merged[off:off + 4] = linked_bytes[off:off + 4]
                                resolved_offsets.add(off)
                    decomp_bytes = bytes(merged)
                    reloc_offsets = reloc_offsets - resolved_offsets

            num_insns = size // 4
            strict_count = 0
            semantic_count = 0
            for off in range(0, min(len(orig_bytes), len(decomp_bytes)), 4):
                a = orig_bytes[off:off + 4]
                b = decomp_bytes[off:off + 4]
                if a == b:
                    strict_count += 1
                    semantic_count += 1
                elif off in reloc_offsets:
                    # Instruction has a relocation — can't compare raw bytes
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
                status = 'E'
            else:
                mismatch += 1
                status = 'N'
                if not summary_only:
                    details.append((short_name, strict_count, semantic_count, num_insns))
            display_name = short_name or mangled
            results[display_name] = (status, strict_count * 100 // num_insns if num_insns else 0)

    total = perfect + semantic + mismatch
    total_funcs = len(all_funcs)

    print()
    print("=" * 70)
    print("  SSBU Decomp -- Verified Binary Comparison (13.0.4)")
    print("=" * 70)
    print()
    print("  Total compiled functions:  %d" % total_funcs)
    print("  Matched to original addr:  %d" % total)
    print("  Unmatched (no address):    %d" % unmatched)
    print()

    if total > 0:
        bar_w = 40
        pf = perfect * bar_w // total
        sm = semantic * bar_w // total
        mm = max(0, bar_w - pf - sm)
        bar = '#' * pf + '~' * sm + '-' * mm
        print("  [%s]" % bar)
        print()
        print("  BYTE-IDENTICAL:   %5d  (%.1f%%)" % (perfect, perfect * 100 / total))
        print("  SEMANTIC MATCH:   %5d  (%.1f%%)  (ADRP/ADD reloc only)" % (semantic, semantic * 100 / total))
        print("  Non-matching:     %5d  (%.1f%%)" % (mismatch, mismatch * 100 / total))
        print("                    -----")
        print("  TOTAL MATCHING:   %5d  (%.1f%%)" % (perfect + semantic, (perfect + semantic) * 100 / total))
        print()
        print("  Bytes: %s / %s strict match (%d%%)" % (
            "{:,}".format(total_bytes_matched),
            "{:,}".format(total_bytes_compared),
            total_bytes_matched * 100 // total_bytes_compared if total_bytes_compared else 0))
    print()

    if details and not summary_only:
        print("  Non-matching functions:")
        for name, sc, smc, tc in sorted(details, key=lambda x: -x[2] / x[3] if x[3] else 0)[:30]:
            print("    %s: %d/%d strict, %d/%d semantic" % (name, sc, tc, smc, tc))
        if len(details) > 30:
            print("    ... and %d more" % (len(details) - 30))

    if unmatched_names and not summary_only:
        print()
        print("  Unmatched symbols (no address):")
        for name in unmatched_names[:20]:
            print("    %s" % name)
        if len(unmatched_names) > 20:
            print("    ... and %d more" % (len(unmatched_names) - 20))

    print()

    if update_csv and results:
        rows = []
        with open(FUNCTIONS_CSV) as f:
            reader = csv.DictReader(f)
            fieldnames = reader.fieldnames
            for row in reader:
                name = row['Name']
                short = extract_short_name(name)
                if name in results:
                    status, _ = results[name]
                    row['Quality'] = status
                elif short in results:
                    status, _ = results[short]
                    row['Quality'] = status
                rows.append(row)
        with open(FUNCTIONS_CSV, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames, extrasaction='ignore')
            writer.writeheader()
            writer.writerows(rows)
        print("  Updated %d entries in functions.csv" % len(results))

    if linked_f:
        linked_f.close()


if __name__ == '__main__':
    main()
