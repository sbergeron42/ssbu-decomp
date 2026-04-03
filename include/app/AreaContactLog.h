#pragma once

#include "types.h"

namespace app {

struct AreaContactLog {
    s32 field_0x00;     // +0x00
    s32 field_0x04;     // +0x04
    s32 field_0x08;     // +0x08
    u8  field_0x0c;     // +0x0c
    u8  field_0x0d;     // +0x0d
    u8  field_0x0e;     // +0x0e
    u8  field_0x0f;     // +0x0f
    float pos_x;        // +0x10
    float pos_y;        // +0x14
};

} // namespace app
