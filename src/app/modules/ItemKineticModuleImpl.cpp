#include "app/BattleObjectModuleAccessor.h"

typedef float v4sf __attribute__((vector_size(16)));

namespace app::lua_bind {

// 71020cc8d0 — 5 instructions (branch: bounds check)
void ItemKineticModuleImpl__set_slope_type_impl(BattleObjectModuleAccessor* accessor, u32 slope_type) {
    if (slope_type <= 7) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(accessor->item_kinetic_module) + 0x9e8) = slope_type;
    }
}

// 71020cc900 — 3 instructions (trivial getter)
u32 ItemKineticModuleImpl__get_kinetic_flags_impl(BattleObjectModuleAccessor* accessor) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(accessor->item_kinetic_module) + 0x9d8);
}

// Field reads (3 instructions)
void* ItemKineticModuleImpl__get_motion_trans_rate_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa80;
}
void* ItemKineticModuleImpl__get_motion_trans_rate_2nd_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->item_kinetic_module) + 0xaa0;
}

// Field writes (3 instructions)
void ItemKineticModuleImpl__set_kinetic_flags_impl(BattleObjectModuleAccessor* a, u32 val) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0x9d8) = val;
}
void ItemKineticModuleImpl__set_interpolate_rate_impl(BattleObjectModuleAccessor* a, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa70) = val;
}
// NOTE: NX Clang x8/x9 regalloc divergence — uses x8+w9 vs our x9+w8
void ItemKineticModuleImpl__it_ai_dir_rot_mode_impl(BattleObjectModuleAccessor* a, u32 val) {
    auto* module = reinterpret_cast<u8*>(a->item_kinetic_module);
    module[0xa50] = val & 1;
}

// Read-modify-write (5 instructions: ldr+orr/bic+str)
void ItemKineticModuleImpl__on_kinetic_flag_impl(BattleObjectModuleAccessor* a, u32 flag) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0x9d8) |= flag;
}
void ItemKineticModuleImpl__off_kinetic_flag_impl(BattleObjectModuleAccessor* a, u32 flag) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0x9d8) &= ~flag;
}

// 71020ccfd0 — it_ai_type: stores type + two Vec3 structs via 64-bit copies
void ItemKineticModuleImpl__it_ai_type_impl(BattleObjectModuleAccessor* a, u32 type, u64* v1, u64* v2) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0xa04) = type;
    *reinterpret_cast<u64*>(p + 0xa28) = v1[1];
    *reinterpret_cast<u64*>(p + 0xa20) = v1[0];
    *reinterpret_cast<u64*>(p + 0xa18) = v2[1];
    *reinterpret_cast<u64*>(p + 0xa10) = v2[0];
}

// 71020cd030 — it_ai_distance_factor: range check [0.0, 1.0], store to +0xA34
// NOTE: negated comparisons generate b.lt/b.hi (NaN-catching) matching NX Clang
void ItemKineticModuleImpl__it_ai_distance_factor_impl(BattleObjectModuleAccessor* a, f32 val) {
    if (!(val >= 0.0f)) return;
    if (!(val <= 1.0f)) return;
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa34) = val;
}

// 71020ccc70 — SIMD: NX ext+mov+mov pattern for zero-w
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_motion_trans_rate_impl(BattleObjectModuleAccessor* a, void* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "ldr x8, [x0, #0x68]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0xa80]\n"
        "ret\n");
}
#endif

// 71020ccca0 — degrees to radians, store at module+0xa90
void ItemKineticModuleImpl__set_motion_trans_angle_impl(BattleObjectModuleAccessor* a, f32 angle) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa90) = angle * (3.14159265f / 180.0f);
}

// 71020cccc0 — radians to degrees from module+0xa90
f32 ItemKineticModuleImpl__get_motion_trans_angle_impl(BattleObjectModuleAccessor* a) {
    f32 val = *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa90);
    return val * 180.0f / 3.14159265f;
}

// 71020cccf0 — SIMD: NX ext+mov+mov pattern for zero-w
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_motion_trans_rate_2nd_impl(BattleObjectModuleAccessor* a, void* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "ldr x8, [x0, #0x68]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0xaa0]\n"
        "ret\n");
}
#endif

// 71020ccd20 — degrees to radians, store at module+0xab0
void ItemKineticModuleImpl__set_motion_trans_angle_2nd_impl(BattleObjectModuleAccessor* a, f32 angle) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xab0) = angle * (3.14159265f / 180.0f);
}

// 71020ccd40 — radians to degrees from module+0xab0
f32 ItemKineticModuleImpl__get_motion_trans_angle_2nd_impl(BattleObjectModuleAccessor* a) {
    f32 val = *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xab0);
    return val * 180.0f / 3.14159265f;
}

// 71020ccd70 — two float stores + SIMD zero-zw vec copy at module+0x3d0
void ItemKineticModuleImpl__set_param_gemini_impl(BattleObjectModuleAccessor* a, f32 p1, f32 p2, v4sf* src) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<f32*>(m + 0xab4) = p1;
    *reinterpret_cast<f32*>(m + 0xab8) = p2;
    v4sf v = *src;
    v[2] = 0;
    v[3] = 0;
    *reinterpret_cast<v4sf*>(m + 0x3d0) = v;
}

// 71020cd000 — clamp [0.0, 1.0] with fccmp pattern (NX divergence)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__it_ai_dir_factor_impl(BattleObjectModuleAccessor* a, f32 val) {
    asm("fmov s1, #1.0\n"
        "fcmp s0, s1\n"
        "fcsel s2, s1, s0, gt\n"
        "fcmp s0, #0.0\n"
        "fmov s3, wzr\n"
        "fcsel s2, s3, s2, mi\n"
        "fcmp s0, s1\n"
        "fccmp s0, s3, #0x8, le\n"
        "ldr x8, [x0, #0x68]\n"
        "fcsel s0, s2, s0, mi\n"
        "str s0, [x8, #0xa30]\n"
        "ret\n");
}
#endif

// 71020cd060 — SIMD: NX ext+mov+mov pattern for zero-w
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__it_base_rot_impl(BattleObjectModuleAccessor* a, void* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "ldr x8, [x0, #0x68]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0x9f0]\n"
        "ret\n");
}
#endif

// 71020ccee0 — it_ai_move: NX prologue (sub;str x23;stp x22,x21;stp x20,x19;stp x29,x30),
//   8 args: accessor,vec2*,x19,x20,vec2*,x21,bool_w6,w22
//   Conditionally calls vtable[0xb0] on posture module, scales vec2 components,
//   optionally updates 2nd-motion vec, builds SIMD vec via ext+ext, stores to kinetic fields
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__it_ai_move_impl(BattleObjectModuleAccessor* a,
    void* p1, void* p2, void* p3, void* p4, void* p5, u32 flag1, u32 flag2) {
    asm(
        "sub sp,sp,#0x60\n"
        "str x23,[sp, #0x20]\n"
        "stp x22,x21,[sp, #0x30]\n"
        "stp x20,x19,[sp, #0x40]\n"
        "stp x29,x30,[sp, #0x50]\n"
        "add x29,sp,#0x50\n"
        "ldr q2,[x1]\n"
        "ldr q1,[x4]\n"
        "mov w22,w7\n"
        "ldr x23,[x0, #0x68]\n"
        "mov x21,x5\n"
        "mov x20,x3\n"
        "mov x19,x2\n"
        "tbz w6,#0x0,1f\n"
        "ldr x8,[x23, #0x8]\n"
        "ldr x0,[x8, #0x38]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0xb0]\n"
        "stp q2,q1,[sp]\n"
        "blr x8\n"
        "ldr q2,[sp]\n"
        "fmul s1,s0,v2.S[0]\n"
        "mov v2.S[0],v1.S[0]\n"
        "ldr q1,[sp, #0x10]\n"
        "fmul s0,s0,v1.S[0]\n"
        "mov v1.S[0],v0.S[0]\n"
        "1:\n"
        "tbz w22,#0x0,2f\n"
        "ldrb w8,[x23, #0x310]\n"
        "cbz w8,2f\n"
        "ldr q0,[x23, #0x2f0]\n"
        "mov v0.S[1],v2.S[1]\n"
        "str q0,[x23, #0x2f0]\n"
        "fmov s0,wzr\n"
        "mov v2.S[1],v0.S[0]\n"
        "2:\n"
        "movi v0.2D,#0x0\n"
        "ext v0.16B,v0.16B,v2.16B,#0x8\n"
        "ext v0.16B,v0.16B,v0.16B,#0x8\n"
        "str q1,[x23, #0x400]\n"
        "str q0,[x23, #0x3d0]\n"
        "ldr x8,[x21, #0x8]\n"
        "str x8,[x23, #0x428]\n"
        "ldr x8,[x21]\n"
        "str x8,[x23, #0x420]\n"
        "ldr x8,[x20, #0x8]\n"
        "str x8,[x23, #0x418]\n"
        "ldr x8,[x20]\n"
        "str x8,[x23, #0x410]\n"
        "ldr x8,[x19, #0x8]\n"
        "str x8,[x23, #0x438]\n"
        "ldr x8,[x19]\n"
        "str x8,[x23, #0x430]\n"
        "mov w8,#0x1\n"
        "strb w8,[x23, #0x3f0]\n"
        "ldr x23,[sp, #0x20]\n"
        "ldp x29,x30,[sp, #0x50]\n"
        "ldp x20,x19,[sp, #0x40]\n"
        "ldp x22,x21,[sp, #0x30]\n"
        "add sp,sp,#0x60\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
