// MEDIUM framed_vtable_call batch 008 (0x7102162a00 – 0x710218dcd0)
// FighterSpecializer/WeaponSpecializer named calls, x9 vtable variants

#include <stdint.h>
typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t  u8;
typedef int32_t  s32;
typedef int64_t  s64;

namespace app {
struct Fighter;
struct Weapon;
struct BattleObjectModuleAccessor;
struct FighterModuleAccessor;
namespace FighterSnakeFinalModule {
void lock_on_ready(BattleObjectModuleAccessor *);
void lock_on(BattleObjectModuleAccessor *);
}
namespace WeaponSpecializer_SnakeC4 {
void detach_constraint(Weapon *, bool);
}
namespace FighterSpecializer_Metaknight {
void set_special_n_ground_effect(Fighter *);
void check_edge_special_lw(FighterModuleAccessor *);
}
namespace FighterSpecializer_Pit {
void request_cut_in_chariotsight(Fighter *);
}
namespace FighterSpecializer_SZerosuit {
void start_final_szerosuit(Fighter *);
void start_final_szerosuit_camera(Fighter *);
void exec_final_szerosuit_camera(Fighter *);
void end_final_szerosuit(Fighter *);
}
namespace FighterSpecializer_Pikmin {
void reduce_pikmin_all(FighterModuleAccessor *);
void reduce_pikmin_all_change_top_pikmin(FighterModuleAccessor *);
void liberty_pikmin_all(FighterModuleAccessor *);
}
namespace FighterSpecializer_Dedede {
void end_special_n_shot_object_hit(Fighter *);
}
namespace FighterSpecializer_Lucario {
void req_aura_effect_both(Fighter *);
void effect_suspend(BattleObjectModuleAccessor *);
void effect_resume(BattleObjectModuleAccessor *);
}
namespace WeaponSpecializer_LucarioAuraball {
void set_scale(BattleObjectModuleAccessor *);
}
namespace WeaponSpecializer_RobotNarrowbeam {
void calc_pos(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Sonic {
void start_final_sonic(Fighter *);
void start_final_sonic_camera(Fighter *);
void end_final_sonic(Fighter *);
}
namespace FighterSpecializer_Purin {
void special_n_set_power(BattleObjectModuleAccessor *);
void special_n_req_effect_dash_smoke(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Palutena {
void init_final_settings(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Reflet {
void exit_special_n_tron_hold(FighterModuleAccessor *);
void special_lw_heal_damage(FighterModuleAccessor *);
void send_final_attack_event(FighterModuleAccessor *);
}
namespace FighterSpecializer_Gekkouga {
void set_special_s_transition_term_forbid_group(FighterModuleAccessor *, bool);
}
namespace WeaponSpecializer_GekkougaGekkougaS {
void set_link_final_end(BattleObjectModuleAccessor *, bool);
void update_moon_position(BattleObjectModuleAccessor *);
void raise_moon_position(BattleObjectModuleAccessor *);
}
}
extern "C" void FUN_71034bcc80(u64, int, int);
extern u8 DAT_71052c10d0[];

// 0x7102162a00 -- FighterSnakeFinalModule::lock_on_ready
u32 FUN_7102162a00(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::lock_on_ready(param_1); return 0; }

// 0x7102162ac0 -- FighterSnakeFinalModule::lock_on
u32 FUN_7102162ac0(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::lock_on(param_1); return 0; }

// 0x7102163c70 -- WeaponSpecializer_SnakeC4::detach_constraint
u32 FUN_7102163c70(app::Weapon *param_1, s64 param_2, bool param_3)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_SnakeC4::detach_constraint(param_1, param_3);
    return 0;
}

// 0x7102167070 -- FighterSpecializer_Metaknight::set_special_n_ground_effect
u32 FUN_7102167070(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Metaknight::set_special_n_ground_effect(param_1); return 0; }

// 0x7102167130 -- FighterSpecializer_Metaknight::check_edge_special_lw
u32 FUN_7102167130(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Metaknight::check_edge_special_lw(param_1); return 0; }

// 0x71021673b0 -- FighterSpecializer_Pit::request_cut_in_chariotsight
u32 FUN_71021673b0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pit::request_cut_in_chariotsight(param_1); return 0; }

// 0x7102168ec0 -- FighterSpecializer_SZerosuit::start_final_szerosuit
u32 FUN_7102168ec0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::start_final_szerosuit(param_1); return 0; }

// 0x7102168f80
u32 FUN_7102168f80(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::start_final_szerosuit_camera(param_1); return 0; }

// 0x7102169040
u32 FUN_7102169040(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::exec_final_szerosuit_camera(param_1); return 0; }

// 0x7102169100
u32 FUN_7102169100(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::end_final_szerosuit(param_1); return 0; }

// 0x710216adb0 -- FighterSpecializer_Pikmin::reduce_pikmin_all
u32 FUN_710216adb0(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::reduce_pikmin_all(param_1); return 0; }

// 0x710216ae70
u32 FUN_710216ae70(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::reduce_pikmin_all_change_top_pikmin(param_1); return 0; }

// 0x710216af30 -- ctor_dtor_small: x9 vtable +0xb0/8 -> FUN_71034bcc80
u32 FUN_710216af30(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    u64 uVar1 = (**(u64 (**)(s64 *, u32))(**(s64 **)(in_x9 + 0x50) + 0xb0))(
        *(s64 **)(in_x9 + 0x50), 0x100000c0u);
    FUN_71034bcc80(uVar1, 0, 0);
    return 0;
}

// 0x710216b1a0 -- FighterSpecializer_Pikmin::liberty_pikmin_all
u32 FUN_710216b1a0(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::liberty_pikmin_all(param_1); return 0; }

// 0x7102177a40 -- FighterSpecializer_Dedede::end_special_n_shot_object_hit
u32 FUN_7102177a40(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Dedede::end_special_n_shot_object_hit(param_1); return 0; }

// 0x710217b270 -- FighterSpecializer_Lucario::req_aura_effect_both
u32 FUN_710217b270(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Lucario::req_aura_effect_both(param_1); return 0; }

// 0x710217b330
u32 FUN_710217b330(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Lucario::effect_suspend(param_1); return 0; }

// 0x710217b3f0
u32 FUN_710217b3f0(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Lucario::effect_resume(param_1); return 0; }

// 0x710217b524 -- x9: vtable +0x130 call with 3 args
u32 FUN_710217b524(s64 param_1, u64 param_2)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *, u64, u32))(**(s64 **)(in_x9 + 0x50) + 0x130))(
        *(s64 **)(in_x9 + 0x50), param_2, 0x200000e2u);
    return 0;
}

// 0x710217b900 -- WeaponSpecializer_LucarioAuraball::set_scale
u32 FUN_710217b900(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LucarioAuraball::set_scale(param_1); return 0; }

// 0x710217c470 -- WeaponSpecializer_RobotNarrowbeam::calc_pos
u32 FUN_710217c470(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_RobotNarrowbeam::calc_pos(param_1); return 0; }

// 0x710217fe10 -- FighterSpecializer_Sonic
u32 FUN_710217fe10(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::start_final_sonic(param_1); return 0; }

// 0x710217fed0
u32 FUN_710217fed0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::start_final_sonic_camera(param_1); return 0; }

// 0x710217ff90
u32 FUN_710217ff90(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::end_final_sonic(param_1); return 0; }

// 0x7102182090 -- FighterSpecializer_Purin::special_n_set_power
u32 FUN_7102182090(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_set_power(param_1); return 0; }

// 0x7102182150 -- ctor_dtor_small: x9 vtable +0x98, conditional DAT_71052c10d0 clear
u32 FUN_7102182150(s64 param_1)
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

// 0x7102182240 -- FighterSpecializer_Purin::special_n_req_effect_dash_smoke
u32 FUN_7102182240(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_req_effect_dash_smoke(param_1); return 0; }

// 0x7102189d70 -- FighterSpecializer_Palutena::init_final_settings
u32 FUN_7102189d70(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Palutena::init_final_settings(param_1); return 0; }

// 0x710218a2c0 -- FighterSpecializer_Reflet::exit_special_n_tron_hold
u32 FUN_710218a2c0(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Reflet::exit_special_n_tron_hold(param_1); return 0; }

// 0x710218a920 -- FighterSpecializer_Reflet::special_lw_heal_damage
u32 FUN_710218a920(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Reflet::special_lw_heal_damage(param_1); return 0; }

// 0x710218ab20 -- FighterSpecializer_Reflet::send_final_attack_event
u32 FUN_710218ab20(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Reflet::send_final_attack_event(param_1); return 0; }

// 0x710218d844 -- FighterSpecializer_Gekkouga::set_special_s_transition_term_forbid_group
u32 FUN_710218d844(app::FighterModuleAccessor *param_1, s64 param_2, bool param_3)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Gekkouga::set_special_s_transition_term_forbid_group(param_1, param_3);
    return 0;
}

// 0x710218db34 -- WeaponSpecializer_GekkougaGekkougaS::set_link_final_end
u32 FUN_710218db34(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::set_link_final_end(param_1, param_3);
    return 0;
}

// 0x710218dc10 -- WeaponSpecializer_GekkougaGekkougaS::update_moon_position
u32 FUN_710218dc10(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::update_moon_position(param_1); return 0; }

// 0x710218dcd0 -- WeaponSpecializer_GekkougaGekkougaS::raise_moon_position
u32 FUN_710218dcd0(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::raise_moon_position(param_1); return 0; }
