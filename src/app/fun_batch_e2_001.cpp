#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102-0x7103 address range, batch e2-001
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

struct BattleObjectModuleAccessor;
struct Fighter;
struct Weapon;
struct FighterModuleAccessor;

[[noreturn]] extern "C" void abort();
extern "C" void FUN_71006eafb0(u64);

namespace app {
    namespace FighterUtil {
        void adjust_bitten_wario(BattleObjectModuleAccessor *);
        void exit_big_small(BattleObjectModuleAccessor *);
        void flash_eye_info(BattleObjectModuleAccessor *);
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
        void special_n_req_effect_dash_smoke(BattleObjectModuleAccessor *);
    }
    namespace FighterSpecializer_Fox {
        void final_end_exit(Fighter *);
    }
    namespace WeaponSpecializer_LuigiPlunger {
        void modify_physics_param_2nd(Weapon *);
    }
    namespace FighterSpecializer_Peach {
        void special_lw_check_num_of_item(FighterModuleAccessor *);
        void final_rand_create_item(FighterModuleAccessor *);
    }
    namespace FighterSpecializer_Popo {
        void end_final_deactivated_iceberg(Fighter *);
    }
    namespace FighterSpecializer_Falco {
        void final_end_exit(Fighter *);
    }
    namespace FighterSnakeFinalModule {
        void end_final(BattleObjectModuleAccessor *);
        void initialize_reticle(BattleObjectModuleAccessor *);
        void lock_on(BattleObjectModuleAccessor *);
    }
    namespace WeaponSpecializer_SnakeC4 {
        void detach_constraint(Weapon *, s64);
    }
    namespace FighterSpecializer_Metaknight {
        void check_edge_special_lw(FighterModuleAccessor *);
    }
    namespace FighterSpecializer_Pit {
        void request_cut_in_chariotsight(Fighter *);
    }
}

// ---- abort() wrappers (12 bytes each) -----------------------------------------------
// Note: 0x7102 abort wrappers are already in fun_batch_c2_*.cpp — only 0x7103 here

// 0x7103177954 (12 bytes)
void FUN_7103177954(void) { abort(); }

// ---- lua_bind wrappers (32 bytes each) -----------------------------------------------
// Pattern: str x10,[x0,#0x10]; mov x0,x8; bl <func>; mov w0,wzr
// x0 = lua state buffer (param_1), x8 = typed object (in_x8, implicit register param)

// 0x71020bf9d0 — FighterUtil::adjust_bitten_wario (32 bytes)
u32 FUN_71020bf9d0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterUtil::adjust_bitten_wario(in_x8);
    return 0;
}

// 0x71020c0670 — FighterUtil::exit_big_small (32 bytes)
u32 FUN_71020c0670(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterUtil::exit_big_small(in_x8);
    return 0;
}

// 0x71020c3ba0 — FighterUtil::flash_eye_info (32 bytes)
u32 FUN_71020c3ba0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterUtil::flash_eye_info(in_x8);
    return 0;
}

// 0x71020c6750 — load sound module ptr via x9, call FUN_71006eafb0 (32 bytes)
// Note: x9 holds the module accessor; loads sound ptr at +0x148
u32 FUN_71020c6750(s64 *param_1)
{
    register u64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    FUN_71006eafb0(*(u64 *)(in_x9 + 0x148));
    return 0;
}

// 0x7102146620 — FighterSpecializer_Link::set_item_hold_anim_for_script (32 bytes)
u32 FUN_7102146620(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Link::set_item_hold_anim_for_script(in_x8);
    return 0;
}

// 0x7102146bd0 — WeaponSpecializer_LinkBowarrow::to_item (32 bytes)
u32 FUN_7102146bd0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_LinkBowarrow::to_item(in_x8);
    return 0;
}

// 0x7102149810 — FighterSpecializer_Kirby::inhale_object (32 bytes)
u32 FUN_7102149810(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Kirby::inhale_object(in_x8);
    return 0;
}

// 0x710214a000 — FighterSpecializer_Purin::special_n_req_effect_dash_smoke (32 bytes)
u32 FUN_710214a000(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_req_effect_dash_smoke(in_x8);
    return 0;
}

// 0x710214fdd0 — FighterSpecializer_Fox::final_end_exit (32 bytes)
u32 FUN_710214fdd0(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Fox::final_end_exit(in_x8);
    return 0;
}

// 0x7102153790 — WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd (32 bytes)
u32 FUN_7102153790(s64 *param_1, s64 param_2)
{
    register Weapon *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_LuigiPlunger::modify_physics_param_2nd(in_x8);
    return 0;
}

// 0x7102157540 — FighterSpecializer_Peach::special_lw_check_num_of_item (32 bytes)
u32 FUN_7102157540(s64 *param_1, s64 param_2)
{
    register FighterModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Peach::special_lw_check_num_of_item(in_x8);
    return 0;
}

// 0x7102157720 — FighterSpecializer_Peach::final_rand_create_item (32 bytes)
u32 FUN_7102157720(s64 *param_1, s64 param_2)
{
    register FighterModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Peach::final_rand_create_item(in_x8);
    return 0;
}

// 0x7102158860 — FighterSpecializer_Popo::end_final_deactivated_iceberg (32 bytes)
u32 FUN_7102158860(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Popo::end_final_deactivated_iceberg(in_x8);
    return 0;
}

// 0x710215e390 — FighterSpecializer_Falco::final_end_exit (32 bytes)
u32 FUN_710215e390(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Falco::final_end_exit(in_x8);
    return 0;
}

// 0x7102162550 — FighterSnakeFinalModule::end_final (32 bytes)
u32 FUN_7102162550(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::end_final(in_x8);
    return 0;
}

// 0x7102162700 — FighterSnakeFinalModule::initialize_reticle (32 bytes)
u32 FUN_7102162700(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::initialize_reticle(in_x8);
    return 0;
}

// 0x7102162ac0 — FighterSnakeFinalModule::lock_on (32 bytes)
u32 FUN_7102162ac0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::lock_on(in_x8);
    return 0;
}

// 0x7102163c70 — WeaponSpecializer_SnakeC4::detach_constraint(Weapon*, bool) (32 bytes)
// bool arg from x1 passed through to callee as second arg
u32 FUN_7102163c70(s64 *param_1, s64 param_2)
{
    register Weapon *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_SnakeC4::detach_constraint(in_x8, param_2);
    return 0;
}

// 0x7102167130 — FighterSpecializer_Metaknight::check_edge_special_lw (32 bytes)
u32 FUN_7102167130(s64 *param_1, s64 param_2)
{
    register FighterModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Metaknight::check_edge_special_lw(in_x8);
    return 0;
}

// 0x71021673b0 — FighterSpecializer_Pit::request_cut_in_chariotsight (32 bytes)
u32 FUN_71021673b0(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Pit::request_cut_in_chariotsight(in_x8);
    return 0;
}
