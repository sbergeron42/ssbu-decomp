#pragma once

#include "types.h"

namespace app {

struct Rhombus2 {
    float corner0_x;    // +0x00
    float corner0_y;    // +0x04
    u8 pad_0x08[8];     // +0x08
    float corner1_x;    // +0x10
    float corner1_y;    // +0x14
    u8 pad_0x18[8];     // +0x18
    float corner2_x;    // +0x20
    float corner2_y;    // +0x24
    u8 pad_0x28[8];     // +0x28
    float corner3_x;    // +0x30
    float corner3_y;    // +0x34
};

} // namespace app
