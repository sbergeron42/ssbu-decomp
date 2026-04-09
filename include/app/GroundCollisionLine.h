#pragma once

#include "types.h"

namespace app {

// CollisionEndpoint — a point on a ground collision line
// +0x10: position as 4 floats (x, y, z, w) [derived: get_near_pos reads as 128-bit NEON vector]
// [derived: Ghidra analysis of get_near_pos (0x71015cbd50)]
struct CollisionEndpoint {
    u8 unk_0x00[0x10];
    float position[4];              // +0x10 [derived: loaded as 128-bit vector for distance comparison in get_near_pos]
};

// GroundCollisionLine — a line segment used for ground collision
// +0x88: endpoint0 pointer [derived: get_near_pos reads line+0x88 as endpoint pointer]
// +0x90: endpoint1 pointer [derived: get_near_pos reads line+0x90 as endpoint pointer]
// [derived: Ghidra analysis of get_near_pos (0x71015cbd50)]
struct GroundCollisionLine {
    u8 unk_0x00[0x88];
    CollisionEndpoint* endpoint0;   // +0x88 [derived: first endpoint, position at +0x10]
    CollisionEndpoint* endpoint1;   // +0x90 [derived: second endpoint, position at +0x10]
};

} // namespace app
