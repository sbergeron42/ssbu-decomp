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

// 0x71021ba7c0 — FighterSpecializer_Buddy::update_special_n_partner_motion(Fighter*, s64) (32 bytes)
// 0x71021ff230 — item::apply_powerup_attr: direct lua_State* pass-through (24 bytes)
