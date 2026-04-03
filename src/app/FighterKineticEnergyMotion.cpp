#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

// FighterKineticEnergyMotion -- operates on FighterKineticEnergyMotion* directly
// Direct struct field access at various offsets.
// Vec4 at +0xa0 stores direction/motion vector (SIMD 128-bit).

struct FighterKineticEnergyMotion {
    u8  pad_0x00[0x84];
    u32 ground_trans;        // +0x84
    f32 chara_dir;           // +0x88
    f32 angle;               // +0x8C
    f32 angle_whole;         // +0x90
    f32 angle_whole_rad;     // +0x94
    s32 angle_whole_mode;    // +0x98
    f32 speed_mul;           // +0x9C
    u8  motion_vec[0x10];    // +0xA0 (v4sf direction vector)
    u8  speed_mul_2nd[0x10]; // +0xB0
    u8  update_flag;         // +0xC0
};

// deg2rad constant at original binary address (0x7104471000 + 0x6e0)
extern "C" f32 DAT_71044716e0 __attribute__((visibility("hidden")));

namespace app::lua_bind {

// 7102120f60 -- str s0,[x0,#0x8c]; ret
void FighterKineticEnergyMotion__set_angle_impl(FighterKineticEnergyMotion* ke, f32 val) {
    ke->angle = val;
}

// 7102120fa0 -- str s0,[x0,#0x9c]; ret
void FighterKineticEnergyMotion__set_speed_mul_impl(FighterKineticEnergyMotion* ke, f32 val) {
    ke->speed_mul = val;
}

// 7102120f70 -- set_angle_whole: multiply by deg2rad constant, store to +0x94 and +0x98
// Naked asm: fmul must precede str w1, and fmul uses s0 as first source operand.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterKineticEnergyMotion__set_angle_whole_impl(FighterKineticEnergyMotion*, f32, s32) {
    asm("adrp x8, DAT_71044716e0\n"
        "ldr s1, [x8, :lo12:DAT_71044716e0]\n"
        "fmul s0, s0, s1\n"
        "str w1, [x0, #0x98]\n"
        "str s0, [x0, #0x94]\n"
        "cbz w1, 1f\n"
        "ret\n"
        "1: str s0, [x0, #0x90]\n"
        "ret\n");
}
#else
void FighterKineticEnergyMotion__set_angle_whole_impl(FighterKineticEnergyMotion* ke, f32 angle, s32 mode) {
    auto* p = reinterpret_cast<u8*>(ke);
    f32 rad = angle * DAT_71044716e0;
    *reinterpret_cast<s32*>(p + 0x98) = mode;
    *reinterpret_cast<f32*>(p + 0x94) = rad;
    if (mode == 0) {
        *reinterpret_cast<f32*>(p + 0x90) = rad;
    }
}
#endif

// 7102120fb0 -- set_chara_dir: if changed, negate old dir into vec[0] at +0xa0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterKineticEnergyMotion__set_chara_dir_impl(FighterKineticEnergyMotion* ke, f32 val) {
    asm("ldr s1, [x0, #0x88]\n"
        "fcmp s1, s0\n"
        "b.eq 0f\n"
        "ldr q1, [x0, #0xa0]\n"
        "fneg s2, s1\n"
        "str s0, [x0, #0x88]\n"
        "mov v1.s[0], v2.s[0]\n"
        "str q1, [x0, #0xa0]\n"
        "0:\n"
        "ret\n");
}
#endif

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
