#!/usr/bin/env python3
"""Compare match rates across different Clang versions."""
import struct, csv, sys
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
CSV = PROJECT_ROOT / "data" / "functions.csv"
BUILD_DIR = PROJECT_ROOT / "build" / "ver_test"
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
csv_data = {}
csv_by_short = {}
with open(CSV) as f:
    for row in csv.DictReader(f):
        a=int(row['Address'],16); s=int(row['Size']); n=row['Name']
        csv_data[n]=(a,s); sn=short_name(n)
        if sn not in csv_by_short: csv_by_short[sn]=(a,s)

versions = ["llvm-7.0.1", "llvm-7.1.0", "llvm-8.0.0"]
results = {v: {"match":0, "nonmatch":0, "match_bytes":0, "total_bytes":0,
               "match_insns":0, "total_insns":0} for v in versions}
# Per-function tracking
per_func = defaultdict(dict)  # func_name -> {version: (matched, pct)}

with open(ORIGINAL_ELF, 'rb') as orig_f:
    for o_path in sorted(BUILD_DIR.glob("*.o")):
        fname = o_path.stem  # e.g. "FighterManager_llvm-8.0.0"
        parts = fname.rsplit('_', 1)
        if len(parts) != 2: continue
        src_name, ver = parts
        if ver not in versions: continue

        data = o_path.read_bytes()
        if data[:4] != b'\x7fELF': continue
        try:
            shoff=struct.unpack_from('<Q',data,0x28)[0]; she=struct.unpack_from('<H',data,0x3a)[0]
            shn=struct.unpack_from('<H',data,0x3c)[0]; shsi=struct.unpack_from('<H',data,0x3e)[0]
            stro=struct.unpack_from('<Q',data,shoff+shsi*she+0x18)[0]
            strs=struct.unpack_from('<Q',data,shoff+shsi*she+0x20)[0]
            st=data[stro:stro+strs]
            for i in range(shn):
                b=shoff+i*she; sno=struct.unpack_from('<I',data,b)[0]
                sht=struct.unpack_from('<I',data,b+4)[0]
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
                n_insns=ss//4
                match_count=0
                for idx in range(n_insns):
                    ow=struct.unpack_from('<I',ob,idx*4)[0]
                    dw=struct.unpack_from('<I',data,so+idx*4)[0]
                    if ow==dw: match_count+=1
                results[ver]["total_bytes"]+=ss
                results[ver]["total_insns"]+=n_insns
                results[ver]["match_insns"]+=match_count
                if match_count==n_insns:
                    results[ver]["match"]+=1
                    results[ver]["match_bytes"]+=ss
                else:
                    results[ver]["nonmatch"]+=1
                pct = match_count*100//n_insns if n_insns else 0
                per_func[sn][ver] = (match_count==n_insns, pct, ss)
        except: continue

print("=== Match rates by Clang version (8 source files, no post-processing) ===")
print()
print("%-12s %6s %6s %6s  %8s  %s" % ("Version", "Match", "NoMat", "Total", "Bytes", "InsnMatch%"))
print("-" * 65)
for v in versions:
    r = results[v]
    total = r["match"] + r["nonmatch"]
    rate = r["match"]*100/total if total else 0
    insn_pct = r["match_insns"]*100/r["total_insns"] if r["total_insns"] else 0
    print("%-12s %6d %6d %6d  %6.1fKB  %5.1f%%" % (
        v, r["match"], r["nonmatch"], total, r["match_bytes"]/1024, insn_pct))

# Show functions where versions differ
print()
print("=== Functions where versions produce DIFFERENT results ===")
print("%-40s %12s %12s %12s" % ("Function", "7.0.1", "7.1.0", "8.0.0"))
print("-" * 80)
for func in sorted(per_func.keys()):
    d = per_func[func]
    if len(d) < 2: continue
    vals = [d.get(v) for v in versions]
    # Only show if at least one version differs
    matches = [v[0] if v else None for v in vals]
    if len(set(m for m in matches if m is not None)) > 1:
        cols = []
        for v in versions:
            if v in d:
                matched, pct, sz = d[v]
                cols.append("MATCH" if matched else "%d%%" % pct)
            else:
                cols.append("-")
        print("%-40s %12s %12s %12s" % (func[:40], cols[0], cols[1], cols[2]))
