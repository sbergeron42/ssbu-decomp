// MEDIUM framed_vtable_call batch 007 (0x710214f810 – 0x7102162700)
// Named FighterSpecializer / WeaponSpecializer / FighterSnakeFinalModule calls

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
void delete_plunger(Fighter *, bool);
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

#define NAMED_CALL_2(fn, T1, T2) \
u32 fn(T1 param_1, s64 param_2) { \
    register u64 in_x10 asm("x10"); \
    asm volatile("" : "+r"(in_x10)); \
    *(u64 *)(param_2 + 0x10) = in_x10; \
    app::fn(param_1); \
    return 0; \
}

// 0x710214f810 -- FighterSpecializer_Fox
u32 FUN_710214f810(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_ready_exec(param_1); return 0; }

// 0x710214f950
u32 FUN_710214f950(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_ready_exit(param_1); return 0; }

// 0x710214fa10
u32 FUN_710214fa10(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_scene01_init(param_1); return 0; }

// 0x710214fad0
u32 FUN_710214fad0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_scene01_exec_fix_pos(param_1); return 0; }

// 0x710214fb90
u32 FUN_710214fb90(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_scene01_exit(param_1); return 0; }

// 0x710214fc50
u32 FUN_710214fc50(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_end_init(param_1); return 0; }

// 0x710214fd10
u32 FUN_710214fd10(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_end_exec(param_1); return 0; }

// 0x710214fdd0
u32 FUN_710214fdd0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_end_exit(param_1); return 0; }

// 0x7102153610 -- FighterSpecializer_Luigi::delete_plunger(Fighter*, bool)
u32 FUN_7102153610(app::Fighter *param_1, s64 param_2, bool param_3)
{
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Luigi::delete_plunger(param_1, param_3);
    return 0;
}

// 0x71021536d0 -- WeaponSpecializer_LuigiPlunger::modify_physics_param
u32 FUN_71021536d0(app::Weapon *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LuigiPlunger::modify_physics_param(param_1); return 0; }

// 0x7102153790 -- WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd
u32 FUN_7102153790(app::Weapon *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd(param_1); return 0; }

// 0x7102157540 -- FighterSpecializer_Peach::special_lw_check_num_of_item
u32 FUN_7102157540(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Peach::special_lw_check_num_of_item(param_1); return 0; }

// 0x7102157720 -- FighterSpecializer_Peach::final_rand_create_item
u32 FUN_7102157720(app::FighterModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Peach::final_rand_create_item(param_1); return 0; }

// 0x7102157b90 -- FighterSpecializer_Popo::init_lr_special_s_partner
u32 FUN_7102157b90(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::init_lr_special_s_partner(param_1); return 0; }

// 0x7102157c50 -- FighterSpecializer_Popo::init_lr_special_hi_cliff_comp
u32 FUN_7102157c50(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::init_lr_special_hi_cliff_comp(param_1); return 0; }

// 0x7102157d10 -- FighterSpecializer_Popo::change_status_special_s_partner
u32 FUN_7102157d10(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::change_status_special_s_partner(param_1); return 0; }

// 0x7102157ee0 -- FighterSpecializer_Popo::init_final_partner
u32 FUN_7102157ee0(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::init_final_partner(param_1); return 0; }

// 0x71021580c0 -- FighterSpecializer_Popo::start_partner_turn
u32 FUN_71021580c0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::start_partner_turn(param_1); return 0; }

// 0x7102158530 -- FighterSpecializer_Popo::start_final_popo
u32 FUN_7102158530(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::start_final_popo(param_1); return 0; }

// 0x71021585f0 -- FighterSpecializer_Popo::start_final_popo_camera
u32 FUN_71021585f0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::start_final_popo_camera(param_1); return 0; }

// 0x71021587a0 -- FighterSpecializer_Popo::enable_partner_catch_transition
u32 FUN_71021587a0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::enable_partner_catch_transition(param_1); return 0; }

// 0x7102158860 -- FighterSpecializer_Popo::end_final_deactivated_iceberg
u32 FUN_7102158860(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::end_final_deactivated_iceberg(param_1); return 0; }

// 0x710215db90 -- FighterSpecializer_Falco
u32 FUN_710215db90(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_start_init(param_1); return 0; }

// 0x710215dc50
u32 FUN_710215dc50(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_start_exit(param_1); return 0; }

// 0x710215dd10
u32 FUN_710215dd10(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_ready_init(param_1); return 0; }

// 0x710215ddd0
u32 FUN_710215ddd0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_ready_exec(param_1); return 0; }

// 0x710215df10
u32 FUN_710215df10(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_ready_exit(param_1); return 0; }

// 0x710215dfd0
u32 FUN_710215dfd0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_scene01_init(param_1); return 0; }

// 0x710215e090
u32 FUN_710215e090(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_scene01_exec_fix_pos(param_1); return 0; }

// 0x710215e150
u32 FUN_710215e150(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_scene01_exit(param_1); return 0; }

// 0x710215e210
u32 FUN_710215e210(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_end_init(param_1); return 0; }

// 0x710215e2d0
u32 FUN_710215e2d0(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_end_exec(param_1); return 0; }

// 0x710215e390
u32 FUN_710215e390(app::Fighter *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_end_exit(param_1); return 0; }

// 0x7102162550 -- FighterSnakeFinalModule::end_final
u32 FUN_7102162550(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::end_final(param_1); return 0; }

// 0x7102162700 -- FighterSnakeFinalModule::initialize_reticle
u32 FUN_7102162700(app::BattleObjectModuleAccessor *param_1, s64 param_2) {
    register u64 in_x10 asm("x10"); asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::initialize_reticle(param_1); return 0; }
