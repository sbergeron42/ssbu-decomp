#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 range, batch d4-021
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch wrappers, single-indirect vtable calls

// NOTE: Functions with `in_x10` carry a value in AArch64 register X10 that
// cannot be represented in standard C++. It is initialized to 0 here for
// compilation; these functions will not verify.

// ---- Functions ---------------------------------------------------------------

// 0x710200a300 — store in_x10 at param_2+0x10, vtable call +0x480
u64 FUN_710200a300(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x480))(param_1);
    return 0;
}

// 0x710200b400 — vtable call +0x58
u64 FUN_710200b400(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x58))(param_1);
    return 0;
}

// 0x710200b4b0 — vtable call +0x60
u64 FUN_710200b4b0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x60))(param_1);
    return 0;
}

// 0x710200ba60 — store in_x10 at param_2+0x10, vtable call +0x50
u64 FUN_710200ba60(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x710200e0d0 — vtable call +0xf8
u64 FUN_710200e0d0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xf8))(param_1);
    return 0;
}

// 0x710200e400 — store in_x10 at param_2+0x10, vtable call +0x128
u64 FUN_710200e400(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x128))(param_1);
    return 0;
}

// 0x7102010380 — store in_x10 at param_2+0x10, vtable call +0x248
u64 FUN_7102010380(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x248))(param_1);
    return 0;
}

// 0x71020104f0 — store in_x10 at param_2+0x10, vtable call +0x250
u64 FUN_71020104f0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x250))(param_1);
    return 0;
}

// 0x7102010a50 — vtable call +0x290
u64 FUN_7102010a50(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x290))(param_1);
    return 0;
}

// 0x7102010b00 — vtable call +0x298
u64 FUN_7102010b00(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x298))(param_1);
    return 0;
}

// 0x7102010e00 — store in_x10 at param_2+0x10, vtable call +0x2d0
u64 FUN_7102010e00(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2d0))(param_1);
    return 0;
}

// 0x710201a5c0 — vtable call +0x98
u64 FUN_710201a5c0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x98))(param_1);
    return 0;
}

// 0x710201b2f0 — vtable call +0xb8
u64 FUN_710201b2f0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xb8))(param_1);
    return 0;
}

// 0x710201ebc0 — store in_x10 at param_2+0x10, vtable call +0x1a8
u64 FUN_710201ebc0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1a8))(param_1);
    return 0;
}

// 0x7102021990 — vtable call +0x240
u64 FUN_7102021990(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x240))(param_1);
    return 0;
}

// 0x71020223d0 — store in_x10 at param_2+0x10, vtable call +0x288
u64 FUN_71020223d0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x288))(param_1);
    return 0;
}

// 0x7102022610 — store in_x10 at param_2+0x10, vtable call +0x298
u64 FUN_7102022610(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x298))(param_1);
    return 0;
}

// 0x7102023ec0 — store in_x10 at param_2+0x10, vtable call +0x350
u64 FUN_7102023ec0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x350))(param_1);
    return 0;
}

// 0x7102024800 — vtable call +0x398
u64 FUN_7102024800(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x398))(param_1);
    return 0;
}

// 0x7102024a60 — vtable call +0x3f8
u64 FUN_7102024a60(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x3f8))(param_1);
    return 0;
}

// 0x7102024cf0 — store in_x10 at param_2+0x10, vtable call +0x408
u64 FUN_7102024cf0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x408))(param_1);
    return 0;
}

// 0x7102025220 — vtable call +0x430
u64 FUN_7102025220(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x430))(param_1);
    return 0;
}

// 0x7102025400 — vtable call +0x440
u64 FUN_7102025400(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x440))(param_1);
    return 0;
}

// 0x7102027170 — vtable call +0x490
u64 FUN_7102027170(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x490))(param_1);
    return 0;
}

// 0x7102027c80 — vtable call +0x50
u64 FUN_7102027c80(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x710202c120 — store in_x10 at param_2+0x10, vtable call +0x168
u64 FUN_710202c120(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x168))(param_1);
    return 0;
}

// 0x710202c290 — store in_x10 at param_2+0x10, vtable call +0x190
u64 FUN_710202c290(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 400))(param_1);
    return 0;
}
