#include "types.h"
#include "app/WeaponKineticEnergyGravity.h"

using app::WeaponKineticEnergyGravity;

namespace app::lua_bind {

// 71021362f0 — str s0,[x0,#0x34]; ret
// [derived: writes accel scalar at +0x34 on the weapon gravity energy]
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* g, f32 v) {
    g->accel = v;
}

// 7102136310 — ldr s0,[x0,#0x38]; ret
// [derived: reads limit_speed scalar at +0x38]
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* g) {
    return g->limit_speed;
}

// 7102136320 — str s0,[x0,#0x38]; ret
// [derived: writes limit_speed scalar at +0x38]
void WeaponKineticEnergyGravity__set_limit_speed_impl(WeaponKineticEnergyGravity* g, f32 v) {
    g->limit_speed = v;
}

} // namespace app::lua_bind

