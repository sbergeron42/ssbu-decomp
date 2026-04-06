#pragma once

#include "types.h"

namespace app {

// WorkModule -- fighter variable storage (floats, ints, flags, transition terms)
// Accessed at BattleObjectModuleAccessor offset +0x50
// Internal allocation: 0x1920 bytes
// Vtable layout uses LinkModule-style inline dispatch (explicit _vt member).
// All vtable method names derived from .dynsym lua_bind::WorkModule__*_impl dispatcher analysis.
struct WorkModule {
    void** _vt;

    // -- Float operations (0x58–0x90) --
    f32 get_float(s32 index) { return ((f32(*)(WorkModule*,s32))_vt[0x58/8])(this,index); }
    void set_float(s32 index, f32 value) { ((void(*)(WorkModule*,s32,f32))_vt[0x60/8])(this,index,value); }
    // 0x68: unknown
    f32 rnd_float(s32 index) { return ((f32(*)(WorkModule*,s32))_vt[0x70/8])(this,index); }
    f32 add_float(s32 index, f32 value) { return ((f32(*)(WorkModule*,s32,f32))_vt[0x78/8])(this,index,value); }
    f32 sub_float(s32 index, f32 value) { return ((f32(*)(WorkModule*,s32,f32))_vt[0x80/8])(this,index,value); }
    f32 mul_float(s32 index, f32 value) { return ((f32(*)(WorkModule*,s32,f32))_vt[0x88/8])(this,index,value); }
    f32 div_float(s32 index, f32 value) { return ((f32(*)(WorkModule*,s32,f32))_vt[0x90/8])(this,index,value); }

    // -- Int operations (0x98–0xf8) --
    s32 get_int(s32 index) { return ((s32(*)(WorkModule*,s32))_vt[0x98/8])(this,index); }
    void set_int(s32 index, s32 value) { ((void(*)(WorkModule*,s32,s32))_vt[0xa0/8])(this,index,value); }
    // 0xa8: unknown
    s64 get_int64(s32 index) { return ((s64(*)(WorkModule*,s32))_vt[0xb0/8])(this,index); }
    void set_int64(s32 index, s64 value) { ((void(*)(WorkModule*,s32,s64))_vt[0xb8/8])(this,index,value); }
    s32 rnd_int(s32 low, s32 high, s32 seed) { return ((s32(*)(WorkModule*,s32,s32,s32))_vt[0xc0/8])(this,low,high,seed); }
    void inc_int(s32 index) { ((void(*)(WorkModule*,s32))_vt[0xc8/8])(this,index); }
    void dec_int(s32 index) { ((void(*)(WorkModule*,s32))_vt[0xd0/8])(this,index); }
    void add_int(s32 index, s32 value) { ((void(*)(WorkModule*,s32,s32))_vt[0xd8/8])(this,index,value); }
    void sub_int(s32 index, s32 value) { ((void(*)(WorkModule*,s32,s32))_vt[0xe0/8])(this,index,value); }
    void mul_int(s32 index, s32 value) { ((void(*)(WorkModule*,s32,s32))_vt[0xe8/8])(this,index,value); }
    void div_int(s32 index, s32 value) { ((void(*)(WorkModule*,s32,s32))_vt[0xf0/8])(this,index,value); }
    void count_down_int(s32 index, s32 min, s32 step) { ((void(*)(WorkModule*,s32,s32,s32))_vt[0xf8/8])(this,index,min,step); }

    // -- Flag operations (0x108–0x138) --
    // 0x100: unknown
    bool is_flag(s32 index) { return ((bool(*)(WorkModule*,s32))_vt[0x108/8])(this,index); }
    void on_flag(s32 index) { ((void(*)(WorkModule*,s32))_vt[0x110/8])(this,index); }
    // 0x118: unknown
    void off_flag(s32 index) { ((void(*)(WorkModule*,s32))_vt[0x120/8])(this,index); }
    // 0x128: unknown
    void set_flag(u64 value, s32 index) { ((void(*)(WorkModule*,u64,s32))_vt[0x130/8])(this,value,index); }
    void turn_off_flag(s32 index) { ((void(*)(WorkModule*,s32))_vt[0x138/8])(this,index); }

    // -- Transition term groups (0x140–0x178) --
    void enable_transition_term_group(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x140/8])(this,group); }
    void unable_transition_term_group(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x148/8])(this,group); }
    void clear_transition_term_group(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x150/8])(this,group); }
    bool is_enable_transition_term_group(s32 group) { return ((bool(*)(WorkModule*,s32))_vt[0x158/8])(this,group); }
    void enable_transition_term_group_ex(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x160/8])(this,group); }
    void enable_transition_term_group_ex_all(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x168/8])(this,group); }
    void unable_transition_term_group_ex(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x170/8])(this,group); }
    void unable_transition_term_group_ex_all(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x178/8])(this,group); }

    // -- Transition terms (0x180–0x200) --
    bool is_enable_transition_term(s32 term) { return ((bool(*)(WorkModule*,s32))_vt[0x180/8])(this,term); }
    void enable_transition_term(s32 term) { ((void(*)(WorkModule*,s32))_vt[0x188/8])(this,term); }
    void unable_transition_term(s32 term) { ((void(*)(WorkModule*,s32))_vt[0x190/8])(this,term); }
    void clear_transition_term() { ((void(*)(WorkModule*))_vt[0x198/8])(this); }
    bool is_enable_transition_term_forbid(s32 term) { return ((bool(*)(WorkModule*,s32))_vt[0x1a0/8])(this,term); }
    void enable_transition_term_forbid(s32 term) { ((void(*)(WorkModule*,s32))_vt[0x1a8/8])(this,term); }
    void unable_transition_term_forbid(s32 term) { ((void(*)(WorkModule*,s32))_vt[0x1b0/8])(this,term); }
    void enable_transition_term_forbid_group(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x1b8/8])(this,group); }
    void unable_transition_term_forbid_group(s32 group) { ((void(*)(WorkModule*,s32))_vt[0x1c0/8])(this,group); }
    void clear_transition_term_forbid() { ((void(*)(WorkModule*))_vt[0x1c8/8])(this); }
    // 0x1d0–0x1f0: unknown
    void enable_transition_term_forbid_indivi(s32 term) { ((void(*)(WorkModule*,s32))_vt[0x1f8/8])(this,term); }
    void unable_transition_term_forbid_indivi(s32 term) { ((void(*)(WorkModule*,s32))_vt[0x200/8])(this,term); }

    // -- Misc (0x220–0x280) --
    // 0x208–0x218: unknown
    void clear_all(s32 flags) { ((void(*)(WorkModule*,s32))_vt[0x220/8])(this,flags); }
    // 0x228–0x240: unknown
    s32 get_param_int(s32 hash1, s32 hash2) { return ((s32(*)(WorkModule*,s32,s32))_vt[0x248/8])(this,hash1,hash2); }
    // 0x250: unknown
    s64 get_param_int64(s32 hash1, s32 hash2) { return ((s64(*)(WorkModule*,s32,s32))_vt[0x258/8])(this,hash1,hash2); }
    // 0x260: unknown
    f32 get_param_float(s32 hash1, s32 hash2) { return ((f32(*)(WorkModule*,s32,s32))_vt[0x268/8])(this,hash1,hash2); }
    // 0x270: unknown
    void set_customize_no(s32 p1, s32 p2) { ((void(*)(WorkModule*,s32,s32))_vt[0x278/8])(this,p1,p2); }
    void calc_param(bool p1, bool p2) { ((void(*)(WorkModule*,bool,bool))_vt[0x280/8])(this,p1,p2); }
};

} // namespace app
