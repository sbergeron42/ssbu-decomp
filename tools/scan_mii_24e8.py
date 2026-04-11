"""Find code that writes to (*DAT_710593a6a0) + 0x24e8 — the Mii manager
back-reference field. Two hunting modes:

  1) External callers: ADRP 0x710593a000 + LDR [.,#0x6a0] -> Rm; STR [Rm,#0x24e8]
  2) Method form: function that takes Mii manager as X0, does STR [X0,#0x24e8]
     (detected by looking at the function's prologue: if the first few
      instructions copy X0 to X19/X20/X21 without loading from a global,
      and the body stores at [X_cs,#0x24e8], it's a Mii-mgr method.)

Plus reader-side: we also scan for LDR [.,#0x24e8] followed by LDR [Xt,#0]
(the "double-deref" access pattern used by Dispatcher A).
"""

import struct
import sys

sys.path.insert(0, "tools")
from xref_bin_scan import (
    load_text, idx_to_addr, dec_adrp, dec_add_imm, dec_mov_reg,
    dec_ldr_str_uimm, dec_ldr_str_simm, dec_stp_ldp, dec_ret, dec_uncond_b,
    dec_bl, RX_VA_START, RX_VA_END, GHIDRA_BASE, word_at,
)

DAT_MII_PAGE = 0x710593A000
DAT_MII_OFF  = 0x6A0
TARGET_FIELD = 0x24E8


def scan_external_writers():
    """Mode 1: scan for STR [Rm, #0x24e8] where Rm was loaded from *DAT_710593a6a0."""
    text = load_text()
    hits = []
    # Per-function tracking: reset at RET / unconditional B
    adrp_regs = {}     # reg -> page_base
    mii_regs = set()   # registers that hold *DAT_710593a6a0
    for i in range(0, len(text) - 4, 4):
        w = struct.unpack_from("<I", text, i)[0]
        addr = idx_to_addr(i)

        if dec_ret(w):
            adrp_regs.clear(); mii_regs.clear(); continue
        b = dec_uncond_b(w)
        if b is not None and (w >> 26) & 0x3F == 0x05:
            adrp_regs.clear(); mii_regs.clear(); continue

        a = dec_adrp(w)
        if a is not None:
            Rd, imm = a
            adrp_regs[Rd] = (addr & ~0xFFF) + imm
            mii_regs.discard(Rd)
            continue

        ad = dec_add_imm(w)
        if ad is not None:
            sf, Rd, Rn, imm = ad
            if Rn in adrp_regs:
                adrp_regs[Rd] = adrp_regs[Rn] + imm
            else:
                adrp_regs.pop(Rd, None)
            mii_regs.discard(Rd)
            continue

        m = dec_mov_reg(w)
        if m is not None:
            sf, Rd, Rm = m
            if Rm in mii_regs:
                mii_regs.add(Rd)
            else:
                mii_regs.discard(Rd)
            if Rm in adrp_regs:
                adrp_regs[Rd] = adrp_regs[Rm]
            else:
                adrp_regs.pop(Rd, None)
            continue

        d = dec_ldr_str_uimm(w)
        if d is not None:
            sz, is_load, imm, Rn, Rt = d
            eff = adrp_regs.get(Rn)
            if is_load and sz == 64:
                if eff == DAT_MII_PAGE + DAT_MII_OFF:
                    mii_regs.add(Rt)
                else:
                    mii_regs.discard(Rt)
                adrp_regs.pop(Rt, None)
            elif not is_load:
                if Rn in mii_regs and imm == TARGET_FIELD:
                    hits.append((addr, "external-writer", Rn, Rt, sz))
            continue

        # Any other write to Rt clobbers it (conservative)
    return hits


def function_start_guess(addr):
    """Find nearest preceding function-like boundary.

    A heuristic: search backward for either a RET followed by a known
    prologue form (STP X29,X30,[SP,#-?]! or SUB SP,SP,#...).
    Cap at 0x4000 bytes.
    """
    text = load_text()
    i = addr - RX_VA_START
    boundary = i
    for step in range(4, 0x4000, 4):
        j = i - step
        if j < 0:
            break
        w = struct.unpack_from("<I", text, j)[0]
        if dec_ret(w):
            boundary = j + 4
            break
    return RX_VA_START + boundary


def scan_method_form():
    """Mode 2: look for a function that treats X0 as its first parameter
    and does STR [Rn,#0x24e8] where Rn is a callee-save copy of X0.

    We sweep every STR at offset 0x24e8 and walk backward within the
    (heuristic) function to see whether Rn was initialised via MOV Rd, X0
    at the function entry, rather than from a global load or allocation.
    """
    text = load_text()
    results = []
    # Re-use the store-offset hit list from mode 1
    candidates = []
    for i in range(0, len(text) - 4, 4):
        w = struct.unpack_from("<I", text, i)[0]
        d = dec_ldr_str_uimm(w)
        if d is not None and not d[1] and d[0] == 64 and d[2] == TARGET_FIELD:
            sz, is_load, imm, Rn, Rt = d
            candidates.append((idx_to_addr(i), Rn, Rt))

    for addr, Rn, Rt in candidates:
        if Rt == 31:
            continue  # XZR (null-init) — not useful
        start = function_start_guess(addr)
        # Walk forward from start, tracking whether Rn was initialised
        # from MOV Rn, X0 before any other definition.
        trace = scan_reg_provenance(start, addr, Rn)
        results.append((addr, Rn, Rt, start, trace))
    return results


def scan_reg_provenance(start_addr, end_addr, target_reg):
    """Scan from start_addr to end_addr tracking target_reg's origin.

    Returns a string describing the earliest known source of target_reg.
    """
    text = load_text()
    source = "?"
    # We remember the latest "definition" of target_reg.
    reg_source = {}     # reg -> string tag
    adrp_regs = {}
    i = start_addr - RX_VA_START
    endi = end_addr - RX_VA_START
    while i < endi:
        w = struct.unpack_from("<I", text, i)[0]
        a = dec_adrp(w)
        if a is not None:
            Rd, imm = a
            page = ((RX_VA_START + i) & ~0xFFF) + imm
            adrp_regs[Rd] = page
            reg_source[Rd] = f"ADRP {page:#x}"
            i += 4; continue
        ad = dec_add_imm(w)
        if ad is not None:
            sf, Rd, Rn, imm = ad
            if Rn in adrp_regs:
                adrp_regs[Rd] = adrp_regs[Rn] + imm
            else:
                adrp_regs.pop(Rd, None)
            if Rn == 0 and Rd != 0 and i - (start_addr - RX_VA_START) < 0x40:
                reg_source[Rd] = f"ADD X{Rd},X0,#{imm:#x} (early)"
            else:
                reg_source[Rd] = f"ADD X{Rd},X{Rn},#{imm:#x}"
            i += 4; continue
        m = dec_mov_reg(w)
        if m is not None:
            sf, Rd, Rm = m
            if Rm == 0:
                off = i - (start_addr - RX_VA_START)
                if off < 0x40:
                    reg_source[Rd] = f"MOV X{Rd},X0 @ +{off:#x}"
                else:
                    reg_source[Rd] = f"MOV X{Rd},X0 @ +{off:#x} (late)"
            else:
                reg_source[Rd] = f"MOV X{Rd},X{Rm}"
            adrp_regs.pop(Rd, None)
            i += 4; continue
        d = dec_ldr_str_uimm(w)
        if d is not None:
            sz, is_load, imm, Rn, Rt = d
            if is_load:
                src_page = adrp_regs.get(Rn)
                if src_page is not None:
                    reg_source[Rt] = f"LDR from {src_page + imm:#x}"
                else:
                    reg_source[Rt] = f"LDR [X{Rn},#{imm:#x}]"
                adrp_regs.pop(Rt, None)
            i += 4; continue
        # track function calls for return values
        bl = dec_bl(w)
        if bl is not None:
            tgt = (RX_VA_START + i + bl) & 0xFFFFFFFFFF
            reg_source[0] = f"BL {tgt:#x}"
            # BL clobbers x0..x17
            for r in range(1, 18):
                adrp_regs.pop(r, None)
            i += 4; continue
        i += 4

    return reg_source.get(target_reg, "?")


if __name__ == "__main__":
    mode = sys.argv[1] if len(sys.argv) > 1 else "both"
    if mode in ("external", "both"):
        print("=== Mode 1: external writers via *DAT_710593a6a0 ===")
        ext = scan_external_writers()
        print(f"{len(ext)} hits")
        for h in ext:
            print(" ", h)
    if mode in ("method", "both"):
        print("\n=== Mode 2: method-form writers (non-null Rt) ===")
        meth = scan_method_form()
        for addr, Rn, Rt, start, src in meth:
            print(f"  {addr:#x}  STR X{Rt},[X{Rn},#0x24e8]   fn~{start:#x}   Rn source: {src}")
