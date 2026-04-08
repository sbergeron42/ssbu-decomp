// MEDIUM framed_vtable_call batch 007 (0x710214f810 – 0x7102162700)
// Named FighterSpecializer / WeaponSpecializer / FighterSnakeFinalModule calls
//
// Calling convention: x0 = context frame, x8 = object pointer, x10 = saved value
// The function stores x10 at [x0+0x10], then dispatches x8 to the specializer.

#include <stdint.h>
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t  s64;

namespace app {
struct Fighter;
struct Weapon;
struct BattleObjectModuleAccessor;
struct FighterModuleAccessor;
namespace FighterSpecializer_Fox {
__attribute__((visibility("hidden"))) void final_ready_exec(Fighter *);
__attribute__((visibility("hidden"))) void final_ready_exit(Fighter *);
__attribute__((visibility("hidden"))) void final_scene01_init(Fighter *);
__attribute__((visibility("hidden"))) void final_scene01_exec_fix_pos(Fighter *);
__attribute__((visibility("hidden"))) void final_scene01_exit(Fighter *);
__attribute__((visibility("hidden"))) void final_end_init(Fighter *);
__attribute__((visibility("hidden"))) void final_end_exec(Fighter *);
__attribute__((visibility("hidden"))) void final_end_exit(Fighter *);
}
namespace FighterSpecializer_Luigi {
__attribute__((visibility("hidden"))) void delete_plunger(Fighter *, u32);
}
namespace WeaponSpecializer_LuigiPlunger {
__attribute__((visibility("hidden"))) void modify_physics_param(Weapon *);
__attribute__((visibility("hidden"))) void modify_physics_param_2nd(Weapon *);
}
namespace FighterSpecializer_Peach {
__attribute__((visibility("hidden"))) void special_lw_check_num_of_item(FighterModuleAccessor *);
__attribute__((visibility("hidden"))) void final_rand_create_item(FighterModuleAccessor *);
}
namespace FighterSpecializer_Popo {
__attribute__((visibility("hidden"))) void init_lr_special_s_partner(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void init_lr_special_hi_cliff_comp(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void change_status_special_s_partner(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void init_final_partner(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void start_partner_turn(Fighter *);
__attribute__((visibility("hidden"))) void start_final_popo(Fighter *);
__attribute__((visibility("hidden"))) void start_final_popo_camera(Fighter *);
__attribute__((visibility("hidden"))) void enable_partner_catch_transition(Fighter *);
__attribute__((visibility("hidden"))) void end_final_deactivated_iceberg(Fighter *);
}
namespace FighterSpecializer_Falco {
__attribute__((visibility("hidden"))) void final_start_init(Fighter *);
__attribute__((visibility("hidden"))) void final_start_exit(Fighter *);
__attribute__((visibility("hidden"))) void final_ready_init(Fighter *);
__attribute__((visibility("hidden"))) void final_ready_exec(Fighter *);
__attribute__((visibility("hidden"))) void final_ready_exit(Fighter *);
__attribute__((visibility("hidden"))) void final_scene01_init(Fighter *);
__attribute__((visibility("hidden"))) void final_scene01_exec_fix_pos(Fighter *);
__attribute__((visibility("hidden"))) void final_scene01_exit(Fighter *);
__attribute__((visibility("hidden"))) void final_end_init(Fighter *);
__attribute__((visibility("hidden"))) void final_end_exec(Fighter *);
__attribute__((visibility("hidden"))) void final_end_exit(Fighter *);
}
namespace FighterSnakeFinalModule {
__attribute__((visibility("hidden"))) void end_final(BattleObjectModuleAccessor *);
__attribute__((visibility("hidden"))) void initialize_reticle(BattleObjectModuleAccessor *);
}
}

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

// FighterSpecializer_Fox
FRAMED_VTCALL(710214f810, app::Fighter, app::FighterSpecializer_Fox::final_ready_exec(in_x8))
FRAMED_VTCALL(710214f950, app::Fighter, app::FighterSpecializer_Fox::final_ready_exit(in_x8))
FRAMED_VTCALL(710214fa10, app::Fighter, app::FighterSpecializer_Fox::final_scene01_init(in_x8))
FRAMED_VTCALL(710214fad0, app::Fighter, app::FighterSpecializer_Fox::final_scene01_exec_fix_pos(in_x8))
FRAMED_VTCALL(710214fb90, app::Fighter, app::FighterSpecializer_Fox::final_scene01_exit(in_x8))
FRAMED_VTCALL(710214fc50, app::Fighter, app::FighterSpecializer_Fox::final_end_init(in_x8))
FRAMED_VTCALL(710214fd10, app::Fighter, app::FighterSpecializer_Fox::final_end_exec(in_x8))
FRAMED_VTCALL(710214fdd0, app::Fighter, app::FighterSpecializer_Fox::final_end_exit(in_x8))

// FighterSpecializer_Luigi::delete_plunger (param in w1)
u32 FUN_7102153610(s64 param_1, u32 param_2) {
    register u64 in_x10 asm("x10");
    register app::Fighter *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x10), "+r"(in_x8));
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Luigi::delete_plunger(in_x8, param_2);
    return 0;
}

// WeaponSpecializer_LuigiPlunger
FRAMED_VTCALL(71021536d0, app::Weapon, app::WeaponSpecializer_LuigiPlunger::modify_physics_param(in_x8))
FRAMED_VTCALL(7102153790, app::Weapon, app::WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd(in_x8))

// FighterSpecializer_Peach
FRAMED_VTCALL(7102157540, app::FighterModuleAccessor, app::FighterSpecializer_Peach::special_lw_check_num_of_item(in_x8))
FRAMED_VTCALL(7102157720, app::FighterModuleAccessor, app::FighterSpecializer_Peach::final_rand_create_item(in_x8))

// FighterSpecializer_Popo
FRAMED_VTCALL(7102157b90, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::init_lr_special_s_partner(in_x8))
FRAMED_VTCALL(7102157c50, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::init_lr_special_hi_cliff_comp(in_x8))
FRAMED_VTCALL(7102157d10, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::change_status_special_s_partner(in_x8))
FRAMED_VTCALL(7102157ee0, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::init_final_partner(in_x8))
FRAMED_VTCALL(71021580c0, app::Fighter, app::FighterSpecializer_Popo::start_partner_turn(in_x8))
FRAMED_VTCALL(7102158530, app::Fighter, app::FighterSpecializer_Popo::start_final_popo(in_x8))
FRAMED_VTCALL(71021585f0, app::Fighter, app::FighterSpecializer_Popo::start_final_popo_camera(in_x8))
FRAMED_VTCALL(71021587a0, app::Fighter, app::FighterSpecializer_Popo::enable_partner_catch_transition(in_x8))
FRAMED_VTCALL(7102158860, app::Fighter, app::FighterSpecializer_Popo::end_final_deactivated_iceberg(in_x8))

// FighterSpecializer_Falco
FRAMED_VTCALL(710215db90, app::Fighter, app::FighterSpecializer_Falco::final_start_init(in_x8))
FRAMED_VTCALL(710215dc50, app::Fighter, app::FighterSpecializer_Falco::final_start_exit(in_x8))
FRAMED_VTCALL(710215dd10, app::Fighter, app::FighterSpecializer_Falco::final_ready_init(in_x8))
FRAMED_VTCALL(710215ddd0, app::Fighter, app::FighterSpecializer_Falco::final_ready_exec(in_x8))
FRAMED_VTCALL(710215df10, app::Fighter, app::FighterSpecializer_Falco::final_ready_exit(in_x8))
FRAMED_VTCALL(710215dfd0, app::Fighter, app::FighterSpecializer_Falco::final_scene01_init(in_x8))
FRAMED_VTCALL(710215e090, app::Fighter, app::FighterSpecializer_Falco::final_scene01_exec_fix_pos(in_x8))
FRAMED_VTCALL(710215e150, app::Fighter, app::FighterSpecializer_Falco::final_scene01_exit(in_x8))
FRAMED_VTCALL(710215e210, app::Fighter, app::FighterSpecializer_Falco::final_end_init(in_x8))
FRAMED_VTCALL(710215e2d0, app::Fighter, app::FighterSpecializer_Falco::final_end_exec(in_x8))
FRAMED_VTCALL(710215e390, app::Fighter, app::FighterSpecializer_Falco::final_end_exit(in_x8))

// FighterSnakeFinalModule
FRAMED_VTCALL(7102162550, app::BattleObjectModuleAccessor, app::FighterSnakeFinalModule::end_final(in_x8))
FRAMED_VTCALL(7102162700, app::BattleObjectModuleAccessor, app::FighterSnakeFinalModule::initialize_reticle(in_x8))
