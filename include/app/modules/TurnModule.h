#pragma once
#include "types.h"

namespace app {

// TurnModule — accessed at BattleObjectModuleAccessor+0xF0
// Manages turn-around logic for battle objects (facing direction changes).
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x48-0x98).
// All method names derived from .dynsym lua_bind::TurnModule__*_impl dispatcher analysis.
struct TurnModule {
    void** _vt;

    // -- Turn control (0x48-0x58) -- [confirmed: lua_bind API names]
    void set_turn(u64 p1, bool p2, bool p3, bool p4) { ((void(*)(TurnModule*,u64,bool,bool,bool))_vt[0x48/8])(this,p1,p2,p3,p4); }
    void end_turn() { ((void(*)(TurnModule*))_vt[0x58/8])(this); }

    // -- State queries (0x68-0x70) --
    bool is_turn() { return ((bool(*)(TurnModule*))_vt[0x68/8])(this); }
    bool is_extern() { return ((bool(*)(TurnModule*))_vt[0x70/8])(this); }

    // -- Misc (0x90-0x98) --
    void set_omit_intermediate(bool p1) { ((void(*)(TurnModule*,bool))_vt[0x90/8])(this,p1); }
    void ry_reverse() { ((void(*)(TurnModule*))_vt[0x98/8])(this); }
};

} // namespace app
