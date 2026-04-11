#!/usr/bin/env python3
"""disasm_window.py - Disassemble a small window of AArch64 instructions
from the runtime-addressed binary. Used for targeted inspection near known
stores/calls when Ghidra is too slow to decompile the enclosing function.

Usage:
    python tools/disasm_window.py 0x71013495XX [--before 64] [--after 32]
"""

import argparse
import struct
import sys
from pathlib import Path

import capstone

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_ELF = REPO_ROOT / "data" / "main.elf"


def load_rx_segment(elf_path):
    with open(elf_path, "rb") as f:
        data = f.read()
    if data[:4] != b"\x7fELF":
        raise SystemExit(f"{elf_path}: not an ELF")
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


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("addr", help="runtime address (hex)")
    ap.add_argument("--before", type=int, default=64, help="bytes before")
    ap.add_argument("--after", type=int, default=32, help="bytes after")
    ap.add_argument("--elf", default=str(DEFAULT_ELF))
    ap.add_argument("--runtime-base", default="0x7100000000")
    args = ap.parse_args()

    target = int(args.addr, 16)
    text, vaddr = load_rx_segment(args.elf)
    rt_base = int(args.runtime_base, 16)
    # runtime_addr = p_vaddr + rt_base
    file_off = target - rt_base - vaddr
    if file_off < 0 or file_off >= len(text):
        raise SystemExit(f"address {args.addr} out of text segment")

    start = max(0, file_off - args.before)
    end = min(len(text), file_off + args.after)
    window = text[start:end]
    window_va = rt_base + vaddr + start

    md = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_ARM)
    md.detail = False
    for insn in md.disasm(window, window_va):
        marker = " <==" if insn.address == target else ""
        print(f"  0x{insn.address:010x}: {insn.mnemonic:<8} {insn.op_str}{marker}")


if __name__ == "__main__":
    main()
