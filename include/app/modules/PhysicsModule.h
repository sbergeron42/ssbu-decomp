#pragma once
#include "types.h"

namespace app {

// PhysicsModule — accessed at BattleObjectModuleAccessor+0x80
// Handles rope/swing physics, 2nd-order simulation (chain/hair), IK, and collision.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x60–0x3d8).
// All method names derived from .dynsym lua_bind::PhysicsModule__*_impl dispatcher analysis.
struct PhysicsModule {
    void** _vt;

    // -- Swing system (0x60–0xc8) -- [confirmed: lua_bind API names]
    void _v0x60(bool p1, bool p2) { ((void(*)(PhysicsModule*,bool,bool))_vt[0x60/8])(this,p1,p2); }
    void reset_swing() { ((void(*)(PhysicsModule*))_vt[0x88/8])(this); }
    void set_swing_only_anim(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0xa8/8])(this,p1); }
    void _v0xc0(bool p1, u64 p2, bool p3) { ((void(*)(PhysicsModule*,bool,u64,bool))_vt[0xc0/8])(this,p1,p2,p3); }
    void set_swing_wind(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0xc8/8])(this,p1); }

    // -- Swing rate/rebirth (0xf0–0xf8) --
    void set_swing_rate() { ((void(*)(PhysicsModule*))_vt[0xf0/8])(this); }
    void set_swing_rebirth(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0xf8/8])(this,p1); }

    // -- 2nd-order simulation core (0x100–0x168) --
    void set_2nd_gravity() { ((void(*)(PhysicsModule*))_vt[0x100/8])(this); }
    void set_2nd_status(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x110/8])(this,p1); }
    u32 get_2nd_status() { return ((u32(*)(PhysicsModule*))_vt[0x118/8])(this); }
    void set_2nd_end_pos(u64 p1, u64 p2) { ((void(*)(PhysicsModule*,u64,u64))_vt[0x120/8])(this,p1,p2); }
    f32 get_2nd_line_length(u64 p1) { return ((f32(*)(PhysicsModule*,u64))_vt[0x130/8])(this,p1); }
    void set_2nd_line_length_all() { ((void(*)(PhysicsModule*))_vt[0x140/8])(this); }
    u32 get_2nd_node_num() { return ((u32(*)(PhysicsModule*))_vt[0x150/8])(this); }
    u32 get_2nd_active_node_num() { return ((u32(*)(PhysicsModule*))_vt[0x158/8])(this); }
    void* get_2nd_active_length() { return ((void*(*)(PhysicsModule*))_vt[0x160/8])(this); }
    void set_2nd_active_node_num() { ((void(*)(PhysicsModule*))_vt[0x168/8])(this); }

    // -- 2nd precede/flip (0x178–0x198) --
    bool is_2nd_precede() { return ((bool(*)(PhysicsModule*))_vt[0x178/8])(this); }
    void set_2nd_precede(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0x180/8])(this,p1); }
    bool is_2nd_flip() { return ((bool(*)(PhysicsModule*))_vt[0x190/8])(this); }
    void set_2nd_flip(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0x198/8])(this,p1); }

    // -- 2nd speed/back (0x1b0) --
    void set_2nd_back_speed() { ((void(*)(PhysicsModule*))_vt[0x1b0/8])(this); }

    // -- IK system (0x1d0–0x1f0) --
    void set_ik(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x1d0/8])(this,p1); }
    void set_ik_target_pos(u64 p1, u64 p2, u64 p3) { ((void(*)(PhysicsModule*,u64,u64,u64))_vt[0x1d8/8])(this,p1,p2,p3); }
    void set_ik_target_dir(u64 p1, u64 p2, u64 p3) { ((void(*)(PhysicsModule*,u64,u64,u64))_vt[0x1e0/8])(this,p1,p2,p3); }
    u32 get_ik_end_joint_id(u64 p1) { return ((u32(*)(PhysicsModule*,u64))_vt[0x1f0/8])(this,p1); }

    // -- Charge/resistance (0x200–0x228) --
    void* stop_charge() { return ((void*(*)(PhysicsModule*))_vt[0x200/8])(this); }
    void set_2nd_air_resistance() { ((void(*)(PhysicsModule*))_vt[0x210/8])(this); }
    void set_2nd_air_resistance_2(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x218/8])(this,p1); }
    void set_2nd_water_resistance() { ((void(*)(PhysicsModule*))_vt[0x228/8])(this); }

    // -- 2nd tension/joints (0x240–0x258) --
    void* get_2nd_tension() { return ((void*(*)(PhysicsModule*))_vt[0x240/8])(this); }
    u32 get_2nd_joint_num() { return ((u32(*)(PhysicsModule*))_vt[0x248/8])(this); }
    u32 get_2nd_joint_id(u64 p1) { return ((u32(*)(PhysicsModule*,u64))_vt[0x250/8])(this,p1); }
    void set_2nd_collision_size(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x258/8])(this,p1); }

    // -- 2nd mass/collision (0x268–0x290) --
    void set_2nd_mass(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x268/8])(this,p1); }
    void set_2nd_disable_collision(u64 p1, bool p2) { ((void(*)(PhysicsModule*,u64,bool))_vt[0x270/8])(this,p1,p2); }
    void set_2nd_fix_flag(u64 p1, bool p2) { ((void(*)(PhysicsModule*,u64,bool))_vt[0x278/8])(this,p1,p2); }
    void set_reflect_param_wall() { ((void(*)(PhysicsModule*))_vt[0x280/8])(this); }
    void set_reflect_param_ceil() { ((void(*)(PhysicsModule*))_vt[0x288/8])(this); }
    void set_reflect_param_floor() { ((void(*)(PhysicsModule*))_vt[0x290/8])(this); }

    // -- 2nd length/pos/speed (0x2a0–0x2c0) --
    void set_2nd_length(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x2a0/8])(this,p1); }
    void* get_2nd_pos(u64 p1) { return ((void*(*)(PhysicsModule*,u64))_vt[0x2a8/8])(this,p1); }
    void set_2nd_pos(u64 p1, u64 p2) { ((void(*)(PhysicsModule*,u64,u64))_vt[0x2b0/8])(this,p1,p2); }
    void* get_2nd_speed(u64 p1) { return ((void*(*)(PhysicsModule*,u64))_vt[0x2b8/8])(this,p1); }
    void set_2nd_speed(u64 p1, u64 p2) { ((void(*)(PhysicsModule*,u64,u64))_vt[0x2c0/8])(this,p1,p2); }

    // -- 2nd node/collision config (0x2e0–0x320) --
    void set_2nd_node_num_max(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x2e0/8])(this,p1); }
    void clear_2nd_speed() { ((void(*)(PhysicsModule*))_vt[0x2e8/8])(this); }
    void set_2nd_collision_object(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0x2f0/8])(this,p1); }
    void set_2nd_sync_gravity(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0x300/8])(this,p1); }
    void set_2nd_restitution_range() { ((void(*)(PhysicsModule*))_vt[0x308/8])(this); }
    void set_2nd_restitution_rate() { ((void(*)(PhysicsModule*))_vt[0x310/8])(this); }
    void set_2nd_restitution_rate_2(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x318/8])(this,p1); }
    void set_2nd_friction_rate(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x320/8])(this,p1); }

    // -- 2nd misc params (0x338–0x358) --
    void set_2nd_fixed_tip_num(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x338/8])(this,p1); }
    void set_2nd_z_range() { ((void(*)(PhysicsModule*))_vt[0x340/8])(this); }
    u32 get_2nd_touch_ground_line_num(u64 p1) { return ((u32(*)(PhysicsModule*,u64))_vt[0x358/8])(this,p1); }

    // -- Floor collision/swing ground (0x3a8–0x3d8) --
    void set_enable_floor_collision_line(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x3a8/8])(this,p1); }
    void set_swing_ground_collision_all(bool p1) { ((void(*)(PhysicsModule*,bool))_vt[0x3b8/8])(this,p1); }
    void set_swing_special_state(u64 p1) { ((void(*)(PhysicsModule*,u64))_vt[0x3d8/8])(this,p1); }
};

} // namespace app
