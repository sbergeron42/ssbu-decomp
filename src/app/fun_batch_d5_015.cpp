#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100-0x7101 range, batch d5-015
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: abort/throw thunks (200-224 byte range), lua_bind wrappers,
//           vtable dispatchers, nested CXA-guard functions

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" s32  __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);
extern "C" void FUN_7103783660(s64, u64, s32, s32);

extern "C" u64 DAT_7105323688;
extern "C" u64 DAT_7105323690;
extern "C" u64 DAT_7105323698;
extern "C" u64 DAT_71053236a0;
extern "C" u64 DAT_7105323718;
extern "C" u64 DAT_7105323720;

struct lua_State;

namespace app {
    namespace sv_animcmd {
        void EFFECT_GLOBAL(lua_State *);
        void SET_PLAY_INHIVIT(lua_State *);
    }
}

// ---- abort() / __throw_out_of_range thunks --------------------------------

// 0x71003bcc3c
[[noreturn]] void FUN_71003bcc3c(void) { abort(); }

// 0x71003bcd1c
[[noreturn]] void FUN_71003bcd1c(void) { abort(); }

// 0x71007800bc
[[noreturn]] void FUN_71007800bc(void) { abort(); }

// 0x7100a2819c
[[noreturn]] void FUN_7100a2819c(void) { abort(); }

// 0x7100a53adc
[[noreturn]] void FUN_7100a53adc(void) { abort(); }

// 0x7100a5455c
[[noreturn]] void FUN_7100a5455c(void) { abort(); }

// 0x7100a718ac
[[noreturn]] void FUN_7100a718ac(void) { abort(); }

// 0x7100baf91c
[[noreturn]] void FUN_7100baf91c(void) { abort(); }

// 0x7100baffac
[[noreturn]] void FUN_7100baffac(void) { abort(); }

// 0x7100ca73bc
[[noreturn]] void FUN_7100ca73bc(void) { abort(); }

// 0x7100d4355c
[[noreturn]] void FUN_7100d4355c(void) { abort(); }

// 0x7100d553ac
[[noreturn]] void FUN_7100d553ac(void) { abort(); }

// 0x7100d7cccc
[[noreturn]] void FUN_7100d7cccc(void) { abort(); }

// 0x7100da5e3c
[[noreturn]] void FUN_7100da5e3c(void) { abort(); }

// 0x7100e68a4c
[[noreturn]] void FUN_7100e68a4c(void) { abort(); }

// 0x7100f341cc
[[noreturn]] void FUN_7100f341cc(void) { abort(); }

// 0x7100f8692c
[[noreturn]] void FUN_7100f8692c(void) { abort(); }

// 0x7100fc2a8c
[[noreturn]] void FUN_7100fc2a8c(void) { abort(); }

// 0x710106a64c
[[noreturn]] void FUN_710106a64c(void) { abort(); }

// 0x71012b565c
[[noreturn]] void FUN_71012b565c(void) { abort(); }

// 0x71012ff75c
[[noreturn]] void FUN_71012ff75c(void) { abort(); }

// 0x7101899a40
[[noreturn]] void FUN_7101899a40(void) { abort(); }

// 0x7101bfe6d4
[[noreturn]] void FUN_7101bfe6d4(void) { abort(); }

// ---- sv_animcmd lua_bind wrappers ----------------------------------------

// 0x7101fb2690 — second registration of EFFECT_GLOBAL
u64 FUN_7101fb2690(lua_State *param_1) { app::sv_animcmd::EFFECT_GLOBAL(param_1); return 0; }

// 0x7101fc3bb0
u64 FUN_7101fc3bb0(lua_State *param_1) { app::sv_animcmd::SET_PLAY_INHIVIT(param_1); return 0; }

// ---- Vtable dispatchers --------------------------------------------------

// 0x710058b1f0 — vtable call at *param_1+0xc0, return vtable result
u32 FUN_710058b1f0(s64 *param_1)
{
    return (*(u32(**)())(*param_1 + 0xc0))();
}

// 0x7101b217d4 — call FUN_7103783660 with field+0x10, param_2, 0, 1
void FUN_7101b217d4(s64 param_1, u64 param_2)
{
    FUN_7103783660(param_1 + 0x10, param_2, 0, 1);
}

// 0x71013287d0 — double-deref vtable +0x110 via *(param_2+0x50), const 0x2100000d, return 1
u64 FUN_71013287d0(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0x50);
    (*(void(**)(s64 *, u32))(*obj + 0x110))(obj, 0x2100000d);
    return 1;
}

// 0x71004523f8 — vtable call at *param_1+0x248, return (result^1)&1
u32 FUN_71004523f8(s64 *param_1)
{
    u32 uVar1 = (*(u32(**)())(*param_1 + 0x248))();
    return (uVar1 ^ 1) & 1;
}

// ---- Nested CXA-guard init functions ------------------------------------

// 0x71017f3c50 — nested double-guard: init DAT_7105323698, set pointer DAT_71053236a0
u64 *FUN_71017f3c50(void)
{
    if (!(DAT_7105323688 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64 *)&DAT_7105323688);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64 *)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64 *)&DAT_7105323690);
                }
            }
            DAT_71053236a0 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64 *)&DAT_7105323688);
        }
    }
    return (u64 *)&DAT_71053236a0;
}

// 0x71017f4d20 — same inner guard, different outer guard, pointer DAT_7105323720
u64 *FUN_71017f4d20(void)
{
    if (!(DAT_7105323718 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64 *)&DAT_7105323718);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64 *)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64 *)&DAT_7105323690);
                }
            }
            DAT_7105323720 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64 *)&DAT_7105323718);
        }
    }
    return (u64 *)&DAT_7105323720;
}
