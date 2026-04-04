#pragma once
#include "types.h"

namespace app {

// ShakeModule — accessed at BattleObjectModuleAccessor+0x168
// Manages screen/object shake effects (hitstop rumble, camera shake).
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x50-0xb8).
struct ShakeModule {
    void** _vt;

    // -- Request (0x50-0x58) -- [confirmed: lua_bind API names]
    void req(u64 p1, u64 p2, bool p3, u64 p4, bool p5, bool p6) { ((void(*)(ShakeModule*,u64,u64,bool,u64,bool,bool))_vt[0x50/8])(this,p1,p2,p3,p4,p5,p6); }
    void req_time_scale(u64 p1, u64 p2, bool p3, u64 p4, bool p5, bool p6, u64 p7) { ((void(*)(ShakeModule*,u64,u64,bool,u64,bool,bool,u64))_vt[0x58/8])(this,p1,p2,p3,p4,p5,p6,p7); }

    // -- Extend/stop (0x60-0x70) --
    void extend(u64 p1, u64 p2) { ((void(*)(ShakeModule*,u64,u64))_vt[0x60/8])(this,p1,p2); }
    void stop() { ((void(*)(ShakeModule*))_vt[0x68/8])(this); }
    void stop_kind(u64 p1) { ((void(*)(ShakeModule*,u64))_vt[0x70/8])(this,p1); }

    // -- State/offset (0x88-0xa0) --
    bool is_shake() { return ((bool(*)(ShakeModule*))_vt[0x88/8])(this); }
    void* offset(u64 p1) { return ((void*(*)(ShakeModule*,u64))_vt[0x90/8])(this,p1); }
    void enable_offset(u64 p1) { ((void(*)(ShakeModule*,u64))_vt[0x98/8])(this,p1); }
    void disable_offset() { ((void(*)(ShakeModule*))_vt[0xa0/8])(this); }

    // -- Scale/axis/slow (0xa8-0xb8) --
    void set_scale_kind(u64 p1) { ((void(*)(ShakeModule*,u64))_vt[0xa8/8])(this,p1); }
    void set_axis_xy_kind(u64 p1, bool p2) { ((void(*)(ShakeModule*,u64,bool))_vt[0xb0/8])(this,p1,p2); }
    void set_ignore_slow(bool p1) { ((void(*)(ShakeModule*,bool))_vt[0xb8/8])(this,p1); }
};

} // namespace app
