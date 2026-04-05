#pragma once
#include "types.h"

namespace app {

// AreaModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::AreaModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0xC0 (fighter_area_module, polymorphic)
struct AreaModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void force_update() { ((void(*)(AreaModule*))_vt[0x50/8])(this); }
    void set_auto_layer_update(bool p1) { ((void(*)(AreaModule*,bool))_vt[0x58/8])(this,p1); }
    void clean() { ((void(*)(AreaModule*))_vt[0x70/8])(this); }
    void set_layer(u64 p1, u64 p2) { ((void(*)(AreaModule*,u64,u64))_vt[0x90/8])(this,p1,p2); }
    void* layer(u64 p1) { return ((void*(*)(AreaModule*,u64))_vt[0x98/8])(this,p1); }
    void set_whole(bool p1) { ((void(*)(AreaModule*,bool))_vt[0xa0/8])(this,p1); }
    u32 get_whole() { return ((u32(*)(AreaModule*))_vt[0xa8/8])(this); }
    void* get_group(u64 p1) { return ((void*(*)(AreaModule*,u64))_vt[0xb0/8])(this,p1); }
    u32 area_instance_size() { return ((u32(*)(AreaModule*))_vt[0xB8/8])(this); }
    void enable_area(u64 p1, bool p2, u64 p3) { ((void(*)(AreaModule*,u64,bool,u64))_vt[0xc0/8])(this,p1,p2,p3); }
    bool is_enable_area(u64 p1) { return ((bool(*)(AreaModule*,u64))_vt[0xc8/8])(this,p1); }
    void reset_area(u64 p1) { ((void(*)(AreaModule*,u64))_vt[0xd0/8])(this,p1); }
    void set_area_target_group_mask(u64 p1, u64 p2) { ((void(*)(AreaModule*,u64,u64))_vt[0xd8/8])(this,p1,p2); }
    void set_area_target_local_group_mask(u64 p1, u64 p2) { ((void(*)(AreaModule*,u64,u64))_vt[0xe0/8])(this,p1,p2); }
    void set_area_shape_aabb(u64 p1, u64 p2, u64 p3) { ((void(*)(AreaModule*,u64,u64,u64))_vt[0xe8/8])(this,p1,p2,p3); }
    void set_area_shape_circle(u64 p1, u64 p2) { ((void(*)(AreaModule*,u64,u64))_vt[0xf0/8])(this,p1,p2); }
    void set_area_shape_type(u64 p1, u64 p2) { ((void(*)(AreaModule*,u64,u64))_vt[0xf8/8])(this,p1,p2); }
    void set_center_x0(u64 p1, bool p2) { ((void(*)(AreaModule*,u64,bool))_vt[0x100/8])(this,p1,p2); }
    u32 get_area_id(u64 p1) { return ((u32(*)(AreaModule*,u64))_vt[0x108/8])(this,p1); }
    bool is_exist_area_instance(u64 p1) { return ((bool(*)(AreaModule*,u64))_vt[0x110/8])(this,p1); }
    u32 get_area_index_from_id(u64 p1) { return ((u32(*)(AreaModule*,u64))_vt[0x120/8])(this,p1); }
    u32 get_area_contact_count(u64 p1) { return ((u32(*)(AreaModule*,u64))_vt[0x128/8])(this,p1); }
    void* get_area_contact_log(u64 p1, u64 p2) { return ((void*(*)(AreaModule*,u64,u64))_vt[0x130/8])(this,p1,p2); }
    u32 get_area_contact_target_id(u64 p1, u64 p2) { return ((u32(*)(AreaModule*,u64,u64))_vt[0x138/8])(this,p1,p2); }
    void erase_wind(u64 p1) { ((void(*)(AreaModule*,u64))_vt[0x140/8])(this,p1); }
    void add_wind_area_2nd(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(AreaModule*,u64,u64,u64,u64))_vt[0x158/8])(this,p1,p2,p3,p4); }
    void add_wind_area_2nd_rad(u64 p1, u64 p2, u64 p3) { ((void(*)(AreaModule*,u64,u64,u64))_vt[0x160/8])(this,p1,p2,p3); }
    void sleep(bool p1) { ((void(*)(AreaModule*,bool))_vt[0x168/8])(this,p1); }
    bool is_sleep() { return ((bool(*)(AreaModule*))_vt[0x170/8])(this); }
    bool is_water() { return ((bool(*)(AreaModule*))_vt[0x198/8])(this); }
    u32 get_water_task_id() { return ((u32(*)(AreaModule*))_vt[0x1B0/8])(this); }
    f32 get_water_surface_y() { return ((f32(*)(AreaModule*))_vt[0x1B8/8])(this); }
    void* test_water(u64 p1, u64 p2) { return ((void*(*)(AreaModule*,u64,u64))_vt[0x1c8/8])(this,p1,p2); }
};

} // namespace app
