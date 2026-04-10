#pragma once

#include "types.h"

// Placeholder struct for object accessed by FUN_7103974820.
// Address range suggests game-specific object (not library code).
// Field names are provisional — only offsets are verified from binary.
struct UnkType_7103974820 {
    u8 unk_0x00[0x6e];
    u8 field_0x6e;       // +0x6e [inferred: cleared as u8 or u16 in reset, flag/state byte]
    u8 field_0x6f;       // +0x6f [inferred: boolean flag checked in reset logic]
    u8 field_0x70;       // +0x70 [inferred: boolean flag, checked and cleared in reset]
    u8 unk_0x71[0x14];
    u8 field_0x85;       // +0x85 [inferred: boolean flag, dual-checked in both reset paths]
    u8 unk_0x86[0x1AE];
    s32 field_0x234;     // +0x234 [inferred: nonzero check gates field clearing]
    u8 unk_0x238[0x2D8];
    u16 field_0x510;     // +0x510 [inferred: cleared to 0 at start of reset path]
};
