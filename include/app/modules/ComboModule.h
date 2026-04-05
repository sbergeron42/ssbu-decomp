#pragma once
#include "types.h"

namespace app {

// ComboModule — accessed at BattleObjectModuleAccessor+0xB8
// Handles combo tracking and input validation.
// Vtable layout recovered from lua_bind dispatchers.
// All method names derived from .dynsym lua_bind::ComboModule__*_impl dispatcher analysis.
struct ComboModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void set(u64 p1) { ((void(*)(ComboModule*,u64))_vt[9])(this,p1); }                         // 0x48
    void reset() { ((void(*)(ComboModule*))_vt[11])(this); }                                    // 0x58
    void clear_setting() { ((void(*)(ComboModule*))_vt[12])(this); }                            // 0x60
    u32 count() { return ((u32(*)(ComboModule*))_vt[13])(this); }                               // 0x68
    bool is_enable_combo_input() { return ((bool(*)(ComboModule*))_vt[22])(this); }              // 0xB0
};

} // namespace app
