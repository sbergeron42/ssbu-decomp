#pragma once

#include "types.h"

namespace app {

// FighterEntry — operates on its own pointer
// Known field offsets:
//   +0x14     u32 fighter_num
//   +0x4150   u64 slot_count
//   +0x4160   void* slots[N] (fighter slot array, indexed by entry)
//   +0x5918   u8  current_index
// Slots have: vtable at +0x0, fighter_id at +0x8, is_active at vtable[0x518/8]
struct FighterEntry;

} // namespace app
