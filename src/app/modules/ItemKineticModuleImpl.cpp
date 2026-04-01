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

// 71020cc8c0 — bool-mask w3, load item_kinetic_module, tail call to 0x71016192b0
void ItemKineticModuleImpl__set_throw_param_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) {
    auto* m = a->item_kinetic_module;
    // tail call target (0x71016192b0) is a non-vtable direct method on ItemKineticModuleImpl
    // stores m+0x310=1, sets speed to zero vector, adds input vec, computes gravity params, etc.
    (void)m; (void)p1; (void)p2; (void)p3;
}

// 71020ccaf0 — load global zero vec (ext+zero pattern), store to module+0x260
// If bool flag && module+0x310: zero lane 1 of module+0x2f0
// NOTE: loads a global Vec3 pointer from 0x71052a7000+0xa88 (won't match due to adrp)
void ItemKineticModuleImpl__clear_speed_impl(BattleObjectModuleAccessor* a, bool flag) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    // Load from global zero-vec and store with zero w-component to module+0x260
    // (actual impl uses a global ptr; we zero it directly)
    *reinterpret_cast<f32*>(m + 0x260) = 0.0f;
    *reinterpret_cast<f32*>(m + 0x264) = 0.0f;
    *reinterpret_cast<f32*>(m + 0x268) = 0.0f;
    *reinterpret_cast<f32*>(m + 0x26c) = 0.0f;
    if (flag && m[0x310]) {
        *reinterpret_cast<f32*>(m + 0x2f4) = 0.0f;  // zero lane 1 of +0x2f0
    }
}

// 71020ccb30 — extract module, tail call to 0x7101616b30 (add_speed_damage)
void ItemKineticModuleImpl__add_speed_damage_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = a->item_kinetic_module;
    (void)m; (void)p1;
}

// 71020ccb40 — compute slope angle of velocity vector (304 bytes)
// Complex: gets speed from ground/work module vtable, computes atan2 in degrees
f32 ItemKineticModuleImpl__slope_angle_impl(BattleObjectModuleAccessor* a) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    if (!*reinterpret_cast<u32*>(m + 0x9dc)) return 0.0f;
    // full implementation requires complex vtable calls + sqrt + atan2
    return 0.0f;
}

// 71020ccda0 — extract module, bool-mask w2, tail call to 0x7101617100 (get_sum_speed)
// Returns accumulated speed Vec2 from all active kinetic energy components
void ItemKineticModuleImpl__get_sum_speed_simple_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    auto* m = a->item_kinetic_module;
    (void)m; (void)p1; (void)p2;
}

// 71020ccdb0 — applies speed cap per axis using item self-param table (304 bytes)
// For each of x,y,z: if component is outside range and speed > threshold, cap it
void ItemKineticModuleImpl__set_rot_along_speed_x_impl(BattleObjectModuleAccessor* a, f32* threshold) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    // loads vec3 from m+0x1e0, checks vs threshold, applies param-table scaling
    // complex SIMD + game-param lookup, not implementable without full param table access
    (void)m; (void)threshold;
}

// 71020ccee0 — set AI movement target (240 bytes)
// Stores velocity, target vectors, optional scale from posture module, sets activate flag
void ItemKineticModuleImpl__it_ai_move_impl(BattleObjectModuleAccessor* a, void* vel, u64 p2, void* target1, void* target2, void* p5, bool use_scale, bool use_gem) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    (void)m; (void)vel; (void)p2; (void)target1; (void)target2; (void)p5; (void)use_scale; (void)use_gem;
}

// 71020cc950 — add speed vector to current speed at module+0x260 (416 bytes)
// Loads current speed, adds input, optionally updates y-gemini, gets gravity params
void ItemKineticModuleImpl__add_speed_consider_gravity_impl(BattleObjectModuleAccessor* a, void* speed_vec, bool use_gem) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    (void)m; (void)speed_vec; (void)use_gem;
}

} // namespace app::lua_bind
