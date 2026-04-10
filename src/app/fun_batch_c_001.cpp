// Batch C - 001: vtable dispatch stubs via x8 register (0x7102 range)
// All functions follow the same pattern: store x10 at out+0x10 (if 2-param),
// dispatch through x8's vtable at varying offsets, return 0.

#include "types.h"

// 0x7102000e40 -- vtable dispatch via x8 at 0x1b0, store x10
u32 FUN_7102000e40(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1b0))(in_x8);
    return 0;
}

// 0x7102002d50 -- vtable dispatch via x8 at 0xa8, store x10
u32 FUN_7102002d50(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xa8))(in_x8);
    return 0;
}

// 0x7102002ee0 -- vtable dispatch via x8 at 0xb8
u32 FUN_7102002ee0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x7102002f90 -- vtable dispatch via x8 at 0xc0
u32 FUN_7102002f90(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xc0))(in_x8);
    return 0;
}

// 0x7102003410 -- vtable dispatch via x8 at 0xf0
u32 FUN_7102003410(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xf0))(in_x8);
    return 0;
}

// 0x71020034c0 -- vtable dispatch via x8 at 0xf8
u32 FUN_71020034c0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xf8))(in_x8);
    return 0;
}

// 0x71020036a0 -- vtable dispatch via x8 at 0x108
u32 FUN_71020036a0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x108))(in_x8);
    return 0;
}

// 0x7102003920 -- vtable dispatch via x8 at 0x118
u32 FUN_7102003920(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x118))(in_x8);
    return 0;
}

// 0x7102003ba0 -- vtable dispatch via x8 at 0x128
u32 FUN_7102003ba0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x128))(in_x8);
    return 0;
}

// 0x7102003c50 -- vtable dispatch via x8 at 0x130
u32 FUN_7102003c50(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x130))(in_x8);
    return 0;
}

// 0x7102003d00 -- vtable dispatch via x8 at 0x138
u32 FUN_7102003d00(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x138))(in_x8);
    return 0;
}

// 0x7102003db0 -- vtable dispatch via x8 at 0x140
u32 FUN_7102003db0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x140))(in_x8);
    return 0;
}

// 0x7102003e60 -- vtable dispatch via x8 at 0x158
u32 FUN_7102003e60(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x158))(in_x8);
    return 0;
}

// 0x7102003f10 -- vtable dispatch via x8 at 0x160
u32 FUN_7102003f10(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x160))(in_x8);
    return 0;
}

// 0x7102003fc0 -- vtable dispatch via x8 at 0x168
u32 FUN_7102003fc0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x168))(in_x8);
    return 0;
}

// 0x7102004070 -- vtable dispatch via x8 at 0x170
u32 FUN_7102004070(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x170))(in_x8);
    return 0;
}

// 0x71020061b0 -- vtable dispatch via x8 at 0x280, store x10
u32 FUN_71020061b0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x280))(in_x8);
    return 0;
}

// 0x7102006950 -- vtable dispatch via x8 at 0x2b8
u32 FUN_7102006950(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x2b8))(in_x8);
    return 0;
}

// 0x7102006a00 -- vtable dispatch via x8 at 0x2c0
u32 FUN_7102006a00(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x2c0))(in_x8);
    return 0;
}

// 0x7102007180 -- vtable dispatch via x8 at 0x2f0, store x10
u32 FUN_7102007180(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x2f0))(in_x8);
    return 0;
}

// 0x71020077c0 -- vtable dispatch via x8 at 0x328
u32 FUN_71020077c0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x328))(in_x8);
    return 0;
}

// 0x7102007870 -- vtable dispatch via x8 at 0x330
u32 FUN_7102007870(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x330))(in_x8);
    return 0;
}

// 0x7102007dc8 -- vtable dispatch via x8 at 0x358, store x10
u32 FUN_7102007dc8(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x358))(in_x8);
    return 0;
}

// 0x71020084c0 -- vtable dispatch via x8 at 0x388, store x10
u32 FUN_71020084c0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x388))(in_x8);
    return 0;
}

// 0x7102008750 -- vtable dispatch via x8 at 0x398
u32 FUN_7102008750(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x398))(in_x8);
    return 0;
}

// 0x7102008aa0 -- vtable dispatch via x8 at 0x3b8
u32 FUN_7102008aa0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x3b8))(in_x8);
    return 0;
}

// 0x7102008fd0 -- vtable dispatch via x8 at 0x3e8
u32 FUN_7102008fd0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x3e8))(in_x8);
    return 0;
}

// 0x7102009d30 -- vtable dispatch via x8 at 0x458, store x10
u32 FUN_7102009d30(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x458))(in_x8);
    return 0;
}

// 0x7102009ec8 -- vtable dispatch via x8 at 0x460, store x10
u32 FUN_7102009ec8(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x460))(in_x8);
    return 0;
}

// 0x7102009f70 -- vtable dispatch via x8 at 0x468
u32 FUN_7102009f70(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x468))(in_x8);
    return 0;
}

// 0x710200a300 -- vtable dispatch via x8 at 0x480, store x10
u32 FUN_710200a300(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x480))(in_x8);
    return 0;
}

// 0x710200b400 -- vtable dispatch via x8 at 0x58
u32 FUN_710200b400(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x58))(in_x8);
    return 0;
}

// 0x710200b4b0 -- vtable dispatch via x8 at 0x60
u32 FUN_710200b4b0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x60))(in_x8);
    return 0;
}

// 0x710200ba60 -- vtable dispatch via x8 at 0x50, store x10
u32 FUN_710200ba60(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x710200e0d0 -- vtable dispatch via x8 at 0xf8
u32 FUN_710200e0d0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xf8))(in_x8);
    return 0;
}

// 0x710200e400 -- vtable dispatch via x8 at 0x128, store x10
u32 FUN_710200e400(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x128))(in_x8);
    return 0;
}

// 0x7102010380 -- vtable dispatch via x8 at 0x248, store x10
u32 FUN_7102010380(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x248))(in_x8);
    return 0;
}

// 0x71020104f0 -- vtable dispatch via x8 at 0x250, store x10
u32 FUN_71020104f0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x250))(in_x8);
    return 0;
}

// 0x7102010a50 -- vtable dispatch via x8 at 0x290
u32 FUN_7102010a50(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x290))(in_x8);
    return 0;
}

// 0x7102010b00 -- vtable dispatch via x8 at 0x298
u32 FUN_7102010b00(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x298))(in_x8);
    return 0;
}

// 0x7102010e00 -- vtable dispatch via x8 at 0x2d0, store x10
u32 FUN_7102010e00(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x2d0))(in_x8);
    return 0;
}

// 0x710201a5c0 -- vtable dispatch via x8 at 0x98
u32 FUN_710201a5c0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x98))(in_x8);
    return 0;
}

// 0x710201b2f0 -- vtable dispatch via x8 at 0xb8
u32 FUN_710201b2f0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x710201ebc0 -- vtable dispatch via x8 at 0x1a8, store x10
u32 FUN_710201ebc0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1a8))(in_x8);
    return 0;
}

// 0x7102021990 -- vtable dispatch via x8 at 0x240
u32 FUN_7102021990(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x240))(in_x8);
    return 0;
}

// 0x71020223d0 -- vtable dispatch via x8 at 0x288, store x10
u32 FUN_71020223d0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x288))(in_x8);
    return 0;
}

// 0x7102022610 -- vtable dispatch via x8 at 0x298, store x10
u32 FUN_7102022610(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x298))(in_x8);
    return 0;
}

// 0x7102023ec0 -- vtable dispatch via x8 at 0x350, store x10
u32 FUN_7102023ec0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x350))(in_x8);
    return 0;
}

// 0x7102024800 -- vtable dispatch via x8 at 0x398
u32 FUN_7102024800(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x398))(in_x8);
    return 0;
}

// 0x7102024a60 -- vtable dispatch via x8 at 0x3f8
u32 FUN_7102024a60(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x3f8))(in_x8);
    return 0;
}

// 0x7102024cf0 -- vtable dispatch via x8 at 0x408, store x10
u32 FUN_7102024cf0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x408))(in_x8);
    return 0;
}

// 0x7102025220 -- vtable dispatch via x8 at 0x430
u32 FUN_7102025220(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x430))(in_x8);
    return 0;
}

// 0x7102025400 -- vtable dispatch via x8 at 0x440
u32 FUN_7102025400(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x440))(in_x8);
    return 0;
}

// 0x7102027c80 -- vtable dispatch via x8 at 0x50
u32 FUN_7102027c80(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x710202c120 -- vtable dispatch via x8 at 0x168, store x10
u32 FUN_710202c120(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x168))(in_x8);
    return 0;
}

// 0x710202c290 -- vtable dispatch via x8 at 0x190, store x10
u32 FUN_710202c290(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x190))(in_x8);
    return 0;
}

// 0x710202c4d0 -- vtable dispatch via x8 at 0x1a8, store x10
u32 FUN_710202c4d0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1a8))(in_x8);
    return 0;
}

// 0x710202c640 -- vtable dispatch via x8 at 0x1e0, store x10
u32 FUN_710202c640(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1e0))(in_x8);
    return 0;
}

// 0x710202c7b0 -- vtable dispatch via x8 at 0x1e8, store x10
u32 FUN_710202c7b0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1e8))(in_x8);
    return 0;
}
