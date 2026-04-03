#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-022
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------
// 0x71001aea30 — SetAvailableEntryNum: clamp-write param_2 to +0x48 (32 bytes)
void FUN_71001aea30(s64 param_1, u32 param_2)
{
    if (param_2 <= *(u32 *)(param_1 + 0x38)) {
        *(u32 *)(param_1 + 0x48) = param_2;
    }
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
// 0x71001b11f0 — GetFacility: return bits [10:0] of u16 at +2 (16 bytes)
u16 FUN_71001b11f0(s64 param_1)
{
    return *(u16 *)(param_1 + 2) & 0x7ff;
}
// 0x71001b20e0 — GetMaxUnitSize: if ptr at +0x60 != 0, return u64 at *(ptr)+0x10 (32 bytes)
u64 FUN_71001b20e0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x60) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0x60) + 0x10);
    }
    return 0;
}
// 0x71001b3e70 — clear: zero three u64 fields at +0x20, +0x28, +0x30 (16 bytes)
void FUN_71001b3e70(s64 param_1)
{
    *(u64 *)(param_1 + 0x28) = 0;
    *(u64 *)(param_1 + 0x30) = 0;
    *(u64 *)(param_1 + 0x20) = 0;
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
// 0x71001bef00 — empty dtor: ~InetAddress (32 bytes)
void FUN_71001bef00(void)
{
}
