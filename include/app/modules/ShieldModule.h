#pragma once
#include "types.h"

namespace app {

// ShieldModule — accessed at BattleObjectModuleAccessor+0x100
// Handles shield state, shield properties (size/life/speed/attack multipliers),
// hop/turn/front behavior, team, and target filtering.
// Vtable layout recovered from lua_bind dispatchers.
// All method names derived from .dynsym lua_bind::ShieldModule__*_impl dispatcher analysis.
struct ShieldModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    // -- core [10-13] --
    void clean() { ((void(*)(ShieldModule*))_vt[10])(this); }                                                // 0x50
    bool is_shield(u64 p1,u64 p2) { return ((bool(*)(ShieldModule*,u64,u64))_vt[17])(this,p1,p2); }          // 0x88
    void set_size(u64 p1,u64 p2) { ((void(*)(ShieldModule*,u64,u64))_vt[18])(this,p1,p2); }                  // 0x90
    void set_status(u64 p1,u64 p2,u64 p3) { ((void(*)(ShieldModule*,u64,u64,u64))_vt[19])(this,p1,p2,p3); } // 0x98
    void set_status_all(u64 p1,u64 p2) { ((void(*)(ShieldModule*,u64,u64))_vt[20])(this,p1,p2); }            // 0xA0

    // -- directional [21-25] --
    bool is_turn(u64 p1) { return ((bool(*)(ShieldModule*,u64))_vt[21])(this,p1); }                           // 0xA8
    bool is_front(u64 p1) { return ((bool(*)(ShieldModule*,u64))_vt[22])(this,p1); }                          // 0xB0
    bool is_hop(u64 p1) { return ((bool(*)(ShieldModule*,u64))_vt[23])(this,p1); }                            // 0xB8
    void* get_hop_angle(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[24])(this,p1); }                   // 0xC0
    bool is_no_hop(u64 p1) { return ((bool(*)(ShieldModule*,u64))_vt[25])(this,p1); }                         // 0xC8

    // -- set direction [26-28] --
    void set_turn(bool p1,u64 p2) { ((void(*)(ShieldModule*,bool,u64))_vt[26])(this,p1,p2); }                // 0xD0
    void set_front(u64 p1,u64 p2) { ((void(*)(ShieldModule*,u64,u64))_vt[27])(this,p1,p2); }                 // 0xD8
    void set_hop(bool p1,u64 p2) { ((void(*)(ShieldModule*,bool,u64))_vt[28])(this,p1,p2); }                 // 0xE0

    // -- multipliers [29-36] --
    void set_attack_mul(u64 p1) { ((void(*)(ShieldModule*,u64))_vt[29])(this,p1); }                           // 0xE8
    void* get_attack_mul(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[30])(this,p1); }                  // 0xF0
    void set_speed_mul(u64 p1) { ((void(*)(ShieldModule*,u64))_vt[31])(this,p1); }                            // 0xF8
    void* get_speed_mul(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[32])(this,p1); }                   // 0x100
    void set_life_mul(u64 p1) { ((void(*)(ShieldModule*,u64))_vt[33])(this,p1); }                             // 0x108
    void* get_life_mul(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[34])(this,p1); }                    // 0x110
    void set_attack_limit(u64 p1) { ((void(*)(ShieldModule*,u64))_vt[35])(this,p1); }                         // 0x118
    void* get_attack_limit(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[36])(this,p1); }                // 0x120

    // -- hit stop [38] --
    void set_hit_stop_mul() { ((void(*)(ShieldModule*))_vt[38])(this); }                                      // 0x130

    // -- m_ball/part [40-41] --
    bool is_no_m_ball(u64 p1) { return ((bool(*)(ShieldModule*,u64))_vt[40])(this,p1); }                      // 0x140
    void* get_part_size(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[41])(this,p1); }                   // 0x148

    // -- team [42-43] --
    u32 get_team_no() { return ((u32(*)(ShieldModule*))_vt[42])(this); }                                      // 0x150
    void set_no_team(bool p1) { ((void(*)(ShieldModule*,bool))_vt[43])(this,p1); }                            // 0x158

    // -- type [44] --
    void set_shield_type(u64 p1,u64 p2,u64 p3) { ((void(*)(ShieldModule*,u64,u64,u64))_vt[44])(this,p1,p2,p3); } // 0x160

    // -- clear [49-50] --
    void clear_all() { ((void(*)(ShieldModule*))_vt[49])(this); }                                             // 0x188
    void clear_all_2(u64 p1) { ((void(*)(ShieldModule*,u64))_vt[50])(this,p1); }                              // 0x190

    // -- position [51-55] --
    void* get_center_pos(u64 p1,u64 p2) { return ((void*(*)(ShieldModule*,u64,u64))_vt[51])(this,p1,p2); }   // 0x198
    void* get_lr(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[52])(this,p1); }                          // 0x1A0
    u32 get_group_num() { return ((u32(*)(ShieldModule*))_vt[53])(this); }                                    // 0x1A8
    void* get_pos_x(u64 p1) { return ((void*(*)(ShieldModule*,u64))_vt[54])(this,p1); }                      // 0x1B0

    // -- target [55-56] --
    void set_target_property(u64 p1,u64 p2) { ((void(*)(ShieldModule*,u64,u64))_vt[55])(this,p1,p2); }       // 0x1B8
    void set_target_category(u64 p1,u64 p2) { ((void(*)(ShieldModule*,u64,u64))_vt[56])(this,p1,p2); }       // 0x1C0

    // -- sleep/hit_stop_slow [58-61] --
    void sleep(bool p1) { ((void(*)(ShieldModule*,bool))_vt[58])(this,p1); }                                  // 0x1D0
    void set_hit_stop_slow(bool p1) { ((void(*)(ShieldModule*,bool))_vt[61])(this,p1); }                      // 0x1E8
};

} // namespace app
