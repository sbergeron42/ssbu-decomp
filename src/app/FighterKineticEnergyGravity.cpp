#include "types.h"

typedef float v4sf __attribute__((vector_size(16)));

// FighterKineticEnergyGravity — fighter-specific 1D gravity energy.
// Only the Y lane of the speed vector is meaningful (x/z lanes stay 0).
// Layout recovered from the 11 FighterKineticEnergyGravity__*_impl
// dispatchers at 0x7102120220–0x71021202b0 (ldr/str offsets).
struct FighterKineticEnergyGravity {
    // -- Base KineticEnergy region (0x00..0x0F) — vtable + first 8 bytes of state --
    u8  pad_0x00[0x10];

    // +0x10 — 16-byte speed vector; Y lane is the actual gravity speed
    // [derived: set_speed_impl at 0x7102120230 does ldr q1,[x0,#0x10];
    //  mov v1.S[1],v0.S[0]; str q1,[x0,#0x10]]
    u8  speed[0x10];

    // -- Gap (0x20..0x37) — unknown base class state --
    u8  pad_0x20[0x18];

    // +0x38 — gravity acceleration (scalar)
    // [derived: set_accel_impl at 0x7102120220 str s0,[x0,#0x38];
    //  get_accel_impl at 0x7102120270 ldr s0,[x0,#0x38]]
    f32 accel;

    // +0x3C — stable (terminal) speed
    // [derived: set_stable_speed_impl at 0x7102120240 str s0,[x0,#0x3c];
    //  get_stable_speed_impl at 0x7102120280 ldr s0,[x0,#0x3c]]
    f32 stable_speed;

    // +0x40 — brake force (applied above stable_speed)
    // [derived: set_brake_impl at 0x7102120260 str s0,[x0,#0x40];
    //  get_brake_impl at 0x71021202a0 ldr s0,[x0,#0x40]]
    f32 brake;

    // +0x44 — speed ceiling
    // [derived: set_limit_speed_impl at 0x7102120250 str s0,[x0,#0x44];
    //  get_limit_speed_impl at 0x7102120290 ldr s0,[x0,#0x44]]
    f32 limit_speed;

    // +0x48 — gravity coefficient (multiplier applied per frame)
    // [derived: set_gravity_coefficient_impl at 0x71021202b0 str s0,[x0,#0x48]]
    f32 gravity_coefficient;
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
