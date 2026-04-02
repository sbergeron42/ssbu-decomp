#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch e2-005
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

extern "C" void FUN_71032e5640(u64);
extern "C" void FUN_71035231c0(u64);
extern "C" u64  DAT_710532e7c8;

// ---- struct getters/setters (stack-spill pattern) -----------------------------------------------
// Note: original uses sub/str/ldr stack spill — compiles correctly, may not verify

// 0x71037b6750 — return bit 0 of *(u8 *)(param_1 + 0x3a) (24 bytes)
u8 FUN_71037b6750(s64 param_1)
{
    return *(u8 *)(param_1 + 0x3a) & 1;
}

// 0x71037b73a0 — return *(u32 *)(param_1 + 0x408) (24 bytes)
u32 FUN_71037b73a0(s64 param_1)
{
    return *(u32 *)(param_1 + 0x408);
}

// 0x71037b7970 — OR bit 3 into *(u32 *)(param_1 + 0x8) (20 bytes)
void FUN_71037b7970(s64 param_1)
{
    *(u32 *)(param_1 + 0x8) = *(u32 *)(param_1 + 0x8) | 8;
}

// 0x71037b8940 — return *param_1 (u32) (20 bytes)
u32 FUN_71037b8940(u32 *param_1)
{
    return *param_1;
}

// 0x71037b8960 — zero-init three u32 fields at +0x38, +0x3c, +0x40 (28 bytes)
void FUN_71037b8960(s64 param_1)
{
    *(u32 *)(param_1 + 0x38) = 0;
    *(u32 *)(param_1 + 0x40) = 0;
    *(u32 *)(param_1 + 0x3c) = 0;
}

// 0x71037b89c0 — return bit 2 of *(u8 *)(param_1 + 0x8) (28 bytes)
u8 FUN_71037b89c0(s64 param_1)
{
    return (*(u8 *)(param_1 + 0x8) >> 2) & 1;
}

// 0x71037b8a40 — return *(u64 *)(param_1 + 0x68) (24 bytes)
u64 FUN_71037b8a40(s64 param_1)
{
    return *(u64 *)(param_1 + 0x68);
}

// 0x71037b9690 — return bit 3 of *(u16 *)(param_1 + 0x4) (28 bytes)
u16 FUN_71037b9690(s64 param_1)
{
    return (*(u16 *)(param_1 + 0x4) >> 3) & 1;
}

// 0x71037b97a0 — return *(u64 *)(param_1 + 0x18) (24 bytes)
u64 FUN_71037b97a0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x18);
}

// 0x71037b9c10 — return param_1 + 0xc (20 bytes)
s64 FUN_71037b9c10(s64 param_1)
{
    return param_1 + 0x0c;
}

// 0x71037bfd80 — return param_1 + 0x78 (20 bytes)
s64 FUN_71037bfd80(s64 param_1)
{
    return param_1 + 0x78;
}

// ---- vtable dispatch + offset (32 bytes each) -----------------------------------------------
// Pattern: ldr x8,[x0]; ldr x8,[x8,#0xc0]; blr x8; add x0,x0,#offset; ret

// 0x71037d1920 — vtable[0xc0/8]() + 0x20
s64 FUN_71037d1920(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x20;
}

// 0x71037d1940 — vtable[0xc0/8]() + 0x230
s64 FUN_71037d1940(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x230;
}

// 0x71037d1960 — vtable[0xc0/8]() + 0x338
s64 FUN_71037d1960(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x338;
}

// 0x71037d3b80 — vtable[0xc0/8]() + 0x20
s64 FUN_71037d3b80(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x20;
}

// 0x71037d3ba0 — vtable[0xc0/8]() + 0x230
s64 FUN_71037d3ba0(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x230;
}

// 0x71037d3bc0 — vtable[0xc0/8]() + 0x338
s64 FUN_71037d3bc0(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x338;
}

// 0x71037d5430 — vtable[0xc0/8]() + 0x20
s64 FUN_71037d5430(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x20;
}

// 0x71037d5450 — vtable[0xc0/8]() + 0x230
s64 FUN_71037d5450(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x230;
}

// 0x71037d5470 — vtable[0xc0/8]() + 0x338
s64 FUN_71037d5470(s64 *param_1)
{
    s64 lVar1 = (**(s64 (**)(s64 *))(*param_1 + 0xc0))(param_1);
    return lVar1 + 0x338;
}

// ---- simple wrappers -----------------------------------------------

// 0x71033669a0 — FUN_71032e5640(DAT_710532e7c8), return 0 (28 bytes)
u64 FUN_71033669a0(void)
{
    FUN_71032e5640(DAT_710532e7c8);
    return 0;
}

// 0x71035237f0 — FUN_71035231c0(*(u64*)(param_2+0x20)), return 1 (28 bytes)
u64 FUN_71035237f0(u64 param_1, s64 param_2)
{
    FUN_71035231c0(*(u64 *)(param_2 + 0x20));
    return 1;
}
