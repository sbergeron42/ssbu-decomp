#pragma once

#include "types.h"

namespace app {

// AttackData — layout recovered from Ghidra decompilation of attack setup functions.
// Field names are inferred from positional patterns and usage context, not .dynsym symbols.
struct AttackData {
    float hitbox0_x;        // +0x00 [inferred: first hitbox X position, sub-table 0 pattern in attack setup]
    float hitbox0_y;        // +0x04 [inferred: first hitbox Y position]
    u32 hitbox0_kind;       // +0x08 [inferred: first hitbox type/kind enum]
    u8 pad_0x0c[4];         // +0x0c
    float hitbox1_x;        // +0x10 [inferred: second hitbox X position, sub-table 1 pattern]
    float hitbox1_y;        // +0x14 [inferred: second hitbox Y position]
    u32 hitbox1_kind;       // +0x18 [inferred: second hitbox type/kind enum]
    u8 pad_0x1c[4];         // +0x1c
    float field_0x20;       // +0x20
    float field_0x24;       // +0x24
    s32 field_0x28;         // +0x28
    s32 field_0x2c;         // +0x2c
    s32 field_0x30;         // +0x30
    s32 field_0x34;         // +0x34
    float field_0x38;       // +0x38
    float field_0x3c;       // +0x3c
    float field_0x40;       // +0x40
    u8 pad_0x44[4];         // +0x44
    s64 field_0x48;         // +0x48
    u16 field_0x50;         // +0x50
    u8 field_0x52;          // +0x52
    u8 flag_0x53;           // +0x53 (bool)
    u8 field_0x54;          // +0x54
    u8 pad_0x55[3];         // +0x55
    s64 field_0x58;         // +0x58
    u8 field_0x60;          // +0x60
    u8 field_0x61;          // +0x61
    u8 field_0x62;          // +0x62
    u8 flag_0x63;           // +0x63 (bool)
    u8 flag_0x64;           // +0x64 (bool)
    u8 flag_0x65;           // +0x65 (bool)
    u8 flag_0x66;           // +0x66 (bool)
    u8 flag_0x67;           // +0x67 (bool)
    u8 flag_0x68;           // +0x68 (bool)
    u8 flag_0x69;           // +0x69 (bool)
    u8 field_0x6a;          // +0x6a
    u8 flag_0x6b;           // +0x6b (bool)
    u8 flag_0x6c;           // +0x6c (bool)
    u8 flag_0x6d;           // +0x6d (bool)
    u8 flag_0x6e;           // +0x6e (bool)
    u8 pad_0x6f;            // +0x6f
    u8 flag_0x70;           // +0x70 (bool)
    u8 field_0x71;          // +0x71
    u8 flag_0x72;           // +0x72 (bool)
    u8 field_0x73;          // +0x73
    u16 field_0x74;         // +0x74
    u8 field_0x76;          // +0x76
    u8 pad_0x77;            // +0x77
    u32 field_0x78;         // +0x78
    u8 flag_0x7c;           // +0x7c (bool)
    u8 flag_0x7d;           // +0x7d (bool)
    u8 field_0x7e;          // +0x7e
    u8 field_0x7f;          // +0x7f
    u8 flag_0x80;           // +0x80 (bool)
    u8 flag_0x81;           // +0x81 (bool)
    u8 pad_0x82[6];         // +0x82
    s64 field_0x88;         // +0x88
    float sub_x;            // +0x90 [inferred: sub-table position X, same pattern as hitbox0/1]
    float sub_y;            // +0x94 [inferred: sub-table position Y]
    u8 pad_0x98[8];         // +0x98
    s32 field_0xa0;         // +0xa0
    u8 flag_0xa4;           // +0xa4 (bool)
    u8 pad_0xa5;            // +0xa5
    u8 flag_0xa6;           // +0xa6 (bool)
};

} // namespace app
