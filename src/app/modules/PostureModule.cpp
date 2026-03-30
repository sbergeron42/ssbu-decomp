#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// All PostureModule dispatchers — accessor+0x38

// 710206aeb0 — set_pos_2d
void PostureModule__set_pos_2d_impl(BattleObjectModuleAccessor* accessor, void* pos) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x78 / 8])(module, pos);
}

// 710206aec0 — add_pos
void PostureModule__add_pos_impl(BattleObjectModuleAccessor* accessor, void* pos) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x80 / 8])(module, pos);
}

// 710206aed0 — add_pos_2d
void PostureModule__add_pos_2d_impl(BattleObjectModuleAccessor* accessor, void* pos) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x88 / 8])(module, pos);
}

// 710206aee0 — prev_pos
void* PostureModule__prev_pos_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*)>(vtable[0xa0 / 8])(module);
}

// 710206af00 — prev_pos_2d
void* PostureModule__prev_pos_2d_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*)>(vtable[0xa8 / 8])(module);
}

// 710206af10 — lr
f32 PostureModule__lr_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0xb0 / 8])(module);
}

// 710206af20 — set_lr
void PostureModule__set_lr_impl(BattleObjectModuleAccessor* accessor, f32 lr) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, f32)>(vtable[0xb8 / 8])(module, lr);
}

// 710206af30 — reverse_lr
void PostureModule__reverse_lr_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0xc0 / 8])(module);
}

// 710206af40 — init_rot
void PostureModule__init_rot_impl(BattleObjectModuleAccessor* accessor, void* rot) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0xc8 / 8])(module, rot);
}

} // namespace app::lua_bind
