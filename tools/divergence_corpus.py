#!/usr/bin/env python3
"""
Build a structured divergence corpus from all >80% matching functions.
Extracts exact instruction diffs, classifies them, and ranks patterns by frequency.
"""
import struct, csv, sys
from pathlib import Path
from collections import Counter, defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
CSV = PROJECT_ROOT / "data" / "functions.csv"
BUILD_DIR = PROJECT_ROOT / "build"
ELF_BASE = 0x7100000000
OBJDUMP = "C:/llvm-8.0.0/bin/llvm-objdump.exe"

def load_segs(path):
    segs = []
    with open(path, 'rb') as f:
        f.seek(0x20); phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36); phes = struct.unpack('<H', f.read(2))[0]; phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i*phes); pt = struct.unpack('<I', f.read(4))[0]; f.read(4)
            po = struct.unpack('<Q', f.read(8))[0]; pv = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            pf = struct.unpack('<Q', f.read(8))[0]
            if pt == 1: segs.append((pv, po, pf))
    return segs

def read_at(f, segs, va, sz):
    for sv, so, sf in segs:
        if sv <= va < sv+sf: f.seek(so+(va-sv)); return f.read(sz)
    return None

def short_name(m):
    if not m.startswith('_Z'): return m
    if m.startswith('_ZN'):
        r=m[3:]; last=m
        while r and r[0]!='E':
            i=0
            while i<len(r) and r[i].isdigit(): i+=1
            if i==0: break
            ln=int(r[:i]); nm=r[i:i+ln]
            if len(nm)<ln: break
            last=nm; r=r[i+ln:]
        return last
    r=m[2:]; i=0
    while i<len(r) and r[i].isdigit(): i+=1
    if i>0:
        ln=int(r[:i]); nm=r[i:i+ln]
        if len(nm)>=ln: return nm
    return m


def classify_insn_diff(orig, decomp):
    """Classify a single instruction difference. Returns (category, detail)."""
    xor = orig ^ decomp

    # Relocation artifacts
    if (orig >> 26) in (0x05, 0x25) and (decomp >> 26) in (0x05, 0x25):
        return 'RELOC_BRANCH', 'B/BL offset'
    if (orig & 0x9F000000) == 0x90000000 and (decomp & 0x9F000000) == 0x90000000:
        return 'RELOC_ADRP', 'ADRP page'
    if (orig & 0x3B000000) == 0x39000000 and (decomp & 0x3B000000) == 0x39000000 and \
       (orig & 0x1F) == (decomp & 0x1F) and ((orig>>5)&0x1F) == ((decomp>>5)&0x1F):
        return 'RELOC_LDST', 'LDR/STR imm12'
    if (orig & 0xFF000000) in (0x11000000, 0x91000000) and \
       (decomp & 0xFF000000) in (0x11000000, 0x91000000) and \
       (orig & 0x3FF) == (decomp & 0x3FF):
        return 'RELOC_ADD', 'ADD imm12'
    if (orig >> 24) == (decomp >> 24) and (orig >> 24) in (0x34, 0x35, 0x36, 0x37, 0x54, 0xB4, 0xB5):
        return 'RELOC_CONDBR', 'CBZ/TBZ/Bcc offset'

    # Width bit only
    if xor == 0x80000000:
        sf_o = (orig >> 31) & 1
        return 'WIDTH', '64->32' if sf_o else '32->64'

    # Commutative swap (same opcode, Rn/Rm swapped, shift=0)
    if (orig & 0xFFE00C00) == (decomp & 0xFFE00C00):
        rd_o, rd_d = orig & 0x1F, decomp & 0x1F
        rn_o, rn_d = (orig>>5)&0x1F, (decomp>>5)&0x1F
        rm_o, rm_d = (orig>>16)&0x1F, (decomp>>16)&0x1F
        imm6 = (orig>>10)&0x3F
        if rd_o == rd_d and imm6 == 0:
            if rn_o == rm_d and rm_o == rn_d:
                return 'COMMUTATIVE', 'Rn/Rm swap'
            if rn_o != rn_d and rm_o == rm_d:
                return 'REG_RN', 'Rn: x%d->x%d' % (rn_d, rn_o)
            if rm_o != rm_d and rn_o == rn_d:
                return 'REG_RM', 'Rm: x%d->x%d' % (rm_d, rm_o)
            if rn_o != rn_d and rm_o != rm_d:
                return 'REG_BOTH', 'Rn+Rm differ'
        if rd_o != rd_d and rn_o == rn_d and rm_o == rm_d:
            return 'REG_RD', 'Rd: x%d->x%d' % (rd_d, rd_o)

    # MOVZ vs ORR
    if (orig & 0xFF800000) in (0x52800000, 0xD2800000) and \
       (decomp & 0xBF800000) in (0x32000000, 0xB2000000):
        return 'MOVZ_VS_ORR', 'NX=movz UP=orr'
    if (decomp & 0xFF800000) in (0x52800000, 0xD2800000) and \
       (orig & 0xBF800000) in (0x32000000, 0xB2000000):
        return 'ORR_VS_MOVZ', 'NX=orr UP=movz'

    # Same top bits, different sub-encoding
    if (orig >> 21) == (decomp >> 21):
        return 'SAME_OP_DIFF_FIELDS', 'opcode match, fields differ'

    return 'OTHER', '0x%08x->0x%08x' % (orig, decomp)


def main():
    segs = load_segs(str(ORIGINAL_ELF))
    csv_data = {}; csv_by_short = {}
    with open(CSV) as f:
        for row in csv.DictReader(f):
            a=int(row['Address'],16); s=int(row['Size']); n=row['Name']
            csv_data[n]=(a,s); sn=short_name(n)
            if sn not in csv_by_short: csv_by_short[sn]=(a,s)

    # Collect all diffs from >80% matching functions
    all_diffs = []  # (func_name, func_size, insn_idx, n_insns, orig_word, decomp_word, category, detail)
    pattern_counts = Counter()  # category -> count of functions blocked
    pattern_funcs = defaultdict(list)  # category -> [func_names]
    functions_checked = 0
    functions_near_match = 0

    with open(ORIGINAL_ELF, 'rb') as orig_f:
        for o_path in sorted(BUILD_DIR.glob('*.o')):
            if 'ver_test' in str(o_path) or 'baseline' in str(o_path): continue
            data = o_path.read_bytes()
            if data[:4] != b'\x7fELF': continue
            try:
                shoff=struct.unpack_from('<Q',data,0x28)[0]; she=struct.unpack_from('<H',data,0x3a)[0]
                shn=struct.unpack_from('<H',data,0x3c)[0]; shsi=struct.unpack_from('<H',data,0x3e)[0]
                stro=struct.unpack_from('<Q',data,shoff+shsi*she+0x18)[0]
                strs=struct.unpack_from('<Q',data,shoff+shsi*she+0x20)[0]
                st=data[stro:stro+strs]
                for i in range(shn):
                    b=shoff+i*she; sno=struct.unpack_from('<I',data,b)[0]; sht=struct.unpack_from('<I',data,b+4)[0]
                    end=st.index(b'\0',sno); nm=st[sno:end].decode('ascii','replace')
                    if not nm.startswith('.text.') or sht!=1: continue
                    so=struct.unpack_from('<Q',data,b+0x18)[0]; ss=struct.unpack_from('<Q',data,b+0x20)[0]
                    if ss<4: continue
                    mn=nm[6:]; sn=short_name(mn)
                    if mn in csv_data: addr,csz=csv_data[mn]
                    elif sn in csv_by_short: addr,csz=csv_by_short[sn]
                    elif sn in csv_data: addr,csz=csv_data[sn]
                    else: continue
                    if csz!=ss: continue
                    va=addr-ELF_BASE if addr>=ELF_BASE else addr
                    ob=read_at(orig_f,segs,va,ss)
                    if not ob or len(ob)!=ss: continue
                    ni=ss//4
                    mc=sum(1 for j in range(ni) if struct.unpack_from('<I',ob,j*4)[0]==struct.unpack_from('<I',data,so+j*4)[0])
                    if mc==ni: continue  # already matches
                    functions_checked += 1
                    pct = mc*100/ni
                    if pct < 80: continue  # only >80%
                    functions_near_match += 1
                    # Extract diffs
                    func_cats = set()
                    for j in range(ni):
                        ow=struct.unpack_from('<I',ob,j*4)[0]
                        dw=struct.unpack_from('<I',data,so+j*4)[0]
                        if ow==dw: continue
                        cat, detail = classify_insn_diff(ow, dw)
                        all_diffs.append((sn, ss, j, ni, ow, dw, cat, detail))
                        func_cats.add(cat)
                    # Track which non-reloc categories block this function
                    real_cats = {c for c in func_cats if not c.startswith('RELOC_')}
                    for c in real_cats:
                        pattern_counts[c] += 1
                        if len(pattern_funcs[c]) < 10:
                            pattern_funcs[c].append(sn)
            except: continue

    # Output
    print("=" * 70)
    print("DIVERGENCE CORPUS: %d functions at >80%% match (%d total non-matching)" % (
        functions_near_match, functions_checked))
    print("=" * 70)
    print()

    # Rank patterns by how many functions they block
    print("PATTERN HIT LIST (ranked by functions blocked):")
    print()
    print("%-25s %6s  %s" % ("Pattern", "Blocks", "Example functions"))
    print("-" * 70)
    for cat, cnt in pattern_counts.most_common():
        examples = ", ".join(pattern_funcs[cat][:3])
        print("%-25s %6d  %s" % (cat, cnt, examples[:45]))
    print()

    # Show actual instruction diffs for top patterns
    for cat, _ in pattern_counts.most_common(5):
        cat_diffs = [d for d in all_diffs if d[6] == cat]
        print("--- %s (%d occurrences) ---" % (cat, len(cat_diffs)))
        seen = set()
        for func, sz, idx, ni, ow, dw, _, detail in cat_diffs[:10]:
            key = (ow, dw)
            if key in seen: continue
            seen.add(key)
            print("  %s [%d/%d] upstream=%08x NX=%08x  %s" % (
                func[:35], idx, ni, dw, ow, detail))
        print()


if __name__ == '__main__':
    main()
