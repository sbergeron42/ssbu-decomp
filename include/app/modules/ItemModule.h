#pragma once
#include "types.h"

namespace app {

// ItemModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::ItemModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0xC8
struct ItemModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    // -- have/use/pickup --
    void have_item(u64 p1, u64 p2, u64 p3, bool p4, bool p5) { ((void(*)(ItemModule*,u64,u64,u64,bool,bool))_vt[0x58/8])(this,p1,p2,p3,p4,p5); }
    void have_item_instance(u64 p1, u64 p2, bool p3, bool p4, bool p5, bool p6) { ((void(*)(ItemModule*,u64,u64,bool,bool,bool,bool))_vt[0x68/8])(this,p1,p2,p3,p4,p5,p6); }
    void* use_item_instance(u64 p1, bool p2) { return ((void*(*)(ItemModule*,u64,bool))_vt[0x98/8])(this,p1,p2); }
    void* use_item(u64 p1, bool p2) { return ((void*(*)(ItemModule*,u64,bool))_vt[0xa0/8])(this,p1,p2); }
    void* pickup_item(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5) { return ((void*(*)(ItemModule*,u64,u64,u64,u64,u64))_vt[0xa8/8])(this,p1,p2,p3,p4,p5); }
    bool is_success_pickup_item() { return ((bool(*)(ItemModule*))_vt[0xb0/8])(this); }
    void* success_auto_pickup_item() { return ((void*(*)(ItemModule*))_vt[0xb8/8])(this); }
    bool is_success_auto_pickup_item() { return ((bool(*)(ItemModule*))_vt[0xc0/8])(this); }
    bool is_have_item(u64 p1) { return ((bool(*)(ItemModule*,u64))_vt[0xc8/8])(this,p1); }

    // -- have_item queries --
    void* get_have_item_size(u64 p1) { return ((void*(*)(ItemModule*,u64))_vt[0xd0/8])(this,p1); }
    u32 get_have_item_kind(u64 p1) { return ((u32(*)(ItemModule*,u64))_vt[0xd8/8])(this,p1); }
    void* get_have_item_trait(u64 p1) { return ((void*(*)(ItemModule*,u64))_vt[0xe0/8])(this,p1); }
    u32 get_have_item_hold_kind(u64 p1) { return ((u32(*)(ItemModule*,u64))_vt[0xe8/8])(this,p1); }
    void* get_have_item_status_param_int(u64 p1, u64 p2) { return ((void*(*)(ItemModule*,u64,u64))_vt[0xf0/8])(this,p1,p2); }
    void* get_have_item_status_param_float(u64 p1, u64 p2) { return ((void*(*)(ItemModule*,u64,u64))_vt[0xf8/8])(this,p1,p2); }
    void* get_have_item_status_param_bool(u64 p1, u64 p2) { return ((void*(*)(ItemModule*,u64,u64))_vt[0x100/8])(this,p1,p2); }
    u32 get_have_item_id(u64 p1) { return ((u32(*)(ItemModule*,u64))_vt[0x108/8])(this,p1); }

    // -- pickable --
    u32 get_pickable_item_object_id() { return ((u32(*)(ItemModule*))_vt[0x120/8])(this); }
    f32 get_pickable_item_size() { return ((f32(*)(ItemModule*))_vt[0x128/8])(this); }
    u32 get_pickable_item_kind() { return ((u32(*)(ItemModule*))_vt[0x130/8])(this); }
    void* get_pickable_item_trait() { return ((void*(*)(ItemModule*))_vt[0x138/8])(this); }

    // -- remove/throw/warp --
    void* remove_item(u64 p1) { return ((void*(*)(ItemModule*,u64))_vt[0x148/8])(this,p1); }
    void* remove_all() { return ((void*(*)(ItemModule*))_vt[0x150/8])(this); }
    void* throw_item(u64 p1, bool p2) { return ((void*(*)(ItemModule*,u64,bool))_vt[0x158/8])(this,p1,p2); }
    void drop_item(u64 p1) { ((void(*)(ItemModule*,u64))_vt[0x168/8])(this,p1); }
    void* warp_item(u64 p1, u64 p2) { return ((void*(*)(ItemModule*,u64,u64))_vt[0x170/8])(this,p1,p2); }
    void* warp_attach_item(u64 p1) { return ((void*(*)(ItemModule*,u64))_vt[0x180/8])(this,p1); }
    void born_item(u64 p1) { ((void(*)(ItemModule*,u64))_vt[0x188/8])(this,p1); }

    // -- shoot --
    void* shoot_item_bullet(u64 p1, u64 p2) { return ((void*(*)(ItemModule*,u64,u64))_vt[0x190/8])(this,p1,p2); }
    void* shoot_item_bullet_blanks(u64 p1, u64 p2) { return ((void*(*)(ItemModule*,u64,u64))_vt[0x198/8])(this,p1,p2); }
    void* get_shoot_item_bullet(u64 p1) { return ((void*(*)(ItemModule*,u64))_vt[0x1a0/8])(this,p1); }

    // -- have_item actions --
    void update_have_item_action_info(u64 p1) { ((void(*)(ItemModule*,u64))_vt[0x1a8/8])(this,p1); }
    void set_have_item_scale_anim(u64 p1, u64 p2) { ((void(*)(ItemModule*,u64,u64))_vt[0x1b0/8])(this,p1,p2); }
    void set_have_item_action(u64 p1, u64 p2) { ((void(*)(ItemModule*,u64,u64))_vt[0x1b8/8])(this,p1,p2); }
    void set_have_item_visibility(bool p1, u64 p2) { ((void(*)(ItemModule*,bool,u64))_vt[0x1c0/8])(this,p1,p2); }
    void set_have_item_hold_anim(bool p1, u64 p2) { ((void(*)(ItemModule*,bool,u64))_vt[0x1c8/8])(this,p1,p2); }
    void set_have_item_constraint_joint(u64 p1, u64 p2) { ((void(*)(ItemModule*,u64,u64))_vt[0x1d0/8])(this,p1,p2); }
    void reset_have_item_constraint_node(u64 p1) { ((void(*)(ItemModule*,u64))_vt[0x1d8/8])(this,p1); }
    void set_have_item_hit_sleep(u64 p1, bool p2) { ((void(*)(ItemModule*,u64,bool))_vt[0x1e0/8])(this,p1,p2); }

    // -- attach --
    void* attach_item(u64 p1, u64 p2, bool p3) { return ((void*(*)(ItemModule*,u64,u64,bool))_vt[0x1f0/8])(this,p1,p2,p3); }
    void attach_item_2(u64 p1, bool p2) { ((void(*)(ItemModule*,u64,bool))_vt[0x200/8])(this,p1,p2); }
    void attach_item_instance(u64 p1, bool p2) { ((void(*)(ItemModule*,u64,bool))_vt[0x200/8])(this,p1,p2); }
    bool is_attach_item(u64 p1) { return ((bool(*)(ItemModule*,u64))_vt[0x208/8])(this,p1); }
    u32 get_attach_item_count() { return ((u32(*)(ItemModule*))_vt[0x218/8])(this); }
    void set_attach_item_visibility(bool p1, u64 p2) { ((void(*)(ItemModule*,bool,u64))_vt[0x228/8])(this,p1,p2); }
    void eject_have_item(u64 p1, bool p2, bool p3) { ((void(*)(ItemModule*,u64,bool,bool))_vt[0x240/8])(this,p1,p2,p3); }
    void eject_attach_item(u64 p1, bool p2, bool p3, bool p4) { ((void(*)(ItemModule*,u64,bool,bool,bool))_vt[0x248/8])(this,p1,p2,p3,p4); }
    void eject_attach(u64 p1, bool p2, bool p3) { ((void(*)(ItemModule*,u64,bool,bool))_vt[0x250/8])(this,p1,p2,p3); }
    void drop_attach(u64 p1) { ((void(*)(ItemModule*,u64))_vt[0x268/8])(this,p1); }
    void drop_attach_group(u64 p1) { ((void(*)(ItemModule*,u64))_vt[0x270/8])(this,p1); }
    void* scale_attach(u64 p1) { return ((void*(*)(ItemModule*,u64))_vt[0x278/8])(this,p1); }
    void set_attach_item_action(u64 p1, u64 p2) { ((void(*)(ItemModule*,u64,u64))_vt[0x280/8])(this,p1,p2); }
    void set_have_item_team(u64 p1, u64 p2) { ((void(*)(ItemModule*,u64,u64))_vt[0x290/8])(this,p1,p2); }
    void set_change_status_event(bool p1) { ((void(*)(ItemModule*,bool))_vt[0x2b0/8])(this,p1); }
};

} // namespace app
