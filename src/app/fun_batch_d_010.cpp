#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71039 address range, batch d-010
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void  FUN_7103927800(u64);
extern u8   *FUN_71039297e0(u64);
extern u32   FUN_710392f0d0(void*, u32);

// External data
extern u8 DAT_7106dd3f1e[];

// ---- Functions ---------------------------------------------------------------

// 0x7103951030 — return *(u64*)(p+8) (32 bytes)
u64 FUN_7103951030(s64 param_1) { return *(u64*)(param_1 + 8); }

// 0x71039586f0 — identity u64 (32 bytes)
u64 FUN_71039586f0(u64 param_1) { return param_1; }

// 0x710395b850 — identity u64 (32 bytes)
u64 FUN_710395b850(u64 param_1) { return param_1; }

// 0x710395f460 — identity u64 (32 bytes)
u64 FUN_710395f460(u64 param_1) { return param_1; }

// 0x710392c5b0 — copy u64: *p1 = *p2 (48 bytes)
void FUN_710392c5b0(u64 *param_1, u64 *param_2) { *param_1 = *param_2; }

// 0x710392c5e0 — set two u32 fields to 1000 (48 bytes)
void FUN_710392c5e0(u32 *param_1)
{
    *param_1 = 1000;
    param_1[1] = 1000;
}

// 0x710393cdc0 — bitfield write: set bit 15 from param_2 & 1 (48 bytes)
void FUN_710393cdc0(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffff0000 | *param_1 & 0x7fff | (u64)(param_2 & 1) << 0xf;
}

// 0x710393cf00 — bitfield write: set bit 12 from param_2 & 1 (48 bytes)
void FUN_710393cf00(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffffe000 | *param_1 & 0xfff | (u64)(param_2 & 1) << 0xc;
}

// 0x710393e1a0 — bitfield write: set bits 16-17 from param_2 (48 bytes)
void FUN_710393e1a0(u64 *param_1, u32 param_2)
{
    *param_1 = *param_1 & 0xfffffffffffcffff | (u64)param_2 << 0x10;
}

// 0x710393f0b0 — bitfield write: set upper 40 bits from param_2 << 0x28 (48 bytes)
void FUN_710393f0b0(u64 *param_1, s64 param_2)
{
    *param_1 = *param_1 & 0xffffffffff | param_2 << 0x28;
}

// 0x710393f8d0 — rotate right by -(param_2) positions (48 bytes)
u64 FUN_710393f8d0(u64 param_1, s8 param_2)
{
    u64 n = (u64)(u32)(-(s32)param_2) & 0x3f;
    return param_1 >> n | param_1 << (0x40 - n);
}

// 0x7103940b60 — bitfield write: set bit 13 from param_2 & 1 (48 bytes)
void FUN_7103940b60(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffffc000 | *param_1 & 0x1fff | (u64)(param_2 & 1) << 0xd;
}

// 0x7103941c00 — bitfield write: set bit 14 from param_2 & 1 (48 bytes)
void FUN_7103941c00(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffff8000 | *param_1 & 0x3fff | (u64)(param_2 & 1) << 0xe;
}

// 0x7103944e60 — bitfield: clear bit 13 (48 bytes)
void FUN_7103944e60(u64 *param_1) { *param_1 = *param_1 & 0xffffffffffffefff; }

// 0x7103944ed0 — set upper 40 bits from param_2 (48 bytes)
void FUN_7103944ed0(u64 *param_1, s64 param_2)
{
    *param_1 = *param_1 & 0xffffffffff | param_2 << 0x28;
}

// 0x7103944f00 — clear bits 16-17 (48 bytes)
void FUN_7103944f00(u64 *param_1) { *param_1 = *param_1 & 0xfffffffffffcffff; }

// 0x7103944f30 — set bit 15 (48 bytes)
void FUN_7103944f30(u64 *param_1)
{
    *param_1 = *param_1 & 0xffffffffffff0000 | *param_1 & 0x7fff | 0x8000;
}

// 0x7103944f60 — set bit 13 (48 bytes)
void FUN_7103944f60(u64 *param_1)
{
    *param_1 = *param_1 & 0xffffffffffffc000 | *param_1 & 0x1fff | 0x2000;
}

// 0x7103944f90 — set bit 14 (48 bytes)
void FUN_7103944f90(u64 *param_1)
{
    *param_1 = *param_1 & 0xffffffffffff8000 | *param_1 & 0x3fff | 0x4000;
}

// 0x7103945ca0 — write lower 16 bits into *(p+0x10) (48 bytes)
void FUN_7103945ca0(s64 param_1, u16 param_2)
{
    *(u64*)(param_1 + 0x10) = *(u64*)(param_1 + 0x10) & 0xffffffffffff0000 | (u64)param_2;
}

// 0x71039576f0 — copy u64: *p1 = *p2 (48 bytes)
void FUN_71039576f0(u64 *param_1, u64 *param_2) { *param_1 = *param_2; }

// 0x710395a470 — decrement field at +0x18, set byte at +0x1c to 1 (48 bytes)
void FUN_710395a470(s64 param_1)
{
    *(s32*)(param_1 + 0x18) = *(s32*)(param_1 + 0x18) - 1;
    *(u8*)(param_1 + 0x1c) = 1;
}

// 0x710395aad0 — increment field at +0x18, clear byte at +0x1c (48 bytes)
void FUN_710395aad0(s64 param_1)
{
    *(s32*)(param_1 + 0x18) = *(s32*)(param_1 + 0x18) + 1;
    *(u8*)(param_1 + 0x1c) = 0;
}

// 0x710395d380 — set two u32 fields to 0x9e (48 bytes)
void FUN_710395d380(u32 *param_1)
{
    *param_1 = 0x9e;
    param_1[1] = 0x9e;
}

// 0x7103929420 — no-op (48 bytes)
void FUN_7103929420(void) { return; }

// 0x7103931320 — return *(u64*)(p+8) & 0xffffffffffff0000 (48 bytes)
u64 FUN_7103931320(s64 param_1) { return *(u64*)(param_1 + 8) & 0xffffffffffff0000; }

// 0x7103931e50 — return *param_1 >> 0x1a & 0x3fff (48 bytes)
u64 FUN_7103931e50(u64 *param_1) { return *param_1 >> 0x1a & 0x3fff; }

// 0x710393cfe0 — return *(u64*)(p+8) & 0xffffffffffff0000 (48 bytes)
u64 FUN_710393cfe0(s64 param_1) { return *(u64*)(param_1 + 8) & 0xffffffffffff0000; }

// 0x71039533b0 — return *(u64*)(p+8) & 0xffffffffffff0000 (48 bytes)
u64 FUN_71039533b0(s64 param_1) { return *(u64*)(param_1 + 8) & 0xffffffffffff0000; }

// 0x7103957d60 — no-op (48 bytes)
void FUN_7103957d60(void) { return; }

// 0x710392f020 — call FUN_710392f0d0 and return bit 0 (48 bytes)
u32 FUN_710392f020(void)
{
    return FUN_710392f0d0(DAT_7106dd3f1e, 0) & 1;
}

// 0x71039737f0 — vtable call at 0x70 on nested field, return 0 (48 bytes)
u64 FUN_71039737f0(s64 param_1)
{
    s64 lVar1 = *(s64*)(*(s64*)(param_1 + 8) + 0x18);
    (*(void(*)(s64))(*(s64*)(lVar1 + 0x70)))(lVar1 + 0x90);
    return 0;
}

// 0x7103978f20 — call function ptr at +0x28 with offset fields, return 0 (48 bytes)
u64 FUN_7103978f20(s64 param_1, s64 param_2, u64 param_3)
{
    (*(void(*)(s64, u64, u32))(*(s64*)(param_1 + 0x28)))(param_1 + 0x60, param_3, *(u32*)(param_2 + 0xd4));
    return 0;
}

// 0x710397c090 — store u32 at +0x84, vtable call at +0x40, return 0 (48 bytes)
u64 FUN_710397c090(u32 param_1, s64 *param_2)
{
    *(u32*)((s64)param_2 + 0x84) = param_1;
    (*(void(*)(u32))(*(s64*)(*(s64*)param_2 + 0x40)))(*(u32*)((s64)param_2 + 0x7c));
    return 0;
}

// 0x71039277d0 — wrapper: FUN_7103927800(param_1) (48 bytes)
void FUN_71039277d0(u64 param_1) { FUN_7103927800(param_1); }

// 0x7103927b00 — deref byte from FUN_71039297e0(param_1) (48 bytes)
u8 FUN_7103927b00(u64 param_1) { return *FUN_71039297e0(param_1); }
