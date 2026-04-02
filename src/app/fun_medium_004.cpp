#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100145000-0x7100165000
// Pool-d worker: auto-generated from Ghidra decompilation

extern void* PTR_DAT_71052a3bd0;
extern u8*   PTR_DAT_71052a3bd8;
extern void* PTR_DAT_71052a4f38;

extern "C" void* FUN_710015f5c0();

// Repeated bool-check pattern: +0x140 == N and +0x110 in [2..4]
// 7100145ec0
bool FUN_7100145ec0(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 3) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}
// 7100146070
bool FUN_7100146070(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 4) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}
// 71001462a0
bool FUN_71001462a0(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 5) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}
// 7100146670
bool FUN_7100146670(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 7) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}
// 71001468b0
bool FUN_71001468b0(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 8) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}
// 7100146a90
bool FUN_7100146a90(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 0x13) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}
// 7100149180
bool FUN_7100149180(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 0x1a) return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    return false;
}

// -- FUN_7100149270 ----------------------------------------------------------
// Set indexed int field; conditionally update PTR_DAT_71052a3bd0+0x124
// 7100149270
void FUN_7100149270(u8* param_1, s32 param_2)
{
    *(s32*)(param_1 + (u64)*(u8*)(param_1 + 0x162) * 4 + 0x180) = param_2;
    if (param_2 != 0) {
        *(s32*)((u8*)PTR_DAT_71052a3bd0 + 0x124) = param_2;
    }
}

// -- FUN_710014f090 ----------------------------------------------------------
// Copy 3 u32 fields from param_2+8/c/10 to param_1+8/c/10
// 710014f090
void FUN_710014f090(u8* param_1, u8* param_2)
{
    *(u32*)(param_1 + 0x10) = *(u32*)(param_2 + 0x10);
    *(u32*)(param_1 + 8)    = *(u32*)(param_2 + 8);
    *(u32*)(param_1 + 0xc)  = *(u32*)(param_2 + 0xc);
}

// -- FUN_710014f150 ----------------------------------------------------------
// Init struct with vtable from PTR_DAT_71052a4f38+0x10
// 710014f150
void FUN_710014f150(u64* param_1)
{
    *(u32*)(param_1 + 1) = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a4f38 + 0x10);
}

// -- FUN_71001506d0 ----------------------------------------------------------
// Find node in circular list by key at +0x20; set byte at +0x2e; return 1 if found
// 71001506d0
u64 FUN_71001506d0(u8* param_1, s64 param_2, u8 param_3)
{
    s64 lVar1 = *(s64*)(param_1 + 0x10);
    if (lVar1 == (s64)(param_1 + 8)) return 0;
    do {
        if (*(s64*)(lVar1 + 0x20) == param_2) {
            *(u8*)(lVar1 + 0x2e) = param_3 & 1;
            return 1;
        }
        lVar1 = *(s64*)(lVar1 + 8);
    } while (lVar1 != (s64)(param_1 + 8));
    return 0;
}

// -- FUN_7100150900 ----------------------------------------------------------
// Clear u32 at +0x14 on every node in circular linked list at +0x10
// 7100150900
void FUN_7100150900(u8* param_1)
{
    for (s64 lVar1 = *(s64*)(param_1 + 0x10); lVar1 != (s64)(param_1 + 8);
         lVar1 = *(s64*)(lVar1 + 8)) {
        *(u32*)(lVar1 + 0x14) = 0;
    }
}

// -- FUN_7100150de0 ----------------------------------------------------------
// Find node by key at +0x20 in circular list; read byte at +0x2d into *param_3; return 1 if found
// 7100150de0
u64 FUN_7100150de0(u8* param_1, s64 param_2, u8* param_3)
{
    s64 lVar1 = *(s64*)(param_1 + 0x10);
    if (lVar1 == (s64)(param_1 + 8)) return 0;
    do {
        if (*(s64*)(lVar1 + 0x20) == param_2) {
            *param_3 = *(u8*)(lVar1 + 0x2d);
            return 1;
        }
        lVar1 = *(s64*)(lVar1 + 8);
    } while (lVar1 != (s64)(param_1 + 8));
    return 0;
}

// -- FUN_7100150e30 ----------------------------------------------------------
// Find node by key at +0x20 in circular list; set byte at +0x2c
// 7100150e30
void FUN_7100150e30(u8* param_1, s64 param_2, u8 param_3)
{
    s64 lVar1 = *(s64*)(param_1 + 0x10);
    if (lVar1 != (s64)(param_1 + 8)) {
        do {
            if (*(s64*)(lVar1 + 0x20) == param_2) {
                *(u8*)(lVar1 + 0x2c) = param_3 & 1;
                return;
            }
            lVar1 = *(s64*)(lVar1 + 8);
        } while (lVar1 != (s64)(param_1 + 8));
    }
}

// -- FUN_7100150ec0 ----------------------------------------------------------
// Count nodes matching int at +0x28 in circular list
// 7100150ec0
s32 FUN_7100150ec0(u8* param_1, s32 param_2)
{
    s64 lVar3 = *(s64*)(param_1 + 0x10);
    if (lVar3 != (s64)(param_1 + 8)) {
        s32 iVar2 = 0;
        do {
            s32* piVar1 = (s32*)(lVar3 + 0x28);
            lVar3 = *(s64*)(lVar3 + 8);
            if (*piVar1 == param_2) iVar2++;
        } while (lVar3 != (s64)(param_1 + 8));
        return iVar2;
    }
    return 0;
}

// -- FUN_7100151fe0 ----------------------------------------------------------
// Bit test from constant 0x31 >> shift; shift from param_1+0x78; guard flags
// 7100151fe0
u32 FUN_7100151fe0(u8* param_1)
{
    if (((*(s8*)(param_1 + 0x48) != '\0') && (*(s8*)(param_1 + 0x50) != '\0')) &&
        (*(u32*)(param_1 + 0x78) < 6)) {
        return 0x31u >> (*(u32*)(param_1 + 0x78) & 0x1f) & 1;
    }
    return 0;
}

// -- FUN_7100153d50 ----------------------------------------------------------
// Set u32 at param_1+0xd8; call vtable fn at *param_1+0x98; return param_1+0xe8
// 7100153d50
u64* FUN_7100153d50(u64* param_1, u32* param_2)
{
    *(u32*)(param_1 + 0x1b) = *param_2;
    (*(void(**)(u64*))(param_1[0] + 0x98))(param_1);
    return param_1 + 0x1d;
}

// -- FUN_7100154c10 ----------------------------------------------------------
// Linear search: find param_2 in array of s32 stride-6; return index or 0xffffffff
// 7100154c10
u64 FUN_7100154c10(s32* param_1, s32 param_2)
{
    s32* piVar1 = param_1 + 0xc0;
    if (*piVar1 < 1) return 0xffffffff;
    u64 uVar2 = 0;
    do {
        if (*param_1 == param_2) return uVar2 & 0xffffffff;
        uVar2++;
        param_1 += 6;
    } while ((s64)uVar2 < (s64)*piVar1);
    return 0xffffffff;
}

// -- FUN_7100154c60 ----------------------------------------------------------
// Push u32 to array at param_1[count*0x18]; count at +0x300; max 0x20
// 7100154c60
s32 FUN_7100154c60(u8* param_1, u32 param_2)
{
    s32 iVar1 = *(s32*)(param_1 + 0x300);
    if (iVar1 < 0x20) {
        *(u32*)(param_1 + (s64)iVar1 * 0x18) = param_2;
        *(s32*)(param_1 + 0x300) = iVar1 + 1;
        return iVar1;
    }
    return -1;
}

// -- FUN_7100154f10 ----------------------------------------------------------
// Advance circular buffer index at +0x14; return base+old*0x658
// 7100154f10
s64 FUN_7100154f10(u8* param_1)
{
    u32 uVar2 = *(u32*)(param_1 + 0x10);
    u32 uVar3 = *(u32*)(param_1 + 0x14);
    u32 uVar1 = uVar3 + 1;
    u32 uVar5 = 0;
    if (uVar2 != 0) uVar5 = uVar1 / uVar2;
    s32 iVar4 = (s32)(uVar1 - uVar5 * uVar2);
    if (iVar4 == *(s32*)(param_1 + 0x1c)) return 0;
    *(s32*)(param_1 + 0x14) = iVar4;
    return *(s64*)(param_1 + 8) + (u64)uVar3 * 0x658;
}

// -- FUN_7100154f50 ----------------------------------------------------------
// Compute entry pointer using offset param_2 from +0x18
// 7100154f50
s64 FUN_7100154f50(u8* param_1, s32 param_2)
{
    u32 uVar2 = *(u32*)(param_1 + 0x10);
    u32 uVar1 = (u32)(*(s32*)(param_1 + 0x18) + param_2);
    u32 uVar3 = 0;
    if (uVar2 != 0) uVar3 = uVar1 / uVar2;
    uVar1 = uVar1 - uVar3 * uVar2;
    if (*(u32*)(param_1 + 0x14) == uVar1) return 0;
    return *(s64*)(param_1 + 8) + (u64)uVar1 * 0x658;
}

// -- FUN_7100155000 ----------------------------------------------------------
// Move pending value at +0x20 to current at +0x1c if >=0; reset pending to -1
// 7100155000
void FUN_7100155000(u8* param_1)
{
    if (*(s64*)(param_1 + 0x20) >= 0) {
        *(s32*)(param_1 + 0x1c) = (s32)*(s64*)(param_1 + 0x20);
        *(u64*)(param_1 + 0x20) = 0xffffffffffffffffULL;
    }
}

// -- FUN_71001578e0 ----------------------------------------------------------
// Check if param_2 not in char array at +0x29; return 1 if not found
// 71001578e0
u64 FUN_71001578e0(u8* param_1, s8 param_2)
{
    if (*(s32*)(param_1 + 0x4c) < 1) return 1;
    s64 lVar1 = 0;
    do {
        if (*(s8*)(param_1 + 0x29 + lVar1) == param_2) return 0;
        lVar1++;
    } while (lVar1 < *(s32*)(param_1 + 0x4c));
    return 1;
}

// -- FUN_7100158070 ----------------------------------------------------------
// Set several struct fields related to render state
// 7100158070
void FUN_7100158070(u8* param_1, u32* param_2, u32 param_3, u8 param_4, u8 param_5)
{
    *(u32*)(param_1 + 0x608) = param_3;
    u32 uVar1 = *param_2;
    *(u8*)(param_1 + 0x61c) = param_4 & 1;
    *(u8*)(param_1 + 0xa04) = 0;
    *(u32*)(param_1 + 0xa00) = 0;
    *(u32*)(param_1 + 0x618) = uVar1;
    *(u8*)(param_1 + 0x61d) = param_5 & 1;
}

// -- FUN_71001583c0 ----------------------------------------------------------
// Append 3 u64 + 3 bit fields to array at param_1+0x620
// 71001583c0
void FUN_71001583c0(u8* param_1, u64 param_2, u64 param_3, u64 param_4,
                    u8 param_5, u8 param_6, u8 param_7)
{
    u32 uVar2 = *(u32*)(param_1 + 0xa00);
    u8* lVar1 = param_1 + (u64)uVar2 * 0x20;
    *(u8*)(lVar1 + 0x638) = param_6 & 1;
    *(u64*)(lVar1 + 0x620) = param_2;
    *(u64*)(lVar1 + 0x628) = param_3;
    *(u64*)(lVar1 + 0x630) = param_4;
    *(u8*)(lVar1 + 0x639) = param_7 & 1;
    *(u8*)(lVar1 + 0x63a) = param_5 & 1;
    *(u32*)(param_1 + 0xa00) = uVar2 + 1;
}

// -- FUN_710015e850 ----------------------------------------------------------
// If ptr at +0x50 non-null and flag at +0x38 != -3: call FUN_710015f5c0; else 0xffffffff
// 710015e850
u64 FUN_710015e850(u8* param_1)
{
    if ((*(u64*)(param_1 + 0x50) != 0) && (*(s8*)(param_1 + 0x38) != -3)) {
        return (u64)FUN_710015f5c0();
    }
    return 0xffffffff;
}

// -- FUN_71001604a0 ----------------------------------------------------------
// Set 2-bit field at bits [3:2] of param_1+0x78
// 71001604a0
void FUN_71001604a0(u8* param_1, u32 param_2)
{
    *(u8*)(param_1 + 0x78) = (*(u8*)(param_1 + 0x78) & 0xf3) | (u8)((param_2 & 3) << 2);
}

// -- FUN_7100162ce0 ----------------------------------------------------------
// Clamp +0xa4 to [1..0xfe], clamp to 0xff; write to PTR_DAT_71052a3bd8+0x2b6
// 7100162ce0
void FUN_7100162ce0(u8* param_1)
{
    s32 iVar1 = *(s32*)(param_1 + 0xa4);
    if (0xfd < (u32)(iVar1 - 1)) iVar1 = 0xff;
    PTR_DAT_71052a3bd8[0x2b6] = (s8)iVar1;
}

// -- FUN_7100163d40 ----------------------------------------------------------
// Same as FUN_7100162ce0 but writes to index 0x2b7
// 7100163d40
void FUN_7100163d40(u8* param_1)
{
    s32 iVar1 = *(s32*)(param_1 + 0xa4);
    if (0xfd < (u32)(iVar1 - 1)) iVar1 = 0xff;
    PTR_DAT_71052a3bd8[0x2b7] = (s8)iVar1;
}

// -- FUN_7100164070 ----------------------------------------------------------
// Zero 0x400 bytes in 0x20-byte blocks (5 u64 + u32 + u8 per block)
// 7100164070
void FUN_7100164070(u8* param_1)
{
    s64 lVar2 = 0;
    do {
        u64* puVar1 = (u64*)(param_1 + lVar2);
        lVar2 += 0x20;
        puVar1[0] = 0; puVar1[1] = 0; puVar1[2] = 0;
        *(u32*)(puVar1 + 3) = 0;
        *(u8*)((u8*)puVar1 + 0x1c) = 0;
    } while (lVar2 != 0x400);
    *(u32*)(param_1 + 0x400) = 0;
}
