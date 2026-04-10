#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

// FighterKineticEnergyMotion — fighter-specific "motion" kinetic energy
// driven by the character facing direction. Operates on self*.
// Layout recovered from the 13+ FighterKineticEnergyMotion__*_impl
// dispatchers at 0x7102120f60–0x7102121080 (ldr/str offsets).
struct FighterKineticEnergyMotion {
    // -- Base class region (0x00..0x83) — inherited KineticEnergy state --
    u8  pad_0x00[0x84];

    // +0x84 — ground transition state machine (reset to 2, 0xB == cliff)
    // [derived: set_ground_trans_impl at 0x7102121080 stores 2;
    //  is_cliff_ground_trans_impl at 0x7102121070 checks == 0xb]
    u32 ground_trans;

    // +0x88 — character facing direction (±1.0 for right/left)
    // [derived: set_chara_dir_impl at 0x7102120fb0 writes via fcmp + conditional flip;
    //  get_chara_dir_impl reads it; reverse_chara_dir_impl negates it]
    f32 chara_dir;

    // +0x8C — motion angle (radians)
    // [derived: set_angle_impl at 0x7102120f60 str s0,[x0,#0x8c];
    //  get_angle_impl at 0x7102121030 ldr s0,[x0,#0x8c]]
    f32 angle;

    // +0x90 — angle_whole (scratch copy of angle_whole_rad when mode==0)
    // [derived: set_angle_whole_impl at 0x7102120f70 writes only when mode==0;
    //  get_angle_whole_impl at 0x7102121040 ldr s0,[x0,#0x90]]
    f32 angle_whole;

    // +0x94 — angle_whole_rad (always the latest deg2rad-converted value)
    // [derived: set_angle_whole_impl at 0x7102120f70 always writes this]
    f32 angle_whole_rad;

    // +0x98 — angle_whole mode selector (0 = sync angle_whole, nonzero = leave untouched)
    // [derived: set_angle_whole_impl at 0x7102120f70 str w1,[x0,#0x98]]
    s32 angle_whole_mode;

    // +0x9C — speed multiplier (scalar)
    // [derived: set_speed_mul_impl at 0x7102120fa0 str s0,[x0,#0x9c];
    //  get_speed_mul_impl at 0x7102121060 ldr s0,[x0,#0x9c]]
    f32 speed_mul;

    // +0xA0 — 16-byte motion direction vector (v4sf)
    // [derived: reverse_chara_dir_impl at 0x7102120fe0 loads q0,[x0,#0xa0],
    //  negates lane 0, stores back. set_chara_dir_impl does the same conditionally.]
    u8  motion_vec[0x10];

    // +0xB0 — 16-byte secondary speed multiplier vector
    // [derived: set_speed_mul_2nd_impl at 0x7102121010 copies 16 bytes as two u64 stores
    //  at [x0,#0xb0] and [x0,#0xb8]]
    u8  speed_mul_2nd[0x10];

    // +0xC0 — update flag (bool-as-byte)
    // [derived: set_update_flag_impl at 0x7102121000 does and w8,w1,#1; strb w8,[x0,#0xc0]]
    u8  update_flag;
};

// deg2rad constant at original binary address (0x7104471000 + 0x6e0)
extern "C" f32 DAT_71044716e0 __attribute__((visibility("hidden")));

namespace app::lua_bind {

// 7102120f60 -- str s0,[x0,#0x8c]; ret
void FighterKineticEnergyMotion__set_angle_impl(FighterKineticEnergyMotion* ke, f32 val) {
    ke->angle = val;
}

// 7102120f70 -- 9 insns: deg2rad, store mode, store rad, cbz mode, store angle_whole
// [derived: adrp/ldr loads DAT_71044716e0 (deg2rad), fmul applies conversion,
//  stores to +0x98 (mode) and +0x94 (rad), conditional store to +0x90 (angle_whole)]
// NOTE: partial match (5/9) — NX Clang emits fmul with operand order `s0,s0,s1` (angle*const)
// while upstream Clang 8.0.0 emits `s0,s1,s0`. Also NX schedules str mode after fmul while
// upstream schedules it before. adrp/ldr reloc differs under flat-link verification.
void FighterKineticEnergyMotion__set_angle_whole_impl(FighterKineticEnergyMotion* ke, f32 angle, s32 mode) {
    f32 rad = angle * DAT_71044716e0;
    ke->angle_whole_mode = mode;
    ke->angle_whole_rad = rad;
    if (mode != 0) return;
    ke->angle_whole = rad;
}

// 7102120fa0 -- str s0,[x0,#0x9c]; ret
void FighterKineticEnergyMotion__set_speed_mul_impl(FighterKineticEnergyMotion* ke, f32 val) {
    ke->speed_mul = val;
}

// 7102120fb0 -- 9 insns: if new != old, store new and negate motion_vec[0]
// [derived: ldr/fcmp old vs new, skip-on-equal via forward branch, body stores new and flips motion_vec.x]
// Compiler reuses old dir register for negation (since v[0] == old by invariant).
// NOTE: partial match (5/9) — upstream Clang 8.0.0 writes fneg into a fresh register (s2)
// preserving s1, then mov-inserts s2 into v1[0]; NX Clang overwrites s1 in place. The
// selected SIMD register also differs (q1 vs q2). Semantics identical.
void FighterKineticEnergyMotion__set_chara_dir_impl(FighterKineticEnergyMotion* ke, f32 new_dir) {
    f32 old = ke->chara_dir;
    if (old != new_dir) {
        auto* v = reinterpret_cast<v4sf*>(ke->motion_vec);
        v4sf vec = *v;
        f32 neg_old = -old;
        ke->chara_dir = new_dir;
        vec[0] = neg_old;
        *v = vec;
    }
}

// 7102120fe0 -- reverse_chara_dir: negate vec[0] at +0xa0 and float at +0x88
void FighterKineticEnergyMotion__reverse_chara_dir_impl(FighterKineticEnergyMotion* ke) {
    auto* v = reinterpret_cast<v4sf*>(ke->motion_vec);
    (*v)[0] = -(*v)[0];
    ke->chara_dir = -ke->chara_dir;
}

// 7102121080 -- set_ground_trans: store 2 to +0x84
void FighterKineticEnergyMotion__set_ground_trans_impl(FighterKineticEnergyMotion* ke) {
    ke->ground_trans = 2;
}

// 7102121000 -- and w8,w1,#0x1; strb w8,[x0,#0xc0]; ret
void FighterKineticEnergyMotion__set_update_flag_impl(FighterKineticEnergyMotion* ke, bool val) {
    ke->update_flag = val & 1;
}

// 7102121010 -- set_speed_mul_2nd: copies 16 bytes from x1 to x0+0xb0
// ldr x8,[x1,#0x8]; str x8,[x0,#0xb8]; ldr x8,[x1]; str x8,[x0,#0xb0]; ret
void FighterKineticEnergyMotion__set_speed_mul_2nd_impl(FighterKineticEnergyMotion* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(ke->speed_mul_2nd);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 7102121030 -- ldr s0,[x0,#0x8c]; ret
f32 FighterKineticEnergyMotion__get_angle_impl(FighterKineticEnergyMotion* ke) {
    return ke->angle;
}

// 7102121040 -- ldr s0,[x0,#0x90]; ret
f32 FighterKineticEnergyMotion__get_angle_whole_impl(FighterKineticEnergyMotion* ke) {
    return ke->angle_whole;
}

// 7102121050 -- ldr s0,[x0,#0x88]; ret
f32 FighterKineticEnergyMotion__get_chara_dir_impl(FighterKineticEnergyMotion* ke) {
    return ke->chara_dir;
}

// 7102121060 -- ldr s0,[x0,#0x9c]; ret
f32 FighterKineticEnergyMotion__get_speed_mul_impl(FighterKineticEnergyMotion* ke) {
    return ke->speed_mul;
}

// 7102121070 -- ldr w8,[x0,#0x84]; cmp w8,#0xb; cset w0,eq; ret
bool FighterKineticEnergyMotion__is_cliff_ground_trans_impl(FighterKineticEnergyMotion* ke) {
    return ke->ground_trans == 0xb;
}

} // namespace app::lua_bind
