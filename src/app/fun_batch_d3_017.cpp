#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-017
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_7100127500(u64);

// ---- Functions ---------------------------------------------------------------

// 0x71001129a0 — setter: write param_2 to +8 (16 bytes)
void FUN_71001129a0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 8) = param_2;
}

// 0x71001129b0 — setter: write param_2 to +0xc (16 bytes)
void FUN_71001129b0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0xc) = param_2;
}

// 0x71001129c0 — setter: write param_2 to +0x268 (16 bytes)
void FUN_71001129c0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x268) = param_2;
}

// 0x71001129d0 — setter: write u16 param_2 to +0x10 (16 bytes)
void FUN_71001129d0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x10) = param_2;
}

// 0x71001129e0 — setter: write u16 param_2 to +0x12 (16 bytes)
void FUN_71001129e0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x12) = param_2;
}

// 0x71001129f0 — setter: write u16 param_2 to +0x14 (16 bytes)
void FUN_71001129f0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x14) = param_2;
}

// 0x7100112a00 — setter: write param_2&1 to byte at +0x16 (16 bytes)
void FUN_7100112a00(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x16) = param_2 & 1;
}

// 0x7100112bd0 — getter: return byte at +0x234 (16 bytes)
u8 FUN_7100112bd0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x234);
}

// 0x7100112be0 — SetUserPasswordEnabled: write param_2&1 to +0x234 (16 bytes)
void FUN_7100112be0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x234) = param_2 & 1;
}

// 0x7100112bf0 — SetSystemPasswordEnabled: write param_2&1 to +0x235 (16 bytes)
void FUN_7100112bf0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x235) = param_2 & 1;
}

// 0x7100112c00 — SetSessionType: set type and enabled flag (16 bytes)
void FUN_7100112c00(s64 param_1, u32 param_2, u8 param_3)
{
    *(u32 *)(param_1 + 0x238) = param_2;
    *(u8 *)(param_1 + 0x23c) = param_3 & 1;
}

// 0x7100112c10 — setter: write u64 param_2 to +0x240 (16 bytes)
void FUN_7100112c10(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x240) = param_2;
}

// 0x7100112c20 — setter: write u64 param_2 to +0x248 (16 bytes)
void FUN_7100112c20(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x248) = param_2;
}

// 0x7100112c30 — ChkLinkedAttribute: write byte param_2 to +0x250 (16 bytes)
void FUN_7100112c30(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x250) = param_2;
}

// 0x71001133a0 — set range: write 0xffff and param_2 to u16 pair, OR bit 2 (32 bytes)
void FUN_71001133a0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0xa38) = 0xffff;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 2;
}

// 0x71001133c0 — set range: write param_3 and param_2 to u16 pair, OR bit 2 (32 bytes)
void FUN_71001133c0(s64 param_1, u16 param_2, u16 param_3)
{
    *(u16 *)(param_1 + 0xa38) = param_3;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 2;
}

// 0x71001133e0 — setter: write param_2&1 to +0xa3c, OR bit 4 (32 bytes)
void FUN_71001133e0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa3c) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 4;
}

// 0x7100113400 — setter: write param_2&1 to +0xa3d, OR bit 8 (32 bytes)
void FUN_7100113400(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa3d) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 8;
}

// 0x7100113420 — setter: write u32 to +0x14, OR bit 0x10 (32 bytes)
void FUN_7100113420(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x14) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x10;
}

// 0x7100113440 — setter: write u32 to +0x18, OR bit 0x20 (32 bytes)
void FUN_7100113440(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x18) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x20;
}

// 0x7100113460 — setter: write u32 to +0x9cc, OR bit 0x4000 (32 bytes)
void FUN_7100113460(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9cc) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x4000;
}

// 0x7100113480 — setter: write param_2&1 to +0x9ca, OR bit 0x1000 (32 bytes)
void FUN_7100113480(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x9ca) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x1000;
}

// 0x71001134a0 — setter: write param_2&1 to +0x9cb, OR bit 0x2000 (32 bytes)
void FUN_71001134a0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x9cb) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x2000;
}

// 0x7100113640 — setter: write u32 to +0x9d0, OR bit 0x8000 (32 bytes)
void FUN_7100113640(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9d0) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x8000;
}

// 0x7100113660 — setter: write u32 to +0x9d4, OR bit 0x10000 (32 bytes)
void FUN_7100113660(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9d4) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x10000;
}

// 0x7100113680 — setter: write u32 to +0x9d8, OR bit 0x20000 (32 bytes)
void FUN_7100113680(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9d8) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x20000;
}

// 0x71001136a0 — setter: write u32 to +0x9dc, OR bit 0x40000 (32 bytes)
void FUN_71001136a0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9dc) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x40000;
}

// 0x71001136c0 — setter: write param_2&1 to +0xa08, OR bit 0x100000 (32 bytes)
void FUN_71001136c0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa08) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x100000;
}

// 0x7100114b80 — getter: return u64 at +0x18 (32 bytes)
u64 FUN_7100114b80(s64 param_1)
{
    return *(u64 *)(param_1 + 0x18);
}

// 0x7100114d90 — SetApplicationDataEnabled: write param_2&1 to +0x97f (16 bytes)
void FUN_7100114d90(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x97f) = param_2 & 1;
}

// 0x7100114da0 — offset: return param_1 + 0x18 (16 bytes)
s64 FUN_7100114da0(s64 param_1)
{
    return param_1 + 0x18;
}

// 0x7100114db0 — getter: return u32 at +0x978 (16 bytes)
u32 FUN_7100114db0(s64 param_1)
{
    return *(u32 *)(param_1 + 0x978);
}

// 0x7100114dc0 — getter: return byte at +0x97d (16 bytes)
u8 FUN_7100114dc0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x97d);
}

// 0x7100114dd0 — getter: return byte at +0x97e (16 bytes)
u8 FUN_7100114dd0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x97e);
}

// 0x7100117050 — getter: return *param_1 (u64) (16 bytes)
u64 FUN_7100117050(u64 *param_1)
{
    return *param_1;
}

// 0x71001170c0 — delegate: call FUN_7100127500 with *param_1 (16 bytes)
void FUN_71001170c0(u64 *param_1)
{
    FUN_7100127500(*param_1);
}
