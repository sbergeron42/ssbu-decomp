#pragma once
#include "types.h"

namespace app {

// CatchModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::CatchModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x120
struct CatchModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void set_catch(u64 p1) { ((void(*)(CatchModule*,u64))_vt[0x58/8])(this,p1); }
    bool is_catch() { return ((bool(*)(CatchModule*))_vt[0x60/8])(this); }
    void catch_cut(bool p1, bool p2) { ((void(*)(CatchModule*,bool,bool))_vt[0x90/8])(this,p1,p2); }
    void update_pos_cling() { ((void(*)(CatchModule*))_vt[0x98/8])(this); }
    void cling_cut(bool p1) { ((void(*)(CatchModule*,bool))_vt[0xa8/8])(this,p1); }
    void check_damage() { ((void(*)(CatchModule*))_vt[0xb0/8])(this); }
    void set_send_cut_event(bool p1) { ((void(*)(CatchModule*,bool))_vt[0xb8/8])(this,p1); }
    u32 capture_object_id(bool p1) { return ((u32(*)(CatchModule*,bool))_vt[0xe0/8])(this,p1); }
    f32 capture_pos_x_diff() { return ((f32(*)(CatchModule*))_vt[0xf0/8])(this); }
};

} // namespace app
