#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-015
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: zero-fills, struct inits with PTR_DAT vtables, vtable dispatch, u16 bit ops

// ---- External declarations -----------------------------------------------

// PTR_DAT globals — hold runtime pointer values
extern u8 *PTR_DAT_71052a3328; // vtable base for FUN_710003aac0
extern u8 *PTR_DAT_71052a3390; // vtable base for FUN_710003bc80
extern s32 *PTR_DAT_71052a3648; // count limit for FUN_710004a590

// ---- Functions ---------------------------------------------------------------

// 0x710003a4e0 — zero-fill 9 u64 fields
void FUN_710003a4e0(u64 *param_1)
{
    param_1[7] = 0;
    param_1[8] = 0;
    *param_1 = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003a7d0 — zero-fill 24 u64 fields in pairs
void FUN_710003a7d0(u64 *param_1)
{
    param_1[0x16] = 0;
    param_1[0x17] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = 0;
    param_1[1] = 0;
}

// 0x710003aac0 — init s64* struct: set fields, store PTR_DAT_71052a3328+0x10 as vtable
void FUN_710003aac0(s64 *param_1, u32 param_2, u32 param_3)
{
    u8 *puVar1;

    param_1[2] = 0;
    *(u32 *)(param_1 + 3) = param_2;
    *(u32 *)((s64)param_1 + 0x1c) = 2;
    puVar1 = PTR_DAT_71052a3328;
    *(u32 *)(param_1 + 4) = param_3;
    *(u64 *)((s64)param_1 + 0x24) = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    param_1[1] = 0;
}

// 0x710003ac20 — set field+0x1c to 1 or 2 based on threshold, store param_2 at +0x28
void FUN_710003ac20(s64 param_1, s32 param_2)
{
    u32 uVar1;

    uVar1 = 1;
    if (0xffff < param_2) {
        uVar1 = 2;
    }
    *(u32 *)(param_1 + 0x1c) = uVar1;
    *(s32 *)(param_1 + 0x28) = param_2;
}

// 0x710003bc80 — init s64* struct: store PTR_DAT_71052a3390+0x10 as vtable, const at index 1
void FUN_710003bc80(s64 *param_1)
{
    u8 *puVar1;

    puVar1 = PTR_DAT_71052a3390;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    param_1[1] = 0x1f00000000LL;
    *(u32 *)(param_1 + 4) = 0;
}

// 0x710003c350 — vtable dispatch: cases 0,2 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003c350(s64 *param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
        (*(void(**)(s64 *, s32))(*param_1 + 0xd8))(param_1, 1);
        (*(void(**)(s64 *))(*param_1 + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x710003de30 — vtable dispatch: cases 0,2,5 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003de30(s64 *param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(s64 *, s32))(*param_1 + 0xd8))(param_1, 1);
        (*(void(**)(s64 *))(*param_1 + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x710003e030 — vtable dispatch: cases 0,2,5 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003e030(s64 *param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(s64 *, s32))(*param_1 + 0xd8))(param_1, 1);
        (*(void(**)(s64 *))(*param_1 + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x7100044c70 — set flag +0x18c, zero +0x190/+0x198, store param_2 at +0xc0
void FUN_7100044c70(s64 param_1, u64 param_2)
{
    *(u8 *)(param_1 + 0x18c) = 1;
    *(u64 *)(param_1 + 400) = 0;
    *(u16 *)(param_1 + 0x198) = 0;
    *(u64 *)(param_1 + 0xc0) = param_2;
}

// 0x7100044dd0 — compare and update two fields at +0x190/+0x198; return 0 if unchanged, 1 if updated
u64 FUN_7100044dd0(s64 param_1, s64 param_2, s16 param_3)
{
    if ((*(s64 *)(param_1 + 400) == param_2) && (*(s16 *)(param_1 + 0x198) == param_3)) {
        return 0;
    }
    *(s64 *)(param_1 + 400) = param_2;
    *(s16 *)(param_1 + 0x198) = param_3;
    return 1;
}

// 0x7100047c70 — doubly-linked list insert: splice param_1 after (param_2+8) node
void FUN_7100047c70(s64 *param_1, s64 param_2)
{
    s64 *plVar1;
    s64 lVar2;

    plVar1 = (s64 *)(param_2 + 8);
    lVar2 = *plVar1;
    *plVar1 = *param_1;
    *(s64 **)(lVar2 + 8) = param_1;
    *(s64 **)(*param_1 + 8) = plVar1;
    *param_1 = lVar2;
}

// 0x710004a590 — bounds-checked array lookup: return entry at (param_1[1]-1)*8 or 0
u64 FUN_710004a590(s64 *param_1)
{
    s32 iVar1;

    iVar1 = (s32)param_1[1];
    if (iVar1 < 1 || *PTR_DAT_71052a3648 < iVar1) {
        return 0;
    }
    return *(u64 *)(*param_1 + (s64)(iVar1 + -1) * 8);
}

// 0x710004c5e0 — array subscript: return entry at (param_1[1] + ~param_2)*8
u64 FUN_710004c5e0(s64 *param_1, u32 param_2)
{
    return *(u64 *)(*param_1 + (s64)(s32)((s32)param_1[1] + ~param_2) * 8);
}

// 0x7100055470 — compute base+offset: return *(*(param_2+200)+0x38) + *(param_1+0x34)
s64 FUN_7100055470(s64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(*(s64 *)(param_2 + 200) + 0x38);
    if (lVar1 != 0) {
        return lVar1 + (u64)*(u32 *)(param_1 + 0x34);
    }
    return 0;
}

// 0x7100059860 — count: u16 field at (param_1+0xa8)+8 minus bool(param_1+0x60 != 0)
s32 FUN_7100059860(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa8) != 0) {
        return (u32)*(u16 *)(*(s64 *)(param_1 + 0xa8) + 8) - (u32)(*(s32 *)(param_1 + 0x60) != 0);
    }
    return 0;
}

// 0x7100059890 — get next node: check param_1+0xa8, branch on +0x60 flag and +8 short
s64 FUN_7100059890(s64 param_1)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0xa8);
    if (lVar1 == 0) {
        return 0;
    }
    if (*(s32 *)(param_1 + 0x60) != 0) {
        if (*(s16 *)(lVar1 + 8) == 1) {
            return 0;
        }
        return lVar1 + 0x18;
    }
    return lVar1 + 0xc;
}

// 0x710005e9f0 — vtable call +0x50(), then return 0 or param_1[0x1b]
s64 FUN_710005e9f0(s64 *param_1, s32 param_2)
{
    (*(void(**)(void))(*param_1 + 0x50))();
    if (param_2 != 0) {
        return 0;
    }
    return param_1[0x1b];
}

// 0x7100060e80 — zero u16[4..7], mask *param_1 to 0xe000 then OR 0x90
void FUN_7100060e80(u16 *param_1)
{
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = *param_1 & 0xe000 | 0x90;
}

// 0x7100060ea0 — conditional u16 init: if param_2 != 0, store at +8 and set flags
void FUN_7100060ea0(u16 *param_1, s64 param_2)
{
    u16 uVar1;

    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    if (param_2 != 0) {
        uVar1 = *param_1;
        *(s64 *)(param_1 + 4) = param_2;
        *param_1 = uVar1 & 0xff00 | 0x90;
        *param_1 = uVar1 & 0xe000 | 0x90;
        return;
    }
    *param_1 = *param_1 & 0xe0ff;
}

// 0x7100060f20 — pack two 2-bit fields from param_2/param_3 into *param_1 bits[0..3]
void FUN_7100060f20(u16 *param_1, u16 param_2, u32 param_3)
{
    *param_1 = param_2 & 3 | (u16)((param_3 & 3) << 2) | *param_1 & 0xfff0;
}

// 0x7100060f40 — pack 3-bit and 1-bit fields into *param_1 bits[4..7]
void FUN_7100060f40(u16 *param_1, u32 param_2, u32 param_3)
{
    *param_1 = (u16)((param_2 & 7) << 4) | (u16)((param_3 & 1) << 7) | *param_1 & 0xff0f;
}

// 0x71000626a0 — vtable call +0x50(), then return 0 or param_1[0x28]
s64 FUN_71000626a0(s64 *param_1, s32 param_2)
{
    (*(void(**)(void))(*param_1 + 0x50))();
    if (param_2 != 0) {
        return 0;
    }
    return param_1[0x28];
}

// 0x7100066040 — check non-null and first byte of nested string: return 0 or 1
u64 FUN_7100066040(u64 param_1)
{
    if (param_1 != 0) {
        param_1 = (u64)(**(s8 **)(param_1 + 0x68) != '\0');
    }
    return param_1;
}
