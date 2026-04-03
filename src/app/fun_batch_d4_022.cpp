#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 range, batch d4-022
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch wrappers

// NOTE: Functions with `in_x10` carry a value in AArch64 register X10 that
// cannot be represented in standard C++. It is initialized to 0 here for
// compilation; these functions will not verify.

// ---- Functions ---------------------------------------------------------------

// 0x710202c4d0 — store in_x10 at param_2+0x10, vtable call +0x1a8
u64 FUN_710202c4d0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1a8))(param_1);
    return 0;
}

// 0x710202c640 — store in_x10 at param_2+0x10, vtable call +0x1e0
u64 FUN_710202c640(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1e0))(param_1);
    return 0;
}

// 0x710202c7b0 — store in_x10 at param_2+0x10, vtable call +0x1e8
u64 FUN_710202c7b0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1e8))(param_1);
    return 0;
}

// 0x710202c9f0 — store in_x10 at param_2+0x10, vtable call +0x1f8
u64 FUN_710202c9f0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x1f8))(param_1);
    return 0;
}

// 0x710202cd00 — store in_x10 at param_2+0x10, vtable call +0x210
u64 FUN_710202cd00(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x210))(param_1);
    return 0;
}

// 0x710202d2c0 — vtable call +0x250
u64 FUN_710202d2c0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x250))(param_1);
    return 0;
}

// 0x710202d370 — vtable call +0x258
u64 FUN_710202d370(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 600))(param_1);
    return 0;
}

// 0x710202d930 — vtable call +0x278
u64 FUN_710202d930(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x278))(param_1);
    return 0;
}

// 0x710202e020 — vtable call +0x2c8
u64 FUN_710202e020(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x2c8))(param_1);
    return 0;
}

// 0x710202e180 — store in_x10 at param_2+0x10, vtable call +0x2d0
u64 FUN_710202e180(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2d0))(param_1);
    return 0;
}

// 0x710202e2f0 — store in_x10 at param_2+0x10, vtable call +0x2d8
u64 FUN_710202e2f0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2d8))(param_1);
    return 0;
}

// 0x710202e630 — store in_x10 at param_2+0x10, vtable call +0x2f0
u64 FUN_710202e630(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x2f0))(param_1);
    return 0;
}

// 0x710202f690 — vtable call +0x360
u64 FUN_710202f690(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x360))(param_1);
    return 0;
}

// 0x71020305a0 — vtable call +0x400
u64 FUN_71020305a0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x400))(param_1);
    return 0;
}

// 0x710203a1a0 — vtable call +0x6b8
u64 FUN_710203a1a0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x6b8))(param_1);
    return 0;
}

// 0x710203a300 — store in_x10 at param_2+0x10, vtable call +0x6c0
u64 FUN_710203a300(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x6c0))(param_1);
    return 0;
}

// 0x710203a8e0 — store in_x10 at param_2+0x10, vtable call +0x6e0
u64 FUN_710203a8e0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x6e0))(param_1);
    return 0;
}

// 0x710203ab40 — vtable call +0x730
u64 FUN_710203ab40(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x730))(param_1);
    return 0;
}

// 0x710203aca0 — store in_x10 at param_2+0x10, vtable call +0x750
u64 FUN_710203aca0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x750))(param_1);
    return 0;
}

// 0x710203ae90 — vtable call +0x798
u64 FUN_710203ae90(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x798))(param_1);
    return 0;
}

// 0x710203af40 — vtable call +0x7a0
u64 FUN_710203af40(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x7a0))(param_1);
    return 0;
}

// 0x710203b0a0 — store in_x10 at param_2+0x10, vtable call +0x7a8
u64 FUN_710203b0a0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x7a8))(param_1);
    return 0;
}

// 0x710203b2d0 — vtable call +0x7b8
u64 FUN_710203b2d0(s64 *param_1)
{
    (*(void(**)(s64*))(*param_1 + 0x7b8))(param_1);
    return 0;
}

// 0x710203b7d0 — store in_x10 at param_2+0x10, vtable call +2000
u64 FUN_710203b7d0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 2000))(param_1);
    return 0;
}

// 0x710203b9c4 — store in_x10 at param_2+0x10, vtable call +0x7d8
u64 FUN_710203b9c4(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x7d8))(param_1);
    return 0;
}

// 0x710203bb30 — store in_x10 at param_2+0x10, vtable call +0x7f8
u64 FUN_710203bb30(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x7f8))(param_1);
    return 0;
}

// 0x710203bdd0 — store in_x10 at param_2+0x10, vtable call +0x818
u64 FUN_710203bdd0(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*param_1 + 0x818))(param_1);
    return 0;
}
