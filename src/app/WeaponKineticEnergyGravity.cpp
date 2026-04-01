#include "types.h"

struct WeaponKineticEnergyGravity;

namespace app::lua_bind {

// 71021362f0 — store float to +0x34
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* g, f32 v) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(g) + 0x34) = v;
}

// 7102136300 — SIMD lane-insert: set y-component (lane 1) of vec4 at +0x10
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void WeaponKineticEnergyGravity__set_speed_impl(WeaponKineticEnergyGravity* g, f32 speed) {
    asm("ldr q1,[x0, #0x10]\n"
        "mov v1.S[1],v0.S[0]\n"
        "str q1,[x0, #0x10]\n"
        "ret\n");
}
#endif

// 7102136310 — load float from +0x38
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* g) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(g) + 0x38);
}

// 7102136320 — store float to +0x38
void WeaponKineticEnergyGravity__set_limit_speed_impl(WeaponKineticEnergyGravity* g, f32 v) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(g) + 0x38) = v;
}

} // namespace app::lua_bind
