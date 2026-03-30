#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 7102087720 — status_kind
s32 StatusModule__status_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x110 / 8])(module);
}

// 7102087730 — status_kind_next
s32 StatusModule__status_kind_next_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x118 / 8])(module);
}

// 7102087740 — set_status_kind_interrupt
void StatusModule__set_status_kind_interrupt_impl(BattleObjectModuleAccessor* accessor, s32 kind) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x120 / 8])(module, kind);
}

// 7102087750 — status_kind_interrupt
s32 StatusModule__status_kind_interrupt_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x128 / 8])(module);
}

// 7102087760 — is_changing
bool StatusModule__is_changing_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x130 / 8])(module);
}

// 7102087770 — prev_status_kind
s32 StatusModule__prev_status_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x138 / 8])(module);
}

// 71020877a0 — situation_kind
s32 StatusModule__situation_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x148 / 8])(module);
}

// 71020877b0 — prev_situation_kind
s32 StatusModule__prev_situation_kind_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->status_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x150 / 8])(module);
}

} // namespace app::lua_bind
