#pragma once

#include "types.h"

// Frame state condition system for net frame exchange
//
// Used by the receive path (FUN_710012ac30) to validate incoming frame data
// before applying it to the game state. Each condition has 6 "slots" (channels)
// that can filter by exact match values or value ranges.
//
// Struct layout derived from FUN_710012ed20 (condition check),
// FUN_710012ebe0/ec80 (slot set), FUN_710012ea10 (reset).

namespace app {

// Number of filter channels in the frame state condition system
// [derived: loop bound in FUN_710012ed20, stride 0x50 per slot]
static constexpr int FRAME_CONDITION_NUM_SLOTS = 6;

// Maximum match values per slot (0x50 bytes / 4 bytes per u32 = 20)
// [derived: stride 0x50 in FUN_710012ea10 memset, u32 access in FUN_710012ed20]
static constexpr int FRAME_CONDITION_MAX_MATCH_VALUES = 20;

// Default tick count set by FUN_710012ea10
// [derived: literal 100 stored to +0xc in FUN_710012ea10]
static constexpr u32 FRAME_CONDITION_DEFAULT_TICK_COUNT = 100;

// Sentinel value for "no filter" on frame ranges
// [derived: 0xFFFF comparison in FUN_710012ed20]
static constexpr u16 FRAME_RANGE_NO_FILTER = 0xFFFF;

struct FrameStateCondition {
    // +0x00..+0x1F: header / base object (vtable etc)
    u8 header[0x0C];                   // +0x00 [inferred: base object data, not accessed in these functions]
    u32 tick_count;                    // +0x0C [derived: FUN_710012ea10 sets to 100]
    u8 pad_10[0x10];                   // +0x10

    // +0x20: filter parameters
    s32 player_id;                     // +0x20 [inferred: compared against vtable[0x10] result in FUN_710012ed20]
    s32 match_type;                    // +0x24 [inferred: compared against FUN_710012cea0 result in FUN_710012ed20]

    // +0x28..+0x1F8: 6 match value slots, each 0x50 bytes (20 u32 entries)
    // [derived: stride 0x50 in FUN_710012ed20 loop, u32 access at param_2+(slot*4)+0x20 in FUN_710012cf80]
    u32 slot_values[FRAME_CONDITION_NUM_SLOTS][FRAME_CONDITION_MAX_MATCH_VALUES];
                                       // +0x28

    // +0x208..+0x21C: per-slot entry count (how many values are valid)
    // [derived: FUN_710012ebe0 sets to 1, FUN_710012ed20 reads as loop bound]
    u32 slot_entry_count[FRAME_CONDITION_NUM_SLOTS];
                                       // +0x208

    // +0x220..+0x234: per-slot range minimum (used when mode=range)
    // [derived: FUN_710012ec80 writes, FUN_710012ed20 compares local_44 < min]
    u32 slot_range_min[FRAME_CONDITION_NUM_SLOTS];
                                       // +0x220

    // +0x238..+0x24C: per-slot range maximum (used when mode=range)
    // [derived: FUN_710012ec80 writes, FUN_710012ed20 compares max < local_44]
    u32 slot_range_max[FRAME_CONDITION_NUM_SLOTS];
                                       // +0x238

    // +0x250..+0x255: per-slot mode flag (0=match-value, 1=range)
    // [derived: FUN_710012ebe0 sets to 0, FUN_710012ec80 sets to 1]
    u8 slot_mode[FRAME_CONDITION_NUM_SLOTS];
                                       // +0x250

    // +0x256..+0x257: primary frame range filter (s16 min, unused byte)
    s16 frame_range_min;               // +0x256 [inferred: compared against vtable[0x28] in FUN_710012ed20]
    u16 frame_range_max;               // +0x258 [inferred: 0xFFFF=disabled, compared against vtable[0x28]]

    // +0x25A..+0x25B: secondary frame range filter
    s16 secondary_range_min;           // +0x25A [inferred: compared against vtable[0x30] in FUN_710012ed20]
    u16 secondary_range_max;           // +0x25C [inferred: 0xFFFF=disabled, compared against vtable[0x30]]

    // +0x25E..+0x25F: boolean flags
    u8 require_online;                 // +0x25E [inferred: if set, requires vtable[0x38] to return true]
    u8 reject_duplicate_frame;         // +0x25F [inferred: if set, rejects when vtable[0x20]==vtable[0x30]]

    // +0x260: dirty bitmask — bits 0..5 for base flags, bits 6..11 for slot enables
    // [derived: FUN_710012ebe0/ec80 set bits (slot+6), FUN_710012ed20 tests them]
    u32 dirty_bits;                    // +0x260
};
// sizeof = 0x264

} // namespace app
