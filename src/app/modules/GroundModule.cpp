#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// All GroundModule dispatchers — accessor+0x58

// 7102029e80 — detach
void GroundModule__detach_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* module = accessor->ground_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, u64)>(vtable[0x3e8 / 8])(module, p1);
}

// 710202a070 — center_pos
void* GroundModule__center_pos_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->ground_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*)>(vtable[0x5a0 / 8])(module);
}

// 7102029bb0 — can_entry_cliff
bool GroundModule__can_entry_cliff_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->ground_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x260 / 8])(module);
}

// 7102029e70 — get_line_movement_speed
void* GroundModule__get_line_movement_speed_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->ground_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0x3d0 / 8])(module, out);
}

} // namespace app::lua_bind
