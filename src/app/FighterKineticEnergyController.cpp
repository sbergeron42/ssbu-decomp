#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

// FighterKineticEnergyController -- operates on FighterKineticEnergyController* directly
// Speed max vector at +0x50 is SIMD 128-bit. Accel fields at +0x8c..+0x98.

struct FighterKineticEnergyController {
    u8  pad_0x00[0x50];
    u8  speed_max[0x10];     // +0x50 (v4sf)
    u8  pad_0x60[0x2C];
    f32 accel_x_mul;         // +0x8C
    f32 accel_x_add;         // +0x90
    f32 accel_y_mul;         // +0x94
    f32 accel_y_add;         // +0x98
};

namespace app::lua_bind {

// 710211f330 -- ldr q1,[x0,#0x50]; fmul s0,s0,v1.S[0]; mov v1.S[0],v0.S[0]; str q1,[x0,#0x50]; ret
void FighterKineticEnergyController__mul_x_speed_max_impl(FighterKineticEnergyController* ke, f32 val) {
    auto* v = reinterpret_cast<v4sf*>(ke->speed_max);
    (*v)[0] *= val;
}

// 710211f350 -- str s0,[x0,#0x8c]; ret
void FighterKineticEnergyController__set_accel_x_mul_impl(FighterKineticEnergyController* ke, f32 val) {
    ke->accel_x_mul = val;
}

// 710211f360 -- str s0,[x0,#0x90]; ret
void FighterKineticEnergyController__set_accel_x_add_impl(FighterKineticEnergyController* ke, f32 val) {
    ke->accel_x_add = val;
}

// 710211f370 -- ldr s1,[x0,#0x8c]; fmul s0,s1,s0; str s0,[x0,#0x8c]; ret
void FighterKineticEnergyController__mul_x_accel_mul_impl(FighterKineticEnergyController* ke, f32 val) {
    ke->accel_x_mul *= val;
}

// 710211f380 -- ldr s1,[x0,#0x90]; fmul s0,s1,s0; str s0,[x0,#0x90]; ret
void FighterKineticEnergyController__mul_x_accel_add_impl(FighterKineticEnergyController* ke, f32 val) {
    ke->accel_x_add *= val;
}

// 710211f390 -- str s0,[x0,#0x94]; ret
void FighterKineticEnergyController__set_accel_y_mul_impl(FighterKineticEnergyController* ke, f32 val) {
    ke->accel_y_mul = val;
}

// 710211f3a0 -- str s0,[x0,#0x98]; ret
void FighterKineticEnergyController__set_accel_y_add_impl(FighterKineticEnergyController* ke, f32 val) {
    ke->accel_y_add = val;
}

// 710211f3b0 -- ldr s0,[x0,#0x8c]; ret
f32 FighterKineticEnergyController__get_accel_x_mul_impl(FighterKineticEnergyController* ke) {
    return ke->accel_x_mul;
}

// 710211f3c0 -- ldr s0,[x0,#0x90]; ret
f32 FighterKineticEnergyController__get_accel_x_add_impl(FighterKineticEnergyController* ke) {
    return ke->accel_x_add;
}

// 710211f3d0 -- ldr s0,[x0,#0x94]; ret
f32 FighterKineticEnergyController__get_accel_y_mul_impl(FighterKineticEnergyController* ke) {
    return ke->accel_y_mul;
}

// 710211f3e0 -- ldr s0,[x0,#0x98]; ret
f32 FighterKineticEnergyController__get_accel_y_add_impl(FighterKineticEnergyController* ke) {
    return ke->accel_y_add;
}

} // namespace app::lua_bind
