#pragma once

#include "types.h"

namespace app {

// Field names derived from .dynsym FighterEntry__*_impl functions.
// Access pattern: FighterEntry* is passed directly (not via accessor).
struct FighterEntry {
    u8    pad_0x00[0x14];
    u32   fighter_num;                       // +0x14 [derived: fighter_num_impl (.dynsym) reads +0x14 as u32]
    u8    pad_0x18[0x4138];
    u64   slot_count;                        // +0x4150 [derived: current_fighter_id_impl (.dynsym) reads +0x4150 as u64 bounds check]
    u8    pad_0x4158[0x08];
    void* slots[759];                        // +0x4160 [derived: current_fighter_id_impl (.dynsym) indexes +0x4160 as ptr array with slot index*8]
    u8    current_index;                     // +0x5918 [derived: current_fighter_id_impl (.dynsym) reads +0x5918 as u8 to select active slot]
    u8    pad_0x5919[0x07];
    u8    entry_type;                        // +0x5920 [inferred: read by FighterManager entry iteration, distinguishes human/cpu/none]
};

} // namespace app
