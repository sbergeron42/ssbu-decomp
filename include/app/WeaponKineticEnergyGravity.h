#pragma once

#include "types.h"

namespace app {

struct WeaponKineticEnergyGravity {
    u8 pad_0x00[0x10];     // +0x00
    u8 vec4_0x10[0x10];    // +0x10 [derived: set_speed_impl (.dynsym) writes speed as f32 into lane 1 of SIMD vec at +0x10]
    u8 pad_0x20[0x14];     // +0x20
    f32 accel;              // +0x34 [derived: set_accel_impl (.dynsym) writes +0x34 as f32]
    f32 limit_speed;        // +0x38 [derived: get_limit_speed_impl (.dynsym) reads +0x38 as f32]
};

} // namespace app
