#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 710200b6f0 — add_damage
void DamageModule__add_damage_impl(BattleObjectModuleAccessor* accessor, f32 damage) {
    auto* module = accessor->damage_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, f32)>(vtable[0xC0 / 8])(module, damage);
}

// 710200b700 — damage (get current damage)
f32 DamageModule__damage_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->damage_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0xC8 / 8])(module);
}

// 710200b710 — reaction
f32 DamageModule__reaction_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->damage_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0xD0 / 8])(module);
}

// 710200b720 — power_max
f32 DamageModule__power_max_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->damage_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0xD8 / 8])(module);
}

} // namespace app::lua_bind
