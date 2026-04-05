#pragma once
#include "types.h"

namespace app {

// GrabModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::GrabModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x158
struct GrabModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void clear_all() { ((void(*)(GrabModule*))_vt[0x50/8])(this); }
    void clear(u64 p1) { ((void(*)(GrabModule*,u64))_vt[0x58/8])(this,p1); }
    void set_constraint(u64 p1, bool p2) { ((void(*)(GrabModule*,u64,bool))_vt[0x70/8])(this,p1,p2); }
    bool is_grab(u64 p1) { return ((bool(*)(GrabModule*,u64))_vt[0x78/8])(this,p1); }
    void* size(u64 p1) { return ((void*(*)(GrabModule*,u64))_vt[0x80/8])(this,p1); }
    void set_size(u64 p1) { ((void(*)(GrabModule*,u64))_vt[0x88/8])(this,p1); }
    f32 pos_x() { return ((f32(*)(GrabModule*))_vt[0x90/8])(this); }
    void* center_pos(u64 p1) { return ((void*(*)(GrabModule*,u64))_vt[0x98/8])(this,p1); }
    void* node(u64 p1) { return ((void*(*)(GrabModule*,u64))_vt[0xA8/8])(this,p1); }
    void set_power_up() { ((void(*)(GrabModule*))_vt[0xb0/8])(this); }
    void set_size_mul() { ((void(*)(GrabModule*))_vt[0xb8/8])(this); }
    void set_scale_2nd() { ((void(*)(GrabModule*))_vt[0xc0/8])(this); }
    void sleep(bool p1) { ((void(*)(GrabModule*,bool))_vt[0xe0/8])(this,p1); }
    void relocate(u64 p1) { ((void(*)(GrabModule*,u64))_vt[0xF0/8])(this,p1); }
    void set_check_front(bool p1) { ((void(*)(GrabModule*,bool))_vt[0xF8/8])(this,p1); }
    void set_rebound(bool p1) { ((void(*)(GrabModule*,bool))_vt[0x100/8])(this,p1); }
    bool is_rebound() { return ((bool(*)(GrabModule*))_vt[0x108/8])(this); }
    bool check_rebound(u64 p1) { return ((bool(*)(GrabModule*,u64))_vt[0x120/8])(this,p1); }
    void disable_sub_fighter() { ((void(*)(GrabModule*))_vt[0x128/8])(this); }
};

} // namespace app
