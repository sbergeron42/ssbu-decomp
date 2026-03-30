#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// All vtable dispatchers — 4 instructions each, trivially matching

// 710208db50 — get_float
f32 WorkModule__get_float_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32)>(vtable[0x58 / 8])(module, index);
}

// 710208db80 — add_float
f32 WorkModule__add_float_impl(BattleObjectModuleAccessor* accessor, s32 index, f32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32, f32)>(vtable[0x78 / 8])(module, index, value);
}

// 710208dc20 — dec_int
void WorkModule__dec_int_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0xD0 / 8])(module, index);
}

// 710208dc30 — add_int
void WorkModule__add_int_impl(BattleObjectModuleAccessor* accessor, s32 index, s32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32)>(vtable[0xD8 / 8])(module, index, value);
}

} // namespace app::lua_bind
