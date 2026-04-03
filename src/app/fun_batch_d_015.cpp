#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71037d-0x71038 address range, batch d-015
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int strcmp(const char*, const char*);

extern void  FUN_710356bb20(void);
extern void  FUN_710392e590(void*);
extern void  FUN_71037d7e30(void);
extern void  FUN_71037d9830(void);

namespace nu {
    extern void VirtualFreeHook(void*);
}

// External data
extern u8 PTR_VirtualFreeHook_71052a7a70[];

// ---- Functions ---------------------------------------------------------------

// 0x71037d1920 -- vtable call at *param_1+0xc0, return result + 0x20 (32 bytes)
s64 FUN_71037d1920(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x20;
}

// 0x71037d1940 -- vtable call at *param_1+0xc0, return result + 0x230 (32 bytes)
s64 FUN_71037d1940(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x230;
}

// 0x71037d1960 -- vtable call at *param_1+0xc0, return result + 0x338 (32 bytes)
s64 FUN_71037d1960(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x338;
}

// 0x71037d3b80 -- vtable call at *param_1+0xc0, return result + 0x20 (32 bytes)
s64 FUN_71037d3b80(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x20;
}

// 0x71037d3ba0 -- vtable call at *param_1+0xc0, return result + 0x230 (32 bytes)
s64 FUN_71037d3ba0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x230;
}

// 0x71037d3bc0 -- vtable call at *param_1+0xc0, return result + 0x338 (32 bytes)
s64 FUN_71037d3bc0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x338;
}

// 0x71037d5430 -- vtable call at *param_1+0xc0, return result + 0x20 (32 bytes)
s64 FUN_71037d5430(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x20;
}

// 0x71037d5450 -- vtable call at *param_1+0xc0, return result + 0x230 (32 bytes)
s64 FUN_71037d5450(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x230;
}

// 0x71037d5470 -- vtable call at *param_1+0xc0, return result + 0x338 (32 bytes)
s64 FUN_71037d5470(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x338;
}

// 0x71037d6e70 -- vtable call at *param_1+0xc0, return result + 0x20 (32 bytes)
s64 FUN_71037d6e70(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x20;
}

// 0x71037d6e90 -- vtable call at *param_1+0xc0, return result + 0x230 (32 bytes)
s64 FUN_71037d6e90(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x230;
}

// 0x71037d6eb0 -- vtable call at *param_1+0xc0, return result + 0x338 (32 bytes)
s64 FUN_71037d6eb0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x338;
}

// 0x71037d8890 -- vtable call at *param_1+0xc0, return result + 0x20 (32 bytes)
s64 FUN_71037d8890(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x20;
}

// 0x71037d88b0 -- vtable call at *param_1+0xc0, return result + 0x230 (32 bytes)
s64 FUN_71037d88b0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x230;
}

// 0x71037d88d0 -- vtable call at *param_1+0xc0, return result + 0x338 (32 bytes)
s64 FUN_71037d88d0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x338;
}

// 0x71037da290 -- vtable call at *param_1+0xc0, return result + 0x20 (32 bytes)
s64 FUN_71037da290(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x20;
}

// 0x71037da2b0 -- vtable call at *param_1+0xc0, return result + 0x230 (32 bytes)
s64 FUN_71037da2b0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x230;
}

// 0x71037da2d0 -- vtable call at *param_1+0xc0, return result + 0x338 (32 bytes)
s64 FUN_71037da2d0(s64 *param_1)
{
    s64 lVar1 = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return lVar1 + 0x338;
}

// 0x71037dc3b0 -- call helper, conditional VirtualFreeHook, then free (64 bytes)
void FUN_71037dc3b0(void *param_1)
{
    FUN_71037d7e30();
    if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        nu::VirtualFreeHook(param_1);
    }
    FUN_710392e590(param_1);
}

// 0x71037dc810 -- call helper, conditional VirtualFreeHook, then free (64 bytes)
void FUN_71037dc810(void *param_1)
{
    FUN_71037d9830();
    if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        nu::VirtualFreeHook(param_1);
    }
    FUN_710392e590(param_1);
}

// 0x7103835760 -- switch: copy two u64 fields or abort (64 bytes)
void FUN_7103835760(u32 param_1, u64 *param_2, u64 *param_3)
{
    switch (param_1) {
    case 0:
    case 1:
        param_3[1] = param_2[1];
        *param_3 = *param_2;
        return;
    default:
        FUN_710356bb20();
    }
}

// 0x7103839270 -- range check: abort if param_1 >= 4 (64 bytes)
void FUN_7103839270(u32 param_1)
{
    if (param_1 < 4) {
        return;
    }
    FUN_710356bb20();
}

// 0x7103841cf0 — abort wrapper (16 bytes)
u32 FUN_7103841cf0(void) { FUN_710356bb20(); }

// 0x7103841d00 — abort wrapper (16 bytes)
u32 FUN_7103841d00(void) { FUN_710356bb20(); }

// 0x71038e0bec -- strcmp returning negated result (36 bytes)
s32 FUN_71038e0bec(s64 param_1, u64 param_2, const char *param_3)
{
    return -strcmp((const char*)(param_1 + 4), param_3);
}

// 0x71038e150c -- strcmp returning negated result (36 bytes)
s32 FUN_71038e150c(s64 param_1, u64 param_2, const char *param_3)
{
    return -strcmp((const char*)(param_1 + 4), param_3);
}
