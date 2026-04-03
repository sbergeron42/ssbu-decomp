#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71031–0x71036 address range, batch d-018
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void FUN_7103540560(s64);
extern u64  FUN_7103266e10(u64, u64);
extern void FUN_710368b740(u64, u32);
extern void FUN_7103775b40(u64);   // used by FUN_710327af70 / FUN_71032a8c30 indirectly

// External data
extern s64  DAT_7105331f20;
extern u8   DAT_7104ada140[] __attribute__((visibility("hidden")));

// ---- Functions ---------------------------------------------------------------

// 0x71031c4294 — vtable call at *param_1+0x58 with three args (44 bytes)
void FUN_71031c4294(s64 *param_1)
{
    (*(void(*)(s64*, s32, s32))(*(s64*)(*param_1 + 0x58)))(param_1, 0x76, 0xffffffff);
}

// 0x71032694c0 — lookup from table by param_2, or return sentinel (48 bytes)
u64 FUN_71032694c0(u64 param_1, u32 param_2)
{
    if (param_2 < 0x7c) {
        return (u64)FUN_7103266e10(param_1, *(u64*)((s64)DAT_7104ada140 + (s64)(s32)param_2 * 8));
    }
    return 0x62ffff0000000000;
}

// 0x710327af70 — conditional reset of 0xffffff via nested pointer (64 bytes)
void FUN_710327af70(s64 param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 8);
    if (*(s32*)(lVar1 + 8) != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        *(u32*)(lVar1 + 8) = 0xffffff;
    }
}

// 0x71032a8c30 — conditional reset of 0xffffff via nested pointer (64 bytes)
void FUN_71032a8c30(s64 param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 8);
    if (*(s32*)(lVar1 + 8) != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        *(u32*)(lVar1 + 8) = 0xffffff;
    }
}

// 0x710357a0ac — vtable call at *param_1+0x160, no args (48 bytes)
void FUN_710357a0ac(s64 *param_1)
{
    (*(void(*)())(*(s64*)(*param_1 + 0x160)))();
}

// 0x710357ac7c — vtable call at *param_1+0x388, no args (36 bytes)
void FUN_710357ac7c(s64 *param_1)
{
    (*(void(*)())(*(s64*)(*param_1 + 0x388)))();
}

// 0x71036981fc — wrapper: FUN_710368b740(param_1, 1) (36 bytes)
u32 FUN_71036981fc(u64 param_1) { FUN_710368b740(param_1, 1); }
