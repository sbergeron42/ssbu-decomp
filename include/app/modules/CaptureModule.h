#pragma once
#include "types.h"

namespace app {

// CaptureModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::CaptureModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x138
struct CaptureModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void set_nodes(u64 p1, u64 p2) { ((void(*)(CaptureModule*,u64,u64))_vt[0x48/8])(this,p1,p2); }
    bool is_thrown_finish() { return ((bool(*)(CaptureModule*))_vt[0x50/8])(this); }
    void set_ignore_object_id(u64 p1) { ((void(*)(CaptureModule*,u64))_vt[0x58/8])(this,p1); }
    bool is_capture() { return ((bool(*)(CaptureModule*))_vt[0x68/8])(this); }
    u32 catch_object_id() { return ((u32(*)(CaptureModule*))_vt[0x70/8])(this); }
    void* capture(u64 p1, u64 p2, bool p3, u64 p4) { return ((void*(*)(CaptureModule*,u64,u64,bool,u64))_vt[0x78/8])(this,p1,p2,p3,p4); }
    void* capture_2(u64 p1, u64 p2, u64 p3, bool p4, u64 p5) { return ((void*(*)(CaptureModule*,u64,u64,u64,bool,u64))_vt[0x80/8])(this,p1,p2,p3,p4,p5); }
    bool is_catch_hit_stop() { return ((bool(*)(CaptureModule*))_vt[0x88/8])(this); }
    void node_offset(bool p1) { ((void(*)(CaptureModule*,bool))_vt[0x90/8])(this,p1); }
    f32 catch_pos_y() { return ((f32(*)(CaptureModule*))_vt[0x98/8])(this); }
    void capture_cut(bool p1, bool p2, bool p3) { ((void(*)(CaptureModule*,bool,bool,bool))_vt[0xa0/8])(this,p1,p2,p3); }
    void* check_damage(u64 p1) { return ((void*(*)(CaptureModule*,u64))_vt[0xa8/8])(this,p1); }
    void check_damage_thrown() { ((void(*)(CaptureModule*))_vt[0xb0/8])(this); }
    void* thrown() { return ((void*(*)(CaptureModule*))_vt[0xb8/8])(this); }
    bool is_thrown() { return ((bool(*)(CaptureModule*))_vt[0xc0/8])(this); }
    void update_pos_thrown() { ((void(*)(CaptureModule*))_vt[0xc8/8])(this); }
    void update_lr_thrown() { ((void(*)(CaptureModule*))_vt[0xd0/8])(this); }
    void thrown_cut(bool p1, bool p2) { ((void(*)(CaptureModule*,bool,bool))_vt[0xd8/8])(this,p1,p2); }
    void set_send_cut_event(bool p1) { ((void(*)(CaptureModule*,bool))_vt[0xe8/8])(this,p1); }
    void set_update_pos(bool p1) { ((void(*)(CaptureModule*,bool))_vt[0xf8/8])(this,p1); }
    bool is_reaction() { return ((bool(*)(CaptureModule*))_vt[0x100/8])(this); }
    u32 motion_offset() { return ((u32(*)(CaptureModule*))_vt[0x108/8])(this); }
    u32 motion_offset_lw() { return ((u32(*)(CaptureModule*))_vt[0x110/8])(this); }
    void* motion(u64 p1, u64 p2) { return ((void*(*)(CaptureModule*,u64,u64))_vt[0x118/8])(this,p1,p2); }
    void* motion_lw(u64 p1, u64 p2) { return ((void*(*)(CaptureModule*,u64,u64))_vt[0x120/8])(this,p1,p2); }
    void* motion_offset_lw_2(u64 p1) { return ((void*(*)(CaptureModule*,u64))_vt[0x128/8])(this,p1); }
    void set_ignore_catching(bool p1) { ((void(*)(CaptureModule*,bool))_vt[0x130/8])(this,p1); }
    bool is_ignore_catching() { return ((bool(*)(CaptureModule*))_vt[0x138/8])(this); }
    bool is_motion_hi_lw() { return ((bool(*)(CaptureModule*))_vt[0x140/8])(this); }
    bool is_ignore_distance() { return ((bool(*)(CaptureModule*))_vt[0x148/8])(this); }
    u32 capture_node() { return ((u32(*)(CaptureModule*))_vt[0x150/8])(this); }
    void set_capture_node_offset(u64 p1) { ((void(*)(CaptureModule*,u64))_vt[0x158/8])(this,p1); }
    u32 capture_node_value() { return ((u32(*)(CaptureModule*))_vt[0x160/8])(this); }
    void update_node_pos() { ((void(*)(CaptureModule*))_vt[0x168/8])(this); }
    f32 catch_node_pos_y() { return ((f32(*)(CaptureModule*))_vt[0x170/8])(this); }
    f32 capture_to_catch_node_pos_diff() { return ((f32(*)(CaptureModule*))_vt[0x178/8])(this); }
};

} // namespace app
