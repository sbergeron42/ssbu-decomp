#!/usr/bin/env python3
"""
Auto-generate C++ vtable dispatch functions by reading instruction bytes
from the original ELF. Handles 4-insn tail-call, 5-insn bool-masking,
and 8-insn framed-call patterns.
"""

import csv
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_ELF = PROJECT_ROOT / "data" / "main.elf"
ELF_BASE = 0x7100000000

# Module accessor offsets → module names and macro names
MODULE_OFFSETS = {
    0x38: ("PostureModule", "POSTURE_MODULE"),
    0x40: ("StatusModule", "STATUS_MODULE"),
    0x48: ("ControlModule", "CONTROL_MODULE"),
    0x50: ("WorkModule", "WORK_MODULE"),
    0x58: ("GroundModule", "GM"),
    0x60: ("CameraModule", "CAMERA_MODULE"),
    0x68: ("KineticModule", "KINETIC_MODULE"),
    0x70: ("JostleModule", "JOSTLE_MODULE"),
    0x78: ("TeamModule", "TEAM_MODULE"),
    0x80: ("SlowModule", "SLOW_MODULE"),
    0x88: ("MotionModule", "MOTION_MODULE"),
    0x90: ("StopModule", "STOP_MODULE"),
    0x98: ("SearchModule", "SEARCH_MODULE"),
    0xA0: ("AttackModule", "ATTACK_MODULE"),
    0xA8: ("DamageModule", "DAMAGE_MODULE"),
    0xB0: ("ShakeModule", "SHAKE_MODULE"),
    0xB8: ("TurnModule", "TURN_MODULE"),
    0xC0: ("AreaModule", "AREA_MODULE"),
    0xC8: ("HitModule", "HIT_MODULE"),
    0xD0: ("LinkModule", "LM"),
    0xD8: ("ShadowModule", "SHADOW_MODULE"),
    0xE0: ("CancelModule", "CANCEL_MODULE"),
    0xE8: ("ModelModule", "MODEL_MODULE"),
    0xF0: ("PhysicsModule", "PHYSICS_MODULE"),
    0xF8: ("ShieldModule", "SHIELD_MODULE"),
    0x100: ("GrabModule", "GRAB_MODULE"),
    0x108: ("CaptureModule", "CAPTURE_MODULE"),
    0x110: ("ItemModule", "ITEM_MODULE"),
    0x118: ("ColorBlendModule", "COLOR_BLEND_MODULE"),
    0x120: ("ComboModule", "COMBO_MODULE"),
    0x128: ("ReflectorModule", "REFLECTOR_MODULE"),
    0x130: ("ReflectModule", "REFLECT_MODULE"),
    0x138: ("AbsorberModule", "ABSORBER_MODULE"),
    0x140: ("EffectModule", "EFFECT_MODULE"),
    0x148: ("SoundModule", "SOUND_MODULE"),
    0x150: ("VisibilityModule", "VISIBILITY_MODULE"),
    0x158: ("InkPaintModule", "INK_PAINT_MODULE"),
    0x160: ("MotionAnimcmdModule", "MOTION_ANIMCMD_MODULE"),
    0x188: ("ArticleModule", "ARTICLE_MODULE"),
}


def load_elf_segments(path):
    segments = []
    with open(path, 'rb') as f:
        f.seek(0x20)
        phoff = struct.unpack('<Q', f.read(8))[0]
        f.seek(0x36)
        phentsize = struct.unpack('<H', f.read(2))[0]
        phnum = struct.unpack('<H', f.read(2))[0]
        for i in range(phnum):
            f.seek(phoff + i * phentsize)
            p_type = struct.unpack('<I', f.read(4))[0]
            f.read(4)
            p_offset = struct.unpack('<Q', f.read(8))[0]
            p_vaddr = struct.unpack('<Q', f.read(8))[0]
            f.read(8)
            p_filesz = struct.unpack('<Q', f.read(8))[0]
            if p_type == 1:
                segments.append((p_vaddr, p_offset, p_filesz))
    return segments


def read_bytes(f, segments, vaddr, size):
    for sv, so, sf in segments:
        if sv <= vaddr < sv + sf:
            f.seek(so + (vaddr - sv))
            return f.read(size)
    return None


def decode_ldr_imm(insn):
    """Decode LDR Xt, [Xn, #imm] — returns (Rt, Rn, offset_bytes) or None."""
    if (insn & 0xFFC00000) == 0xF9400000:  # LDR 64-bit unsigned offset
        imm12 = (insn >> 10) & 0xFFF
        rn = (insn >> 5) & 0x1F
        rt = insn & 0x1F
        return (rt, rn, imm12 * 8)
    return None


def decode_br(insn):
    """Decode BR Xn — returns Rn or None."""
    if (insn & 0xFFFFFC1F) == 0xD61F0000:
        return (insn >> 5) & 0x1F
    return None


def decode_blr(insn):
    """Decode BLR Xn — returns Rn or None."""
    if (insn & 0xFFFFFC1F) == 0xD63F0000:
        return (insn >> 5) & 0x1F
    return None


def decode_and_bool(insn):
    """Decode AND Wd, Wn, #1 — returns (Rd, Rn) or None."""
    # AND (immediate) 32-bit: 0x12000000 | immr/imms encoding for #1
    if (insn & 0xFFFFFC00) == 0x12000000:
        rd = insn & 0x1F
        rn = (insn >> 5) & 0x1F
        return (rd, rn)
    return None


def is_stp_frame_push(insn):
    """Check for STP x29, x30, [sp, #-0x10]!"""
    return insn == 0xA9BF7BFD


def is_mov_fp(insn):
    """Check for MOV x29, sp"""
    return insn == 0x910003FD


def is_ldp_frame_pop(insn):
    """Check for LDP x29, x30, [sp], #0x10"""
    return insn == 0xA8C17BFD


def is_ret(insn):
    """Check for RET"""
    return insn == 0xD65F03C0


def guess_return_type(func_name):
    """Guess return type from function name."""
    short = func_name.split('__')[1] if '__' in func_name else func_name
    if short.startswith('is_') or short.startswith('can_') or short.startswith('chk_'):
        return 'bool'
    if short.startswith('get_') and any(w in short for w in
            ['pos', 'speed', 'normal', 'scale', 'rotation', 'offset', 'movement']):
        return 'void*'
    if short.startswith('get_') and any(w in short for w in
            ['kind', 'flag', 'count', 'num', 'id', 'no', 'type', 'shape']):
        return 'u32'
    if short.startswith('get_') and any(w in short for w in
            ['radius', 'offset_x', 'offset_y', 'width', 'z']):
        return 'f32'
    if short.startswith('set_') or short.startswith('clear_') or \
       short.startswith('entry_') or short.startswith('leave_') or \
       short.startswith('detach_') or short.startswith('attach_') or \
       short.startswith('update_') or short.startswith('correct_') or \
       short.startswith('modify_') or short.startswith('select_') or \
       short.startswith('reentry_') or short.startswith('pass_') or \
       short.startswith('ignore_') or short.startswith('adjust_') or \
       short.startswith('reset_') or short.startswith('enable_') or \
       short.startswith('unable_') or short.startswith('add_'):
        return 'void'
    if short.startswith('get_'):
        return 'void*'
    return 'void*'


def analyze_function(insns, func_name):
    """Analyze instructions and return C++ code template info."""
    n = len(insns)

    # Pattern 1: 4-insn tail call
    if n == 4:
        ldr0 = decode_ldr_imm(insns[0])
        ldr1 = decode_ldr_imm(insns[1])
        ldr2 = decode_ldr_imm(insns[2])
        br = decode_br(insns[3])
        if ldr0 and ldr1 and ldr2 and br is not None:
            mod_off = ldr0[2]
            vt_off = ldr2[2]
            method_reg = br
            num_params = method_reg - 1  # x0=module, x1..x(N-1)=params
            return {
                'type': 'tail_call',
                'mod_offset': mod_off,
                'vt_offset': vt_off,
                'num_params': num_params,
                'bool_params': [],
            }

    # Pattern 2: 5-insn tail call with bool masking
    if n == 5:
        ldr0 = decode_ldr_imm(insns[0])
        ldr1 = decode_ldr_imm(insns[1])
        ldr2 = decode_ldr_imm(insns[2])
        and_b = decode_and_bool(insns[3])
        br = decode_br(insns[4])
        if ldr0 and ldr1 and ldr2 and and_b and br is not None:
            mod_off = ldr0[2]
            vt_off = ldr2[2]
            method_reg = br
            bool_param = and_b[0]  # which register has the bool
            num_params = method_reg - 1
            return {
                'type': 'tail_call',
                'mod_offset': mod_off,
                'vt_offset': vt_off,
                'num_params': num_params,
                'bool_params': [bool_param],
            }

    # Pattern 3: 8-insn framed call
    if n == 8:
        if is_stp_frame_push(insns[0]) and is_mov_fp(insns[1]):
            ldr0 = decode_ldr_imm(insns[2])
            ldr1 = decode_ldr_imm(insns[3])
            ldr2 = decode_ldr_imm(insns[4])
            blr = decode_blr(insns[5])
            if ldr0 and ldr1 and ldr2 and blr is not None and \
               is_ldp_frame_pop(insns[6]) and is_ret(insns[7]):
                mod_off = ldr0[2]
                vt_off = ldr2[2]
                return {
                    'type': 'framed_call',
                    'mod_offset': mod_off,
                    'vt_offset': vt_off,
                    'num_params': 0,  # can't determine from 8-insn pattern
                    'bool_params': [],
                }

    return None


def generate_cpp(func_name, info, macro_name):
    """Generate a single C++ function line using module macro style."""
    vt_off = info['vt_offset']
    num_params = info['num_params']
    bool_params = info['bool_params']

    ret_type = guess_return_type(func_name)
    ret = 'return ' if ret_type != 'void' else ''

    # Build parameter list
    params = ['BattleObjectModuleAccessor* a']
    args = ['m']
    cast_params = ['void*']

    for i in range(num_params):
        reg = i + 1  # x1, x2, etc.
        if reg in bool_params:
            params.append(f'bool p{i+1}')
            cast_params.append('bool')
        else:
            params.append(f'u64 p{i+1}')
            cast_params.append('u64')
        args.append(f'p{i+1}')

    params_str = ','.join(params)
    args_str = ','.join(args)
    cast_params_str = ','.join(cast_params)
    cast_ret = ret_type if ret_type != 'void' else 'void'

    return f'{ret_type} {func_name}({params_str}) {{ auto* m={macro_name}(a); {ret}reinterpret_cast<{cast_ret}(*)({cast_params_str})>(VT(m)[{vt_off:#x}/8])({args_str}); }}'


def main():
    if len(sys.argv) < 2:
        print("Usage: gen_from_elf.py ModuleName [--dry-run]")
        sys.exit(1)

    target_module = sys.argv[1]
    dry_run = '--dry-run' in sys.argv

    # Load ELF
    segments = load_elf_segments(ORIGINAL_ELF)

    # Find target functions
    targets = []
    with open(PROJECT_ROOT / 'data' / 'functions.csv') as f:
        for row in csv.reader(f):
            if row[1] != 'U':
                continue
            name = row[3]
            if not name.startswith(target_module + '__'):
                continue
            size = int(row[2])
            if size > 32:
                continue
            addr = int(row[0], 16)
            targets.append((addr, name, size))

    if not targets:
        print(f"No U-status functions found for {target_module}")
        return

    targets.sort(key=lambda t: t[0])
    print(f"Found {len(targets)} functions for {target_module}")

    generated = []
    failed = []

    with open(ORIGINAL_ELF, 'rb') as f:
        for addr, name, csv_size in targets:
            vaddr = addr - ELF_BASE if addr >= ELF_BASE else addr
            # Read up to 32 bytes (8 instructions max)
            raw = read_bytes(f, segments, vaddr, 32)
            if not raw:
                failed.append((name, "couldn't read bytes"))
                continue

            # Decode instructions (read until ret or br)
            insns = []
            for i in range(0, 32, 4):
                insn = struct.unpack('<I', raw[i:i+4])[0]
                insns.append(insn)
                if is_ret(insn) or decode_br(insn) is not None:
                    break

            info = analyze_function(insns, name)
            if info is None:
                failed.append((name, f"{len(insns)} insns, unknown pattern"))
                continue

            # Find macro name for this module offset
            mod_off = info['mod_offset']
            if mod_off in MODULE_OFFSETS:
                _, macro = MODULE_OFFSETS[mod_off]
            else:
                macro = f'MOD_{mod_off:#x}'

            cpp = generate_cpp(name, info, macro)
            generated.append(cpp)

    print(f"Generated: {len(generated)}, Failed: {len(failed)}")
    print()

    if failed:
        print("Failed functions:")
        for name, reason in failed:
            print(f"  {name}: {reason}")
        print()

    if generated:
        if dry_run:
            print("Generated code:")
            for line in generated:
                print(line)
        else:
            for line in generated:
                print(line)


if __name__ == '__main__':
    main()
