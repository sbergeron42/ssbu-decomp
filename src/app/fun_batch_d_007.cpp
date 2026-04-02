#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71039 address range, batch d-007
// Pool-d worker: auto-generated from Ghidra decompilation
// All functions are 32 bytes (one-liner bodies)

// ---- Functions ---------------------------------------------------------------

// 0x7103927ac0 — return param_1 == 0 (32 bytes)
u8 FUN_7103927ac0(s64 param_1) { return (u8)(param_1 == 0); }

// 0x7103927b90 — no-op (32 bytes)
void FUN_7103927b90(void) { return; }

// 0x7103928290 — copy field: *p = p[1] (32 bytes)
void FUN_7103928290(u32 *param_1) { *param_1 = param_1[1]; }

// 0x7103929100 — return param_1 + 0x1b0 (32 bytes)
s64 FUN_7103929100(s64 param_1) { return param_1 + 0x1b0; }

// 0x7103929140 — deref u32 (32 bytes)
u64 FUN_7103929140(u32 *param_1) { return *param_1; }

// 0x7103929190 — return param_1 + 0x1c0 (32 bytes)
s64 FUN_7103929190(s64 param_1) { return param_1 + 0x1c0; }

// 0x7103929210 — return param_1 + 1 (32 bytes)
s64 FUN_7103929210(s64 param_1) { return param_1 + 1; }

// 0x7103929740 — return param_1 + 0x1a8 (32 bytes)
s64 FUN_7103929740(s64 param_1) { return param_1 + 0x1a8; }

// 0x71039297c0 — return param_1 + 0x1800 (32 bytes)
s64 FUN_71039297c0(s64 param_1) { return param_1 + 0x1800; }

// 0x7103929810 — return param_1 + 3 (32 bytes)
s64 FUN_7103929810(s64 param_1) { return param_1 + 3; }

// 0x710392c110 — return param_1 & 1 (32 bytes)
u64 FUN_710392c110(u32 param_1) { return param_1 & 1; }

// 0x710392c160 — return param_1 + 0x28 (32 bytes)
s64 FUN_710392c160(s64 param_1) { return param_1 + 0x28; }

// 0x710392c590 — return *param_1 < 2 (32 bytes)
u8 FUN_710392c590(u8 *param_1) { return (u8)(*param_1 < 2); }

// 0x710392c610 — return param_1 + 2 (32 bytes)
s64 FUN_710392c610(s64 param_1) { return param_1 + 2; }

// 0x710392c660 — return param_1 + 4 (32 bytes)
s64 FUN_710392c660(s64 param_1) { return param_1 + 4; }

// 0x710392c6b0 — return param_1 + 0x1b8 (32 bytes)
s64 FUN_710392c6b0(s64 param_1) { return param_1 + 0x1b8; }

// 0x710392ef20 — no-op (32 bytes)
void FUN_710392ef20(void) { return; }

// 0x710392f170 — deref u32 (32 bytes)
u64 FUN_710392f170(u32 *param_1) { return *param_1; }

// 0x7103930140 — deref u64 (32 bytes)
u64 FUN_7103930140(u64 *param_1) { return *param_1; }

// 0x7103930160 — return *(u64*)(p+0x10) masked (32 bytes)
u64 FUN_7103930160(s64 param_1) { return *(u64*)(param_1 + 0x10) & 0xffffffffffff0000; }

// 0x71039302c0 — return param_1 == 0 (32 bytes)
u8 FUN_71039302c0(s64 param_1) { return (u8)(param_1 == 0); }

// 0x7103930330 — return param_1 + 0x1800 (32 bytes)
s64 FUN_7103930330(s64 param_1) { return param_1 + 0x1800; }

// 0x71039316b0 — return param_1 & 1 (32 bytes)
u64 FUN_71039316b0(u32 param_1) { return param_1 & 1; }

// 0x7103931ba0 — return param_1 + 0x28 (32 bytes)
s64 FUN_7103931ba0(s64 param_1) { return param_1 + 0x28; }

// 0x71039322b0 — copy field: *p = p[1] (32 bytes)
void FUN_71039322b0(u32 *param_1) { *param_1 = param_1[1]; }

// 0x7103932450 — return param_1 + 4 (32 bytes)
s64 FUN_7103932450(s64 param_1) { return param_1 + 4; }

// 0x71039324a0 — return param_1 + 0x1b8 (32 bytes)
s64 FUN_71039324a0(s64 param_1) { return param_1 + 0x1b8; }

// 0x7103932890 — return *param_1 >> 0x28 (32 bytes)
u64 FUN_7103932890(u64 *param_1) { return *param_1 >> 0x28; }

// 0x7103933660 — return param_1 + 0x1c0 (32 bytes)
s64 FUN_7103933660(s64 param_1) { return param_1 + 0x1c0; }

// 0x71039336e0 — return param_1 + 1 (32 bytes)
s64 FUN_71039336e0(s64 param_1) { return param_1 + 1; }

// 0x7103933730 — return param_1 + 0x1b0 (32 bytes)
s64 FUN_7103933730(s64 param_1) { return param_1 + 0x1b0; }

// 0x7103933780 — return param_1 + 0x1a8 (32 bytes)
s64 FUN_7103933780(s64 param_1) { return param_1 + 0x1a8; }

// 0x71039337d0 — return param_1 + 3 (32 bytes)
s64 FUN_71039337d0(s64 param_1) { return param_1 + 3; }

// 0x7103936250 — zero out u64 field (32 bytes)
void FUN_7103936250(u64 *param_1) { *param_1 = 0; }

// 0x7103936cb0 — return *(u16*)(p+0x10) (32 bytes)
u16 FUN_7103936cb0(s64 param_1) { return *(u16*)(param_1 + 0x10); }

// 0x71039388f0 — return param_1 == 0 (32 bytes)
u8 FUN_71039388f0(s64 param_1) { return (u8)(param_1 == 0); }

// 0x7103938960 — return param_1 + 0x1800 (32 bytes)
s64 FUN_7103938960(s64 param_1) { return param_1 + 0x1800; }

// 0x7103938af0 — zero out u64 field (32 bytes)
void FUN_7103938af0(u64 *param_1) { *param_1 = 0; }

// 0x7103938b10 — return *param_1 == 0 (32 bytes)
u8 FUN_7103938b10(s64 *param_1) { return (u8)(*param_1 == 0); }

// 0x71039395a0 — return *param_1 >> 0x28 (32 bytes)
u64 FUN_71039395a0(u64 *param_1) { return *param_1 >> 0x28; }

// 0x710393c1e0 — return *(u32*)(p+0x690) (32 bytes)
u64 FUN_710393c1e0(s64 param_1) { return *(u32*)(param_1 + 0x690); }

// 0x710393c360 — no-op (32 bytes)
void FUN_710393c360(void) { return; }

// 0x710393ca60 — return *param_1 >> 0xd & 1 (32 bytes)
u64 FUN_710393ca60(u64 *param_1) { return *param_1 >> 0xd & 1; }

// 0x710393ca80 — return *(u64*)(p+0x10) masked (32 bytes)
u64 FUN_710393ca80(s64 param_1) { return *(u64*)(param_1 + 0x10) & 0xffffffffffff0000; }

// 0x710393cdf0 — return *param_1 >> 0xf & 1 (32 bytes)
u64 FUN_710393cdf0(u64 *param_1) { return *param_1 >> 0xf & 1; }

// 0x710393dd30 — return param_1 + 8 (32 bytes)
s64 FUN_710393dd30(s64 param_1) { return param_1 + 8; }

// 0x710393de40 — return *param_1 >> 0xc & 1 (32 bytes)
u64 FUN_710393de40(u64 *param_1) { return *param_1 >> 0xc & 1; }

// 0x710393fb30 — return param_1 + 3 (32 bytes)
s64 FUN_710393fb30(s64 param_1) { return param_1 + 3; }

// 0x710393fe00 — deref u32 (32 bytes)
u64 FUN_710393fe00(u32 *param_1) { return *param_1; }

// 0x7103940800 — return *param_1 >> 0x10 & 3 (32 bytes)
u64 FUN_7103940800(u64 *param_1) { return *param_1 >> 0x10 & 3; }

// 0x7103941a10 — return param_1 & 1 (32 bytes)
u64 FUN_7103941a10(u32 param_1) { return param_1 & 1; }

// 0x7103941a50 — return *param_1 >> 0xe & 1 (32 bytes)
u64 FUN_7103941a50(u64 *param_1) { return *param_1 >> 0xe & 1; }
