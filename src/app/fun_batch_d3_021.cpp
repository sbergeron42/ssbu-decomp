#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-021
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_710015ffc0(s64);
extern void FUN_7100181270(s64);
extern void FUN_710017f100(s64);

// Intra-batch forward declaration (defined later in this file)
u8 FUN_710017f1d0(s64 param_1);

// ---- Functions ---------------------------------------------------------------

// 0x71001604f0 — setter: write param_2&1 to byte at +0x7a (16 bytes)
void FUN_71001604f0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x7a) = param_2 & 1;
}

// 0x7100160500 — setter: write param_2&1 to byte at +0x7b (16 bytes)
void FUN_7100160500(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x7b) = param_2 & 1;
}

// 0x7100160990 — empty stub (16 bytes)
void FUN_7100160990(void)
{
}

// 0x7100160b20 — delegate: call FUN_710015ffc0(param_1 + 0x88) (16 bytes)
void FUN_7100160b20(s64 param_1)
{
    FUN_710015ffc0(param_1 + 0x88);
}

// 0x7100161fa0 — getter: return u64 at +0x90 (GetStation) (16 bytes)
u64 FUN_7100161fa0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x90);
}

// 0x7100161fb0 — getter: return u64 at +0x98 (16 bytes)
u64 FUN_7100161fb0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x98);
}

// 0x71001623f0 — cond getter: if ptr at +0xa8 != 0, return u64 at *(ptr)+8 (32 bytes)
u64 FUN_71001623f0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa8) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0xa8) + 8);
    }
    return 0;
}

// 0x7100162410 — cond getter: if ptr at +0xa8 != 0, return u64 at *(ptr)+0x10 (32 bytes)
u64 FUN_7100162410(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa8) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0xa8) + 0x10);
    }
    return 0;
}

// 0x7100162490 — getter: return u64 at +0xa0 (16 bytes)
u64 FUN_7100162490(s64 param_1)
{
    return *(u64 *)(param_1 + 0xa0);
}

// 0x7100163170 — setter: write u64 param_2 to +0x50 (16 bytes)
void FUN_7100163170(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x50) = param_2;
}

// 0x7100163180 — setter: write u64 param_2 to +0x48 (16 bytes)
void FUN_7100163180(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x48) = param_2;
}

// 0x71001645a0 — conditional clear: if byte at +0x18 != 0, zero it (16 bytes)
void FUN_71001645a0(s64 param_1)
{
    if (*(s8 *)(param_1 + 0x18) != '\0') {
        *(u8 *)(param_1 + 0x18) = 0;
    }
}

// 0x7100165690 — cond getter: if ptr at +8 != 0, return *(s32)(*(ptr)+0x10)-0x18 (32 bytes)
s32 FUN_7100165690(s64 param_1)
{
    if (*(s64 *)(param_1 + 8) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 8) + 0x10) + -0x18;
    }
    return 0;
}

// 0x71001672d0 — empty stub (16 bytes)
void FUN_71001672d0(void)
{
}

// 0x7100175240 — conditional delegate: if ptr at +0x18 != 0, tail-call FUN_7100181270 (16 bytes)
void FUN_7100175240(s64 param_1)
{
    s64 ptr = *(s64 *)(param_1 + 0x18);
    if (ptr != 0) {
        FUN_7100181270(ptr);
    }
}

// 0x7100175780 — delegate: tail-call FUN_710017f100 with ptr at +0x18 (16 bytes)
void FUN_7100175780(s64 param_1)
{
    FUN_710017f100(*(s64 *)(param_1 + 0x18));
}

// 0x7100175790 — delegate: call FUN_710017f1d0 with u64 at *(+0x18) (16 bytes)
void FUN_7100175790(s64 param_1)
{
    FUN_710017f1d0(*(u64 *)(param_1 + 0x18));
}

// 0x7100177110 — setter: write u64 param_2 to +8 (16 bytes)
void FUN_7100177110(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 8) = param_2;
}

// 0x710017dde0 — setter: write u32 param_2 to +0x46c (16 bytes)
void FUN_710017dde0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x46c) = param_2;
}

// 0x710017f0f0 — setter: write two u64 params to +0x520 and +0x528 (16 bytes)
void FUN_710017f0f0(s64 param_1, u64 param_2, u64 param_3)
{
    *(u64 *)(param_1 + 0x520) = param_2;
    *(u64 *)(param_1 + 0x528) = param_3;
}

// 0x710017f1c0 — setter: write param_2&1 to byte at +0x1735 (16 bytes)
void FUN_710017f1c0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x1735) = param_2 & 1;
}

// 0x710017f1d0 — getter: return byte at +0x1735 (16 bytes)
u8 FUN_710017f1d0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x1735);
}

// 0x71001804d0 — bool: *(s32)(+0x4e8) == 1 (16 bytes)
bool FUN_71001804d0(s64 param_1)
{
    return *(s32 *)(param_1 + 0x4e8) == 1;
}

// 0x7100192f60 — getter: return u64 at +0xa0 (16 bytes)
u64 FUN_7100192f60(s64 param_1)
{
    return *(u64 *)(param_1 + 0xa0);
}

// 0x7100193110 — getter: return byte at +0xab (16 bytes)
u8 FUN_7100193110(s64 param_1)
{
    return *(u8 *)(param_1 + 0xab);
}

// 0x7100193200 — setter: write u64 param_2 to +0x60 (16 bytes)
void FUN_7100193200(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x60) = param_2;
}

// 0x7100193210 — clear: zero u64 at +0x60 (16 bytes)
void FUN_7100193210(s64 param_1)
{
    *(u64 *)(param_1 + 0x60) = 0;
}

// 0x71001932a0 — clear: zero u64 at +0x68 (16 bytes)
void FUN_71001932a0(s64 param_1)
{
    *(u64 *)(param_1 + 0x68) = 0;
}

// 0x71001932b0 — setter: write u64 param_2 to +0x70 (16 bytes)
void FUN_71001932b0(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x70) = param_2;
}

// 0x7100193300 — getter: return u32 at +0xb8 (16 bytes)
u32 FUN_7100193300(s64 param_1)
{
    return *(u32 *)(param_1 + 0xb8);
}

// 0x7100193310 — setter: write param_2&1 to byte at +0xe2 (16 bytes)
void FUN_7100193310(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xe2) = param_2 & 1;
}

// 0x7100193320 — getter: return byte at +0xe2 (16 bytes)
u8 FUN_7100193320(s64 param_1)
{
    return *(u8 *)(param_1 + 0xe2);
}

// 0x7100193370 — setter: write param_2&1 to byte at +0x129 (16 bytes)
void FUN_7100193370(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x129) = param_2 & 1;
}

// 0x7100193380 — setter: write param_2&1 to byte at +0x128 (16 bytes)
void FUN_7100193380(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x128) = param_2 & 1;
}

// 0x7100193540 — setter: write u64 param_2 to +0x120 (16 bytes)
void FUN_7100193540(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x120) = param_2;
}

// 0x7100193550 — clear: zero u64 at +0x120 (16 bytes)
void FUN_7100193550(s64 param_1)
{
    *(u64 *)(param_1 + 0x120) = 0;
}

// 0x7100193560 — getter: return byte at +0xac (16 bytes)
u8 FUN_7100193560(s64 param_1)
{
    return *(u8 *)(param_1 + 0xac);
}

// 0x7100193580 — getter: return u64 at +0x80 (16 bytes)
u64 FUN_7100193580(s64 param_1)
{
    return *(u64 *)(param_1 + 0x80);
}

// 0x71001939c0 — getter: return u64 at +0x38 (16 bytes)
u64 FUN_71001939c0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x38);
}

// 0x71001939f0 — getter: return u64 at +0x20 (16 bytes)
u64 FUN_71001939f0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x20);
}

// 0x7100193a00 — getter: return byte at +0xbc (16 bytes)
u8 FUN_7100193a00(s64 param_1)
{
    return *(u8 *)(param_1 + 0xbc);
}

// 0x7100193a30 — getter: return u64 at +0x360 (16 bytes)
u64 FUN_7100193a30(s64 param_1)
{
    return *(u64 *)(param_1 + 0x360);
}

// 0x7100193a40 — getter: return u64 at +0x368 (16 bytes)
u64 FUN_7100193a40(s64 param_1)
{
    return *(u64 *)(param_1 + 0x368);
}

// 0x7100193a80 — getter: return u16 at +0x35a (16 bytes)
u16 FUN_7100193a80(s64 param_1)
{
    return *(u16 *)(param_1 + 0x35a);
}

// 0x7100193a90 — getter: return u16 at +0x35c (16 bytes)
u16 FUN_7100193a90(s64 param_1)
{
    return *(u16 *)(param_1 + 0x35c);
}
