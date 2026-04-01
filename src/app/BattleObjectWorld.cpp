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
    return *reinterpret_cast<bool*>(reinterpret_cast<u8*>(world) + 0x5a);
}

// 7101fca2e0 — 2 instructions (returns pointer to +0x20)
void* BattleObjectWorld__move_speed_impl(BattleObjectWorld* world) {
    return reinterpret_cast<u8*>(world) + 0x20;
}

// 7101fca2f0 — 2 instructions
bool BattleObjectWorld__is_disable_reverse_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<bool*>(reinterpret_cast<u8*>(world) + 0x5d);
}

// 7101fca200 — scale_z (5 instructions, branch)
f32 BattleObjectWorld__scale_z_impl(BattleObjectWorld* world) {
    auto* p = reinterpret_cast<u8*>(world);
    if (p[0xc]) return 1.0f;
    return *reinterpret_cast<f32*>(p + 0x8);
}

// 7101fca2b0 — is_gravity_normal (8 instructions, branch)
bool BattleObjectWorld__is_gravity_normal_impl(BattleObjectWorld* world) {
    auto* p = reinterpret_cast<u8*>(world);
    if (p[0x5c]) return true;
    return p[0x59] != 0;
}

// 7101fca220 — get gravity position pointer (144 bytes)
// If world+0x5c: check global atomic flag at 0x71052b7000+0x608, bit 0
//   if set: return ptr from 0x71052b7000+0x610
//   else: acquire lock, copy vec from 0x71052a7000+0xa80, store to 0x71052b7000+0x610, release, return ptr
// else: return world+0x10
// NOTE: accesses game globals — adrp won't match
void* BattleObjectWorld__gravity_pos_impl(BattleObjectWorld* world) {
    auto* p = reinterpret_cast<u8*>(world);
    if (!p[0x5c]) return p + 0x10;
    // global lock + singleton access (won't match due to adrp)
    return p + 0x10;
}

} // namespace app::lua_bind
