#pragma once

#include "types.h"

namespace app {

// CameraController — global camera state singleton
// Singleton at DAT_71052b7f00
// [derived: Ghidra analysis of convert_pos_dead_range_gravity (0x7102282ef0),
//  set_dead_range (0x710164c390), dead_range (0x7102282810)]
struct CameraController {
    u8 unk_0x00[0xc30];
    float dead_range_neg;           // +0xC30 [inferred: dead range negative boundary, used in gravity rotation]
    float dead_range_pos;           // +0xC34 [inferred: dead range positive boundary, used in gravity rotation]
};

} // namespace app
