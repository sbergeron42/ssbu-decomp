#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 range, batch d4-023
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch wrappers

// NOTE: Functions with `in_x10` carry a value in AArch64 register X10 that
// cannot be represented in standard C++. It is initialized to 0 here for
// compilation; these functions will not verify.

// ---- Functions ---------------------------------------------------------------

// 0x710203dcf0 — vtable call +0x58
u64 FUN_710203dcf0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x58))(param_1);
    return 0;
}

// 0x710203de50 — store in_x10 at param_2+0x10, vtable call +0x70
u64 FUN_710203de50(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x70))(param_1);
    return 0;
}

// 0x710203f810 — store in_x10 at param_2+0x10, vtable call +0x188
u64 FUN_710203f810(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x188))(param_1);
    return 0;
}

// 0x7102040ae0 — vtable call +0x80
u64 FUN_7102040ae0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x80))(param_1);
    return 0;
}

// 0x71020410f0 — store in_x10 at param_2+0x10, vtable call +0x48
u64 FUN_71020410f0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x48))(param_1);
    return 0;
}

// 0x7102041670 — store in_x10 at param_2+0x10, vtable call +0x68
u64 FUN_7102041670(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x68))(param_1);
    return 0;
}

// 0x7102041bf0 — store in_x10 at param_2+0x10, vtable call +0xb0
u64 FUN_7102041bf0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xb0))(param_1);
    return 0;
}

// 0x7102042040 — store in_x10 at param_2+0x10, vtable call +0xc0
u64 FUN_7102042040(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xc0))(param_1);
    return 0;
}

// 0x7102042640 — vtable call +0xf8
u64 FUN_7102042640(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xf8))(param_1);
    return 0;
}

// 0x71020431a0 — store in_x10 at param_2+0x10, vtable call +0x138
u64 FUN_71020431a0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x138))(param_1);
    return 0;
}

// 0x7102043310 — store in_x10 at param_2+0x10, vtable call +0x140
u64 FUN_7102043310(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x140))(param_1);
    return 0;
}

// 0x7102043d40 — vtable call +0x90
u64 FUN_7102043d40(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x90))(param_1);
    return 0;
}

// 0x7102044100 — vtable call +0xb0
u64 FUN_7102044100(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xb0))(param_1);
    return 0;
}

// 0x71020441b0 — vtable call +0xb8
u64 FUN_71020441b0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xb8))(param_1);
    return 0;
}

// 0x7102046a80 — store in_x10 at param_2+0x10, vtable call +0x168
u64 FUN_7102046a80(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x168))(param_1);
    return 0;
}

// 0x710204a8c0 — vtable call +0x138
u64 FUN_710204a8c0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x138))(param_1);
    return 0;
}

// 0x71020502e0 — store in_x10 at param_2+0x10, vtable call +0x3b0
u64 FUN_71020502e0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x3b0))(param_1);
    return 0;
}

// 0x7102050468 — store in_x10 at param_2+0x10, vtable call +0x3c0
u64 FUN_7102050468(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x3c0))(param_1);
    return 0;
}

// 0x7102053220 — store in_x10 at param_2+0x10, vtable call +0x508
u64 FUN_7102053220(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x508))(param_1);
    return 0;
}

// 0x710205b550 — store in_x10 at param_2+0x10, vtable call +0x1c0
u64 FUN_710205b550(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1c0))(param_1);
    return 0;
}

// 0x710205c720 — vtable call +0x358
u64 FUN_710205c720(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x358))(param_1);
    return 0;
}

// 0x710205c7d0 — vtable call +0x360
u64 FUN_710205c7d0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x360))(param_1);
    return 0;
}

// 0x71020619b0 — vtable call +0x218
u64 FUN_71020619b0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x218))(param_1);
    return 0;
}

// 0x7102061d10 — store in_x10 at param_2+0x10, vtable call +0x240
u64 FUN_7102061d10(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x240))(param_1);
    return 0;
}

// 0x71020628f0 — vtable call +0x2c0
u64 FUN_71020628f0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x2c0))(param_1);
    return 0;
}
