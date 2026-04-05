#pragma once
#include "types.h"

namespace app {

// TeamModule — accessed at BattleObjectModuleAccessor+0xD8
// Manages team assignment and hit-team relationships for battle objects.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x50-0xd8).
// All method names derived from .dynsym lua_bind::TeamModule__*_impl dispatcher analysis.
struct TeamModule {
    void** _vt;

    // -- Team identity (0x50-0x68) -- [confirmed: lua_bind API names]
    u32 team_no() { return ((u32(*)(TeamModule*))_vt[0x50/8])(this); }
    u32 team_second_no() { return ((u32(*)(TeamModule*))_vt[0x58/8])(this); }
    void set_team(u64 p1, bool p2) { ((void(*)(TeamModule*,u64,bool))_vt[0x60/8])(this,p1,p2); }
    void set_team_second(u64 p1) { ((void(*)(TeamModule*,u64))_vt[0x68/8])(this,p1); }

    // -- Hit team (0x78-0x90) --
    u32 hit_team_no() { return ((u32(*)(TeamModule*))_vt[0x78/8])(this); }
    u32 hit_team_second_no() { return ((u32(*)(TeamModule*))_vt[0x80/8])(this); }
    void set_hit_team(u64 p1) { ((void(*)(TeamModule*,u64))_vt[0x88/8])(this,p1); }
    void set_hit_team_second(u64 p1) { ((void(*)(TeamModule*,u64))_vt[0x90/8])(this,p1); }

    // -- Owner (0xa0-0xa8) --
    void set_team_owner_id(u64 p1) { ((void(*)(TeamModule*,u64))_vt[0xa0/8])(this,p1); }
    u32 team_owner_id() { return ((u32(*)(TeamModule*))_vt[0xa8/8])(this); }

    // -- Ditto (Metamon) (0xd8) --
    u32 metamon_owner_fighter_entry_id() { return ((u32(*)(TeamModule*))_vt[0xd8/8])(this); }
};

} // namespace app
