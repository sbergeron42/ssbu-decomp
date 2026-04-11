"""Find all BL sites that target a given address."""

import struct
import sys

sys.path.insert(0, "tools")
from xref_bin_scan import load_text, idx_to_addr, dec_bl, RX_VA_START


def find_callers(target):
    text = load_text()
    hits = []
    for i in range(0, len(text) - 4, 4):
        w = struct.unpack_from("<I", text, i)[0]
        bl = dec_bl(w)
        if bl is None:
            continue
        src = idx_to_addr(i)
        dst = (src + bl) & 0xFFFFFFFFFF
        if dst == target:
            hits.append(src)
    return hits


if __name__ == "__main__":
    for a in sys.argv[1:]:
        t = int(a, 0)
        hits = find_callers(t)
        print(f"target {t:#x}: {len(hits)} callers")
        for h in hits:
            print(f"  {h:#x}")
