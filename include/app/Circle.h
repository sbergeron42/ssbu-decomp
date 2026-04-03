#pragma once

#include "types.h"

namespace app {

struct Circle {
    float pos_x;        // +0x00
    float pos_y;        // +0x04
    u8 pad_0x08[8];     // +0x08 (unknown)
    float size;         // +0x10
};

} // namespace app
