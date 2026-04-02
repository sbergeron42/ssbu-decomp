#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-022
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------

// 0x710019b540 — setter: write u64 param_2 to +0x48 (16 bytes)
void FUN_710019b540(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x48) = param_2;
}

// 0x710019b550 — setter: write u64 param_2 to +0x50 (16 bytes)
void FUN_710019b550(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x50) = param_2;
}

// 0x71001a35e0 — init: zero u64 at +0x78, set u32 sentinel 0xffff00 at +0x80 (16 bytes)
void FUN_71001a35e0(s64 param_1)
{
    *(u64 *)(param_1 + 0x78) = 0;
    *(u32 *)(param_1 + 0x80) = 0xffff00;
}

// 0x71001a87c0 — clear: zero u32 at +0xf8 (16 bytes)
void FUN_71001a87c0(s64 param_1)
{
    *(u32 *)(param_1 + 0xf8) = 0;
}

// 0x71001aa410 — empty stub (16 bytes)
void FUN_71001aa410(void)
{
}

// 0x71001ac5b0 — empty stub (16 bytes)
void FUN_71001ac5b0(void)
{
}

// 0x71001ad2e0 — empty stub (16 bytes)
void FUN_71001ad2e0(void)
{
}

// 0x71001aea30 — SetAvailableEntryNum: clamp-write param_2 to +0x48 (32 bytes)
void FUN_71001aea30(s64 param_1, u32 param_2)
{
    if (param_2 <= *(u32 *)(param_1 + 0x38)) {
        *(u32 *)(param_1 + 0x48) = param_2;
    }
}

// 0x71001aea50 — empty stub (16 bytes)
void FUN_71001aea50(void)
{
}

// 0x71001aea70 — empty stub (16 bytes)
void FUN_71001aea70(void)
{
}

// 0x71001aead0 — SetBaseTime: copy u64 from param_2, set flag byte (32 bytes)
void FUN_71001aead0(u64 *param_1, u64 *param_2)
{
    *param_1 = *param_2;
    *(u8 *)(param_1 + 1) = 1;
}

// 0x71001aeaf0 — ClearBaseTime: clear flag byte, zero u64 (16 bytes)
void FUN_71001aeaf0(u64 *param_1)
{
    *(u8 *)(param_1 + 1) = 0;
    *param_1 = 0;
}

// 0x71001b04e0 — copy: write *param_2 into *param_1 (u64) (16 bytes)
void FUN_71001b04e0(u64 *param_1, u64 *param_2)
{
    *param_1 = *param_2;
}

// 0x71001b0590 — getter: return *param_1 (u64) (16 bytes)
u64 FUN_71001b0590(u64 *param_1)
{
    return *param_1;
}

// 0x71001b05a0 — getter: return *param_1 (u64) — operator cast (16 bytes)
u64 FUN_71001b05a0(u64 *param_1)
{
    return *param_1;
}

// 0x71001b08c0 — GetYear: return bits [43:30] of u64 (16 bytes)
u64 FUN_71001b08c0(u64 *param_1)
{
    return *param_1 >> 0x1a & 0x3fff;
}

// 0x71001b08e0 — GetDay: return bits [21:17] of u32 (16 bytes)
u32 FUN_71001b08e0(u32 *param_1)
{
    return *param_1 >> 0x11 & 0x1f;
}

// 0x71001b08f0 — GetHour: return bits [16:12] of u32 (16 bytes)
u32 FUN_71001b08f0(u32 *param_1)
{
    return *param_1 >> 0xc & 0x1f;
}

// 0x71001b0900 — GetMinute: return bits [11:6] of u32 (16 bytes)
u32 FUN_71001b0900(u32 *param_1)
{
    return *param_1 >> 6 & 0x3f;
}

// 0x71001b0910 — GetSecond: return bits [5:0] of byte (32 bytes)
u8 FUN_71001b0910(u8 *param_1)
{
    return *param_1 & 0x3f;
}

// 0x71001b11f0 — GetFacility: return bits [10:0] of u16 at +2 (16 bytes)
u16 FUN_71001b11f0(s64 param_1)
{
    return *(u16 *)(param_1 + 2) & 0x7ff;
}

// 0x71001b17c0 — getter: return u64 at +0x10 (32 bytes)
u64 FUN_71001b17c0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x10);
}

// 0x71001b20e0 — GetMaxUnitSize: if ptr at +0x60 != 0, return u64 at *(ptr)+0x10 (32 bytes)
u64 FUN_71001b20e0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x60) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0x60) + 0x10);
    }
    return 0;
}

// 0x71001b3130 — accumulate: *(s32*)(+8) += param_2 (16 bytes)
void FUN_71001b3130(s64 param_1, s32 param_2)
{
    *(s32 *)(param_1 + 8) = *(s32 *)(param_1 + 8) + param_2;
}

// 0x71001b3140 — subtract with floor-zero: *(u32*)(+8) = max(val - param_2, 0) (32 bytes)
void FUN_71001b3140(s64 param_1, u32 param_2)
{
    u32 uVar1;

    uVar1 = *(u32 *)(param_1 + 8);
    if (*(u32 *)(param_1 + 8) <= param_2) {
        uVar1 = param_2;
    }
    *(u32 *)(param_1 + 8) = uVar1 - param_2;
}

// 0x71001b32f0 — clear: zero byte at +0x121 (16 bytes)
void FUN_71001b32f0(s64 param_1)
{
    *(u8 *)(param_1 + 0x121) = 0;
}

// 0x71001b3e70 — clear: zero three u64 fields at +0x20, +0x28, +0x30 (16 bytes)
void FUN_71001b3e70(s64 param_1)
{
    *(u64 *)(param_1 + 0x28) = 0;
    *(u64 *)(param_1 + 0x30) = 0;
    *(u64 *)(param_1 + 0x20) = 0;
}

// 0x71001b3ef0 — empty stub (16 bytes)
void FUN_71001b3ef0(void)
{
}

// 0x71001b42e0 — ResultInfo init: copy u32, set string ptr, set code 0xa1 (32 bytes)
void FUN_71001b42e0(u32 *param_1, u32 *param_2)
{
    u32 uVar1;

    uVar1 = *param_2;
    *(const char **)(param_1 + 2) =
         "C:/home/ws/hac-appc2/Pack/7923402a/OnlineCore/src/Platform/Core/Result.cpp";
    *param_1 = uVar1;
    param_1[4] = 0xa1;
}

// 0x71001b4730 — empty stub (48 bytes)
void FUN_71001b4730(void)
{
}

// 0x71001b6060 — GetBuffer: return *param_1 (u64) (16 bytes)
u64 FUN_71001b6060(u64 *param_1)
{
    return *param_1;
}

// 0x71001b6070 — GetBufferSize: return u64 at +8 (16 bytes)
u64 FUN_71001b6070(s64 param_1)
{
    return *(u64 *)(param_1 + 8);
}

// 0x71001b6170 — GetLength: return *(ptr+0x18) - *(ptr+8) (16 bytes)
s64 FUN_71001b6170(s64 param_1)
{
    return *(s64 *)(param_1 + 0x18) - *(s64 *)(param_1 + 8);
}

// 0x71001b7b40 — getter: return u32 at +8 (16 bytes)
u32 FUN_71001b7b40(s64 param_1)
{
    return *(u32 *)(param_1 + 8);
}

// 0x71001b7b50 — cond: if type==6||1, return u64 at *param_1, else 0 (32 bytes)
u64 FUN_71001b7b50(u64 *param_1)
{
    if (*(s32 *)(param_1 + 1) == 6 || *(s32 *)(param_1 + 1) == 1) {
        return *param_1;
    }
    return 0;
}

// 0x71001b7b70 — cond: if type==6||1, return u64 at *param_1, else 0 (32 bytes)
u64 FUN_71001b7b70(u64 *param_1)
{
    if (*(s32 *)(param_1 + 1) == 6 || *(s32 *)(param_1 + 1) == 1) {
        return *param_1;
    }
    return 0;
}

// 0x71001b7b90 — cond: if type==6||1, return u32 at *param_1, else 0 (32 bytes)
u32 FUN_71001b7b90(u32 *param_1)
{
    if (param_1[2] == 6 || param_1[2] == 1) {
        return *param_1;
    }
    return 0;
}

// 0x71001b7bb0 — cond: if type==6||1, return u32 at *param_1, else 0 (32 bytes)
u32 FUN_71001b7bb0(u32 *param_1)
{
    if (param_1[2] == 6 || param_1[2] == 1) {
        return *param_1;
    }
    return 0;
}

// 0x71001beae0 — constant: return 1 (16 bytes)
u64 FUN_71001beae0(void)
{
    return 1;
}

// 0x71001beaf0 — constant: return 1 (16 bytes)
u64 FUN_71001beaf0(void)
{
    return 1;
}

// 0x71001bef00 — empty dtor: ~InetAddress (32 bytes)
void FUN_71001bef00(void)
{
}

// 0x71001bef90 — setter: write u32 param_2 to +0xc (16 bytes)
void FUN_71001bef90(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0xc) = param_2;
}

// 0x71001bf250 — getter: return u32 at *param_1 (16 bytes)
u32 FUN_71001bf250(u32 *param_1)
{
    return *param_1;
}

// 0x71001bf260 — getter: return u32 at +4 (32 bytes)
u32 FUN_71001bf260(s64 param_1)
{
    return *(u32 *)(param_1 + 4);
}

// 0x71001bf280 — clear: zero u32 and u64 fields (16 bytes)
void FUN_71001bf280(u32 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 2) = 0;
}

// 0x71001c38c0 — offset: return param_1 + 8 (16 bytes)
s64 FUN_71001c38c0(s64 param_1)
{
    return param_1 + 8;
}
