#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-009
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

struct BattleObjectModuleAccessor;
struct Fighter;

extern "C" void FUN_71026084c0(u64);

namespace app {
    namespace FighterSpecializer_Rockman {
        void set_leafshield(BattleObjectModuleAccessor *, s64);
    }
    namespace WeaponSpecializer_ShizueFishingrod {
        void enable_search(BattleObjectModuleAccessor *, s64);
    }
    namespace FighterSpecializer_Brave {
        void special_lw_close_window(Fighter *, s64, s64, s64);
    }
}

// ---- lua_bind wrappers -----------------------------------------------

// 0x71021456d4 — ldr x0,[x8]; bl FUN_71026084c0; store x10 (32 bytes)
// x8 is dereferenced to get the argument (not passed directly)
u32 FUN_71021456d4(s64 *param_1, s64 param_2)
{
    register u64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    FUN_71026084c0(*in_x8);
    return 0;
}

// 0x7102192724 — FighterSpecializer_Rockman::set_leafshield (32 bytes)
// param_2 (x1) = bool arg passed through as s64 to avoid and-normalization
u32 FUN_7102192724(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Rockman::set_leafshield(in_x8, param_2);
    return 0;
}

// 0x71021a2fa4 — WeaponSpecializer_ShizueFishingrod::enable_search (32 bytes)
u32 FUN_71021a2fa4(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_ShizueFishingrod::enable_search(in_x8, param_2);
    return 0;
}

// 0x71021b67b0 — FighterSpecializer_Brave::special_lw_close_window (32 bytes)
// 3 bool args (x1,x2,x3) passed as s64 to avoid and-normalization
u32 FUN_71021b67b0(s64 *param_1, s64 param_2, s64 param_3, s64 param_4)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_close_window(in_x8, param_2, param_3, param_4);
    return 0;
}

// ---- ctor_dtor_small: WorkModule flag setters -----------------------------------------------
// Pattern: plVar1=*(*(*(param_1-8)+0x1a0)+0x68); lVar2=vtable[0x60](plVar1,idx);
//          *(u8*)(lVar2+off)=val; return 0
// Access: param_1 (x0) is lua state, *(x0-8) navigates to WorkModule via +0x1a0/+0x68

// 0x7102208730 — WorkModule.get(0xc).flag[0x30]=0
u64 FUN_7102208730(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xc);
    *(u8 *)(lVar2 + 0x30) = 0;
    return 0;
}

// 0x7102208770 — WorkModule.get(0xd).flag[0x30]=0
u64 FUN_7102208770(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xd);
    *(u8 *)(lVar2 + 0x30) = 0;
    return 0;
}

// 0x7102208810 — WorkModule.get(0xc).flag[0x30]=1
u64 FUN_7102208810(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xc);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x7102208850 — WorkModule.get(0xd).flag[0x30]=1
u64 FUN_7102208850(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0xd);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x710221c620 — WorkModule.get(0).flag[0x30]=1
u64 FUN_710221c620(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x710221c700 — WorkModule.get(0).flag[0x31]=1
u64 FUN_710221c700(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 0);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x710221e780 — WorkModule.get(1).flag[0x30]=0
u64 FUN_710221e780(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 1);
    *(u8 *)(lVar2 + 0x30) = 0;
    return 0;
}

// 0x710221e860 — WorkModule.get(1).flag[0x31]=0
u64 FUN_710221e860(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 1);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x71022208e0 — WorkModule.get(2).flag[0x30]=1
u64 FUN_71022208e0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 2);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x71022209c0 — WorkModule.get(2).flag[0x31]=1
u64 FUN_71022209c0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 2);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102220a00 — WorkModule.get(2).flag[0x31]=0
u64 FUN_7102220a00(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 2);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x71022220e0 — WorkModule.get(3).flag[0x30]=1
u64 FUN_71022220e0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 3);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}

// 0x71022221c0 — WorkModule.get(3).flag[0x31]=1
u64 FUN_71022221c0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 3);
    *(u8 *)(lVar2 + 0x31) = 1;
    return 0;
}

// 0x7102222200 — WorkModule.get(3).flag[0x31]=0
u64 FUN_7102222200(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 3);
    *(u8 *)(lVar2 + 0x31) = 0;
    return 0;
}

// 0x7102223ee0 — WorkModule.get(4).flag[0x30]=1
u64 FUN_7102223ee0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    s64 lVar2 = (**(s64 (**)(s64 *, s64))(*plVar1 + 0x60))(plVar1, 4);
    *(u8 *)(lVar2 + 0x30) = 1;
    return 0;
}
