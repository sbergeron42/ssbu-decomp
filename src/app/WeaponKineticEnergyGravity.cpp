#include "types.h"
#include "app/WeaponKineticEnergyGravity.h"

using app::WeaponKineticEnergyGravity;

namespace app::lua_bind {

// 71021362f0 -- store float to +0x34
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* g, f32 v) {
    g->accel = v;
}

// 7102136310 -- load float from +0x38
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* g) {
    return g->limit_speed;
}

// 7102136320 -- store float to +0x38
void WeaponKineticEnergyGravity__set_limit_speed_impl(WeaponKineticEnergyGravity* g, f32 v) {
    g->limit_speed = v;
}

} // namespace app::lua_bind

