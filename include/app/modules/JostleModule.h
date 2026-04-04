#pragma once
#include "types.h"

namespace app {

// JostleModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// Module accessed via BattleObjectModuleAccessor +0x118
struct JostleModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void set_status(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x48/8])(this,p1); }
    void set_layer(u64 p1) { ((void(*)(JostleModule*,u64))_vt[0x50/8])(this,p1); }
    void set_fix(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x58/8])(this,p1); }
    void set_ignore_speed_x(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x60/8])(this,p1); }
    void sleep(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x68/8])(this,p1); }
    bool is_sleep() { return ((bool(*)(JostleModule*))_vt[0x70/8])(this); }
    f32 jostle_speed_x() { return ((f32(*)(JostleModule*))_vt[0x80/8])(this); }
    f32 speed_attenuation_rate() { return ((f32(*)(JostleModule*))_vt[0x98/8])(this); }
    void* target_weight() { return ((void*(*)(JostleModule*))_vt[0xa0/8])(this); }
    f32 pos_z() { return ((f32(*)(JostleModule*))_vt[0xA8/8])(this); }
    void set_refer(bool p1) { ((void(*)(JostleModule*,bool))_vt[0xb0/8])(this,p1); }
    void set_push_speed_x(bool p1) { ((void(*)(JostleModule*,bool))_vt[0xb8/8])(this,p1); }
    void set_push_speed_x_2(u64 p1, bool p2) { ((void(*)(JostleModule*,u64,bool))_vt[0xc0/8])(this,p1,p2); }
    void set_priority(u64 p1) { ((void(*)(JostleModule*,u64))_vt[0xc8/8])(this,p1); }
    u32 priority() { return ((u32(*)(JostleModule*))_vt[0xD0/8])(this); }
    void set_force_gap(u64 p1) { ((void(*)(JostleModule*,u64))_vt[0xE0/8])(this,p1); }
    void set_ignore_owner_id(u64 p1) { ((void(*)(JostleModule*,u64))_vt[0xe8/8])(this,p1); }
    void* ignore_owner_id() { return ((void*(*)(JostleModule*))_vt[0xf0/8])(this); }
    void reset_area() { ((void(*)(JostleModule*))_vt[0xF8/8])(this); }
    void overlap_x(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x100/8])(this,p1); }
    void set_ignore_pri(u64 p1) { ((void(*)(JostleModule*,u64))_vt[0x108/8])(this,p1); }
    void set_push_speed_x_overlap_rate() { ((void(*)(JostleModule*))_vt[0x110/8])(this); }
    void set_push_speed_x_overlap_rate_status() { ((void(*)(JostleModule*))_vt[0x118/8])(this); }
    u32 area_kind() { return ((u32(*)(JostleModule*))_vt[0x120/8])(this); }
    f32 weight() { return ((f32(*)(JostleModule*))_vt[0x128/8])(this); }
    void set_weight() { ((void(*)(JostleModule*))_vt[0x130/8])(this); }
    void set_influence_opponent_weight(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x138/8])(this,p1); }
    void set_propagate_push_speed(bool p1) { ((void(*)(JostleModule*,bool))_vt[0x140/8])(this,p1); }
    void set_overlap_rate_mul() { ((void(*)(JostleModule*))_vt[0x158/8])(this); }
    void set_team(u64 p1) { ((void(*)(JostleModule*,u64))_vt[0x160/8])(this,p1); }
};

} // namespace app
