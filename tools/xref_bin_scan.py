"""Direct binary ADRP/instruction scanner for the SSBU main.elf.

Why: Ghidra's xref index misses code in regions its auto-analyzer has not
carved into functions. For "who writes to global X" or "who writes field F"
questions, a direct raw-.text scan is more reliable.

Primary modes:
  - find_store_offset: all STR/STRB/STRH/STUR with a given immediate offset
  - find_adrp_access: track ADRP+ADD/LDR/STR flows that compute a target global
  - decode_at: disassemble a single instruction (summary form)

Addresses are expressed in the Ghidra virtual scheme (base 0x71000000).
"""

import struct
import sys

ELF_PATH = "original/main.elf"
# Ghidra loads the NSO at 0x7100000000 (36-bit base, Switch virtual addressing).
GHIDRA_BASE = 0x7100000000
RX_FILE_OFFSET = 0x378  # PT_LOAD R+X file offset for vaddr 0
RX_VA_START = GHIDRA_BASE
RX_VA_END = GHIDRA_BASE + 0x39C7E90


def load_text():
    with open(ELF_PATH, "rb") as f:
        data = f.read()
    # .text in file: [RX_FILE_OFFSET, RX_FILE_OFFSET + (RX_VA_END-RX_VA_START))
    size = RX_VA_END - RX_VA_START
    return data[RX_FILE_OFFSET : RX_FILE_OFFSET + size]


def addr_to_idx(addr):
    return addr - RX_VA_START


def idx_to_addr(i):
    return RX_VA_START + i


def word_at(text, addr):
    i = addr_to_idx(addr)
    return struct.unpack_from("<I", text, i)[0]


# ---- instruction decoders -----------------------------------------------
# All helpers return None if the word doesn't match that form.


def dec_adrp(w):
    # 1 immlo:2 10000 immhi:19 Rd:5
    if (w >> 31) & 1 != 1:
        return None
    if (w >> 24) & 0x1F != 0x10:
        return None
    immlo = (w >> 29) & 3
    immhi = (w >> 5) & 0x7FFFF
    imm = ((immhi << 2) | immlo)
    # sign-extend 21 bits
    if imm & (1 << 20):
        imm -= 1 << 21
    Rd = w & 0x1F
    return (Rd, imm << 12)


def dec_add_imm(w):
    # sf 0 0 10001 sh imm12 Rn Rd (ADD immediate)
    if ((w >> 24) & 0x7F) != 0x22:
        return None
    sf = (w >> 31) & 1
    sh = (w >> 22) & 1
    imm12 = (w >> 10) & 0xFFF
    Rn = (w >> 5) & 0x1F
    Rd = w & 0x1F
    imm = imm12 << (12 if sh else 0)
    return (sf, Rd, Rn, imm)


def dec_sub_imm(w):
    # sf 1 0 10001 sh imm12 Rn Rd
    if ((w >> 24) & 0x7F) != 0x62:
        return None
    sf = (w >> 31) & 1
    sh = (w >> 22) & 1
    imm12 = (w >> 10) & 0xFFF
    Rn = (w >> 5) & 0x1F
    Rd = w & 0x1F
    imm = imm12 << (12 if sh else 0)
    return (sf, Rd, Rn, imm)


def dec_mov_reg(w):
    # ORR (shifted register) Rd, WZR/XZR, Rm  -> MOV alias
    # sf 0101010 shift 0 Rm imm6 Rn Rd  with shift=0, imm6=0, Rn=31
    sf = (w >> 31) & 1
    if ((w >> 24) & 0x7F) != 0x2A:
        return None
    shift = (w >> 22) & 3
    N = (w >> 21) & 1
    Rm = (w >> 16) & 0x1F
    imm6 = (w >> 10) & 0x3F
    Rn = (w >> 5) & 0x1F
    Rd = w & 0x1F
    if shift != 0 or N != 0 or imm6 != 0 or Rn != 31:
        return None
    return (sf, Rd, Rm)


def dec_ret(w):
    # RET: 1101011 0 0 10 11111 000000 Rn 00000
    return (w & 0xFFFFFC1F) == 0xD65F0000


def dec_uncond_b(w):
    if ((w >> 26) & 0x3F) != 0x05:
        return None
    imm26 = w & 0x03FFFFFF
    if imm26 & (1 << 25):
        imm26 -= 1 << 26
    return imm26 << 2


def dec_bl(w):
    if ((w >> 26) & 0x3F) != 0x25:
        return None
    imm26 = w & 0x03FFFFFF
    if imm26 & (1 << 25):
        imm26 -= 1 << 26
    return imm26 << 2


def dec_cbz_cbnz(w):
    op = (w >> 24) & 0x7F
    if op != 0x34 and op != 0x35:
        return None
    return True


def dec_ldr_str_uimm(w):
    """Return (size_bits, is_load, imm, Rn, Rt) for LDR/STR unsigned-imm forms.

    Covers:
      STR/LDR Xt  [size=11, V=0, opc=00/01, imm12 scaled*8]
      STR/LDR Wt  [size=10, V=0, opc=00/01, imm12 scaled*4]
      STRH/LDRH   [size=01, V=0, opc=00/01, imm12 scaled*2]
      STRB/LDRB   [size=00, V=0, opc=00/01, imm12 scaled*1]
    """
    if ((w >> 24) & 0x3F) != 0x39:
        return None
    if ((w >> 26) & 1) != 0:  # V=0 only
        return None
    size = (w >> 30) & 3
    opc = (w >> 22) & 3
    if opc > 1:
        return None  # skip LDRSB/SH/SW forms for now
    is_load = opc == 1
    imm12 = (w >> 10) & 0xFFF
    Rn = (w >> 5) & 0x1F
    Rt = w & 0x1F
    scale = 1 << size
    return (8 << size, is_load, imm12 * scale, Rn, Rt)


def dec_ldr_str_simm(w):
    """LDUR/STUR forms with signed 9-bit imm (unscaled)."""
    if ((w >> 24) & 0x3F) != 0x38:
        return None
    if ((w >> 10) & 3) != 0:
        return None
    if ((w >> 21) & 1) != 0:
        return None
    size = (w >> 30) & 3
    opc = (w >> 22) & 3
    if opc > 1:
        return None
    is_load = opc == 1
    imm9 = (w >> 12) & 0x1FF
    if imm9 & 0x100:
        imm9 -= 0x200
    Rn = (w >> 5) & 0x1F
    Rt = w & 0x1F
    return (8 << size, is_load, imm9, Rn, Rt)


def dec_stp_ldp(w):
    """STP/LDP (signed offset) 64/32-bit. Returns (size_bits, is_load, imm, Rn, Rt, Rt2)."""
    # 1010100 1 L 0 imm7 Rt2 Rn Rt   (STP/LDP 64-bit signed offset)
    # size bits are [31:30]: 10=32-bit, 10... actually:
    # 64-bit: op=0x29 (bits 29:22 = 10100100 => 64-bit signed offset STP; 10100101 LDP)
    # Simpler: check bits [29:23] == 1010010 and [26:23]==0010 scratch...
    top = (w >> 22) & 0x3FF  # 10 bits
    # STP 64-bit signed offset: 1010 1001 00  -> 0x2A4
    # LDP 64-bit signed offset: 1010 1001 01  -> 0x2A5
    # STP 32-bit signed offset: 1010 1000 00  -> 0x2A0
    # LDP 32-bit signed offset: 1010 1000 01  -> 0x2A1
    if top == 0x2A4:
        sz, ld = 64, False
    elif top == 0x2A5:
        sz, ld = 64, True
    elif top == 0x2A0:
        sz, ld = 32, False
    elif top == 0x2A1:
        sz, ld = 32, True
    else:
        return None
    imm7 = (w >> 15) & 0x7F
    if imm7 & 0x40:
        imm7 -= 0x80
    scale = 8 if sz == 64 else 4
    Rt2 = (w >> 10) & 0x1F
    Rn = (w >> 5) & 0x1F
    Rt = w & 0x1F
    return (sz, ld, imm7 * scale, Rn, Rt, Rt2)


# ---- scanners -----------------------------------------------------------


def scan_store_offset(target_offset, size_filter=None):
    """Find every STR/STUR/STP with the given immediate offset.

    size_filter: None, 64, 32, 16, 8 to narrow.
    Returns list of (addr, kind, Rn, Rt, extra).
    """
    text = load_text()
    hits = []
    for i in range(0, len(text) - 4, 4):
        w = struct.unpack_from("<I", text, i)[0]
        addr = idx_to_addr(i)
        d = dec_ldr_str_uimm(w)
        if d is not None:
            sz, is_load, imm, Rn, Rt = d
            if not is_load and imm == target_offset:
                if size_filter is None or sz == size_filter:
                    kind = {8: "STRB", 16: "STRH", 32: "STR_W", 64: "STR_X"}[sz]
                    hits.append((addr, kind, Rn, Rt, None))
            continue
        d = dec_ldr_str_simm(w)
        if d is not None:
            sz, is_load, imm, Rn, Rt = d
            if not is_load and imm == target_offset:
                if size_filter is None or sz == size_filter:
                    kind = {8: "STURB", 16: "STURH", 32: "STUR_W", 64: "STUR_X"}[sz]
                    hits.append((addr, kind, Rn, Rt, None))
            continue
        d = dec_stp_ldp(w)
        if d is not None:
            sz, is_load, imm, Rn, Rt, Rt2 = d
            if not is_load and imm == target_offset:
                if size_filter is None or sz == size_filter:
                    kind = "STP_X" if sz == 64 else "STP_W"
                    hits.append((addr, kind, Rn, Rt, Rt2))
    return hits


def scan_adrp_global_writers(page_base, offset):
    """Forward-propagate ADRP chains to find stores to the exact global (page_base + offset).

    Tracked ops: ADRP sets Rd=page_base; ADD imm extends with offset; LDR [Rn, #imm]
    materialises the pointer pointed-to; MOV Rd, Rm copies; AUX stores clear Rd.
    Returns list of (addr, instr_kind, stored_from_reg_or_None).
    """
    text = load_text()
    target_addr = page_base + offset
    hits = []
    regs = {}
    memregs = {}  # regs that hold a *loaded* value from the target
    block_start = 0
    for i in range(0, len(text) - 4, 4):
        w = struct.unpack_from("<I", text, i)[0]
        addr = idx_to_addr(i)

        if dec_ret(w) or dec_uncond_b(w) is not None:
            regs = {}
            memregs = {}
            block_start = i + 4
            continue

        a = dec_adrp(w)
        if a is not None:
            Rd, imm = a
            regs[Rd] = (addr & ~0xFFF) + imm
            continue

        ad = dec_add_imm(w)
        if ad is not None:
            sf, Rd, Rn, imm = ad
            if Rn in regs:
                regs[Rd] = regs[Rn] + imm
            else:
                regs.pop(Rd, None)
            continue

        m = dec_mov_reg(w)
        if m is not None:
            sf, Rd, Rm = m
            if Rm in regs:
                regs[Rd] = regs[Rm]
            else:
                regs.pop(Rd, None)
            if Rm in memregs:
                memregs[Rd] = memregs[Rm]
            else:
                memregs.pop(Rd, None)
            continue

        # Check loads/stores via unsigned imm form
        d = dec_ldr_str_uimm(w)
        if d is not None:
            sz, is_load, imm, Rn, Rt = d
            eff = None
            if Rn in regs:
                eff = regs[Rn] + imm
            if is_load:
                if eff == target_addr and sz == 64:
                    memregs[Rt] = target_addr
                else:
                    memregs.pop(Rt, None)
                    regs.pop(Rt, None)
            else:
                if eff == target_addr:
                    hits.append((addr, "STR", Rn, Rt, imm, "direct-global-store"))
                # if Rn was a memreg pointing at target and imm applied, that's a ptr-deref store
                if Rn in memregs and imm == 0:
                    hits.append((addr, "STR-via-memreg", Rn, Rt, imm, "store-through-loaded-ptr"))
            continue

        # Clear Rd for any other instruction that writes it - conservative: skip
    return hits


def disasm_window(addr, before=6, after=6):
    """Quick textual window around an address, four-byte words with decoders."""
    text = load_text()
    lines = []
    for k in range(-before, after + 1):
        a = addr + k * 4
        w = word_at(text, a)
        tag = ""
        x = dec_adrp(w)
        if x:
            tag = f"ADRP X{x[0]}, page+0x{x[1]:x}"
        x = dec_add_imm(w)
        if x and not tag:
            tag = f"ADD X{x[1]},X{x[2]},#0x{x[3]:x}"
        x = dec_ldr_str_uimm(w)
        if x and not tag:
            sz, ld, imm, Rn, Rt = x
            tag = f"{'LDR' if ld else 'STR'}{sz} X{Rt},[X{Rn},#0x{imm:x}]"
        x = dec_stp_ldp(w)
        if x and not tag:
            sz, ld, imm, Rn, Rt, Rt2 = x
            tag = f"{'LDP' if ld else 'STP'}{sz} X{Rt},X{Rt2},[X{Rn},#{imm:+#x}]"
        x = dec_mov_reg(w)
        if x and not tag:
            tag = f"MOV X{x[1]},X{x[2]}"
        x = dec_bl(w)
        if x is not None and not tag:
            tag = f"BL {(a+x)&0xFFFFFFFFFFFFFFFF:#x}"
        x = dec_uncond_b(w)
        if x is not None and not tag and (w >> 26) & 0x3F == 0x05:
            tag = f"B {(a+x)&0xFFFFFFFFFFFFFFFF:#x}"
        if dec_ret(w) and not tag:
            tag = "RET"
        lines.append(f"  {a:010x}: {w:08x}  {tag}")
    return "\n".join(lines)


# ---- CLI ----------------------------------------------------------------


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return
    cmd = sys.argv[1]
    if cmd == "store-offset":
        off = int(sys.argv[2], 0)
        sz = int(sys.argv[3], 0) if len(sys.argv) > 3 else None
        hits = scan_store_offset(off, sz)
        print(f"{len(hits)} store hits with offset {off:#x}")
        for addr, kind, Rn, Rt, extra in hits:
            extra_s = f" Rt2={extra}" if extra is not None else ""
            print(f"  {addr:010x} {kind:6s} X{Rt},[X{Rn},#{off:#x}]{extra_s}")
    elif cmd == "adrp-global":
        page = int(sys.argv[2], 0)
        offs = int(sys.argv[3], 0)
        hits = scan_adrp_global_writers(page, offs)
        print(f"{len(hits)} writer hits for {(page+offs):#x}")
        for h in hits:
            print(" ", h)
    elif cmd == "window":
        a = int(sys.argv[2], 0)
        print(disasm_window(a))
    elif cmd == "word":
        a = int(sys.argv[2], 0)
        text = load_text()
        w = word_at(text, a)
        print(f"{a:010x}: {w:08x}")
    else:
        print("unknown command")


if __name__ == "__main__":
    main()
