#pragma once

#include "types.h"

namespace lib {

// L2CAgent — base class for Lua/ACMD script agents.
// sizeof(L2CAgent) = 0x38 (verified: constructor writes +0x00..+0x30)
//
// Vtable at 0x710523be40 [derived: constructor stores &DAT_710523be40]
// Constructor at 0x710372da00, D1 dtor at 0x710372da20, D0 dtor at 0x710372da80
//
// Members derived from constructor zero-init pattern + destructor free pattern:
//   +0x00: vtable pointer
//   +0x08: lua_State* (passed to ctor, read in clear_lua_stack)
//   +0x10: alloc_ptr (freed in dtor, zeroed after free)
//   +0x18: zeroed in ctor (purpose unknown)
//   +0x20: linked list head (walk-and-free in dtor)
//   +0x28: zeroed in ctor (purpose unknown)
//   +0x30: 0x3f800000 = 1.0f raw bits (playback rate, stored as u32 for matching)
struct L2CAgent {
    void** _vt;              // +0x00 [derived: DAT_710523be40 vtable stored in ctor]
    void* lua_state;         // +0x08 [derived: read in clear_lua_stack, passed to ctor]
    void* alloc_ptr;         // +0x10 [derived: freed in ~L2CAgent, zeroed after free]
    u64 unk_0x18;            // +0x18 [derived: zeroed in ctor]
    u8* linked_list_head;    // +0x20 [derived: walk-and-free linked list in ~L2CAgent]
    u64 unk_0x28;            // +0x28 [derived: zeroed in ctor]
    u32 rate_raw;            // +0x30 [derived: 0x3f800000 = 1.0f, stored as integer for NX Clang matching]
    u32 pad_0x34;            // +0x34
};
static_assert(sizeof(L2CAgent) == 0x38, "L2CAgent size mismatch");

} // namespace lib
