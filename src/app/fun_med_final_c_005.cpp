// MEDIUM framed_vtable_call batch 005 (0x710208d900 – 0x71020bf9d0)

#include <stdint.h>
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t  s64;

// forward declarations for named calls
namespace app {
struct BattleObjectModuleAccessor;
namespace FighterUtil {
void adjust_butterflynet(BattleObjectModuleAccessor *);
void end_butterflynet(BattleObjectModuleAccessor *);
void adjust_bitten_wario(BattleObjectModuleAccessor *);
}
}
extern "C" void FUN_71006ab9d0(u64);
extern "C" void FUN_71006be630(u64);

// 0x710208d900
u32 FUN_710208d900(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x118))(in_x8);
    return 0;
}

// 0x7102090ff0
u32 FUN_7102090ff0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x198))(in_x8);
    return 0;
}

// 0x71020916b0
u32 FUN_71020916b0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x1c8))(in_x8);
    return 0;
}

// 0x7102091c20
u32 FUN_7102091c20(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x218))(in_x8);
    return 0;
}

// 0x71020929d0
u32 FUN_71020929d0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x7102092a80
u32 FUN_7102092a80(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x68))(in_x8);
    return 0;
}

// 0x7102099f00
u32 FUN_7102099f00(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0xb8))(in_x8);
    return 0;
}

// 0x710209b1e0
u32 FUN_710209b1e0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x150))(in_x8);
    return 0;
}

// 0x710209f2f0
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

// 0x710209fee8
u32 FUN_710209fee8(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x60))(in_x8);
    return 0;
}

// 0x710209ff90
u32 FUN_710209ff90(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x88))(in_x8);
    return 0;
}

// 0x71020a04c0
u32 FUN_71020a04c0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xc8))(in_x8);
    return 0;
}

// 0x71020a0800
u32 FUN_71020a0800(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0xf8))(in_x8);
    return 0;
}

// 0x71020a1ae0
u32 FUN_71020a1ae0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x180))(in_x8);
    return 0;
}

// 0x71020a1d20
u32 FUN_71020a1d20(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x198))(in_x8);
    return 0;
}

// 0x71020a2e00
u32 FUN_71020a2e00(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x200))(in_x8);
    return 0;
}

// 0x71020a5c40
u32 FUN_71020a5c40(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x2e8))(in_x8);
    return 0;
}

// 0x71020a5da0
u32 FUN_71020a5da0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x2f0))(in_x8);
    return 0;
}

// 0x71020a5f10
u32 FUN_71020a5f10(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x300))(in_x8);
    return 0;
}

// 0x71020a7008
u32 FUN_71020a7008(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x3a8))(in_x8);
    return 0;
}

// 0x71020a7160
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

// 0x71020a79e0
u32 FUN_71020a79e0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (**(void (**)(s64 *))(*in_x8 + 0x70))(in_x8);
    return 0;
}

// 0x71020a8f1c -- calls FUN_71006ab9d0 with value at *param_1
u32 FUN_71020a8f1c(u64 *param_1)
{
    FUN_71006ab9d0(*param_1);
    return 0;
}

// 0x71020adef0
u32 FUN_71020adef0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x280))(in_x8);
    return 0;
}

// 0x71020af048 -- calls FUN_71006be630 with param_1 (x0), stores x10 to param_2+0x10
u32 FUN_71020af048(u64 param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_71006be630(param_1);
    return 0;
}

// 0x71020afd68
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

// 0x71020bf850 -- FighterUtil::adjust_butterflynet
u32 FUN_71020bf850(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::adjust_butterflynet(param_1);
    return 0;
}

// 0x71020bf910 -- FighterUtil::end_butterflynet
u32 FUN_71020bf910(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::end_butterflynet(param_1);
    return 0;
}

// 0x71020bf9d0 -- FighterUtil::adjust_bitten_wario
u32 FUN_71020bf9d0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::adjust_bitten_wario(param_1);
    return 0;
}
