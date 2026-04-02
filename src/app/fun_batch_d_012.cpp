#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71031 / 0x71037b address range, batch d-012
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" float sqrtf(float);

extern void FUN_71037af510(u64);

// External data (vtable/label pointers)
extern u8 PTR_FUN_71052406a8[];
extern u8 PTR_LAB_710517b8e0[] __attribute__((visibility("hidden")));

// ---- Functions ---------------------------------------------------------------

// 0x71037b0650 — offset + stride (48 bytes)
s64 FUN_71037b0650(s64 param_1, s32 param_2) { return *(s64*)(param_1 + 0x10) + (s64)param_2 * 8; }

// 0x71037b0c80 — copy u64 at +8 from p2 to p1 (32 bytes)
void FUN_71037b0c80(s64 param_1, s64 param_2) { *(u64*)(param_1 + 8) = *(u64*)(param_2 + 8); }

// 0x71037b0cb0 — write vtable pointer (32 bytes)
void FUN_71037b0cb0(u64 *param_1) { *param_1 = (u64)PTR_FUN_71052406a8; }

// 0x71037b2bc0 — return bit 1 of byte at +0x19298 (32 bytes)
u8 FUN_71037b2bc0(s64 param_1) { return *(u8*)(param_1 + 0x19298) >> 1 & 1; }

// 0x71037b3130 — return *(u64*)(p+0x60) (32 bytes)
u64 FUN_71037b3130(s64 param_1) { return *(u64*)(param_1 + 0x60); }

// 0x71037b3150 — return *(u64*)(p+0x68) (32 bytes)
u64 FUN_71037b3150(s64 param_1) { return *(u64*)(param_1 + 0x68); }

// 0x71037b3600 — return bit 5 of *(u16*)(p+4) (32 bytes)
u16 FUN_71037b3600(s64 param_1) { return *(u16*)(param_1 + 4) >> 5 & 1; }

// 0x71037b3620 — init u16 triple: {1, 0xffff, 0} (48 bytes)
void FUN_71037b3620(u16 *param_1)
{
    *param_1 = 1;
    param_1[1] = 0xffff;
    param_1[2] = 0;
}

// 0x71037b4430 — return *(s32*)(p+0x1c) == -1 (32 bytes)
u8 FUN_71037b4430(s64 param_1) { return (u8)(*(s32*)(param_1 + 0x1c) == -1); }

// 0x71037b52d0 — return *(u64*)(p+0x10) (32 bytes)
u64 FUN_71037b52d0(s64 param_1) { return *(u64*)(param_1 + 0x10); }

// 0x71037b52f0 — return bit 1 of byte at +8 (32 bytes)
u8 FUN_71037b52f0(s64 param_1) { return *(u8*)(param_1 + 8) >> 1 & 1; }

// 0x71037b5570 — return *(u32*)(p+0x70) (32 bytes)
u64 FUN_71037b5570(s64 param_1) { return *(u32*)(param_1 + 0x70); }

// 0x71037b5590 — return *(u32*)(p+0x74) (32 bytes)
u64 FUN_71037b5590(s64 param_1) { return *(u32*)(param_1 + 0x74); }

// 0x71037b55b0 — return *(u64*)(p+0x18) (32 bytes)
u64 FUN_71037b55b0(s64 param_1) { return *(u64*)(param_1 + 0x18); }

// 0x71037b55d0 — return bit 1 of *(u16*)(p+4) (32 bytes)
u16 FUN_71037b55d0(s64 param_1) { return *(u16*)(param_1 + 4) >> 1 & 1; }

// 0x71037b5650 — offset + stride*0x28 (48 bytes)
s64 FUN_71037b5650(s64 param_1, s32 param_2) { return *(s64*)(param_1 + 8) + (s64)param_2 * 0x28; }

// 0x71037b6320 — indexed u64 field in stride-0x28 array (48 bytes)
u64 FUN_71037b6320(s64 param_1, s32 param_2)
{
    return *(u64*)(*(s64*)(param_1 + 8) + (s64)param_2 * 0x28 + 0x10);
}

// 0x71037b6730 — return *(u64*)(p+0x88) (32 bytes)
u64 FUN_71037b6730(s64 param_1) { return *(u64*)(param_1 + 0x88); }

// 0x71037b6750 — return bit 0 of byte at +0x3a (32 bytes)
u8 FUN_71037b6750(s64 param_1) { return *(u8*)(param_1 + 0x3a) & 1; }

// 0x71037b72b0 — init self-ref list head + counters (48 bytes)
void FUN_71037b72b0(s64 *param_1)
{
    *param_1 = (s64)(param_1 + 1);
    *(u32*)(param_1 + 0x81) = 0;
    *(u32*)((s64)param_1 + 0x40c) = 0x100;
}

// 0x71037b73a0 — return *(u32*)(p+0x408) (32 bytes)
u64 FUN_71037b73a0(s64 param_1) { return *(u32*)(param_1 + 0x408); }

// 0x71037b73c0 — stack pop: decrement counter, return indexed element (48 bytes)
u64 FUN_71037b73c0(s64 *param_1)
{
    *(s32*)(param_1 + 0x81) = (s32)param_1[0x81] + -1;
    return *(u32*)(*param_1 + (s64)(s32)param_1[0x81] * 4);
}

// 0x71037b7970 — set bit 3 of *(u32*)(p+8) (32 bytes)
void FUN_71037b7970(s64 param_1) { *(u32*)(param_1 + 8) = *(u32*)(param_1 + 8) | 8; }

// 0x71037b7c60 — store u64 at +0x19308 (32 bytes)
void FUN_71037b7c60(s64 param_1, u64 param_2) { *(u64*)(param_1 + 0x19308) = param_2; }

// 0x71037b7c90 — store u64 at +0x19310 (32 bytes)
void FUN_71037b7c90(s64 param_1, u64 param_2) { *(u64*)(param_1 + 0x19310) = param_2; }

// 0x71037b8940 — deref u32 (32 bytes)
u64 FUN_71037b8940(u32 *param_1) { return *param_1; }

// 0x71037b8960 — clear three u32 fields at +0x38/0x3c/0x40 (48 bytes)
void FUN_71037b8960(s64 param_1)
{
    *(u32*)(param_1 + 0x38) = 0;
    *(u32*)(param_1 + 0x3c) = 0;
    *(u32*)(param_1 + 0x40) = 0;
}

// 0x71037b8980 — push param_2 into indexed array, store index at param_2+8 (48 bytes)
void FUN_71037b8980(s64 param_1, s64 param_2)
{
    *(u32*)(param_2 + 8) = *(u32*)(param_1 + 0x38);
    *(s64*)(*(s64*)(param_1 + 0x10) + (s64)*(s32*)(param_1 + 0x38) * 8) = param_2;
    *(s32*)(param_1 + 0x38) = *(s32*)(param_1 + 0x38) + 1;
}

// 0x71037b89c0 — return bit 2 of byte at +8 (32 bytes)
u8 FUN_71037b89c0(s64 param_1) { return *(u8*)(param_1 + 8) >> 2 & 1; }

// 0x71037b89e0 — append param_2 to *(p+0x18)[count++] at +0x40 (48 bytes)
void FUN_71037b89e0(s64 param_1, u64 param_2)
{
    s32 iVar1 = *(s32*)(param_1 + 0x40);
    *(s32*)(param_1 + 0x40) = iVar1 + 1;
    *(u64*)(*(s64*)(param_1 + 0x18) + (s64)iVar1 * 8) = param_2;
}

// 0x71037b8a10 — append param_2 to *(p+0x20)[count++] at +0x3c (48 bytes)
void FUN_71037b8a10(s64 param_1, u64 param_2)
{
    s32 iVar1 = *(s32*)(param_1 + 0x3c);
    *(s32*)(param_1 + 0x3c) = iVar1 + 1;
    *(u64*)(*(s64*)(param_1 + 0x20) + (s64)iVar1 * 8) = param_2;
}

// 0x71037b8a40 — return *(u64*)(p+0x68) (32 bytes)
u64 FUN_71037b8a40(s64 param_1) { return *(u64*)(param_1 + 0x68); }

// 0x71037b9690 — return bit 3 of *(u16*)(p+4) (32 bytes)
u16 FUN_71037b9690(s64 param_1) { return *(u16*)(param_1 + 4) >> 3 & 1; }

// 0x71037b97a0 — return *(u64*)(p+0x18) (32 bytes)
u64 FUN_71037b97a0(s64 param_1) { return *(u64*)(param_1 + 0x18); }

// 0x71037b9be0 — wrapper: FUN_71037af510(*(p+0x18)) (48 bytes)
void FUN_71037b9be0(s64 param_1) { FUN_71037af510(*(u64*)(param_1 + 0x18)); }

// 0x71037b9c10 — return param_1 + 0xc (32 bytes)
s64 FUN_71037b9c10(s64 param_1) { return param_1 + 0xc; }

// 0x71037bc690 — sqrtf(p1*p2), result discarded (48 bytes)
void FUN_71037bc690(float param_1, float param_2) { sqrtf(param_1 * param_2); }

// FUN_71031758c0 is defined in fun_batch_d_001.cpp
