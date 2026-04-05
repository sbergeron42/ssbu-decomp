#pragma once
#include "types.h"

namespace app {

// MotionAnimcmdModule — accessed at BattleObjectModuleAccessor+0x188
// Manages animation command (animcmd) script execution for motion lines.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x58-0xd0).
// All method names derived from .dynsym lua_bind::MotionAnimcmdModule__*_impl dispatcher analysis.
struct MotionAnimcmdModule {
    void** _vt;

    // -- Script execution (0x58-0x80) -- [confirmed: lua_bind API names]
    void exec_motion_lines() { ((void(*)(MotionAnimcmdModule*))_vt[0x58/8])(this); }
    void change_script_motion_lines(u64 p1, bool p2, bool p3, bool p4) { ((void(*)(MotionAnimcmdModule*,u64,bool,bool,bool))_vt[0x68/8])(this,p1,p2,p3,p4); }
    void* change_script_motion_partial_lines(u64 p1, bool p2, bool p3) { return ((void*(*)(MotionAnimcmdModule*,u64,bool,bool))_vt[0x70/8])(this,p1,p2,p3); }
    void* call_script_single(u64 p1, u64 p2, u64 p3) { return ((void*(*)(MotionAnimcmdModule*,u64,u64,u64))_vt[0x78/8])(this,p1,p2,p3); }
    void* change_script_motion_line_single(u64 p1, u64 p2, u64 p3) { return ((void*(*)(MotionAnimcmdModule*,u64,u64,u64))_vt[0x80/8])(this,p1,p2,p3); }

    // -- Initialization/flush (0x88-0x98) --
    void exec_motion_lines_initialize(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0x88/8])(this,p1); }
    void flush_current_motion() { ((void(*)(MotionAnimcmdModule*))_vt[0x90/8])(this); }
    void flush(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0x98/8])(this,p1); }

    // -- Sleep control (0xa0-0xc0) --
    void set_sleep(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0xa0/8])(this,p1); }
    void set_sleep_game(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0xa8/8])(this,p1); }
    void set_sleep_effect(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0xb0/8])(this,p1); }
    void set_sleep_sound(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0xb8/8])(this,p1); }
    bool is_sleep() { return ((bool(*)(MotionAnimcmdModule*))_vt[0xc0/8])(this); }

    // -- Misc (0xc8-0xd0) --
    void enable_skip_delay_update() { ((void(*)(MotionAnimcmdModule*))_vt[0xc8/8])(this); }
    void set_change_partial_immediate(bool p1) { ((void(*)(MotionAnimcmdModule*,bool))_vt[0xd0/8])(this,p1); }
};

} // namespace app
