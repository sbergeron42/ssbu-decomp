#include "types.h"

// BattleObjectSlow -- operates on BattleObjectSlow* directly (not accessor)
// These are direct struct field reads, not vtable dispatchers

struct BattleObjectSlow {
    s32 mode;     // +0x0
    f32 rate;     // +0x4
    u8  type;     // +0x8
};

namespace app::lua_bind {

// 7101fca5b0 -- 2 instructions (ldr s0,[x0,#4]; ret)
f32 BattleObjectSlow__rate_impl(BattleObjectSlow* slow) {
    return slow->rate;
}

// 7101fca650 -- 7 instructions (branch on byte field)
bool BattleObjectSlow__is_estimate_impl(BattleObjectSlow* slow) {
    if (slow->type == 0) return true;
    return slow->mode == 0;
}

// 7101fca670 -- 7 instructions (branch on byte field, compare to 2)
bool BattleObjectSlow__is_adjust_impl(BattleObjectSlow* slow) {
    if (slow->type == 0) return true;
    return slow->mode == 2;
}

} // namespace app::lua_bind
