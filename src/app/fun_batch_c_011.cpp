// Batch C - 011: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 57

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

struct lua_State;

extern "C" void FUN_710160dea0();

namespace app {
    struct ItemModuleAccessor;

    namespace item_hud {
        void del_cursor(lua_State*);
        void clear_owner_color(lua_State*);
    }
    namespace backshield {
        void set_reflector(BattleObjectModuleAccessor*);
    }
    namespace beetle {
        void set_grab(BattleObjectModuleAccessor*);
    }
    namespace clubshot {
        void check_roll_up_area(ItemModuleAccessor*);
    }
    namespace dragoonsight {
        void set_dragoonsight_effect(ItemModuleAccessor*, bool);
    }
    namespace healball {
        void fighter_heal(ItemModuleAccessor*);
    }
    namespace sandbag {
        void homerun_contest_change_fly_camera();
        void homerun_contest_change_landing_camera();
        void homerun_contest_change_timeup_fly_camera();
        void homerun_contest_change_normal_camera();
    }
    namespace smashball {
        void escape_from_fighter(ItemModuleAccessor*);
        void chase_fighter(ItemModuleAccessor*);
    }
    namespace warpstar {
        void clear_collision_info(BattleObjectModuleAccessor*);
    }
    namespace wood {
        void free_log_group(ItemModuleAccessor*);
    }
    namespace androssshot {
        void hit_check(ItemModuleAccessor*);
    }
    namespace devil {
        void set_camera_devil_mode(bool);
        void set_camera_devil_fix_mode(bool);
    }
    namespace ghirahim {
        void set_shield(ItemModuleAccessor*);
    }
    namespace midna {
        void throw_attack(ItemModuleAccessor*);
    }
    namespace nintendogshi {
        void set_nintendogs_effect(ItemModuleAccessor*, bool);
    }
    namespace riki {
        void yorokobemo(ItemModuleAccessor*);
        void healdamo(ItemModuleAccessor*);
        void stealdamo(ItemModuleAccessor*);
    }
    namespace tvgame {
        void set_camera_devil_mode(bool);
        void set_reflector(ItemModuleAccessor*);
        void set_info_tv15_visible(bool);
    }
    namespace tvgameshot {
        void info_tv15_set_visible(bool);
    }
    namespace meloettashot {
        void ReflectOnViewFrame(ItemModuleAccessor*);
    }
    namespace sirnight {
        void set_reflector(ItemModuleAccessor*);
    }
    namespace xerneas {
        void powerup(ItemModuleAccessor*);
    }
    namespace zoroark {
        void send_link_event_final_finish_pre(ItemModuleAccessor*);
    }
    namespace starring {
        void shoot(ItemModuleAccessor*);
    }
    namespace blackball {
        void start_item_capture(ItemModuleAccessor*);
        void set_attack_offset_back_line_z(ItemModuleAccessor*);
    }
    namespace teamhealfield {
        void heal_fighters(ItemModuleAccessor*);
    }
    namespace robinlift {
        void set_clatter(BattleObjectModuleAccessor*);
    }
    namespace cyborg {
        void set_reflector(ItemModuleAccessor*);
    }
    namespace guile {
        void set_shield(BattleObjectModuleAccessor*);
    }
    namespace akira {
        void set_all_shield(BattleObjectModuleAccessor*);
        void set_bullet_shield(BattleObjectModuleAccessor*);
    }
    namespace shovelknight {
        void set_reflector(BattleObjectModuleAccessor*);
    }
    namespace mimikkyu {
        void set_captured_fighter_visibility_and_hit(ItemModuleAccessor*);
    }
    namespace sukapon {
        void set_all_shield(ItemModuleAccessor*);
        void set_bullet_shield(ItemModuleAccessor*);
    }
    namespace springman {
        void set_all_shield(ItemModuleAccessor*);
        void set_bullet_shield(ItemModuleAccessor*);
    }
    namespace baitocrane {
        void set_grab(BattleObjectModuleAccessor*);
    }
    namespace dracula2 {
        void notify_melee_start_to_hud_manager();
    }
    namespace marx {
        void fighter_visible(bool);
    }
    namespace pickelobject {
        void update_collision_work(ItemModuleAccessor*);
        void set_material_visibility_mesh_all_invisible(ItemModuleAccessor*);
        void check_range_from_onwer(ItemModuleAccessor*);
        void update_blink(ItemModuleAccessor*);
    }
}

// 0x710220c280 — lua_bind pass-through, dispatches to item_hud::del_cursor
u32 FUN_710220c280(lua_State *param_1)
{
    app::item_hud::del_cursor(param_1);
    return 0;
}

// 0x710220c2a0 — lua_bind pass-through, dispatches to item_hud::clear_owner_color
u32 FUN_710220c2a0(lua_State *param_1)
{
    app::item_hud::clear_owner_color(param_1);
    return 0;
}

// 0x7102238360 — lua_bind forwarding wrapper, dispatches to backshield::set_reflector
u64 FUN_7102238360(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::backshield::set_reflector(param_1);
    return 0;
}

// 0x7102238550 — lua_bind forwarding wrapper, dispatches to beetle::set_grab
u64 FUN_7102238550(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::beetle::set_grab(param_1);
    return 0;
}

// 0x7102239370 — lua_bind forwarding wrapper, dispatches to clubshot::check_roll_up_area
u64 FUN_7102239370(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::clubshot::check_roll_up_area(param_1);
    return 0;
}

// 0x710223a064 — lua_bind forwarding wrapper, dispatches to dragoonsight::set_dragoonsight_effect
u64 FUN_710223a064(app::ItemModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::dragoonsight::set_dragoonsight_effect(param_1, param_3);
    return 0;
}

// 0x710223ad10 — lua_bind forwarding wrapper, dispatches to healball::fighter_heal
u64 FUN_710223ad10(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::healball::fighter_heal(param_1);
    return 0;
}

// 0x710223fc70 — lua_bind pass-through, dispatches to sandbag::homerun_contest_change_fly_camera
u32 FUN_710223fc70()
{
    app::sandbag::homerun_contest_change_fly_camera();
    return 0;
}

// 0x710223fc90 — lua_bind pass-through, dispatches to sandbag::homerun_contest_change_landing_camera
u32 FUN_710223fc90()
{
    app::sandbag::homerun_contest_change_landing_camera();
    return 0;
}

// 0x710223fcb0 — lua_bind pass-through, dispatches to sandbag::homerun_contest_change_timeup_fly_camera
u32 FUN_710223fcb0()
{
    app::sandbag::homerun_contest_change_timeup_fly_camera();
    return 0;
}

// 0x710223fcd0 — lua_bind pass-through, dispatches to sandbag::homerun_contest_change_normal_camera
u32 FUN_710223fcd0()
{
    app::sandbag::homerun_contest_change_normal_camera();
    return 0;
}

// 0x71022409e0 — lua_bind forwarding wrapper, dispatches to smashball::escape_from_fighter
u64 FUN_71022409e0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::smashball::escape_from_fighter(param_1);
    return 0;
}

// 0x7102240aa0 — lua_bind forwarding wrapper, dispatches to smashball::chase_fighter
u64 FUN_7102240aa0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::smashball::chase_fighter(param_1);
    return 0;
}

// 0x7102241d50 — lua_bind forwarding wrapper, dispatches to warpstar::clear_collision_info
u64 FUN_7102241d50(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::warpstar::clear_collision_info(param_1);
    return 0;
}

// 0x7102242a70 — lua_bind forwarding wrapper, dispatches to wood::free_log_group
u64 FUN_7102242a70(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::wood::free_log_group(param_1);
    return 0;
}

// 0x7102242bb0 — lua_bind forwarding wrapper, dispatches to androssshot::hit_check
u64 FUN_7102242bb0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::androssshot::hit_check(param_1);
    return 0;
}

// 0x7102243258 — lua_bind forwarding wrapper, passes bool via w8 to devil::set_camera_devil_mode
u64 FUN_7102243258(s64 param_1)
{
    bool in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::devil::set_camera_devil_mode(in_w8);
    return 0;
}

// 0x7102243368 — lua_bind forwarding wrapper, passes bool via w8 to devil::set_camera_devil_fix_mode
u64 FUN_7102243368(s64 param_1)
{
    bool in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::devil::set_camera_devil_fix_mode(in_w8);
    return 0;
}

// 0x71022438f0 — lua_bind forwarding wrapper, dispatches to ghirahim::set_shield
u64 FUN_71022438f0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::ghirahim::set_shield(param_1);
    return 0;
}

// 0x7102243e60 — lua_bind forwarding wrapper, dispatches to midna::throw_attack
u64 FUN_7102243e60(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::midna::throw_attack(param_1);
    return 0;
}

// 0x7102244924 — lua_bind forwarding wrapper, dispatches to nintendogshi::set_nintendogs_effect
u64 FUN_7102244924(app::ItemModuleAccessor *param_1, s64 param_2, bool param_3)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::nintendogshi::set_nintendogs_effect(param_1, param_3);
    return 0;
}

// 0x7102244ad0 — lua_bind forwarding wrapper, dispatches to riki::yorokobemo
u64 FUN_7102244ad0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::riki::yorokobemo(param_1);
    return 0;
}

// 0x7102244b90 — lua_bind forwarding wrapper, dispatches to riki::healdamo
u64 FUN_7102244b90(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::riki::healdamo(param_1);
    return 0;
}

// 0x7102244c50 — lua_bind forwarding wrapper, dispatches to riki::stealdamo
u64 FUN_7102244c50(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::riki::stealdamo(param_1);
    return 0;
}

// 0x71022451d8 — lua_bind forwarding wrapper, passes bool via w8 to tvgame::set_camera_devil_mode
u64 FUN_71022451d8(s64 param_1)
{
    bool in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::tvgame::set_camera_devil_mode(in_w8);
    return 0;
}

// 0x71022453f0 — lua_bind forwarding wrapper, dispatches to tvgame::set_reflector
u64 FUN_71022453f0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::tvgame::set_reflector(param_1);
    return 0;
}

// 0x71022456e8 — lua_bind forwarding wrapper, passes bool via w8 to tvgame::set_info_tv15_visible
u64 FUN_71022456e8(s64 param_1)
{
    bool in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::tvgame::set_info_tv15_visible(in_w8);
    return 0;
}

// 0x71022459c8 — lua_bind forwarding wrapper, passes bool via w8 to tvgameshot::info_tv15_set_visible
u64 FUN_71022459c8(s64 param_1)
{
    bool in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::tvgameshot::info_tv15_set_visible(in_w8);
    return 0;
}

// 0x7102246b80 — lua_bind forwarding wrapper, dispatches to meloettashot::ReflectOnViewFrame
u64 FUN_7102246b80(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::meloettashot::ReflectOnViewFrame(param_1);
    return 0;
}

// 0x7102247040 — lua_bind forwarding wrapper, dispatches to sirnight::set_reflector
u64 FUN_7102247040(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::sirnight::set_reflector(param_1);
    return 0;
}

// 0x7102247280 — lua_bind forwarding wrapper, dispatches to xerneas::powerup
u64 FUN_7102247280(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::xerneas::powerup(param_1);
    return 0;
}

// 0x71022475d0 — lua_bind forwarding wrapper, dispatches to zoroark::send_link_event_final_finish_pre
u64 FUN_71022475d0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::zoroark::send_link_event_final_finish_pre(param_1);
    return 0;
}

// 0x7102247940 — lua_bind forwarding wrapper, dispatches to starring::shoot
u64 FUN_7102247940(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::starring::shoot(param_1);
    return 0;
}

// 0x7102247af0 — lua_bind forwarding wrapper, dispatches to blackball::start_item_capture
u64 FUN_7102247af0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::blackball::start_item_capture(param_1);
    return 0;
}

// 0x7102247ca0 — lua_bind forwarding wrapper, dispatches to blackball::set_attack_offset_back_line_z
u64 FUN_7102247ca0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::blackball::set_attack_offset_back_line_z(param_1);
    return 0;
}

// 0x7102247d60 — lua_bind forwarding wrapper, dispatches to teamhealfield::heal_fighters
u64 FUN_7102247d60(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::teamhealfield::heal_fighters(param_1);
    return 0;
}

// 0x71022499b0 — lua_bind forwarding wrapper, dispatches to robinlift::set_clatter
u64 FUN_71022499b0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::robinlift::set_clatter(param_1);
    return 0;
}

// 0x7102249a70 — lua_bind forwarding wrapper, dispatches to cyborg::set_reflector
u64 FUN_7102249a70(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::cyborg::set_reflector(param_1);
    return 0;
}

// 0x7102249b30 — lua_bind forwarding wrapper, dispatches to guile::set_shield
u64 FUN_7102249b30(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::guile::set_shield(param_1);
    return 0;
}

// 0x710224b5e0 — lua_bind pass-through, dispatches to FUN_710160dea0
u32 FUN_710224b5e0()
{
    FUN_710160dea0();
    return 0;
}

// 0x710224c3d0 — lua_bind forwarding wrapper, dispatches to akira::set_all_shield
u64 FUN_710224c3d0(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::akira::set_all_shield(param_1);
    return 0;
}

// 0x710224c490 — lua_bind forwarding wrapper, dispatches to akira::set_bullet_shield
u64 FUN_710224c490(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::akira::set_bullet_shield(param_1);
    return 0;
}

// 0x710224d760 — lua_bind forwarding wrapper, dispatches to shovelknight::set_reflector
u64 FUN_710224d760(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::shovelknight::set_reflector(param_1);
    return 0;
}

// 0x710224e230 — lua_bind forwarding wrapper, dispatches to mimikkyu::set_captured_fighter_visibility_and_hit
u64 FUN_710224e230(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::mimikkyu::set_captured_fighter_visibility_and_hit(param_1);
    return 0;
}

// 0x7102251380 — lua_bind pass-through, dispatches to FUN_710160dea0
u32 FUN_7102251380()
{
    FUN_710160dea0();
    return 0;
}

// 0x7102252e00 — lua_bind forwarding wrapper, dispatches to sukapon::set_all_shield
u64 FUN_7102252e00(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::sukapon::set_all_shield(param_1);
    return 0;
}

// 0x7102252ec0 — lua_bind forwarding wrapper, dispatches to sukapon::set_bullet_shield
u64 FUN_7102252ec0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::sukapon::set_bullet_shield(param_1);
    return 0;
}

// 0x7102254220 — lua_bind forwarding wrapper, dispatches to springman::set_all_shield
u64 FUN_7102254220(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::springman::set_all_shield(param_1);
    return 0;
}

// 0x71022542e0 — lua_bind forwarding wrapper, dispatches to springman::set_bullet_shield
u64 FUN_71022542e0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::springman::set_bullet_shield(param_1);
    return 0;
}

// 0x7102256790 — lua_bind forwarding wrapper, dispatches to baitocrane::set_grab
u64 FUN_7102256790(app::BattleObjectModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::baitocrane::set_grab(param_1);
    return 0;
}

// 0x7102256b00 — lua_bind pass-through, dispatches to dracula2::notify_melee_start_to_hud_manager
u32 FUN_7102256b00()
{
    app::dracula2::notify_melee_start_to_hud_manager();
    return 0;
}

// 0x7102256d58 — lua_bind forwarding wrapper, passes bool via w8 to marx::fighter_visible
u64 FUN_7102256d58(s64 param_1)
{
    bool in_w8;
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::marx::fighter_visible(in_w8);
    return 0;
}

// 0x7102258b60 — lua_bind pass-through, dispatches to FUN_710160dea0
u32 FUN_7102258b60()
{
    FUN_710160dea0();
    return 0;
}

// 0x710226d400 — lua_bind forwarding wrapper, dispatches to pickelobject::update_collision_work
u64 FUN_710226d400(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::pickelobject::update_collision_work(param_1);
    return 0;
}

// 0x710226d4c0 — lua_bind forwarding wrapper, dispatches to pickelobject::set_material_visibility_mesh_all_invisible
u64 FUN_710226d4c0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::pickelobject::set_material_visibility_mesh_all_invisible(param_1);
    return 0;
}

// 0x710226e000 — lua_bind forwarding wrapper, dispatches to pickelobject::check_range_from_onwer
u64 FUN_710226e000(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::pickelobject::check_range_from_onwer(param_1);
    return 0;
}

// 0x710226e0c0 — lua_bind forwarding wrapper, dispatches to pickelobject::update_blink
u64 FUN_710226e0c0(app::ItemModuleAccessor *param_1, s64 param_2)
{
    u64 in_x10;
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    *(u64 *)(param_2 + 0x10) = in_x10;
    app::pickelobject::update_blink(param_1);
    return 0;
}
