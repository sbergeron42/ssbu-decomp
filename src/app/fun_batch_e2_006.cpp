#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-006
// Pool-e worker: auto-generated from Ghidra decompilation
// Pattern: framed vtable call — x8 holds object, vtable[0xNN](obj), return 0

// ---- framed vtable call wrappers (36 bytes each) -----------------------------------------------
// Pattern: stp; mov x29; ldr x9,[x8]; ldr x9,[x9,#0xNN]; mov x0,x8; blr x9; ldp; mov w0,wzr; ret
// x8 = object (BattleObjectModuleAccessor or similar), x0/x1 unused

// 0x7102002f90 — vtable[0xc0/8](obj) (36 bytes)
u32 FUN_7102002f90(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc0))(in_x8);
    return 0;
}

// 0x71020034c0 — vtable[0xf8/8](obj) (36 bytes)
u32 FUN_71020034c0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xf8))(in_x8);
    return 0;
}

// 0x7102008aa0 — vtable[0x3b8/8](obj) (36 bytes)
u32 FUN_7102008aa0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x3b8))(in_x8);
    return 0;
}

// 0x7102008fd0 — vtable[0x3e8/8](obj) (36 bytes)
// Note: 1000 decimal = 0x3e8
u32 FUN_7102008fd0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x3e8))(in_x8);
    return 0;
}

// 0x7102009f70 — vtable[0x468/8](obj) (36 bytes)
u32 FUN_7102009f70(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x468))(in_x8);
    return 0;
}

// 0x7102024a60 — vtable[0x3f8/8](obj) (36 bytes)
u32 FUN_7102024a60(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x3f8))(in_x8);
    return 0;
}

// 0x7102025220 — vtable[0x430/8](obj) (36 bytes)
u32 FUN_7102025220(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x430))(in_x8);
    return 0;
}

// 0x7102027170 — vtable[0x490/8](obj) (36 bytes)
u32 FUN_7102027170(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x490))(in_x8);
    return 0;
}

// 0x7102027c80 — vtable[0x50/8](obj) (36 bytes)
u32 FUN_7102027c80(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x710202f690 — vtable[0x360/8](obj) (36 bytes)
u32 FUN_710202f690(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x360))(in_x8);
    return 0;
}

// 0x71020305a0 — vtable[0x400/8](obj) (36 bytes)
u32 FUN_71020305a0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x400))(in_x8);
    return 0;
}

// 0x7102042040 — vtable[0xc0/8](obj), with x10 store — standard lua_bind variant (32 bytes)
u32 FUN_7102042040(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xc0))(in_x8);
    return 0;
}

// 0x7102043d40 — vtable[0x90/8](obj) (36 bytes)
u32 FUN_7102043d40(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x90))(in_x8);
    return 0;
}

// 0x71020441b0 — vtable[0xb8/8](obj) (36 bytes)
u32 FUN_71020441b0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x710205c7d0 — vtable[0x360/8](obj) (36 bytes)
u32 FUN_710205c7d0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x360))(in_x8);
    return 0;
}

// 0x7102067880 — vtable[0x590/8](obj) (36 bytes)
u32 FUN_7102067880(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x590))(in_x8);
    return 0;
}

// 0x710206cb80 — vtable[0xc8/8](obj) (36 bytes)
// Note: 200 decimal = 0xc8
u32 FUN_710206cb80(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}

// 0x71020704d0 — vtable[0x50/8](obj) (36 bytes)
u32 FUN_71020704d0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x7102072840 — vtable[0x128/8](obj) (36 bytes)
u32 FUN_7102072840(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x128))(in_x8);
    return 0;
}

// 0x7102074070 — vtable[0x68/8](obj) (36 bytes)
u32 FUN_7102074070(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x68))(in_x8);
    return 0;
}

// 0x7102077d10 — vtable[0x188/8](obj) (36 bytes)
u32 FUN_7102077d10(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x188))(in_x8);
    return 0;
}

// 0x710207b8e0 — vtable[0x188/8](obj) (36 bytes)
u32 FUN_710207b8e0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x188))(in_x8);
    return 0;
}

// 0x710207f4b0 — vtable[0x188/8](obj) (36 bytes)
u32 FUN_710207f4b0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x188))(in_x8);
    return 0;
}

// 0x7102080cc0 — vtable[0x88/8](obj) (36 bytes)
u32 FUN_7102080cc0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x88))(in_x8);
    return 0;
}

// 0x7102083000 — vtable[0xc8/8](obj) (36 bytes)
u32 FUN_7102083000(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}
