#pragma once

#include "types.h"

namespace app {

// Offsets from Ghidra analysis of 13.0.4
// This is the main module accessor — first param to most lua_bind functions
struct BattleObjectModuleAccessor {
    u8 pad_0x00[0x38];
    void* posture_module;            // +0x38  PostureModule (vtable dispatch)
    void* status_module;             // +0x40  StatusModule (vtable dispatch)
    void* fighter_control_module;    // +0x48  FighterControlModule
    void* work_module;               // +0x50  WorkModule (vtable dispatch)
    u8 pad_0x58[0x10];
    void* item_kinetic_module;       // +0x68  ItemKineticModule
    u8 pad_0x70[0x38];
    void* damage_module;             // +0xA8  DamageModule (vtable dispatch)
    u8 pad_0xB0[0x10];
    void* fighter_area_module;       // +0xC0  FighterAreaModule
};

} // namespace app
