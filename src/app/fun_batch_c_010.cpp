// Batch C - 010: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 35 — Tantan/Pickel/Demon/Trail/Edge/item/boss wrappers + misc

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

struct lua_State;

extern "C" void FUN_7100f03ef0(u64);
extern "C" void FUN_71015c0410();
extern "C" void FUN_710069b6c0(s64, s32);
extern "C" void FUN_71015b08c0(u64);
extern "C" void FUN_71015b3a40(u64);
extern "C" void FUN_71004e9e30(u64, u32);

namespace app {
    struct Fighter;
    struct Weapon;

    namespace FighterSpecializer_Tantan {
        void clear_control_command_move(Fighter*);
    }

    namespace WeaponSpecializer_TantanBeam {
        void update_tip_pos(Weapon*);
    }

    namespace WeaponSpecializer_TantanSpiralleft {
        void update_dragon_beam_nest_tip_pos(BattleObjectModuleAccessor*);
    }

    namespace WeaponSpecializer_TantanRing {
        void check_attach(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Pickel {
        void create_table(BattleObjectModuleAccessor*, bool, bool);
        void update_mining_pickelobject(Fighter*);
        void remove_have_craft_weapon_all(BattleObjectModuleAccessor*);
        void set_head_angle_change_motion(Fighter*);
    }

    namespace WeaponSpecializer_PickelTrolley {
        void send_link_event_nodes_check_collision(Weapon*);
        void set_original_pickel_team(Weapon*);
    }

    namespace WeaponSpecializer_PickelTable {
        void set_z_pos_for_flat_stage(BattleObjectModuleAccessor*);
    }

    namespace FighterSpecializer_Demon {
        void check_disabled_motion_camera_of_stage(BattleObjectModuleAccessor*);
        void check_disabled_motion_camera_of_scale(BattleObjectModuleAccessor*);
    }

    namespace WeaponSpecializer_DemonBlaster {
        void update_fly_posture(Weapon*);
    }

    namespace FighterSpecializer_Trail {
        void change_magic(Fighter*);
    }

    namespace WeaponSpecializer_ElementDiver {
        void remove_constraint(Weapon*);
    }

    namespace FighterSpecializer_Edge {
        void set_one_winged_light_weight_data(Fighter*, bool);
    }

    namespace WeaponSpecializer_EdgeFire {
        void request_effect(BattleObjectModuleAccessor*);
    }

    namespace item {
        void apply_powerup_throw(lua_State*);
        void apply_powerup_etc(lua_State*);
        void apply_powerup_attr(lua_State*);
    }

    namespace boss_private {
        void send_event_on_boss_dead(lua_State*);
    }

    namespace item_collision_manager {
        void disable_ground_collision(lua_State*);
    }
}

// 0x71021c29f0
u64 FUN_71021c29f0(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Tantan::clear_control_command_move(param_1);
    return 0;
}

// 0x71021c3050
u64 FUN_71021c3050(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_TantanBeam::update_tip_pos(param_1);
    return 0;
}

// 0x71021c3890
u64 FUN_71021c3890(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_TantanSpiralleft::update_dragon_beam_nest_tip_pos(param_1);
    return 0;
}

// 0x71021c4000
u64 FUN_71021c4000(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_TantanRing::check_attach(param_1);
    return 0;
}

// 0x71021c7c1c
u64 FUN_71021c7c1c(app::BattleObjectModuleAccessor *param_1, s64 param_2, bool param_3, bool param_4)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::create_table(param_1, param_3, param_4);
    return 0;
}

// 0x71021c86e0
u64 FUN_71021c86e0(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::update_mining_pickelobject(param_1);
    return 0;
}

// 0x71021c8c30
u64 FUN_71021c8c30(u64 param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    FUN_7100f03ef0(param_1);
    return 0;
}

// 0x71021ca8e0
u64 FUN_71021ca8e0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::remove_have_craft_weapon_all(param_1);
    return 0;
}

// 0x71021cbd00
u64 FUN_71021cbd00(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Pickel::set_head_angle_change_motion(param_1);
    return 0;
}

// 0x71021cc550
u64 FUN_71021cc550(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_PickelTrolley::send_link_event_nodes_check_collision(param_1);
    return 0;
}

// 0x71021cc610
u64 FUN_71021cc610(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_PickelTrolley::set_original_pickel_team(param_1);
    return 0;
}

// 0x71021d3680
u64 FUN_71021d3680(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_PickelTable::set_z_pos_for_flat_stage(param_1);
    return 0;
}

// 0x71021d8910
u64 FUN_71021d8910(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Demon::check_disabled_motion_camera_of_stage(param_1);
    return 0;
}

// 0x71021d89d0
u64 FUN_71021d89d0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Demon::check_disabled_motion_camera_of_scale(param_1);
    return 0;
}

// 0x71021d9730
u64 FUN_71021d9730(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_DemonBlaster::update_fly_posture(param_1);
    return 0;
}

// 0x71021db850
u64 FUN_71021db850(app::Fighter *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Trail::change_magic(param_1);
    return 0;
}

// 0x71021de820
u64 FUN_71021de820(app::Weapon *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_ElementDiver::remove_constraint(param_1);
    return 0;
}

// 0x71021e1290
u64 FUN_71021e1290(app::Fighter *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::FighterSpecializer_Edge::set_one_winged_light_weight_data(param_1, param_3);
    return 0;
}

// 0x71021e1690
u64 FUN_71021e1690(s64 param_1, s64 param_2)
{
    s64 lVar1;
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    lVar1 = *(s64 *)(param_1 + 0xc0);
    *(u64 *)(lVar1 + 0x2f8) = 0;
    *(u64 *)(lVar1 + 0x2f0) = 0;
    *(u64 *)(lVar1 + 0x2e0) = *(u64 *)(lVar1 + 0x2d8);
    FUN_710069b6c0(param_1, 0x59);
    return 0;
}

// 0x71021e2520
u64 FUN_71021e2520(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::WeaponSpecializer_EdgeFire::request_effect(param_1);
    return 0;
}

// 0x71021f6514
u64 FUN_71021f6514(s64 *param_1)
{
    (**(void (**)(s64 *, s32))(*param_1 + 0x520))(param_1, 0);
    return 0;
}

// 0x71021f72f0
u64 FUN_71021f72f0(void)
{
    FUN_71015c0410();
    return 0;
}

// 0x71021fabc4
u64 FUN_71021fabc4(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(param_1 + 0x208);
    (**(void (**)())(*plVar1 + 0xc8))();
    return 0;
}

// 0x71021fbaa0
u64 FUN_71021fbaa0(s64 param_1)
{
    FUN_71015b08c0(*(u64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x190) + 0x220));
    return 0;
}

// 0x71021fc278
u64 FUN_71021fc278(s64 param_1, s64 *param_2)
{
    *(u16 *)(param_1 + 0x150) = 1;
    *(u8 *)(param_1 + 0x152) = 0;
    (**(void (**)(s64 *, s32))(*param_2 + 0x540))(param_2, 1);
    return 0;
}

// 0x71021ff030
u64 FUN_71021ff030(lua_State *param_1)
{
    app::item::apply_powerup_throw(param_1);
    return 0;
}

// 0x71021ff1c0
u64 FUN_71021ff1c0(lua_State *param_1)
{
    app::item::apply_powerup_etc(param_1);
    return 0;
}

// 0x71021ff230
u64 FUN_71021ff230(lua_State *param_1)
{
    app::item::apply_powerup_attr(param_1);
    return 0;
}

// 0x71022004e0
u64 FUN_71022004e0(s64 param_1)
{
    s64 *plVar1;
    plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x190) + 0x220) + 0x100);
    (**(void (**)(s64 *, s32))(*plVar1 + 0x130))(plVar1, 4);
    return 0;
}

// 0x7102203b00
u64 FUN_7102203b00(s64 param_1)
{
    FUN_71015b3a40(*(u64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x190) + 0x220));
    return 0;
}

// 0x7102208ccc
u64 FUN_7102208ccc(s64 param_1, s64 param_2)
{
    FUN_71004e9e30(*(u64 *)(param_1 + 8),
                   *(u32 *)(*(s64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_2 - 8) + 0x1a0) + 0x190) + 0x220) + 0xc));
    return 0;
}

// 0x7102208d00
u64 FUN_7102208d00(lua_State *param_1)
{
    app::boss_private::send_event_on_boss_dead(param_1);
    return 0;
}

// 0x7102208df0
u64 FUN_7102208df0(s64 param_1)
{
    s64 *plVar1;
    plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x78);
    (**(void (**)(s64 *, s32))(*plVar1 + 0x330))(plVar1, 1);
    return 0;
}

// 0x710220bf50
u64 FUN_710220bf50(lua_State *param_1)
{
    app::item_collision_manager::disable_ground_collision(param_1);
    return 0;
}
