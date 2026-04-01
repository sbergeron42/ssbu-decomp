#!/usr/bin/env python3
"""
Generate src/app/engine_functions.cpp — auto-generates C++ for named engine utility
functions (Initialize, Finalize, Set*, Get*, thunk_*, Create, Destroy, Update, Calc,
Reset, Clear, Init, Final) that are undecompiled (Quality='U'), named (not FUN_* or __),
and <= 64 bytes.

Reads actual AArch64 bytes from data/main.elf, applies instruction-pattern matching,
and emits readable C++ stubs.  Functions with unrecognised patterns are silently skipped.

Usage:
    python tools/gen_engine_functions.py          # dry run
    python tools/gen_engine_functions.py --apply  # write engine_functions.cpp
"""

import csv
import re
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF  = PROJECT_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
OUTPUT_CPP    = PROJECT_ROOT / "src" / "app" / "engine_functions.cpp"

ELF_BASE = 0x7100000000

ENGINE_PATTERNS = [
    'Initialize', 'Finalize', 'Set', 'Get', 'thunk_',
    'Create', 'Destroy', 'Update', 'Calc', 'Reset', 'Clear', 'Init', 'Final',
]

MAX_SIZE = 64   # bytes


# ── ELF helpers ───────────────────────────────────────────────────────────────

def load_elf_segments(path):
    segs = []
    with open(path, 'rb') as f:
        f.seek(0x20);  phoff     = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36);  phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type   = struct.unpack('<I', f.read(4))[0];  f.read(4)
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr  = struct.unpack('<Q', f.read(8))[0];  f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1:
                segs.append((p_vaddr, p_offset, p_filesz))
    return segs


def read_bytes_at(f, segs, vaddr, size):
    for sv, so, sf in segs:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


# ── AArch64 bitmask-immediate decoder ────────────────────────────────────────

def decode_bitmask_imm32(N, immr, imms):
    """Return the 32-bit value encoded by an AArch64 bitmask immediate."""
    e = 64 if N else 32
    ones = imms + 1
    if ones >= e:
        return None           # all-ones or reserved
    pattern = (1 << ones) - 1
    mask_e  = (1 << e) - 1
    rotated = ((pattern >> immr) | (pattern << (e - immr))) & mask_e
    val = 0
    for shift in range(0, 32, e):
        val |= (rotated << shift)
    return val & 0xFFFFFFFF


# ── Name sanitisation ─────────────────────────────────────────────────────────

_UNSAFE = re.compile(r'[^A-Za-z0-9_]')

def make_safe_ident(name):
    s = (name
         .replace('::', '_').replace('.', '_')
         .replace('<', '_').replace('>', '_')
         .replace(',', '_').replace(' ', '_')
         .replace('?', '_').replace('~', 'dtor_').replace('*', 'ptr'))
    return _UNSAFE.sub('_', s)


def func_cname(name, addr):
    return '%s_%x' % (make_safe_ident(name), addr & 0xFFFFFFFF)


# ── Instruction-pattern engine ────────────────────────────────────────────────

RET = 0xD65F03C0

def is_ret(w): return w == RET
def is_br(w):  return (w & 0xFFFFFC1F) == 0xD61F0000   # br xN
def is_b(w):   return (w & 0xFC000000) == 0x14000000   # b #imm (unconditional)
def is_bl(w):  return (w & 0xFC000000) == 0x94000000   # bl #imm
def is_adrp(w):return (w & 0x9F000000) == 0x90000000   # adrp xN, page


def decode_insns(raw, limit=16):
    """Decode up to `limit` 4-byte words from `raw`, stopping after ret/br."""
    insns = []
    for off in range(0, min(len(raw), limit * 4), 4):
        w = struct.unpack('<I', raw[off:off + 4])[0]
        insns.append(w)
        if is_ret(w) or is_br(w):
            break
    return insns


def generate(name, addr, insns):
    """
    Try to match instruction patterns and return (c_code, pattern_tag).
    Returns (None, None) when no pattern matches.
    """
    if not insns:
        return None, None

    n    = len(insns)
    last = insns[-1]
    fn   = func_cname(name, addr)

    # Reject anything containing an indirect call or adrp (complex enough to skip)
    if any(is_bl(i) or is_adrp(i) for i in insns):
        return None, None

    # ── 1-instruction ─────────────────────────────────────────────────────────

    # Pattern 1: ret only → empty stub
    if n == 1 and is_ret(last):
        return 'void %s(void* obj) { }' % fn, 'noop'

    # Pattern 2: unconditional branch (trampoline) — skip; can't reproduce target
    if n == 1 and is_b(last):
        return None, None

    # Any remaining branch-containing sequence → skip
    if any(is_b(i) for i in insns):
        return None, None

    # ── 2-instruction ─────────────────────────────────────────────────────────

    if n == 2 and is_ret(last):
        i0   = insns[0]
        mask = i0 & 0xFFC00000
        rd   = i0 & 0x1F
        rn   = (i0 >> 5) & 0x1F

        # Pattern 3: add x0, x0, #imm; ret  → return pointer to field
        if mask == 0x91000000 and rd == 0 and rn == 0:
            imm = (i0 >> 10) & 0xFFF
            return ('void* %s(void* obj) { return reinterpret_cast<u8*>(obj) + %s; }' % (fn, hex(imm)),
                    'add-ret-ptr')

        # Pattern 4: ldr x0, [x0, #imm]; ret  → u64 field read
        if mask == 0xF9400000 and rd == 0 and rn == 0:
            imm = ((i0 >> 10) & 0xFFF) * 8
            return ('u64 %s(void* obj) { return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm)),
                    'ldr-x0-ret')

        # Pattern 5: ldr w0, [x0, #imm]; ret  → u32 field read
        if mask == 0xB9400000 and rd == 0 and rn == 0:
            imm = ((i0 >> 10) & 0xFFF) * 4
            return ('u32 %s(void* obj) { return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm)),
                    'ldr-w0-ret')

        # Pattern 6: ldrb w0, [x0, #imm]; ret  → u8 field read
        if mask == 0x39400000 and rd == 0 and rn == 0:
            imm = (i0 >> 10) & 0xFFF
            return ('u8 %s(void* obj) { return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm)),
                    'ldrb-w0-ret')

        # Pattern 6b: ldrh w0, [x0, #imm]; ret  → u16 field read
        if mask == 0x79400000 and rd == 0 and rn == 0:
            imm = ((i0 >> 10) & 0xFFF) * 2
            return ('u16 %s(void* obj) { return *reinterpret_cast<u16*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm)),
                    'ldrh-w0-ret')

        # Pattern 6c: ldr s0, [x0, #imm]; ret  → f32 field read (0xBD400000)
        if mask == 0xBD400000 and rd == 0 and rn == 0:
            imm = ((i0 >> 10) & 0xFFF) * 4
            return ('f32 %s(void* obj) { return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(obj) + %s); }' % (fn, hex(imm)),
                    'ldr-s0-ret')

        # Pattern 9a: strb wzr, [x0, #imm]; ret  → clear byte field
        if mask == 0x39000000 and rd == 31 and rn == 0:
            off = (i0 >> 10) & 0xFFF
            return ('void %s(void* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(off)),
                    'strb-wzr-ret')

        # Pattern 9b: str xzr, [x0, #imm]; ret  → clear u64 field
        if mask == 0xF9000000 and rd == 31 and rn == 0:
            off = ((i0 >> 10) & 0xFFF) * 8
            return ('void %s(void* obj) { *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(off)),
                    'str-xzr-ret')

        # Pattern 9c: str wzr, [x0, #imm]; ret  → clear u32 field
        if mask == 0xB9000000 and rd == 31 and rn == 0:
            off = ((i0 >> 10) & 0xFFF) * 4
            return ('void %s(void* obj) { *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(off)),
                    'str-wzr-ret')

        # Pattern 10: orr w0, wzr, #imm; ret  → return constant (bitmask-encoded)
        if (i0 & 0xFF800000) == 0x32000000 and rd == 0 and rn == 31:
            N    = (i0 >> 22) & 1
            immr = (i0 >> 16) & 0x3F
            imms = (i0 >> 10) & 0x3F
            val  = decode_bitmask_imm32(N, immr, imms)
            if val is not None:
                return ('u32 %s(void* obj) { return %s; }' % (fn, hex(val)),
                        'orr-imm-ret')

        # Pattern 11: str w1, [x0, #imm]; ret  → u32 field setter from first param
        if mask == 0xB9000000 and rd == 1 and rn == 0:
            off = ((i0 >> 10) & 0xFFF) * 4
            return ('void %s(void* obj, u32 val) { *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (fn, hex(off)),
                    'str-w1-ret')

        # Pattern 11b: strh w1, [x0, #imm]; ret  → u16 field setter
        if mask == 0x79000000 and rd == 1 and rn == 0:
            off = ((i0 >> 10) & 0xFFF) * 2
            return ('void %s(void* obj, u16 val) { *reinterpret_cast<u16*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (fn, hex(off)),
                    'strh-w1-ret')

        # Pattern 11c: strb w1, [x0, #imm]; ret  → u8 field setter
        if mask == 0x39000000 and rd == 1 and rn == 0:
            off = (i0 >> 10) & 0xFFF
            return ('void %s(void* obj, u8 val) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (fn, hex(off)),
                    'strb-w1-ret')

        # Pattern 11d: str x1, [x0, #imm]; ret  → u64 field setter from first param
        if mask == 0xF9000000 and rd == 1 and rn == 0:
            off = ((i0 >> 10) & 0xFFF) * 8
            return ('void %s(void* obj, u64 val) { *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = val; }' % (fn, hex(off)),
                    'str-x1-ret')

        # Pattern 12: stp xzr, xzr, [x0, #imm]; ret  → clear two consecutive u64 fields
        # STP Xt1, Xt2, [Xn, #imm]: encoding 0xA9000000 (64-bit, signed offset)
        if (i0 & 0xFFC00000) == 0xA9000000:
            rt1 = i0 & 0x1F
            rn0 = (i0 >> 5) & 0x1F
            rt2 = (i0 >> 10) & 0x1F
            imm7 = (i0 >> 15) & 0x7F
            if imm7 & 0x40: imm7 -= 0x80  # sign-extend
            off = imm7 * 8
            if rn0 == 0 and rt1 == 31 and rt2 == 31:
                return ('void %s(void* obj) { *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = 0; *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(off), hex(off + 8)),
                        'stp-xzr-xzr-ret')

    # ── 3-instruction ─────────────────────────────────────────────────────────

    if n == 3:
        i0, i1, i2 = insns

        # Pattern 8: vtable dispatch — ldr x8,[x0]; ldr xN,[x8,#vt_off]; br xN
        if is_br(i2):
            ldr0_x8 = ((i0 & 0xFFC00000) == 0xF9400000 and
                       (i0 & 0x1F) == 8 and ((i0 >> 5) & 0x1F) == 0 and
                       ((i0 >> 10) & 0xFFF) == 0)
            ldr1_ok  = ((i1 & 0xFFC00000) == 0xF9400000 and ((i1 >> 5) & 0x1F) == 8)
            if ldr0_x8 and ldr1_ok:
                br_reg  = (i2 >> 5) & 0x1F
                vt_off  = ((i1 >> 10) & 0xFFF) * 8
                nparams = max(0, br_reg - 1)
                params      = ['void* obj'] + ['u64 p%d' % k for k in range(1, nparams + 1)]
                args        = ['obj']        + ['p%d'   % k for k in range(1, nparams + 1)]
                cast_params = ['void*']      + ['u64']       * nparams
                code = ('void* %s(%s) { return reinterpret_cast<void*(*)(%s)>((*reinterpret_cast<void***>(obj))[%s/8])(%s); }'
                        % (fn, ', '.join(params), ', '.join(cast_params), hex(vt_off), ', '.join(args)))
                return code, 'vtable-dispatch'

        if is_ret(i2):
            # Pattern 9d: mov wN, #imm16 + strb wN, [x0, #off]; ret  → set byte to constant
            if ((i0 & 0xFF800000) == 0x52800000 and
                    (i1 & 0xFFC00000) == 0x39000000 and ((i1 >> 5) & 0x1F) == 0):
                val = (i0 >> 5) & 0xFFFF
                off = (i1 >> 10) & 0xFFF
                return ('void %s(void* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = %d; }' % (fn, hex(off), val),
                        'mov-strb-ret')

            # Pattern 9e: movz wN, #imm + stp xN, xzr, [x0, #off]; ret → set u64 pair
            if ((i0 & 0xFF800000) == 0x52800000 and (i0 & 0x1F) == 8 and
                    (i1 & 0xFFC00000) == 0xA9000000):
                imm_val = (i0 >> 5) & 0xFFFF
                rt1 = i1 & 0x1F; rn0 = (i1 >> 5) & 0x1F; rt2 = (i1 >> 10) & 0x1F
                imm7 = (i1 >> 15) & 0x7F
                if imm7 & 0x40: imm7 -= 0x80
                off = imm7 * 8
                if rt1 == 8 and rn0 == 0 and rt2 == 31:
                    return ('void %s(void* obj) { *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = %s; *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(off), hex(imm_val), hex(off + 8)),
                            'movz-stp-ret')

            # Pattern 7: ldr x8,[x0,#off1]; ldr/ldrb/ldrh/ldr_w/ldr_f x0,[x8,#off2]; ret
            if ((i0 & 0xFFC00000) == 0xF9400000 and
                    (i0 & 0x1F) == 8 and ((i0 >> 5) & 0x1F) == 0):
                off1  = ((i0 >> 10) & 0xFFF) * 8
                rt1   = i1 & 0x1F
                rn1   = (i1 >> 5) & 0x1F
                mask1 = i1 & 0xFFC00000
                if rn1 == 8 and rt1 == 0:
                    if   mask1 == 0xF9400000: off2, rtype = ((i1 >> 10) & 0xFFF) * 8, 'u64'
                    elif mask1 == 0xB9400000: off2, rtype = ((i1 >> 10) & 0xFFF) * 4, 'u32'
                    elif mask1 == 0x39400000: off2, rtype = (i1 >> 10) & 0xFFF,        'u8'
                    elif mask1 == 0x79400000: off2, rtype = ((i1 >> 10) & 0xFFF) * 2,  'u16'
                    elif mask1 == 0xBD400000: off2, rtype = ((i1 >> 10) & 0xFFF) * 4,  'f32'
                    else:
                        return None, None
                    code = ('%s %s(void* obj) { auto* p = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(obj) + %s); return *reinterpret_cast<%s*>(p + %s); }'
                            % (rtype, fn, hex(off1), rtype, hex(off2)))
                    return code, 'deref-field'

    # ── 4-instruction ─────────────────────────────────────────────────────────

    if n == 4 and is_ret(last):
        i0, i1, i2, i3 = insns

        # Pattern 14: orr w8, wzr, #bitmask; str w8, [x0, #off1]; strb wzr, [x0, #off2]; ret
        if ((i0 & 0xFF800000) == 0x32000000 and (i0 & 0x1F) == 8 and ((i0 >> 5) & 0x1F) == 31 and
                (i1 & 0xFFC00000) == 0xB9000000 and (i1 & 0x1F) == 8 and ((i1 >> 5) & 0x1F) == 0 and
                (i2 & 0xFFC00000) == 0x39000000 and (i2 & 0x1F) == 31 and ((i2 >> 5) & 0x1F) == 0):
            N    = (i0 >> 22) & 1; immr = (i0 >> 16) & 0x3F; imms = (i0 >> 10) & 0x3F
            val  = decode_bitmask_imm32(N, immr, imms)
            off1 = ((i1 >> 10) & 0xFFF) * 4
            off2 = (i2 >> 10) & 0xFFF
            if val is not None:
                return ('void %s(void* obj) { *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + %s) = %s; *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (fn, hex(off1), hex(val), hex(off2)),
                        'orr-str-strb-ret')

    # ── 4+ instruction patterns ───────────────────────────────────────────────

    # Pattern 13: sequence of str/strb/strh xzr/wzr + ret → multi-field clear
    # All instructions except the last must be zero-stores to [x0, #imm]
    if n >= 3 and is_ret(last):
        stores = []
        valid = True
        for w in insns[:-1]:
            rn = (w >> 5) & 0x1F
            rd = w & 0x1F
            mask_w = w & 0xFFC00000
            if rn != 0 or rd != 31:
                valid = False; break
            if mask_w == 0xF9000000:   # str xzr, [x0, #imm]
                off = ((w >> 10) & 0xFFF) * 8; stores.append(('u64', off))
            elif mask_w == 0xB9000000: # str wzr, [x0, #imm]
                off = ((w >> 10) & 0xFFF) * 4; stores.append(('u32', off))
            elif mask_w == 0x39000000: # strb wzr, [x0, #imm]
                off = (w >> 10) & 0xFFF; stores.append(('u8', off))
            elif mask_w == 0x79000000: # strh wzr, [x0, #imm]
                off = ((w >> 10) & 0xFFF) * 2; stores.append(('u16', off))
            elif (w & 0xFFC00000) == 0xA9000000:  # stp xzr,xzr,[x0,#imm]
                rt1 = w & 0x1F; rt2 = (w >> 10) & 0x1F; rn0 = (w >> 5) & 0x1F
                imm7 = (w >> 15) & 0x7F
                if imm7 & 0x40: imm7 -= 0x80
                off = imm7 * 8
                if rn0 == 0 and rt1 == 31 and rt2 == 31:
                    stores.append(('u64', off)); stores.append(('u64', off + 8))
                else:
                    valid = False; break
            else:
                valid = False; break
        if valid and stores and len(stores) <= 5:  # skip large multi-store (compiler may reorder)
            parts = ['*reinterpret_cast<%s*>(reinterpret_cast<u8*>(obj) + %s) = 0' % (t, hex(o)) for t, o in stores]
            code = 'void %s(void* obj) { %s; }' % (fn, '; '.join(parts))
            return code, 'multi-zero'

    return None, None


# ── Main ──────────────────────────────────────────────────────────────────────

def main():
    do_apply = '--apply' in sys.argv

    print('Loading ELF segments ...')
    segs = load_elf_segments(str(ORIGINAL_ELF))

    print('Scanning functions.csv ...')
    targets = []
    with open(str(FUNCTIONS_CSV)) as f:
        for row in csv.reader(f):
            if row[0] == 'Address':
                continue
            if row[1] != 'U':
                continue
            name = row[3]
            if name.startswith('FUN_') or name.startswith('__'):
                continue
            if int(row[2]) > MAX_SIZE:
                continue
            if not any(p in name for p in ENGINE_PATTERNS):
                continue
            targets.append((int(row[0], 16), name, int(row[2])))

    print('Candidates: %d' % len(targets))

    generated = []   # (addr, orig_name, pattern, code)
    skipped   = 0

    with open(str(ORIGINAL_ELF), 'rb') as elf:
        for addr, name, size in targets:
            vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
            raw   = read_bytes_at(elf, segs, vaddr, max(size, 64))
            if not raw or len(raw) < 4:
                skipped += 1
                continue

            insns = decode_insns(raw, limit=MAX_SIZE // 4)
            code, pat = generate(name, addr, insns)
            if code is None:
                skipped += 1
                continue

            generated.append((addr, name, pat, code))

    # Summary
    from collections import Counter
    pat_counts = Counter(pat for _, _, pat, _ in generated)
    print('Generated: %d  |  Skipped: %d' % (len(generated), skipped))
    print('Pattern breakdown:')
    for pat, cnt in sorted(pat_counts.items(), key=lambda x: -x[1]):
        print('  %-22s %d' % (pat, cnt))

    if not do_apply:
        print()
        print('Sample (first 12):')
        for addr, name, pat, code in generated[:12]:
            print('  [%s] %s' % (pat, code[:120]))
        print()
        print('Run with --apply to write %s' % OUTPUT_CPP)
        return

    # ── Emit C++ ─────────────────────────────────────────────────────────────
    lines = [
        '#include "types.h"',
        '',
        '// Engine utility functions — Initialize, Finalize, Set*, Get*, thunk_*, etc.',
        '// AUTO-GENERATED by tools/gen_engine_functions.py — do not hand-edit.',
        '//',
        '// Generated: %d functions  |  Skipped: %d (no recognized pattern)' % (len(generated), skipped),
        '',
        'namespace app::lua_bind {',
        '',
        '// AUTO-GENERATED EASY functions',
        '',
    ]

    for addr, name, pat, code in generated:
        lines.append('// 0x%x  [%s]  %s' % (addr, pat, name))
        lines.append(code)
        lines.append('')

    lines += ['} // namespace app::lua_bind', '']

    content = '\n'.join(lines)
    OUTPUT_CPP.write_text(content, encoding='utf-8')
    print('Written: %s  (%d lines)' % (OUTPUT_CPP, len(lines)))


if __name__ == '__main__':
    main()
