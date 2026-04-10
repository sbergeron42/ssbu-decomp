#!/usr/bin/env python3
"""
Classify ALL instruction-level differences between decomp and original binary.
Focuses on functions with 1-3 diffs (easiest to trace to root cause).
"""

import struct, csv, sys
from pathlib import Path
from collections import Counter, defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
CSV = PROJECT_ROOT / "data" / "functions.csv"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000


def load_segs(path):
    segs = []
    with open(path, 'rb') as f:
        f.seek(0x20); phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36); phes = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phes)
            pt = struct.unpack('<I', f.read(4))[0]; f.read(4)
            po = struct.unpack('<Q', f.read(8))[0]
            pv = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            pf = struct.unpack('<Q', f.read(8))[0]
            if pt == 1:
                segs.append((pv, po, pf))
    return segs


def read_at(f, segs, va, sz):
    for sv, so, sf in segs:
        if sv <= va < sv + sf:
            f.seek(so + (va - sv))
            return f.read(sz)
    return None


def short_name(mangled):
    if not mangled.startswith('_Z'):
        return mangled
    if mangled.startswith('_ZN'):
        rest = mangled[3:]
        last = mangled
        while rest and rest[0] != 'E':
            i = 0
            while i < len(rest) and rest[i].isdigit():
                i += 1
            if i == 0:
                break
            ln = int(rest[:i])
            nm = rest[i:i + ln]
            if len(nm) < ln:
                break
            last = nm
            rest = rest[i + ln:]
        return last
    rest = mangled[2:]
    i = 0
    while i < len(rest) and rest[i].isdigit():
        i += 1
    if i > 0:
        ln = int(rest[:i])
        nm = rest[i:i + ln]
        if len(nm) >= ln:
            return nm
    return mangled


def classify_diff(orig, decomp):
    xor = orig ^ decomp

    # Pure width bit (bit 31 only)
    if xor == 0x80000000:
        return 'WIDTH_BIT_ONLY'

    # Branch offset (B / BL)
    if (orig >> 26) in (0x05, 0x25) and (decomp >> 26) in (0x05, 0x25):
        return 'BRANCH_OFFSET'

    # ADRP page offset
    if (orig & 0x9F000000) == 0x90000000 and (decomp & 0x9F000000) == 0x90000000:
        return 'ADRP_OFFSET'

    # LDR/STR with different unsigned immediate (relocation)
    if (orig & 0xFF800000) == (decomp & 0xFF800000) and \
       (orig & 0x1F) == (decomp & 0x1F) and \
       ((orig >> 5) & 0x1F) == ((decomp >> 5) & 0x1F):
        top9 = (orig >> 23) & 0x1FF
        if top9 in range(0x170, 0x180) or top9 in range(0x178, 0x180) or \
           (orig & 0x3B000000) == 0x39000000:  # LDR/STR unsigned offset
            return 'LDST_OFFSET_RELOC'

    # ADD immediate with different imm12 (relocation: ADD_ABS_LO12)
    if (orig & 0xFF000000) == (decomp & 0xFF000000) == 0x91000000 and \
       (orig & 0x3FF) == (decomp & 0x3FF):
        return 'ADD_IMM_RELOC'

    # Same base opcode, check register fields
    if (orig & 0xFFE00C00) == (decomp & 0xFFE00C00):
        rd_o, rd_d = orig & 0x1F, decomp & 0x1F
        rn_o, rn_d = (orig >> 5) & 0x1F, (decomp >> 5) & 0x1F
        rm_o, rm_d = (orig >> 16) & 0x1F, (decomp >> 16) & 0x1F
        imm6_o = (orig >> 10) & 0x3F
        imm6_d = (decomp >> 10) & 0x3F
        if rd_o == rd_d and imm6_o == imm6_d == 0:
            if rn_o == rm_d and rm_o == rn_d:
                return 'COMMUTATIVE_SWAP'
            if (rn_o != rn_d) != (rm_o != rm_d):
                return 'ONE_REG_DIFF'
            if rn_o != rn_d and rm_o != rm_d:
                return 'TWO_REG_DIFF'
        if rd_o != rd_d and rn_o == rn_d and rm_o == rm_d:
            return 'DST_REG_DIFF'

    # MOVZ vs ORR encoding
    if ((orig & 0xFF800000) in (0x52800000, 0xD2800000) and
            (decomp & 0xBF800000) in (0x32000000, 0xB2000000)):
        return 'MOVZ_vs_ORR'
    if ((decomp & 0xFF800000) in (0x52800000, 0xD2800000) and
            (orig & 0xBF800000) in (0x32000000, 0xB2000000)):
        return 'ORR_vs_MOVZ'

    # Width + other change
    if (orig >> 31) != (decomp >> 31):
        if (orig & 0x7FFFFFFF) == (decomp & 0x7FFFFFFF):
            return 'WIDTH_BIT_ONLY'  # shouldn't reach here but safety
        return 'WIDTH_PLUS_OTHER'

    # CBZ/CBNZ/TBZ/TBNZ offset difference
    if (orig >> 24) == (decomp >> 24) and (orig >> 24) in (0x34, 0x35, 0x36, 0x37, 0xB4, 0xB5):
        return 'COND_BRANCH_OFFSET'

    # B.cond offset
    if (orig >> 24) == (decomp >> 24) == 0x54:
        return 'BCOND_OFFSET'

    # Completely different top bits
    if (orig >> 25) != (decomp >> 25):
        return 'DIFFERENT_CLASS'

    return 'OTHER'


def main():
    segs = load_segs(str(ORIGINAL_ELF))

    csv_data = {}
    csv_by_short = {}
    with open(CSV) as f:
        for row in csv.DictReader(f):
            addr = int(row['Address'], 16)
            size = int(row['Size'])
            name = row['Name']
            csv_data[name] = (addr, size)
            s = short_name(name)
            if s not in csv_by_short:
                csv_by_short[s] = (addr, size)

    categories = Counter()
    examples = defaultdict(list)
    total_checked = 0
    funcs_with_few_diffs = 0

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for o_path in sorted(BUILD_DIR.glob('*.o')):
            data = o_path.read_bytes()
            if data[:4] != b'\x7fELF':
                continue
            try:
                shoff = struct.unpack_from('<Q', data, 0x28)[0]
                she = struct.unpack_from('<H', data, 0x3a)[0]
                shn = struct.unpack_from('<H', data, 0x3c)[0]
                shsi = struct.unpack_from('<H', data, 0x3e)[0]
                stro = struct.unpack_from('<Q', data, shoff + shsi * she + 0x18)[0]
                strs = struct.unpack_from('<Q', data, shoff + shsi * she + 0x20)[0]
                strtab = data[stro:stro + strs]

                for i in range(shn):
                    b = shoff + i * she
                    sno = struct.unpack_from('<I', data, b)[0]
                    sht = struct.unpack_from('<I', data, b + 4)[0]
                    end = strtab.index(b'\0', sno)
                    nm = strtab[sno:end].decode('ascii', 'replace')
                    if not nm.startswith('.text.') or sht != 1:
                        continue
                    so = struct.unpack_from('<Q', data, b + 0x18)[0]
                    ss = struct.unpack_from('<Q', data, b + 0x20)[0]
                    if ss < 4:
                        continue
                    mn = nm[6:]

                    # Lookup
                    if mn in csv_data:
                        addr, csz = csv_data[mn]
                    else:
                        s = short_name(mn)
                        if s in csv_by_short:
                            addr, csz = csv_by_short[s]
                        elif s in csv_data:
                            addr, csz = csv_data[s]
                        else:
                            continue
                    if csz != ss:
                        continue

                    va = addr - ELF_BASE if addr >= ELF_BASE else addr
                    ob = read_at(orig_f, segs, va, ss)
                    if not ob or len(ob) != ss:
                        continue

                    total_checked += 1
                    n = ss // 4
                    diffs = []
                    for j in range(n):
                        ow = struct.unpack_from('<I', ob, j * 4)[0]
                        dw = struct.unpack_from('<I', data, so + j * 4)[0]
                        if ow != dw:
                            diffs.append((j, ow, dw))

                    if len(diffs) == 0:
                        continue  # matches
                    if len(diffs) > 5:
                        continue  # too many diffs, skip for now

                    funcs_with_few_diffs += 1
                    for j, ow, dw in diffs:
                        cat = classify_diff(ow, dw)
                        categories[cat] += 1
                        if len(examples[cat]) < 4:
                            display = short_name(mn)
                            examples[cat].append(
                                (display[:40], j, ow, dw, n))
            except Exception:
                continue

    print("Checked %d functions, %d with 1-5 diffs" % (
        total_checked, funcs_with_few_diffs))
    print()
    total = sum(categories.values())
    print("%-25s %6s %6s" % ("Category", "Count", "%"))
    print("-" * 42)
    for cat, cnt in categories.most_common():
        pct = 100 * cnt / total if total else 0
        print("%-25s %6d %5.1f%%" % (cat, cnt, pct))
        for fn, off, o, d, ni in examples[cat][:2]:
            print("    %-35s [%3d/%3d] %08x -> %08x" % (fn, off, ni, o, d))
    print("%-25s %6d" % ("TOTAL", total))


if __name__ == '__main__':
    main()
