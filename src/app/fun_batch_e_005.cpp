#include "types.h"

// Batch decompiled via Ghidra MCP — pool-e, batch 005
// Range: 0x7100000000 — 0x7100FFFFFF

// ---- External declarations --------------------------------------------------

// Called functions
extern void FUN_71001f2180(s64);
extern void FUN_71001bee30(u64, u32);
extern void FUN_71001f24a0(s64);
extern void FUN_71001b0ab0(s64, const char *);
extern u64  FUN_7100230c50(void);
extern void FUN_7100230a20(u64);
extern u32  FUN_7100251150(s64, u64, u64, u64 *, u64);
extern u32  FUN_71002513c0(s64, u64, u64, u64 *, u64);
extern u32  FUN_710026d770(s64, u64, u16 *, u8 *);
extern s32  FUN_71002babe0(void);
extern u64  FUN_71002babd0(u32);
extern u64  FUN_71002babf0(u64, u32);
extern u32  FUN_71002c2f60(u32, u32);
extern void FUN_71002c2df0(u32);
extern void FUN_71002c2e50(u64, u32, u32);
extern u32  FUN_71002c2d60(u32, u32);
extern void FUN_71002c2bf0(u32);
extern void FUN_71002c2c30(u64, u32, u32);
extern void FUN_71037378c0(u64 *);
extern void FUN_710170de70(s64, u64, s64);
extern void FUN_710170f2a0(s64, u64, u64);
extern void FUN_710170d890(s64, u64, u64);
extern u8   FUN_71001b34a0(u32);
extern void FUN_71001b47e0(s64, s64, s64);
extern void FUN_71001b6470(s64, u32);
extern u64  FUN_71001b0fd0(void);
extern void FUN_71002ba5e0(u64);
extern void FUN_71002c1d20(u64);

// Data
extern void *PTR_FUN_7104f61778;
extern u8    DAT_7104348271;

// ---- Functions --------------------------------------------------------------

// 0x71001e59e0 — conditional init then dispatch
void FUN_71001e59e0(s64 param_1, u32 param_2)
{
    if (*(char *)(param_1 + 0x68) == '\0') {
        FUN_71001f2180(param_1);
    }
    FUN_71001bee30(*(u64 *)(param_1 + 8), param_2);
    *(u8 *)(param_1 + 0x69) = 0;
}

// 0x71001ecde0 — conditional init then store field
void FUN_71001ecde0(s64 param_1, u32 param_2)
{
    if (*(char *)(param_1 + 0x68) == '\0') {
        FUN_71001f2180(param_1);
    }
    *(u32 *)(param_1 + 0x10) = param_2;
    *(u8 *)(param_1 + 0x69) = 0;
}

// 0x71001f3690 — conditional init then dispatch
void FUN_71001f3690(u64 param_1, s64 param_2)
{
    if (*(char *)(param_2 + 0x69) == '\0') {
        FUN_71001f24a0(param_2);
    }
    FUN_71001b0ab0(param_1, (const char *)*(u64 *)(param_2 + 0x60));
}

// 0x7100230c10 — check flag then dispatch
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

// 0x7100251110 — wrapper: FUN_7100251150(param_1+0x140, ...) & 1
u32 FUN_7100251110(s64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    u32 uVar1;
    u64 local_18;

    local_18 = param_3;
    uVar1 = FUN_7100251150(param_1 + 0x140, param_2, param_5, &local_18, param_4);
    return uVar1 & 1;
}

// 0x7100251380 — wrapper: FUN_71002513c0(param_1+0x140, ...) & 1
u32 FUN_7100251380(s64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    u32 uVar1;
    u64 local_18;

    local_18 = param_3;
    uVar1 = FUN_71002513c0(param_1 + 0x140, param_2, param_5, &local_18, param_4);
    return uVar1 & 1;
}

// 0x710026d730 — build local args, call FUN_710026d770(+0x28) & 1
u32 FUN_710026d730(s64 param_1, u64 param_2, u16 param_3, u8 param_4)
{
    u32 uVar1;
    u8  local_18[4];
    u16 local_14[2];

    local_18[0] = param_4 & 1;
    local_14[0] = param_3;
    uVar1 = FUN_710026d770(param_1 + 0x28, param_2, local_14, local_18);
    return uVar1 & 1;
}

// 0x71002b3e80 — endian/swap helper
u64 FUN_71002b3e80(u64 param_1)
{
    s32 iVar1;
    u64 uVar2;
    u64 uVar3;

    iVar1 = FUN_71002babe0();
    if (iVar1 == 1) {
        return param_1 & 0xffffffff;
    }
    uVar2 = FUN_71002babd0((u32)param_1);
    uVar3 = FUN_71002babf0(uVar2, 1);
    return uVar3;
}

// 0x71002c2910 — 3-call dispatch
void FUN_71002c2910(s64 param_1, u32 param_2, u32 param_3)
{
    u32 uVar1;

    uVar1 = FUN_71002c2f60(param_2, param_3);
    FUN_71002c2df0(param_2);
    FUN_71002c2e50(*(u64 *)(param_1 + 0x10), param_2, uVar1);
}

// 0x71002c2960 — 3-call dispatch variant
void FUN_71002c2960(s64 param_1, u32 param_2, u32 param_3)
{
    u32 uVar1;

    uVar1 = FUN_71002c2d60(param_2, param_3);
    FUN_71002c2bf0(param_2);
    FUN_71002c2c30(*(u64 *)(param_1 + 0x18), param_2, uVar1);
}

// 0x71003a71f0 — vtable ptr init with linked list heads
void FUN_71003a71f0(u64 *param_1)
{
    *param_1 = (u64)&PTR_FUN_7104f61778;
    FUN_71037378c0(param_1 + 0xc);
    param_1[0xc] = 0;
    *(u32 *)(param_1 + 0xd) = 0xffffffff;
    FUN_71037378c0(param_1 + 10);
    *(u32 *)(param_1 + 0xb) = 0xffffffff;
    param_1[10] = 0;
}

// 0x7100254160 — copy byte field, conditional copy via FUN_710170de70
s64 FUN_7100254160(s64 param_1, s64 param_2)
{
    *(u8 *)(param_1 + 8) = *(u8 *)(param_2 + 8);
    if (param_1 != param_2) {
        FUN_710170de70(param_1 + 0x10, *(u64 *)(param_2 + 0x10), param_2 + 0x18);
    }
    return param_1;
}

// 0x7100261490 — copy fields, conditional copy via FUN_710170f2a0
s64 FUN_7100261490(s64 param_1, s64 param_2)
{
    *(u8 *)(param_1 + 8) = *(u8 *)(param_2 + 8);
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_2 + 0xc);
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
    if (param_1 != param_2) {
        FUN_710170f2a0(param_1 + 0x18, *(u64 *)(param_2 + 0x18), *(u64 *)(param_2 + 0x20));
    }
    return param_1;
}

// 0x710028af20 — copy byte fields, conditional copy via FUN_710170d890
s64 FUN_710028af20(s64 param_1, s64 param_2)
{
    *(u8 *)(param_1 + 8) = *(u8 *)(param_2 + 8);
    *(u8 *)(param_1 + 9) = *(u8 *)(param_2 + 9);
    if (param_1 != param_2) {
        FUN_710170d890(param_1 + 0x10, *(u64 *)(param_2 + 0x10), *(u64 *)(param_2 + 0x18));
    }
    return param_1;
}

// 0x7100213040 — vtable call at offset 0x18 with 8 args, return 1
u64 FUN_7100213040(s64 param_1, s64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    s64 *plVar1 = *(s64 **)(param_1 + 0x10);
    (*(void (*)(s64 *, s64, s32, s32, u8, u64, s32, u64))(*plVar1 + 0x18))
        (plVar1, param_2, 1, 0, *(u8 *)(param_2 + 0x42), param_3, 0, param_5);
    return 1;
}

// 0x71002134a0 — identical to FUN_7100213040 (different address)
u64 FUN_71002134a0(s64 param_1, s64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    s64 *plVar1 = *(s64 **)(param_1 + 0x10);
    (*(void (*)(s64 *, s64, s32, s32, u8, u64, s32, u64))(*plVar1 + 0x18))
        (plVar1, param_2, 1, 0, *(u8 *)(param_2 + 0x42), param_3, 0, param_5);
    return 1;
}

// 0x7100223fa0 — fill buffer with random bytes
u64 FUN_7100223fa0(u64 param_1, u8 *param_2, s64 param_3)
{
    u8 uVar1;

    if (param_3 != 0) {
        do {
            uVar1 = FUN_71001b34a0(0xff);
            param_3--;
            *param_2 = uVar1;
            param_2++;
        } while (param_3 != 0);
    }
    return 0;
}

// 0x71002b41f0 — single-call wrapper
void FUN_71002b41f0(u64 *param_1)
{
    FUN_71002ba5e0(*param_1);
}

// 0x71002b4b30 — single-call wrapper
void FUN_71002b4b30(u64 *param_1)
{
    FUN_71002c1d20(*param_1);
}

// 0x71002b8ca0 — no-op
void FUN_71002b8ca0(void)
{
    return;
}

// 0x71001b0f80 — conditional arithmetic based on mode flag
u64 FUN_71001b0f80(u32 *param_1)
{
    s32 iVar1;
    s32 iVar2;
    u64 uVar3;

    uVar3 = FUN_71001b0fd0();
    iVar2 = (s32)uVar3;
    if (iVar2 != 0) {
        uVar3 = 0x15fde20;
        if (iVar2 >= 0) {
            iVar1 = 0x1600530;
            if ((*param_1 & 0x7ff0000) != 0x720000) {
                iVar1 = 0x15fde20;
            }
            uVar3 = (u64)(u32)(iVar1 + iVar2);
        }
    }
    return uVar3;
}

// 0x71001b2f70 — conditional update via FUN_71001b47e0
s64 FUN_71001b2f70(s64 param_1, s64 param_2)
{
    if (param_1 != param_2) {
        FUN_71001b47e0(param_1, *(s64 *)(param_2 + 0x18), 0xffffffffffffffff);
    }
    return param_1;
}

// 0x71001b65c0 — conditional string dispatch
void FUN_71001b65c0(s64 param_1, u32 param_2)
{
    if (*(char *)(param_1 + 0x122) == '\0') {
        FUN_71001b6470(param_1, param_2 & 1);
        return;
    }
    if ((param_2 & 1) != 0) {
        FUN_71001b0ab0(param_1, (const char *)&DAT_7104348271);
        return;
    }
    FUN_71001b0ab0(param_1, "false");
}
