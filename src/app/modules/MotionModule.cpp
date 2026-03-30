#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// All MotionModule dispatchers — accessor+0x88

// 710205cb30 — change_motion (3 bool params, and w2-w4 #1)
void MotionModule__change_motion_impl(BattleObjectModuleAccessor* accessor, u64 hash, f32 rate, bool unk1, bool unk2, bool unk3) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64, f32, bool, bool, bool)>(vtable[0xe0 / 8])(module, hash, rate, unk1, unk2, unk3);
}

// 710205cb50 — change_motion_inherit_frame (2 bool params)
void MotionModule__change_motion_inherit_frame_impl(BattleObjectModuleAccessor* accessor, u64 hash, bool unk1, bool unk2) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64, bool, bool)>(vtable[0xe8 / 8])(module, hash, unk1, unk2);
}

// 710205cb70 — change_motion_inherit_frame_keep_rate
void MotionModule__change_motion_inherit_frame_keep_rate_impl(BattleObjectModuleAccessor* accessor, u64 hash) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64)>(vtable[0xf0 / 8])(module, hash);
}

// 710205cb80 — change_motion_force_inherit_frame
void MotionModule__change_motion_force_inherit_frame_impl(BattleObjectModuleAccessor* accessor, u64 hash) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64)>(vtable[0xf8 / 8])(module, hash);
}

// 710205cb90 — change_motion_kind
void MotionModule__change_motion_kind_impl(BattleObjectModuleAccessor* accessor, u64 hash) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64)>(vtable[0x100 / 8])(module, hash);
}

// 710205cba0 — add_motion_2nd (1 bool param, and w2 #1)
void MotionModule__add_motion_2nd_impl(BattleObjectModuleAccessor* accessor, u64 hash, bool unk1) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64, bool)>(vtable[0x108 / 8])(module, hash, unk1);
}

// 710205cbe0 — get_weight
f32 MotionModule__get_weight_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0x118 / 8])(module);
}

// 710205cc00 — is_blend
bool MotionModule__is_blend_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x128 / 8])(module);
}

// 710205cc10 — is_changing
bool MotionModule__is_changing_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x130 / 8])(module);
}

// 710205cc70 — frame
f32 MotionModule__frame_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0x160 / 8])(module);
}

// 710205ccd0 — end_frame
f32 MotionModule__end_frame_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0x180 / 8])(module);
}

// 710205cd90 — is_end
bool MotionModule__is_end_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->motion_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x1c8 / 8])(module);
}

} // namespace app::lua_bind
