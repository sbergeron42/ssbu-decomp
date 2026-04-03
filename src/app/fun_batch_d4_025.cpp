#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 range, batch d4-025
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch wrappers

// NOTE: Functions with `in_x10` carry a value in AArch64 register X10 that
// cannot be represented in standard C++. It is initialized to 0 here for
// compilation; these functions will not verify.

// ---- Functions ---------------------------------------------------------------

// 0x710202f870 — vtable call +0x370
u64 FUN_710202f870(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x370))(param_1);
    return 0;
}

// 0x710202ff00 — store in_x10 at param_2+0x10, vtable call +0x3a8
u64 FUN_710202ff00(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x3a8))(param_1);
    return 0;
}

// 0x710206d660 — vtable call +0xe8
u64 FUN_710206d660(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xe8))(param_1);
    return 0;
}

// 0x710206d8b0 — vtable call +0x100
u64 FUN_710206d8b0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x100))(param_1);
    return 0;
}

// 0x710206d960 — vtable call +0x108
u64 FUN_710206d960(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x108))(param_1);
    return 0;
}

// 0x710206e0c0 — vtable call +0x138
u64 FUN_710206e0c0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x138))(param_1);
    return 0;
}

// 0x710206eeb0 — vtable call +0x50
u64 FUN_710206eeb0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x710206fce0 — store in_x10 at param_2+0x10, vtable call +0xb0
u64 FUN_710206fce0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xb0))(param_1);
    return 0;
}

// 0x71020704d0 — vtable call +0x50
u64 FUN_71020704d0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x7102071cf0 — store in_x10 at param_2+0x10, vtable call +0xd8
u64 FUN_7102071cf0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xd8))(param_1);
    return 0;
}

// 0x7102071f30 — store in_x10 at param_2+0x10, vtable call +0xe8
u64 FUN_7102071f30(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xe8))(param_1);
    return 0;
}

// 0x7102072530 — store in_x10 at param_2+0x10, vtable call +0x110
u64 FUN_7102072530(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x110))(param_1);
    return 0;
}

// 0x71020726a0 — store in_x10 at param_2+0x10, vtable call +0x118
u64 FUN_71020726a0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x118))(param_1);
    return 0;
}

// 0x7102072840 — vtable call +0x128
u64 FUN_7102072840(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x128))(param_1);
    return 0;
}

// 0x7102072e00 — store in_x10 at param_2+0x10, vtable call +0x50
u64 FUN_7102072e00(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x7102074070 — vtable call +0x68
u64 FUN_7102074070(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x68))(param_1);
    return 0;
}

// 0x7102074a40 — vtable call +0xa0
u64 FUN_7102074a40(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0xa0))(param_1);
    return 0;
}

// 0x7102074f40 — store in_x10 at param_2+0x10, vtable call +0xb8
u64 FUN_7102074f40(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xb8))(param_1);
    return 0;
}

// 0x7102075410 — vtable call +0x50
u64 FUN_7102075410(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x7102077ae0 — store in_x10 at param_2+0x10, vtable call +0x158
u64 FUN_7102077ae0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x158))(param_1);
    return 0;
}
