#!/usr/bin/env python3
"""Generate ALL remaining matchable functions (no b/adrp/simd) from the original ELF."""
import struct, csv, subprocess, re
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
DECOMP_ELF = PROJECT_ROOT / "build" / "ssbu-decomp.elf"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"
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
            p_vaddr = struct.unpack('<Q', f.read(8))[0]; f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1: segments.append((p_vaddr, p_offset, p_filesz))
    return segments

def read_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv)); return f.read(size)
    return None

def extract_func_name(m):
    prefix = "_ZN3app8lua_bind"
    if not m.startswith(prefix): return None
    rest = m[len(prefix):]
    i = 0
    while i < len(rest) and rest[i].isdigit(): i += 1
    if i == 0: return None
    l = int(rest[:i]); return rest[i:i+l] if len(rest[i:i+l]) == l else None

def guess_ret(fn):
    s = fn.split('__')[1] if '__' in fn else fn
    if s.startswith(('is_','can_','chk_')): return 'bool'
    if s.startswith(('set_','clear_','reset_','enable_','unable_','add_','on_','off_',
        'start_','stop_','load_','save_','eject_','kill_','req_','send_','sleep_','entry_',
        'leave_','update_','detach_','notify_','prepare_','exit_','resume_','pause_','hide_',
        'show_','delete_','change_','remove_','end_','adjust_','modify_','pass_','ignore_',
        'attach_','correct_','select_','reentry_','test_','sync_','have_','use_','final_')): return 'void'
    if s.startswith('get_') and any(w in s for w in ['kind','flag','count','num','id','type','no']): return 'u32'
    if s.startswith('get_'): return 'void*'
    return 'void*'

def main():
    orig_segs = load_elf_segments(ORIGINAL_ELF)
    result = subprocess.run([OBJDUMP, '-t', str(DECOMP_ELF)], capture_output=True, text=True)
    compiled = set()
    for line in result.stdout.split('\n'):
        if 'F .text' in line:
            short = extract_func_name(line.split()[-1])
            if short: compiled.add(short)

    generated = defaultdict(list)
    skipped = 0

    with open(ORIGINAL_ELF, 'rb') as f:
        with open(PROJECT_ROOT / 'data' / 'functions.csv') as cf:
            reader = csv.reader(cf); next(reader)
            for row in reader:
                if row[1] != 'U': continue
                name = row[3]
                if name in compiled or '__' not in name or name.startswith('FUN_'): continue
                addr = int(row[0], 16); vaddr = addr - ELF_BASE
                raw = read_bytes(f, orig_segs, vaddr, 128)
                if not raw: continue

                insns = []
                for i in range(0, min(len(raw), 128), 4):
                    insn = struct.unpack('<I', raw[i:i+4])[0]
                    insns.append(insn)
                    if insn == 0xD65F03C0 or (insn & 0xFFFFFC1F) == 0xD61F0000: break

                has_b = any((i & 0xFC000000) == 0x14000000 for i in insns)
                has_adrp = any((i & 0x9F000000) == 0x90000000 for i in insns)
                has_simd = any(((i >> 24) & 0xFF) in (0x4C,0x4E,0x6E,0x0E,0x3D,0x1E,0xBD,0x3C,0x0D,0x4D,0x2D,0x6D) for i in insns)
                if has_b or has_adrp or has_simd: continue

                n = len(insns)
                module = name.split('__')[0]
                last = insns[-1]
                has_br = (last & 0xFFFFFC1F) == 0xD61F0000

                # --- Vtable dispatch (br) ---
                if has_br and n <= 10:
                    vt_off = None
                    for insn in insns:
                        if (insn & 0xFFC00000) == 0xF9400000 and ((insn >> 5) & 0x1F) == 8:
                            vt_off = ((insn >> 10) & 0xFFF) * 8; break
                    if vt_off is None: skipped += 1; continue

                    br_reg = (last >> 5) & 0x1F
                    num_params = br_reg - 1
                    bool_regs = set(i & 0x1F for i in insns if (i & 0xFFFFFC00) == 0x12000000)
                    const_args = {}
                    for insn in insns:
                        if (insn & 0xFF800000) == 0x52800000:
                            const_args[insn & 0x1F] = str((insn >> 5) & 0xFFFF)
                        elif (insn & 0xFF800000) == 0x12800000:
                            const_args[insn & 0x1F] = str(-((insn >> 5) & 0xFFFF) - 1)
                        elif (insn & 0xFFE0FFE0) == 0x2A0003E0 and ((insn >> 16) & 0x1F) == 31:
                            const_args[insn & 0x1F] = '0'

                    first = insns[0]
                    if (first & 0xFFC00000) == 0xF9400000:
                        rn = (first >> 5) & 0x1F; rt = first & 0x1F
                        if rn == 0 and rt == 0:
                            mod_off = ((first >> 10) & 0xFFF) * 8
                            fp = 'BattleObjectModuleAccessor* a'
                            obj = 'reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+%s))' % hex(mod_off)
                            fc = 'void*'; use_m = True
                        elif rn == 0 and rt == 8:
                            fp = '%s* obj' % module; obj = None; fc = '%s*' % module; use_m = False
                        else: skipped += 1; continue
                    else: skipped += 1; continue

                    ret = guess_ret(name); rk = 'return ' if ret != 'void' else ''; cr = ret if ret != 'void' else 'void'
                    ps = [fp]; ar = ['m' if use_m else 'obj']; cp = [fc]
                    for i in range(num_params):
                        reg = i + 1
                        if reg in const_args: continue
                        if reg in bool_regs: ps.append('bool p%d' % (i+1)); cp.append('bool')
                        else: ps.append('u64 p%d' % (i+1)); cp.append('u64')
                        ar.append('p%d' % (i+1))
                    for reg in sorted(const_args.keys()):
                        if reg > 0: cp.append('u64'); v = const_args[reg]
                        else: continue
                        ar.append('static_cast<u64>(%s)' % v if v.startswith('-') else v)

                    if use_m:
                        line = '%s %s(%s) { auto* m=%s; %sreinterpret_cast<%s(*)(%s)>(VT(m)[%s/8])(%s); }' % (ret, name, ','.join(ps), obj, rk, cr, ','.join(cp), hex(vt_off), ','.join(ar))
                    else:
                        line = '%s %s(%s) { %sreinterpret_cast<%s(*)(%s)>(VT(obj)[%s/8])(%s); }' % (ret, name, ','.join(ps), rk, cr, ','.join(cp), hex(vt_off), ','.join(ar))
                    generated[module].append((name, line)); continue

                # --- add x0, x0, #imm; ret ---
                if n == 2 and insns[1] == 0xD65F03C0 and (insns[0] & 0xFFC00000) == 0x91000000:
                    rd = insns[0] & 0x1F; rn = (insns[0] >> 5) & 0x1F
                    if rd == 0 and rn == 0:
                        imm = (insns[0] >> 10) & 0xFFF
                        line = 'void* %s(%s* obj) { return reinterpret_cast<u8*>(obj) + %s; }' % (name, module, hex(imm))
                        generated[module].append((name, line)); continue

                # --- mov+strb+ret (set flag) ---
                if n == 3 and insns[2] == 0xD65F03C0:
                    if (insns[0] & 0xFF800000) == 0x52800000 and (insns[1] & 0xFFC00000) == 0x39000000:
                        val = (insns[0] >> 5) & 0xFFFF; off = (insns[1] >> 10) & 0xFFF
                        line = 'void %s(%s* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = %d; }' % (name, module, hex(off), val)
                        generated[module].append((name, line)); continue

                # --- strb wzr+ret (clear flag) ---
                if n == 2 and insns[1] == 0xD65F03C0 and (insns[0] & 0xFFC00000) == 0x39000000:
                    rt = insns[0] & 0x1F
                    if rt == 31:
                        off = (insns[0] >> 10) & 0xFFF
                        line = 'void %s(%s* obj) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + %s) = 0; }' % (name, module, hex(off))
                        generated[module].append((name, line)); continue

                # --- just ret (noop) ---
                if n == 1 and insns[0] == 0xD65F03C0:
                    line = 'void %s(%s* obj) { }' % (name, module)
                    generated[module].append((name, line)); continue

                skipped += 1

    total = sum(len(v) for v in generated.values())
    print('Generated: %d, Skipped: %d' % (total, skipped))

    # Write to source files
    src_dir = PROJECT_ROOT / 'src' / 'app'
    for module, funcs in sorted(generated.items()):
        candidates = list(src_dir.rglob('%s.cpp' % module))
        if candidates:
            src_file = candidates[0]
            content = src_file.read_text()
            if '} // namespace app::lua_bind' not in content: continue
            block = ''
            has_vt = '#define VT(' in content or '#define VTABLE(' in content
            for name, line in funcs:
                if name + '(' not in content:
                    block += line + '\n'
            if block:
                if not has_vt and 'VT(' in block:
                    content = content.replace('namespace app::lua_bind {',
                        '#define VT(m) (*reinterpret_cast<void***>(m))\nnamespace app::lua_bind {', 1)
                content = content.replace('} // namespace app::lua_bind', block + '} // namespace app::lua_bind')
                src_file.write_text(content)
                print('  Updated %s (+%d)' % (src_file.name, block.count('\n')))
        else:
            src_file = src_dir / ('%s.cpp' % module)
            content = '#include "types.h"\n#define VT(m) (*reinterpret_cast<void***>(m))\n\nstruct %s;\n\nnamespace app::lua_bind {\n\n' % module
            for name, line in funcs:
                content += line + '\n'
            content += '\n} // namespace app::lua_bind\n'
            src_file.write_text(content)
            print('  Created %s (%d)' % (src_file.name, len(funcs)))

if __name__ == '__main__':
    main()
