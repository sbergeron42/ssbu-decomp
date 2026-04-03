#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 range, batch d4-020
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch wrappers, single-indirect vtable calls

// NOTE: Functions with `in_x10` carry a value in AArch64 register X10 that
// cannot be represented in standard C++. It is initialized to 0 here for
// compilation; these functions will not verify.

// ---- Functions ---------------------------------------------------------------

// 0x7102000e40 — store in_x10 at param_2+0x10, vtable call +0x1b0
u64 FUN_7102000e40(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1b0))(param_1);
    return 0;
}

// 0x7102002d50 — store in_x10 at param_2+0x10, vtable call +0xa8
u64 FUN_7102002d50(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xa8))(param_1);
    return 0;
}

// 0x7102002ee0 — vtable call +0xb8
u64 FUN_7102002ee0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xb8))(param_1);
    return 0;
}

// 0x7102002f90 — vtable call +0xc0
u64 FUN_7102002f90(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xc0))(param_1);
    return 0;
}

// 0x7102003410 — vtable call +0xf0
u64 FUN_7102003410(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xf0))(param_1);
    return 0;
}

// 0x71020034c0 — vtable call +0xf8
u64 FUN_71020034c0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xf8))(param_1);
    return 0;
}

// 0x71020036a0 — vtable call +0x108
u64 FUN_71020036a0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x108))(param_1);
    return 0;
}

// 0x7102003920 — vtable call +0x118
u64 FUN_7102003920(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x118))(param_1);
    return 0;
}

// 0x7102003ba0 — vtable call +0x128
u64 FUN_7102003ba0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x128))(param_1);
    return 0;
}

// 0x7102003c50 — vtable call +0x130
u64 FUN_7102003c50(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x130))(param_1);
    return 0;
}

// 0x7102003d00 — vtable call +0x138
u64 FUN_7102003d00(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x138))(param_1);
    return 0;
}

// 0x7102003db0 — vtable call +0x140
u64 FUN_7102003db0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x140))(param_1);
    return 0;
}

// 0x7102003e60 — vtable call +0x158
u64 FUN_7102003e60(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x158))(param_1);
    return 0;
}

// 0x7102003f10 — vtable call +0x160
u64 FUN_7102003f10(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x160))(param_1);
    return 0;
}

// 0x7102003fc0 — vtable call +0x168
u64 FUN_7102003fc0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x168))(param_1);
    return 0;
}

// 0x7102004070 — vtable call +0x170
u64 FUN_7102004070(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x170))(param_1);
    return 0;
}

// 0x71020061b0 — store in_x10 at param_2+0x10, vtable call +0x280
u64 FUN_71020061b0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x280))(param_1);
    return 0;
}

// 0x7102006950 — vtable call +0x2b8
u64 FUN_7102006950(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x2b8))(param_1);
    return 0;
}

// 0x7102006a00 — vtable call +0x2c0
u64 FUN_7102006a00(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x2c0))(param_1);
    return 0;
}

// 0x7102007180 — store in_x10 at param_2+0x10, vtable call +0x2f0
u64 FUN_7102007180(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2f0))(param_1);
    return 0;
}

// 0x71020077c0 — vtable call +0x328
u64 FUN_71020077c0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x328))(param_1);
    return 0;
}

// 0x7102007870 — vtable call +0x330
u64 FUN_7102007870(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x330))(param_1);
    return 0;
}

// 0x7102007dc8 — store in_x10 at param_2+0x10, vtable call +0x358
u64 FUN_7102007dc8(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x358))(param_1);
    return 0;
}

// 0x71020084c0 — store in_x10 at param_2+0x10, vtable call +0x388
u64 FUN_71020084c0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x388))(param_1);
    return 0;
}

// 0x7102008750 — vtable call +0x398
u64 FUN_7102008750(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x398))(param_1);
    return 0;
}

// 0x7102008aa0 — vtable call +0x3b8
u64 FUN_7102008aa0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x3b8))(param_1);
    return 0;
}

// 0x7102008fd0 — vtable call +0x3e8
u64 FUN_7102008fd0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x3e8))(param_1);
    return 0;
}

// 0x7102009d30 — store in_x10 at param_2+0x10, vtable call +0x458
u64 FUN_7102009d30(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x458))(param_1);
    return 0;
}

// 0x7102009ec8 — store in_x10 at param_2+0x10, vtable call +0x460
u64 FUN_7102009ec8(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x460))(param_1);
    return 0;
}

// 0x7102009f70 — vtable call +0x468
u64 FUN_7102009f70(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x468))(param_1);
    return 0;
}
