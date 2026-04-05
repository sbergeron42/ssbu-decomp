#pragma once
#include "types.h"

namespace app {

// ShadowModule — accessed at BattleObjectModuleAccessor+0x180
// Manages shadow rendering beneath battle objects.
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x48-0x78).
// All method names derived from .dynsym lua_bind::ShadowModule__*_impl dispatcher analysis.
struct ShadowModule {
    void** _vt;

    // -- Draw control (0x48-0x50) -- [confirmed: lua_bind API names]
    void set_draw(u64 p1, bool p2) { ((void(*)(ShadowModule*,u64,bool))_vt[0x48/8])(this,p1,p2); }
    void set_draw_status(bool p1) { ((void(*)(ShadowModule*,bool))_vt[0x50/8])(this,p1); }

    // -- Size/offset (0x60, 0x78) --
    void set_size() { ((void(*)(ShadowModule*))_vt[0x60/8])(this); }
    void set_offset_y() { ((void(*)(ShadowModule*))_vt[0x78/8])(this); }
};

} // namespace app
