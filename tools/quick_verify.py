#!/usr/bin/env python3
"""Quick byte-level verification for a single .o file using objdump.
Usage: python tools/quick_verify.py build/fun_batch_d5_049.o
"""
import struct, re, sys, subprocess

ELF = 'data/main.elf'
BASE = 0x7100000000

segments = []
with open(ELF, 'rb') as f:
    f.seek(0x20); phoff = struct.unpack('<Q', f.read(8))[0]
    f.seek(0x36)
    phentsize = struct.unpack('<H', f.read(2))[0]
    phnum = struct.unpack('<H', f.read(2))[0]
    for i in range(phnum):
        f.seek(phoff + i * phentsize)
        p_type = struct.unpack('<I', f.read(4))[0]; f.read(4)
        p_offset = struct.unpack('<Q', f.read(8))[0]
        p_vaddr = struct.unpack('<Q', f.read(8))[0]; f.read(8)
        p_filesz = struct.unpack('<Q', f.read(8))[0]
        if p_type == 1: segments.append((p_vaddr, p_offset, p_filesz))

def read_binary(addr, size):
    va = addr - BASE
    with open(ELF, 'rb') as f:
        for sv, so, ss in segments:
            if sv <= va < sv + ss:
                f.seek(so + (va - sv))
                return f.read(size)
    return None

o_file = sys.argv[1] if len(sys.argv) > 1 else 'build/fun_batch_d5_049.o'
show_diff = '--diff' in sys.argv

result = subprocess.run(['C:/llvm-8.0.0/bin/llvm-objdump.exe', '-d', o_file],
                       capture_output=True, text=True)

current_func = None
func_bytes = {}
for line in result.stdout.split('\n'):
    m = re.match(r'^[0-9a-f]+ ([_A-Za-z]\S+):', line)
    if m:
        current_func = m.group(1)
        func_bytes[current_func] = bytearray()
        continue
    if current_func:
        m2 = re.match(r'^\s+[0-9a-f]+:\s+([0-9a-f ]+)\t', line)
        if m2:
            try:
                func_bytes[current_func] += bytes.fromhex(m2.group(1).strip().replace(' ', ''))
            except ValueError:
                pass

# Extract addresses from mangled names
addr_map = {}
for name in func_bytes:
    # Try FUN_<hex> pattern first
    m = re.search(r'FUN_(7[0-9a-fA-F]{8,10})', name)
    if m:
        addr_map[name] = int(m.group(1), 16)
        continue
    # Try named functions with hex suffix
    m = re.search(r'_impl_(7[0-9a-fA-F]{8,10})', name)
    if m:
        addr_map[name] = int(m.group(1), 16)

total = 0; matched = 0
for mangled in sorted(addr_map, key=lambda x: addr_map[x]):
    addr = addr_map[mangled]
    compiled = func_bytes[mangled]
    original = read_binary(addr, len(compiled))
    if original is None:
        continue
    n = len(compiled) // 4
    total += 1
    exact = reloc = 0
    diffs = []
    for i in range(0, len(compiled), 4):
        c = struct.unpack('<I', compiled[i:i+4])[0]
        o = struct.unpack('<I', original[i:i+4])[0]
        if c == o:
            exact += 1; reloc += 1
        elif (c & 0xfc000000) == (o & 0xfc000000) and (c & 0xfc000000) in (0x94000000, 0x14000000):
            reloc += 1  # bl/b with different offset
        elif (c & 0x9f000000) == (o & 0x9f000000) == 0x90000000 and (c & 0x1f) == (o & 0x1f):
            reloc += 1  # adrp with same Rd, different page
        elif (c & 0xffc003e0) == (o & 0xffc003e0) and (c & 0xffc00000) in (0xf9400000, 0xf9000000, 0xb9400000, 0xb9000000):
            reloc += 1  # ldr/str with same regs, different offset (lo12 reloc)
        else:
            diffs.append((i//4, c, o))
    short = f'FUN_{addr:x}'
    if reloc == n:
        matched += 1
        print(f'{short}: MATCH ({n} insns)')
    else:
        print(f'{short}: {exact}/{n} exact, {reloc}/{n} w/reloc')
        if show_diff:
            for idx, c, o in diffs[:5]:
                print(f'  [{idx}] compiled=0x{c:08x} expected=0x{o:08x}')

print(f'\n{matched}/{total} functions matching')
