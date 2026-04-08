// MEDIUM framed_vtable_call batch 008 (0x7102162a00 – 0x710218dcd0)
// FighterSpecializer/WeaponSpecializer named calls, x9 vtable variants
//
// Calling convention: x0 = context frame, x8 = object pointer, x10 = saved value

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
__attribute__((visibility("hidden"))) void lock_on_ready(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void lock_on(BattleObjectModuleAccessor *);
}
namespace WeaponSpecializer_SnakeC4 {
__attribute__((visibility("hidden"))) void detach_constraint(Weapon *, u32);
}
namespace FighterSpecializer_Metaknight {
__attribute__((visibility("hidden"))) void set_special_n_ground_effect(Fighter *);
__attribute__((visibility("hidden"))) void check_edge_special_lw(FighterModuleAccessor *);
}
namespace FighterSpecializer_Pit {
__attribute__((visibility("hidden"))) void request_cut_in_chariotsight(Fighter *);
}
namespace FighterSpecializer_SZerosuit {
__attribute__((visibility("hidden"))) void start_final_szerosuit(Fighter *);
__attribute__((visibility("hidden"))) void start_final_szerosuit_camera(Fighter *);
__attribute__((visibility("hidden"))) void exec_final_szerosuit_camera(Fighter *);
__attribute__((visibility("hidden"))) void end_final_szerosuit(Fighter *);
}
namespace FighterSpecializer_Pikmin {
__attribute__((visibility("hidden"))) void reduce_pikmin_all(FighterModuleAccessor *);
__attribute__((visibility("hidden"))) void reduce_pikmin_all_change_top_pikmin(FighterModuleAccessor *);
__attribute__((visibility("hidden"))) void liberty_pikmin_all(FighterModuleAccessor *);
}
namespace FighterSpecializer_Dedede {
__attribute__((visibility("hidden"))) void end_special_n_shot_object_hit(Fighter *);
}
namespace FighterSpecializer_Lucario {
__attribute__((visibility("hidden"))) void req_aura_effect_both(Fighter *);
__attribute__((visibility("hidden"))) void effect_suspend(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void effect_resume(BattleObjectModuleAccessor *);
}
namespace WeaponSpecializer_LucarioAuraball {
__attribute__((visibility("hidden"))) void set_scale(BattleObjectModuleAccessor *);
}
namespace WeaponSpecializer_RobotNarrowbeam {
__attribute__((visibility("hidden"))) void calc_pos(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Sonic {
__attribute__((visibility("hidden"))) void start_final_sonic(Fighter *);
__attribute__((visibility("hidden"))) void start_final_sonic_camera(Fighter *);
__attribute__((visibility("hidden"))) void end_final_sonic(Fighter *);
}
namespace FighterSpecializer_Purin {
__attribute__((visibility("hidden"))) void special_n_set_power(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void special_n_req_effect_dash_smoke(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Palutena {
__attribute__((visibility("hidden"))) void init_final_settings(BattleObjectModuleAccessor *);
}
namespace FighterSpecializer_Reflet {
__attribute__((visibility("hidden"))) void exit_special_n_tron_hold(FighterModuleAccessor *);
__attribute__((visibility("hidden"))) void special_lw_heal_damage(FighterModuleAccessor *);
__attribute__((visibility("hidden"))) void send_final_attack_event(FighterModuleAccessor *);
}
namespace FighterSpecializer_Gekkouga {
__attribute__((visibility("hidden"))) void set_special_s_transition_term_forbid_group(FighterModuleAccessor *, u32);
}
namespace WeaponSpecializer_GekkougaGekkougaS {
__attribute__((visibility("hidden"))) void set_link_final_end(BattleObjectModuleAccessor *, u32);
__attribute__((visibility("hidden"))) void update_moon_position(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void raise_moon_position(BattleObjectModuleAccessor *);
}
}
__attribute__((visibility("hidden"))) extern "C" void FUN_71034bcc80(u64, int, int);
__attribute__((visibility("hidden"))) extern u8 DAT_71052c10d0[];

// Framed vtable call: x0=context, x8=object, x10=value to save
#define FRAMED_VTCALL(addr, ObjType, call_expr)                              \
u32 FUN_##addr(s64 param_1) {                                                \
    register u64 in_x10 asm("x10");                                          \
    register ObjType *in_x8 asm("x8");                                       \
    asm volatile("" : "+r"(in_x10), "+r"(in_x8));                           \
    *(u64 *)(param_1 + 0x10) = in_x10;                                      \
    call_expr;                                                                \
    return 0;                                                                 \
}

// FighterSnakeFinalModule
FRAMED_VTCALL(7102162a00, app::BattleObjectModuleAccessor, app::FighterSnakeFinalModule::lock_on_ready(in_x8))
FRAMED_VTCALL(7102162ac0, app::BattleObjectModuleAccessor, app::FighterSnakeFinalModule::lock_on(in_x8))

// WeaponSpecializer_SnakeC4::detach_constraint (extra u32 param in w1)
u32 FUN_7102163c70(s64 param_1, u32 param_2) {
    register u64 in_x10 asm("x10");
    register app::Weapon *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x10), "+r"(in_x8));
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_SnakeC4::detach_constraint(in_x8, param_2);
    return 0;
}

// FighterSpecializer_Metaknight
FRAMED_VTCALL(7102167070, app::Fighter, app::FighterSpecializer_Metaknight::set_special_n_ground_effect(in_x8))
FRAMED_VTCALL(7102167130, app::FighterModuleAccessor, app::FighterSpecializer_Metaknight::check_edge_special_lw(in_x8))

// FighterSpecializer_Pit
FRAMED_VTCALL(71021673b0, app::Fighter, app::FighterSpecializer_Pit::request_cut_in_chariotsight(in_x8))

// FighterSpecializer_SZerosuit
FRAMED_VTCALL(7102168ec0, app::Fighter, app::FighterSpecializer_SZerosuit::start_final_szerosuit(in_x8))
FRAMED_VTCALL(7102168f80, app::Fighter, app::FighterSpecializer_SZerosuit::start_final_szerosuit_camera(in_x8))
FRAMED_VTCALL(7102169040, app::Fighter, app::FighterSpecializer_SZerosuit::exec_final_szerosuit_camera(in_x8))
FRAMED_VTCALL(7102169100, app::Fighter, app::FighterSpecializer_SZerosuit::end_final_szerosuit(in_x8))

// FighterSpecializer_Pikmin
FRAMED_VTCALL(710216adb0, app::FighterModuleAccessor, app::FighterSpecializer_Pikmin::reduce_pikmin_all(in_x8))
FRAMED_VTCALL(710216ae70, app::FighterModuleAccessor, app::FighterSpecializer_Pikmin::reduce_pikmin_all_change_top_pikmin(in_x8))

// 0x710216af30 -- x9 vtable +0xb0/8 -> FUN_71034bcc80
u32 FUN_710216af30(s64 param_1) {
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    u64 uVar1 = (**(u64 (**)(s64 *, u32))(**(s64 **)(in_x9 + 0x50) + 0xb0))(
        *(s64 **)(in_x9 + 0x50), 0x100000c0u);
    FUN_71034bcc80(uVar1, 0, 0);
    return 0;
}

FRAMED_VTCALL(710216b1a0, app::FighterModuleAccessor, app::FighterSpecializer_Pikmin::liberty_pikmin_all(in_x8))

// FighterSpecializer_Dedede
FRAMED_VTCALL(7102177a40, app::Fighter, app::FighterSpecializer_Dedede::end_special_n_shot_object_hit(in_x8))

// FighterSpecializer_Lucario
FRAMED_VTCALL(710217b270, app::Fighter, app::FighterSpecializer_Lucario::req_aura_effect_both(in_x8))
FRAMED_VTCALL(710217b330, app::BattleObjectModuleAccessor, app::FighterSpecializer_Lucario::effect_suspend(in_x8))
FRAMED_VTCALL(710217b3f0, app::BattleObjectModuleAccessor, app::FighterSpecializer_Lucario::effect_resume(in_x8))

// 0x710217b524 -- x9 vtable +0x130 call with 3 args
u32 FUN_710217b524(s64 param_1, u64 param_2) {
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    (**(void (**)(s64 *, u64, u32))(**(s64 **)(in_x9 + 0x50) + 0x130))(
        *(s64 **)(in_x9 + 0x50), param_2, 0x200000e2u);
    return 0;
}

// WeaponSpecializer_LucarioAuraball
FRAMED_VTCALL(710217b900, app::BattleObjectModuleAccessor, app::WeaponSpecializer_LucarioAuraball::set_scale(in_x8))

// WeaponSpecializer_RobotNarrowbeam
FRAMED_VTCALL(710217c470, app::BattleObjectModuleAccessor, app::WeaponSpecializer_RobotNarrowbeam::calc_pos(in_x8))

// FighterSpecializer_Sonic
FRAMED_VTCALL(710217fe10, app::Fighter, app::FighterSpecializer_Sonic::start_final_sonic(in_x8))
FRAMED_VTCALL(710217fed0, app::Fighter, app::FighterSpecializer_Sonic::start_final_sonic_camera(in_x8))
FRAMED_VTCALL(710217ff90, app::Fighter, app::FighterSpecializer_Sonic::end_final_sonic(in_x8))

// FighterSpecializer_Purin
FRAMED_VTCALL(7102182090, app::BattleObjectModuleAccessor, app::FighterSpecializer_Purin::special_n_set_power(in_x8))

// 0x7102182150 -- x9 vtable +0x98, conditional DAT_71052c10d0 clear
u32 FUN_7102182150(s64 param_1) {
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s32 iVar1 = (**(s32 (**)(s64 *, s32))(**(s64 **)(in_x9 + 0x50) + 0x98))(
        *(s64 **)(in_x9 + 0x50), 0x10000000);
    if (iVar1 < 8) {
        DAT_71052c10d0[(s64)iVar1 * 0x110] = 0;
    }
    return 0;
}

FRAMED_VTCALL(7102182240, app::BattleObjectModuleAccessor, app::FighterSpecializer_Purin::special_n_req_effect_dash_smoke(in_x8))

// FighterSpecializer_Palutena
FRAMED_VTCALL(7102189d70, app::BattleObjectModuleAccessor, app::FighterSpecializer_Palutena::init_final_settings(in_x8))

// FighterSpecializer_Reflet
FRAMED_VTCALL(710218a2c0, app::FighterModuleAccessor, app::FighterSpecializer_Reflet::exit_special_n_tron_hold(in_x8))
FRAMED_VTCALL(710218a920, app::FighterModuleAccessor, app::FighterSpecializer_Reflet::special_lw_heal_damage(in_x8))
FRAMED_VTCALL(710218ab20, app::FighterModuleAccessor, app::FighterSpecializer_Reflet::send_final_attack_event(in_x8))

// FighterSpecializer_Gekkouga (extra u32 param in w1)
u32 FUN_710218d844(s64 param_1, u32 param_2) {
    register u64 in_x10 asm("x10");
    register app::FighterModuleAccessor *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x10), "+r"(in_x8));
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Gekkouga::set_special_s_transition_term_forbid_group(in_x8, param_2);
    return 0;
}

// WeaponSpecializer_GekkougaGekkougaS (extra u32 param in w1)
u32 FUN_710218db34(s64 param_1, u32 param_2) {
    register u64 in_x10 asm("x10");
    register app::BattleObjectModuleAccessor *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x10), "+r"(in_x8));
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::set_link_final_end(in_x8, param_2);
    return 0;
}

FRAMED_VTCALL(710218dc10, app::BattleObjectModuleAccessor, app::WeaponSpecializer_GekkougaGekkougaS::update_moon_position(in_x8))
FRAMED_VTCALL(710218dcd0, app::BattleObjectModuleAccessor, app::WeaponSpecializer_GekkougaGekkougaS::raise_moon_position(in_x8))
