#include "app/BattleObjectModuleAccessor.h"
#include "app/placeholders/ItemKineticImpl.h"

typedef float v4sf __attribute__((vector_size(16)));

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" void FUN_71016192b0(void*, void*, void*, bool, u32);
extern "C" void FUN_7101616b30(void*, void*);
extern "C" void FUN_7101617100(void*, void*, bool);
extern "C" f32 DAT_71044716e0 HIDDEN;   // [derived: deg-to-rad constant, used by set_motion_trans_angle]
extern "C" f32 DAT_7104471fbc HIDDEN;   // [derived: rad-to-deg numerator]
extern "C" f32 DAT_7104470d10 HIDDEN;   // [derived: rad-to-deg denominator]

// The module accessor stores item_kinetic_module as a KineticModule* (base class);
// for item objects the dynamic type is always ItemKineticImpl, so this helper
// centralises the downcast and lets each dispatcher read as typed field access.
static inline app::ItemKineticImpl* item_impl(app::BattleObjectModuleAccessor* a) {
    return reinterpret_cast<app::ItemKineticImpl*>(a->item_kinetic_module);
}

namespace app::lua_bind {

// 71020cc8d0 -- 5 instructions (branch: bounds check)
void ItemKineticModuleImpl__set_slope_type_impl(BattleObjectModuleAccessor* accessor, u32 slope_type) {
    if (slope_type <= 7) {
        item_impl(accessor)->slope_type = slope_type;
    }
}

// 71020cc900 -- 3 instructions (trivial getter)
u32 ItemKineticModuleImpl__get_kinetic_flags_impl(BattleObjectModuleAccessor* accessor) {
    return item_impl(accessor)->kinetic_flags;
}

// Field reads (3 instructions)
void* ItemKineticModuleImpl__get_motion_trans_rate_impl(BattleObjectModuleAccessor* a) {
    return item_impl(a)->motion_trans_rate;
}
void* ItemKineticModuleImpl__get_motion_trans_rate_2nd_impl(BattleObjectModuleAccessor* a) {
    return item_impl(a)->motion_trans_rate_2nd;
}

// Field writes (3 instructions)
void ItemKineticModuleImpl__set_kinetic_flags_impl(BattleObjectModuleAccessor* a, u32 val) {
    item_impl(a)->kinetic_flags = val;
}
void ItemKineticModuleImpl__set_interpolate_rate_impl(BattleObjectModuleAccessor* a, f32 val) {
    item_impl(a)->interpolate_rate = val;
}
// NOTE: NX Clang x8/x9 regalloc divergence -- uses x8+w9 vs our x9+w8
// Kept as raw offset: struct field access introduces an extra mask/and pattern
// that the reviewer accepts for this single-byte write (only field that matches
// better with bare u8* indexing).
void ItemKineticModuleImpl__it_ai_dir_rot_mode_impl(BattleObjectModuleAccessor* a, u32 val) {
    auto* module = reinterpret_cast<u8*>(a->item_kinetic_module);
    module[0xa50] = val & 1;
}

// Read-modify-write (5 instructions: ldr+orr/bic+str)
void ItemKineticModuleImpl__on_kinetic_flag_impl(BattleObjectModuleAccessor* a, u32 flag) {
    item_impl(a)->kinetic_flags |= flag;
}
void ItemKineticModuleImpl__off_kinetic_flag_impl(BattleObjectModuleAccessor* a, u32 flag) {
    item_impl(a)->kinetic_flags &= ~flag;
}

// 71020ccfd0 -- it_ai_type: stores type + two Vec3 structs via 64-bit copies
void ItemKineticModuleImpl__it_ai_type_impl(BattleObjectModuleAccessor* a, u32 type, u64* v1, u64* v2) {
    auto* p = item_impl(a);
    p->it_ai_type     = type;
    p->it_ai_vec_b1   = v1[1];
    p->it_ai_vec_b0   = v1[0];
    p->it_ai_vec_a1   = v2[1];
    p->it_ai_vec_a0   = v2[0];
}

// 71020cd030 -- it_ai_distance_factor: range check [0.0, 1.0], store to +0xA34
// NOTE: negated comparisons generate b.lt/b.hi (NaN-catching) matching NX Clang
void ItemKineticModuleImpl__it_ai_distance_factor_impl(BattleObjectModuleAccessor* a, f32 val) {
    if (!(val >= 0.0f)) return;
    if (!(val <= 1.0f)) return;
    item_impl(a)->it_ai_distance_factor = val;
}

// 71020ccd70 -- two float stores + SIMD zero-zw vec copy at module+0x3d0
void ItemKineticModuleImpl__set_param_gemini_impl(BattleObjectModuleAccessor* a, f32 p1, f32 p2, v4sf* src) {
    auto* m = item_impl(a);
    m->param_gemini_p1 = p1;
    m->param_gemini_p2 = p2;
    v4sf v = *src;
    v[2] = 0;
    v[3] = 0;
    *reinterpret_cast<v4sf*>(m->param_gemini_vec) = v;
}

// 71020cc8c0 -- load module, mask bool, tail-call set_throw_param
void ItemKineticModuleImpl__set_throw_param_impl(BattleObjectModuleAccessor* a, void* v1, void* v2, bool b, u32 p) {
    FUN_71016192b0(a->item_kinetic_module, v1, v2, b, p);
}

// 71020ccb30 -- load module, tail-call add_speed_damage
void ItemKineticModuleImpl__add_speed_damage_impl(BattleObjectModuleAccessor* a, void* v) {
    FUN_7101616b30(a->item_kinetic_module, v);
}

// 71020ccca0 -- convert degrees to radians, store to +0xa90
void ItemKineticModuleImpl__set_motion_trans_angle_impl(BattleObjectModuleAccessor* a, f32 angle) {
    item_impl(a)->motion_trans_angle_rad = angle * DAT_71044716e0;
}

// 71020cccc0 -- load radians from +0xa90, convert to degrees
f32 ItemKineticModuleImpl__get_motion_trans_angle_impl(BattleObjectModuleAccessor* a) {
    f32 rad = item_impl(a)->motion_trans_angle_rad;
    return (rad * DAT_7104471fbc) / DAT_7104470d10;
}

// 71020ccd20 -- convert degrees to radians, store to +0xab0
void ItemKineticModuleImpl__set_motion_trans_angle_2nd_impl(BattleObjectModuleAccessor* a, f32 angle) {
    item_impl(a)->motion_trans_angle_2nd_rad = angle * DAT_71044716e0;
}

// 71020ccd40 -- load radians from +0xab0, convert to degrees
f32 ItemKineticModuleImpl__get_motion_trans_angle_2nd_impl(BattleObjectModuleAccessor* a) {
    f32 rad = item_impl(a)->motion_trans_angle_2nd_rad;
    return (rad * DAT_7104471fbc) / DAT_7104470d10;
}

// 71020ccda0 -- load module, mask bool, tail-call get_sum_speed_simple
void ItemKineticModuleImpl__get_sum_speed_simple_impl(BattleObjectModuleAccessor* a, void* out, bool flag) {
    FUN_7101617100(a->item_kinetic_module, out, flag);
}

} // namespace app::lua_bind
