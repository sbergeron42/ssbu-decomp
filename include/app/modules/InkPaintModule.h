#pragma once
#include "types.h"

namespace app {

// InkPaintModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// Module accessed via BattleObjectModuleAccessor +0x198
struct InkPaintModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    f32 ink(u64 p1) { return ((f32(*)(InkPaintModule*,u64))_vt[0x60/8])(this,p1); }
    f32 ink_max() { return ((f32(*)(InkPaintModule*))_vt[0x68/8])(this); }
    void add_ink(u64 p1) { ((void(*)(InkPaintModule*,u64))_vt[0x70/8])(this,p1); }
    void set_ink(u64 p1) { ((void(*)(InkPaintModule*,u64))_vt[0x78/8])(this,p1); }
    void reset_ink() { ((void(*)(InkPaintModule*))_vt[0x80/8])(this); }
    u32 get_ink_color() { return ((u32(*)(InkPaintModule*))_vt[0x88/8])(this); }
    void set_special_paint(u64 p1) { ((void(*)(InkPaintModule*,u64))_vt[0xb8/8])(this,p1); }
};

} // namespace app
