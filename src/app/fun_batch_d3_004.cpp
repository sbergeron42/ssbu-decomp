#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-004
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u8  PTR_DAT_71052a3bd8[];
extern u8  PTR_DAT_71052a4490[];
extern u8  PTR_DAT_71052a44f8[];
extern u8  PTR_DAT_71052a4570[];
extern u8  PTR_DAT_71052a4608[];
extern u8  PTR_DAT_71052a4740[];

// External FUN_* forward declarations
extern void FUN_71000b1900(u8 *);
extern void FUN_71000b1910(s64, u8 *);
extern u32  FUN_71000b4990();
extern void FUN_71000bed00();
extern void FUN_710013d270();
extern void FUN_710013dcf0();
extern void FUN_710018f180();
extern void FUN_71001424e0();
extern s64  FUN_7100154fa0(u64, u32);

// ---- Functions ---------------------------------------------------------------

// 0x7100104ce0 — ctor: parent init, clear fields, set vtable (112 bytes)
void FUN_7100104ce0(s64 *param_1)
{
    u8 *puVar1;

    FUN_710013d270();
    param_1[0x14] = 0;
    puVar1 = PTR_DAT_71052a4490;
    *(u32 *)(param_1 + 0x17) = 0;
    param_1[0x18] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    *(u8 *)(param_1 + 0x19) = 0;
    param_1[0x1a] = 0;
}

// 0x710010a650 — ctor: parent init, set vtable (48 bytes)
void FUN_710010a650(s64 *param_1)
{
    FUN_710018f180();
    *param_1 = (s64)(PTR_DAT_71052a4608 + 0x10);
}

// 0x710010f170 — ctor: parent init, set vtable + secondary ptr (64 bytes)
void FUN_710010f170(s64 *param_1)
{
    u8 *puVar1;

    FUN_71000bed00();
    puVar1 = PTR_DAT_71052a4740 + 0x60;
    *param_1 = (s64)(PTR_DAT_71052a4740 + 0x10);
    param_1[3] = (s64)puVar1;
}

// 0x7100106240 — ctor: parent init, set vtable (48 bytes)
void FUN_7100106240(s64 *param_1)
{
    FUN_710013dcf0();
    *param_1 = (s64)(PTR_DAT_71052a44f8 + 0x10);
}

// 0x7100107800 — ctor: parent init, clear 5 fields, set vtable + clear more (96 bytes)
void FUN_7100107800(s64 *param_1)
{
    u8 *puVar1;

    FUN_71001424e0();
    puVar1 = PTR_DAT_71052a4570;
    param_1[0x2d] = 0;
    param_1[0x29] = 0;
    param_1[0x2a] = 0;
    param_1[0x2b] = 0;
    param_1[0x2c] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    *(u32 *)(param_1 + 0x30) = 0;
    *(u16 *)((s64)param_1 + 0x184) = 0;
    param_1[0x31] = 0;
}

// 0x71001353c0 — setter: conditional 3-field init (param guard) (256 bytes)
void FUN_71001353c0(u32 *param_1, s32 param_2, s64 param_3)
{
    if ((0 < param_2) && (param_3 != 0)) {
        *(s64 *)(param_1 + 2) = param_3;
        *param_1 = 0;
        param_1[1] = (u32)param_2;
    }
}

// 0x7100135500 — bit util: return index of Nth set bit, or 0xffffffff (96 bytes)
u32 FUN_7100135500(u32 param_1, s32 param_2)
{
    u32 uVar1;

    if (param_1 == 0) {
        return 0xffffffff;
    }
    param_2 = param_2 + 1;
    do {
        param_2 = param_2 - 1;
        if (param_2 < 2) {
            uVar1 = (param_1 & -param_1) - 1;
            uVar1 = uVar1 - (uVar1 >> 1 & 0x55555555);
            uVar1 = (uVar1 >> 2 & 0x33333333) + (uVar1 & 0x33333333);
            uVar1 = (uVar1 + (uVar1 >> 4)) & 0xf0f0f0f;
            uVar1 = uVar1 + (uVar1 >> 8);
            return (uVar1 + (uVar1 >> 0x10)) & 0x3f;
        }
        param_1 = (param_1 - 1) & param_1;
    } while (param_1 != 0);
    return 0xffffffff;
}

// 0x71001476b0 — flag-or: check two pointer fields, OR FUN_71000b4990 results (64 bytes)
u32 FUN_71001476b0(s64 param_1)
{
    u32 uVar1;
    u32 uVar2;
    s64 lVar3;

    if (*(s64 *)(param_1 + 0x20) == 0) {
        uVar1 = 0;
        lVar3 = *(s64 *)(param_1 + 0x30);
    } else {
        uVar1 = FUN_71000b4990();
        lVar3 = *(s64 *)(param_1 + 0x30);
    }
    if (lVar3 != 0) {
        uVar2 = FUN_71000b4990();
        uVar1 = uVar1 | uVar2;
    }
    return uVar1 & 1;
}

// 0x7100149290 — indexed store: write int at computed offset, optionally store global (64 bytes)
void FUN_7100149290(s64 param_1, s32 param_2)
{
    *(s32 *)(param_1 + (u64)(*(s8 *)(param_1 + 0x162) == '\0') * 4 + 0x180) = param_2;
    if (param_2 != 0) {
        *(s32 *)(PTR_DAT_71052a3bd8 + 0x300) = param_2;
    }
}

// 0x7100150720 — linked-list search: find param_2 at +0x20, return flag at +0x2e (80 bytes)
bool FUN_7100150720(s64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x10);
    if (lVar1 == param_1 + 8) {
        return false;
    }
    do {
        if (*(s64 *)(lVar1 + 0x20) == param_2) {
            return *(s8 *)(lVar1 + 0x2e) != '\0';
        }
        lVar1 = *(s64 *)(lVar1 + 8);
    } while (lVar1 != param_1 + 8);
    return false;
}

// 0x7100153200 — byte-set membership: return 1 if param_2 is in known set (128 bytes)
u64 FUN_7100153200(u64 param_1, u8 param_2)
{
    switch (param_2) {
    case 0x08: case 0x14: case 0x18: case 0x1c: case 0x24: case 0x28: case 0x2c:
    case 0x34: case 0x44: case 0x54: case 0x58: case 0x65: case 0x68: case 0x6c:
    case 0x73: case 0x74: case 0x76: case 0x77: case 0x78: case 0x7b: case 0x7c:
    case 0x80: case 0x81: case 0x84: case 0x94: case 0xa4: case 0xa8: case 0xac:
    case 0xb0: case 0xb4:
        return 1;
    default:
        return 0;
    }
}

// 0x7100153dc0 — bool wrapper: FUN_7100154fa0(+0x38, +0xdc) == 0 (64 bytes)
bool FUN_7100153dc0(s64 param_1)
{
    s64 lVar1;

    lVar1 = FUN_7100154fa0(*(u64 *)(param_1 + 0x38), *(u32 *)(param_1 + 0xdc));
    return lVar1 == 0;
}

// 0x7100154360 — init: clear +0x10, init stack buf, copy to +0x18 (48 bytes)
void FUN_7100154360(s64 param_1)
{
    u8 auStack_38[24];

    *(u64 *)(param_1 + 0x10) = 0;
    FUN_71000b1900(auStack_38);
    FUN_71000b1910(param_1 + 0x18, auStack_38);
}
