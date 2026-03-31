#!/usr/bin/env python3
"""
Migrate functions.csv from 3-column (Address,Name,Status) to viking 4-column
(Address,Quality,Size,Name) format.

Changes:
  - Adds Size column (calculated from consecutive addresses)
  - Addresses get 0x prefix and zero-padded to 16 hex digits
  - Status codes mapped: M->O, E->m, N->M, U->U
  - Decompiled function names replaced with mangled C++ symbols from ELF
  - Duplicate names resolved
"""

import csv
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
ELF_BASE = 0x7100000000

# Map our status codes to viking quality codes
STATUS_MAP = {
    'M': 'O',   # our Matching -> viking Matching
    'E': 'm',   # our Equivalent -> viking NonMatchingMinor
    'N': 'M',   # our Non-matching -> viking NonMatchingMajor
    'U': 'U',   # not decompiled
}


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


def get_decomp_symbols():
    """Build short_name -> (mangled_name, size) mapping from decomp ELF."""
    result = subprocess.run(
        [OBJDUMP, "-t", str(DECOMP_ELF)],
        capture_output=True, text=True
    )
    mapping = {}
    for line in result.stdout.split('\n'):
        if 'F .text' in line:
            parts = line.split()
            mangled = parts[-1]
            size = int(parts[4], 16) if len(parts) > 4 else 0
            if size > 0:
                short = extract_func_name(mangled)
                if short:
                    mapping[short] = (mangled, size)
    return mapping


def main():
    print("Reading decomp ELF symbols...")
    short_to_mangled = get_decomp_symbols()
    print(f"  Found {len(short_to_mangled)} decomp symbols")

    print("Reading current functions.csv...")
    rows = []
    with open(FUNCTIONS_CSV) as f:
        for row in csv.DictReader(f):
            addr = int(row['Address'], 16)
            name = row['Name']
            status = row['Status']
            rows.append((addr, name, status))

    print(f"  Found {len(rows)} entries")

    # Sort by address
    rows.sort(key=lambda r: r[0])

    # Calculate gap sizes from consecutive addresses
    entries = []
    for i, (addr, name, status) in enumerate(rows):
        if i + 1 < len(rows):
            gap = rows[i + 1][0] - addr
        else:
            gap = 4  # last function, assume minimum
        # Clamp to reasonable range
        gap = max(4, min(gap, 0x100000))
        entries.append((addr, name, status, gap))

    # Build mangled name mapping for decompiled functions
    # and resolve duplicate names
    seen_names = {}
    output = []

    for addr, name, status, gap in entries:
        quality = STATUS_MAP.get(status, 'U')

        # For decompiled functions, use mangled name and actual size from ELF
        # but cap to gap to avoid overlapping with next function
        if quality in ('O', 'm', 'M') and name in short_to_mangled:
            out_name, elf_size = short_to_mangled[name]
            size = min(elf_size, gap)
        else:
            out_name = name
            size = gap

        # Viking CSV parser doesn't support quoting — strip commas
        out_name = out_name.replace(',', '')

        # Resolve duplicates
        if out_name in seen_names:
            # Append address suffix to make unique
            base = out_name
            out_name = f"{base}_{addr:x}"
            # If still duplicate (shouldn't happen), keep appending
            while out_name in seen_names:
                out_name = f"{base}_{addr:x}_dup"
        seen_names[out_name] = True

        output.append({
            'Address': f"0x{addr:016x}",
            'Quality': quality,
            'Size': f"{size:06d}",
            'Name': out_name,
        })

    # Backup original
    backup = FUNCTIONS_CSV.with_suffix('.csv.bak')
    print(f"Backing up to {backup.name}...")
    import shutil
    shutil.copy2(FUNCTIONS_CSV, backup)

    # Write new format
    print("Writing viking-format functions.csv...")
    with open(FUNCTIONS_CSV, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=['Address', 'Quality', 'Size', 'Name'])
        writer.writeheader()
        writer.writerows(output)

    # Count stats
    matching = sum(1 for o in output if o['Quality'] == 'O')
    minor = sum(1 for o in output if o['Quality'] == 'm')
    major = sum(1 for o in output if o['Quality'] == 'M')
    undecomp = sum(1 for o in output if o['Quality'] == 'U')

    print(f"\nMigration complete!")
    print(f"  Total:           {len(output)}")
    print(f"  Matching (O):    {matching}")
    print(f"  Minor (m):       {minor}")
    print(f"  Major (M):       {major}")
    print(f"  Not decomp (U):  {undecomp}")


if __name__ == '__main__':
    main()
