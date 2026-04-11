#!/usr/bin/env python3
"""xref_bin_scan.py - Binary ADRP-propagation xref scanner for AArch64 ELFs.

Finds readers and writers of a global address (or address range) by walking
the raw R+X segment of an AArch64 ELF and propagating ADRP+ADD+MOV chains.
Uses no symbol information, so it finds cross-references that Ghidra's
function-centric xref index misses in code regions the auto-analyzer never
carved into functions.

Test case (DAT_710593a530, SSBU 13.0.4):
    python tools/xref_bin_scan.py 0x710593a530
Expected: 3 readers, 1 writer (STP XZR,XZR .init_array ctor), 0 BL args,
0 pointer-init stores.

Why this exists:
    Ghidra's xref index is incomplete in regions its auto-analyzer has not
    carved into functions. For sim-tick / match-state hunts the missing
    xrefs are usually the interesting ones (ctors, dispatchers, etc.).

See docs/rollback/sim_tick_hunt.md "Pool C - DAT_710593a530" for the
original manual scan this script replaces.
"""

import argparse
import bisect
import csv
import os
import struct
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_ELF = REPO_ROOT / "data" / "main.elf"
FUNCTIONS_CSV = REPO_ROOT / "data" / "functions.csv"


def sext(val, bits):
    sign = 1 << (bits - 1)
    return (val & (sign - 1)) - (val & sign)


def load_rx_segment(elf_path):
    """Return (text_bytes, base_vaddr) for the first PT_LOAD with PF_X."""
    with open(elf_path, "rb") as f:
        data = f.read()
    if data[:4] != b"\x7fELF":
        raise SystemExit(f"{elf_path}: not an ELF")
    if data[4] != 2:
        raise SystemExit("only ELF64 supported")
    e_phoff = struct.unpack_from("<Q", data, 0x20)[0]
    e_phentsize, e_phnum = struct.unpack_from("<HH", data, 0x36)
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_flags = struct.unpack_from("<II", data, off)
        p_offset, p_vaddr, _, p_filesz, _, _ = struct.unpack_from(
            "<QQQQQQ", data, off + 8
        )
        if p_type == 1 and (p_flags & 1):
            return data[p_offset : p_offset + p_filesz], p_vaddr
    raise SystemExit("no PT_LOAD with PF_X found")


def load_functions():
    """Return (sorted_starts, starts_to_name) or ([], {}) if no csv."""
    if not FUNCTIONS_CSV.exists():
        return [], {}
    starts = []
    names = {}
    with open(FUNCTIONS_CSV, newline="") as f:
        rdr = csv.DictReader(f)
        for row in rdr:
            try:
                addr = int(row["Address"], 16)
            except (KeyError, ValueError):
                continue
            starts.append(addr)
            names[addr] = row.get("Name", "")
    starts.sort()
    return starts, names


def lookup_function(fn_starts, fn_names, addr):
    """Return (fn_start, fn_name or 'undefined')."""
    if not fn_starts:
        return None, "undefined"
    idx = bisect.bisect_right(fn_starts, addr) - 1
    if idx < 0:
        return None, "undefined"
    return fn_starts[idx], fn_names.get(fn_starts[idx], "undefined")


# --- AArch64 decoder helpers ---------------------------------------------

def decode_adrp(inst, pc):
    """Return (Rd, page_base) or None."""
    if (inst & 0x9F000000) != 0x90000000:
        return None
    immlo = (inst >> 29) & 0x3
    immhi = (inst >> 5) & 0x7FFFF
    imm = sext((immhi << 2) | immlo, 21) << 12
    Rd = inst & 0x1F
    return Rd, (pc & ~0xFFF) + imm


def decode_add_imm(inst):
    """64-bit ADD immediate. Returns (Rd, Rn, imm) or None."""
    if (inst & 0xFF000000) != 0x91000000:
        return None
    sh = (inst >> 22) & 1
    imm12 = (inst >> 10) & 0xFFF
    imm = imm12 << 12 if sh else imm12
    Rn = (inst >> 5) & 0x1F
    Rd = inst & 0x1F
    return Rd, Rn, imm


def decode_sub_imm(inst):
    if (inst & 0xFF000000) != 0xD1000000:
        return None
    sh = (inst >> 22) & 1
    imm12 = (inst >> 10) & 0xFFF
    imm = imm12 << 12 if sh else imm12
    Rn = (inst >> 5) & 0x1F
    Rd = inst & 0x1F
    return Rd, Rn, imm


def decode_mov_reg64(inst):
    """ORR Xd, XZR, Xm (= MOV Xd, Xm). Returns (Rd, Rm) or None."""
    if (inst & 0xFFE0FFE0) != 0xAA0003E0:
        return None
    Rm = (inst >> 16) & 0x1F
    Rd = inst & 0x1F
    return Rd, Rm


# Unsigned-offset ldr/str: (mask, match, scale, is_load, width_label)
LDST_UIMM = [
    (0xFFC00000, 0xF9000000, 8, False, "STR X"),
    (0xFFC00000, 0xF9400000, 8, True,  "LDR X"),
    (0xFFC00000, 0xB9000000, 4, False, "STR W"),
    (0xFFC00000, 0xB9400000, 4, True,  "LDR W"),
    (0xFFC00000, 0x39000000, 1, False, "STRB"),
    (0xFFC00000, 0x39400000, 1, True,  "LDRB"),
    (0xFFC00000, 0x79000000, 2, False, "STRH"),
    (0xFFC00000, 0x79400000, 2, True,  "LDRH"),
    (0xFFC00000, 0xFD000000, 8, False, "STR D"),
    (0xFFC00000, 0xFD400000, 8, True,  "LDR D"),
    (0xFFC00000, 0xBD000000, 4, False, "STR S"),
    (0xFFC00000, 0xBD400000, 4, True,  "LDR S"),
    (0xFFC00000, 0x3D800000, 16, False, "STR Q"),
    (0xFFC00000, 0x3DC00000, 16, True,  "LDR Q"),
]

# Unscaled (stur/ldur, imm9 signed)
LDST_UNSCALED = [
    (0xFFE00C00, 0xF8000000, False, "STUR X"),
    (0xFFE00C00, 0xF8400000, True,  "LDUR X"),
    (0xFFE00C00, 0xB8000000, False, "STUR W"),
    (0xFFE00C00, 0xB8400000, True,  "LDUR W"),
    (0xFFE00C00, 0x38000000, False, "STURB"),
    (0xFFE00C00, 0x38400000, True,  "LDURB"),
    (0xFFE00C00, 0x78000000, False, "STURH"),
    (0xFFE00C00, 0x78400000, True,  "LDURH"),
]

# STP/LDP variants: (mask, match, scale, is_load, label)
LDST_PAIR = [
    # X-pair
    (0xFFC00000, 0xA9000000, 8, False, "STP X (off)"),
    (0xFFC00000, 0xA9400000, 8, True,  "LDP X (off)"),
    (0xFFC00000, 0xA9800000, 8, False, "STP X (pre)"),
    (0xFFC00000, 0xA9C00000, 8, True,  "LDP X (pre)"),
    (0xFFC00000, 0xA8800000, 8, False, "STP X (post)"),
    (0xFFC00000, 0xA8C00000, 8, True,  "LDP X (post)"),
    # W-pair
    (0xFFC00000, 0x29000000, 4, False, "STP W (off)"),
    (0xFFC00000, 0x29400000, 4, True,  "LDP W (off)"),
    (0xFFC00000, 0x29800000, 4, False, "STP W (pre)"),
    (0xFFC00000, 0x29C00000, 4, True,  "LDP W (pre)"),
    (0xFFC00000, 0x28800000, 4, False, "STP W (post)"),
    (0xFFC00000, 0x28C00000, 4, True,  "LDP W (post)"),
    # D / S / Q SIMD pairs (common in BSS init)
    (0xFFC00000, 0x6D000000, 8, False, "STP D (off)"),
    (0xFFC00000, 0x6D400000, 8, True,  "LDP D (off)"),
    (0xFFC00000, 0x2D000000, 4, False, "STP S (off)"),
    (0xFFC00000, 0x2D400000, 4, True,  "LDP S (off)"),
    (0xFFC00000, 0xAD000000, 16, False, "STP Q (off)"),
    (0xFFC00000, 0xAD400000, 16, True,  "LDP Q (off)"),
]

# Release/acquire single-reg: STLR/LDAR family. These have no imm
# (offset is always 0). (mask, match, is_load, label)
LDST_REL = [
    (0xFFFFFC00, 0xC8DFFC00, True,  "LDAR X"),
    (0xFFFFFC00, 0xC89FFC00, False, "STLR X"),
    (0xFFFFFC00, 0x88DFFC00, True,  "LDAR W"),
    (0xFFFFFC00, 0x889FFC00, False, "STLR W"),
    (0xFFFFFC00, 0x08DFFC00, True,  "LDARB"),
    (0xFFFFFC00, 0x089FFC00, False, "STLRB"),
    (0xFFFFFC00, 0x48DFFC00, True,  "LDARH"),
    (0xFFFFFC00, 0x489FFC00, False, "STLRH"),
]

# Exclusive single-reg: STXR Ws, Wt, [Xn] / LDXR Wt, [Xn]. Offset = 0.
LDST_EXCL = [
    (0xFFE08000, 0xC8008000, False, "STXR X"),
    (0xFFE08000, 0xC8408000, True,  "LDXR X"),
    (0xFFE08000, 0x88008000, False, "STXR W"),
    (0xFFE08000, 0x88408000, True,  "LDXR W"),
]


def decode_ldst_uimm(inst):
    for mask, match, scale, is_load, label in LDST_UIMM:
        if (inst & mask) == match:
            imm12 = (inst >> 10) & 0xFFF
            imm = imm12 * scale
            Rn = (inst >> 5) & 0x1F
            Rt = inst & 0x1F
            return Rt, Rn, imm, is_load, label, scale
    return None


def decode_ldst_unscaled(inst):
    for mask, match, is_load, label in LDST_UNSCALED:
        if (inst & mask) == match:
            imm9 = sext((inst >> 12) & 0x1FF, 9)
            Rn = (inst >> 5) & 0x1F
            Rt = inst & 0x1F
            return Rt, Rn, imm9, is_load, label
    return None


def decode_ldst_pair(inst):
    for mask, match, scale, is_load, label in LDST_PAIR:
        if (inst & mask) == match:
            imm7 = sext((inst >> 15) & 0x7F, 7) * scale
            Rn = (inst >> 5) & 0x1F
            Rt = inst & 0x1F
            Rt2 = (inst >> 10) & 0x1F
            return Rt, Rt2, Rn, imm7, is_load, label, scale
    return None


def decode_ldst_rel(inst):
    for mask, match, is_load, label in LDST_REL:
        if (inst & mask) == match:
            Rn = (inst >> 5) & 0x1F
            Rt = inst & 0x1F
            return Rt, Rn, is_load, label
    return None


def decode_ldst_excl(inst):
    for mask, match, is_load, label in LDST_EXCL:
        if (inst & mask) == match:
            Rn = (inst >> 5) & 0x1F
            Rt = inst & 0x1F
            return Rt, Rn, is_load, label
    return None


def decode_bl(inst, pc):
    if (inst & 0xFC000000) != 0x94000000:
        return None
    imm26 = sext(inst & 0x03FFFFFF, 26)
    return pc + (imm26 << 2)


def is_uncond_b(inst):
    return (inst & 0xFC000000) == 0x14000000


def is_ret(inst):
    return (inst & 0xFFFFFC1F) == 0xD65F0000


# --- scan ----------------------------------------------------------------

class Hit:
    __slots__ = ("kind", "addr", "label", "extra")
    def __init__(self, kind, addr, label, extra=None):
        self.kind = kind
        self.addr = addr
        self.label = label
        self.extra = extra


def scan(text, base, target_lo, target_hi,
         want_readers=True, want_writers=True,
         want_bl=True, want_ptrinit=True):
    """Walk text linearly with per-basic-block register propagation.

    Registers are tracked as a dict {reg_num: full_address_value}. ADRP
    seeds, ADD/SUB/MOV propagates, RET/uncond-B clears state. Every
    load/store tests Rn against tracked; every BL tests X0..X7 for target
    equality; every store tests Rt against target (pointer-init).
    """
    regs = {}
    hits = []
    n = len(text) // 4
    for i in range(n):
        pc = base + i * 4
        inst = struct.unpack_from("<I", text, i * 4)[0]

        # ADRP seed
        hit = decode_adrp(inst, pc)
        if hit is not None:
            Rd, page = hit
            if Rd != 31:
                regs[Rd] = page
            continue

        # ADD/SUB imm propagation
        add = decode_add_imm(inst)
        if add is not None:
            Rd, Rn, imm = add
            if Rn in regs and Rd != 31:
                regs[Rd] = (regs[Rn] + imm) & 0xFFFFFFFFFFFFFFFF
            elif Rd in regs and Rd != 31:
                del regs[Rd]
            continue
        sub = decode_sub_imm(inst)
        if sub is not None:
            Rd, Rn, imm = sub
            if Rn in regs and Rd != 31:
                regs[Rd] = (regs[Rn] - imm) & 0xFFFFFFFFFFFFFFFF
            elif Rd in regs and Rd != 31:
                del regs[Rd]
            continue
        mov = decode_mov_reg64(inst)
        if mov is not None:
            Rd, Rm = mov
            if Rm in regs and Rd != 31:
                regs[Rd] = regs[Rm]
            elif Rd in regs and Rd != 31:
                del regs[Rd]
            continue

        # Unsigned-offset loads/stores
        u = decode_ldst_uimm(inst)
        if u is not None:
            Rt, Rn, imm, is_load, label, _scale = u
            if Rn in regs:
                ea = regs[Rn] + imm
                if target_lo <= ea < target_hi:
                    if is_load and want_readers:
                        hits.append(Hit("R", pc, label, ea))
                    elif not is_load and want_writers:
                        hits.append(Hit("W", pc, label, ea))
            if not is_load and want_ptrinit and Rt != 31 and Rt in regs:
                if target_lo <= regs[Rt] < target_hi:
                    hits.append(Hit("P", pc, label, regs[Rt]))
            # writeback to Rt on load clears tracking
            if is_load and Rt != 31:
                regs.pop(Rt, None)
            continue

        # Unscaled loads/stores
        u = decode_ldst_unscaled(inst)
        if u is not None:
            Rt, Rn, imm9, is_load, label = u
            if Rn in regs:
                ea = (regs[Rn] + imm9) & 0xFFFFFFFFFFFFFFFF
                if target_lo <= ea < target_hi:
                    if is_load and want_readers:
                        hits.append(Hit("R", pc, label, ea))
                    elif not is_load and want_writers:
                        hits.append(Hit("W", pc, label, ea))
            if not is_load and want_ptrinit and Rt != 31 and Rt in regs:
                if target_lo <= regs[Rt] < target_hi:
                    hits.append(Hit("P", pc, label, regs[Rt]))
            if is_load and Rt != 31:
                regs.pop(Rt, None)
            continue

        # LDP/STP
        p = decode_ldst_pair(inst)
        if p is not None:
            Rt, Rt2, Rn, imm7, is_load, label, scale = p
            if Rn in regs:
                ea1 = (regs[Rn] + imm7) & 0xFFFFFFFFFFFFFFFF
                ea2 = (ea1 + scale) & 0xFFFFFFFFFFFFFFFF
                for ea in (ea1, ea2):
                    if target_lo <= ea < target_hi:
                        if is_load and want_readers:
                            hits.append(Hit("R", pc, label, ea))
                        elif not is_load and want_writers:
                            hits.append(Hit("W", pc, label, ea))
            if not is_load and want_ptrinit:
                for Rs in (Rt, Rt2):
                    if Rs != 31 and Rs in regs and target_lo <= regs[Rs] < target_hi:
                        hits.append(Hit("P", pc, label, regs[Rs]))
            if is_load:
                for Rs in (Rt, Rt2):
                    if Rs != 31:
                        regs.pop(Rs, None)
            continue

        # STLR/LDAR (offset 0)
        r = decode_ldst_rel(inst)
        if r is not None:
            Rt, Rn, is_load, label = r
            if Rn in regs and target_lo <= regs[Rn] < target_hi:
                if is_load and want_readers:
                    hits.append(Hit("R", pc, label, regs[Rn]))
                elif not is_load and want_writers:
                    hits.append(Hit("W", pc, label, regs[Rn]))
            if not is_load and want_ptrinit and Rt != 31 and Rt in regs:
                if target_lo <= regs[Rt] < target_hi:
                    hits.append(Hit("P", pc, label, regs[Rt]))
            if is_load and Rt != 31:
                regs.pop(Rt, None)
            continue

        # STXR/LDXR (offset 0)
        e = decode_ldst_excl(inst)
        if e is not None:
            Rt, Rn, is_load, label = e
            if Rn in regs and target_lo <= regs[Rn] < target_hi:
                if is_load and want_readers:
                    hits.append(Hit("R", pc, label, regs[Rn]))
                elif not is_load and want_writers:
                    hits.append(Hit("W", pc, label, regs[Rn]))
            if is_load and Rt != 31:
                regs.pop(Rt, None)
            continue

        # BL setter-helper
        bl_tgt = decode_bl(inst, pc)
        if bl_tgt is not None:
            if want_bl:
                for arg in range(8):
                    if arg in regs and target_lo <= regs[arg] < target_hi:
                        hits.append(
                            Hit("B", pc, f"arg=X{arg}",
                                (bl_tgt, regs[arg]))
                        )
            # call clobbers X0..X18, X30
            for clob in list(range(0, 19)) + [30]:
                regs.pop(clob, None)
            continue

        # RET / unconditional B end a basic block
        if is_ret(inst) or is_uncond_b(inst):
            regs.clear()
            continue

        # Any other instruction: if it has an Rd that matches a tracked
        # reg, be conservative and forget it. We approximate by checking
        # the common Rd encoding at bits[4:0]. This is imprecise but the
        # false-negative cost is low (occasional missed xref); the false-
        # positive cost of keeping stale state would be much higher.
        Rd = inst & 0x1F
        if Rd in regs:
            # don't clobber on known-safe forms; but most other insns
            # write Rd, so drop it.
            regs.pop(Rd, None)

    return hits


def group_hits(hits):
    return {
        "W": [h for h in hits if h.kind == "W"],
        "R": [h for h in hits if h.kind == "R"],
        "B": [h for h in hits if h.kind == "B"],
        "P": [h for h in hits if h.kind == "P"],
    }


def format_report(groups, fn_starts, fn_names):
    out = []
    def fn_for(addr):
        start, name = lookup_function(fn_starts, fn_names, addr)
        if start is None:
            return "(undefined)"
        return f"in fn 0x{start:x} ({name})"

    out.append("WRITERS:")
    if groups["W"]:
        for h in groups["W"]:
            out.append(
                f"  0x{h.addr:x}  {h.label:<14}  ea=0x{h.extra:x}  {fn_for(h.addr)}"
            )
    else:
        out.append("  (none)")

    out.append("READERS:")
    if groups["R"]:
        for h in groups["R"]:
            out.append(
                f"  0x{h.addr:x}  {h.label:<14}  ea=0x{h.extra:x}  {fn_for(h.addr)}"
            )
    else:
        out.append("  (none)")

    out.append("SETTER-HELPER BL CALLS:")
    if groups["B"]:
        for h in groups["B"]:
            callee, argv = h.extra
            out.append(
                f"  0x{h.addr:x}  callee=0x{callee:x}  {h.label}  "
                f"value=0x{argv:x}  {fn_for(h.addr)}"
            )
    else:
        out.append("  (none)")

    out.append("POINTER-INIT STORES:")
    if groups["P"]:
        for h in groups["P"]:
            out.append(
                f"  0x{h.addr:x}  {h.label:<14}  source=0x{h.extra:x}  {fn_for(h.addr)}"
            )
    else:
        out.append("  (none)")

    return "\n".join(out)


def parse_range(spec):
    if "-" in spec:
        lo, hi = spec.split("-", 1)
        return int(lo, 0), int(hi, 0)
    addr = int(spec, 0)
    return addr, addr + 1


def main():
    ap = argparse.ArgumentParser(
        description="AArch64 binary ADRP-propagation xref scanner.")
    ap.add_argument("target", help="address (0xHEX) or lo-hi range")
    ap.add_argument("--elf", default=str(DEFAULT_ELF),
                    help="path to ELF (default: data/main.elf)")
    ap.add_argument("--runtime-base", default="0x7100000000",
                    help="runtime load address of the R+X segment "
                         "(default: 0x7100000000 for SSBU 13.0.4). Added to "
                         "ELF p_vaddr so all addresses match Ghidra.")
    ap.add_argument("--writers-only", action="store_true")
    ap.add_argument("--readers-only", action="store_true")
    ap.add_argument("--non-zero-writes", action="store_true",
                    help="filter out STP XZR/WZR writes and STR WZR/XZR")
    ap.add_argument("--called-as-arg", action="store_true",
                    help="report only setter-helper BL calls + ptr-init")
    args = ap.parse_args()

    target_lo, target_hi = parse_range(args.target)
    text, p_vaddr = load_rx_segment(args.elf)
    runtime_base = int(args.runtime_base, 0)
    base = p_vaddr + runtime_base

    want_r = not args.writers_only and not args.called_as_arg
    want_w = not args.readers_only and not args.called_as_arg
    want_bl = not args.writers_only and not args.readers_only
    want_pi = not args.writers_only and not args.readers_only

    hits = scan(text, base, target_lo, target_hi,
                want_readers=want_r, want_writers=want_w,
                want_bl=want_bl, want_ptrinit=want_pi)

    if args.non_zero_writes:
        # Drop writes whose source register is WZR/XZR. We can re-decode
        # the instruction to check Rt == 31 for single stores or both Rt
        # and Rt2 == 31 for pair stores.
        filtered = []
        for h in hits:
            if h.kind != "W":
                filtered.append(h)
                continue
            off = h.addr - base
            inst = struct.unpack_from("<I", text, off)[0]
            Rt = inst & 0x1F
            is_pair = decode_ldst_pair(inst) is not None
            if is_pair:
                Rt2 = (inst >> 10) & 0x1F
                if Rt == 31 and Rt2 == 31:
                    continue
            else:
                if Rt == 31:
                    continue
            filtered.append(h)
        hits = filtered

    groups = group_hits(hits)
    fn_starts, fn_names = load_functions()
    print(f"# Target: 0x{target_lo:x}"
          f"{'' if target_hi == target_lo + 1 else f'-0x{target_hi - 1:x}'}")
    print(f"# ELF: {args.elf}  text base=0x{base:x}  size=0x{len(text):x}")
    print(format_report(groups, fn_starts, fn_names))
    counts = {k: len(v) for k, v in groups.items()}
    print(f"# summary: W={counts['W']} R={counts['R']} "
          f"B={counts['B']} P={counts['P']}")


if __name__ == "__main__":
    main()
