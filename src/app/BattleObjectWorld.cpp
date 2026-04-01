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

// 7101fca220 — gravity_pos_impl: return own gravity vec (+0x10) if normal, else global zero vec
// DCL-initialized global zero vec — external branches, won't byte-match
void* BattleObjectWorld__gravity_pos_impl(BattleObjectWorld* world) {
    auto* p = reinterpret_cast<u8*>(world);
    if (!p[0x5c]) return p + 0x10;
    // modified gravity — return global zero vec (DCL singleton at 0x71052b7610)
    static __attribute__((aligned(16))) u8 s_zero_gravity[16];
    static u64 s_guard;
    if (!(s_guard & 1)) {
        extern int __cxa_guard_acquire(void*);
        extern void __cxa_guard_release(void*);
        if (__cxa_guard_acquire(&s_guard)) {
            __cxa_guard_release(&s_guard);
        }
    }
    return s_zero_gravity;
}

} // namespace app::lua_bind
