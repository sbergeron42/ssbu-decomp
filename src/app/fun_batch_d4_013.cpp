#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-013
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: binary search, date/time calcs, init helpers, comparison, vtable calls

// ---- External declarations -----------------------------------------------

// nn::socket SDK
extern "C" long nnsocketRecv();
extern "C" int nnsocketGetLastErrno();

// Creator/factory helpers
extern "C" s64 FUN_71000b1b90();
extern "C" s64 FUN_7100130810(s64, s64);
extern "C" void FUN_7100194810(s64);
extern "C" void FUN_710017bb40(s64);
extern "C" void FUN_7100189a10(s64);
extern "C" void FUN_710019f980(s64);

// Misc helper externs
extern "C" s64 FUN_7100039590(u64);
extern "C" s64 FUN_71000399e0(u64);
extern "C" void FUN_71000bb5d0(u64 *);
extern "C" u16 FUN_710003e210(u32);
extern "C" void FUN_71002282c0(u64);
extern "C" s64 FUN_71002282f0(u64);
extern "C" s32 FUN_7100228310(u64);
extern "C" void FUN_7100228130(u64);
extern "C" u64 FUN_7100230c50();
extern "C" void FUN_7100230a20(u64);
extern "C" void FUN_71002ba5e0(u64);
extern "C" void FUN_71002c1d20(u64);
extern "C" s32 FUN_71001c4c40(u32, s64, s64, u64 *, u64, s32);
extern "C" void FUN_71001b4200(u8 *, u32 *);
extern "C" void FUN_71001e1770(u64, u32, u8 *);
extern "C" void FUN_71001f2180(s64);
extern "C" s64 FUN_71001beb00(s64);
extern "C" u64 FUN_71001b0fd0();
extern "C" void FUN_7100187f50();

// For FUN_7100130f30
extern "C" void FUN_7100133850(s64 *, u64, s32, s64 *, u64, s32, u32);
extern "C" s64 *FUN_71001352b0(u64);
extern "C" void FUN_710013ba30(s64 *);
extern "C" void FUN_710013ba40(s64 *);
extern "C" void FUN_7100131060(s64 *);

// Global data pointers
extern u64 PTR_DAT_71052a3f30;  // double-deref ulong* for FUN_71001b0960
extern u64 PTR_DAT_71052a4bd8;  // for FUN_7100130f30
extern u64 PTR_DAT_71052a4bb0;  // for FUN_7100130f30
extern u64 PTR_DAT_71052a4220;  // for FUN_71000f4d30
extern s64 *DAT_71052b60e8;     // base object pointer for FUN_710033ba50

// ---- Functions ---------------------------------------------------------------

// 0x710003a790 — return sum of two sub-object sizes
s64 FUN_710003a790(s64 param_1)
{
    s64 lVar1;
    s64 lVar2;

    lVar1 = FUN_7100039590(*(u64 *)(param_1 + 8));
    lVar2 = FUN_71000399e0(*(u64 *)(param_1 + 0x20));
    return lVar2 + lVar1;
}

// 0x71000cf1d0 — set entry flag and store callback result (small-addr DAT pattern)
void FUN_71000cf1d0(s64 param_1)
{
    u64 local_18;

    *(u8 *)(param_1 + 0x1850) = 1;
    local_18 = 0;
    FUN_71000bb5d0(&local_18);
    *(u64 *)(param_1 + 0x1858) = local_18;
}

// 0x71000f4d30 — init vtable pointer from global (PTR_DAT + 0x10)
void FUN_71000f4d30(s64 *param_1)
{
    FUN_7100187f50();
    *param_1 = (s64)(PTR_DAT_71052a4220 + 0x10);
}

// 0x710007bdc0 — binary search: find glyph ID in font cmap table
u32 FUN_710007bdc0(s64 param_1, u32 param_2)
{
    s64 lVar1;
    u32 *puVar2;
    s16 sVar3;
    s32 iVar4;
    u32 uVar5;
    u32 *puVar6;
    u32 *puVar7;
    s64 lVar8;

    uVar5 = *(u32 *)(*(s64 *)(param_1 + 0x20) + 0x14);
    if (uVar5 == 0) {
        return 0xffff;
    }
    while( true ) {
        puVar6 = (u32 *)(*(s64 *)(param_1 + 0x18) + (u64)uVar5);
        uVar5 = *puVar6;
        if ((uVar5 <= param_2) && (param_2 <= puVar6[1])) break;
        uVar5 = puVar6[3];
        if (uVar5 == 0) {
            return 0xffff;
        }
    }
    iVar4 = *(s32 *)(param_1 + 0x80);
    if (iVar4 != 0) {
        if (iVar4 < 1) {
            return 0xffff;
        }
        lVar8 = 0;
        while ((lVar1 = param_1 + lVar8 * 4, param_2 < *(u32 *)(lVar1 + 0x84) ||
               (*(u32 *)(lVar1 + 0xc4) < param_2))) {
            lVar8 = lVar8 + 1;
            if (iVar4 <= lVar8) {
                return 0xffff;
            }
        }
    }
    sVar3 = (s16)puVar6[2];
    if (sVar3 == 2) {
        puVar7 = puVar6 + 5;
        puVar6 = puVar7 + (u64)(u16)puVar6[4] * 2 + -2;
        if (puVar7 <= puVar6) {
            do {
                while( true ) {
                    lVar8 = (s64)puVar6 - (s64)puVar7 >> 3;
                    if (lVar8 < 0) {
                        lVar8 = lVar8 + 1;
                    }
                    puVar2 = puVar7 + (lVar8 >> 1) * 2;
                    uVar5 = *puVar2;
                    if (param_2 <= uVar5) break;
                    puVar7 = puVar2 + 2;
                    if (puVar6 < puVar7) {
                        return 0xffff;
                    }
                }
                if (param_2 > uVar5 || uVar5 == param_2) {
                    return (u32)(u16)puVar2[1];
                }
                puVar6 = puVar2 + -2;
            } while (puVar7 <= puVar6);
        }
    }
    else {
        if (sVar3 == 1) {
            return (u32)*(u16 *)((s64)puVar6 + (s64)(s32)(param_2 - uVar5) * 2 + 0x10);
        }
        if (sVar3 == 0) {
            return (u32)(u16)puVar6[4] + (param_2 - uVar5);
        }
    }
    return 0xffff;
}

// 0x7100130f30 — allocate and init a stream/socket object
s64 *FUN_7100130f30(s64 *param_1, u64 param_2, u64 param_3, u32 param_4)
{
    s32 iVar1;
    s64 *plVar2;
    s64 *plVar3;

    if (0x128 < (param_2 & 0xfffffffffffffff8ULL)) {
        FUN_7100133850(param_1, param_3, 0, param_1, param_2 & 0xfffffffffffffff8ULL, 1, param_4 & 1);
        *(u32 *)((s64)param_1 + 0xd4) = 0;
        *param_1 = (s64)(PTR_DAT_71052a4bd8 + 0x10);
        param_1[0x1b] = (s64)(param_1 + 0x1b);
        param_1[0x1c] = (s64)(param_1 + 0x1b);
        param_1[0x1f] = (s64)(param_1 + 0x1e);
        param_1[0x20] = -0x100000000LL;
        param_1[0x1d] = -0x100000000LL;
        param_1[0x1e] = (s64)(param_1 + 0x1e);
        if ((*(u8 *)(param_1 + 0x1a) & 1) == 0) {
            plVar3 = (s64 *)0x0;
            *(u32 *)((s64)param_1 + 0xec) = 0;
            *(u32 *)((s64)param_1 + 0x104) = 0;
            iVar1 = (s32)param_1[0x11];
        }
        else {
            plVar3 = param_1 + 0x12;
            FUN_710013ba30(plVar3);
            *(u32 *)((s64)param_1 + 0xec) = 0;
            *(u32 *)((s64)param_1 + 0x104) = 0;
            FUN_710013ba40(plVar3);
            if ((*(u8 *)(param_1 + 0x1a) & 1) == 0) {
                plVar3 = (s64 *)0x0;
                iVar1 = (s32)param_1[0x11];
            }
            else {
                FUN_710013ba30(plVar3);
                iVar1 = (s32)param_1[0x11];
            }
        }
        if (iVar1 == 1) {
            plVar2 = param_1 + 0x21;
        }
        else {
            plVar2 = (s64 *)param_1[6];
        }
        *plVar2 = 0;
        plVar2[1] = 0;
        *(u32 *)(plVar2 + 2) = 0;
        plVar2[3] = 0;
        plVar2[3] = param_1[7] + -0x128;
        FUN_7100131060(param_1);
        if (plVar3 != (s64 *)0x0) {
            FUN_710013ba40(plVar3);
        }
        return param_1;
    }
    return (s64 *)0x0;
}

// 0x7100179500 — create RPC session object (type 0x118)
s64 FUN_7100179500(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = (u64)FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x118, (s64)uVar1);
    if (lVar2 != 0) {
        FUN_7100194810(lVar2);
    }
    return lVar2;
}

// 0x7100179b30 — create RPC session object (type 0xb8)
s64 FUN_7100179b30(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = (u64)FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xb8, (s64)uVar1);
    if (lVar2 != 0) {
        FUN_710017bb40(lVar2);
    }
    return lVar2;
}

// 0x7100194390 — create RPC session object (type 0xf0)
s64 FUN_7100194390(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = (u64)FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xf0, (s64)uVar1);
    if (lVar2 != 0) {
        FUN_7100189a10(lVar2);
    }
    return lVar2;
}

// 0x7100194790 — create RPC session object (type 0x1130)
s64 FUN_7100194790(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = (u64)FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x1130, (s64)uVar1);
    if (lVar2 != 0) {
        FUN_710019f980(lVar2);
    }
    return lVar2;
}

// 0x71001ae0d0 — zero-fill transport struct fields
void FUN_71001ae0d0(u64 *param_1)
{
    *param_1 = 0;
    param_1[1] = 0;
    FUN_71000bb5d0(param_1 + 3);
    param_1[3] = 0;
    param_1[4] = 0;
    FUN_71000bb5d0(param_1 + 3);
    param_1[6] = 0;
    *(u32 *)(param_1 + 7) = 0;
    *(u32 *)((s64)param_1 + 0x2c) = 0;
    param_1[8] = 0;
    *(u32 *)(param_1 + 9) = 0;
}

// 0x71001b0960 — convert packed date/time fields to Unix timestamp
s64 FUN_71001b0960(u64 *param_1)
{
    u32 uVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    u32 uVar5;
    u64 uVar6;
    u32 uVar7;
    s32 iVar8;

    uVar6 = *param_1;
    if (uVar6 == **(u64 **)PTR_DAT_71052a3f30) {
        return 0;
    }
    uVar5 = (u32)uVar6 >> 0x16 & 0xf;
    iVar8 = -0x7d1;
    if (2 < uVar5) {
        iVar8 = -2000;
    }
    uVar1 = iVar8 + ((u32)(uVar6 >> 0x1a) & 0x3fff);
    iVar8 = 9;
    if (2 < uVar5) {
        iVar8 = -3;
    }
    uVar7 = 1;
    if (((s32)uVar1 < 0) && ((s32)uVar1 % 400 != 0)) {
        if ((s32)uVar1 % 100 == 0) {
            uVar7 = 0;
        }
        else {
            uVar7 = (u32)(((s32)uVar1 & 3) == 0);
        }
    }
    iVar3 = ((s32)uVar1 / 100) * 0x23ab1;
    iVar2 = iVar3 + 3;
    if (-1 < iVar3) {
        iVar2 = iVar3;
    }
    iVar4 = ((s32)uVar1 % 100) * 0x5b5;
    iVar3 = iVar4 + 3;
    if (-1 < iVar4) {
        iVar3 = iVar4;
    }
    return (uVar6 >> 6 & 0x3f) * 0x3c + (uVar6 & 0x3f | 0x386d4380) +
           (uVar6 >> 0xc & 0x1f) * 0xe10 +
           (s64)(s32)(((u32)uVar6 >> 0x11 & 0x1f) + (iVar3 >> 2) + (iVar2 >> 2) +
                      (s32)((iVar8 + (s32)uVar5) * 0x99 + 2) / 5 + uVar7 + 0x3a) * 0x15180;
}

// 0x71001b0f80 — compute NTP offset with calendar correction
u64 FUN_71001b0f80(u32 *param_1)
{
    s32 iVar1;
    s32 iVar2;
    u64 uVar3;

    uVar3 = FUN_71001b0fd0();
    iVar2 = (s32)uVar3;
    if (iVar2 != 0) {
        uVar3 = 0x15fde20;
        if (-1 < iVar2) {
            iVar1 = 0x1600530;
            if ((*param_1 & 0x7ff0000) != 0x720000) {
                iVar1 = 0x15fde20;
            }
            uVar3 = (u64)(u32)(iVar1 + iVar2);
        }
    }
    return uVar3;
}

// 0x71001c04e0 — network state machine: set connection phase from event code
u64 FUN_71001c04e0(s64 param_1, u32 param_2)
{
    u64 uVar1;
    u64 uVar2;

    uVar1 = 0;
    switch(param_2) {
    case 0:
        uVar1 = 1;
    default:
        return uVar1;
    case 4:
        break;
    case 5:
        if (*(s32 *)(param_1 + 0xc0) != 0) {
            return 0;
        }
        uVar2 = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0xb0) + 0x10)) + 0x48))();
        if ((uVar2 & 1) != 0) {
            return 0;
        }
        *(u32 *)(param_1 + 0xc0) = 2;
        return 0;
    case 6:
        if (*(s32 *)(param_1 + 0xc0) != 0) {
            return 0;
        }
        uVar2 = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0xb0) + 0x10)) + 0x48))();
        if ((uVar2 & 1) != 0) {
            return 0;
        }
        *(u32 *)(param_1 + 0xc0) = 3;
        return 0;
    case 7:
        if (*(s32 *)(param_1 + 0xc0) != 0) {
            return 0;
        }
        uVar2 = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0xb0) + 0x10)) + 0x48))();
        if ((uVar2 & 1) != 0) {
            return 0;
        }
        *(u32 *)(param_1 + 0xc0) = 4;
        return 0;
    case 8:
        if (*(s32 *)(param_1 + 0xc0) != 0) {
            return 0;
        }
        uVar2 = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0xb0) + 0x10)) + 0x48))();
        if ((uVar2 & 1) != 0) {
            return 0;
        }
        *(u32 *)(param_1 + 0xc0) = 5;
        return 0;
    case 9:
        if (*(s32 *)(param_1 + 0xc0) != 0) {
            return 0;
        }
        uVar2 = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0xb0) + 0x10)) + 0x48))();
        if ((uVar2 & 1) != 0) {
            return 0;
        }
        *(u32 *)(param_1 + 0xc0) = 6;
        return 0;
    }
    if (*(s32 *)(param_1 + 0xc0) != 0) {
        return 0;
    }
    uVar2 = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_1 + 0xb0) + 0x10)) + 0x48))();
    if ((uVar2 & 1) != 0) {
        return 0;
    }
    *(u32 *)(param_1 + 0xc0) = 1;
    return 0;
}

// 0x71001c5010 — decompress range into output field
void FUN_71001c5010(u32 param_1, s64 param_2, u64 param_3)
{
    s32 iVar1;
    u64 local_18;

    local_18 = 0;
    iVar1 = FUN_71001c4c40(param_1,
                           *(s64 *)(param_2 + 0x10) + *(s64 *)(param_2 + 0x28),
                           *(s64 *)(param_2 + 0x20) - *(s64 *)(param_2 + 0x28),
                           &local_18, param_3, 1);
    if (iVar1 != 0) {
        return;
    }
    *(u64 *)(param_2 + 0x18) = local_18;
}

// 0x71001e1830 — build and dispatch error result with code 0x800300d2
void FUN_71001e1830(u64 param_1, u32 param_2)
{
    u32 local_3c;
    u8 auStack_38[24];

    local_3c = 0x800300d2;
    FUN_71001b4200(auStack_38, &local_3c);
    FUN_71001e1770(param_1, param_2, auStack_38);
}

// 0x71001ecde0 — set connection mode field, clear flag if needed
void FUN_71001ecde0(s64 param_1, u32 param_2)
{
    if (*(s8 *)(param_1 + 0x68) == '\0') {
        FUN_71001f2180(param_1);
    }
    *(u32 *)(param_1 + 0x10) = param_2;
    *(u8 *)(param_1 + 0x69) = 0;
}

// 0x710021a4f0 — compare two objects by timestamp then ID then flag
u8 FUN_710021a4f0(s64 param_1, s64 param_2)
{
    s64 lVar1;
    s64 lVar2;

    lVar1 = FUN_71001beb00(param_1);
    lVar2 = FUN_71001beb00(param_2);
    if (lVar1 < lVar2) {
        return 1;
    }
    lVar1 = FUN_71001beb00(param_1);
    lVar2 = FUN_71001beb00(param_2);
    if ((lVar1 == lVar2) && (*(u32 *)(param_1 + 0x88) < *(u32 *)(param_2 + 0x88))) {
        return 1;
    }
    lVar1 = FUN_71001beb00(param_1);
    lVar2 = FUN_71001beb00(param_2);
    if (lVar1 != lVar2) {
        return 0;
    }
    if (*(s32 *)(param_1 + 0x88) == *(s32 *)(param_2 + 0x88)) {
        return *(u8 *)(param_1 + 0x90) < *(u8 *)(param_2 + 0x90);
    }
    return 0;
}

// 0x71002263c0 — write 8 u64 fields from array into small-addr offsets
void FUN_71002263c0(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    u64 uVar2;
    u64 uVar3;

    uVar1 = *param_2;
    uVar3 = param_2[1];
    uVar2 = param_2[2];
    *(u64 *)(param_1 + 0x10d8) = param_2[3];
    *(u64 *)(param_1 + 0x10d0) = uVar2;
    *(u64 *)(param_1 + 0x10c8) = uVar3;
    *(u64 *)(param_1 + 0x10c0) = uVar1;
    uVar1 = param_2[4];
    uVar3 = param_2[5];
    uVar2 = param_2[6];
    *(u64 *)(param_1 + 0x10f8) = param_2[7];
    *(u64 *)(param_1 + 0x10f0) = uVar2;
    *(u64 *)(param_1 + 0x10e8) = uVar3;
    *(u64 *)(param_1 + 0x10e0) = uVar1;
}

// 0x7100227510 — pop next pending frame from queue
s64 FUN_7100227510(s64 param_1)
{
    s32 iVar1;
    s64 lVar2;

    if ((*(u8 *)(param_1 + 0x11) >> 1 & 1) == 0) {
        lVar2 = FUN_71002282f0(0);
        FUN_71002282c0(*(u64 *)(param_1 + 0x88));
        return lVar2;
    }
    iVar1 = FUN_7100228310(*(u64 *)(param_1 + 0x88));
    if (iVar1 == 0) {
        do {
            lVar2 = FUN_71002282f0(*(u64 *)(param_1 + 0x88));
            FUN_71002282c0(*(u64 *)(param_1 + 0x88));
            if (*(s8 *)(lVar2 + 1) == '\b') {
                return lVar2;
            }
            if (lVar2 != 0) {
                FUN_7100228130(*(u64 *)(lVar2 + 8));
                FUN_7100228130(lVar2);
            }
            iVar1 = FUN_7100228310(*(u64 *)(param_1 + 0x88));
        } while (iVar1 == 0);
        return 0;
    }
    return 0;
}

// 0x7100230c10 — check condition and delegate on failure
u64 FUN_7100230c10(u64 param_1)
{
    u64 uVar1;

    uVar1 = FUN_7100230c50();
    if ((uVar1 & 1) != 0) {
        return 1;
    }
    FUN_7100230a20(param_1);
    return 0;
}

// 0x71002b41f0 — forward call to sub-object's cleanup
void FUN_71002b41f0(u64 *param_1)
{
    FUN_71002ba5e0(*param_1);
}

// 0x71002b4b30 — forward call to sub-object's teardown
void FUN_71002b4b30(u64 *param_1)
{
    FUN_71002c1d20(*param_1);
}

// 0x71002b8ca0 — stub (no-op)
void FUN_71002b8ca0(void)
{
    return;
}

// 0x710033ba50 — look up stage/world object pointer by region slot index
s64 FUN_710033ba50(u32 param_1)
{
    s64 lVar1;
    s64 lVar2;

    switch(param_1) {
    case 0:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x728);
        goto joined_r0x00710033baa8;
    case 1:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x778);
joined_r0x00710033baa8:
        if (lVar1 != 0) {
            return lVar1;
        }
        goto LAB_710033baac;
    case 2:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x7c8);
        break;
    case 3:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x818);
        break;
    case 4:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x868);
        break;
    case 5:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x8b8);
        break;
    case 6:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x908);
        break;
    case 7:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x958);
        break;
    case 8:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x9a8);
        break;
    case 9:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x9f8);
        break;
    case 10:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xa48);
        break;
    case 0xb:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xa98);
        break;
    case 0xc:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xae8);
        break;
    case 0xd:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xb38);
        break;
    case 0xe:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xb88);
        break;
    case 0xf:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xbd8);
        break;
    case 0x10:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xc28);
        break;
    case 0x11:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xc78);
        break;
    case 0x12:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xcc8);
        break;
    case 0x13:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xd18);
        break;
    case 0x14:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xd68);
        break;
    case 0x15:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xdb8);
        break;
    case 0x16:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xe08);
        break;
    case 0x17:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xe58);
        break;
    case 0x18:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xea8);
        break;
    case 0x19:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xef8);
        break;
    case 0x1a:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xf48);
        break;
    case 0x1b:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xf98);
        break;
    case 0x1c:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0xfe8);
        break;
    case 0x1d:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1038);
        break;
    case 0x1e:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1088);
        break;
    case 0x1f:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x10d8);
        break;
    case 0x20:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1128);
        break;
    case 0x21:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1178);
        break;
    case 0x22:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x11c8);
        break;
    case 0x23:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1218);
        break;
    case 0x24:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1268);
        break;
    case 0x25:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x12b8);
        break;
    case 0x26:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1308);
        break;
    case 0x27:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1358);
        break;
    case 0x28:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x13a8);
        break;
    case 0x29:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x13f8);
        break;
    case 0x2a:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1448);
        break;
    case 0x2b:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1498);
        break;
    case 0x2c:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x14e8);
        break;
    case 0x2d:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1538);
        break;
    case 0x2e:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1588);
        break;
    case 0x2f:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x15d8);
        break;
    case 0x30:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1628);
        break;
    case 0x31:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1678);
        break;
    case 0x32:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x16c8);
        break;
    case 0x33:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1718);
        break;
    case 0x34:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1768);
        break;
    case 0x35:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x17b8);
        break;
    case 0x36:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1808);
        break;
    case 0x37:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1858);
        break;
    case 0x38:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x18a8);
        break;
    case 0x39:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x18f8);
        break;
    case 0x3a:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1948);
        break;
    case 0x3b:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1998);
        break;
    case 0x3c:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x19e8);
        break;
    case 0x3d:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1a38);
        break;
    case 0x3e:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1a88);
        break;
    case 0x3f:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1ad8);
        break;
    case 0x40:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1b28);
        break;
    case 0x41:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1b78);
        break;
    case 0x42:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1bc8);
        break;
    case 0x43:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1c18);
        break;
    case 0x44:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1c68);
        break;
    case 0x45:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1cb8);
        break;
    case 0x46:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1d08);
        break;
    case 0x47:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1d58);
        break;
    case 0x48:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1da8);
        break;
    case 0x49:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1df8);
        break;
    case 0x4a:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1e48);
        break;
    case 0x4b:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1e98);
        break;
    case 0x4c:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1ee8);
        break;
    case 0x4d:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1f38);
        break;
    case 0x4e:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1f88);
        break;
    case 0x4f:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x1fd8);
        break;
    case 0x50:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2028);
        break;
    case 0x51:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2078);
        break;
    case 0x52:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x20c8);
        break;
    case 0x53:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2118);
        break;
    case 0x54:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2168);
        break;
    case 0x55:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x21b8);
        break;
    case 0x56:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2208);
        break;
    case 0x57:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2258);
        break;
    case 0x58:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x22a8);
        break;
    case 0x59:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x22f8);
        break;
    case 0x5a:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2348);
        break;
    case 0x5b:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2398);
        break;
    case 0x5c:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x23e8);
        break;
    case 0x5d:
        lVar2 = *DAT_71052b60e8;
        lVar1 = *(s64 *)(lVar2 + 0x2438);
        break;
    default:
        lVar2 = *DAT_71052b60e8;
        goto LAB_710033baac;
    }
    if (lVar1 == 0) {
LAB_710033baac:
        lVar1 = lVar2 + 0x6e8;
    }
    return lVar1;
}

// 0x7100358c20 — check if move/attack is executable given state flags
u32 FUN_7100358c20(s64 param_1, u32 param_2)
{
    u32 uVar1;
    u8 bVar2;
    u32 uVar3;

    uVar1 = *(u32 *)(param_1 + 0x58);
    if ((uVar1 >> 0xc & 1) != 0) {
        uVar3 = 0;
        if ((param_2 & 1) != 0) {
            uVar3 = (u32)((uVar1 & 0x400) == 0);
        }
        return uVar3;
    }
    uVar3 = 0;
    switch(*(u32 *)(param_1 + 0x28)) {
    case 5:
        bVar2 = *(u8 *)(param_1 + 0x68);
        goto joined_r0x007100358dd4;
    case 0xc:
        goto switchD_7100358c4c_caseD_c;
    case 0x1c:
        if ((*(u8 *)(param_1 + 0x68) & 1) != 0) {
            return 0;
        }
        break;
    case 0x22:
        if ((*(u8 *)(param_1 + 0x68) >> 2 & 1) == 0) {
            return 0;
        }
        break;
    case 0x25:
        if ((uVar1 >> 4 & 1) != 0) {
            return 0;
        }
        break;
    case 0x27:
        if ((*(u8 *)(param_1 + 0x68) >> 2 & 1) != 0) {
            return 0;
        }
        break;
    case 0x29:
        if ((*(u8 *)(param_1 + 0x68) & 1) != 0) {
            return 0;
        }
        break;
    case 0x2b:
    case 0x30:
    case 0x46:
        bVar2 = *(u8 *)(param_1 + 0x68) >> 3;
        goto joined_r0x007100358dd4;
    case 0x2d:
        bVar2 = *(u8 *)(param_1 + 0x68) >> 2;
        goto joined_r0x007100358dd4;
    case 0x31:
        if ((*(u8 *)(param_1 + 0x68) >> 1 & 1) != 0) {
            return 0;
        }
        break;
    case 0x37:
        if ((*(u8 *)(param_1 + 0x68) >> 3 & 1) != 0) {
            return 0;
        }
        break;
    case 0x38:
        if ((*(u8 *)(param_1 + 0x68) >> 2 & 1) == 0) {
            return 0;
        }
        break;
    case 0x3a:
        if ((*(u8 *)(param_1 + 0x68) >> 2 & 1) != 0) {
            return 0;
        }
        break;
    case 0x40:
        if ((*(u8 *)(param_1 + 0x68) >> 1 & 1) != 0) {
            return 1;
        }
        uVar3 = 0;
        if (((uVar1 >> 0xd & 1) == 0) && (*(s32 *)(param_1 + 0x74) != 0x10)) {
            if (*(s16 *)(param_1 + 0xcc) != 0) {
                return 1;
            }
            uVar3 = 0;
        }
        goto switchD_7100358c4c_caseD_c;
    case 0x4b:
        bVar2 = *(u8 *)(param_1 + 0x68) >> 1;
        goto joined_r0x007100358dd4;
    case 0x52:
        if (((uVar1 >> 4 & 1) != 0) && ((*(u32 *)(param_1 + 0x68) & 1) == 0)) {
            return 0;
        }
        break;
    case 0x53:
        uVar3 = param_2;
        if (*(s8 *)(param_1 + 0x68) < '\0') {
            return 1;
        }
        goto switchD_7100358c4c_caseD_c;
    case 0x54:
        bVar2 = *(u8 *)(param_1 + 0x68) >> 3;
joined_r0x007100358dd4:
        uVar3 = param_2;
        if ((bVar2 & 1) == 0) {
switchD_7100358c4c_caseD_c:
            return uVar3 & 1;
        }
        break;
    case 0x56:
        if ((uVar1 >> 4 & 1) != 0) {
            return 0;
        }
        break;
    case 0x57:
        if ((uVar1 >> 4 & 1) != 0) {
            return 0;
        }
        break;
    case 0x5a:
        if ((*(u8 *)(param_1 + 0x68) >> 1 & 1) != 0) {
            if ((param_2 & 1) != 0) {
                return (u32)((uVar1 & 0x400) == 0);
            }
            return 0;
        }
        break;
    case 0x5c:
        uVar3 = *(u32 *)(param_1 + 0x68) >> 2 & 1;
        if ((*(u32 *)(param_1 + 0x68) >> 2 & 1) == 0) {
            if ((param_2 & 1) != 0) {
                uVar3 = (u32)((uVar1 & 0x400) == 0);
            }
            return uVar3;
        }
        goto switchD_7100358c4c_caseD_c;
    }
    return 1;
}
