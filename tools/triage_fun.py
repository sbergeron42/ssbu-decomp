#!/usr/bin/env python3
"""
Triage unnamed FUN_* functions — categorize by instruction pattern, size,
and content to prioritize decomp work.

Usage:
    python tools/triage_fun.py                # Full triage report
    python tools/triage_fun.py --actionable   # Only show decompilable functions
    python tools/triage_fun.py --export       # Export categorized CSV
"""

import csv
import struct
import sys
from pathlib import Path
from collections import Counter, defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
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


def read_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


def classify_function(insns, size):
    """Classify a function by its instruction pattern."""
    n = len(insns)
    if n == 0:
        return 'empty'

    first = insns[0]
    last = insns[-1]
    has_ret = last == 0xD65F03C0
    has_br = (last & 0xFFFFFC1F) == 0xD61F0000
    has_frame = n >= 2 and first == 0xA9BF7BFD  # stp x29,x30,[sp,#-16]!
    has_b = any((i & 0xFC000000) == 0x14000000 for i in insns)
    has_bl = any((i & 0xFC000000) == 0x94000000 for i in insns)
    has_adrp = any((i & 0x9F000000) == 0x90000000 for i in insns)
    has_simd = any(((i >> 24) & 0xFF) in (0x4C, 0x4E, 0x6E, 0x0E, 0x3D, 0x1E,
                    0xBD, 0x3C, 0x0D, 0x4D, 0x2D, 0x6D) for i in insns)
    n_ldr = sum(1 for i in insns if (i & 0x3F000000) in (0x39000000, 0x3D000000, 0x38000000))
    n_str = sum(1 for i in insns if (i & 0x3F000000) in (0x39000000, 0x3D000000, 0x38000000)
                and (i & 0xFFC00000) in (0x39000000, 0xF9000000, 0x3D000000, 0xBD000000))

    # 1-2 instruction stubs (ret, b external, trampoline)
    if n <= 2:
        if n == 1 and has_ret:
            return 'noop'
        if has_b:
            return 'trampoline'
        return 'tiny_stub'

    # 3-4 instruction vtable dispatchers
    if n <= 4 and (has_br or has_b):
        if has_br:
            return 'vtable_dispatch'
        return 'tail_call'

    # 5-7 instruction dispatchers with bool masks or constants
    if n <= 7 and has_br:
        n_and = sum(1 for i in insns if (i & 0xFFFFFC00) == 0x12000000)
        if n_and > 0:
            return 'vtable_dispatch_bool'
        return 'vtable_dispatch_ext'

    # Simple field accessors (no branches, few instructions)
    if n <= 5 and has_ret and not has_bl and not has_b:
        return 'field_accessor'

    # Framed vtable call (stp/mov/.../blr/.../ldp/ret)
    if has_frame and n <= 12 and not has_b:
        return 'framed_vtable_call'

    # Constructor/destructor patterns
    if has_frame and n <= 20 and not has_simd:
        return 'ctor_dtor_small'

    # Functions with external calls
    if has_bl and not has_b:
        if n <= 20:
            return 'small_with_calls'
        elif n <= 50:
            return 'medium_with_calls'
        else:
            return 'large_with_calls'

    # Functions with branches to external (tail calls)
    if has_b and not has_bl:
        if n <= 10:
            return 'small_tail_call'
        else:
            return 'complex_tail_call'

    # SIMD functions
    if has_simd:
        if n <= 15:
            return 'simd_small'
        else:
            return 'simd_complex'

    # Pure computation (no calls, no branches to external)
    if not has_bl and not has_b:
        if n <= 15:
            return 'computation_small'
        elif n <= 50:
            return 'computation_medium'
        else:
            return 'computation_large'

    # Everything else
    if size <= 100:
        return 'complex_small'
    elif size <= 500:
        return 'complex_medium'
    else:
        return 'complex_large'


def main():
    actionable_only = '--actionable' in sys.argv
    do_export = '--export' in sys.argv

    segments = load_elf_segments(ORIGINAL_ELF)

    # Load FUN_* functions
    fun_functions = []
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            name = row[3]
            if not name.startswith('FUN_'):
                continue
            addr = int(row[0], 16)
            size = int(row[2])
            fun_functions.append((addr, size, name))

    print("=" * 60)
    print("  FUN_* Triage Report")
    print("=" * 60)
    print()
    print("  Total unnamed functions: %d" % len(fun_functions))
    print()

    # Classify each function
    categories = Counter()
    by_category = defaultdict(list)

    with open(ORIGINAL_ELF, 'rb') as f:
        for addr, size, name in fun_functions:
            vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
            read_size = min(size, 512)  # read up to 512 bytes
            raw = read_bytes(f, segments, vaddr, read_size)
            if not raw:
                categories['unreadable'] += 1
                continue

            insns = []
            for i in range(0, min(len(raw), read_size), 4):
                insn = struct.unpack('<I', raw[i:i + 4])[0]
                insns.append(insn)
                if insn == 0xD65F03C0 or (insn & 0xFFFFFC1F) == 0xD61F0000:
                    break

            cat = classify_function(insns, size)
            categories[cat] += 1
            by_category[cat].append((addr, size, name))

    # Categorize into difficulty tiers
    easy = ['noop', 'trampoline', 'tiny_stub', 'vtable_dispatch',
            'vtable_dispatch_bool', 'vtable_dispatch_ext', 'field_accessor',
            'tail_call']
    medium = ['framed_vtable_call', 'ctor_dtor_small', 'small_with_calls',
              'small_tail_call', 'simd_small', 'computation_small']
    hard = ['medium_with_calls', 'complex_tail_call', 'simd_complex',
            'computation_medium', 'complex_small']
    very_hard = ['large_with_calls', 'computation_large', 'complex_medium',
                 'complex_large']

    easy_count = sum(categories[c] for c in easy)
    medium_count = sum(categories[c] for c in medium)
    hard_count = sum(categories[c] for c in hard)
    very_hard_count = sum(categories[c] for c in very_hard)

    print("  By difficulty tier:")
    print("    EASY (automatable):      %5d  — vtable dispatch, stubs, field access" % easy_count)
    print("    MEDIUM (per-function):   %5d  — framed calls, constructors, small logic" % medium_count)
    print("    HARD (complex):          %5d  — multi-call, SIMD, computation" % hard_count)
    print("    VERY HARD (large):       %5d  — 100+ insn game logic" % very_hard_count)
    print()

    print("  By category:")
    for cat, count in categories.most_common():
        tier = 'EASY' if cat in easy else 'MED' if cat in medium else 'HARD' if cat in hard else 'VHARD'
        example = by_category[cat][0] if by_category[cat] else None
        ex_str = " (e.g. %s, %dB)" % (example[2], example[1]) if example else ""
        print("    %-25s %5d  [%s]%s" % (cat, count, tier, ex_str))

    if actionable_only:
        print()
        print("=" * 60)
        print("  Actionable functions (EASY tier)")
        print("=" * 60)
        for cat in easy:
            funcs = by_category[cat]
            if funcs:
                print()
                print("  %s (%d):" % (cat, len(funcs)))
                for addr, size, name in funcs[:10]:
                    print("    0x%x  %dB  %s" % (addr, size, name))
                if len(funcs) > 10:
                    print("    ... +%d more" % (len(funcs) - 10))

    if do_export:
        export_path = PROJECT_ROOT / "data" / "fun_triage.csv"
        with open(export_path, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['Address', 'Size', 'Name', 'Category', 'Tier'])
            for cat, funcs in sorted(by_category.items()):
                tier = 'EASY' if cat in easy else 'MEDIUM' if cat in medium else 'HARD' if cat in hard else 'VERY_HARD'
                for addr, size, name in funcs:
                    writer.writerow(['0x%016x' % addr, size, name, cat, tier])
        print()
        print("  Exported to %s" % export_path)


if __name__ == '__main__':
    main()
