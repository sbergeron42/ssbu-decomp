#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-020
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------

// 0x7100154ed0 — Reset: zero u64+u32, set u64 sentinel 0xffffffffffffffff (48 bytes)
void FUN_7100154ed0(s64 param_1)
{
    *(u64 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x1c) = 0;
    *(u64 *)(param_1 + 0x20) = 0xffffffffffffffff;
}

// 0x7100154ef0 — Reset: zero u64+u32, set u64 sentinel 0xffffffffffffffff (48 bytes)
void FUN_7100154ef0(s64 param_1)
{
    *(u64 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x1c) = 0;
    *(u64 *)(param_1 + 0x20) = 0xffffffffffffffff;
}

// 0x7100154f90 — copy: write u32 at +0x14 into +0x18 (16 bytes)
void FUN_7100154f90(s64 param_1)
{
    *(u32 *)(param_1 + 0x18) = *(u32 *)(param_1 + 0x14);
}

// 0x7100155050 — empty stub (16 bytes)
void FUN_7100155050(void)
{
}

// 0x7100156210 — empty stub (16 bytes)
void FUN_7100156210(void)
{
}

// 0x71001563d0 — empty stub (16 bytes)
void FUN_71001563d0(void)
{
}

// 0x7100157cf0 — getter: return u64 at +0x38 (16 bytes)
u64 FUN_7100157cf0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x38);
}

// 0x7100158050 — empty stub (16 bytes)
void FUN_7100158050(void)
{
}

// 0x7100158060 — setter: write u64 param_2 to +0x610 (16 bytes)
void FUN_7100158060(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x610) = param_2;
}

// 0x7100158070 — init: set u32/u8 fields, clear two fields (32 bytes)
void FUN_7100158070(s64 param_1, u32 *param_2, u32 param_3, u8 param_4, u8 param_5)
{
    u32 uVar1;

    *(u32 *)(param_1 + 0x608) = param_3;
    uVar1 = *param_2;
    *(u8 *)(param_1 + 0x61c) = param_4 & 1;
    *(u8 *)(param_1 + 0xa04) = 0;
    *(u32 *)(param_1 + 0xa00) = 0;
    *(u32 *)(param_1 + 0x618) = uVar1;
    *(u8 *)(param_1 + 0x61d) = param_5 & 1;
}

// 0x710015e160 — empty stub (16 bytes)
void FUN_710015e160(void)
{
}

// 0x710015e1f0 — empty stub (16 bytes)
void FUN_710015e1f0(void)
{
}

// 0x710015e200 — GetNextSendSequenceId: increment u16, skip 0 (32 bytes)
s32 FUN_710015e200(s64 param_1)
{
    s32 iVar1;
    u16 uVar2;

    uVar2 = *(u16 *)(param_1 + 8);
    iVar1 = uVar2 + 2;
    if ((uVar2 + 1 & 0xffff) != 0) {
        iVar1 = uVar2 + 1;
    }
    *(s16 *)(param_1 + 8) = (s16)iVar1;
    return iVar1;
}

// 0x710015e530 — clear: zero u8 at +8 and u64 at +0x50 (16 bytes)
void FUN_710015e530(s64 param_1)
{
    *(u8 *)(param_1 + 8) = 0;
    *(u64 *)(param_1 + 0x50) = 0;
}

// 0x710015e540 — setter: write u8 param_2 to +0x38 (16 bytes)
void FUN_710015e540(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x38) = param_2;
}

// 0x710015e550 — setter: write u64 param_2 to +0x40 (16 bytes)
void FUN_710015e550(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x40) = param_2;
}

// 0x7100160210 — offset: return param_1 + 8 (16 bytes)
s64 FUN_7100160210(s64 param_1)
{
    return param_1 + 8;
}

// 0x7100160300 — bool: (byte at +0x78 & 0xc) == 8 (16 bytes)
bool FUN_7100160300(s64 param_1)
{
    return (*(u8 *)(param_1 + 0x78) & 0xc) == 8;
}

// 0x71001603c0 — bool: u64 at +0x68 equals u64 at param_2+0x68 (16 bytes)
bool FUN_71001603c0(s64 param_1, s64 param_2)
{
    return *(s64 *)(param_1 + 0x68) == *(s64 *)(param_2 + 0x68);
}

// 0x71001603e0 — bool: u32 at +0x74 equals u32 at param_2+0x74 (16 bytes)
bool FUN_71001603e0(s64 param_1, s64 param_2)
{
    return *(s32 *)(param_1 + 0x74) == *(s32 *)(param_2 + 0x74);
}

// 0x7100160400 — bool: u32 at +0x70 equals u32 at param_2+0x70 (16 bytes)
bool FUN_7100160400(s64 param_1, s64 param_2)
{
    return *(s32 *)(param_1 + 0x70) == *(s32 *)(param_2 + 0x70);
}

// 0x7100160420 — bool: byte at +0x7a == 1 (16 bytes)
bool FUN_7100160420(s64 param_1)
{
    return *(s8 *)(param_1 + 0x7a) == '\x01';
}

// 0x7100160480 — setter: write u32 param_2 to +0x70 (16 bytes)
void FUN_7100160480(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x70) = param_2;
}

// 0x71001604a0 — bit-field setter: update bits 2-3 of byte at +0x78 (16 bytes)
void FUN_71001604a0(s64 param_1, u32 param_2)
{
    *(u8 *)(param_1 + 0x78) = *(u8 *)(param_1 + 0x78) & 0xf3 | (u8)((param_2 & 3) << 2);
}

// 0x71001604e0 — setter: write u8 param_2 to +0x79 (16 bytes)
void FUN_71001604e0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x79) = param_2;
}
