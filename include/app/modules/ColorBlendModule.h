#pragma once
#include "types.h"

namespace app {

// ColorBlendModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::ColorBlendModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x70
struct ColorBlendModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void off_flash(bool p1) { ((void(*)(ColorBlendModule*,bool))_vt[0x80/8])(this,p1); }
    void set_enable_flash(bool p1) { ((void(*)(ColorBlendModule*,bool))_vt[0x88/8])(this,p1); }
    void set_burn_color(u64 p1, bool p2) { ((void(*)(ColorBlendModule*,u64,bool))_vt[0x90/8])(this,p1,p2); }
    void set_burn_color_frame(u64 p1, bool p2) { ((void(*)(ColorBlendModule*,u64,bool))_vt[0x98/8])(this,p1,p2); }
    void off_burn_color(bool p1) { ((void(*)(ColorBlendModule*,bool))_vt[0xa0/8])(this,p1); }
    void set_burn_color_priority(u64 p1, bool p2) { ((void(*)(ColorBlendModule*,u64,bool))_vt[0xa8/8])(this,p1,p2); }
    void set_priority(u64 p1, bool p2) { ((void(*)(ColorBlendModule*,u64,bool))_vt[0xc8/8])(this,p1,p2); }
    void set_shadow_bloom(bool p1) { ((void(*)(ColorBlendModule*,bool))_vt[0xd8/8])(this,p1); }
    void set_last_attack_direction(u64 p1) { ((void(*)(ColorBlendModule*,u64))_vt[0xe0/8])(this,p1); }
    void set_main_color(u64 p1, u64 p2, u64 p3, bool p4) { ((void(*)(ColorBlendModule*,u64,u64,u64,bool))_vt[0xf8/8])(this,p1,p2,p3,p4); }
    void cancel_main_color(u64 p1) { ((void(*)(ColorBlendModule*,u64))_vt[0x100/8])(this,p1); }
    void set_status(bool p1) { ((void(*)(ColorBlendModule*,bool))_vt[0x168/8])(this,p1); }
    s32 get_status() { return ((s32(*)(ColorBlendModule*))_vt[0x170/8])(this); }
    void set_disable_camera_depth_influence(bool p1) { ((void(*)(ColorBlendModule*,bool))_vt[0x1b0/8])(this,p1); }
};

} // namespace app
