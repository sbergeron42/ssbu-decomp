#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71039 address range, batch d-007
// All functions are 32 bytes (one-liner bodies)

// ---- Functions ---------------------------------------------------------------

// 0x7103927ac0 -- null check (32 bytes)
u8 FUN_7103927ac0(s64 value) { return (u8)(value == 0); }

// 0x7103927b90 -- no-op (32 bytes)
void FUN_7103927b90(void) { return; }

// 0x7103928290 -- copy next field to current: *fields = fields[1] (32 bytes)
void FUN_7103928290(u32 *fields) { *fields = fields[1]; }

// 0x7103929100 -- get field at +0x1b0 (32 bytes)
s64 FUN_7103929100(s64 self) { return self + 0x1b0; }

// 0x7103929140 -- read u32 (32 bytes)
u64 FUN_7103929140(u32 *ptr) { return *ptr; }

// 0x7103929190 -- get field at +0x1c0 (32 bytes)
s64 FUN_7103929190(s64 self) { return self + 0x1c0; }

// 0x7103929210 -- increment by 1 (32 bytes)
s64 FUN_7103929210(s64 self) { return self + 1; }

// 0x7103929740 -- get field at +0x1a8 (32 bytes)
s64 FUN_7103929740(s64 self) { return self + 0x1a8; }

// 0x71039297c0 -- get field at +0x1800 (32 bytes)
s64 FUN_71039297c0(s64 self) { return self + 0x1800; }

// 0x7103929810 -- increment by 3 (32 bytes)
s64 FUN_7103929810(s64 self) { return self + 3; }

// 0x710392c110 -- extract bit 0 (32 bytes)
u64 FUN_710392c110(u32 flags) { return flags & 1; }

// 0x710392c160 -- get field at +0x28 (32 bytes)
s64 FUN_710392c160(s64 self) { return self + 0x28; }

// 0x710392c590 -- check value < 2 (32 bytes)
u8 FUN_710392c590(u8 *ptr) { return (u8)(*ptr < 2); }

// 0x710392c610 -- increment by 2 (32 bytes)
s64 FUN_710392c610(s64 self) { return self + 2; }

// 0x710392c660 -- increment by 4 (32 bytes)
s64 FUN_710392c660(s64 self) { return self + 4; }

// 0x710392c6b0 -- get field at +0x1b8 (32 bytes)
s64 FUN_710392c6b0(s64 self) { return self + 0x1b8; }

// 0x710392ef20 -- no-op (32 bytes)
void FUN_710392ef20(void) { return; }

// 0x710392f170 -- read u32 (32 bytes)
u64 FUN_710392f170(u32 *ptr) { return *ptr; }

// 0x7103930140 -- read u64 (32 bytes)
u64 FUN_7103930140(u64 *ptr) { return *ptr; }

// 0x7103930160 -- read +0x10 masked to upper 48 bits (32 bytes)
u64 FUN_7103930160(s64 self) { return *(u64*)(self + 0x10) & 0xffffffffffff0000; }

// 0x71039302c0 -- null check (32 bytes)
u8 FUN_71039302c0(s64 value) { return (u8)(value == 0); }

// 0x7103930330 -- get field at +0x1800 (32 bytes)
s64 FUN_7103930330(s64 self) { return self + 0x1800; }

// 0x71039316b0 -- extract bit 0 (32 bytes)
u64 FUN_71039316b0(u32 flags) { return flags & 1; }

// 0x7103931ba0 -- get field at +0x28 (32 bytes)
s64 FUN_7103931ba0(s64 self) { return self + 0x28; }

// 0x71039322b0 -- copy next field to current: *fields = fields[1] (32 bytes)
void FUN_71039322b0(u32 *fields) { *fields = fields[1]; }

// 0x7103932450 -- increment by 4 (32 bytes)
s64 FUN_7103932450(s64 self) { return self + 4; }

// 0x71039324a0 -- get field at +0x1b8 (32 bytes)
s64 FUN_71039324a0(s64 self) { return self + 0x1b8; }

// 0x7103932890 -- extract bits [63:40] (32 bytes)
u64 FUN_7103932890(u64 *ptr) { return *ptr >> 0x28; }

// 0x7103933660 -- get field at +0x1c0 (32 bytes)
s64 FUN_7103933660(s64 self) { return self + 0x1c0; }

// 0x71039336e0 -- increment by 1 (32 bytes)
s64 FUN_71039336e0(s64 self) { return self + 1; }

// 0x7103933730 -- get field at +0x1b0 (32 bytes)
s64 FUN_7103933730(s64 self) { return self + 0x1b0; }

// 0x7103933780 -- get field at +0x1a8 (32 bytes)
s64 FUN_7103933780(s64 self) { return self + 0x1a8; }

// 0x71039337d0 -- increment by 3 (32 bytes)
s64 FUN_71039337d0(s64 self) { return self + 3; }

// 0x7103936250 -- clear u64 field (32 bytes)
void FUN_7103936250(u64 *ptr) { *ptr = 0; }

// 0x7103936cb0 -- read u16 at +0x10 (32 bytes)
u16 FUN_7103936cb0(s64 self) { return *(u16*)(self + 0x10); }

// 0x71039388f0 -- null check (32 bytes)
u8 FUN_71039388f0(s64 value) { return (u8)(value == 0); }

// 0x7103938960 -- get field at +0x1800 (32 bytes)
s64 FUN_7103938960(s64 self) { return self + 0x1800; }

// 0x7103938af0 -- clear u64 field (32 bytes)
void FUN_7103938af0(u64 *ptr) { *ptr = 0; }

// 0x7103938b10 -- check *self == 0 (32 bytes)
u8 FUN_7103938b10(s64 *ptr) { return (u8)(*ptr == 0); }

// 0x71039395a0 -- extract bits [63:40] (32 bytes)
u64 FUN_71039395a0(u64 *ptr) { return *ptr >> 0x28; }

// 0x710393c1e0 -- read u32 at +0x690 (32 bytes)
u64 FUN_710393c1e0(s64 self) { return *(u32*)(self + 0x690); }

// 0x710393c360 -- no-op (32 bytes)
void FUN_710393c360(void) { return; }

// 0x710393ca60 -- extract bit 13 (32 bytes)
u64 FUN_710393ca60(u64 *flags) { return *flags >> 0xd & 1; }

// 0x710393ca80 -- read +0x10 masked to upper 48 bits (32 bytes)
u64 FUN_710393ca80(s64 self) { return *(u64*)(self + 0x10) & 0xffffffffffff0000; }

// 0x710393cdf0 -- extract bit 15 (32 bytes)
u64 FUN_710393cdf0(u64 *flags) { return *flags >> 0xf & 1; }

// 0x710393dd30 -- get field at +8 (32 bytes)
s64 FUN_710393dd30(s64 self) { return self + 8; }

// 0x710393de40 -- extract bit 12 (32 bytes)
u64 FUN_710393de40(u64 *flags) { return *flags >> 0xc & 1; }

// 0x710393fb30 -- increment by 3 (32 bytes)
s64 FUN_710393fb30(s64 self) { return self + 3; }

// 0x710393fe00 -- read u32 (32 bytes)
u64 FUN_710393fe00(u32 *ptr) { return *ptr; }

// 0x7103940800 -- extract bits [17:16] (32 bytes)
u64 FUN_7103940800(u64 *flags) { return *flags >> 0x10 & 3; }

// 0x7103941a10 -- extract bit 0 (32 bytes)
u64 FUN_7103941a10(u32 flags) { return flags & 1; }

// 0x7103941a50 -- extract bit 14 (32 bytes)
u64 FUN_7103941a50(u64 *flags) { return *flags >> 0xe & 1; }
