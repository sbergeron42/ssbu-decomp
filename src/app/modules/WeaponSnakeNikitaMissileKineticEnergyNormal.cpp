#include "types.h"

struct WeaponSnakeNikitaMissileKineticEnergyNormal;

namespace app::lua_bind {

// 7102164020 — str s0,[x0,#0xa0]; ret
void WeaponSnakeNikitaMissileKineticEnergyNormal__set_rot_z_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* self, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0xa0) = val;
}

// 7102164030 — ldr s0,[x0,#0xa0]; ret
f32 WeaponSnakeNikitaMissileKineticEnergyNormal__rot_z_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* self) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0xa0);
}

} // namespace app::lua_bind
