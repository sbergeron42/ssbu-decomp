#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102-0x7103 address range, batch e2-001
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

struct BattleObjectModuleAccessor;
struct Fighter;
struct Weapon;
struct FighterModuleAccessor;

[[noreturn]] extern "C" void abort();
extern "C" void playVoiceWakeup_71006eafb0(u64);

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


// ---- lua_bind wrappers (32 bytes each) -----------------------------------------------
// Pattern: str x10,[x0,#0x10]; mov x0,x8; bl <func>; mov w0,wzr
// x0 = lua state buffer (param_1), x8 = typed object (in_x8, implicit register param)

// 0x71020c6750 — load sound module ptr via x9, call playVoiceWakeup_71006eafb0 (32 bytes)
// Note: x9 holds the module accessor; loads sound ptr at +0x148
u32 FUN_71020c6750(s64 *param_1)
{
    register u64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)((char *)param_1 + 0x10) = in_x10;
    playVoiceWakeup_71006eafb0(*(u64 *)(in_x9 + 0x148));
    return 0;
}

// 0x7102163c70 — WeaponSpecializer_SnakeC4::detach_constraint(Weapon*, bool) (32 bytes)
