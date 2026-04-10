#!/usr/bin/env python3
"""
Find N-quality functions where changing return type u64->int would fix byte mismatch.
Pattern: function has mov x0,xzr in .o but original has mov w0,wzr (or vice versa),
and is >= 60% matching overall.

Checks first 200 N-quality functions from functions.csv.
"""

import csv, struct, os, re
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
BUILD_DIR = PROJECT_ROOT / "build"
FUNCTIONS_CSV = PROJECT_ROOT / "data" / "functions.csv"
SRC_DIR = PROJECT_ROOT / "src"
ELF_BASE = 0x7100000000

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
            p_vaddr  = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1:
                segments.append((p_vaddr, p_offset, p_filesz))
    return segments

def extract_short_name(mangled):
    if mangled.startswith("_ZN3app8lua_bind"):
        rest = mangled[len("_ZN3app8lua_bind"):]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i > 0:
            length = int(rest[:i])
            name = rest[i:i+length]
            if len(name) == length:
                return name
    if mangled.startswith("_Z"):
        rest = mangled[2:]
        i = 0
        while i < len(rest) and rest[i].isdigit():
            i += 1
        if i > 0:
            length = int(rest[:i])
            name = rest[i:i+length]
            if len(name) == length:
                return name
    return mangled

def main():
    # Load first 200 N-quality functions
    n_funcs = []
    with open(FUNCTIONS_CSV) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            if row[1] == "N":
                n_funcs.append((int(row[0], 16), row[1], int(row[2]), row[3]))
            if len(n_funcs) >= 200:
                break
    print(f"Loaded {len(n_funcs)} N-quality functions")

    # Load ELF
    segs = load_elf_segments(ORIGINAL_ELF)
    orig_data = open(ORIGINAL_ELF, "rb").read()

    def read_orig(addr, size):
        vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
        for sv, so, sf in segs:
            if sv <= vaddr < sv + sf:
                return orig_data[so + (vaddr - sv): so + (vaddr - sv) + size]
        return None

    # Scan .o files once
    print("Scanning .o files...")
    o_sections = {}
    for fn in sorted(os.listdir(BUILD_DIR)):
        if not fn.endswith(".o"):
            continue
        try:
            with open(BUILD_DIR / fn, "rb") as f:
                data = f.read()
            if data[:4] != b"\x7fELF":
                continue
            e_shoff     = struct.unpack_from("<Q", data, 0x28)[0]
            e_shentsize = struct.unpack_from("<H", data, 0x3a)[0]
            e_shnum     = struct.unpack_from("<H", data, 0x3c)[0]
            e_shstrndx  = struct.unpack_from("<H", data, 0x3e)[0]
            strtab_off  = struct.unpack_from("<Q", data, e_shoff + e_shstrndx * e_shentsize + 0x18)[0]
            strtab_sz   = struct.unpack_from("<Q", data, e_shoff + e_shstrndx * e_shentsize + 0x20)[0]
            strtab = data[strtab_off:strtab_off+strtab_sz]
            for i in range(e_shnum):
                sh_off      = e_shoff + i * e_shentsize
                sh_name_idx = struct.unpack_from("<I", data, sh_off)[0]
                sh_type     = struct.unpack_from("<I", data, sh_off+4)[0]
                if sh_type != 1:
                    continue
                end      = strtab.index(b"\x00", sh_name_idx)
                sec_name = strtab[sh_name_idx:end].decode("ascii", errors="replace")
                if not sec_name.startswith(".text."):
                    continue
                sh_offset = struct.unpack_from("<Q", data, sh_off + 0x18)[0]
                sh_size   = struct.unpack_from("<Q", data, sh_off + 0x20)[0]
                if sh_size == 0:
                    continue
                mangled = sec_name[6:]
                o_sections[mangled] = (data[sh_offset:sh_offset+sh_size], fn)
        except Exception:
            pass
    print(f"Found {len(o_sections)} sections in .o files")

    # Build short-name index for o_sections
    short_to_mangled = {}
    for mangled in o_sections:
        short = extract_short_name(mangled)
        if short and short not in short_to_mangled:
            short_to_mangled[short] = mangled

    # Search src/ files for function occurrences
    src_cache = {}
    print("Indexing src/ files...")
    src_index = {}  # token -> [src_file]
    for src_file in sorted(SRC_DIR.rglob("*.cpp")):
        try:
            content = src_file.read_text(errors="replace")
            # Extract all word tokens
            for token in re.findall(r"\b\w{6,}\b", content):
                if token not in src_index:
                    src_index[token] = []
                src_index[token].append(str(src_file.relative_to(PROJECT_ROOT)))
        except Exception:
            pass

    def find_src(short_name):
        hits = src_index.get(short_name, [])
        if hits:
            return hits[0]
        return None

    results = []

    for addr, quality, size, csv_name in n_funcs:
        # Find section
        decomp_bytes = None
        o_file = None
        mangled = None

        if csv_name in o_sections:
            decomp_bytes, o_file = o_sections[csv_name]
            mangled = csv_name
        else:
            short = extract_short_name(csv_name)
            if short in short_to_mangled:
                m = short_to_mangled[short]
                decomp_bytes, o_file = o_sections[m]
                mangled = m

        if decomp_bytes is None:
            continue

        orig_bytes = read_orig(addr, len(decomp_bytes))
        if orig_bytes is None or len(orig_bytes) < len(decomp_bytes):
            continue

        num_insns = len(decomp_bytes) // 4
        if num_insns == 0:
            continue

        match_count = 0
        width_diffs = []

        for i in range(num_insns):
            oi = struct.unpack_from("<I", orig_bytes,   i*4)[0]
            di = struct.unpack_from("<I", decomp_bytes, i*4)[0]
            if oi == di:
                match_count += 1
            else:
                # Check: both are mov rN, rzr but differ only in 64-bit bit (bit 31)
                # mov wN, wzr = 0x2A1F03E0|N, mov xN, xzr = 0xAA1F03E0|N
                o_is_movw = (oi & 0xFFFFFFE0) == 0x2A1F03E0
                o_is_movx = (oi & 0xFFFFFFE0) == 0xAA1F03E0
                d_is_movw = (di & 0xFFFFFFE0) == 0x2A1F03E0
                d_is_movx = (di & 0xFFFFFFE0) == 0xAA1F03E0
                o_rd = oi & 0x1F
                d_rd = di & 0x1F
                if (o_is_movw or o_is_movx) and (d_is_movw or d_is_movx) and o_rd == d_rd:
                    width_diffs.append((i, oi, di))

        pct = match_count * 100 // num_insns

        if width_diffs and pct >= 60:
            short_name = extract_short_name(csv_name)
            src_file = find_src(short_name)
            results.append({
                "name":        short_name,
                "mangled":     csv_name,
                "addr":        addr,
                "pct":         pct,
                "match":       match_count,
                "total":       num_insns,
                "width_diffs": width_diffs,
                "src":         src_file or "?",
                "o_file":      o_file,
            })

    print()
    print("=" * 70)
    print(f"Functions with mov x/w width mismatch (N-quality, >=60% match)")
    print(f"Checked {len(n_funcs)} N-quality functions | Found {len(results)} hits")
    print("=" * 70)
    results.sort(key=lambda x: (-x["pct"], x["name"]))
    for r in results:
        diff_detail = []
        for ins_i, oi, di in r["width_diffs"]:
            o_reg = "x" if (oi & 0xFFFFFFE0) == 0xAA1F03E0 else "w"
            d_reg = "x" if (di & 0xFFFFFFE0) == 0xAA1F03E0 else "w"
            rd = oi & 0x1F
            diff_detail.append(f"[{ins_i}] orig=mov {o_reg}{rd},{'xzr' if o_reg=='x' else 'wzr'} got=mov {d_reg}{rd},{'xzr' if d_reg=='x' else 'wzr'}")
        print(f"  {r['name']}")
        print(f"    {r['match']}/{r['total']} ({r['pct']}%)  addr=0x{r['addr']:x}")
        print(f"    src: {r['src']}")
        print(f"    obj: {r['o_file']}")
        for d in diff_detail:
            print(f"    {d}")
        print()

if __name__ == "__main__":
    main()
