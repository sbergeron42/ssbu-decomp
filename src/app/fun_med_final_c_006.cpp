// MEDIUM framed_vtable_call batch 006 (0x71020ad4e0 – 0x710214f750)
// Includes named FighterUtil/FighterSpecializer calls and x9-register patterns

#include <stdint.h>
typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t  s32;
typedef int64_t  s64;

// Forward declarations — named game functions
namespace app {
struct Fighter;
struct BattleObjectModuleAccessor;
namespace FighterUtil {
void init_big_small(BattleObjectModuleAccessor *);
void exec_big_small(BattleObjectModuleAccessor *);
void exit_big_small(BattleObjectModuleAccessor *);
void reset_hit_data(BattleObjectModuleAccessor *);
void clung_thrown_diddy_unlink_capture(BattleObjectModuleAccessor *);
void set_restart_up_position(BattleObjectModuleAccessor *);
void set_parent_external_stat_bank_handle(BattleObjectModuleAccessor *);
void flash_eye_info(BattleObjectModuleAccessor *);
void set_stage_pause_for_final(bool, BattleObjectModuleAccessor *);
void jump_board_on(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Link {
void set_item_hold_anim_for_script(Fighter *);
}
namespace WeaponSpecializer_LinkBowarrow {
void to_item(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Kirby {
void inhale_object(Fighter *);
}
namespace FighterSpecializer_Purin {
void special_n_set_power(BattleObjectModuleAccessor *);
void special_n_req_effect_dash_smoke(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Fox {
void final_start_init(Fighter *);
void final_start_exit(Fighter *);
void final_ready_init(Fighter *);
}
}
extern "C" void FUN_71006eadc0(u64);
extern "C" void FUN_71006eafb0(u64);
extern "C" void FUN_7101610890(u64);
extern "C" void FUN_710260c800(u64);
extern "C" void FUN_71026084c0(u64);
extern "C" void FUN_710067f640(u64);
extern s64 *lib_Singleton_StageManager_instance_;
extern u8 DAT_71052c10d0[];

// 0x71020ad4e0 -- x9: vtable dispatch through *(x9+0x10)+8
u32 FUN_71020ad4e0(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s64 *obj = *(s64 **)(*(s64 *)(in_x9 + 0x10) + 8);
    (**(void (**)(void))(*obj + 0xa0))();
    return 0;
}

// 0x71020c04f0 -- FighterUtil::init_big_small
u32 FUN_71020c04f0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::init_big_small(param_1);
    return 0;
}

// 0x71020c05b0 -- FighterUtil::exec_big_small
u32 FUN_71020c05b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::exec_big_small(param_1);
    return 0;
}

// 0x71020c0670 -- FighterUtil::exit_big_small
u32 FUN_71020c0670(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::exit_big_small(param_1);
    return 0;
}

// 0x71020c0d90 -- FighterUtil::reset_hit_data
u32 FUN_71020c0d90(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::reset_hit_data(param_1);
    return 0;
}

// 0x71020c11b0 -- FighterUtil::clung_thrown_diddy_unlink_capture
u32 FUN_71020c11b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::clung_thrown_diddy_unlink_capture(param_1);
    return 0;
}

// 0x71020c13b0 -- FighterUtil::set_restart_up_position
u32 FUN_71020c13b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::set_restart_up_position(param_1);
    return 0;
}

// 0x71020c1690 -- FighterUtil::set_parent_external_stat_bank_handle
u32 FUN_71020c1690(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::set_parent_external_stat_bank_handle(param_1);
    return 0;
}

// 0x71020c3ba0 -- FighterUtil::flash_eye_info
u32 FUN_71020c3ba0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::flash_eye_info(param_1);
    return 0;
}

// 0x71020c4454 -- FighterUtil::set_stage_pause_for_final(w8 bool, param_2)
u32 FUN_71020c4454(s64 param_1, app::BattleObjectModuleAccessor *param_2)
{
    register s64 in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterUtil::set_stage_pause_for_final((bool)(int)in_x8, param_2);
    return 0;
}

// 0x71020c6598 -- ctor_dtor_small: StageManager vtable call, x9+w12
u32 FUN_71020c6598(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register int in_w12 asm("w12");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_w12));
    *(s64 *)(param_1 + 0x10) = in_x9;
    s64 lVar1 = *(s64 *)((u8 *)lib_Singleton_StageManager_instance_ + 0x128);
    void (*pcVar2)(void *);
    if (in_w12 == 0) {
        pcVar2 = *(void (**)(void *))(lVar1 + 0x1a8);
    } else {
        pcVar2 = *(void (**)(void *))(lVar1 + 0x1b0);
    }
    (*pcVar2)((u8 *)lib_Singleton_StageManager_instance_ + 0x128);
    return 0;
}

// 0x71020c6690 -- x9: FUN_71006eadc0(*(x9+0x148))
u32 FUN_71020c6690(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_71006eadc0(*(u64 *)(in_x9 + 0x148));
    return 0;
}

// 0x71020c6750 -- x9: FUN_71006eafb0(*(x9+0x148))
u32 FUN_71020c6750(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_71006eafb0(*(u64 *)(in_x9 + 0x148));
    return 0;
}

// 0x71020c6d60 -- FighterUtil::jump_board_on
u32 FUN_71020c6d60(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterUtil::jump_board_on(param_1);
    return 0;
}

// 0x71020c6e20 -- x9: vtable through *(x9+0x58), call with arg 0
u32 FUN_71020c6e20(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s64 *obj = *(s64 **)(in_x9 + 0x58);
    (**(void (**)(s64 *, int))(*obj + 0x808))(obj, 0);
    return 0;
}

// 0x71020c6ef0 -- x9: same vtable pattern, arg 1
u32 FUN_71020c6ef0(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s64 *obj = *(s64 **)(in_x9 + 0x58);
    (**(void (**)(s64 *, int))(*obj + 0x808))(obj, 1);
    return 0;
}

// 0x71020c6fc0 -- x9: same vtable pattern, arg 2
u32 FUN_71020c6fc0(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s64 *obj = *(s64 **)(in_x9 + 0x58);
    (**(void (**)(s64 *, int))(*obj + 0x808))(obj, 2);
    return 0;
}

// 0x71020d2620 -- forward to FUN_7101610890
u32 FUN_71020d2620(u64 param_1)
{
    FUN_7101610890(param_1);
    return 0;
}

// 0x71020f47d0 -- vtable +0x70
u32 FUN_71020f47d0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x70))(in_x8);
    return 0;
}

// 0x71020f7020 -- vtable +0x48
u32 FUN_71020f7020(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x48))(in_x8);
    return 0;
}

// 0x71020f70f0 -- vtable +0x50
u32 FUN_71020f70f0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x50))(in_x8);
    return 0;
}

// 0x71020f7dc0 -- vtable +0x78
u32 FUN_71020f7dc0(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x78))(in_x8);
    return 0;
}

// 0x71020f7e90 -- vtable +0x80
u32 FUN_71020f7e90(s64 *param_1, s64 param_2)
{
    register s64 *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *))(*in_x8 + 0x80))(in_x8);
    return 0;
}

// 0x7102143184 -- x9: FUN_710260c800(StageManager), stores x9
u32 FUN_7102143184(s64 param_1)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    *(s64 *)(param_1 + 0x10) = in_x9;
    FUN_710260c800((u64)*lib_Singleton_StageManager_instance_);
    return 0;
}

// 0x7102143d5c -- vtable through param_1+0xb80 (no x8)
u32 FUN_7102143d5c(s64 *param_1)
{
    FUN_710067f640(**(u64 **)((u8 *)*param_1 + 0xb80));
    return 0;
}

// 0x71021456d4 -- FUN_71026084c0(*param_1) with x10 store
u32 FUN_71021456d4(u64 *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_71026084c0(*param_1);
    return 0;
}

// 0x7102146620 -- FighterSpecializer_Link::set_item_hold_anim_for_script
u32 FUN_7102146620(app::Fighter *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Link::set_item_hold_anim_for_script(param_1);
    return 0;
}

// 0x7102146bd0 -- WeaponSpecializer_LinkBowarrow::to_item
u32 FUN_7102146bd0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LinkBowarrow::to_item(param_1);
    return 0;
}

// 0x7102149810 -- FighterSpecializer_Kirby::inhale_object
u32 FUN_7102149810(app::Fighter *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Kirby::inhale_object(param_1);
    return 0;
}

// 0x7102149e50 -- FighterSpecializer_Purin::special_n_set_power
u32 FUN_7102149e50(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_set_power(param_1);
    return 0;
}

// 0x7102149f10 -- ctor_dtor_small: x9 vtable call, conditional store to DAT array
u32 FUN_7102149f10(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s32 iVar1 = (**(s32 (**)(s64 *, s32))(**(s64 **)(in_x9 + 0x50) + 0x98))(
        *(s64 **)(in_x9 + 0x50), 0x10000000);
    if (iVar1 < 8) {
        DAT_71052c10d0[(s64)iVar1 * 0x110] = 0;
    }
    return 0;
}

// 0x710214a000 -- FighterSpecializer_Purin::special_n_req_effect_dash_smoke
u32 FUN_710214a000(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_req_effect_dash_smoke(param_1);
    return 0;
}

// 0x710214f5d0 -- FighterSpecializer_Fox::final_start_init
u32 FUN_710214f5d0(app::Fighter *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_start_init(param_1);
    return 0;
}

// 0x710214f690 -- FighterSpecializer_Fox::final_start_exit
u32 FUN_710214f690(app::Fighter *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_start_exit(param_1);
    return 0;
}

// 0x710214f750 -- FighterSpecializer_Fox::final_ready_init
u32 FUN_710214f750(app::Fighter *param_1, s64 param_2)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_ready_init(param_1);
    return 0;
}
