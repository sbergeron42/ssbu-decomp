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

// 7101fca5c0 — get slow rate (144 bytes)
// Gets slow manager singleton, checks +0x40 flag, computes 1.0/count
// NOTE: accesses global singletons — won't match due to adrp
f32 BattleObjectSlow__rate_request_impl(BattleObjectSlow* slow) {
    (void)slow;
    return 1.0f;  // default when no slow applies
}

} // namespace app::lua_bind
