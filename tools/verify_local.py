#!/usr/bin/env python3
"""
Worker-safe local verification — checks compiled functions without modifying functions.csv.

For use in git worktrees where workers should not touch the shared CSV.
Compiles, links, and verifies only the specified modules or all modules.

Usage:
    python tools/verify_local.py                          # Verify all
    python tools/verify_local.py --modules GroundModule    # Verify specific module(s)
    python tools/verify_local.py --build                   # Rebuild before verifying
"""

import csv
import struct
import subprocess
import sys
import os
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
CLANG = r"C:\llvm-8.0.0\bin\clang++.exe"
LLD = r"C:\llvm-8.0.0\bin\ld.lld.exe"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
CFLAGS = "-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude"
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


def read_bytes(f, segments, vaddr, size):
    for seg_vaddr, seg_offset, seg_filesz in segments:
        if seg_vaddr <= vaddr < seg_vaddr + seg_filesz:
            f.seek(seg_offset + (vaddr - seg_vaddr))
            return f.read(size)
    return None


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


def build_incremental():
    """Compile only changed .cpp files, then link."""
    build_dir = PROJECT_ROOT / "build"
    build_dir.mkdir(exist_ok=True)
    src_files = list((PROJECT_ROOT / "src").rglob("*.cpp"))

    compiled = 0
    for src in src_files:
        obj = build_dir / (src.stem + ".o")
        if obj.exists() and obj.stat().st_mtime >= src.stat().st_mtime:
            continue
        cmd = f'"{CLANG}" {CFLAGS} -c "{src}" -o "{obj}"'
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        if result.returncode != 0:
            print(f"  ERROR compiling {src.name}:")
            print(result.stderr[:500])
            return False
        compiled += 1

    if compiled > 0:
        print(f"  Compiled {compiled} file(s)")

    # Post-process: patch movz → orr to match NX original encoding
    fix_movz = PROJECT_ROOT / "tools" / "fix_movz_to_orr.py"
    if fix_movz.exists():
        objs = [str(o) for o in (build_dir).glob("*.o")]
        if objs:
            subprocess.run(["python", str(fix_movz)] + objs, capture_output=True)

    # Check for fix_prologue_sched.py and run it if present
    fix_script = PROJECT_ROOT / "tools" / "fix_prologue_sched.py"
    if fix_script.exists():
        prologue_targets = ["PostureModule", "KineticEnergy", "CameraModule",
                           "GroundModule", "KineticModule", "LinkModule",
                           "FighterControlModuleImpl", "BattleObjectManager",
                           "FighterManager", "FighterEntry", "FighterCutInManager",
                           "FighterInformation", "ItemManager",
                           "FighterMotionModuleImpl", "EffectModule",
                           "FighterBayonettaFinalModule", "ItemKineticModuleImpl",
                           "FighterKineticEnergyMotion", "KineticEnergyNormal"]
        objs = [str(build_dir / f"{t}.o") for t in prologue_targets if (build_dir / f"{t}.o").exists()]
        if objs:
            subprocess.run(["python", str(fix_script)] + objs, capture_output=True)

    # Generate linker script for address-matched layout
    gen_ld = PROJECT_ROOT / "tools" / "gen_linker_script.py"
    linker_script = build_dir / "decomp.ld"
    subprocess.run(["python", str(gen_ld)], capture_output=True)

    # Link with linker script for correct symbol placement
    obj_files = list(build_dir.glob("*.o"))
    cmd = [LLD, "-T", str(linker_script), "-o", str(DECOMP_ELF),
           "--unresolved-symbols=ignore-all",
           "--no-undefined-version", "-nostdlib",
           "--noinhibit-exec"] + [str(o) for o in obj_files]
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  Link error: {result.stderr[:500]}")
        return False

    print("  Linked OK")
    return True


def main():
    modules_filter = None
    do_build = False

    # Parse args
    args = sys.argv[1:]
    i = 0
    while i < len(args):
        if args[i] == '--modules':
            modules_filter = set()
            i += 1
            while i < len(args) and not args[i].startswith('--'):
                modules_filter.add(args[i])
                i += 1
        elif args[i] == '--build':
            do_build = True
            i += 1
        else:
            i += 1

    if do_build:
        print("Building...")
        if not build_incremental():
            sys.exit(1)

    if not DECOMP_ELF.exists():
        print("ERROR: %s not found. Run --build first or build manually." % DECOMP_ELF)
        sys.exit(1)

    if not ORIGINAL_ELF.exists():
        print("ERROR: %s not found. Symlink the original ELF." % ORIGINAL_ELF)
        sys.exit(1)

    # Build CSV lookup (read-only) — store all entries per name for disambiguation
    csv_lookup = {}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            addr = int(row[0], 16)
            csv_size = int(row[2])
            name = row[3]
            csv_lookup.setdefault(name, []).append((addr, csv_size))
            if name.startswith('_ZN3app8lua_bind'):
                short = extract_func_name(name)
                if short:
                    csv_lookup.setdefault(short, []).append((addr, csv_size))

    def resolve_addr(name, decomp_size):
        entries = csv_lookup.get(name, [])
        if not entries:
            return None
        if len(entries) == 1:
            return entries[0][0]
        for addr, cs in entries:
            if cs == decomp_size:
                return addr
        return min(entries, key=lambda e: e[1])[0]

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
                func_name = extract_func_name(name)
                if func_name:
                    # Filter by module if specified
                    if modules_filter:
                        module = func_name.split('__')[0] if '__' in func_name else ''
                        if module not in modules_filter:
                            continue
                    symbols.append((name, func_name, addr, size))

    # Load ELF segments
    orig_segments = load_elf_segments(ORIGINAL_ELF)
    decomp_segments = load_elf_segments(DECOMP_ELF)

    perfect = 0
    mismatch = 0
    unmatched = 0
    details = []

    with open(ORIGINAL_ELF, 'rb') as orig_f, open(DECOMP_ELF, 'rb') as decomp_f:
        for mangled, func_name, decomp_addr, size in symbols:
            # Prefer full mangled name match, then short name.
            # resolve_addr picks the CSV entry whose size best matches decomp.
            orig_addr = resolve_addr(mangled, size)
            if orig_addr is None:
                orig_addr = resolve_addr(func_name, size)
            if orig_addr is None:
                unmatched += 1
                continue
            orig_vaddr = orig_addr - ELF_BASE if orig_addr >= ELF_BASE else orig_addr

            orig_bytes = read_bytes(orig_f, orig_segments, orig_vaddr, size)
            decomp_bytes = read_bytes(decomp_f, decomp_segments, decomp_addr, size)

            if orig_bytes is None or decomp_bytes is None:
                unmatched += 1
                continue

            num_insns = size // 4
            match_count = sum(1 for i in range(0, min(len(orig_bytes), len(decomp_bytes)), 4)
                            if orig_bytes[i:i+4] == decomp_bytes[i:i+4])

            if match_count == num_insns:
                perfect += 1
            else:
                mismatch += 1
                details.append((func_name, match_count, num_insns))

    total = perfect + mismatch
    scope = "modules: %s" % ', '.join(sorted(modules_filter)) if modules_filter else "all functions"

    print()
    print("=" * 60)
    print("  Local Verification (%s)" % scope)
    print("=" * 60)
    print()
    print("  Checked:        %d" % total)
    print("  Byte-identical: %d  (%.1f%%)" % (perfect, perfect * 100 / total if total else 0))
    print("  Non-matching:   %d" % mismatch)
    print("  Unmatched (no CSV): %d" % unmatched)

    if details:
        print()
        print("  Non-matching:")
        for name, mc, tc in sorted(details, key=lambda x: -x[1]/x[2] if x[2] else 0):
            print("    %s: %d/%d" % (name, mc, tc))

    print()

    # Exit code: 0 if all matched, 1 if any mismatches
    sys.exit(0 if mismatch == 0 else 1)


if __name__ == '__main__':
    main()
