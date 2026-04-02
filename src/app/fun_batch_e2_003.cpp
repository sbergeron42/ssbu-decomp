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

// ---- lua_bind wrappers (32 bytes each) -----------------------------------------------
// Pattern: str x10,[x0,#0x10]; mov x0,x8; bl <func>; mov w0,wzr
// x0 = lua state buffer (param_1), x8 = typed object (in_x8, implicit register param)

// ---- no-arg wrappers (24 bytes each) -----------------------------------------------
// Pattern: stp; mov x29; bl func(); mov w0,wzr; ldp; ret

// FUN_710223fc70, FUN_710223fc90 — compiled in fun_batch_c_011.cpp

// FUN_710223fcb0, FUN_710223fcd0 — compiled in fun_batch_c_011.cpp

// ---- lua_bind wrappers (32 bytes) — ItemModuleAccessor via x8 -----------------------------------------------

