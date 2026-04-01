#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

struct WeaponKineticEnergyGravity;

namespace app::lua_bind {

// 71021362f0 — str s0,[x0,#0x34]; ret
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* self, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0x34) = val;
}

// 7102136300 — ldr q1,[x0,#0x10]; mov v1.s[1],v0.s[0]; str q1,[x0,#0x10]; ret
void WeaponKineticEnergyGravity__set_speed_impl(WeaponKineticEnergyGravity* self, f32 val) {
    v4sf* vec = reinterpret_cast<v4sf*>(reinterpret_cast<u8*>(self) + 0x10);
    v4sf tmp = *vec;
    tmp[1] = val;
    *vec = tmp;
}

// 7102136310 — ldr s0,[x0,#0x38]; ret
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* self) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0x38);
}

// 7102136320 — str s0,[x0,#0x38]; ret
void WeaponKineticEnergyGravity__set_limit_speed_impl(WeaponKineticEnergyGravity* self, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(self) + 0x38) = val;
}

} // namespace app::lua_bind
