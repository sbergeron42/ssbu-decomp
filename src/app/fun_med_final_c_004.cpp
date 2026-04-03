// MEDIUM framed_vtable_call batch 004 (0x710207c340 – 0x710208ca30)

#include <stdint.h>
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t  s64;

// 0x710207c340
u32 FUN_710207c340(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1d0))(in_x8);
    return 0;
}

// 0x710207c4b0
u32 FUN_710207c4b0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1e8))(in_x8);
    return 0;
}

// 0x710207cbb0
u32 FUN_710207cbb0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x710207f280
u32 FUN_710207f280(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x158))(in_x8);
    return 0;
}

// 0x710207f4b0
u32 FUN_710207f4b0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x188))(in_x8);
    return 0;
}

// 0x710207ff10
u32 FUN_710207ff10(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1d0))(in_x8);
    return 0;
}

// 0x7102080080
u32 FUN_7102080080(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1e8))(in_x8);
    return 0;
}

// 0x7102080cc0
u32 FUN_7102080cc0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x88))(in_x8);
    return 0;
}

// 0x7102081440
u32 FUN_7102081440(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}

// 0x7102083000
u32 FUN_7102083000(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}

// 0x71020833d0
u32 FUN_71020833d0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xd8))(in_x8);
    return 0;
}

// 0x7102083610
u32 FUN_7102083610(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xe8))(in_x8);
    return 0;
}

// 0x7102085b70
u32 FUN_7102085b70(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x1b0))(in_x8);
    return 0;
}

// 0x7102085cd0
u32 FUN_7102085cd0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1b8))(in_x8);
    return 0;
}

// 0x71020861a0
u32 FUN_71020861a0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x1d8))(in_x8);
    return 0;
}

// 0x71020864b0
u32 FUN_71020864b0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x238))(in_x8);
    return 0;
}

// 0x7102086560
u32 FUN_7102086560(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x240))(in_x8);
    return 0;
}

// 0x7102086fd0
u32 FUN_7102086fd0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x2c0))(in_x8);
    return 0;
}

// 0x7102087140
u32 FUN_7102087140(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x2d8))(in_x8);
    return 0;
}

// 0x7102088b40
u32 FUN_7102088b40(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x188))(in_x8);
    return 0;
}

// 0x7102089340
u32 FUN_7102089340(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x48))(in_x8);
    return 0;
}

// 0x71020899f0
u32 FUN_71020899f0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x78))(in_x8);
    return 0;
}

// 0x7102089c08
u32 FUN_7102089c08(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x80))(in_x8);
    return 0;
}

// 0x710208a5f0
u32 FUN_710208a5f0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xe0))(in_x8);
    return 0;
}

// 0x710208a6b0
u32 FUN_710208a6b0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xe8))(in_x8);
    return 0;
}

// 0x710208bb90
u32 FUN_710208bb90(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x58))(in_x8);
    return 0;
}

// 0x710208bef0
u32 FUN_710208bef0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x90))(in_x8);
    return 0;
}

// 0x710208bfb0
u32 FUN_710208bfb0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x98))(in_x8);
    return 0;
}

// 0x710208c980
u32 FUN_710208c980(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x80))(in_x8);
    return 0;
}

// 0x710208ca30
u32 FUN_710208ca30(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x88))(in_x8);
    return 0;
}
