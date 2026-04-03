#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100174000-0x7100b8000
// Pool-d worker: auto-generated from Ghidra decompilation

extern u8* PTR_DAT_71052a53d8;
extern u8* PTR_DAT_71052a53e0;
extern u8* PTR_DAT_71052a53e8;
extern void* PTR_DAT_71052a5528;

static const char* s_result_cpp =
    "C:/home/ws/hac-appc2/Pack/7923402a/OnlineCore/src/Platform/Core/Result.cpp";

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
