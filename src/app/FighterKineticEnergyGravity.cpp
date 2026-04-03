#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

// FighterKineticEnergyGravity -- operates on FighterKineticEnergyGravity* directly
// Simple field getters/setters at various offsets.
// Speed vector at +0x10 is a Vec4 (SIMD 128-bit), Y component at index 1.

struct FighterKineticEnergyGravity {
    u8  pad_0x00[0x10];
    u8  speed[0x10];             // +0x10 (v4sf, Y component at index 1)
    u8  pad_0x20[0x18];
    f32 accel;                   // +0x38
    f32 stable_speed;            // +0x3C
    f32 brake;                   // +0x40
    f32 limit_speed;             // +0x44
    f32 gravity_coefficient;     // +0x48
};

namespace app::lua_bind {

// 7102120220 -- str s0,[x0,#0x38]; ret
void FighterKineticEnergyGravity__set_accel_impl(FighterKineticEnergyGravity* ke, f32 val) {
    ke->accel = val;
}

// 7102120230 -- ldr q1,[x0,#0x10]; mov v1.S[1],v0.S[0]; str q1,[x0,#0x10]; ret
void FighterKineticEnergyGravity__set_speed_impl(FighterKineticEnergyGravity* ke, f32 val) {
    auto* v = reinterpret_cast<v4sf*>(ke->speed);
    (*v)[1] = val;
}

// 7102120240 -- str s0,[x0,#0x3c]; ret
void FighterKineticEnergyGravity__set_stable_speed_impl(FighterKineticEnergyGravity* ke, f32 val) {
    ke->stable_speed = val;
}

// 7102120250 -- str s0,[x0,#0x44]; ret
void FighterKineticEnergyGravity__set_limit_speed_impl(FighterKineticEnergyGravity* ke, f32 val) {
    ke->limit_speed = val;
}

// 7102120260 -- str s0,[x0,#0x40]; ret
void FighterKineticEnergyGravity__set_brake_impl(FighterKineticEnergyGravity* ke, f32 val) {
    ke->brake = val;
}

// 7102120270 -- ldr s0,[x0,#0x38]; ret
f32 FighterKineticEnergyGravity__get_accel_impl(FighterKineticEnergyGravity* ke) {
    return ke->accel;
}

// 7102120280 -- ldr s0,[x0,#0x3c]; ret
f32 FighterKineticEnergyGravity__get_stable_speed_impl(FighterKineticEnergyGravity* ke) {
    return ke->stable_speed;
}

// 7102120290 -- ldr s0,[x0,#0x44]; ret
f32 FighterKineticEnergyGravity__get_limit_speed_impl(FighterKineticEnergyGravity* ke) {
    return ke->limit_speed;
}

// 71021202a0 -- ldr s0,[x0,#0x40]; ret
f32 FighterKineticEnergyGravity__get_brake_impl(FighterKineticEnergyGravity* ke) {
    return ke->brake;
}

// 71021202b0 -- str s0,[x0,#0x48]; ret
void FighterKineticEnergyGravity__set_gravity_coefficient_impl(FighterKineticEnergyGravity* ke, f32 val) {
    ke->gravity_coefficient = val;
}

} // namespace app::lua_bind
