// Batch C - 003: vtable dispatch stubs via x8 register (0x7102 range)
// All 40 functions follow the same pattern: store x10 at out+0x10 (if 2-param),
// dispatch through x8's vtable at varying offsets, return 0.

#include "types.h"

// 0x71020410f0 -- vtable dispatch via x8 at 0x48, store x10
u32 FUN_71020410f0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x48))(in_x8);
    return 0;
}

// 0x7102041670 -- vtable dispatch via x8 at 0x68, store x10
u32 FUN_7102041670(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x68))(in_x8);
    return 0;
}

// 0x7102041bf0 -- vtable dispatch via x8 at 0xb0, store x10
u32 FUN_7102041bf0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xb0))(in_x8);
    return 0;
}

// 0x7102042040 -- vtable dispatch via x8 at 0xc0, store x10
u32 FUN_7102042040(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xc0))(in_x8);
    return 0;
}

// 0x7102042640 -- vtable dispatch via x8 at 0xf8
u32 FUN_7102042640(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xf8))(in_x8);
    return 0;
}

// 0x71020431a0 -- vtable dispatch via x8 at 0x138, store x10
u32 FUN_71020431a0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x138))(in_x8);
    return 0;
}

// 0x7102043310 -- vtable dispatch via x8 at 0x140, store x10
u32 FUN_7102043310(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x140))(in_x8);
    return 0;
}

// 0x7102043d40 -- vtable dispatch via x8 at 0x90
u32 FUN_7102043d40(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x90))(in_x8);
    return 0;
}

// 0x7102044100 -- vtable dispatch via x8 at 0xb0
u32 FUN_7102044100(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xb0))(in_x8);
    return 0;
}

// 0x71020441b0 -- vtable dispatch via x8 at 0xb8
u32 FUN_71020441b0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x7102046a80 -- vtable dispatch via x8 at 0x168, store x10
u32 FUN_7102046a80(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x168))(in_x8);
    return 0;
}

// 0x710204a8c0 -- vtable dispatch via x8 at 0x138
u32 FUN_710204a8c0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x138))(in_x8);
    return 0;
}

// 0x71020502e0 -- vtable dispatch via x8 at 0x3b0, store x10
u32 FUN_71020502e0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3b0))(in_x8);
    return 0;
}

// 0x7102050468 -- vtable dispatch via x8 at 0x3c0, store x10
u32 FUN_7102050468(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3c0))(in_x8);
    return 0;
}

// 0x7102053220 -- vtable dispatch via x8 at 0x508, store x10
u32 FUN_7102053220(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x508))(in_x8);
    return 0;
}

// 0x710205b550 -- vtable dispatch via x8 at 0x1c0, store x10
u32 FUN_710205b550(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x1c0))(in_x8);
    return 0;
}

// 0x710205c720 -- vtable dispatch via x8 at 0x358
u32 FUN_710205c720(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x358))(in_x8);
    return 0;
}

// 0x710205c7d0 -- vtable dispatch via x8 at 0x360
u32 FUN_710205c7d0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x360))(in_x8);
    return 0;
}

// 0x71020619b0 -- vtable dispatch via x8 at 0x218
u32 FUN_71020619b0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x218))(in_x8);
    return 0;
}

// 0x7102061d10 -- vtable dispatch via x8 at 0x240, store x10
u32 FUN_7102061d10(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x240))(in_x8);
    return 0;
}

// 0x71020628f0 -- vtable dispatch via x8 at 0x2c0
u32 FUN_71020628f0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x2c0))(in_x8);
    return 0;
}

// 0x7102065690 -- vtable dispatch via x8 at 0x3a0, store x10
u32 FUN_7102065690(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3a0))(in_x8);
    return 0;
}

// 0x71020657f0 -- vtable dispatch via x8 at 0x3a8, store x10
u32 FUN_71020657f0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3a8))(in_x8);
    return 0;
}

// 0x7102066010 -- vtable dispatch via x8 at 0x3d0, store x10
u32 FUN_7102066010(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3d0))(in_x8);
    return 0;
}

// 0x7102066788 -- vtable dispatch via x8 at 0x420, store x10
u32 FUN_7102066788(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x420))(in_x8);
    return 0;
}

// 0x71020668e0 -- vtable dispatch via x8 at 0x438, store x10
u32 FUN_71020668e0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x438))(in_x8);
    return 0;
}

// 0x7102066c50 -- vtable dispatch via x8 at 0x468, store x10
u32 FUN_7102066c50(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x468))(in_x8);
    return 0;
}

// 0x71020671d0 -- vtable dispatch via x8 at 0x4c0, store x10
u32 FUN_71020671d0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x4c0))(in_x8);
    return 0;
}

// 0x7102067340 -- vtable dispatch via x8 at 0x4f8, store x10
u32 FUN_7102067340(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x4f8))(in_x8);
    return 0;
}

// 0x71020677c0 -- vtable dispatch via x8 at 0x588, store x10
u32 FUN_71020677c0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x588))(in_x8);
    return 0;
}

// 0x7102067880 -- vtable dispatch via x8 at 0x590
u32 FUN_7102067880(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x590))(in_x8);
    return 0;
}

// 0x7102067b10 -- vtable dispatch via x8 at 0x5a0, store x10
u32 FUN_7102067b10(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x5a0))(in_x8);
    return 0;
}

// 0x7102067c80 -- vtable dispatch via x8 at 0x5b8, store x10
u32 FUN_7102067c80(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x5b8))(in_x8);
    return 0;
}

// 0x7102068230 -- vtable dispatch via x8 at 0x5d0, store x10
u32 FUN_7102068230(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x5d0))(in_x8);
    return 0;
}

// 0x71020683a0 -- vtable dispatch via x8 at 0x5e0, store x10
u32 FUN_71020683a0(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x5e0))(in_x8);
    return 0;
}

// 0x7102068510 -- vtable dispatch via x8 at 0x5f8, store x10
u32 FUN_7102068510(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x5f8))(in_x8);
    return 0;
}

// 0x710206a1b0 -- vtable dispatch via x8 at 0x90
u32 FUN_710206a1b0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x90))(in_x8);
    return 0;
}

// 0x710206a338 -- vtable dispatch via x8 at 0x98, store x10
u32 FUN_710206a338(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x98))(in_x8);
    return 0;
}

// 0x710206a490 -- vtable dispatch via x8 at 0xa0, store x10
u32 FUN_710206a490(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xa0))(in_x8);
    return 0;
}

// 0x710206a600 -- vtable dispatch via x8 at 0xa8, store x10
u32 FUN_710206a600(s64 *out, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)out + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xa8))(in_x8);
    return 0;
}
