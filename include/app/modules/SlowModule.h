#pragma once
#include "types.h"

namespace app {

// SlowModule — accessed at BattleObjectModuleAccessor+0x170
// Manages slow-motion effects (hitstop slow, special slow, whole-game slow).
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x58-0xe0).
struct SlowModule {
    void** _vt;

    // -- State query (0x58) -- [confirmed: lua_bind API names]
    bool is_slow() { return ((bool(*)(SlowModule*))_vt[0x58/8])(this); }

    // -- Set/clear (0x60-0x98) --
    void set(u64 p1, u64 p2, u64 p3, bool p4, u64 p5) { ((void(*)(SlowModule*,u64,u64,u64,bool,u64))_vt[0x60/8])(this,p1,p2,p3,p4,p5); }
    f32 mag(u64 p1) { return ((f32(*)(SlowModule*,u64))_vt[0x70/8])(this,p1); }
    f32 rate_ignore_effect() { return ((f32(*)(SlowModule*))_vt[0x78/8])(this); }
    f32 frame(u64 p1) { return ((f32(*)(SlowModule*,u64))_vt[0x80/8])(this,p1); }
    void clear() { ((void(*)(SlowModule*))_vt[0x88/8])(this); }
    void clear_2(u64 p1) { ((void(*)(SlowModule*,u64))_vt[0x90/8])(this,p1); }
    void clear_immediate(u64 p1, bool p2) { ((void(*)(SlowModule*,u64,bool))_vt[0x98/8])(this,p1,p2); }

    // -- Rate/skip (0xa8-0xb8) --
    f32 rate() { return ((f32(*)(SlowModule*))_vt[0xa8/8])(this); }
    bool is_skip() { return ((bool(*)(SlowModule*))_vt[0xb0/8])(this); }
    bool is_prev_skip() { return ((bool(*)(SlowModule*))_vt[0xb8/8])(this); }

    // -- Whole-game slow (0xc0-0xe0) --
    void set_whole(u64 p1, u64 p2) { ((void(*)(SlowModule*,u64,u64))_vt[0xc0/8])(this,p1,p2); }
    void clear_whole() { ((void(*)(SlowModule*))_vt[0xc8/8])(this); }
    f32 whole_mag() { return ((f32(*)(SlowModule*))_vt[0xd0/8])(this); }
    void set_whole_frame(u64 p1) { ((void(*)(SlowModule*,u64))_vt[0xd8/8])(this,p1); }
    f32 whole_frame() { return ((f32(*)(SlowModule*))_vt[0xe0/8])(this); }
};

} // namespace app
