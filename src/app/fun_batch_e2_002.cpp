#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-002
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

struct BattleObjectModuleAccessor;
struct Fighter;
struct Weapon;
struct FighterModuleAccessor;

namespace app {
    namespace FighterSpecializer_SZerosuit {
        void end_final_szerosuit(Fighter *);
    }
    namespace FighterSpecializer_Pikmin {
        void liberty_pikmin_all(FighterModuleAccessor *);
    }
    namespace WeaponSpecializer_LucarioAuraball {
        void set_scale(BattleObjectModuleAccessor *);
    }
    namespace WeaponSpecializer_RobotNarrowbeam {
        void calc_pos(BattleObjectModuleAccessor *);
    }
    namespace FighterSpecializer_Sonic {
        void end_final_sonic(Fighter *);
    }
    namespace FighterSpecializer_Purin {
        void special_n_req_effect_dash_smoke(BattleObjectModuleAccessor *);
    }
    namespace WeaponSpecializer_GekkougaGekkougaS {
        void raise_moon_position(BattleObjectModuleAccessor *);
    }
    namespace FighterSpecializer_Inkling {
        void lack_ink(Fighter *);
    }
    namespace WeaponSpecializer_SimonWhip {
        void sleep_attack_by_speed(Weapon *);
        void reset_node_fix_flag_list(Weapon *);
    }
    namespace WeaponSpecializer_JackDoyle {
        void update_aura_visible(BattleObjectModuleAccessor *);
    }
    namespace WeaponSpecializer_BraveLightning {
        void exec_map_collection(Weapon *);
    }
    namespace FighterSpecializer_Buddy {
        void update_special_n_partner_motion(Fighter *, s64);
    }
    namespace FighterSpecializer_Tantan {
        void clear_control_command_move(Fighter *);
    }
    namespace WeaponSpecializer_TantanRing {
        void check_attach(BattleObjectModuleAccessor *);
    }
    namespace FighterSpecializer_Pickel {
        void update_mining_pickelobject(Fighter *);
        void remove_have_craft_weapon_all(BattleObjectModuleAccessor *);
        void set_head_angle_change_motion(Fighter *);
    }
    namespace FighterSpecializer_Demon {
        void check_disabled_motion_camera_of_scale(BattleObjectModuleAccessor *);
    }
    namespace FighterSpecializer_Trail {
        void change_magic(Fighter *);
    }
    namespace WeaponSpecializer_ElementDiver {
        void remove_constraint(Weapon *);
    }
    namespace WeaponSpecializer_EdgeFire {
        void request_effect(BattleObjectModuleAccessor *);
    }
    namespace item {
        void apply_powerup_attr(s64 *);
    }
}

// ---- lua_bind wrappers (32 bytes each) -----------------------------------------------
// Pattern: str x10,[x0,#0x10]; mov x0,x8; bl <func>; mov w0,wzr
// x0 = lua state buffer (param_1), x8 = typed object (in_x8, implicit register param)

// 0x7102169100 — FighterSpecializer_SZerosuit::end_final_szerosuit (32 bytes)
u32 FUN_7102169100(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::end_final_szerosuit(in_x8);
    return 0;
}

// 0x710216b1a0 — FighterSpecializer_Pikmin::liberty_pikmin_all (32 bytes)
u32 FUN_710216b1a0(s64 *param_1, s64 param_2)
{
    register FighterModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::liberty_pikmin_all(in_x8);
    return 0;
}

// 0x710217b900 — WeaponSpecializer_LucarioAuraball::set_scale (32 bytes)
u32 FUN_710217b900(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_LucarioAuraball::set_scale(in_x8);
    return 0;
}

// 0x710217c470 — WeaponSpecializer_RobotNarrowbeam::calc_pos (32 bytes)
u32 FUN_710217c470(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_RobotNarrowbeam::calc_pos(in_x8);
    return 0;
}

// 0x710217ff90 — FighterSpecializer_Sonic::end_final_sonic (32 bytes)
u32 FUN_710217ff90(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::end_final_sonic(in_x8);
    return 0;
}

// 0x7102182240 — FighterSpecializer_Purin::special_n_req_effect_dash_smoke (32 bytes)
u32 FUN_7102182240(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_req_effect_dash_smoke(in_x8);
    return 0;
}

// 0x710218dcd0 — WeaponSpecializer_GekkougaGekkougaS::raise_moon_position (32 bytes)
u32 FUN_710218dcd0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::raise_moon_position(in_x8);
    return 0;
}

// 0x710219ec30 — FighterSpecializer_Inkling::lack_ink (32 bytes)
u32 FUN_710219ec30(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Inkling::lack_ink(in_x8);
    return 0;
}

// 0x71021ac310 — WeaponSpecializer_SimonWhip::sleep_attack_by_speed (32 bytes)
u32 FUN_71021ac310(s64 *param_1, s64 param_2)
{
    register Weapon *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_SimonWhip::sleep_attack_by_speed(in_x8);
    return 0;
}

// 0x71021ad260 — WeaponSpecializer_SimonWhip::reset_node_fix_flag_list (32 bytes)
u32 FUN_71021ad260(s64 *param_1, s64 param_2)
{
    register Weapon *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_SimonWhip::reset_node_fix_flag_list(in_x8);
    return 0;
}

// 0x71021b3c50 — WeaponSpecializer_JackDoyle::update_aura_visible (32 bytes)
u32 FUN_71021b3c50(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_JackDoyle::update_aura_visible(in_x8);
    return 0;
}

// 0x71021b7f20 — WeaponSpecializer_BraveLightning::exec_map_collection (32 bytes)
u32 FUN_71021b7f20(s64 *param_1, s64 param_2)
{
    register Weapon *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_BraveLightning::exec_map_collection(in_x8);
    return 0;
}

// 0x71021ba7c0 — FighterSpecializer_Buddy::update_special_n_partner_motion(Fighter*, s64) (32 bytes)
// Second arg (bool-like flag) passed via x1 without normalization
u32 FUN_71021ba7c0(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Buddy::update_special_n_partner_motion(in_x8, param_2);
    return 0;
}

// 0x71021c29f0 — FighterSpecializer_Tantan::clear_control_command_move (32 bytes)
u32 FUN_71021c29f0(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Tantan::clear_control_command_move(in_x8);
    return 0;
}

// 0x71021c4000 — WeaponSpecializer_TantanRing::check_attach (32 bytes)
u32 FUN_71021c4000(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_TantanRing::check_attach(in_x8);
    return 0;
}

// 0x71021c86e0 — FighterSpecializer_Pickel::update_mining_pickelobject (32 bytes)
u32 FUN_71021c86e0(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::update_mining_pickelobject(in_x8);
    return 0;
}

// 0x71021ca8e0 — FighterSpecializer_Pickel::remove_have_craft_weapon_all (32 bytes)
u32 FUN_71021ca8e0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::remove_have_craft_weapon_all(in_x8);
    return 0;
}

// 0x71021cbd00 — FighterSpecializer_Pickel::set_head_angle_change_motion (32 bytes)
u32 FUN_71021cbd00(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::set_head_angle_change_motion(in_x8);
    return 0;
}

// 0x71021d89d0 — FighterSpecializer_Demon::check_disabled_motion_camera_of_scale (32 bytes)
u32 FUN_71021d89d0(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Demon::check_disabled_motion_camera_of_scale(in_x8);
    return 0;
}

// 0x71021db850 — FighterSpecializer_Trail::change_magic (32 bytes)
u32 FUN_71021db850(s64 *param_1, s64 param_2)
{
    register Fighter *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Trail::change_magic(in_x8);
    return 0;
}

// 0x71021de820 — WeaponSpecializer_ElementDiver::remove_constraint (32 bytes)
u32 FUN_71021de820(s64 *param_1, s64 param_2)
{
    register Weapon *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_ElementDiver::remove_constraint(in_x8);
    return 0;
}

// 0x71021e2520 — WeaponSpecializer_EdgeFire::request_effect (32 bytes)
u32 FUN_71021e2520(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::WeaponSpecializer_EdgeFire::request_effect(in_x8);
    return 0;
}

// 0x71021ff230 — item::apply_powerup_attr: direct lua_State* pass-through (24 bytes)
// No x10 store — param_1 (x0 = lua_State*) passed directly to callee
u32 FUN_71021ff230(s64 *param_1)
{
    app::item::apply_powerup_attr(param_1);
    return 0;
}
