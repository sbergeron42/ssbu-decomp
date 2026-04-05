#pragma once
#include "types.h"

namespace app {

// HitModule — accessed at BattleObjectModuleAccessor+0xB0
// Handles hitbox/hurtbox status, invincibility, XLU (intangibility), and hit logging.
// Vtable layout recovered from lua_bind dispatchers.
// All method names derived from .dynsym lua_bind::HitModule__*_impl dispatcher analysis.
struct HitModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    // -- core [11-14] --
    void clean() { ((void(*)(HitModule*))_vt[11])(this); }                                                  // 0x58
    void sleep(bool p1) { ((void(*)(HitModule*,bool))_vt[14])(this,p1); }                                   // 0x70

    // -- status [17-27] --
    void reset_status_all(u64 p1) { ((void(*)(HitModule*,u64))_vt[17])(this,p1); }                          // 0x88
    void set_status(u64 p1,u64 p2,u64 p3) { ((void(*)(HitModule*,u64,u64,u64))_vt[22])(this,p1,p2,p3); }   // 0xB0
    void set_status_joint(u64 p1,u64 p2,u64 p3) { ((void(*)(HitModule*,u64,u64,u64))_vt[23])(this,p1,p2,p3); } // 0xB8
    void set_status_joint_default(u64 p1,u64 p2,u64 p3) { ((void(*)(HitModule*,u64,u64,u64))_vt[24])(this,p1,p2,p3); } // 0xC0
    void set_status_all(u64 p1,u64 p2) { ((void(*)(HitModule*,u64,u64))_vt[25])(this,p1,p2); }              // 0xC8
    void set_whole(u64 p1,u64 p2) { ((void(*)(HitModule*,u64,u64))_vt[26])(this,p1,p2); }                   // 0xD0
    void* get_whole(u64 p1) { return ((void*(*)(HitModule*,u64))_vt[27])(this,p1); }                        // 0xD8

    // -- catch/xlu [29-38] --
    void set_check_catch(bool p1,u64 p2) { ((void(*)(HitModule*,bool,u64))_vt[29])(this,p1,p2); }           // 0xE8
    void set_xlu_global(u64 p1) { ((void(*)(HitModule*,u64))_vt[33])(this,p1); }                            // 0x108
    void cancel_xlu_global(u64 p1) { ((void(*)(HitModule*,u64))_vt[34])(this,p1); }                         // 0x110
    void set_xlu_frame_global(u64 p1,u64 p2) { ((void(*)(HitModule*,u64,u64))_vt[35])(this,p1,p2); }       // 0x118
    void set_invincible_frame_global(u64 p1,bool p2,u64 p3) { ((void(*)(HitModule*,u64,bool,u64))_vt[38])(this,p1,p2,p3); } // 0x130

    // -- queries [41-46] --
    void* get_status(u64 p1,u64 p2) { return ((void*(*)(HitModule*,u64,u64))_vt[41])(this,p1,p2); }         // 0x148
    void* get_total_status(u64 p1) { return ((void*(*)(HitModule*,u64))_vt[42])(this,p1); }                  // 0x150
    void* get_total_status_disguise(u64 p1) { return ((void*(*)(HitModule*,u64))_vt[43])(this,p1); }         // 0x158
    void set_total_status_disguise(u64 p1,u64 p2) { ((void(*)(HitModule*,u64,u64))_vt[44])(this,p1,p2); }   // 0x160
    u32 get_part_size(u64 p1) { return ((u32(*)(HitModule*,u64))_vt[46])(this,p1); }                         // 0x170

    // -- team/reaction [49-61] --
    void set_no_team(bool p1) { ((void(*)(HitModule*,bool))_vt[49])(this,p1); }                              // 0x188
    void set_reaction_frame(u64 p1) { ((void(*)(HitModule*,u64))_vt[59])(this,p1); }                         // 0x1D8
    void set_hit_stop_mul(u64 p1) { ((void(*)(HitModule*,u64))_vt[61])(this,p1); }                           // 0x1E8

    // -- position/defense [64-69] --
    void* get_center_pos(u64 p1,u64 p2) { return ((void*(*)(HitModule*,u64,u64))_vt[64])(this,p1,p2); }     // 0x200
    void set_defense_mul_status() { ((void(*)(HitModule*))_vt[66])(this); }                                   // 0x210
    void* exist_log(u64 p1,u64 p2) { return ((void*(*)(HitModule*,u64,u64))_vt[69])(this,p1,p2); }          // 0x228
};

} // namespace app
