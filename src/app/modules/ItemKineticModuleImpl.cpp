#include "app/BattleObjectModuleAccessor.h"

typedef float v4sf __attribute__((vector_size(16)));

namespace app::lua_bind {

// 71020cc8d0 -- 5 instructions (branch: bounds check)
void ItemKineticModuleImpl__set_slope_type_impl(BattleObjectModuleAccessor* accessor, u32 slope_type) {
    if (slope_type <= 7) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(accessor->item_kinetic_module) + 0x9e8) = slope_type;
    }
}

// 71020cc900 -- 3 instructions (trivial getter)
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
// NOTE: NX Clang x8/x9 regalloc divergence -- uses x8+w9 vs our x9+w8
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

// 71020ccfd0 -- it_ai_type: stores type + two Vec3 structs via 64-bit copies
void ItemKineticModuleImpl__it_ai_type_impl(BattleObjectModuleAccessor* a, u32 type, u64* v1, u64* v2) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0xa04) = type;
    *reinterpret_cast<u64*>(p + 0xa28) = v1[1];
    *reinterpret_cast<u64*>(p + 0xa20) = v1[0];
    *reinterpret_cast<u64*>(p + 0xa18) = v2[1];
    *reinterpret_cast<u64*>(p + 0xa10) = v2[0];
}

// 71020cd030 -- it_ai_distance_factor: range check [0.0, 1.0], store to +0xA34
// NOTE: negated comparisons generate b.lt/b.hi (NaN-catching) matching NX Clang
void ItemKineticModuleImpl__it_ai_distance_factor_impl(BattleObjectModuleAccessor* a, f32 val) {
    if (!(val >= 0.0f)) return;
    if (!(val <= 1.0f)) return;
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa34) = val;
}

// 71020ccd70 -- two float stores + SIMD zero-zw vec copy at module+0x3d0
void ItemKineticModuleImpl__set_param_gemini_impl(BattleObjectModuleAccessor* a, f32 p1, f32 p2, v4sf* src) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<f32*>(m + 0xab4) = p1;
    *reinterpret_cast<f32*>(m + 0xab8) = p2;
    v4sf v = *src;
    v[2] = 0;
    v[3] = 0;
    *reinterpret_cast<v4sf*>(m + 0x3d0) = v;
}

} // namespace app::lua_bind

