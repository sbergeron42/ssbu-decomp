#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

// FighterKineticEnergyGravity — operates on FighterKineticEnergyGravity* directly
// Simple field getters/setters at various offsets.
// Speed vector at +0x10 is a Vec4 (SIMD 128-bit), Y component at index 1.

struct FighterKineticEnergyGravity;

namespace app::lua_bind {

// 7102120220 — str s0,[x0,#0x38]; ret
void FighterKineticEnergyGravity__set_accel_impl(FighterKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x38) = val;
}

// 7102120230 — ldr q1,[x0,#0x10]; mov v1.S[1],v0.S[0]; str q1,[x0,#0x10]; ret
void FighterKineticEnergyGravity__set_speed_impl(FighterKineticEnergyGravity* ke, f32 val) {
    auto* v = reinterpret_cast<v4sf*>(reinterpret_cast<u8*>(ke) + 0x10);
    (*v)[1] = val;
}

// 7102120240 — str s0,[x0,#0x3c]; ret
void FighterKineticEnergyGravity__set_stable_speed_impl(FighterKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x3c) = val;
}

// 7102120250 — str s0,[x0,#0x44]; ret
void FighterKineticEnergyGravity__set_limit_speed_impl(FighterKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x44) = val;
}

// 7102120260 — str s0,[x0,#0x40]; ret
void FighterKineticEnergyGravity__set_brake_impl(FighterKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x40) = val;
}

// 7102120270 — ldr s0,[x0,#0x38]; ret
f32 FighterKineticEnergyGravity__get_accel_impl(FighterKineticEnergyGravity* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x38);
}

// 7102120280 — ldr s0,[x0,#0x3c]; ret
f32 FighterKineticEnergyGravity__get_stable_speed_impl(FighterKineticEnergyGravity* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x3c);
}

// 7102120290 — ldr s0,[x0,#0x44]; ret
f32 FighterKineticEnergyGravity__get_limit_speed_impl(FighterKineticEnergyGravity* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x44);
}

// 71021202a0 — ldr s0,[x0,#0x40]; ret
f32 FighterKineticEnergyGravity__get_brake_impl(FighterKineticEnergyGravity* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x40);
}

// 71021202b0 — str s0,[x0,#0x48]; ret
void FighterKineticEnergyGravity__set_gravity_coefficient_impl(FighterKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x48) = val;
}

} // namespace app::lua_bind
