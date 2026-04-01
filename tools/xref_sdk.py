#!/usr/bin/env python3
"""
Cross-reference SDK functions between KinokoDecomp-S (Captain Toad) and SSBU.

Both games use NintendoSDK 8.2.x compiled with NX Clang. SDK functions
have identical machine code (excluding ADRP/B relocations). This tool
finds matching byte sequences to identify unnamed FUN_* functions.

Usage:
    python tools/xref_sdk.py                    # Full cross-reference
    python tools/xref_sdk.py --min-size 16      # Only functions >= 16 bytes
    python tools/xref_sdk.py --dry-run          # Show matches without updating CSV
"""

import csv
import struct
import sys
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
SSBU_ELF = PROJECT_ROOT / "data" / "main.elf"
KINOKO_FLAT = Path("C:/Users/seanb/Dev/KinokoDecomp-S/data/main.flat")
KINOKO_CSV = Path("C:/Users/seanb/Dev/KinokoDecomp-S/data/kinoko-s_functions.csv")
SSBU_CSV = PROJECT_ROOT / "data" / "functions.csv"
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


def read_bytes_elf(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


def mask_relocations(data):
    """Mask ADRP and B/BL instructions (position-dependent) for fuzzy matching."""
    if len(data) < 4:
        return data
    masked = bytearray(data)
    for i in range(0, len(data) - 3, 4):
        insn = struct.unpack_from('<I', data, i)[0]
        # ADRP: mask entire instruction (page-relative)
        if (insn & 0x9F000000) == 0x90000000:
            struct.pack_into('<I', masked, i, 0x90000000 | (insn & 0x1F))  # keep Rd only
        # B/BL: mask offset (keep opcode)
        elif (insn & 0xFC000000) in (0x14000000, 0x94000000):
            struct.pack_into('<I', masked, i, insn & 0xFC000000)
        # ADD immediate after ADRP: mask imm12
        elif (insn & 0x7F800000) == 0x11000000:
            struct.pack_into('<I', masked, i, insn & 0xFFC003FF)  # keep Rd, Rn
    return bytes(masked)


def main():
    min_size = 8
    dry_run = False
    for i, arg in enumerate(sys.argv[1:]):
        if arg == '--min-size' and i + 1 < len(sys.argv) - 1:
            min_size = int(sys.argv[i + 2])
        elif arg == '--dry-run':
            dry_run = True

    print("SSBU × KinokoDecomp-S SDK Cross-Reference")
    print("=" * 60)

    # Load KinokoDecomp-S functions (named SDK functions only)
    kinoko_funcs = []
    with open(KINOKO_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            name = row[3]
            if not name or name.startswith('FUN_'):
                continue
            addr = int(row[0], 16) - ELF_BASE  # convert to flat offset
            size = int(row[2])
            if size < min_size or size > 4096:
                continue
            kinoko_funcs.append((addr, size, name))

    print(f"  KinokoDecomp-S named functions: {len(kinoko_funcs)}")

    # Load SSBU unnamed functions
    ssbu_unnamed = {}
    with open(SSBU_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            name = row[3]
            if not name.startswith('FUN_'):
                continue
            addr = int(row[0], 16)
            ssbu_unnamed[addr] = name

    print(f"  SSBU unnamed (FUN_*) functions: {len(ssbu_unnamed)}")

    # Load binaries
    kinoko_data = open(KINOKO_FLAT, 'rb').read()
    ssbu_segments = load_elf_segments(SSBU_ELF)

    # Build SSBU .text index for fast searching
    # Read the entire .text section
    ssbu_text_start = ssbu_segments[0][0]
    ssbu_text_size = ssbu_segments[0][2]
    with open(SSBU_ELF, 'rb') as f:
        ssbu_text = read_bytes_elf(f, ssbu_segments, ssbu_text_start, ssbu_text_size)

    print(f"  SSBU .text size: {len(ssbu_text):,} bytes")
    print()
    print("Searching for matches...")

    # For each KinokoDecomp-S function, search in SSBU
    matches = []
    checked = 0

    for k_addr, k_size, k_name in kinoko_funcs:
        if k_addr + k_size > len(kinoko_data):
            continue

        k_bytes = kinoko_data[k_addr:k_addr + k_size]
        if not k_bytes or len(k_bytes) < min_size:
            continue

        # Mask relocations for fuzzy matching
        k_masked = mask_relocations(k_bytes)

        # Search in SSBU .text
        found = []
        for offset in range(0, len(ssbu_text) - k_size, 4):
            s_bytes = ssbu_text[offset:offset + k_size]
            s_masked = mask_relocations(s_bytes)
            if k_masked == s_masked:
                ssbu_addr = (ssbu_text_start + offset) + ELF_BASE
                found.append(ssbu_addr)

        if len(found) == 1:
            # Unique match
            ssbu_addr = found[0]
            if ssbu_addr in ssbu_unnamed:
                matches.append((ssbu_addr, k_name, k_size, ssbu_unnamed[ssbu_addr]))

        checked += 1
        if checked % 1000 == 0:
            print(f"  Checked {checked}/{len(kinoko_funcs)} ({len(matches)} matches)...")

    print()
    print(f"=== Results ===")
    print(f"  Checked: {checked}")
    print(f"  Unique matches: {len(matches)}")
    print()

    # Show matches by namespace
    by_ns = defaultdict(int)
    for _, name, _, _ in matches:
        if '::' in name:
            ns = name.split('::')[0]
        elif name.startswith('_Z'):
            ns = 'mangled'
        else:
            ns = 'C'
        by_ns[ns] += 1

    print("  By namespace:")
    for ns, c in sorted(by_ns.items(), key=lambda x: -x[1])[:15]:
        print(f"    {ns}: {c}")

    if matches:
        print()
        print("  Sample matches:")
        for addr, name, size, old_name in matches[:20]:
            print(f"    {old_name} -> {name} ({size}B)")

    if not dry_run and matches:
        print()
        print(f"  Updating {len(matches)} entries in functions.csv...")
        # Read CSV, update names
        rows = []
        updated = 0
        with open(SSBU_CSV) as f:
            reader = csv.reader(f)
            header = next(reader)
            for row in reader:
                addr = int(row[0], 16)
                for m_addr, m_name, _, _ in matches:
                    if addr == m_addr:
                        row[3] = m_name
                        updated += 1
                        break
                rows.append(row)

        with open(SSBU_CSV, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(header)
            writer.writerows(rows)

        print(f"  Updated {updated} function names in CSV")


if __name__ == '__main__':
    main()
