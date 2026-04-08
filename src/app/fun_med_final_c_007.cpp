// MEDIUM framed_vtable_call batch 007 (0x710214f810 – 0x7102162700)
// Named FighterSpecializer / WeaponSpecializer / FighterSnakeFinalModule calls
//
// lua_bind calling convention:
//   x8 = object pointer (Fighter*, Weapon*, etc.)
//   x0 = param_2 (s64, typically a lua state pointer)
//   x10 = value to store at param_2+0x10
//   Additional args (bool, etc.) in x1, x2, ...

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
void final_ready_exec(Fighter *);
void final_ready_exit(Fighter *);
void final_scene01_init(Fighter *);
void final_scene01_exec_fix_pos(Fighter *);
void final_scene01_exit(Fighter *);
void final_end_init(Fighter *);
void final_end_exec(Fighter *);
void final_end_exit(Fighter *);
}
namespace FighterSpecializer_Luigi {
void delete_plunger(Fighter *, u32);
}
namespace WeaponSpecializer_LuigiPlunger {
void modify_physics_param(Weapon *);
void modify_physics_param_2nd(Weapon *);
}
namespace FighterSpecializer_Peach {
void special_lw_check_num_of_item(FighterModuleAccessor *);
void final_rand_create_item(FighterModuleAccessor *);
}
namespace FighterSpecializer_Popo {
void init_lr_special_s_partner(BattleObjectModuleAccessor *);
void init_lr_special_hi_cliff_comp(BattleObjectModuleAccessor *);
void change_status_special_s_partner(BattleObjectModuleAccessor *);
void init_final_partner(BattleObjectModuleAccessor *);
void start_partner_turn(Fighter *);
void start_final_popo(Fighter *);
void start_final_popo_camera(Fighter *);
void enable_partner_catch_transition(Fighter *);
void end_final_deactivated_iceberg(Fighter *);
}
namespace FighterSpecializer_Falco {
void final_start_init(Fighter *);
void final_start_exit(Fighter *);
void final_ready_init(Fighter *);
void final_ready_exec(Fighter *);
void final_ready_exit(Fighter *);
void final_scene01_init(Fighter *);
void final_scene01_exec_fix_pos(Fighter *);
void final_scene01_exit(Fighter *);
void final_end_init(Fighter *);
void final_end_exec(Fighter *);
void final_end_exit(Fighter *);
}
namespace FighterSnakeFinalModule {
void end_final(BattleObjectModuleAccessor *);
void initialize_reticle(BattleObjectModuleAccessor *);
}
}

// lua_bind wrapper: object in x8, param_2 in x0, in_x10 in x10
#define LUA_BIND_WRAP(fn_name, ObjType, call_expr) \
u32 fn_name(s64 param_2) { \
    register ObjType* obj asm("x8"); \
    asm volatile("" : "+r"(obj)); \
    register u64 in_x10 asm("x10"); \
    asm volatile("" : "+r"(in_x10)); \
    *(u64 *)(param_2 + 0x10) = in_x10; \
    call_expr; \
    return 0; \
}

// 0x710214f810 -- FighterSpecializer_Fox::final_ready_exec
LUA_BIND_WRAP(FUN_710214f810, app::Fighter, app::FighterSpecializer_Fox::final_ready_exec(obj))

// 0x710214f950
LUA_BIND_WRAP(FUN_710214f950, app::Fighter, app::FighterSpecializer_Fox::final_ready_exit(obj))

// 0x710214fa10
LUA_BIND_WRAP(FUN_710214fa10, app::Fighter, app::FighterSpecializer_Fox::final_scene01_init(obj))

// 0x710214fad0
LUA_BIND_WRAP(FUN_710214fad0, app::Fighter, app::FighterSpecializer_Fox::final_scene01_exec_fix_pos(obj))

// 0x710214fb90
LUA_BIND_WRAP(FUN_710214fb90, app::Fighter, app::FighterSpecializer_Fox::final_scene01_exit(obj))

// 0x710214fc50
LUA_BIND_WRAP(FUN_710214fc50, app::Fighter, app::FighterSpecializer_Fox::final_end_init(obj))

// 0x710214fd10
LUA_BIND_WRAP(FUN_710214fd10, app::Fighter, app::FighterSpecializer_Fox::final_end_exec(obj))

// 0x710214fdd0
LUA_BIND_WRAP(FUN_710214fdd0, app::Fighter, app::FighterSpecializer_Fox::final_end_exit(obj))

// 0x7102153610 -- FighterSpecializer_Luigi::delete_plunger(Fighter*, bool)
u32 FUN_7102153610(s64 param_2, u32 param_3)
{
    register app::Fighter* obj asm("x8");
    asm volatile("" : "+r"(obj));
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Luigi::delete_plunger(obj, param_3);
    return 0;
}

// 0x71021536d0 -- WeaponSpecializer_LuigiPlunger::modify_physics_param
LUA_BIND_WRAP(FUN_71021536d0, app::Weapon, app::WeaponSpecializer_LuigiPlunger::modify_physics_param(obj))

// 0x7102153790 -- WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd
LUA_BIND_WRAP(FUN_7102153790, app::Weapon, app::WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd(obj))

// 0x7102157540 -- FighterSpecializer_Peach::special_lw_check_num_of_item
LUA_BIND_WRAP(FUN_7102157540, app::FighterModuleAccessor, app::FighterSpecializer_Peach::special_lw_check_num_of_item(obj))

// 0x7102157720 -- FighterSpecializer_Peach::final_rand_create_item
LUA_BIND_WRAP(FUN_7102157720, app::FighterModuleAccessor, app::FighterSpecializer_Peach::final_rand_create_item(obj))

// 0x7102157b90 -- FighterSpecializer_Popo::init_lr_special_s_partner
LUA_BIND_WRAP(FUN_7102157b90, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::init_lr_special_s_partner(obj))

// 0x7102157c50 -- FighterSpecializer_Popo::init_lr_special_hi_cliff_comp
LUA_BIND_WRAP(FUN_7102157c50, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::init_lr_special_hi_cliff_comp(obj))

// 0x7102157d10 -- FighterSpecializer_Popo::change_status_special_s_partner
LUA_BIND_WRAP(FUN_7102157d10, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::change_status_special_s_partner(obj))

// 0x7102157ee0 -- FighterSpecializer_Popo::init_final_partner
LUA_BIND_WRAP(FUN_7102157ee0, app::BattleObjectModuleAccessor, app::FighterSpecializer_Popo::init_final_partner(obj))

// 0x71021580c0 -- FighterSpecializer_Popo::start_partner_turn
LUA_BIND_WRAP(FUN_71021580c0, app::Fighter, app::FighterSpecializer_Popo::start_partner_turn(obj))

// 0x7102158530 -- FighterSpecializer_Popo::start_final_popo
LUA_BIND_WRAP(FUN_7102158530, app::Fighter, app::FighterSpecializer_Popo::start_final_popo(obj))

// 0x71021585f0 -- FighterSpecializer_Popo::start_final_popo_camera
LUA_BIND_WRAP(FUN_71021585f0, app::Fighter, app::FighterSpecializer_Popo::start_final_popo_camera(obj))

// 0x71021587a0 -- FighterSpecializer_Popo::enable_partner_catch_transition
LUA_BIND_WRAP(FUN_71021587a0, app::Fighter, app::FighterSpecializer_Popo::enable_partner_catch_transition(obj))

// 0x7102158860 -- FighterSpecializer_Popo::end_final_deactivated_iceberg
LUA_BIND_WRAP(FUN_7102158860, app::Fighter, app::FighterSpecializer_Popo::end_final_deactivated_iceberg(obj))

// 0x710215db90 -- FighterSpecializer_Falco::final_start_init
LUA_BIND_WRAP(FUN_710215db90, app::Fighter, app::FighterSpecializer_Falco::final_start_init(obj))

// 0x710215dc50
LUA_BIND_WRAP(FUN_710215dc50, app::Fighter, app::FighterSpecializer_Falco::final_start_exit(obj))

// 0x710215dd10
LUA_BIND_WRAP(FUN_710215dd10, app::Fighter, app::FighterSpecializer_Falco::final_ready_init(obj))

// 0x710215ddd0
LUA_BIND_WRAP(FUN_710215ddd0, app::Fighter, app::FighterSpecializer_Falco::final_ready_exec(obj))

// 0x710215df10
LUA_BIND_WRAP(FUN_710215df10, app::Fighter, app::FighterSpecializer_Falco::final_ready_exit(obj))

// 0x710215dfd0
LUA_BIND_WRAP(FUN_710215dfd0, app::Fighter, app::FighterSpecializer_Falco::final_scene01_init(obj))

// 0x710215e090
LUA_BIND_WRAP(FUN_710215e090, app::Fighter, app::FighterSpecializer_Falco::final_scene01_exec_fix_pos(obj))

// 0x710215e150
LUA_BIND_WRAP(FUN_710215e150, app::Fighter, app::FighterSpecializer_Falco::final_scene01_exit(obj))

// 0x710215e210
LUA_BIND_WRAP(FUN_710215e210, app::Fighter, app::FighterSpecializer_Falco::final_end_init(obj))

// 0x710215e2d0
LUA_BIND_WRAP(FUN_710215e2d0, app::Fighter, app::FighterSpecializer_Falco::final_end_exec(obj))

// 0x710215e390
LUA_BIND_WRAP(FUN_710215e390, app::Fighter, app::FighterSpecializer_Falco::final_end_exit(obj))

// 0x7102162550 -- FighterSnakeFinalModule::end_final
LUA_BIND_WRAP(FUN_7102162550, app::BattleObjectModuleAccessor, app::FighterSnakeFinalModule::end_final(obj))

// 0x7102162700 -- FighterSnakeFinalModule::initialize_reticle
LUA_BIND_WRAP(FUN_7102162700, app::BattleObjectModuleAccessor, app::FighterSnakeFinalModule::initialize_reticle(obj))
