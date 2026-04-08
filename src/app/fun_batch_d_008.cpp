#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71039 address range, batch d-008
// Pool-d worker: auto-generated from Ghidra decompilation
// All functions are 32 bytes (one-liner bodies)

// ---- Functions ---------------------------------------------------------------

// 0x7103941be0 -- store u64 at p+8 (32 bytes)
__attribute__((optnone))
void FUN_7103941be0(s64 param_1, u64 param_2) { *(u64*)(param_1 + 8) = param_2; }

// 0x7103942360 -- return param_1 + 0x28 (32 bytes)
__attribute__((optnone))
s64 FUN_7103942360(s64 param_1) { return param_1 + 0x28; }

// 0x7103942580 -- deref u64 (32 bytes)
__attribute__((optnone))
u64 FUN_7103942580(u64 *param_1) { return *param_1; }

// 0x7103944410 -- return *(u64*)(p+0x10) (32 bytes)
__attribute__((optnone))
u64 FUN_7103944410(s64 param_1) { return *(u64*)(param_1 + 0x10); }

// 0x71039447f0 -- return param_1 == 0 (32 bytes)
u8 FUN_71039447f0(s64 param_1) { return (u8)(param_1 == 0); }

// 0x71039449d0 -- return param_1 + 3 (32 bytes)
__attribute__((optnone))
s64 FUN_71039449d0(s64 param_1) { return param_1 + 3; }

// 0x7103944d10 -- return *param_1 >> 0x28 (32 bytes)
__attribute__((optnone))
u64 FUN_7103944d10(u64 *param_1) { return *param_1 >> 0x28; }

// 0x7103944e20 -- store u64 at p+8 (32 bytes)
__attribute__((optnone))
void FUN_7103944e20(s64 param_1, u64 param_2) { *(u64*)(param_1 + 8) = param_2; }

// 0x7103944e40 -- store u64 at p+0x10 (32 bytes)
__attribute__((optnone))
void FUN_7103944e40(s64 param_1, u64 param_2) { *(u64*)(param_1 + 0x10) = param_2; }

// 0x7103944ff0 -- deref u32 (32 bytes)
__attribute__((optnone))
u64 FUN_7103944ff0(u32 *param_1) { return *param_1; }

// 0x71039455c0 -- return param_1 + 0x1800 (32 bytes)
__attribute__((optnone))
s64 FUN_71039455c0(s64 param_1) { return param_1 + 0x1800; }

// 0x7103945fb0 -- indexed load: *(u64*)(p + p[2]*8 + 0x10) (32 bytes)
__attribute__((optnone))
u64 FUN_7103945fb0(s64 param_1) { return *(u64*)(param_1 + (u64)*(u32*)(param_1 + 8) * 8 + 0x10); }

// 0x7103945fe0 -- return param_1 != 0 (32 bytes)
u8 FUN_7103945fe0(s32 param_1) { return (u8)(param_1 != 0); }

// 0x7103947040 -- return param_1 == 0 (32 bytes)
u8 FUN_7103947040(s64 param_1) { return (u8)(param_1 == 0); }

// 0x710394ad60 -- deref u32 (32 bytes)
__attribute__((optnone))
u64 FUN_710394ad60(u32 *param_1) { return *param_1; }

// 0x71039506a0 -- return param_1 + 3 (32 bytes)
__attribute__((optnone))
s64 FUN_71039506a0(s64 param_1) { return param_1 + 3; }

// 0x7103950de0 -- return param_1 == 0 (32 bytes)
u8 FUN_7103950de0(s64 param_1) { return (u8)(param_1 == 0); }

// 0x7103951240 -- copy field: *p = p[1] (32 bytes)
__attribute__((optnone))
void FUN_7103951240(u32 *param_1) { *param_1 = param_1[1]; }

// 0x71039513e0 -- return param_1 + 4 (32 bytes)
__attribute__((optnone))
s64 FUN_71039513e0(s64 param_1) { return param_1 + 4; }

// 0x7103951430 -- return param_1 + 0x1b8 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951430(s64 param_1) { return param_1 + 0x1b8; }

// 0x7103951450 -- deref u32 (32 bytes)
__attribute__((optnone))
u64 FUN_7103951450(u32 *param_1) { return *param_1; }

// 0x7103951520 -- return param_1 + 0x1800 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951520(s64 param_1) { return param_1 + 0x1800; }

// 0x7103951c00 -- return param_1 + 0x1c0 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951c00(s64 param_1) { return param_1 + 0x1c0; }

// 0x7103951c80 -- return param_1 + 1 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951c80(s64 param_1) { return param_1 + 1; }

// 0x7103951cd0 -- return param_1 + 0x1b0 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951cd0(s64 param_1) { return param_1 + 0x1b0; }

// 0x7103951d20 -- return param_1 + 0x1a8 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951d20(s64 param_1) { return param_1 + 0x1a8; }

// 0x7103951de0 -- return param_1 + 3 (32 bytes)
__attribute__((optnone))
s64 FUN_7103951de0(s64 param_1) { return param_1 + 3; }

// 0x7103952870 -- return *(u64*)(p+0x10) masked (32 bytes)
__attribute__((optnone))
u64 FUN_7103952870(s64 param_1) { return *(u64*)(param_1 + 0x10) & 0xffffffffffff0000; }

// 0x7103952e50 -- return param_1 & 1 (32 bytes)
__attribute__((optnone))
u64 FUN_7103952e50(u32 param_1) { return param_1 & 1; }

// 0x7103953390 -- return param_1 + 0x28 (32 bytes)
__attribute__((optnone))
s64 FUN_7103953390(s64 param_1) { return param_1 + 0x28; }

// 0x71039536b0 -- no-op (32 bytes)
__attribute__((optnone))
void FUN_71039536b0(void) { return; }

// 0x7103957210 -- no-op (32 bytes)
__attribute__((optnone))
void FUN_7103957210(void) { return; }

// 0x7103957670 -- store u64 (32 bytes)
__attribute__((optnone))
void FUN_7103957670(u64 *param_1, u64 param_2) { *param_1 = param_2; }

// 0x71039576d0 -- deref u64 (32 bytes)
__attribute__((optnone))
u64 FUN_71039576d0(u64 *param_1) { return *param_1; }

// 0x7103958350 -- return param_1 != 0 (32 bytes)
u8 FUN_7103958350(s64 param_1) { return (u8)(param_1 != 0); }

// 0x71039586d0 -- return param_1 == 0 (32 bytes)
u8 FUN_71039586d0(s64 param_1) { return (u8)(param_1 == 0); }

// 0x7103958740 -- return param_1 + 0x1800 (32 bytes)
__attribute__((optnone))
s64 FUN_7103958740(s64 param_1) { return param_1 + 0x1800; }

// 0x710395b830 -- return param_1 == 0 (32 bytes)
u8 FUN_710395b830(s64 param_1) { return (u8)(param_1 == 0); }

// 0x710395b970 -- copy field: *p = p[1] (32 bytes)
__attribute__((optnone))
void FUN_710395b970(u32 *param_1) { *param_1 = param_1[1]; }

// 0x710395bb10 -- return param_1 + 4 (32 bytes)
__attribute__((optnone))
s64 FUN_710395bb10(s64 param_1) { return param_1 + 4; }

// 0x710395bb60 -- return param_1 + 0x1b8 (32 bytes)
__attribute__((optnone))
s64 FUN_710395bb60(s64 param_1) { return param_1 + 0x1b8; }

// 0x710395bb80 -- deref u32 (32 bytes)
__attribute__((optnone))
u64 FUN_710395bb80(u32 *param_1) { return *param_1; }

// 0x710395bc50 -- return param_1 + 0x1800 (32 bytes)
__attribute__((optnone))
s64 FUN_710395bc50(s64 param_1) { return param_1 + 0x1800; }

// 0x710395c470 -- return param_1 + 0x28 (32 bytes)
__attribute__((optnone))
s64 FUN_710395c470(s64 param_1) { return param_1 + 0x28; }

// 0x710395c840 -- return param_1 + 0x1c0 (32 bytes)
__attribute__((optnone))
s64 FUN_710395c840(s64 param_1) { return param_1 + 0x1c0; }

// 0x710395d270 -- return param_1 + 1 (32 bytes)
__attribute__((optnone))
s64 FUN_710395d270(s64 param_1) { return param_1 + 1; }

// 0x710395d2c0 -- return param_1 + 0x1b0 (32 bytes)
__attribute__((optnone))
s64 FUN_710395d2c0(s64 param_1) { return param_1 + 0x1b0; }

// 0x710395d310 -- return param_1 + 0x1a8 (32 bytes)
__attribute__((optnone))
s64 FUN_710395d310(s64 param_1) { return param_1 + 0x1a8; }
