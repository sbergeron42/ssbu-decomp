#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100-0x7101 range, batch d5-014
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: abort/throw thunks, lua_bind wrappers, vtable dispatchers, misc

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" void FUN_7100404f60();
extern "C" void FUN_7100a24780();
extern "C" void FUN_71014ca790(u64);
extern "C" void FUN_710377a930(u32, s64);
extern "C" void FUN_710377ab90(s64);

struct lua_State;

namespace app {
    namespace sv_animcmd {
        void LAST_EFFECT_SET_WORK_INT(lua_State *);
        void HIT_NO(lua_State *);
        void REG_LANDING_SE(lua_State *);
    }
}

// ---- abort() / __throw_out_of_range thunks --------------------------------

// 0x710075fe4c
[[noreturn]] void FUN_710075fe4c(void) { abort(); }

// 0x7100ae41bc
[[noreturn]] void FUN_7100ae41bc(void) { abort(); }

// 0x7100e3526c
[[noreturn]] void FUN_7100e3526c(void) { abort(); }

// 0x71012030c4
[[noreturn]] void FUN_71012030c4(void) { abort(); }

// 0x710129580c
[[noreturn]] void FUN_710129580c(void) { abort(); }

// 0x7101b33640
[[noreturn]] void FUN_7101b33640(void) { abort(); }

// ---- sv_animcmd lua_bind wrappers ----------------------------------------

// 0x7101fba2e0
u64 FUN_7101fba2e0(lua_State *param_1) { app::sv_animcmd::LAST_EFFECT_SET_WORK_INT(param_1); return 0; }

// 0x7101fc0e70
u64 FUN_7101fc0e70(lua_State *param_1) { app::sv_animcmd::HIT_NO(param_1); return 0; }

// 0x7101fc3c80
u64 FUN_7101fc3c80(lua_State *param_1) { app::sv_animcmd::REG_LANDING_SE(param_1); return 0; }

// ---- Simple call wrapper -------------------------------------------------

// 0x7100a2c9d0 — call FUN_7100a24780, return 1
u64 FUN_7100a2c9d0(void)
{
    FUN_7100a24780();
    return 1;
}

// ---- Vtable dispatchers --------------------------------------------------

// 0x710165d960 — double-deref vtable +0x98 via *(param_2+0xe8), const 0x10000012, return==0
bool FUN_710165d960(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0xe8);
    s32 iVar1 = (*(s32(**)(s64 *, u32))(*obj + 0x98))(obj, 0x10000012);
    return iVar1 == 0;
}

// 0x71006c4410 — triple vtable dispatch: check bit, then two more calls with hash constants
void FUN_71006c4410(u64 param_1, s64 param_2)
{
    FUN_7100404f60();
    s64 *obj = *(s64 **)(param_2 + 0x50);
    u64 uVar3 = (*(u64(**)(s64 *, u32))(*obj + 0x108))(obj, 0x20000098);
    if ((uVar3 & 1) != 0) {
        return;
    }
    s64 *plVar1 = *(s64 **)(param_2 + 0x48);
    u32 uVar2 = (*(u32(**)(s64 *, u64, u64))(*obj + 0x250))(obj, 0x6e5ec7051ULL, 0x1edca940c7ULL);
    (*(void(**)(s64 *, u32, s32))(*plVar1 + 0x308))(plVar1, uVar2, 1);
}

// ---- Misc wrappers -------------------------------------------------------

// 0x71013bcc60 — FUN_710377a930(1.0f, +0x40), FUN_710377ab90 ×2, decrement counter
void FUN_71013bcc60(s64 param_1)
{
    s64 lVar1 = *(s64 *)(*(s64 *)(param_1 + 0x10) + 0x80);
    FUN_710377a930(0x3f800000U, lVar1 + 0x40);
    FUN_710377ab90(lVar1 + 0x4e0);
    FUN_710377ab90(lVar1 + 0x520);
    if (0 < *(s32 *)(param_1 + 0x1fc)) {
        *(s32 *)(param_1 + 0x1fc) = *(s32 *)(param_1 + 0x1fc) - 1;
    }
}

// 0x71014cb290 — iterate vector-like array (stride 2), call FUN_71014ca790 per entry
void FUN_71014cb290(s64 param_1)
{
    u64 *vec_inner = *(u64 **)(param_1 + 0x18);
    u64 *puVar1 = (u64 *)vec_inner[1];
    for (u64 *puVar2 = (u64 *)vec_inner[0]; puVar2 != puVar1; puVar2 += 2) {
        FUN_71014ca790(*puVar2);
    }
}

// 0x7101886de0 — bounds-checked array write via double-deref, abort on OOB
void FUN_7101886de0(s64 param_1)
{
    s64 lVar2 = *(s64 *)(param_1 + 0xc8);
    s64 lVar3 = *(s64 *)(lVar2 + 0x80);
    u32 uVar1 = *(u32 *)(lVar3 + 0x1fc);
    if (uVar1 < 0x13) {
        *(u32 *)(lVar3 + (s64)(s32)uVar1 * 4 + 0x1b0) = 0x13;
        *(u8 *)(lVar2 + 0x70) = 0;
        if (*(u32 *)(param_1 + 0xa4) < 0x13) {
            *(u32 *)(param_1 + (s64)(s32)*(u32 *)(param_1 + 0xa4) * 4 + 0x58) = 2;
            return;
        }
    }
    abort();
}

// 0x7101ee92f0 — write 0x8ffff... sentinel, bounds-checked array write to +0xb8 slot
void FUN_7101ee92f0(s64 param_1)
{
    s32 iVar1 = *(s32 *)(param_1 + 0x108);
    if (iVar1 != 0) {
        if ((iVar1 != 4) && (iVar1 != 6)) {
            *(u64 *)(param_1 + 0x1b8) = 0x8ffff0000000000ULL;
            u32 uVar2 = *(u32 *)(param_1 + 0x104);
            *(u32 *)(param_1 + 0x1c4) = 0;
            if (*(s8 *)(param_1 + 0x1cc) == '\0') {
                if (uVar2 < 0x13) {
                    *(u32 *)(param_1 + (s64)(s32)uVar2 * 4 + 0xb8) = 4;
                    return;
                }
            } else if (uVar2 < 0x13) {
                *(u32 *)(param_1 + (s64)(s32)uVar2 * 4 + 0xb8) = 6;
                return;
            }
            abort();
        }
        *(u64 *)(param_1 + 0x1b8) = 0x8ffff0000000000ULL;
        *(u32 *)(param_1 + 0x1c4) = 0;
    }
}
