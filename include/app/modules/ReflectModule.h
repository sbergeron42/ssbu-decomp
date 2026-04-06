#pragma once
#include "types.h"

namespace app {

// ReflectModule — accessed at BattleObjectModuleAccessor+0xF8
// Manages projectile reflection properties (attack/speed/life multipliers).
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x50-0xe0).
// All method names derived from .dynsym lua_bind::ReflectModule__*_impl dispatcher analysis.
struct ReflectModule {
    void** _vt;

    // -- Info management (0x50) -- [confirmed: lua_bind API names]
    void reset_info() { ((void(*)(ReflectModule*))_vt[0x50/8])(this); }

    // -- Object/team identity (0x58-0x70) --
    // [inferred: returns u64 to preserve tail-call in lua_bind wrapper; underlying value is object ID]
    u64 object_id() { return ((u64(*)(ReflectModule*))_vt[0x58/8])(this); }
    void set_object_id(u64 p1) { ((void(*)(ReflectModule*,u64))_vt[0x60/8])(this,p1); }
    // [inferred: returns u64 to preserve tail-call in lua_bind wrapper; underlying value is team number]
    u64 team_no() { return ((u64(*)(ReflectModule*))_vt[0x68/8])(this); }
    void set_team_no(u64 p1) { ((void(*)(ReflectModule*,u64))_vt[0x70/8])(this,p1); }

    // -- Multipliers (0x78-0xa0) --
    f32 attack_mul() { return ((f32(*)(ReflectModule*))_vt[0x78/8])(this); }
    void set_attack_mul() { ((void(*)(ReflectModule*))_vt[0x80/8])(this); }
    f32 speed_mul() { return ((f32(*)(ReflectModule*))_vt[0x88/8])(this); }
    void set_speed_mul() { ((void(*)(ReflectModule*))_vt[0x90/8])(this); }
    f32 life_mul() { return ((f32(*)(ReflectModule*))_vt[0x98/8])(this); }
    void set_life_mul() { ((void(*)(ReflectModule*))_vt[0xa0/8])(this); }

    // -- State queries (0xa8-0xc0) --
    bool is_reflect() { return ((bool(*)(ReflectModule*))_vt[0xa8/8])(this); }
    void set_no_speed_mul(bool p1) { ((void(*)(ReflectModule*,bool))_vt[0xb0/8])(this,p1); }
    bool is_count_max() { return ((bool(*)(ReflectModule*))_vt[0xb8/8])(this); }
    u32 count() { return ((u32(*)(ReflectModule*))_vt[0xc0/8])(this); }

    // -- Misc (0xd8-0xe0) --
    f32 get_reverse_lr() { return ((f32(*)(ReflectModule*))_vt[0xd8/8])(this); }
    void set_collision_no(u64 p1) { ((void(*)(ReflectModule*,u64))_vt[0xe0/8])(this,p1); }
};

} // namespace app
