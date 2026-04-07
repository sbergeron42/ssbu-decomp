#!/usr/bin/env python3
"""
Fix epilogue scheduling in batch_c/d .o files using a whitelist.

NX Clang places `ldp x29, x30, [sp], #N` BEFORE `mov w0, wzr` in the epilogue,
but upstream Clang 8.0.0 may put `mov w0, wzr` first. This script swaps them
only for functions listed in build/epilogue_swap_list.txt.
"""

import struct
import sys
from pathlib import Path

RET_INSN = 0xd65f03c0
LDP_X29_X30_MASK = 0xFFC07FFF
LDP_X29_X30_BITS = 0xA8C00000 | (30 << 10) | (31 << 5) | 29


def load_whitelist():
    p = Path(__file__).parent.parent / 'build' / 'epilogue_swap_list.txt'
    if not p.exists():
        return set()
    return set(line.strip() for line in p.read_text().splitlines() if line.strip())


def process_elf(filepath, whitelist, dry_run=False):
    path = Path(filepath)
    name = path.name
    if not (name.startswith('fun_batch_c_') or name.startswith('fun_batch_d_') or name.startswith('fun_batch_e2_')):
        return 0

    data = bytearray(path.read_bytes())
    if data[:4] != b'\x7fELF' or data[4] != 2 or data[5] != 1:
        return 0

    e_shoff = struct.unpack_from('<Q', data, 0x28)[0]
    e_shentsize = struct.unpack_from('<H', data, 0x3A)[0]
    e_shnum = struct.unpack_from('<H', data, 0x3C)[0]
    e_shstrndx = struct.unpack_from('<H', data, 0x3E)[0]

    shstrtab_off = struct.unpack_from('<Q', data,
                                       e_shoff + e_shstrndx * e_shentsize + 0x18)[0]

    text_sections = {}
    rela_sections = {}

    for i in range(e_shnum):
        sh_off = e_shoff + i * e_shentsize
        sh_name_idx = struct.unpack_from('<I', data, sh_off)[0]
        sh_type = struct.unpack_from('<I', data, sh_off + 4)[0]
        sh_offset = struct.unpack_from('<Q', data, sh_off + 0x18)[0]
        sh_size = struct.unpack_from('<Q', data, sh_off + 0x20)[0]

        name_end = data.index(0, shstrtab_off + sh_name_idx)
        sec_name = data[shstrtab_off + sh_name_idx:name_end].decode('ascii', errors='replace')

        if sh_type == 1 and sec_name.startswith('.text.'):
            text_sections[i] = (sec_name, sh_offset, sh_size)
        elif sh_type == 4:
            sh_info = struct.unpack_from('<I', data, sh_off + 0x2C)[0]
            rela_sections[sh_info] = (sh_offset, sh_size)

    patches = 0
    for sec_idx, (sec_name, sec_off, sec_size) in text_sections.items():
        # Extract mangled name from section name (.text.MANGLED_NAME)
        mangled = sec_name[6:]  # strip ".text."
        if mangled not in whitelist:
            continue

        if sec_size < 12:
            continue

        last3_off = sec_off + sec_size - 12
        insn_a = struct.unpack_from('<I', data, last3_off)[0]
        insn_b = struct.unpack_from('<I', data, last3_off + 4)[0]
        insn_c = struct.unpack_from('<I', data, last3_off + 8)[0]

        if insn_c != RET_INSN:
            continue
        if (insn_b & LDP_X29_X30_MASK) != LDP_X29_X30_BITS:
            continue
        if (insn_a & LDP_X29_X30_MASK) == LDP_X29_X30_BITS:
            continue
        rd = insn_a & 0x1F
        if rd != 0:
            continue

        if dry_run:
            patches += 1
            continue

        struct.pack_into('<I', data, last3_off, insn_b)
        struct.pack_into('<I', data, last3_off + 4, insn_a)

        swap_off_a = sec_size - 12
        swap_off_b = sec_size - 8
        if sec_idx in rela_sections:
            rela_off, rela_size = rela_sections[sec_idx]
            num_entries = rela_size // 24
            for j in range(num_entries):
                entry_off = rela_off + j * 24
                r_offset = struct.unpack_from('<Q', data, entry_off)[0]
                if r_offset == swap_off_a:
                    struct.pack_into('<Q', data, entry_off, swap_off_b)
                elif r_offset == swap_off_b:
                    struct.pack_into('<Q', data, entry_off, swap_off_a)

        patches += 1

    if patches > 0 and not dry_run:
        path.write_bytes(data)

    return patches


def main():
    whitelist = load_whitelist()
    if not whitelist:
        return

    import glob as _glob
    dry_run = '--dry-run' in sys.argv
    files = []
    for f in sys.argv[1:]:
        if f.startswith('--'):
            continue
        matched = _glob.glob(f)
        files.extend(matched if matched else [f])
    for f in files:
        process_elf(f, whitelist, dry_run=dry_run)


if __name__ == '__main__':
    main()
