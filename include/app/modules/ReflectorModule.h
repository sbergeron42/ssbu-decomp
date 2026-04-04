#pragma once
#include "types.h"

namespace app {

// ReflectorModule — accessed at BattleObjectModuleAccessor+0x108
// Manages reflector hitboxes (shield reflectors on fighters/items).
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x50-0x1d0).
struct ReflectorModule {
    void** _vt;

    // -- Cleanup (0x50) -- [confirmed: lua_bind API names]
    void clean() { ((void(*)(ReflectorModule*))_vt[0x50/8])(this); }

    // -- Shield/size/status (0x88-0xa0) --
    bool is_shield(u64 p1, u64 p2) { return ((bool(*)(ReflectorModule*,u64,u64))_vt[0x88/8])(this,p1,p2); }
    void set_size(u64 p1, u64 p2) { ((void(*)(ReflectorModule*,u64,u64))_vt[0x90/8])(this,p1,p2); }
    void set_status(u64 p1, u64 p2, u64 p3) { ((void(*)(ReflectorModule*,u64,u64,u64))_vt[0x98/8])(this,p1,p2,p3); }
    void set_status_all(u64 p1, u64 p2) { ((void(*)(ReflectorModule*,u64,u64))_vt[0xa0/8])(this,p1,p2); }

    // -- Turn/front/hop queries (0xa8-0xc8) --
    bool is_turn(u64 p1) { return ((bool(*)(ReflectorModule*,u64))_vt[0xa8/8])(this,p1); }
    bool is_front(u64 p1) { return ((bool(*)(ReflectorModule*,u64))_vt[0xb0/8])(this,p1); }
    bool is_hop(u64 p1) { return ((bool(*)(ReflectorModule*,u64))_vt[0xb8/8])(this,p1); }
    void* get_hop_angle(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0xc0/8])(this,p1); }
    bool is_no_hop(u64 p1) { return ((bool(*)(ReflectorModule*,u64))_vt[0xc8/8])(this,p1); }

    // -- Turn/front/hop setters (0xd0-0xe0) --
    void set_turn(bool p1, u64 p2) { ((void(*)(ReflectorModule*,bool,u64))_vt[0xd0/8])(this,p1,p2); }
    void set_front(u64 p1, u64 p2) { ((void(*)(ReflectorModule*,u64,u64))_vt[0xd8/8])(this,p1,p2); }
    void set_hop(bool p1, u64 p2) { ((void(*)(ReflectorModule*,bool,u64))_vt[0xe0/8])(this,p1,p2); }

    // -- Multipliers (0xe8-0x130) --
    void set_attack_mul(u64 p1) { ((void(*)(ReflectorModule*,u64))_vt[0xe8/8])(this,p1); }
    void* get_attack_mul(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0xf0/8])(this,p1); }
    void set_speed_mul(u64 p1) { ((void(*)(ReflectorModule*,u64))_vt[0xf8/8])(this,p1); }
    void* get_speed_mul(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0x100/8])(this,p1); }
    void set_life_mul(u64 p1) { ((void(*)(ReflectorModule*,u64))_vt[0x108/8])(this,p1); }
    void* get_life_mul(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0x110/8])(this,p1); }
    void set_attack_limit(u64 p1) { ((void(*)(ReflectorModule*,u64))_vt[0x118/8])(this,p1); }
    void* get_attack_limit(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0x120/8])(this,p1); }
    void set_hit_stop_mul() { ((void(*)(ReflectorModule*))_vt[0x130/8])(this); }

    // -- State queries (0x140-0x158) --
    bool is_no_m_ball(u64 p1) { return ((bool(*)(ReflectorModule*,u64))_vt[0x140/8])(this,p1); }
    void* get_part_size(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0x148/8])(this,p1); }
    u32 get_team_no() { return ((u32(*)(ReflectorModule*))_vt[0x150/8])(this); }
    void set_no_team(bool p1) { ((void(*)(ReflectorModule*,bool))_vt[0x158/8])(this,p1); }

    // -- Shield type (0x160) --
    void set_shield_type(u64 p1, u64 p2, u64 p3) { ((void(*)(ReflectorModule*,u64,u64,u64))_vt[0x160/8])(this,p1,p2,p3); }

    // -- Clear (0x188-0x190) --
    void clear_all() { ((void(*)(ReflectorModule*))_vt[0x188/8])(this); }
    void clear_all_2(u64 p1) { ((void(*)(ReflectorModule*,u64))_vt[0x190/8])(this,p1); }

    // -- Position/LR (0x198-0x1b8) --
    void* get_center_pos(u64 p1, u64 p2) { return ((void*(*)(ReflectorModule*,u64,u64))_vt[0x198/8])(this,p1,p2); }
    void* get_lr(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0x1a0/8])(this,p1); }
    u32 get_group_num() { return ((u32(*)(ReflectorModule*))_vt[0x1a8/8])(this); }
    void* get_pos_x(u64 p1) { return ((void*(*)(ReflectorModule*,u64))_vt[0x1b0/8])(this,p1); }
    void set_target_property(u64 p1, u64 p2) { ((void(*)(ReflectorModule*,u64,u64))_vt[0x1b8/8])(this,p1,p2); }

    // -- Target/sleep (0x1c0-0x1d0) --
    void set_target_category(u64 p1, u64 p2) { ((void(*)(ReflectorModule*,u64,u64))_vt[0x1c0/8])(this,p1,p2); }
    void sleep(bool p1) { ((void(*)(ReflectorModule*,bool))_vt[0x1d0/8])(this,p1); }
};

} // namespace app
