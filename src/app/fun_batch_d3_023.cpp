#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-023
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_71001cf300(u64, u64, s64);
extern void FUN_71001d2570(void);
extern void FUN_71001d2830(void);
extern void FUN_71001efaf0(s64);

// ---- Functions ---------------------------------------------------------------

// 0x71001cb860 — empty dtor: ~ChecksumAlgorithm (16 bytes)
void FUN_71001cb860(void)
{
}
// 0x71001cbc40 — GetLength: return ptr+0x18 - ptr+0x10 (16 bytes)
s64 FUN_71001cbc40(s64 param_1)
{
    return *(s64 *)(param_1 + 0x18) - *(s64 *)(param_1 + 0x10);
}

// 0x71001ce080 — GetChecksumLength: return 0x10 (16 bytes)
u64 FUN_71001ce080(void)
{
    return 0x10;
}
// 0x71001cfb70 — SetHeadShiftSize: swap field and adjust ptr (32 bytes)
void FUN_71001cfb70(s64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x28);
    *(s64 *)(param_1 + 0x28) = param_2;
    *(s64 *)(param_1 + 0x18) = (*(s64 *)(param_1 + 0x18) - param_2) + lVar1;
}

// 0x71001d0c80 — SetDependentConnection: write u64 to +0x70, u32 to +0x78 (16 bytes)
void FUN_71001d0c80(s64 param_1, u64 param_2, u32 param_3)
{
    *(u64 *)(param_1 + 0x70) = param_2;
    *(u32 *)(param_1 + 0x78) = param_3;
}
// 0x71001d6920 — GetContentPtr: if ptr+0x10 != ptr+0x18, return ptr+0x10 (16 bytes)
s64 FUN_71001d6920(s64 param_1)
{
    s64 lVar1;

    lVar1 = 0;
    if (*(s64 *)(param_1 + 0x10) != *(s64 *)(param_1 + 0x18)) {
        lVar1 = *(s64 *)(param_1 + 0x10);
    }
    return lVar1;
}

// 0x71001d6b80 — GetCurrentOperation: cond getter via ptr chain (32 bytes)
u64 FUN_71001d6b80(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x30) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0x20) + 0x10);
    }
    return 0;
}
// 0x710022b380 — SetProtocolID: write u16 param_2 to +0x48 (16 bytes)
void FUN_710022b380(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x48) = param_2;
}

// 0x710022b500 — FlagIsSet: (param_2 & ~*(u32*)(+0x60)) == 0 (16 bytes)
bool FUN_710022b500(s64 param_1, u32 param_2)
{
    return (param_2 & (*(u32 *)(param_1 + 0x60) ^ 0xffffffff)) == 0;
}
// 0x7100255b10 — SetExcludeLocked: write param_2&1 to byte at +0xc9 (16 bytes)
void FUN_7100255b10(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xc9) = param_2 & 1;
}

// 0x7100255b20 — SetVacantOnly: set byte at +0xc8, set u16 sentinel at +0xd0 (32 bytes)
void FUN_7100255b20(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xc8) = param_2 & 1;
    *(u16 *)(param_1 + 0xd0) = 1;
}

// 0x7100255b40 — SetExcludeNonHostPid: write param_2&1 to byte at +0xca (16 bytes)
void FUN_7100255b40(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xca) = param_2 & 1;
}

// 0x7100255b50 — SetExcludeUserPasswordSet: write param_2&1 to byte at +0x100 (16 bytes)
void FUN_7100255b50(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x100) = param_2 & 1;
}
