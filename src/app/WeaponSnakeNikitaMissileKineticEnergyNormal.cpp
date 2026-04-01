#include "types.h"

struct WeaponSnakeNikitaMissileKineticEnergyNormal;

namespace app::lua_bind {

// 7102164020 — store float to +0xa0
void WeaponSnakeNikitaMissileKineticEnergyNormal__set_rot_z_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* w, f32 v) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(w) + 0xa0) = v;
}

// 7102164030 — load float from +0xa0
f32 WeaponSnakeNikitaMissileKineticEnergyNormal__rot_z_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* w) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(w) + 0xa0);
}

// 7102164040 — bool store to +0xa4 (3 instructions: and+strb+ret)
void WeaponSnakeNikitaMissileKineticEnergyNormal__set_enable_rot_impl(WeaponSnakeNikitaMissileKineticEnergyNormal* w, u32 enable) {
    reinterpret_cast<u8*>(w)[0xa4] = enable & 1;
}

} // namespace app::lua_bind
