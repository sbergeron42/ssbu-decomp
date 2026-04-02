#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-003
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

struct BattleObjectModuleAccessor;
struct ItemModuleAccessor;

extern "C" void FUN_710160dea0();

namespace app {
    namespace item_collision_manager {
        void disable_ground_collision(s64 *);
    }
    namespace item_hud {
        void del_cursor(s64 *);
    }
    namespace beetle {
        void set_grab(BattleObjectModuleAccessor *);
    }
    namespace sandbag {
        void homerun_contest_change_fly_camera();
        void homerun_contest_change_landing_camera();
        void homerun_contest_change_timeup_fly_camera();
        void homerun_contest_change_normal_camera();
    }
    namespace smashball {
        void chase_fighter(ItemModuleAccessor *);
    }
    namespace androssshot {
        void hit_check(ItemModuleAccessor *);
    }
    namespace ghirahim {
        void set_shield(ItemModuleAccessor *);
    }
    namespace tvgame {
        void set_reflector(ItemModuleAccessor *);
    }
    namespace meloettashot {
        void ReflectOnViewFrame(ItemModuleAccessor *);
    }
    namespace sirnight {
        void set_reflector(ItemModuleAccessor *);
    }
    namespace xerneas {
        void powerup(ItemModuleAccessor *);
    }
    namespace zoroark {
        void send_link_event_final_finish_pre(ItemModuleAccessor *);
    }
    namespace starring {
        void shoot(ItemModuleAccessor *);
    }
    namespace blackball {
        void start_item_capture(ItemModuleAccessor *);
    }
    namespace akira {
        void set_bullet_shield(BattleObjectModuleAccessor *);
    }
    namespace shovelknight {
        void set_reflector(BattleObjectModuleAccessor *);
    }
    namespace mimikkyu {
        void set_captured_fighter_visibility_and_hit(ItemModuleAccessor *);
    }
    namespace sukapon {
        void set_bullet_shield(ItemModuleAccessor *);
    }
    namespace springman {
        void set_bullet_shield(ItemModuleAccessor *);
    }
    namespace baitocrane {
        void set_grab(BattleObjectModuleAccessor *);
    }
    namespace dracula2 {
        void notify_melee_start_to_hud_manager();
    }
    namespace pickelobject {
        void set_material_visibility_mesh_all_invisible(ItemModuleAccessor *);
    }
}

// ---- direct lua_State* pass-through wrappers (24 bytes each) -----------------------------------------------
// Pattern: stp; mov x29; bl func(x0=param_1); mov w0,wzr; ldp; ret

// 0x710220bf50 — item_collision_manager::disable_ground_collision (24 bytes)
u32 FUN_710220bf50(s64 *param_1)
{
    app::item_collision_manager::disable_ground_collision(param_1);
    return 0;
}

// 0x710220c280 — item_hud::del_cursor (24 bytes)
u32 FUN_710220c280(s64 *param_1)
{
    app::item_hud::del_cursor(param_1);
    return 0;
}

// ---- lua_bind wrappers (32 bytes each) -----------------------------------------------
// Pattern: str x10,[x0,#0x10]; mov x0,x8; bl <func>; mov w0,wzr
// x0 = lua state buffer (param_1), x8 = typed object (in_x8, implicit register param)

// 0x7102238550 — beetle::set_grab (32 bytes)
u32 FUN_7102238550(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::beetle::set_grab(in_x8);
    return 0;
}

// ---- no-arg wrappers (24 bytes each) -----------------------------------------------
// Pattern: stp; mov x29; bl func(); mov w0,wzr; ldp; ret

// 0x710223fc70 — sandbag::homerun_contest_change_fly_camera (24 bytes)
u32 FUN_710223fc70(void)
{
    app::sandbag::homerun_contest_change_fly_camera();
    return 0;
}

// 0x710223fc90 — sandbag::homerun_contest_change_landing_camera (24 bytes)
u32 FUN_710223fc90(void)
{
    app::sandbag::homerun_contest_change_landing_camera();
    return 0;
}

// 0x710223fcb0 — sandbag::homerun_contest_change_timeup_fly_camera (24 bytes)
u32 FUN_710223fcb0(void)
{
    app::sandbag::homerun_contest_change_timeup_fly_camera();
    return 0;
}

// 0x710223fcd0 — sandbag::homerun_contest_change_normal_camera (24 bytes)
u32 FUN_710223fcd0(void)
{
    app::sandbag::homerun_contest_change_normal_camera();
    return 0;
}

// ---- lua_bind wrappers (32 bytes) — ItemModuleAccessor via x8 -----------------------------------------------

// 0x7102240aa0 — smashball::chase_fighter (32 bytes)
u32 FUN_7102240aa0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::smashball::chase_fighter(in_x8);
    return 0;
}

// 0x7102242bb0 — androssshot::hit_check (32 bytes)
u32 FUN_7102242bb0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::androssshot::hit_check(in_x8);
    return 0;
}

// 0x71022438f0 — ghirahim::set_shield (32 bytes)
u32 FUN_71022438f0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::ghirahim::set_shield(in_x8);
    return 0;
}

// 0x71022453f0 — tvgame::set_reflector (32 bytes)
u32 FUN_71022453f0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::tvgame::set_reflector(in_x8);
    return 0;
}

// 0x7102246b80 — meloettashot::ReflectOnViewFrame (32 bytes)
u32 FUN_7102246b80(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::meloettashot::ReflectOnViewFrame(in_x8);
    return 0;
}

// 0x7102247040 — sirnight::set_reflector (32 bytes)
u32 FUN_7102247040(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::sirnight::set_reflector(in_x8);
    return 0;
}

// 0x7102247280 — xerneas::powerup (32 bytes)
u32 FUN_7102247280(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::xerneas::powerup(in_x8);
    return 0;
}

// 0x71022475d0 — zoroark::send_link_event_final_finish_pre (32 bytes)
u32 FUN_71022475d0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::zoroark::send_link_event_final_finish_pre(in_x8);
    return 0;
}

// 0x7102247940 — starring::shoot (32 bytes)
u32 FUN_7102247940(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::starring::shoot(in_x8);
    return 0;
}

// 0x7102247af0 — blackball::start_item_capture (32 bytes)
u32 FUN_7102247af0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::blackball::start_item_capture(in_x8);
    return 0;
}

// 0x710224c490 — akira::set_bullet_shield (32 bytes)
u32 FUN_710224c490(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::akira::set_bullet_shield(in_x8);
    return 0;
}

// 0x710224d760 — shovelknight::set_reflector (32 bytes)
u32 FUN_710224d760(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::shovelknight::set_reflector(in_x8);
    return 0;
}

// 0x710224e230 — mimikkyu::set_captured_fighter_visibility_and_hit (32 bytes)
u32 FUN_710224e230(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::mimikkyu::set_captured_fighter_visibility_and_hit(in_x8);
    return 0;
}

// 0x7102251380 — no-arg: calls FUN_710160dea0 (24 bytes)
u32 FUN_7102251380(void)
{
    FUN_710160dea0();
    return 0;
}

// 0x7102252ec0 — sukapon::set_bullet_shield (32 bytes)
u32 FUN_7102252ec0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::sukapon::set_bullet_shield(in_x8);
    return 0;
}

// 0x71022542e0 — springman::set_bullet_shield (32 bytes)
u32 FUN_71022542e0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::springman::set_bullet_shield(in_x8);
    return 0;
}

// 0x7102256790 — baitocrane::set_grab (32 bytes)
u32 FUN_7102256790(s64 *param_1, s64 param_2)
{
    register BattleObjectModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::baitocrane::set_grab(in_x8);
    return 0;
}

// 0x7102256b00 — dracula2::notify_melee_start_to_hud_manager (24 bytes)
u32 FUN_7102256b00(void)
{
    app::dracula2::notify_melee_start_to_hud_manager();
    return 0;
}

// 0x710226d4c0 — pickelobject::set_material_visibility_mesh_all_invisible (32 bytes)
u32 FUN_710226d4c0(s64 *param_1, s64 param_2)
{
    register ItemModuleAccessor *in_x8 asm("x8");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x8));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    app::pickelobject::set_material_visibility_mesh_all_invisible(in_x8);
    return 0;
}
