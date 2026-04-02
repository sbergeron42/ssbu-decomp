// Batch C - 008: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 37 — FighterSpecializer wrappers (Snake/Metaknight/Pit/SZerosuit/Pikmin/etc.)

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

extern "C" void FUN_7100829e00();

namespace app {
    struct Fighter;
    struct Weapon;
    struct FighterModuleAccessor;

    namespace FighterSnakeFinalModule {
        void lock_on(BattleObjectModuleAccessor*);
    }

    namespace WeaponSpecializer_SnakeC4 {
        void detach_constraint(Weapon*, bool);
    }

    namespace FighterSpecializer_Metaknight {
        void set_special_n_ground_effect(Fighter*);
        void check_edge_special_lw(FighterModuleAccessor*);
    }

    namespace FighterSpecializer_Pit {
        void request_cut_in_chariotsight(Fighter*);
    }

    namespace FighterSpecializer_SZerosuit {
        void start_final_szerosuit(Fighter*);
        void start_final_szerosuit_camera(Fighter*);
        void exec_final_szerosuit_camera(Fighter*);
        void end_final_szerosuit(Fighter*);
    }

    namespace FighterSpecializer_Pikmin {
        void reduce_pikmin_all(FighterModuleAccessor*);
        void reduce_pikmin_all_change_top_pikmin(FighterModuleAccessor*);
        void liberty_pikmin_all(FighterModuleAccessor*);
    }

    namespace FighterSpecializer_Dedede {
        void end_special_n_shot_object_hit(Fighter*);
    }

    namespace FighterSpecializer_Lucario {
        void req_aura_effect_both(Fighter*);
        void effect_suspend(BattleObjectModuleAccessor*);
        void effect_resume(BattleObjectModuleAccessor*);
    }

    namespace WeaponSpecializer_LucarioAuraball {
        void set_scale(BattleObjectModuleAccessor*);
    }

    namespace WeaponSpecializer_RobotNarrowbeam {
        void calc_pos(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Sonic {
        void start_final_sonic(Fighter*);
        void start_final_sonic_camera(Fighter*);
        void end_final_sonic(Fighter*);
    }

    namespace FighterSpecializer_Purin {
        void special_n_set_power(BattleObjectModuleAccessor*);
        void special_n_req_effect_dash_smoke(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Palutena {
        void init_final_settings(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Reflet {
        void exit_special_n_tron_hold(FighterModuleAccessor*);
        void special_lw_heal_damage(FighterModuleAccessor*);
        void send_final_attack_event(FighterModuleAccessor*);
    }

    namespace FighterSpecializer_Gekkouga {
        void set_special_s_transition_term_forbid_group(FighterModuleAccessor*, bool);
    }

    namespace WeaponSpecializer_GekkougaGekkougaS {
        void set_link_final_end(BattleObjectModuleAccessor*, bool);
        void update_moon_position(BattleObjectModuleAccessor*);
        void raise_moon_position(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Rockman {
        void set_leafshield(BattleObjectModuleAccessor*, bool);
    }

    namespace FighterSpecializer_Ryu {
        void set_final_stage_disp_status(BattleObjectModuleAccessor*, bool, bool);
    }

    namespace FighterSpecializer_Roy {
        void hit_absolute_final_chrom(Fighter*);
    }

    namespace FighterSpecializer_Cloud {
        void display_final_window(bool);
        void display_final_window_final2(bool);
    }
}

// 0x7102162ac0
u64 FUN_7102162ac0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSnakeFinalModule::lock_on(param_1);
    return 0;
}

// 0x7102163c70
u64 FUN_7102163c70(app::Weapon *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_SnakeC4::detach_constraint(param_1, param_3);
    return 0;
}

// 0x7102167070
u64 FUN_7102167070(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Metaknight::set_special_n_ground_effect(param_1);
    return 0;
}

// 0x7102167130
u64 FUN_7102167130(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Metaknight::check_edge_special_lw(param_1);
    return 0;
}

// 0x71021673b0
u64 FUN_71021673b0(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pit::request_cut_in_chariotsight(param_1);
    return 0;
}

// 0x7102168ec0
u64 FUN_7102168ec0(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::start_final_szerosuit(param_1);
    return 0;
}

// 0x7102168f80
u64 FUN_7102168f80(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::start_final_szerosuit_camera(param_1);
    return 0;
}

// 0x7102169040
u64 FUN_7102169040(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::exec_final_szerosuit_camera(param_1);
    return 0;
}

// 0x7102169100
u64 FUN_7102169100(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_SZerosuit::end_final_szerosuit(param_1);
    return 0;
}

// 0x710216adb0
u64 FUN_710216adb0(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::reduce_pikmin_all(param_1);
    return 0;
}

// 0x710216ae70
u64 FUN_710216ae70(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::reduce_pikmin_all_change_top_pikmin(param_1);
    return 0;
}

// 0x710216b1a0
u64 FUN_710216b1a0(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pikmin::liberty_pikmin_all(param_1);
    return 0;
}

// 0x7102177a40
u64 FUN_7102177a40(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Dedede::end_special_n_shot_object_hit(param_1);
    return 0;
}

// 0x710217b270
u64 FUN_710217b270(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Lucario::req_aura_effect_both(param_1);
    return 0;
}

// 0x710217b330
u64 FUN_710217b330(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Lucario::effect_suspend(param_1);
    return 0;
}

// 0x710217b3f0
u64 FUN_710217b3f0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Lucario::effect_resume(param_1);
    return 0;
}

// 0x710217b900
u64 FUN_710217b900(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_LucarioAuraball::set_scale(param_1);
    return 0;
}

// 0x710217c470
u64 FUN_710217c470(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_RobotNarrowbeam::calc_pos(param_1);
    return 0;
}

// 0x710217fe10
u64 FUN_710217fe10(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::start_final_sonic(param_1);
    return 0;
}

// 0x710217fed0
u64 FUN_710217fed0(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::start_final_sonic_camera(param_1);
    return 0;
}

// 0x710217ff90
u64 FUN_710217ff90(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Sonic::end_final_sonic(param_1);
    return 0;
}

// 0x7102182090
u64 FUN_7102182090(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_set_power(param_1);
    return 0;
}

// 0x7102182240
u64 FUN_7102182240(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Purin::special_n_req_effect_dash_smoke(param_1);
    return 0;
}

// 0x7102189d70
u64 FUN_7102189d70(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Palutena::init_final_settings(param_1);
    return 0;
}

// 0x710218a2c0
u64 FUN_710218a2c0(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Reflet::exit_special_n_tron_hold(param_1);
    return 0;
}

// 0x710218a920
u64 FUN_710218a920(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Reflet::special_lw_heal_damage(param_1);
    return 0;
}

// 0x710218ab20
u64 FUN_710218ab20(app::FighterModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Reflet::send_final_attack_event(param_1);
    return 0;
}

// 0x710218d844
u64 FUN_710218d844(app::FighterModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Gekkouga::set_special_s_transition_term_forbid_group(param_1, param_3);
    return 0;
}

// 0x710218db34
u64 FUN_710218db34(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::set_link_final_end(param_1, param_3);
    return 0;
}

// 0x710218dc10
u64 FUN_710218dc10(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::update_moon_position(param_1);
    return 0;
}

// 0x710218dcd0
u64 FUN_710218dcd0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_GekkougaGekkougaS::raise_moon_position(param_1);
    return 0;
}

// 0x7102192724
u64 FUN_7102192724(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Rockman::set_leafshield(param_1, param_3);
    return 0;
}

// 0x71021958a8
u32 FUN_71021958a8(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3, bool param_4)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Ryu::set_final_stage_disp_status(param_1, param_3, param_4);
    return 0;
}

// 0x7102198f90
u64 FUN_7102198f90(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Roy::hit_absolute_final_chrom(param_1);
    return 0;
}

// 0x7102199088
u64 FUN_7102199088(s64 param_1)
{
    u8 in_w8;
    u64 in_x10;
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Cloud::display_final_window(in_w8);
    return 0;
}

// 0x7102199198
u64 FUN_7102199198(s64 param_1)
{
    u8 in_w8;
    u64 in_x10;
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::FighterSpecializer_Cloud::display_final_window_final2(in_w8);
    return 0;
}

// 0x710219a280
u64 FUN_710219a280(s64 param_1)
{
    u64 in_x10;
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_7100829e00();
    return 0;
}
