// Batch C - 009: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 39 -- FighterSpecializer wrappers (Inkling/Shizue/Ridley/Gaogaen/Packun/Jack/Brave/Tantan/etc.)

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

extern "C" void FUN_710082a290();
extern "C" void FUN_710082a4a0();
extern "C" void FUN_710082c560();
extern "C" void FUN_710082ca60();
extern "C" void FUN_710082e2c0();
extern "C" void FUN_710082ec20();
extern "C" void FUN_710082f150();
extern "C" void FUN_710082fa30();
extern "C" void FUN_710082b620();

namespace app {
    struct Fighter;
    struct Weapon;
    struct FighterModuleAccessor;

    namespace FighterSpecializer_Inkling {
        void generate_rollerink(Fighter*);
        void lack_ink(Fighter*);
    }

    namespace WeaponSpecializer_ShizueFishingrod {
        void setup_physics_air_resistance(BattleObjectModuleAccessor*);
        void start_cut(BattleObjectModuleAccessor*);
        void enable_search(BattleObjectModuleAccessor*, bool);
    }

    namespace FighterSpecializer_Ridley {
        void request_special_s_wall_effect(FighterModuleAccessor*);
    }

    namespace FighterSpecializer_Gaogaen {
        void generate_rope(FighterModuleAccessor*);
        void revenge_off(Fighter*, bool);
    }

    namespace WeaponSpecializer_SimonWhip {
        void sleep_attack_by_speed(Weapon*);
        void reset_node_fix_flag_list(Weapon*);
    }

    namespace FighterSpecializer_Packun {
        void update_special_n_spikeball_pos(Fighter*);
        void start_final_packun(Fighter*);
        void end_final_packun(Fighter*);
    }

    namespace WeaponSpecializer_PackunBosspackun {
        void end_turn(Weapon*);
    }

    namespace FighterSpecializer_Jack {
        void set_doyle_suspend(BattleObjectModuleAccessor*, bool);
    }

    namespace WeaponSpecializer_JackDoyle {
        void update_aura_visible(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Brave {
        void lot_critical(Fighter*);
        void special_lw_open_command(Fighter*);
        void special_lw_start_select_command(Fighter*);
        void special_lw_close_window(Fighter*, bool, bool, bool);
        void special_lw_cursor_decide(Fighter*);
        void special_lw_start_cursor_blink(Fighter*);
        void special_lw_on_start_command(Fighter*);
    }

    namespace WeaponSpecializer_BraveFireball {
        void request_effect(BattleObjectModuleAccessor*);
    }

    namespace WeaponSpecializer_BraveLightning {
        void exec_map_collection(Weapon*);
    }

    namespace FighterSpecializer_Buddy {
        void update_special_n_partner_motion(Fighter*, bool);
    }

    namespace WeaponSpecializer_BuddyBullet {
        void request_bound_effect(Weapon*);
    }

    namespace WeaponSpecializer_MasterArrow1 {
        void set_search(Weapon*, bool);
    }

    namespace FighterSpecializer_Tantan {
        void check_attack_reverse(BattleObjectModuleAccessor*);
        void clear_control_command_punch(Fighter*);
    }
}

// 0x710219a420 — lua_bind forwarding wrapper, dispatches to FUN_710082a290
u64 FUN_710219a420(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082a290();
    return 0;
}

// 0x710219a4f0 — lua_bind forwarding wrapper, dispatches to FUN_710082a4a0
u64 FUN_710219a4f0(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082a4a0();
    return 0;
}

// 0x710219a810 — lua_bind forwarding wrapper, dispatches to FUN_710082c560
u64 FUN_710219a810(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082c560();
    return 0;
}

// 0x710219a8e0 — lua_bind forwarding wrapper, dispatches to FUN_710082ca60
u64 FUN_710219a8e0(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082ca60();
    return 0;
}

// 0x710219a9b0 — lua_bind forwarding wrapper, dispatches to FUN_710082e2c0
u64 FUN_710219a9b0(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082e2c0();
    return 0;
}

// 0x710219aa80 — lua_bind forwarding wrapper, dispatches to FUN_710082ec20
u64 FUN_710219aa80(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082ec20();
    return 0;
}

// 0x710219ab50 — lua_bind forwarding wrapper, dispatches to FUN_710082f150
u64 FUN_710219ab50(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082f150();
    return 0;
}

// 0x710219ac20 — lua_bind forwarding wrapper, dispatches to FUN_710082fa30
u64 FUN_710219ac20(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082fa30();
    return 0;
}

// 0x710219acf0 — lua_bind forwarding wrapper, dispatches to FUN_710082b620
u64 FUN_710219acf0(s64 param_1)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082b620();
    return 0;
}

// 0x710219e950 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Inkling::generate_rollerink
u64 FUN_710219e950(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Inkling::generate_rollerink(param_1);
    return 0;
}

// 0x710219ec30 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Inkling::lack_ink
u64 FUN_710219ec30(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Inkling::lack_ink(param_1);
    return 0;
}

// 0x71021a2db0 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_ShizueFishingrod::setup_physics_air_resistance
u64 FUN_71021a2db0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_ShizueFishingrod::setup_physics_air_resistance(param_1);
    return 0;
}

// 0x71021a2e70 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_ShizueFishingrod::start_cut
u64 FUN_71021a2e70(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_ShizueFishingrod::start_cut(param_1);
    return 0;
}

// 0x71021a2fa4 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_ShizueFishingrod::enable_search
u64 FUN_71021a2fa4(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_ShizueFishingrod::enable_search(param_1, param_3);
    return 0;
}

// 0x71021aa240 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Ridley::request_special_s_wall_effect
u64 FUN_71021aa240(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Ridley::request_special_s_wall_effect(param_1);
    return 0;
}

// 0x71021ab100 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Gaogaen::generate_rope
u64 FUN_71021ab100(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Gaogaen::generate_rope(param_1);
    return 0;
}

// 0x71021ab250 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Gaogaen::revenge_off
u64 FUN_71021ab250(app::Fighter *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Gaogaen::revenge_off(param_1, param_3);
    return 0;
}

// 0x71021ac310 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_SimonWhip::sleep_attack_by_speed
u64 FUN_71021ac310(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_SimonWhip::sleep_attack_by_speed(param_1);
    return 0;
}

// 0x71021ad260 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_SimonWhip::reset_node_fix_flag_list
u64 FUN_71021ad260(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_SimonWhip::reset_node_fix_flag_list(param_1);
    return 0;
}

// 0x71021b0d00 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Packun::update_special_n_spikeball_pos
u64 FUN_71021b0d00(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Packun::update_special_n_spikeball_pos(param_1);
    return 0;
}

// 0x71021b0dc0 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Packun::start_final_packun
u64 FUN_71021b0dc0(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Packun::start_final_packun(param_1);
    return 0;
}

// 0x71021b0e80 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Packun::end_final_packun
u64 FUN_71021b0e80(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Packun::end_final_packun(param_1);
    return 0;
}

// 0x71021b0f40 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_PackunBosspackun::end_turn
u64 FUN_71021b0f40(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_PackunBosspackun::end_turn(param_1);
    return 0;
}

// 0x71021b3884 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Jack::set_doyle_suspend
u64 FUN_71021b3884(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Jack::set_doyle_suspend(param_1, param_3);
    return 0;
}

// 0x71021b3c50 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_JackDoyle::update_aura_visible
u64 FUN_71021b3c50(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_JackDoyle::update_aura_visible(param_1);
    return 0;
}

// 0x71021b6250 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::lot_critical
u64 FUN_71021b6250(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::lot_critical(param_1);
    return 0;
}

// 0x71021b6490 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::special_lw_open_command
u64 FUN_71021b6490(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_open_command(param_1);
    return 0;
}

// 0x71021b6550 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::special_lw_start_select_command
u64 FUN_71021b6550(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_start_select_command(param_1);
    return 0;
}

// 0x71021b67b0 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::special_lw_close_window
u64 FUN_71021b67b0(app::Fighter *param_1, s64 param_2, bool param_3, bool param_4, bool param_5)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_close_window(param_1, param_3, param_4, param_5);
    return 0;
}

// 0x71021b6980 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::special_lw_cursor_decide
u64 FUN_71021b6980(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_cursor_decide(param_1);
    return 0;
}

// 0x71021b6a40 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::special_lw_start_cursor_blink
u64 FUN_71021b6a40(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_start_cursor_blink(param_1);
    return 0;
}

// 0x71021b6c10 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Brave::special_lw_on_start_command
u64 FUN_71021b6c10(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Brave::special_lw_on_start_command(param_1);
    return 0;
}

// 0x71021b7e60 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_BraveFireball::request_effect
u64 FUN_71021b7e60(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_BraveFireball::request_effect(param_1);
    return 0;
}

// 0x71021b7f20 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_BraveLightning::exec_map_collection
u64 FUN_71021b7f20(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_BraveLightning::exec_map_collection(param_1);
    return 0;
}

// 0x71021ba7c0 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Buddy::update_special_n_partner_motion
u64 FUN_71021ba7c0(app::Fighter *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Buddy::update_special_n_partner_motion(param_1, param_3);
    return 0;
}

// 0x71021ba9d0 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_BuddyBullet::request_bound_effect
u64 FUN_71021ba9d0(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_BuddyBullet::request_bound_effect(param_1);
    return 0;
}

// 0x71021beeb4 — lua_bind forwarding wrapper, dispatches to WeaponSpecializer_MasterArrow1::set_search
u64 FUN_71021beeb4(app::Weapon *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_MasterArrow1::set_search(param_1, param_3);
    return 0;
}

// 0x71021c2650 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Tantan::check_attack_reverse
u64 FUN_71021c2650(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Tantan::check_attack_reverse(param_1);
    return 0;
}

// 0x71021c2930 — lua_bind forwarding wrapper, dispatches to FighterSpecializer_Tantan::clear_control_command_punch
u64 FUN_71021c2930(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Tantan::clear_control_command_punch(param_1);
    return 0;
}
