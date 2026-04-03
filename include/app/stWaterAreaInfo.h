#pragma once

#include "types.h"

namespace app {

struct stWaterAreaInfo {
    u16 field_0x00;     // +0x00
    u8 pad_0x02[2];     // +0x02
    float field_0x04;   // +0x04
    float field_0x08;   // +0x08
    u8 is_active;       // +0x0c (bool)
};

} // namespace app
