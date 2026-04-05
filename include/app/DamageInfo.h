#pragma once

#include "types.h"

namespace app {

// DamageInfo — layout recovered from Ghidra decompilation of damage processing functions.
// Positional field names (pos0, pos1) are inferred from access patterns, not .dynsym symbols.
struct DamageInfo {
    float field_0x00;       // +0x00
    float field_0x04;       // +0x04
    float field_0x08;       // +0x08
    float field_0x0c;       // +0x0c
    float field_0x10;       // +0x10
    u8 pad_0x14[0x14c];     // +0x14 (unknown region)
    float field_0x160;      // +0x160
    u8 pad_0x164[0xc];      // +0x164
    float pos0_x;           // +0x170
    float pos0_y;           // +0x174
    u32 pos0_kind;          // +0x178
    u8 pad_0x17c[4];        // +0x17c
    float pos1_x;           // +0x180
    float pos1_y;           // +0x184
    u8 pad_0x188[8];        // +0x188
    float field_0x190;      // +0x190
    s32 field_0x194;        // +0x194
    float field_0x198;      // +0x198
    u8 flag_0x19c;          // +0x19c (bool)
    u8 flag_0x19d;          // +0x19d (bool)
};

} // namespace app
