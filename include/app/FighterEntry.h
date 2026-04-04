#pragma once

#include "types.h"

namespace app {

struct FighterEntry {
    u8    pad_0x00[0x14];
    u32   fighter_num;                       // +0x14
    u8    pad_0x18[0x4138];
    u64   slot_count;                        // +0x4150
    u8    pad_0x4158[0x08];
    void* slots[759];                        // +0x4160
    u8    current_index;                     // +0x5918
    u8    pad_0x5919[0x07];
    u8    entry_type;                        // +0x5920
};

} // namespace app
