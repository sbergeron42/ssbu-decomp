#pragma once

#include "types.h"

namespace app {

// DamageLog — layout recovered from Ghidra decompilation of damage log functions.
// Positional field names (pos0-pos3) are inferred from sequential access patterns, not .dynsym symbols.
struct DamageLog {
    float field_0x00;       // +0x00
    s32 field_0x04;         // +0x04
    s32 field_0x08;         // +0x08
    u8 pad_0x0c[4];         // +0x0c
    float pos0_x;           // +0x10
    float pos0_y;           // +0x14
    u8 pad_0x18[8];         // +0x18
    float pos1_x;           // +0x20
    float pos1_y;           // +0x24
    u32 pos1_kind;          // +0x28
    u8 pad_0x2c[4];         // +0x2c
    float pos2_x;           // +0x30
    float pos2_y;           // +0x34
    u8 pad_0x38[8];         // +0x38
    float field_0x40;       // +0x40
    float field_0x44;       // +0x44
    float field_0x48;       // +0x48
    s32 field_0x4c;         // +0x4c
    s64 field_0x50;         // +0x50
    float field_0x58;       // +0x58
    s32 field_0x5c;         // +0x5c
    float field_0x60;       // +0x60
    u8 pad_0x64[0xc];       // +0x64
    float pos3_x;           // +0x70
    float pos3_y;           // +0x74
    u8 pad_0x78[8];         // +0x78
    s32 field_0x80;         // +0x80
    s32 field_0x84;         // +0x84
    u8 field_0x88;          // +0x88
    u8 flag_0x89;           // +0x89 (bool)
    u8 flag_0x8a;           // +0x8a (bool)
    u8 flag_0x8b;           // +0x8b (bool)
    u8 flag_0x8c;           // +0x8c (bool)
    u8 flag_0x8d;           // +0x8d (bool)
    u8 flag_0x8e;           // +0x8e (bool)
    u8 flag_0x8f;           // +0x8f (bool)
    u8 flag_0x90;           // +0x90 (bool)
    u8 flag_0x91;           // +0x91 (bool)
    u8 flag_0x92;           // +0x92 (bool)
    u8 flag_0x93;           // +0x93 (bool)
    u8 flag_0x94;           // +0x94 (bool)
    u8 pad_0x95[3];         // +0x95
    s32 field_0x98;         // +0x98
    u8 field_0x9c;          // +0x9c
};

} // namespace app
