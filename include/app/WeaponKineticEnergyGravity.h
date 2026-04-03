#pragma once

#include "types.h"

namespace app {

struct WeaponKineticEnergyGravity {
    u8 pad_0x00[0x10];     // +0x00
    u8 vec4_0x10[0x10];    // +0x10 (SIMD vec4: speed in lane 1)
    u8 pad_0x20[0x14];     // +0x20
    f32 accel;              // +0x34
    f32 limit_speed;        // +0x38
};

} // namespace app
