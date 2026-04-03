#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100-0x7101 range, batch d5-011
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: abort()/__throw_out_of_range thunks (0x7100 range),
//           global-dispatch wrapper, sv_animcmd lua_bind, vtable dispatcher

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" void FUN_71014f8940(u64);

extern "C" u64 *DAT_71052c2760;

struct lua_State;

namespace app {
    namespace sv_animcmd {
        void RUMBLE_ALL(lua_State *);
    }
}

// ---- abort() / __throw_out_of_range thunks (0x7100 range) ----------------

// 0x7100760a9c
[[noreturn]] void FUN_7100760a9c(void) { abort(); }

// 0x7100760b1c
[[noreturn]] void FUN_7100760b1c(void) { abort(); }

// 0x710083850c
[[noreturn]] void FUN_710083850c(void) { abort(); }

// 0x71008659dc
[[noreturn]] void FUN_71008659dc(void) { abort(); }

// 0x710089c57c
[[noreturn]] void FUN_710089c57c(void) { abort(); }

// 0x71008d0bdc
[[noreturn]] void FUN_71008d0bdc(void) { abort(); }

// 0x71008e46ec
[[noreturn]] void FUN_71008e46ec(void) { abort(); }

// 0x71008f70dc
[[noreturn]] void FUN_71008f70dc(void) { abort(); }

// 0x710091a3dc
[[noreturn]] void FUN_710091a3dc(void) { abort(); }

// 0x710096017c
[[noreturn]] void FUN_710096017c(void) { abort(); }

// 0x710097c9bc
[[noreturn]] void FUN_710097c9bc(void) { abort(); }

// 0x71009b3d2c
[[noreturn]] void FUN_71009b3d2c(void) { abort(); }

// 0x71009eb86c
[[noreturn]] void FUN_71009eb86c(void) { abort(); }

// 0x7100a52f3c
[[noreturn]] void FUN_7100a52f3c(void) { abort(); }

// 0x7100a701cc
[[noreturn]] void FUN_7100a701cc(void) { abort(); }

// 0x7100aac90c
[[noreturn]] void FUN_7100aac90c(void) { abort(); }

// 0x7101aa77b8
[[noreturn]] void FUN_7101aa77b8(void) { abort(); }

// ---- Global-dispatch wrapper ---------------------------------------------

// 0x7101520030 — dispatch to FUN_71014f8940
void FUN_7101520030(void)
{
    FUN_71014f8940(*DAT_71052c2760);
}

// ---- sv_animcmd lua_bind wrapper -----------------------------------------

// 0x7101fc2ca0
u32 FUN_7101fc2ca0(lua_State *param_1) { app::sv_animcmd::RUMBLE_ALL(param_1); return 0; }

// ---- Vtable dispatcher ---------------------------------------------------

// 0x7101008df0 — double-deref via *(param_2+0x20)+0x50, vtable +0x110 with const 0x200000e2
u64 FUN_7101008df0(u64 param_1, s64 param_2)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x50);
    (*(void(**)(s64 *, u32))(*plVar1 + 0x110))(plVar1, 0x200000e2);
    return 1;
}
