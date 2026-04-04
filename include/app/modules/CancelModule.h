#pragma once
#include "types.h"

namespace app {

// CancelModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// Module accessed via BattleObjectModuleAccessor +0x128
struct CancelModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    bool is_enable_cancel() { return ((bool(*)(CancelModule*))_vt[0x48/8])(this); }
    void enable_cancel() { ((void(*)(CancelModule*))_vt[0x50/8])(this); }
};

} // namespace app
