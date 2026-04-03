#pragma once

#include "types.h"

namespace app {

struct AttackAbsoluteData {
    float field_0x00;       // +0x00
    s32 field_0x04;         // +0x04
    s32 field_0x08;         // +0x08
    s32 field_0x0c;         // +0x0c
    s32 field_0x10;         // +0x10
    float field_0x14;       // +0x14
    float field_0x18;       // +0x18
    float field_0x1c;       // +0x1c
    s64 field_0x20;         // +0x20
    u8 field_0x28;          // +0x28
    u8 field_0x29;          // +0x29
    u8 field_0x2a;          // +0x2a
    u8 flag_0x2b;           // +0x2b (bool)
    u8 flag_0x2c;           // +0x2c (bool)
    u8 pad_0x2d;            // +0x2d
    u8 field_0x2e;          // +0x2e
    u8 flag_0x2f;           // +0x2f (bool)
};

} // namespace app
