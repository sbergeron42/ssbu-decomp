#!/usr/bin/env python3
"""
Generate networking/threading/memory function stubs for pool-d worker.
Creates src/app/network_functions.cpp, threading_functions.cpp, memory_functions.cpp
"""

import csv
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
ELF_BASE = 0x7100000000

DOMAIN_KEYWORDS = {
    'network': ['curl', 'ssl', 'socket', 'http', 'network', 'resolver', 'siglo',
                'nnssl', 'nnsocket', 'tls', 'nncurl'],
    'threading': ['mutex', 'thread', 'fiber', 'lock', 'semaphore', 'yield',
                  'nnosmutex', 'nnosthread', 'nnoslock', 'nnos', 'pthread',
                  'recursive_mutex', 'try_lock', 'clocksnapshot'],
    'memory': ['heap', 'alloc', 'malloc', 'free', 'memory', 'pool',
               'bufferallocator', 'standardallocator', 'frameheap',
               'cxa_allocate', 'cxa_free', 'bad_alloc', 'reallocate'],
}

def classify(name):
    nl = name.lower()
    for domain, keys in DOMAIN_KEYWORDS.items():
        if any(k in nl for k in keys):
            return domain
    return None


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
            if p_type == 1:
                segments.append((p_vaddr, p_offset, p_filesz))
    return segments


def read_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


def decode_insns(raw, max_insns=16):
    insns = []
    for i in range(0, min(len(raw), max_insns * 4), 4):
        if i + 4 > len(raw):
            break
        insn = struct.unpack('<I', raw[i:i+4])[0]
        insns.append(insn)
        if insn == 0xD65F03C0 or (insn & 0xFFFFFC1F) == 0xD61F0000:
            break
    return insns


def safe_name(name, addr):
    n = name.replace('.', '_').replace('::', '_').replace('<', '_').replace('>', '_')
    n = n.replace(',', '_').replace(' ', '_').replace('?', '_').replace('~', 'dtor_').replace('*', 'ptr')
    return '%s_%x' % (n, addr & 0xFFFFFFFF)


def is_trampoline(insns):
    """Return True if this is a PLT stub / branch-only trampoline."""
    for i in insns:
        if (i & 0xFC000000) == 0x14000000:  # b imm
            return True
        if (i & 0xFC000000) == 0x94000000:  # bl imm
            return True
    return False


def try_generate(name, addr, insns):
    n = len(insns)
    if n == 0:
        return None
    last = insns[-1]
    has_ret = last == 0xD65F03C0
    has_br  = (last & 0xFFFFFC1F) == 0xD61F0000
    fn = safe_name(name, addr)

    # Skip trampolines
    if is_trampoline(insns):
        return None

    # 1-insn ret → noop
    if n == 1 and has_ret:
        return 'void %s(void*) { }' % fn

    # 2-insn: add x0,x0,#imm; ret → return pointer to field
    if n == 2 and has_ret and (insns[0] & 0xFFC00000) == 0x91000000:
        rd = insns[0] & 0x1F; rn = (insns[0] >> 5) & 0x1F
        if rd == 0 and rn == 0:
            imm = (insns[0] >> 10) & 0xFFF
            return 'void* %s(void* obj) { return reinterpret_cast<u8*>(obj) + %s; }' % (fn, hex(imm))

    # 2-insn: ldr x0,[x0,#imm]; ret
    if n == 2 and has_ret:
        i0 = insns[0]
        if (i0 & 0xFFC00000) == 0xF9400000 and (i0 & 0x1F) == 0 and ((i0>>5)&0x1F) == 0:
            imm = ((i0 >> 10) & 0xFFF) * 8
            return 'u64 %s(void* obj) { return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm))
        if (i0 & 0xFFC00000) == 0xB9400000 and (i0 & 0x1F) == 0 and ((i0>>5)&0x1F) == 0:
            imm = ((i0 >> 10) & 0xFFF) * 4
            return 'u32 %s(void* obj) { return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm))
        if (i0 & 0xFFC00000) == 0x39400000 and (i0 & 0x1F) == 0 and ((i0>>5)&0x1F) == 0:
            imm = (i0 >> 10) & 0xFFF
            return 'u8 %s(void* obj) { return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm))
        # strb wzr, [x0, #imm]; ret → clear byte flag
        if (i0 & 0xFFC00000) == 0x39000000 and (i0 & 0x1F) == 31:
            imm = (i0 >> 10) & 0xFFF
            return 'void %s(void* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(imm))

    # 3-insn vtable dispatch
    if n == 3 and has_br:
        i0, i1 = insns[0], insns[1]
        if ((i0 & 0xFFC00000) == 0xF9400000 and (i1 & 0xFFC00000) == 0xF9400000
                and (i0 & 0x1F) == 8 and ((i0>>5)&0x1F) == 0
                and ((i1>>5)&0x1F) == 8):
            vt_off = ((i1 >> 10) & 0xFFF) * 8
            br_reg = (last >> 5) & 0x1F
            nparams = br_reg - 1
            params = ['void* obj'] + ['u64 p%d' % (k+1) for k in range(nparams)]
            args   = ['obj'] + ['p%d' % (k+1) for k in range(nparams)]
            cparams = ['void*'] + ['u64'] * nparams
            return 'void* %s(%s) { return reinterpret_cast<void*(*)(%s)>((*reinterpret_cast<void***>(obj))[%s/8])(%s); }' % (
                fn, ','.join(params), ','.join(cparams), hex(vt_off), ','.join(args))

    # 3-insn field-through-pointer read
    if n == 3 and has_ret:
        i0, i1 = insns[0], insns[1]
        if (i0 & 0xFFC00000) == 0xF9400000 and (i0 & 0x1F) == 8 and ((i0>>5)&0x1F) == 0:
            off1 = ((i0 >> 10) & 0xFFF) * 8
            if (i1 & 0xFFC00000) == 0xF9400000 and (i1 & 0x1F) == 0 and ((i1>>5)&0x1F) == 8:
                off2 = ((i1 >> 10) & 0xFFF) * 8
                return 'u64 %s(void* obj) { auto* p = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(obj) + %s); return *reinterpret_cast<u64*>(p + %s); }' % (fn, hex(off1), hex(off2))
            if (i1 & 0xFFC00000) == 0xB9400000 and (i1 & 0x1F) == 0 and ((i1>>5)&0x1F) == 8:
                off2 = ((i1 >> 10) & 0xFFF) * 4
                return 'u32 %s(void* obj) { auto* p = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(obj) + %s); return *reinterpret_cast<u32*>(p + %s); }' % (fn, hex(off1), hex(off2))
            if (i1 & 0xFFC00000) == 0x39400000 and (i1 & 0x1F) == 0 and ((i1>>5)&0x1F) == 8:
                off2 = (i1 >> 10) & 0xFFF
                return 'u8 %s(void* obj) { auto* p = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(obj) + %s); return *reinterpret_cast<u8*>(p + %s); }' % (fn, hex(off1), hex(off2))

    # 3-insn: mov imm + strb + ret (set byte flag)
    if n == 3 and has_ret and (insns[0] & 0xFF800000) == 0x52800000 and (insns[1] & 0xFFC00000) == 0x39000000:
        val = (insns[0] >> 5) & 0xFFFF
        off = (insns[1] >> 10) & 0xFFF
        return 'void %s(void* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = %d; }' % (fn, hex(off), val)

    return None


def main():
    do_apply = '--apply' in sys.argv

    segments = load_elf_segments(ORIGINAL_ELF)

    # Collect domain targets ≤64B undecompiled
    targets = {'network': [], 'threading': [], 'memory': []}
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f); next(reader)
        for row in reader:
            if row[1] != 'U': continue
            addr = int(row[0], 16)
            size = int(row[2])
            name = row[3]
            if size > 64: continue
            if name.startswith('FUN_'): continue
            domain = classify(name)
            if domain:
                targets[domain].append((addr, size, name))

    for d, lst in targets.items():
        print("Domain %s: %d candidates" % (d, len(lst)))

    generated = {'network': [], 'threading': [], 'memory': []}
    skipped   = {'network': 0, 'threading': 0, 'memory': 0}

    with open(ORIGINAL_ELF, 'rb') as f:
        for domain, lst in targets.items():
            for addr, size, name in lst:
                vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
                raw = read_bytes(f, segments, vaddr, max(size, 32))
                if not raw:
                    skipped[domain] += 1
                    continue
                insns = decode_insns(raw)
                code = try_generate(name, addr, insns)
                if code:
                    generated[domain].append((name, addr, code))
                else:
                    skipped[domain] += 1

    for d in generated:
        print("Generated %-12s: %d  (skipped %d)" % (d, len(generated[d]), skipped[d]))

    if not do_apply:
        print()
        print("Sample output:")
        for domain, lst in generated.items():
            print("  -- %s --" % domain)
            for name, addr, code in lst[:4]:
                print("    %s" % code[:100])
        print()
        print("Use --apply to write files.")
        return

    # Write source files
    src_dir = PROJECT_ROOT / 'src' / 'app'
    file_map = {
        'network':   src_dir / 'network_functions.cpp',
        'threading': src_dir / 'threading_functions.cpp',
        'memory':    src_dir / 'memory_functions.cpp',
    }

    for domain, filepath in file_map.items():
        funcs = generated[domain]
        if not funcs:
            print("  %s: nothing to write" % domain)
            continue
        lines = ['#include "types.h"', '', '// Auto-generated pool-d: %s functions' % domain, '']
        for name, addr, code in funcs:
            lines.append('// 0x%x  %s' % (addr, name))
            lines.append(code)
        lines.append('')
        filepath.write_text('\n'.join(lines))
        print("  Wrote %s: %d functions" % (filepath.name, len(funcs)))


if __name__ == '__main__':
    main()
