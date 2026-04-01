#include "types.h"

// BattleObjectSlow — operates on BattleObjectSlow* directly (not accessor)
// These are direct struct field reads, not vtable dispatchers

struct BattleObjectSlow;

namespace app::lua_bind {

// 7101fca5b0 — 2 instructions (ldr s0,[x0,#4]; ret)
f32 BattleObjectSlow__rate_impl(BattleObjectSlow* slow) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(slow) + 0x4);
}

// 7101fca650 — 7 instructions (branch on byte field)
bool BattleObjectSlow__is_estimate_impl(BattleObjectSlow* slow) {
    auto* p = reinterpret_cast<u8*>(slow);
    if (p[0x8] == 0) return true;
    return *reinterpret_cast<s32*>(p) == 0;
}

// 7101fca670 — 7 instructions (branch on byte field, compare to 2)
bool BattleObjectSlow__is_adjust_impl(BattleObjectSlow* slow) {
    auto* p = reinterpret_cast<u8*>(slow);
    if (p[0x8] == 0) return true;
    return *reinterpret_cast<s32*>(p) == 2;
}

// 7101fca5c0 — rate_request_impl: 1.0f / (float)global_team_count_byte
// Reads global team param via once-flag DCL — external branches, won't byte-match
f32 BattleObjectSlow__rate_request_impl(BattleObjectSlow* slow) {
    (void)slow;
    // original: checks DAT_71052c2610[0x40], reads global byte at DAT_71052c4189
    // (initialized via __cxa_guard and FUN_71017641a0 team param init)
    // returns 1.0f / (float)team_count_byte
    extern u8 DAT_71052c4189;
    extern void* DAT_71052c2610;
    extern int __cxa_guard_acquire(void*);
    extern void __cxa_guard_release(void*);
    extern u64 g_team_param_init_guard;
    u8 bVar;
    if (*reinterpret_cast<char*>(reinterpret_cast<u8*>(DAT_71052c2610) + 0x40) == '\0') {
        bVar = DAT_71052c4189;
        if (!(g_team_param_init_guard & 1)) {
            int r = __cxa_guard_acquire(&g_team_param_init_guard);
            bVar = DAT_71052c4189;
            if (r) __cxa_guard_release(&g_team_param_init_guard);
        }
    } else {
        extern u8 FUN_71014a2cd0();
        bVar = FUN_71014a2cd0();
    }
    return 1.0f / (float)(unsigned)bVar;
}

} // namespace app::lua_bind
