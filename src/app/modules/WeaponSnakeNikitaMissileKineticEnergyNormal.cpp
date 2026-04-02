#include "types.h"

struct WeaponSnakeNikitaMissileKineticEnergyNormal;

namespace app::lua_bind {

// 7102164020 -- str s0,[x0,#0xa0]; ret
void WeaponSnakeNikitaMissileKineticEnergyNormal__set_rot_z_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* self, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0xa0) = val;
}

// 7102164030 -- ldr s0,[x0,#0xa0]; ret
f32 WeaponSnakeNikitaMissileKineticEnergyNormal__rot_z_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* self) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0xa0);
}

// 7102164040 -- and w8,w1,#0x1; strb w8,[x0,#0xa4]; ret
void WeaponSnakeNikitaMissileKineticEnergyNormal__set_enable_rot_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* self, bool val) {
    *reinterpret_cast<bool*>(reinterpret_cast<u8*>(self) + 0xa4) = val;
}

} // namespace app::lua_bind
