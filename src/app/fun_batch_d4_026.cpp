#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 range, batch d4-026
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch wrappers

// NOTE: Functions with `in_x10` carry a value in AArch64 register X10 that
// cannot be represented in standard C++. It is initialized to 0 here for
// compilation; these functions will not verify.

// ---- Functions ---------------------------------------------------------------

// 0x7102077d10 — vtable call +0x188
u64 FUN_7102077d10(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x188))(param_1);
    return 0;
}

// 0x7102078770 — store in_x10 at param_2+0x10, vtable call +0x1d0
u64 FUN_7102078770(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1d0))(param_1);
    return 0;
}

// 0x71020788e0 — store in_x10 at param_2+0x10, vtable call +0x1e8
u64 FUN_71020788e0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1e8))(param_1);
    return 0;
}

// 0x7102078fe0 — vtable call +0x50
u64 FUN_7102078fe0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x710207b6b0 — store in_x10 at param_2+0x10, vtable call +0x158
u64 FUN_710207b6b0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x158))(param_1);
    return 0;
}

// 0x710207b8e0 — vtable call +0x188
u64 FUN_710207b8e0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x188))(param_1);
    return 0;
}

// 0x710207c340 — store in_x10 at param_2+0x10, vtable call +0x1d0
u64 FUN_710207c340(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1d0))(param_1);
    return 0;
}

// 0x710207c4b0 — store in_x10 at param_2+0x10, vtable call +0x1e8
u64 FUN_710207c4b0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1e8))(param_1);
    return 0;
}

// 0x710207cbb0 — vtable call +0x50
u64 FUN_710207cbb0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x50))(param_1);
    return 0;
}

// 0x710207f280 — store in_x10 at param_2+0x10, vtable call +0x158
u64 FUN_710207f280(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x158))(param_1);
    return 0;
}

// 0x710207f4b0 — vtable call +0x188
u64 FUN_710207f4b0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x188))(param_1);
    return 0;
}

// 0x710207ff10 — store in_x10 at param_2+0x10, vtable call +0x1d0
u64 FUN_710207ff10(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1d0))(param_1);
    return 0;
}

// 0x7102080080 — store in_x10 at param_2+0x10, vtable call +0x1e8
u64 FUN_7102080080(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1e8))(param_1);
    return 0;
}

// 0x7102080cc0 — vtable call +0x88
u64 FUN_7102080cc0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x88))(param_1);
    return 0;
}

// 0x7102081440 — vtable call +0xc8
u64 FUN_7102081440(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 200))(param_1);
    return 0;
}

// 0x7102083000 — vtable call +0xc8
u64 FUN_7102083000(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 200))(param_1);
    return 0;
}

// 0x71020833d0 — store in_x10 at param_2+0x10, vtable call +0xd8
u64 FUN_71020833d0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xd8))(param_1);
    return 0;
}

// 0x7102083610 — store in_x10 at param_2+0x10, vtable call +0xe8
u64 FUN_7102083610(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0xe8))(param_1);
    return 0;
}

// 0x7102085b70 — vtable call +0x1b0
u64 FUN_7102085b70(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x1b0))(param_1);
    return 0;
}

// 0x7102085cd0 — store in_x10 at param_2+0x10, vtable call +0x1b8
u64 FUN_7102085cd0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1b8))(param_1);
    return 0;
}

// 0x71020861a0 — vtable call +0x1d8
u64 FUN_71020861a0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x1d8))(param_1);
    return 0;
}

// 0x71020864b0 — vtable call +0x238
u64 FUN_71020864b0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x238))(param_1);
    return 0;
}

// 0x7102086560 — vtable call +0x240
u64 FUN_7102086560(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x240))(param_1);
    return 0;
}

// 0x7102086fd0 — store in_x10 at param_2+0x10, vtable call +0x2c0
u64 FUN_7102086fd0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2c0))(param_1);
    return 0;
}

// 0x7102087140 — store in_x10 at param_2+0x10, vtable call +0x2d8
u64 FUN_7102087140(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2d8))(param_1);
    return 0;
}
