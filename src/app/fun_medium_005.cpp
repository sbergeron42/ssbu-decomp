#include "types.h"

// MEDIUM-tier FUN_* functions — address range 0x7100174000–0x7100b8000
// Pool-d worker: auto-generated from Ghidra decompilation

extern u8* PTR_DAT_71052a53d8;
extern u8* PTR_DAT_71052a53e0;
extern u8* PTR_DAT_71052a53e8;
extern void* PTR_DAT_71052a5528;

static const char* s_result_cpp =
    "C:/home/ws/hac-appc2/Pack/7923402a/OnlineCore/src/Platform/Core/Result.cpp";

// -- FUN_7100174530 ----------------------------------------------------------
// Call vtable fn at *param_1+0x30; clear byte at param_1+9
// 7100174530
void FUN_7100174530(u64* param_1)
{
    (*(void(**)())(param_1[0] + 0x30))();
    *(u8*)((u8*)param_1 + 9) = 0;
}

// -- FUN_7100174cb0 ----------------------------------------------------------
// Return true if flag at +8 set and *(*(param_1+0x18)+0x418) != 0
// 7100174cb0
bool FUN_7100174cb0(u8* param_1)
{
    if (*(s8*)(param_1 + 8) == '\0') return false;
    u64 p = *(u64*)(param_1 + 0x18);
    if (p != 0) return *(s32*)(p + 0x418) != 0;
    return false;
}

// -- FUN_7100174ff0 ----------------------------------------------------------
// Store param_2 at +0x18; call vtable fn at *param_2+0x178(local, param_2, *(param_1+0x10))
// 7100174ff0
void FUN_7100174ff0(u8* param_1, u64* param_2)
{
    u8 auStack_20[16];
    *(u64**)(param_1 + 0x18) = param_2;
    (*(void(**)(u8*, u64*, u64))(param_2[0] + 0x178))(auStack_20, param_2, *(u64*)(param_1 + 0x10));
}

// -- FUN_7100182c70 ----------------------------------------------------------
// Init struct with vtable from PTR_DAT_71052a53d8+0x10; set fields
// 7100182c70
void FUN_7100182c70(u64* param_1, s64 param_2, u16 param_3)
{
    *(u16*)(param_1 + 2) = param_3;
    *(u16*)(param_1 + 3) = 0;
    *param_1 = (u64)(PTR_DAT_71052a53d8 + 0x10);
    param_1[1] = (u64)param_2;
    *(u8*)((u8*)param_1 + 0x12) = 0x12;
    *(u32*)((u8*)param_1 + 0x14) = 0x10;
}

// -- FUN_7100182d10 ----------------------------------------------------------
// Init struct with vtable from PTR_DAT_71052a53e0+0x10; set fields
// 7100182d10
void FUN_7100182d10(u64* param_1, s64 param_2, u16 param_3)
{
    *(u16*)(param_1 + 2) = param_3;
    *(u16*)(param_1 + 3) = 0;
    *param_1 = (u64)(PTR_DAT_71052a53e0 + 0x10);
    param_1[1] = (u64)param_2;
    *(u8*)((u8*)param_1 + 0x12) = 0x13;
    *(u32*)((u8*)param_1 + 0x14) = 0x10;
}

// -- FUN_7100182db0 ----------------------------------------------------------
// Init struct with vtable from PTR_DAT_71052a53e8+0x10; set fields
// 7100182db0
void FUN_7100182db0(u64* param_1, s64 param_2, u16 param_3, u8 param_4, u32 param_5)
{
    *(u16*)(param_1 + 2) = param_3;
    *(u16*)(param_1 + 3) = 0;
    *(u32*)((u8*)param_1 + 0x1c) = param_5;
    *param_1 = (u64)(PTR_DAT_71052a53e8 + 0x10);
    param_1[1] = (u64)param_2;
    *(u8*)((u8*)param_1 + 0x12) = param_4;
    *(u32*)((u8*)param_1 + 0x14) = 0x14;
}

// -- FUN_7100185e30 ----------------------------------------------------------
// Clear bit param_2 in u32 at param_1+0x5c
// 7100185e30
void FUN_7100185e30(u8* param_1, u32 param_2)
{
    *(u32*)(param_1 + 0x5c) =
        *(u32*)(param_1 + 0x5c) & (u32)(1u << (param_2 & 0x1f) ^ 0xffffffffu);
}

// -- FUN_7100186270 ----------------------------------------------------------
// Init struct with vtable from PTR_DAT_71052a5528+0x10
// 7100186270
void FUN_7100186270(u64* param_1)
{
    *(u32*)(param_1 + 1) = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a5528 + 0x10);
}

// -- FUN_7100191f90 ----------------------------------------------------------
// Return true if +0x118==2 and +0xe8 in [2..4]
// 7100191f90
bool FUN_7100191f90(u8* param_1)
{
    if (*(s32*)(param_1 + 0x118) == 2) return (u32)(*(s32*)(param_1 + 0xe8) - 2) < 3;
    return false;
}
// 7100192260
bool FUN_7100192260(u8* param_1)
{
    if (*(s32*)(param_1 + 0x118) == 3) return (u32)(*(s32*)(param_1 + 0xe8) - 2) < 3;
    return false;
}
// 7100192ce0
bool FUN_7100192ce0(u8* param_1)
{
    if (*(s32*)(param_1 + 0x118) == 5) return (u32)(*(s32*)(param_1 + 0xe8) - 2) < 3;
    return false;
}

// -- FUN_7100193740 ----------------------------------------------------------
// Return true if *(param_1+0x38) non-null and byte at +0x84 != '\0'
// 7100193740
bool FUN_7100193740(u8* param_1)
{
    u64 p = *(u64*)(param_1 + 0x38);
    if (p != 0) return *(s8*)(p + 0x84) != '\0';
    return false;
}

// -- FUN_71001aa3d0 ----------------------------------------------------------
// SetDefault: zero + set constant fields
// 71001aa3d0
void FUN_71001aa3d0(u64* param_1)
{
    *(u64*)((u8*)param_1 + 0x44) = 0;
    param_1[6] = 0x40001f4ULL;
    param_1[7] = 0;
    *(u16*)(param_1 + 8) = 0x5fd;
    *(u8*)((u8*)param_1 + 0x42) = 0xff;
    *(u8*)((u8*)param_1 + 0x4c) = 0;
    param_1[10] = 0;
    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0;
}

// -- FUN_71001aca20 ----------------------------------------------------------
// Compute buffer size from dimensions in struct
// 71001aca20
s32 FUN_71001aca20(u8* param_1)
{
    s32 iVar2 = *(s32*)(param_1 + 0x3c);
    u32 uVar3 = (u32)iVar2 * (u32)*(u8*)(param_1 + 0x41) * (u32)iVar2;
    s32 iVar1 = 0;
    if ((uVar3 & 7) != 0) iVar1 = 8 - (s32)(uVar3 & 7);
    return iVar2 * 4 + ((s32)(iVar1 + uVar3) >> 3) + 4;
}

// -- FUN_71001ad2c0 ----------------------------------------------------------
// SetDefault: zero struct fields
// 71001ad2c0
void FUN_71001ad2c0(u64* param_1)
{
    param_1[0] = 0; param_1[1] = 0;
    *(u32*)(param_1 + 10) = 0;
    *(u32*)((u8*)param_1 + 0x5dc) = 0;
    param_1[2] = 0; param_1[3] = 0; param_1[4] = 0;
    param_1[5] = 0; param_1[6] = 0; param_1[7] = 0;
    param_1[8] = 0; param_1[9] = 0;
}

// -- FUN_71001ae5a0 ----------------------------------------------------------
// Find node in circular list where +0x10 == param_2; return &node+0x10 or null
// 71001ae5a0
s64* FUN_71001ae5a0(u8* param_1, s64 param_2)
{
    s64 lVar1 = *(s64*)(param_1 + 8);
    if (lVar1 == (s64)param_1) return nullptr;
    do {
        if (*(s64*)(lVar1 + 0x10) == param_2) return (s64*)(lVar1 + 0x10);
        lVar1 = *(s64*)(lVar1 + 8);
    } while (lVar1 != (s64)param_1);
    return nullptr;
}

// -- FUN_71001ae660 ----------------------------------------------------------
// Find node in circular list where +0x10 == param_2; return bool at +0x28
// 71001ae660
bool FUN_71001ae660(u8* param_1, s64 param_2)
{
    s64 lVar1 = *(s64*)(param_1 + 8);
    if (lVar1 == (s64)param_1) return false;
    do {
        if (*(s64*)(lVar1 + 0x10) == param_2) return *(s8*)(lVar1 + 0x28) != '\0';
        lVar1 = *(s64*)(lVar1 + 8);
    } while (lVar1 != (s64)param_1);
    return false;
}

// -- FUN_71001ae9f0 ----------------------------------------------------------
// Count nodes in circular list at +8
// 71001ae9f0
s32 FUN_71001ae9f0(u8* param_1)
{
    s64 lVar2 = *(s64*)(param_1 + 8);
    if (lVar2 != (s64)param_1) {
        s32 iVar1 = 0;
        do {
            lVar2 = *(s64*)(lVar2 + 8);
            iVar1++;
        } while (lVar2 != (s64)param_1);
        return iVar1;
    }
    return 0;
}

// -- FUN_71001afae0 ----------------------------------------------------------
// Update sum, count, min, max statistics at +0x40..+0x58
// 71001afae0
void FUN_71001afae0(u8* param_1, u64 param_2)
{
    *(u64*)(param_1 + 0x50) = *(u64*)(param_1 + 0x50) + param_2;
    *(u64*)(param_1 + 0x58) = *(u64*)(param_1 + 0x58) + 1;
    if (param_2 < *(u64*)(param_1 + 0x40)) {
        *(u64*)(param_1 + 0x40) = param_2;
    }
    if (param_2 > *(u64*)(param_1 + 0x48)) {
        *(u64*)(param_1 + 0x48) = param_2;
    }
}

// -- FUN_71001b1270 ----------------------------------------------------------
// Split u32 into quotient/remainder of 10000: returns (q | r<<32)
// 71001b1270
u64 FUN_71001b1270(u32 param_1)
{
    return (u64)param_1 / 10000 | (u64)(param_1 % 10000) << 0x20;
}

// -- FUN_71001b3140 ----------------------------------------------------------
// Clamped subtraction: max(0, *(param_1+8) - param_2)
// 71001b3140
void FUN_71001b3140(u8* param_1, u32 param_2)
{
    u32 uVar1 = *(u32*)(param_1 + 8);
    if (*(u32*)(param_1 + 8) <= param_2) uVar1 = param_2;
    *(u32*)(param_1 + 8) = uVar1 - param_2;
}

// -- FUN_71001b4220 ----------------------------------------------------------
// Set Result struct: check *param_2 for code; write to param_1, set line 0x74
// 71001b4220
void FUN_71001b4220(u32* param_1, s8* param_2)
{
    s8 cVar1 = *param_2;
    u32 uVar2 = 0x80010001;
    *(const char**)(param_1 + 2) = s_result_cpp;
    if (cVar1 != '\0') uVar2 = 0x10001;
    *param_1 = uVar2;
    param_1[4] = 0x74;
}

// -- FUN_71001b42a0 ----------------------------------------------------------
// Set Result struct: same pattern, line 0x91
// 71001b42a0
void FUN_71001b42a0(u32* param_1, s8* param_2)
{
    s8 cVar1 = *param_2;
    u32 uVar2 = 0x80010001;
    *(const char**)(param_1 + 2) = s_result_cpp;
    if (cVar1 != '\0') uVar2 = 0x10001;
    *param_1 = uVar2;
    param_1[4] = 0x91;
}

// -- FUN_71001b42e0 ----------------------------------------------------------
// Set Result struct: copy from param_2, set line 0xa1
// 71001b42e0
void FUN_71001b42e0(u32* param_1, u32* param_2)
{
    u32 uVar1 = *param_2;
    *(const char**)(param_1 + 2) = s_result_cpp;
    *param_1 = uVar1;
    param_1[4] = 0xa1;
}

// -- FUN_71001b7b50 ----------------------------------------------------------
// Return *param_1 if param_1[1]==6 or ==1; else 0
// 71001b7b50
u64 FUN_71001b7b50(u64* param_1)
{
    if (*(s32*)(param_1 + 1) == 6 || *(s32*)(param_1 + 1) == 1) return *param_1;
    return 0;
}

// -- FUN_71001b7b70 ----------------------------------------------------------
// Return *param_1 if param_1[1]==6 or ==1; else 0 (identical to FUN_71001b7b50)
// 71001b7b70
u64 FUN_71001b7b70(u64* param_1)
{
    if (*(s32*)(param_1 + 1) == 6 || *(s32*)(param_1 + 1) == 1) return *param_1;
    return 0;
}

// -- FUN_71001b7b90 ----------------------------------------------------------
// Return *param_1 (u32) if param_1[2]==6 or ==1; else 0
// 71001b7b90
u32 FUN_71001b7b90(u32* param_1)
{
    if (param_1[2] == 6 || param_1[2] == 1) return *param_1;
    return 0;
}

// -- FUN_71001b7bb0 ----------------------------------------------------------
// Return *param_1 (u32) if param_1[2]==6 or ==1; else 0 (identical)
// 71001b7bb0
u32 FUN_71001b7bb0(u32* param_1)
{
    if (param_1[2] == 6 || param_1[2] == 1) return *param_1;
    return 0;
}

// -- FUN_71001b7c80 ----------------------------------------------------------
// Copy *param_2 to *param_1 if param_2[1]==5; else zero *param_1
// 71001b7c80
void FUN_71001b7c80(u64* param_1, u64* param_2)
{
    if (*(s32*)(param_2 + 1) == 5) {
        *param_1 = *param_2;
        return;
    }
    *param_1 = 0;
}
