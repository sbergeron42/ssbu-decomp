#!/usr/bin/env python3
"""Quantify what it takes to reach 4-5% byte-matched."""
import struct, csv
from pathlib import Path

ORIGINAL_ELF = Path(__file__).parent.parent / "data" / "main.elf"
CSV = Path(__file__).parent.parent / "data" / "functions.csv"
BUILD_DIR = Path(__file__).parent.parent / "build"
ELF_BASE = 0x7100000000

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

segs = load_segs(str(ORIGINAL_ELF))
csv_data = {}; csv_by_short = {}
with open(CSV) as f:
    for row in csv.DictReader(f):
        a = int(row['Address'], 16); s = int(row['Size']); n = row['Name']
        csv_data[n] = (a, s); sn = short_name(n)
        if sn not in csv_by_short: csv_by_short[sn] = (a, s)

text_total = 27.0 * 1048576
current_matched_bytes = 0
buckets = {'>90%': [0, 0], '80-90%': [0, 0], '50-80%': [0, 0], '<50%': [0, 0]}
diff_patterns = {}

with open(ORIGINAL_ELF, 'rb') as orig_f:
    for o_path in sorted(BUILD_DIR.glob('*.o')):
        if 'ver_test' in str(o_path) or 'baseline' in str(o_path):
            continue
        data = o_path.read_bytes()
        if data[:4] != b'\x7fELF': continue
        try:
            shoff = struct.unpack_from('<Q', data, 0x28)[0]
            she = struct.unpack_from('<H', data, 0x3a)[0]
            shn = struct.unpack_from('<H', data, 0x3c)[0]
            shsi = struct.unpack_from('<H', data, 0x3e)[0]
            stro = struct.unpack_from('<Q', data, shoff+shsi*she+0x18)[0]
            strs = struct.unpack_from('<Q', data, shoff+shsi*she+0x20)[0]
            st = data[stro:stro+strs]
            for i in range(shn):
                b = shoff+i*she
                sno = struct.unpack_from('<I', data, b)[0]
                sht = struct.unpack_from('<I', data, b+4)[0]
                end = st.index(b'\0', sno)
                nm = st[sno:end].decode('ascii', 'replace')
                if not nm.startswith('.text.') or sht != 1: continue
                so = struct.unpack_from('<Q', data, b+0x18)[0]
                ss = struct.unpack_from('<Q', data, b+0x20)[0]
                if ss < 4: continue
                mn = nm[6:]; sn = short_name(mn)
                if mn in csv_data: addr, csz = csv_data[mn]
                elif sn in csv_by_short: addr, csz = csv_by_short[sn]
                elif sn in csv_data: addr, csz = csv_data[sn]
                else: continue
                if csz != ss: continue
                va = addr - ELF_BASE if addr >= ELF_BASE else addr
                ob = read_at(orig_f, segs, va, ss)
                if not ob or len(ob) != ss: continue
                ni = ss // 4
                mc = sum(1 for j in range(ni)
                         if struct.unpack_from('<I', ob, j*4)[0] ==
                            struct.unpack_from('<I', data, so+j*4)[0])
                pct = mc*100/ni if ni else 0
                if mc == ni:
                    current_matched_bytes += ss
                elif pct >= 90:
                    buckets['>90%'][0] += 1; buckets['>90%'][1] += ss
                    if ni - mc <= 2:
                        for j in range(ni):
                            ow = struct.unpack_from('<I', ob, j*4)[0]
                            dw = struct.unpack_from('<I', data, so+j*4)[0]
                            if ow != dw:
                                xor = ow ^ dw
                                if (ow >> 26) in (0x05, 0x25) and (dw >> 26) in (0x05, 0x25):
                                    cat = 'BRANCH_OFFSET'
                                elif (ow & 0x9F000000) == 0x90000000 and (dw & 0x9F000000) == 0x90000000:
                                    cat = 'ADRP_OFFSET'
                                elif (ow & 0x3B000000) == 0x39000000 and (dw & 0x3B000000) == 0x39000000:
                                    cat = 'LDST_OFFSET'
                                elif (ow & 0xFF000000) in (0x11000000, 0x91000000) and (dw & 0xFF000000) in (0x11000000, 0x91000000):
                                    cat = 'ADD_IMM'
                                elif xor == 0x80000000:
                                    cat = 'WIDTH_BIT'
                                elif (ow & 0xFFE00C00) == (dw & 0xFFE00C00):
                                    rn_o, rm_o = (ow>>5)&0x1F, (ow>>16)&0x1F
                                    rn_d, rm_d = (dw>>5)&0x1F, (dw>>16)&0x1F
                                    if rn_o == rm_d and rm_o == rn_d:
                                        cat = 'COMMUTATIVE'
                                    else:
                                        cat = 'REG_DIFF'
                                else:
                                    cat = 'OTHER'
                                diff_patterns[cat] = diff_patterns.get(cat, 0) + 1
                elif pct >= 80:
                    buckets['80-90%'][0] += 1; buckets['80-90%'][1] += ss
                elif pct >= 50:
                    buckets['50-80%'][0] += 1; buckets['50-80%'][1] += ss
                else:
                    buckets['<50%'][0] += 1; buckets['<50%'][1] += ss
        except:
            continue

target_4 = text_total * 0.04
target_5 = text_total * 0.05
need_4 = target_4 - current_matched_bytes
need_5 = target_5 - current_matched_bytes

print("=== PATH TO 4-5%% BYTE-MATCHED ===")
print()
print("Current matched: %.2f MB (%.2f%%)" % (current_matched_bytes/1048576, current_matched_bytes/text_total*100))
print("Target 4%%:       %.2f MB — need +%.2f MB" % (target_4/1048576, need_4/1048576))
print("Target 5%%:       %.2f MB — need +%.2f MB" % (target_5/1048576, need_5/1048576))
print()
print("Already compiled but not matching:")
print("  %-10s %6s %8s" % ("Closeness", "Funcs", "Bytes"))
print("  " + "-" * 28)
for k in ['>90%', '80-90%', '50-80%', '<50%']:
    print("  %-10s %6d %7.1f KB" % (k, buckets[k][0], buckets[k][1]/1024))
total_nonmatch = sum(v[1] for v in buckets.values())
print("  %-10s %6d %7.1f KB" % ("TOTAL", sum(v[0] for v in buckets.values()), total_nonmatch/1024))
print()

avail_90 = buckets['>90%'][1]
avail_80 = buckets['>90%'][1] + buckets['80-90%'][1]
print("Lever 1: Fix the >90%% functions (compiler patches)")
print("  Would add: %.1f KB — new total: %.2f MB (%.2f%%)" % (
    avail_90/1024, (current_matched_bytes+avail_90)/1048576,
    (current_matched_bytes+avail_90)/text_total*100))
print()
print("  The 1-2 instruction diffs in these functions:")
for cat, cnt in sorted(diff_patterns.items(), key=lambda x: -x[1]):
    print("    %-20s %d occurrences" % (cat, cnt))
print()

print("Lever 2: Decomp more functions")
still_need = need_4 - avail_90
if still_need > 0:
    print("  After fixing >90%% funcs, still need %.1f KB to reach 4%%" % (still_need/1024))
    print("  At ~40 KB new compiled bytes per session (74%% match rate):")
    per_session_matched = 40 * 1024 * 0.74
    sessions = still_need / per_session_matched
    print("  ~%.0f sessions to reach 4%%" % (sessions + 1))
else:
    print("  Fixing >90%% funcs alone gets past 4%%!")

still_need_5 = need_5 - avail_80
if still_need_5 > 0:
    print("  After fixing >80%% funcs, still need %.1f KB to reach 5%%" % (still_need_5/1024))
    per_session_matched = 40 * 1024 * 0.74
    sessions = still_need_5 / per_session_matched
    print("  ~%.0f sessions to reach 5%%" % (sessions + 1))
