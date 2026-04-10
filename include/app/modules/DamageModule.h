#pragma once
#include "types.h"

namespace app {

// DamageModule vtable layout recovered from lua_bind dispatchers
// Accessed via BattleObjectModuleAccessor+0xA8
//
// All method names derived from .dynsym lua_bind::DamageModule__*_impl dispatcher analysis.
// Vtable index = byte_offset / 8
struct DamageModule {
    void** _vt;

    // slot 10 (0x50)
    void sleep(bool p1) { ((void(*)(DamageModule*,bool))_vt[10])(this,p1); }
    // slot 12 (0x60)
    void init_damage() { ((void(*)(DamageModule*))_vt[12])(this); }
    // slot 20 (0xA0)
    void set_force_damage(u32 p1, void* pos, s32 p3, s32 p4, bool p5, bool p6, bool p7, bool p8) {
        ((void(*)(DamageModule*,u32,void*,s32,s32,bool,bool,bool,bool))_vt[20])(this,p1,pos,p3,p4,p5,p6,p7,p8);
    }
    // slot 24 (0xC0) — lua_bind passes u64 in x1 (passthrough) + f32 in s0
    void add_damage(u64 p1) { ((void(*)(DamageModule*,u64))_vt[24])(this,p1); }
    // slot 25 (0xC8) — lua_bind passes u64 in x1 (passthrough to vtable impl)
    void* damage(u64 p1) { return ((void*(*)(DamageModule*,u64))_vt[25])(this,p1); }
    // slot 26 (0xD0) — lua_bind passes u64 in x1 (passthrough to vtable impl)
    void* reaction(u64 p1) { return ((void*(*)(DamageModule*,u64))_vt[26])(this,p1); }
    // slot 27 (0xD8) — lua_bind passes u64 in x1 (passthrough to vtable impl)
    void* power_max(u64 p1) { return ((void*(*)(DamageModule*,u64))_vt[27])(this,p1); }
    // slot 28 (0xE0)
    void check_no_reaction(u64 p1) { ((void(*)(DamageModule*,u64))_vt[28])(this,p1); }
    // slot 29 (0xE8)
    void set_no_reaction_mode_status(u64 p1, u64 p2) { ((void(*)(DamageModule*,u64,u64))_vt[29])(this,p1,p2); }
    // slot 31 (0xF8)
    void reset_no_reaction_mode_status() { ((void(*)(DamageModule*))_vt[31])(this); }
    // slot 36 (0x120)
    void set_no_reaction_damage_power() { ((void(*)(DamageModule*))_vt[36])(this); }
    // slot 37 (0x128)
    void set_no_reaction_no_effect(bool p1) { ((void(*)(DamageModule*,bool))_vt[37])(this,p1); }
    // slot 38 (0x130)
    bool is_no_reaction_mode_perfect() { return ((bool(*)(DamageModule*))_vt[38])(this); }
    // slot 49 (0x188)
    void* damage_log() { return ((void*(*)(DamageModule*))_vt[49])(this); }
    // slot 54 (0x1B0)
    void set_attacker_info(u64 p1) { ((void(*)(DamageModule*,u64))_vt[54])(this,p1); }
    // slot 59 (0x1D8)
    bool is_capture_cut() { return ((bool(*)(DamageModule*))_vt[59])(this); }
    // slot 61 (0x1E8)
    void set_ignore_capture_cut_no(u64 p1) { ((void(*)(DamageModule*,u64))_vt[61])(this,p1); }
    // slot 66 (0x210)
    void set_damage_mul() { ((void(*)(DamageModule*))_vt[66])(this); }
    // slot 67 (0x218)
    void set_damage_mul_2nd() { ((void(*)(DamageModule*))_vt[67])(this); }
    // slot 68 (0x220)
    void set_force_damage_mul() { ((void(*)(DamageModule*))_vt[68])(this); }
    // slot 69 (0x228)
    void set_reaction_mul() { ((void(*)(DamageModule*))_vt[69])(this); }
    // slot 70 (0x230)
    void set_reaction_mul_2nd() { ((void(*)(DamageModule*))_vt[70])(this); }
    // slot 71 (0x238)
    void set_reaction_mul_4th() { ((void(*)(DamageModule*))_vt[71])(this); }
    // slot 72 (0x240)
    void set_weak_param(u64 p1) { ((void(*)(DamageModule*,u64))_vt[72])(this,p1); }
    // slot 73 (0x248)
    void set_damage_lock(bool p1) { ((void(*)(DamageModule*,bool))_vt[73])(this,p1); }
    // slot 74 (0x250)
    void set_damage_lock_2nd(bool p1) { ((void(*)(DamageModule*,bool))_vt[74])(this,p1); }
    // slot 75 (0x258)
    bool is_damage_lock() { return ((bool(*)(DamageModule*))_vt[75])(this); }
    // slot 77 (0x268)
    void heal(u64 p1) { ((void(*)(DamageModule*,u64))_vt[77])(this,p1); }
    // slot 81 (0x288)
    void overwrite_log_reaction_frame() { ((void(*)(DamageModule*))_vt[81])(this); }
    // slot 82 (0x290)
    void start_damage_info_log() { ((void(*)(DamageModule*))_vt[82])(this); }
    // slot 83 (0x298)
    void end_damage_info_log() { ((void(*)(DamageModule*))_vt[83])(this); }
    // slot 84 (0x2A0)
    void set_force_damage_from_last_damage() { ((void(*)(DamageModule*))_vt[84])(this); }
    // slot 85 (0x2A8)
    bool is_paralyze() { return ((bool(*)(DamageModule*))_vt[85])(this); }
    // slot 90 (0x2D0)
    void set_critical_hit(bool p1) { ((void(*)(DamageModule*,bool))_vt[90])(this,p1); }
    // slot 91 (0x2D8)
    bool is_critical_hit() { return ((bool(*)(DamageModule*))_vt[91])(this); }
};

} // namespace app
