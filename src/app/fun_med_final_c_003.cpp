// MEDIUM framed_vtable_call batch 003 (0x710206a770 – 0x7102077d10)
// All functions use x8 ABI: object in x8, optional context in x0, x10 stored to x0+0x10

#include <stdint.h>
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t  s64;

// 0x710206a770
u32 FUN_710206a770(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xb0))(in_x8);
    return 0;
}

// 0x710206a8e0
u32 FUN_710206a8e0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x710206aa70
u32 FUN_710206aa70(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}

// 0x710206abd0
u32 FUN_710206abd0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xd0))(in_x8);
    return 0;
}

// 0x710206cad0
u32 FUN_710206cad0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc0))(in_x8);
    return 0;
}

// 0x710206cb80
u32 FUN_710206cb80(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}

// 0x710206d660
u32 FUN_710206d660(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xe8))(in_x8);
    return 0;
}

// 0x710206d8b0
u32 FUN_710206d8b0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x100))(in_x8);
    return 0;
}

// 0x710206d960
u32 FUN_710206d960(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x108))(in_x8);
    return 0;
}

// 0x710206e0c0
u32 FUN_710206e0c0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x138))(in_x8);
    return 0;
}

// 0x710206eeb0
u32 FUN_710206eeb0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x710206fce0
u32 FUN_710206fce0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xb0))(in_x8);
    return 0;
}

// 0x71020704d0
u32 FUN_71020704d0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x7102071cf0
u32 FUN_7102071cf0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xd8))(in_x8);
    return 0;
}

// 0x7102071f30
u32 FUN_7102071f30(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xe8))(in_x8);
    return 0;
}

// 0x7102072530
u32 FUN_7102072530(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x110))(in_x8);
    return 0;
}

// 0x71020726a0
u32 FUN_71020726a0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x118))(in_x8);
    return 0;
}

// 0x7102072840
u32 FUN_7102072840(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x128))(in_x8);
    return 0;
}

// 0x7102072e00
u32 FUN_7102072e00(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x7102074070
u32 FUN_7102074070(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x68))(in_x8);
    return 0;
}

// 0x7102074a40
u32 FUN_7102074a40(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xa0))(in_x8);
    return 0;
}

// 0x7102074f40
u32 FUN_7102074f40(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x7102075410
u32 FUN_7102075410(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x7102077ae0
u32 FUN_7102077ae0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x158))(in_x8);
    return 0;
}

// 0x7102077d10
u32 FUN_7102077d10(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x188))(in_x8);
    return 0;
}
