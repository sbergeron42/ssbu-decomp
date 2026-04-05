#pragma once
#include "types.h"

namespace app {

// StopModule — accessed at BattleObjectModuleAccessor+0x90
// Manages hitstop, item stop, and other stop effects during combat.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x48-0xe8).
// All method names derived from .dynsym lua_bind::StopModule__*_impl dispatcher analysis.
struct StopModule {
    void** _vt;

    // -- Hit stop (0x48) -- [confirmed: lua_bind API names]
    void cancel_hit_stop() { ((void(*)(StopModule*))_vt[0x48/8])(this); }

    // -- Other stop (0x50-0x60) --
    void set_other_stop(u64 p1, u64 p2) { ((void(*)(StopModule*,u64,u64))_vt[0x50/8])(this,p1,p2); }
    void* get_other_stop(u64 p1) { return ((void*(*)(StopModule*,u64))_vt[0x58/8])(this,p1); }
    void* cancel_other_stop(u64 p1) { return ((void*(*)(StopModule*,u64))_vt[0x60/8])(this,p1); }

    // -- Item stop (0x68-0x78) --
    void set_item_stop(u64 p1) { ((void(*)(StopModule*,u64))_vt[0x68/8])(this,p1); }
    u32 get_item_stop() { return ((u32(*)(StopModule*))_vt[0x70/8])(this); }
    void cancel_item_stop() { ((void(*)(StopModule*))_vt[0x78/8])(this); }

    // -- Link stop (0x80) --
    void set_link_stop(bool p1, bool p2) { ((void(*)(StopModule*,bool,bool))_vt[0x80/8])(this,p1,p2); }

    // -- State queries (0x88-0xb8) --
    bool is_stop() { return ((bool(*)(StopModule*))_vt[0x88/8])(this); }
    bool is_special_stop() { return ((bool(*)(StopModule*))_vt[0x90/8])(this); }
    bool is_hit() { return ((bool(*)(StopModule*))_vt[0x98/8])(this); }
    bool is_damage() { return ((bool(*)(StopModule*))_vt[0xa0/8])(this); }
    bool is_item() { return ((bool(*)(StopModule*))_vt[0xb0/8])(this); }
    bool is_other() { return ((bool(*)(StopModule*))_vt[0xb8/8])(this); }

    // -- Frame control (0xc8-0xe8) --
    u32 get_hit_stop_real_frame() { return ((u32(*)(StopModule*))_vt[0xc8/8])(this); }
    void set_hit_stop_frame(u64 p1, bool p2) { ((void(*)(StopModule*,u64,bool))_vt[0xd0/8])(this,p1,p2); }
    void set_hit_stop_frame_fix(u64 p1) { ((void(*)(StopModule*,u64))_vt[0xd8/8])(this,p1); }
    void set_special_stop(bool p1) { ((void(*)(StopModule*,bool))_vt[0xe0/8])(this,p1); }
    void end_stop() { ((void(*)(StopModule*))_vt[0xe8/8])(this); }
};

} // namespace app
