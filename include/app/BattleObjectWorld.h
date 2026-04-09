#pragma once

#include "types.h"

namespace app {

// BattleObjectWorld — global world state including gravity parameters
// Singleton at DAT_71052b7558
// [derived: Ghidra analysis of convert_pos_dead_range_gravity (0x7102282ef0),
//  restore_pos_dead_range_gravity (0x7102283020)]
struct BattleObjectWorld {
    u8 unk_0x00[0x10];
    float gravity_origin_x;         // +0x10 [inferred: gravity origin X, read as packed {x,y} in convert_pos]
    float gravity_origin_y;         // +0x14 [inferred: gravity origin Y / gravity_y value used in sin/cos rotation]
    u8 unk_0x18[0x41];
    u8 gravity_override_flag;       // +0x59 [inferred: if nonzero, gravity rotation is bypassed]
    u8 unk_0x5A[0x02];
    u8 gravity_disabled_flag;       // +0x5C [inferred: if nonzero, gravity rotation is bypassed]
};

} // namespace app
