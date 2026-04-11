"""Improved function-start finder and context dumper for 0x24e8 writers.

Finds function starts by scanning backwards for the standard prologue
`STP x29, x30, [sp, #-N]!` or `SUB sp, sp, #N`. Then dumps ~20 instructions
of context around each write and identifies the stored value's origin.
"""

import struct
import sys

sys.path.insert(0, "tools")
from xref_bin_scan import (
    load_text, idx_to_addr, dec_adrp, dec_add_imm, dec_mov_reg,
    dec_ldr_str_uimm, dec_ldr_str_simm, dec_stp_ldp, dec_ret, dec_uncond_b,
    dec_bl, RX_VA_START, word_at, disasm_window,
)


def is_prologue(w):
    """True if w looks like a function prologue instruction."""
    # STP x29, x30, [sp, #-imm]! (pre-index) => 1010100110 | imm7 | 11110 | 11111 | 11101
    # Or: SUB SP, SP, #imm (imm12 form)  => 1 1 0 10001 sh imm12 11111 11111
    # STP pre-index 64: 1010 1001 10 (= 0x2A6) top10
    top = (w >> 22) & 0x3FF
    if top == 0x2A6:  # STP pre-index 64
        Rt = w & 0x1F
        Rt2 = (w >> 10) & 0x1F
        Rn = (w >> 5) & 0x1F
        if Rt == 29 and Rt2 == 30 and Rn == 31:
            return True
    # SUB SP, SP, #imm: sf=1, op=1, S=0, 10001 sh imm12 Rn Rd  -> opcode 11010001 (sh=0) or similar
    if (w & 0xFF000000) == 0xD1000000:  # SUB imm 64-bit
        Rd = w & 0x1F
        Rn = (w >> 5) & 0x1F
        if Rd == 31 and Rn == 31:
            return True
    return False


def find_function_start(addr, max_scan=0x10000):
    """Scan backwards for the nearest prologue instruction.

    Looks for either a STP x29,x30,[sp,#-imm]! or a SUB sp,sp,#imm, provided
    the instruction immediately before is either RET, B (unconditional),
    BR/BLR, or four bytes of zero padding.
    """
    text = load_text()
    i = addr - RX_VA_START
    for step in range(0, max_scan, 4):
        j = i - step
        if j <= 0:
            break
        w = struct.unpack_from("<I", text, j)[0]
        if not is_prologue(w):
            continue
        # check the preceding word
        if j == 0:
            return RX_VA_START + j
        prev = struct.unpack_from("<I", text, j - 4)[0]
        if (
            dec_ret(prev)
            or (dec_uncond_b(prev) is not None and (prev >> 26) & 0x3F == 0x05)
            or prev == 0
            or (prev & 0xFFFFFC1F) == 0xD61F0000  # BR
            or (prev & 0xFFFFFC1F) == 0xD63F0000  # BLR
        ):
            return RX_VA_START + j
    return None


def trace_reg(start, end, target):
    """Forward pass from start to end to find target's origin."""
    text = load_text()
    src = {}
    adrp = {}
    i = start - RX_VA_START
    ei = end - RX_VA_START
    off = 0
    while i < ei:
        w = struct.unpack_from("<I", text, i)[0]
        off = i - (start - RX_VA_START)
        a = dec_adrp(w)
        if a:
            Rd, imm = a
            adrp[Rd] = ((start + off) & ~0xFFF) + imm
            src[Rd] = f"ADRP {adrp[Rd]:#x}"
            i += 4; continue
        ad = dec_add_imm(w)
        if ad:
            sf, Rd, Rn, imm = ad
            if Rn in adrp:
                adrp[Rd] = adrp[Rn] + imm
                src[Rd] = f"&({adrp[Rd]:#x})"
            else:
                adrp.pop(Rd, None)
                src[Rd] = f"ADD X{Rn}+{imm:#x}"
            i += 4; continue
        m = dec_mov_reg(w)
        if m:
            sf, Rd, Rm = m
            if Rm in src:
                src[Rd] = f"X{Rd}=X{Rm}({src[Rm]})"
            else:
                src[Rd] = f"X{Rd}=X{Rm}"
            if Rm in adrp:
                adrp[Rd] = adrp[Rm]
            else:
                adrp.pop(Rd, None)
            # Special mark: MOV from X0 at entry => param0
            if Rm == 0 and off < 0x50:
                src[Rd] = f"param0 (MOV at +{off:#x})"
            if Rm == 1 and off < 0x50:
                src[Rd] = f"param1 (MOV at +{off:#x})"
            i += 4; continue
        d = dec_ldr_str_uimm(w)
        if d:
            sz, is_load, imm, Rn, Rt = d
            if is_load:
                if Rn in adrp:
                    addr = adrp[Rn] + imm
                    src[Rt] = f"LDR[{addr:#x}]"
                    adrp.pop(Rt, None)
                else:
                    # chain through src
                    base = src.get(Rn, f"X{Rn}")
                    src[Rt] = f"LDR[{base}+{imm:#x}]"
                    adrp.pop(Rt, None)
            i += 4; continue
        d = dec_ldr_str_simm(w)
        if d:
            sz, is_load, imm, Rn, Rt = d
            if is_load:
                base = src.get(Rn, f"X{Rn}")
                src[Rt] = f"LDUR[{base}+{imm}]"
                adrp.pop(Rt, None)
            i += 4; continue
        bl = dec_bl(w)
        if bl is not None:
            tgt = (RX_VA_START + i + bl)
            src[0] = f"BL_ret({tgt:#x})"
            for r in range(1, 18):
                adrp.pop(r, None)
                src.pop(r, None)
            i += 4; continue
        i += 4
    return src.get(target, "?")


def main():
    candidates = [
        (0x7102A5FB1C, 19, 8),
        (0x7102A60D88, 19, 8),
        (0x710352662C, 20, 9),
        (0x71035392F8, 20, 10),
        (0x7103757CD0, 19, 20),
    ]
    for addr, Rn, Rt in candidates:
        print(f"\n=== {addr:#x}  STR X{Rt},[X{Rn},#0x24e8] ===")
        start = find_function_start(addr)
        if start is None:
            print("  function start NOT FOUND")
            continue
        print(f"  fn start: {start:#x}   (size to here: {addr - start:#x})")
        src_rn = trace_reg(start, addr, Rn)
        src_rt = trace_reg(start, addr + 4, Rt)
        print(f"  X{Rn} source: {src_rn}")
        print(f"  X{Rt} source: {src_rt}")


if __name__ == "__main__":
    main()
