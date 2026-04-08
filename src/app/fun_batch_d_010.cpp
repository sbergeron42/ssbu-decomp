#include "types.h"

// Batch D - 010: bitfield accessors, identity functions, small helpers (0x71039 range)

#define VT(m) (*reinterpret_cast<void***>(m))

// ---- External declarations -----------------------------------------------

extern void  FUN_7103927800(u64);
extern u8   *FUN_71039297e0(u64);
extern u32   FUN_710392f0d0(void*, u32);

// External data
extern u8 DAT_7106dd3f1e[];

// ---- Functions ---------------------------------------------------------------

// 0x7103951030 -- return *(u64*)(p+8) (32 bytes)
// +0x08 [inferred: u64 field, read and returned directly]
u64 FUN_7103951030(s64 param_1) { return *(u64*)(param_1 + 8); }

// 0x71039586f0 -- identity u64 (32 bytes)
__attribute__((optnone))
u64 FUN_71039586f0(u64 param_1) { return param_1; }

// 0x710395b850 -- identity u64 (32 bytes)
__attribute__((optnone))
u64 FUN_710395b850(u64 param_1) { return param_1; }

// 0x710395f460 -- identity u64 (32 bytes)
__attribute__((optnone))
u64 FUN_710395f460(u64 param_1) { return param_1; }

// 0x710392c5b0 -- copy u64: *p1 = *p2 (48 bytes)
__attribute__((optnone))
void FUN_710392c5b0(u64 *param_1, u64 *param_2) { *param_1 = *param_2; }

// 0x710392c5e0 -- set two u32 fields to 1000 (48 bytes)
__attribute__((optnone))
void FUN_710392c5e0(u32 *param_1)
{
    *param_1 = 1000;
    param_1[1] = 1000;
}

// 0x710393cdc0 -- bitfield write: set bit 15 from param_2 & 1 (48 bytes)
__attribute__((optnone))
void FUN_710393cdc0(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffff0000 | *param_1 & 0x7fff | (u64)(param_2 & 1) << 0xf;
}

// 0x710393cf00 -- bitfield write: set bit 12 from param_2 & 1 (48 bytes)
__attribute__((optnone))
void FUN_710393cf00(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffffe000 | *param_1 & 0xfff | (u64)(param_2 & 1) << 0xc;
}

// 0x710393e1a0 -- bitfield write: set bits 16-17 from param_2 (48 bytes)
__attribute__((optnone))
void FUN_710393e1a0(u64 *param_1, u32 param_2)
{
    *param_1 = *param_1 & 0xfffffffffffcffff | (u64)param_2 << 0x10;
}

// 0x710393f0b0 -- bitfield write: set upper 40 bits from param_2 << 0x28 (48 bytes)
__attribute__((optnone))
void FUN_710393f0b0(u64 *param_1, s64 param_2)
{
    *param_1 = *param_1 & 0xffffffffff | param_2 << 0x28;
}

// 0x710393f8d0 -- rotate right by -(param_2) positions (48 bytes)
__attribute__((optnone))
u64 FUN_710393f8d0(u64 param_1, s8 param_2)
{
    u64 n = (u64)(u32)(-(s32)param_2) & 0x3f;
    return param_1 >> n | param_1 << (0x40 - n);
}

// 0x7103940b60 -- bitfield write: set bit 13 from param_2 & 1 (48 bytes)
__attribute__((optnone))
void FUN_7103940b60(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffffc000 | *param_1 & 0x1fff | (u64)(param_2 & 1) << 0xd;
}

// 0x7103941c00 -- bitfield write: set bit 14 from param_2 & 1 (48 bytes)
__attribute__((optnone))
void FUN_7103941c00(u64 *param_1, u8 param_2)
{
    *param_1 = *param_1 & 0xffffffffffff8000 | *param_1 & 0x3fff | (u64)(param_2 & 1) << 0xe;
}

// 0x7103944e60 -- bitfield: clear bit 13 (48 bytes)
__attribute__((optnone))
void FUN_7103944e60(u64 *param_1) { *param_1 = *param_1 & 0xffffffffffffefff; }

// 0x7103944ed0 -- set upper 40 bits from param_2 (48 bytes)
__attribute__((optnone))
void FUN_7103944ed0(u64 *param_1, s64 param_2)
{
    *param_1 = *param_1 & 0xffffffffff | param_2 << 0x28;
}

// 0x7103944f00 -- clear bits 16-17 (48 bytes)
__attribute__((optnone))
void FUN_7103944f00(u64 *param_1) { *param_1 = *param_1 & 0xfffffffffffcffff; }

// 0x7103944f30 -- set bit 15 (48 bytes)
__attribute__((optnone))
void FUN_7103944f30(u64 *param_1)
{
    *param_1 = *param_1 & 0xffffffffffff0000 | *param_1 & 0x7fff | 0x8000;
}

// 0x7103944f60 -- set bit 13 (48 bytes)
__attribute__((optnone))
void FUN_7103944f60(u64 *param_1)
{
    *param_1 = *param_1 & 0xffffffffffffc000 | *param_1 & 0x1fff | 0x2000;
}

// 0x7103944f90 -- set bit 14 (48 bytes)
__attribute__((optnone))
void FUN_7103944f90(u64 *param_1)
{
    *param_1 = *param_1 & 0xffffffffffff8000 | *param_1 & 0x3fff | 0x4000;
}

// 0x7103945ca0 -- write lower 16 bits into *(p+0x10) (48 bytes)
// +0x10 [inferred: u64 bitfield, lower 16 bits written with param_2]
void FUN_7103945ca0(s64 param_1, u16 param_2)
{
    *(u64*)(param_1 + 0x10) = *(u64*)(param_1 + 0x10) & 0xffffffffffff0000 | (u64)param_2;
}

// 0x71039576f0 -- copy u64: *p1 = *p2 (48 bytes)
__attribute__((optnone))
void FUN_71039576f0(u64 *param_1, u64 *param_2) { *param_1 = *param_2; }

// 0x710395a470 -- decrement field at +0x18, set byte at +0x1c to 1 (48 bytes)
// param_1 [inferred: ref-count struct with counter and dirty flag]
//   +0x18 [inferred: s32 counter, decremented]
//   +0x1c [inferred: u8 dirty/changed flag, set to 1 after decrement]
void FUN_710395a470(s64 param_1)
{
    *(s32*)(param_1 + 0x18) = *(s32*)(param_1 + 0x18) - 1;
    *(u8*)(param_1 + 0x1c) = 1;
}

// 0x710395aad0 -- increment field at +0x18, clear byte at +0x1c (48 bytes)
// param_1 [inferred: same ref-count struct as FUN_710395a470]
//   +0x18 [inferred: s32 counter, incremented]
//   +0x1c [inferred: u8 dirty/changed flag, cleared after increment]
void FUN_710395aad0(s64 param_1)
{
    *(s32*)(param_1 + 0x18) = *(s32*)(param_1 + 0x18) + 1;
    *(u8*)(param_1 + 0x1c) = 0;
}

// 0x710395d380 -- set two u32 fields to 0x9e (48 bytes)
__attribute__((optnone))
void FUN_710395d380(u32 *param_1)
{
    *param_1 = 0x9e;
    param_1[1] = 0x9e;
}

// 0x7103929420 -- no-op (48 bytes)
__attribute__((optnone))
void FUN_7103929420(void) { return; }

// 0x7103931320 -- return *(u64*)(p+8) & 0xffffffffffff0000 (48 bytes)
// +0x08 [inferred: u64 bitfield, upper 48 bits extracted]
u64 FUN_7103931320(s64 param_1) { return *(u64*)(param_1 + 8) & 0xffffffffffff0000; }

// 0x7103931e50 -- return *param_1 >> 0x1a & 0x3fff (48 bytes)
__attribute__((optnone))
u64 FUN_7103931e50(u64 *param_1) { return *param_1 >> 0x1a & 0x3fff; }

// 0x710393cfe0 -- return *(u64*)(p+8) & 0xffffffffffff0000 (48 bytes)
// +0x08 [inferred: u64 bitfield, upper 48 bits extracted, same pattern as FUN_7103931320]
u64 FUN_710393cfe0(s64 param_1) { return *(u64*)(param_1 + 8) & 0xffffffffffff0000; }

// 0x71039533b0 -- return *(u64*)(p+8) & 0xffffffffffff0000 (48 bytes)
// +0x08 [inferred: u64 bitfield, upper 48 bits extracted, same pattern as FUN_7103931320]
u64 FUN_71039533b0(s64 param_1) { return *(u64*)(param_1 + 8) & 0xffffffffffff0000; }

// 0x7103957d60 -- no-op (48 bytes)
__attribute__((optnone))
void FUN_7103957d60(void) { return; }

// 0x710392f020 -- call FUN_710392f0d0 and return bit 0 (48 bytes)
__attribute__((optnone))
u64 FUN_710392f020(void)
{
    return FUN_710392f0d0(DAT_7106dd3f1e, 0) & 1;
}

// 0x71039737f0 -- call fn_ptr at +0x70 of nested field with +0x90 as this (48 bytes)
// param_1 [inferred: wrapper struct]
//   +0x08 [inferred: pointer to intermediate struct]
//   *(+0x08)+0x18 [inferred: pointer to inner object with fn table and data]
//   inner+0x70 [inferred: function pointer in inner object]
//   inner+0x90 [inferred: data region passed as 'this' to function at +0x70]
u32 FUN_71039737f0(s64 param_1)
{
    s64 inner = *(s64 *)(*(s64 *)(param_1 + 8) + 0x18);
    reinterpret_cast<void (*)(s64)>(*(s64 *)(inner + 0x70))(inner + 0x90);
    return 0;
}

// 0x7103978f20 -- call function ptr at +0x28 with offset fields, return 0 (48 bytes)
// param_1 [inferred: struct with fn_ptr and data region]
//   +0x28 [inferred: function pointer]
//   +0x60 [inferred: data/this pointer passed as first arg]
// param_2 [inferred: config/state struct]
//   +0xd4 [inferred: u32 parameter passed as third arg]
u64 FUN_7103978f20(s64 param_1, s64 param_2, u64 param_3)
{
    // +0x28 [inferred: fn_ptr], +0x60 [inferred: this], +0xd4 [inferred: u32 config value]
    (*(void(*)(s64, u64, u32))(*(s64*)(param_1 + 0x28)))(param_1 + 0x60, param_3, *(u32*)(param_2 + 0xd4));
    return 0;
}

// 0x710397c090 -- store u32 at +0x84, vtable[0x40/8] with field at +0x7c, return 0 (48 bytes)
// param_2 [inferred: vtable-bearing object]
//   +0x7c [inferred: u32 value passed to vtable method]
//   +0x84 [inferred: u32 field written with param_1]
//   vtable+0x40 [inferred: virtual method slot 8, takes u32 arg]
u32 FUN_710397c090(u32 param_1, s64 *param_2)
{
    // +0x84 [inferred: u32 store]
    *(u32 *)((s64)param_2 + 0x84) = param_1;
    // vtable+0x40 [inferred: virtual method], +0x7c [inferred: u32 arg]
    reinterpret_cast<void (*)(u32)>(VT(param_2)[0x40 / 8])(*(u32 *)((s64)param_2 + 0x7c));
    return 0;
}

// 0x71039277d0 -- wrapper: FUN_7103927800(param_1) (48 bytes)
__attribute__((optnone))
void FUN_71039277d0(u64 param_1) { FUN_7103927800(param_1); }

// 0x7103927b00 -- deref byte from FUN_71039297e0(param_1) (48 bytes)
u8 FUN_7103927b00(u64 param_1) { return *FUN_71039297e0(param_1); }
