#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71001xxxxx range, batch d4-012
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: struct inits, bit ops, zero-fill, network ctx, vtable calls, bool checks

// ---- External declarations -----------------------------------------------

// Multiplier for time conversion (FUN_710015d240)
#pragma GCC visibility push(hidden)
extern u64 PTR_DAT_71052a3cd0;

// Network context pointer (FUN_7100162ce0 / 7100163d40)
extern u64 PTR_DAT_71052a3bd8;

// Vtable bases for struct inits
extern u64 PTR_DAT_71052a53d8;
extern u64 PTR_DAT_71052a53e0;
extern u64 PTR_DAT_71052a53e8;
extern u64 PTR_DAT_71052a5528;
#pragma GCC visibility pop

// FUN_710015e850 / FUN_710015e880 callees
extern "C" u64 FUN_710015f5c0(s64, s8);
extern "C" u64 FUN_710015f600(s64, s8, u32);

// FUN_7100181270 callees
extern "C" u64 FUN_71000b2850(s64);
extern "C" u64 FUN_71000b2b10(s64, s64);

// FUN_7100194e60 callee
extern "C" u64 FUN_7100157cf0(s64);

// ---- Functions ---------------------------------------------------------------

// 0x71001583c0 — write 3 u64 fields + 2 bit0 bytes into array entry at index field+0xa00
void FUN_71001583c0(s64 param_1, u64 param_2, u64 param_3, u64 param_4, u8 param_5, u8 param_6, u8 param_7)
{
    s64 lVar1;
    u32 uVar2;

    uVar2 = *(u32 *)(param_1 + 0xa00);
    lVar1 = param_1 + (u64)uVar2 * 0x20;
    *(u8 *)(lVar1 + 0x638) = param_6 & 1;
    *(u64 *)(lVar1 + 0x620) = param_2;
    *(u64 *)(lVar1 + 0x628) = param_3;
    *(u64 *)(lVar1 + 0x630) = param_4;
    *(u8 *)(lVar1 + 0x639) = param_7 & 1;
    *(u8 *)(lVar1 + 0x63a) = param_5 & 1;
    *(u32 *)(param_1 + 0xa00) = uVar2 + 1;
}

// 0x710015e850 — if ptr+0x50 != 0 and byte+0x38 != -3: call FUN_710015f5c0, else -1
u64 FUN_710015e850(s64 param_1)
{
    u64 uVar1;

    if ((*(s64 *)(param_1 + 0x50) != 0) && (*(s8 *)(param_1 + 0x38) != -3)) {
        uVar1 = FUN_710015f5c0(*(s64 *)(param_1 + 0x50), *(s8 *)(param_1 + 0x38));
        return uVar1;
    }
    return 0xffffffff;
}

// 0x710015fb50 — if *param_1 != 0: clear connection state fields (disconnect cleanup)
void FUN_710015fb50(s8 *param_1)
{
    if (*param_1 != '\0') {
        param_1[4] = -1;
        param_1[5] = -1;
        param_1[6] = -1;
        param_1[7] = -1;
        param_1[8] = -1;
        param_1[9] = -1;
        param_1[10] = -1;
        param_1[0xb] = -1;
        *param_1 = '\0';
        param_1[0x10] = '\0';
        param_1[0x11] = '\0';
        param_1[0x12] = '\0';
        param_1[0x13] = '\0';
        param_1[0x14] = '\0';
        param_1[0x15] = '\0';
        param_1[0x16] = '\0';
        param_1[0x17] = '\0';
        param_1[0x18] = '\0';
        param_1[0x48] = '\0';
        param_1[0x49] = '\0';
        param_1[0x4a] = '\0';
        param_1[0x4b] = '\0';
        param_1[0x4c] = '\0';
        param_1[0x4d] = '\0';
        param_1[0x4e] = '\0';
        param_1[0x4f] = '\0';
        param_1[0x1c] = '\0';
        param_1[0x1d] = '\0';
        param_1[0x1e] = '\0';
        param_1[0x1f] = '\0';
        param_1[0x20] = '\0';
        param_1[0x21] = '\0';
        param_1[0x22] = '\0';
        param_1[0x23] = '\0';
        param_1[0xc] = -1;
        param_1[0xd] = -1;
        param_1[0xe] = -1;
        param_1[0xf] = -1;
        param_1[0x50] = '\0';
        param_1[0x51] = '\0';
        param_1[0x52] = '\0';
        param_1[0x53] = '\0';
    }
}

// 0x7100162ce0 — clamp field+0xa4 to [1..0xfe]→0xff, write to PTR_DAT+0x2b6
void FUN_7100162ce0(s64 param_1)
{
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0xa4);
    if (0xfd < iVar1 - 1U) {
        iVar1 = 0xff;
    }
    *(s8 *)(PTR_DAT_71052a3bd8 + 0x2b6) = (s8)iVar1;
}

// 0x7100163d40 — clamp field+0xa4 to [1..0xfe]→0xff, write to PTR_DAT+0x2b7
void FUN_7100163d40(s64 param_1)
{
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0xa4);
    if (0xfd < iVar1 - 1U) {
        iVar1 = 0xff;
    }
    *(s8 *)(PTR_DAT_71052a3bd8 + 0x2b7) = (s8)iVar1;
}

// 0x7100164070 — zero-fill 0x400-byte region in 0x20-byte blocks, then clear trailing u32
void FUN_7100164070(s64 param_1)
{
    u64 *puVar1;
    s64 lVar2;

    lVar2 = 0;
    do {
        puVar1 = (u64 *)(param_1 + lVar2);
        lVar2 = lVar2 + 0x20;
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        *(u32 *)(puVar1 + 3) = 0;
        *(u8 *)((s64)puVar1 + 0x1c) = 0;
    } while (lVar2 != 0x400);
    *(u32 *)(param_1 + 0x400) = 0;
}

// 0x7100174530 — call vtable[0x30], then clear byte at param_1+9
void FUN_7100174530(s64 *param_1)
{
    (**(void(**)())(*param_1 + 0x30))();
    *(u8 *)((s64)param_1 + 9) = 0;
}

// 0x7100174cb0 — true if byte+8 != 0 and nested ptr field+0x418 != 0
u8 FUN_7100174cb0(s64 param_1)
{
    if (*(s8 *)(param_1 + 8) == '\0') {
        return 0;
    }
    if (*(s64 *)(param_1 + 0x18) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 0x18) + 0x418) != 0;
    }
    return 0;
}

// 0x7100174ff0 — store param_2 ptr, then call vtable[0x178] with local buffer
void FUN_7100174ff0(s64 param_1, s64 *param_2)
{
    u8 auStack_20[16];

    *(s64 **)(param_1 + 0x18) = param_2;
    (**(void(**)(u8 *, s64 *, u64))(*param_2 + 0x178))(auStack_20, param_2, *(u64 *)(param_1 + 0x10));
}

// 0x7100181270 — check network protocol readiness via b2850/b2b10 chain, return field+0x46c
u32 FUN_7100181270(s64 param_1)
{
    s64 lVar1;
    u64 uVar2;

    if (*(s32 *)(param_1 + 0x418) == 0) {
        lVar1 = param_1 + 0x2c0;
        uVar2 = FUN_71000b2850(lVar1);
        if ((uVar2 & 1) != 0) {
            uVar2 = FUN_71000b2850(param_1 + 0x2a0);
            if (((uVar2 & 1) != 0) && (uVar2 = FUN_71000b2b10(param_1 + 0x2a0, lVar1), (uVar2 & 1) != 0))
                goto LAB_710018128c;
        }
        uVar2 = FUN_71000b2850(lVar1);
        if ((uVar2 & 1) == 0) {
            return 0;
        }
        uVar2 = FUN_71000b2850(param_1 + 0x2a0);
        if ((uVar2 & 1) == 0) {
            return 0;
        }
        uVar2 = FUN_71000b2b10(param_1 + 0x2a0, lVar1);
        if ((uVar2 & 1) != 0) {
            return 0;
        }
    }
LAB_710018128c:
    return *(u32 *)(param_1 + 0x46c);
}

// 0x7100182c70 — init event descriptor: vtable PTR+0x10, param_2, param_3, type=0x12, size=0x10
void FUN_7100182c70(s64 *param_1, s64 param_2, u16 param_3)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *param_1 = (s64)(PTR_DAT_71052a53d8 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((s64)param_1 + 0x12) = 0x12;
    *(u32 *)((s64)param_1 + 0x14) = 0x10;
}

// 0x7100182d10 — init event descriptor: vtable PTR+0x10, param_2, param_3, type=0x13, size=0x10
void FUN_7100182d10(s64 *param_1, s64 param_2, u16 param_3)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *param_1 = (s64)(PTR_DAT_71052a53e0 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((s64)param_1 + 0x12) = 0x13;
    *(u32 *)((s64)param_1 + 0x14) = 0x10;
}

// 0x7100182db0 — init event descriptor: vtable PTR+0x10, param_2, param_3, param_4, param_5, size=0x14
void FUN_7100182db0(s64 *param_1, s64 param_2, u16 param_3, u8 param_4, u32 param_5)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *(u32 *)((s64)param_1 + 0x1c) = param_5;
    *param_1 = (s64)(PTR_DAT_71052a53e8 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((s64)param_1 + 0x12) = param_4;
    *(u32 *)((s64)param_1 + 0x14) = 0x14;
}

// 0x7100185e30 — clear bit (param_2 & 0x1f) in u32 field at param_1+0x5c
void FUN_7100185e30(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x5c) = *(u32 *)(param_1 + 0x5c) & (1 << (u64)(param_2 & 0x1f) ^ 0xffffffffU);
}

// 0x7100186270 — init vtable ptr in param_1[0] to PTR_DAT+0x10, zero param_1[1] low 32b
void FUN_7100186270(s64 *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a5528 + 0x10);
}

// 0x7100191f90 — true if field+0x118 == 2 and field+0xe8 in [2..4]
u8 FUN_7100191f90(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x118) == 2) {
        return *(s32 *)(param_1 + 0xe8) - 2U < 3;
    }
    return 0;
}

// 0x7100192260 — true if field+0x118 == 3 and field+0xe8 in [2..4]
u8 FUN_7100192260(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x118) == 3) {
        return *(s32 *)(param_1 + 0xe8) - 2U < 3;
    }
    return 0;
}

// 0x7100192ce0 — true if field+0x118 == 5 and field+0xe8 in [2..4]
u8 FUN_7100192ce0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x118) == 5) {
        return *(s32 *)(param_1 + 0xe8) - 2U < 3;
    }
    return 0;
}

// 0x7100193740 — true if nested ptr at +0x38 is non-null and byte+0x84 is non-zero
u8 FUN_7100193740(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x38) != 0) {
        return *(s8 *)(*(s64 *)(param_1 + 0x38) + 0x84) != '\0';
    }
    return 0;
}
