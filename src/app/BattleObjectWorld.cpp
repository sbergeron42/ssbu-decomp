#include "types.h"

// BattleObjectWorld — operates on BattleObjectWorld* directly
// Simple struct field reads

struct BattleObjectWorld;

namespace app::lua_bind {

// 7101fca1f0 — 2 instructions
f32 BattleObjectWorld__gravity_speed_coefficient_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(world) + 0x4);
}

// 7101fca2d0 — 2 instructions
bool BattleObjectWorld__is_move_impl(BattleObjectWorld* world) {
    return reinterpret_cast<u8*>(world)[0x5a];
}

// 7101fca2e0 — 2 instructions (returns pointer to +0x20)
void* BattleObjectWorld__move_speed_impl(BattleObjectWorld* world) {
    return reinterpret_cast<u8*>(world) + 0x20;
}

// 7101fca2f0 — 2 instructions
bool BattleObjectWorld__is_disable_reverse_impl(BattleObjectWorld* world) {
    return reinterpret_cast<u8*>(world)[0x5d];
}

} // namespace app::lua_bind
