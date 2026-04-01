#include "types.h"

// MEDIUM-tier FUN_* functions — address range 0x7100044000–0x7100b4000
// Pool-d worker: auto-generated from Ghidra decompilation

extern void* PTR_DAT_71052a3648;
extern void* PTR_DAT_71052a3bc0;
extern void* PTR_DAT_71052a3bf0;
extern void* PTR_DAT_71052a3bf8;
extern void* PTR_DAT_71052a3c00;
extern void* PTR_DAT_71052a3c08;
extern void* PTR_DAT_71052a3c10;
extern void* PTR_DAT_71052a3c18;

extern u64 DAT_7104f49388, DAT_7104f49390;
extern u64 DAT_7104f49428, DAT_7104f49430;
extern u64 DAT_7104492890[];
extern u32 DAT_7104492960[];
extern u32 DAT_71044705bc[];

// -- FUN_7100044dd0 ----------------------------------------------------------
// Check if values changed; update and return 1 if changed, 0 if same
// 7100044dd0
u64 FUN_7100044dd0(u8* param_1, s64 param_2, s16 param_3)
{
    if ((*(s64*)(param_1 + 400) == param_2) && (*(s16*)(param_1 + 0x198) == param_3)) {
        return 0;
    }
    *(s64*)(param_1 + 400) = param_2;
    *(s16*)(param_1 + 0x198) = param_3;
    return 1;
}

// -- FUN_7100047c70 ----------------------------------------------------------
// Doubly-linked list splice: insert param_1's node before param_2
// 7100047c70
void FUN_7100047c70(u64* param_1, u8* param_2)
{
    u64* plVar1 = (u64*)(param_2 + 8);
    u64  lVar2  = *plVar1;
    *plVar1 = *param_1;
    *(u64**)(lVar2 + 8) = param_1;
    *(u64**)(*param_1 + 8) = plVar1;
    *param_1 = lVar2;
}

// -- FUN_710004a590 ----------------------------------------------------------
// Return vtable entry at index param_1[1]-1 if in range [1..max]
// 710004a590
u64 FUN_710004a590(u64* param_1)
{
    s32 idx = (s32)param_1[1];
    if (idx < 1 || *(s32*)PTR_DAT_71052a3648 < idx) return 0;
    return *(u64*)(param_1[0] + (s64)(idx - 1) * 8);
}

// -- FUN_710004c5e0 ----------------------------------------------------------
// Load from array at param_1[0] using index (param_1[1] - param_2 - 1)
// 710004c5e0
u64 FUN_710004c5e0(u64* param_1, u32 param_2)
{
    return *(u64*)(param_1[0] + (s64)(s32)((s32)param_1[1] + ~param_2) * 8);
}

// -- FUN_7100055470 ----------------------------------------------------------
// Return *(*(param_2+200)+0x38) + *(param_1+0x34) if non-zero
// 7100055470
s64 FUN_7100055470(u8* param_1, u8* param_2)
{
    s64 lVar1 = *(s64*)(*(u8**)(param_2 + 200) + 0x38);
    if (lVar1 != 0) {
        return lVar1 + (u64)*(u32*)(param_1 + 0x34);
    }
    return 0;
}

// -- FUN_7100059860 ----------------------------------------------------------
// Return count from +0xa8 struct: *(short*)(+8) minus (*(int*)(+0x60) != 0)
// 7100059860
s32 FUN_7100059860(u8* param_1)
{
    u8* p = *(u8**)(param_1 + 0xa8);
    if (p != nullptr) {
        return (u32)*(u16*)(p + 8) - (u32)(*(s32*)(param_1 + 0x60) != 0);
    }
    return 0;
}

// -- FUN_7100059890 ----------------------------------------------------------
// Return pointer to entry list at +0xa8, adjusted for whether +0x60 is set
// 7100059890
s64 FUN_7100059890(u8* param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 0xa8);
    if (lVar1 == 0) return 0;
    if (*(s32*)(param_1 + 0x60) != 0) {
        if (*(s16*)(lVar1 + 8) == 1) return 0;
        return lVar1 + 0x18;
    }
    return lVar1 + 0xc;
}

// -- FUN_7100060e80 ----------------------------------------------------------
// Clear u16 fields [4..7] and set low bits of [0]
// 7100060e80
void FUN_7100060e80(u16* param_1)
{
    param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0;
    *param_1 = *param_1 & 0xe000 | 0x90;
}

// -- FUN_7100060ea0 ----------------------------------------------------------
// Clear fields then set +8 pointer from param_2 if non-zero
// 7100060ea0
void FUN_7100060ea0(u16* param_1, s64 param_2)
{
    u16 uVar1;
    param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0;
    if (param_2 != 0) {
        uVar1 = *param_1;
        *(s64*)(param_1 + 4) = param_2;
        *param_1 = uVar1 & 0xff00 | 0x90;
        *param_1 = uVar1 & 0xe000 | 0x90;
        return;
    }
    *param_1 = *param_1 & 0xe0ff;
}

// -- FUN_7100060f20 ----------------------------------------------------------
// Bitfield update: set bits [1:0] and [3:2] from params
// 7100060f20
void FUN_7100060f20(u16* param_1, u16 param_2, u32 param_3)
{
    *param_1 = (param_2 & 3) | (u16)((param_3 & 3) << 2) | (*param_1 & 0xfff0);
}

// -- FUN_7100060f40 ----------------------------------------------------------
// Bitfield update: set bits [6:4] and [7] from params
// 7100060f40
void FUN_7100060f40(u16* param_1, u32 param_2, u32 param_3)
{
    *param_1 = (u16)((param_2 & 7) << 4) | (u16)((param_3 & 1) << 7) | (*param_1 & 0xff0f);
}

// -- FUN_7100066040 ----------------------------------------------------------
// Return 1 if **(param_1+0x68) != '\0', else 0 (or 0 if param_1==0)
// 7100066040
u64 FUN_7100066040(u64 param_1)
{
    if (param_1 != 0) {
        param_1 = (u64)(**(s8**)(param_1 + 0x68) != '\0');
    }
    return param_1;
}

// -- FUN_7100078b00 ----------------------------------------------------------
// Doubly-linked list splice using offsets +0x38 and +0x48
// 7100078b00
void FUN_7100078b00(u8* param_1, u8* param_2)
{
    u64* plVar2 = (u64*)(param_2 + 0x48);
    u64  lVar3  = *plVar2;
    u64* plVar1 = (u64*)(param_1 + 0x38);
    *plVar2 = *plVar1;
    *(u64**)(lVar3 + 8) = plVar1;
    *(u64**)(*plVar1 + 8) = plVar2;
    *plVar1 = lVar3;
}

// -- FUN_7100078b20 ----------------------------------------------------------
// SetDefault: init struct with float/color constants
// 7100078b20
void FUN_7100078b20(u64* param_1)
{
    param_1[0] = 0xffffffffffffffffULL;
    param_1[1] = 0x3f80000000000000ULL;
    *(u16*)(param_1 + 7) = 0xff00;
    param_1[2] = 0x3f800000ULL;
    param_1[5] = 0; param_1[6] = 0;
    param_1[3] = 0; param_1[4] = 0;
}

// -- FUN_7100078f80 ----------------------------------------------------------
// SetDefault: zero 24 u64 fields; first two via u64+u32 pattern
// 7100078f80
void FUN_7100078f80(u64* param_1)
{
    param_1[0] = 0;
    *(u32*)(param_1 + 1) = 0;
    param_1[0x16] = 0; param_1[0x17] = 0;
    param_1[0x14] = 0; param_1[0x15] = 0;
    param_1[0x12] = 0; param_1[0x13] = 0;
    param_1[0x10] = 0; param_1[0x11] = 0;
    param_1[0xe]  = 0; param_1[0xf]  = 0;
    param_1[0xc]  = 0; param_1[0xd]  = 0;
    param_1[10]   = 0; param_1[0xb]  = 0;
    param_1[8]    = 0; param_1[9]    = 0;
    param_1[6]    = 0; param_1[7]    = 0;
    param_1[4]    = 0; param_1[5]    = 0;
    param_1[2]    = 0; param_1[3]    = 0;
}

// -- FUN_71000837a0 ----------------------------------------------------------
// Check if Unicode codepoint is a zero-width/invisible char; return 0 if so, 1 otherwise
// 71000837a0
u64 FUN_71000837a0(u32 param_1)
{
    if ((param_1 & 0xffffff00) == 0x2000) {
        switch (param_1) {
        case 0x200b: case 0x200e: case 0x200f:
        case 0x202a: case 0x202b: case 0x202c:
        case 0x202d: case 0x202e: case 0x2060:
            return 0;
        }
        if (param_1 - 0x2066u < 4) return 0;
    }
    return 1;
}

// -- FUN_71000887d0 ----------------------------------------------------------
// Advance animation frame index, wrap around based on 3-column mode flag
// 71000887d0
u64 FUN_71000887d0(u8* param_1, s32 param_2)
{
    if (param_2 == 2) {
        if ((param_1[9] == '\0') && (param_1[10] == '\0')) return 0;
    } else if (param_2 != 1) {
        return 0;
    }
    *(u16*)(param_1 + 9) = 0;
    s32 iVar1 = *(s32*)(param_1 + 0x30) + 1;
    s32 iVar4 = 2;
    if (*(s8*)(*(u64*)(*(u64*)(param_1 + 0x78) + 0x20) + 0x36) != '\0') iVar4 = 3;
    s32 iVar3 = 0;
    if (iVar4 != 0) iVar3 = iVar1 / iVar4;
    u32 uVar2 = (u32)(iVar1 - iVar3 * iVar4);
    *(u32*)(param_1 + 0x30) = uVar2;
    *(u64*)(param_1 + 0xc0) = (u64)(param_1 + (u64)uVar2 * 0x58 + 200);
    return 1;
}

// -- FUN_710008a3b0 ----------------------------------------------------------
// Walk linked list at param_1+0x150 via +0x80 next pointers, param_2 steps (no return)
// 710008a3b0
void FUN_710008a3b0(u8* param_1, s32 param_2)
{
    s64 lVar1 = *(s64*)(param_1 + 0x150);
    if ((param_2 != 0) && (lVar1 != 0)) {
        param_2--;
        do {
            lVar1 = *(s64*)(lVar1 + 0x80);
            if (param_2 == 0) return;
            param_2--;
        } while (lVar1 != 0);
    }
}

// -- FUN_710008a3e0 ----------------------------------------------------------
// Return param_1[0] if non-zero and param_1[1] matches int at +0x2c, else 0
// 710008a3e0
s64 FUN_710008a3e0(u64* param_1)
{
    s64 lVar1 = (s64)*param_1;
    if (lVar1 != 0) {
        if ((s32)param_1[1] != *(s32*)(lVar1 + 0x2c)) lVar1 = 0;
        return lVar1;
    }
    return 0;
}

// -- FUN_710009e130 ----------------------------------------------------------
// Count linked list from +0x418+0x18, starting from *(param_1+0x2c)
// 710009e130
s32 FUN_710009e130(u8* param_1)
{
    if (*(s8*)(*(u64*)(param_1 + 0x418) + 0x10) == '\0') return 0;
    s32 iVar1 = *(s32*)(param_1 + 0x2c);
    for (s64 lVar2 = *(s64*)(*(u64*)(param_1 + 0x418) + 0x18); lVar2 != 0;
         lVar2 = *(s64*)(lVar2 + 0x68)) {
        iVar1++;
    }
    return iVar1;
}

// -- FUN_71000a3920 ----------------------------------------------------------
// Count linked list from +0x418+0x18, starting from *(param_1+0x2c) (identical to FUN_710009e130)
// 71000a3920
s32 FUN_71000a3920(u8* param_1)
{
    if (*(s8*)(*(u64*)(param_1 + 0x418) + 0x10) == '\0') return 0;
    s32 iVar1 = *(s32*)(param_1 + 0x2c);
    for (s64 lVar2 = *(s64*)(*(u64*)(param_1 + 0x418) + 0x18); lVar2 != 0;
         lVar2 = *(s64*)(lVar2 + 0x68)) {
        iVar1++;
    }
    return iVar1;
}

// -- FUN_71000af810 ----------------------------------------------------------
// Compute table offset from byte fields at param_1+8,9,10
// 71000af810
s64 FUN_71000af810(u8* param_1)
{
    return *(s64*)PTR_DAT_71052a3bc0 +
           ((u64)param_1[9] + (u64)param_1[8] * 4 + (u64)param_1[10] * 0x10) * 0xa8;
}

// -- FUN_71000b1b50 ----------------------------------------------------------
// Table lookup: get u64 via jump table indexed by (param_1-2), default at index 25
// 71000b1b50
u64 FUN_71000b1b50(s32 param_1)
{
    if ((u32)(param_1 - 2) < 0x19) {
        return *(u64*)((u64)PTR_DAT_71052a3c18 +
                       DAT_7104492890[(s32)(param_1 - 2)] * 8);
    }
    return *(u64*)((u64)PTR_DAT_71052a3c18 + 200);
}

// -- FUN_71000b1bb0 ----------------------------------------------------------
// Set current state from table; default state 0x19
// 71000b1bb0
void FUN_71000b1bb0(s32 param_1)
{
    if ((u32)(param_1 - 2) < 0x19) {
        *(u32*)PTR_DAT_71052a3c10 = DAT_7104492960[(s32)(param_1 - 2)];
        return;
    }
    *(u32*)PTR_DAT_71052a3c10 = 0x19;
}

// -- FUN_71000b3c70 ----------------------------------------------------------
// Compute DAT_7104f49390 / DAT_7104f49388 if denominator non-zero
// 71000b3c70
u64 FUN_71000b3c70()
{
    if (DAT_7104f49388 != 0) {
        u64 uVar1 = 0;
        if (DAT_7104f49388 != 0) uVar1 = DAT_7104f49390 / DAT_7104f49388;
        return uVar1;
    }
    return 0;
}

// -- FUN_71000b3d10 ----------------------------------------------------------
// Compute DAT_7104f49430 / DAT_7104f49428 if denominator non-zero
// 71000b3d10
u64 FUN_71000b3d10()
{
    if (DAT_7104f49428 != 0) {
        u64 uVar1 = 0;
        if (DAT_7104f49428 != 0) uVar1 = DAT_7104f49430 / DAT_7104f49428;
        return uVar1;
    }
    return 0;
}
