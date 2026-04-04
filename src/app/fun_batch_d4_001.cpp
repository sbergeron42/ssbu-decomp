#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-001
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void nn__detail__UnexpectedDefaultImpl(const char*, const char*, s32);

// External FUN_* forward declarations
extern "C" char *FUN_71002c31d0(s64);
extern "C" void  FUN_71002c3200(void *);
extern "C" s64   FUN_71000339f0(u64);
extern "C" u32   FUN_71002c2f60(u32, u32);
extern "C" u32   FUN_71002c2d60(u32, u32);
extern "C" void  FUN_710003a0e0();
extern "C" void  FUN_710003a240(s64);
extern "C" void  FUN_7100313000(s64, s64, s64, s64, s64);
extern "C" void  FUN_7100313460(s64, s64, s64, s64, s64);

// External data
#pragma GCC visibility push(hidden)
extern u8 DAT_71044a7c80;
extern u8 DAT_71044a7cd0;
extern u8 DAT_71044a7d50;
#pragma GCC visibility pop

// ---- Functions ---------------------------------------------------------------
// 0x71002c2810 — table lookup by index (<3): return u64 entry from DAT table
u64 FUN_71002c2810(u32 param_1)
{
    if (param_1 < 3) {
        return *(u64 *)(&DAT_71044a7c80 + (s64)(s32)param_1 * 8);
    }
    /* WARNING: Subroutine does not return */
    nn__detail__UnexpectedDefaultImpl("", "", 0);
}

// 0x71002c2bf0 — table lookup by index (<12): return u32 entry from DAT table
u32 FUN_71002c2bf0(u32 param_1)
{
    if (param_1 < 0xc) {
        return *(u32 *)(&DAT_71044a7cd0 + (s64)(s32)param_1 * 4);
    }
    /* WARNING: Subroutine does not return */
    nn__detail__UnexpectedDefaultImpl("", "", 0);
}

// 0x71002c2c30 — switch returning pointer offset into param_1 by category (12 cases)
s64 FUN_71002c2c30(s64 param_1, u32 param_2, s32 param_3)
{
    switch(param_2) {
    case 0:
        return param_1 + (s64)param_3 * 0x58 + 0x6c;
    case 1:
        return param_1 + (s64)param_3 * 0x58 + 0x1cc;
    case 2:
        return param_1 + (s64)param_3 * 0x58 + 0x5ec;
    case 3:
        return param_1 + (s64)param_3 * 0x58 + 0xa0c;
    case 4:
        return param_1 + (s64)param_3 * 0x58 + 0x376c;
    case 5:
        return param_1 + (s64)param_3 * 0x58 + 0x64cc;
    case 6:
        return param_1 + (s64)param_3 * 0x58 + 0x922c;
    case 7:
        return param_1 + (s64)param_3 * 0x58 + 0xbf8c;
    case 8:
        return param_1 + (s64)param_3 * 0x58 + 0xecec;
    case 9:
        return param_1 + (s64)param_3 * 0x58 + 0x11a4c;
    case 10:
        return param_1 + (s64)param_3 * 0x58 + 0x11aa4;
    case 0xb:
        return param_1 + (s64)param_3 * 0x58 + 0x120d4;
    default:
        /* WARNING: Subroutine does not return */
        nn__detail__UnexpectedDefaultImpl("", "", 0);
    }
}

// 0x71002c2df0 — table lookup by index (<11): return u32 entry from DAT table
u32 FUN_71002c2df0(u32 param_1)
{
    if (param_1 < 0xb) {
        return *(u32 *)(&DAT_71044a7d50 + (s64)(s32)param_1 * 4);
    }
    /* WARNING: Subroutine does not return */
    nn__detail__UnexpectedDefaultImpl("", "", 0);
}

// 0x71002c2e50 — switch returning pointer offset into param_1 struct by category (11 cases)
u8 *FUN_71002c2e50(s64 param_1, u32 param_2, s32 param_3)
{
    switch(param_2) {
    case 0:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 100);
    case 1:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0xed4);
    case 2:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x159c);
    case 3:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x183c);
    case 4:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x1874);
    case 5:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x19c4);
    case 6:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x1b14);
    case 7:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x1d44);
    case 8:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x1d7c);
    case 9:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x2188);
    case 10:
        return (u8 *)(param_1 + (s64)param_3 * 0x1c + 0x2230);
    default:
        /* WARNING: Subroutine does not return */
        nn__detail__UnexpectedDefaultImpl("", "", 0);
    }
}

// 0x71002c1790 — get non-empty string: return ptr if not '\0', else null
char *FUN_71002c1790(s64 param_1, u32 param_2)
{
    char *pcVar1;
    char *pcVar2;

    pcVar2 = (char *)FUN_71002c31d0(param_1 + (u64)param_2 * 0x128 + 8);
    pcVar1 = (char *)0x0;
    if (*pcVar2 != '\0') {
        pcVar1 = pcVar2;
    }
    return pcVar1;
}

// 0x71002c1d20 — delegate: call FUN_71002c3200 with computed array offset
void FUN_71002c1d20(s64 param_1, u32 param_2)
{
    FUN_71002c3200((void *)(param_1 + (u64)param_2 * 0x128 + 8));
}
// 0x71002c1fe0 — delegate+offset: return FUN_71000339f0(*p) + p[2]
s64 FUN_71002c1fe0(u64 *param_1)
{
    s64 lVar1;

    lVar1 = FUN_71000339f0(*param_1);
    return lVar1 + param_1[2];
}
// 0x71002c2ba0 — divide field +0x2c by table[1] entry
u64 FUN_71002c2ba0(s64 param_1)
{
    u32 uVar1;
    u64 uVar2;
    u64 uVar3;

    uVar1 = *(u32 *)(param_1 + 0x2c);
    uVar3 = FUN_71002c2810(1);
    uVar2 = 0;
    if (uVar3 != 0) {
        uVar2 = uVar1 / uVar3;
    }
    return uVar2;
}

// 0x71002c2910 — dispatch: lookup type+size, then write to ptr+0x10 region
void FUN_71002c2910(s64 param_1, u32 param_2, u32 param_3)
{
    u32 uVar1;

    uVar1 = FUN_71002c2f60(param_2, param_3);
    FUN_71002c2df0(param_2);
    FUN_71002c2e50(*(u64 *)(param_1 + 0x10), param_2, uVar1);
}

// 0x71002c2960 — dispatch: lookup type+size, then write to ptr+0x18 region
void FUN_71002c2960(s64 param_1, u32 param_2, u32 param_3)
{
    u32 uVar1;

    uVar1 = FUN_71002c2d60(param_2, param_3);
    FUN_71002c2bf0(param_2);
    FUN_71002c2c30(*(u64 *)(param_1 + 0x18), param_2, uVar1);
}

// 0x71002c2f70 — init: call setup fns and set -1 sentinel at +0x120
void FUN_71002c2f70(s64 param_1)
{
    FUN_710003a0e0();
    FUN_710003a240(param_1 + 0xd8);
    *(u64 *)(param_1 + 0x120) = 0xffffffffffffffff;
}
// 0x710031321c — delegate: call FUN_7100313000 with 4 sub-offsets
u64 FUN_710031321c(s64 param_1, s64 param_2)
{
    FUN_7100313000(param_1, param_1 + 4, param_1 + 8, param_1 + 0xc, param_2 + -4);
    return 1;
}

// 0x710031367c — delegate: call FUN_7100313460 with 4 sub-offsets
u64 FUN_710031367c(s64 param_1, s64 param_2)
{
    FUN_7100313460(param_1, param_1 + 4, param_1 + 8, param_1 + 0xc, param_2 + -4);
    return 1;
}
