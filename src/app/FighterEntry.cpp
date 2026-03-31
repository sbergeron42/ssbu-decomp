#include "types.h"

// FighterEntry — operates on FighterEntry* directly

struct FighterEntry;

namespace app::lua_bind {

// 71020cbc40 — fighter_num (2 instructions)
u32 FighterEntry__fighter_num_impl(FighterEntry* entry) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + 0x14);
}

} // namespace app::lua_bind
