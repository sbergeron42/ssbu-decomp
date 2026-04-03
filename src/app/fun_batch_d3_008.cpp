#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-008
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u64 PTR_DAT_71052a4180 HIDDEN;

// External FUN_* forward declarations
extern void FUN_710013e590();
extern u32  FUN_7100227700(u32);
extern void FUN_71001d0c80(u64, s64, u32);
extern u64  FUN_71001b4e00(u64, const char *);
extern u64  FUN_710022b360(u64, s64);
extern u64  FUN_710024cc10(u64, s64);
extern void FUN_71001b2f70(u64, s64);
extern void FUN_71001b4200(u64, u32 *);

// ---- Functions ---------------------------------------------------------------

// 0x71000f20e0 — ctor: parent init, clear 5 fields, set vtable (80 bytes)
void FUN_71000f20e0(s64 *param_1)
{
    u64 uVar1;

    FUN_710013e590();
    uVar1 = PTR_DAT_71052a4180;
    *(u32 *)(param_1 + 0x2d) = 0;
    param_1[0x27] = 0;
    param_1[0x28] = 0;
    param_1[0x29] = 0;
    param_1[0x2a] = 0;
    *param_1 = (s64)(uVar1 + 0x10);
    *(u8 *)((s64)param_1 + 0x16c) = 0;
    param_1[0x2e] = 0;
}

// 0x71002280d0 — bswap64: byte-swap both 32-bit halves via FUN_7100227700 (48 bytes)
u64 FUN_71002280d0(u64 param_1)
{
    s64 lVar1;
    u64 uVar2;

    lVar1 = FUN_7100227700((u32)param_1);
    uVar2 = FUN_7100227700(param_1 >> 0x20);
    return uVar2 & 0xffffffff | lVar1 << 0x20;
}

// 0x7100246338 — delegate: forward to FUN_71001d0c80 with field at +0x90 (32 bytes)
u64 FUN_7100246338(s64 param_1, u64 param_2, u64 param_3)
{
    FUN_71001d0c80(param_3, param_1, *(u32 *)(param_1 + 0x90));
    return 1;
}

// 0x710024a610 — type guard: skip if +0x18 is "AuthenticationInfo", else delegate (64 bytes)
u64 FUN_710024a610(u64 param_1, s64 param_2)
{
    u64 uVar1;
    u64 uVar2;

    uVar1 = FUN_71001b4e00(*(u64 *)(param_2 + 0x18), "AuthenticationInfo");
    if ((uVar1 & 1) != 0) {
        return 1;
    }
    uVar2 = FUN_710022b360(param_1, param_2);
    return uVar2;
}

// 0x7100255690 — type guard: skip if +0x18 is "MatchmakeSession", else delegate (64 bytes)
u64 FUN_7100255690(u64 param_1, s64 param_2)
{
    u64 uVar1;
    u64 uVar2;

    uVar1 = FUN_71001b4e00(*(u64 *)(param_2 + 0x18), "MatchmakeSession");
    if ((uVar1 & 1) != 0) {
        return 1;
    }
    uVar2 = FUN_710024cc10(param_1, param_2);
    return uVar2;
}

// 0x7100256ac0 — type guard: skip if +0x18 is "PersistentGathering", else delegate (64 bytes)
u64 FUN_7100256ac0(u64 param_1, s64 param_2)
{
    u64 uVar1;
    u64 uVar2;

    uVar1 = FUN_71001b4e00(*(u64 *)(param_2 + 0x18), "PersistentGathering");
    if ((uVar1 & 1) != 0) {
        return 1;
    }
    uVar2 = FUN_710024cc10(param_1, param_2);
    return uVar2;
}

// 0x7100282924 — delegate: forward param_1 and param_2+0x478 to FUN_71001b2f70 (32 bytes)
void FUN_7100282924(u64 param_1, s64 param_2)
{
    FUN_71001b2f70(param_1, param_2 + 0x478);
}

// 0x71002a9850 — NEX error map: switch NEX code → result code, call FUN_71001b4200 (256 bytes)
void FUN_71002a9850(u64 param_1, s64 param_2)
{
    u32 local_14;

    switch (param_2) {
    case 0x24bb:
    case 0x24bc:
        local_14 = 0x80720004;
        break;
    case 0x24bd:
        local_14 = 0x80720006;
        break;
    case 0x24be:
        local_14 = 0x80720005;
        break;
    case 0x24c0:
        local_14 = 0x80720007;
        break;
    case 0x24c1:
        local_14 = 0x8072000a;
        break;
    case 0x24c3:
        local_14 = 0x80720008;
        break;
    case 0x24c4:
        local_14 = 0x80720009;
        break;
    case 0x24ca:
        local_14 = 0x80720011;
        break;
    case 0x24cb:
        local_14 = 0x80720014;
        break;
    case 0x24d4:
        local_14 = 0x80720010;
        break;
    case 0x24ea:
        local_14 = 0x80720012;
        break;
    case 0x251b:
        local_14 = 0x8072000f;
        break;
    case 0x251c:
        local_14 = 0x8072000b;
        break;
    case 0x251d:
        local_14 = 0x8072000c;
        break;
    case 0x2527:
        local_14 = 0x8072000e;
        break;
    default:
        if (param_2 == 0x257f) {
            local_14 = 0x8072000d;
            break;
        }
        if (param_2 == 0) {
            local_14 = 0x10001;
            break;
        }
    case 0x24bf:
    case 0x24c2:
    case 0x24c5:
    case 0x24c6:
    case 0x24c7:
    case 0x24c8:
    case 0x24c9:
    case 0x24cc:
    case 0x24cd:
    case 0x24ce:
    case 0x24cf:
    case 0x24d0:
    case 0x24d1:
    case 0x24d2:
    case 0x24d3:
    case 0x24d5:
    case 0x24d6:
    case 0x24d7:
    case 0x24d8:
    case 0x24d9:
    case 0x24da:
    case 0x24db:
    case 0x24dc:
    case 0x24dd:
    case 0x24de:
    case 0x24df:
    case 0x24e0:
    case 0x24e1:
    case 0x24e2:
    case 0x24e3:
    case 0x24e4:
    case 0x24e5:
    case 0x24e6:
    case 0x24e7:
    case 0x24e8:
    case 0x24e9:
    case 0x24eb:
    case 0x24ec:
    case 0x24ed:
    case 0x24ee:
    case 0x24ef:
    case 0x24f0:
    case 0x24f1:
    case 0x24f2:
    case 0x24f3:
    case 0x24f4:
    case 0x24f5:
    case 0x24f6:
    case 0x24f7:
    case 0x24f8:
    case 0x24f9:
    case 0x24fa:
    case 0x24fb:
    case 0x24fc:
    case 0x24fd:
    case 0x24fe:
    case 0x24ff:
    case 0x2500:
    case 0x2501:
    case 0x2502:
    case 0x2503:
    case 0x2504:
    case 0x2505:
    case 0x2506:
    case 0x2507:
    case 0x2508:
    case 0x2509:
    case 0x250a:
    case 0x250b:
    case 0x250c:
    case 0x250d:
    case 0x250e:
    case 0x250f:
    case 0x2510:
    case 0x2511:
    case 0x2512:
    case 0x2513:
    case 0x2514:
    case 0x2515:
    case 0x2516:
    case 0x2517:
    case 0x2518:
    case 0x2519:
    case 0x251a:
    case 0x251e:
    case 0x251f:
    case 0x2520:
    case 0x2521:
    case 0x2522:
    case 0x2523:
    case 0x2524:
    case 0x2525:
    case 0x2526:
        local_14 = 0x80720001;
    }
    FUN_71001b4200(param_1, &local_14);
}
