#include "app/BattleObjectModuleAccessor.h"

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
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0x9dc) = val;
}
void ItemKineticModuleImpl__it_ai_dir_rot_mode_impl(BattleObjectModuleAccessor* a, u32 val) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xadc) = val;
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

} // namespace app::lua_bind
