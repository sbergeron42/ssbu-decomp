#include "app/BattleObjectModuleAccessor.h"

// KineticModule uses the same accessor field as ItemKineticModule (+0x68)
// The field is a polymorphic KineticModule base — Item and Fighter variants share it

namespace app::lua_bind {

// 7102043990 — clear_speed_all
void KineticModule__clear_speed_all_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0x90 / 8])(module);
}

// 71020439f0 — get_sum_speed
void* KineticModule__get_sum_speed_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xc0 / 8])(module, out);
}

// 7102043a00 — get_sum_speed_x
void* KineticModule__get_sum_speed_x_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xc8 / 8])(module, out);
}

// 7102043a10 — get_sum_speed_y
void* KineticModule__get_sum_speed_y_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xd0 / 8])(module, out);
}

// 7102043a20 — get_sum_speed_length
void* KineticModule__get_sum_speed_length_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xd8 / 8])(module, out);
}

// 7102043a30 — get_sum_speed3f
void* KineticModule__get_sum_speed3f_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xe0 / 8])(module, out);
}

// 7102043a70 — mul_speed
void KineticModule__mul_speed_impl(BattleObjectModuleAccessor* accessor, void* speed, u64 p2) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*, u64)>(vtable[0xf8 / 8])(module, speed, p2);
}

// 7102043ab0 — change_kinetic
void KineticModule__change_kinetic_impl(BattleObjectModuleAccessor* accessor, s32 kind) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x118 / 8])(module, kind);
}

// 7102043ac0 — get_kinetic_type
s32 KineticModule__get_kinetic_type_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x120 / 8])(module);
}

// 7102043af0 — is_enable_energy
bool KineticModule__is_enable_energy_impl(BattleObjectModuleAccessor* accessor, s32 id) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*, s32)>(vtable[0x138 / 8])(module, id);
}

// 7102043b30 — add_speed
void KineticModule__add_speed_impl(BattleObjectModuleAccessor* accessor, void* speed) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x158 / 8])(module, speed);
}

// 7102043b40 — add_speed_outside
void KineticModule__add_speed_outside_impl(BattleObjectModuleAccessor* accessor, void* speed, u64 p2) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*, u64)>(vtable[0x160 / 8])(module, speed, p2);
}

} // namespace app::lua_bind
