#pragma once
#include "types.h"

namespace app {

// ModelModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// Module accessed via BattleObjectModuleAccessor +0x78
struct ModelModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void set_rotation_order(u64 p1) { ((void(*)(ModelModule*,u64))_vt[0xe0/8])(this,p1); }
    u32 rotation_order() { return ((u32(*)(ModelModule*))_vt[0xE8/8])(this); }
    void* scale() { return ((void*(*)(ModelModule*))_vt[0xF0/8])(this); }
    void set_scale() { ((void(*)(ModelModule*))_vt[0xf8/8])(this); }
    f32 scale_z() { return ((f32(*)(ModelModule*))_vt[0x100/8])(this); }
    void set_scale_z() { ((void(*)(ModelModule*))_vt[0x108/8])(this); }
    void set_temporary_scale_z() { ((void(*)(ModelModule*))_vt[0x110/8])(this); }
    void* joint_global_position(u64 p1, u64 p2, bool p3) { return ((void*(*)(ModelModule*,u64,u64,bool))_vt[0x150/8])(this,p1,p2,p3); }
    void* joint_global_position_with_offset(u64 p1, u64 p2, u64 p3, bool p4) { return ((void*(*)(ModelModule*,u64,u64,u64,bool))_vt[0x158/8])(this,p1,p2,p3,p4); }
    void* joint_global_offset_from_top(u64 p1, u64 p2) { return ((void*(*)(ModelModule*,u64,u64))_vt[0x170/8])(this,p1,p2); }
    void* top_joint_global_position_from_joint(u64 p1, u64 p2, u64 p3) { return ((void*(*)(ModelModule*,u64,u64,u64))_vt[0x178/8])(this,p1,p2,p3); }
    void* joint_global_rotation(u64 p1, u64 p2, bool p3) { return ((void*(*)(ModelModule*,u64,u64,bool))_vt[0x180/8])(this,p1,p2,p3); }
    void* joint_global_axis(u64 p1, u64 p2, bool p3) { return ((void*(*)(ModelModule*,u64,u64,bool))_vt[0x188/8])(this,p1,p2,p3); }
    void set_joint_srt(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(ModelModule*,u64,u64,u64,u64))_vt[0x190/8])(this,p1,p2,p3,p4); }
    void set_joint_scale(u64 p1, u64 p2) { ((void(*)(ModelModule*,u64,u64))_vt[0x198/8])(this,p1,p2); }
    void set_joint_rotate(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(ModelModule*,u64,u64,u64,u64))_vt[0x1a0/8])(this,p1,p2,p3,p4); }
    void set_joint_translate(u64 p1, u64 p2, bool p3, bool p4) { ((void(*)(ModelModule*,u64,u64,bool,bool))_vt[0x1a8/8])(this,p1,p2,p3,p4); }
    void clear_joint_srt(u64 p1) { ((void(*)(ModelModule*,u64))_vt[0x1B0/8])(this,p1); }
    void* joint_rotate(u64 p1, u64 p2) { return ((void*(*)(ModelModule*,u64,u64))_vt[0x1b8/8])(this,p1,p2); }
    void set_visibility(bool p1) { ((void(*)(ModelModule*,bool))_vt[0x1c0/8])(this,p1); }
    bool is_visible() { return ((bool(*)(ModelModule*))_vt[0x1C8/8])(this); }
    void set_mesh_visibility(u64 p1, bool p2) { ((void(*)(ModelModule*,u64,bool))_vt[0x1d0/8])(this,p1,p2); }
    void set_alpha() { ((void(*)(ModelModule*))_vt[0x1f0/8])(this); }
    void set_color_rgb(u64 p1) { ((void(*)(ModelModule*,u64))_vt[0x1F8/8])(this,p1); }
    void set_emmisive_scale() { ((void(*)(ModelModule*))_vt[0x258/8])(this); }
    void set_render_offset_position(u64 p1) { ((void(*)(ModelModule*,u64))_vt[0x2d8/8])(this,p1); }
    void set_depth_offset() { ((void(*)(ModelModule*))_vt[0x2e8/8])(this); }
    void set_depth_stencil(u64 p1) { ((void(*)(ModelModule*,u64))_vt[0x2f0/8])(this,p1); }
    void* virtual_joint_tra(u64 p1) { return ((void*(*)(ModelModule*,u64))_vt[0x328/8])(this,p1); }
    void enable_gold_eye() { ((void(*)(ModelModule*))_vt[0x358/8])(this); }
    void disable_gold_eye() { ((void(*)(ModelModule*))_vt[0x360/8])(this); }
};

} // namespace app
