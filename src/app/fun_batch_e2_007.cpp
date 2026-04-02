#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-007
// Pool-e worker: auto-generated from Ghidra decompilation
// Pattern: framed vtable call wrappers (x8-object, various offsets)

// ---- with x10 store (lua_bind vtable variant, 32 bytes) -----------------------------------------------
// Ghidra param_1 = x8 (object), param_2 = x0 (lua state = my param_1)

// 0x7102000e40 — vtable[0x1b0/8](obj) with x10 store
u32 FUN_7102000e40(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1b0))(in_x8);
    return 0;
}

// 0x71020061b0 — vtable[0x280/8](obj) with x10 store
u32 FUN_71020061b0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x280))(in_x8);
    return 0;
}

// 0x710200a300 — vtable[0x480/8](obj) with x10 store
u32 FUN_710200a300(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x480))(in_x8);
    return 0;
}

// 0x7102024cf0 — vtable[0x408/8](obj) with x10 store
u32 FUN_7102024cf0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x408))(in_x8);
    return 0;
}

// 0x710202cd00 — vtable[0x210/8](obj) with x10 store
u32 FUN_710202cd00(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x210))(in_x8);
    return 0;
}

// 0x710202ff00 — vtable[0x3a8/8](obj) with x10 store
u32 FUN_710202ff00(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3a8))(in_x8);
    return 0;
}

// 0x710203aca0 — vtable[0x750/8](obj) with x10 store
u32 FUN_710203aca0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x750))(in_x8);
    return 0;
}

// 0x710203b0a0 — vtable[0x7a8/8](obj) with x10 store
u32 FUN_710203b0a0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x7a8))(in_x8);
    return 0;
}

// 0x710203bb30 — vtable[0x7f8/8](obj) with x10 store
u32 FUN_710203bb30(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x7f8))(in_x8);
    return 0;
}

// 0x710203bdd0 — vtable[0x818/8](obj) with x10 store
u32 FUN_710203bdd0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x818))(in_x8);
    return 0;
}

// 0x710209f2f0 — vtable[0x2b0/8](obj) with x10 store
u32 FUN_710209f2f0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x2b0))(in_x8);
    return 0;
}

// 0x71020a7160 — vtable[0x3b8/8](obj) with x10 store
u32 FUN_71020a7160(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3b8))(in_x8);
    return 0;
}

// 0x71020afd68 — vtable[0x460/8](obj) with x10 store
u32 FUN_71020afd68(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x460))(in_x8);
    return 0;
}

// ---- without x10 store (36 bytes each) -----------------------------------------------

// 0x71020861a0 — vtable[0x1d8/8](obj)
u32 FUN_71020861a0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x1d8))(in_x8);
    return 0;
}

// 0x710208a6b0 — vtable[0xe8/8](obj)
u32 FUN_710208a6b0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xe8))(in_x8);
    return 0;
}

// 0x710208bfb0 — vtable[0x98/8](obj)
u32 FUN_710208bfb0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x98))(in_x8);
    return 0;
}

// 0x7102090ff0 — vtable[0x198/8](obj)
u32 FUN_7102090ff0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x198))(in_x8);
    return 0;
}

// 0x71020916b0 — vtable[0x1c8/8](obj)
u32 FUN_71020916b0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x1c8))(in_x8);
    return 0;
}

// 0x7102091c20 — vtable[0x218/8](obj)
u32 FUN_7102091c20(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x218))(in_x8);
    return 0;
}

// 0x7102092a80 — vtable[0x68/8](obj)
u32 FUN_7102092a80(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x68))(in_x8);
    return 0;
}
