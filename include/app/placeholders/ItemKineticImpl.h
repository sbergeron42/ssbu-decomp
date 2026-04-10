#pragma once
#include "types.h"

namespace app {

// ItemKineticImpl — concrete KineticModule subclass used by all Items.
// Accessed via BattleObjectModuleAccessor::item_kinetic_module for item objects.
// Partial layout recovered from lua_bind::ItemKineticModuleImpl__*_impl dispatchers.
// Unknown regions are preserved as padding so the struct remains a drop-in
// replacement for raw u8* offset access.
struct ItemKineticImpl {
    // -- Head (0x000..0x3CF) — unknown (kinetic base class + energy slots) --
    u8 _unk_0x000[0x3d0];

    // +0x3d0 — 16-byte gemini parameter vector
    // [derived: ItemKineticModuleImpl__set_param_gemini_impl at 0x71020ccd70
    //  writes q-sized value with zeroed z/w components]
    u8 param_gemini_vec[0x10];

    // -- Mid padding --
    u8 _unk_0x3e0[0x9d8 - 0x3e0];

    // +0x9D8 — kinetic flag bitset
    // [derived: ItemKineticModuleImpl__get_kinetic_flags_impl / set_/on_/off_kinetic_flag_impl
    //  read-modify-write 32-bit word at this offset]
    u32 kinetic_flags;

    u8 _unk_0x9dc[0x9e8 - 0x9dc];

    // +0x9E8 — slope type enum (clamped to <= 7)
    // [derived: ItemKineticModuleImpl__set_slope_type_impl at 0x71020cc8d0 writes u32
    //  only when slope_type <= 7]
    u32 slope_type;

    u8 _unk_0x9ec[0xa04 - 0x9ec];

    // +0xA04 — it_ai type selector
    // [derived: ItemKineticModuleImpl__it_ai_type_impl writes u32 before the two Vec3 copies]
    u32 it_ai_type;

    u8 _unk_0xa08[0xa10 - 0xa08];

    // +0xA10..+0xA2F — two Vec3 structs written together by it_ai_type_impl
    // [derived: 4 x u64 stores at +0xA10,+0xA18,+0xA20,+0xA28 from two source pointers]
    u64 it_ai_vec_b0;    // +0xA10 [v2 low half]
    u64 it_ai_vec_b1;    // +0xA18 [v2 high half]
    u64 it_ai_vec_a0;    // +0xA20 [v1 low half]
    u64 it_ai_vec_a1;    // +0xA28 [v1 high half]

    u8 _unk_0xa30[0xa34 - 0xa30];

    // +0xA34 — distance factor in [0.0, 1.0]
    // [derived: ItemKineticModuleImpl__it_ai_distance_factor_impl at 0x71020cd030
    //  stores only when 0 <= val <= 1]
    f32 it_ai_distance_factor;

    u8 _unk_0xa38[0xa50 - 0xa38];

    // +0xA50 — dir rotation mode (bool-as-byte)
    // [derived: ItemKineticModuleImpl__it_ai_dir_rot_mode_impl writes `val & 1`]
    u8 it_ai_dir_rot_mode;

    u8 _unk_0xa51[0xa70 - 0xa51];

    // +0xA70 — interpolate rate (float)
    // [derived: ItemKineticModuleImpl__set_interpolate_rate_impl stores s0]
    f32 interpolate_rate;

    u8 _unk_0xa74[0xa80 - 0xa74];

    // +0xA80 — 16-byte motion_trans_rate vector
    // [derived: ItemKineticModuleImpl__get_motion_trans_rate_impl returns &this+0xa80]
    u8 motion_trans_rate[0x10];

    // +0xA90 — motion_trans_angle in radians
    // [derived: ItemKineticModuleImpl__set_motion_trans_angle_impl writes angle*deg2rad,
    //  get_motion_trans_angle_impl reads and converts back to degrees]
    f32 motion_trans_angle_rad;

    u8 _unk_0xa94[0xaa0 - 0xa94];

    // +0xAA0 — 16-byte motion_trans_rate_2nd vector
    // [derived: ItemKineticModuleImpl__get_motion_trans_rate_2nd_impl returns &this+0xaa0]
    u8 motion_trans_rate_2nd[0x10];

    // +0xAB0 — motion_trans_angle_2nd in radians
    // [derived: ItemKineticModuleImpl__set_motion_trans_angle_2nd_impl writes angle*deg2rad]
    f32 motion_trans_angle_2nd_rad;

    // +0xAB4, +0xAB8 — gemini scalar params
    // [derived: ItemKineticModuleImpl__set_param_gemini_impl at 0x71020ccd70 stores two
    //  scalar floats before writing the gemini vec at +0x3d0]
    f32 param_gemini_p1;   // +0xAB4
    f32 param_gemini_p2;   // +0xAB8
};

} // namespace app
