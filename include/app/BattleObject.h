#pragma once

#include "types.h"

namespace app {

struct BattleObjectModuleAccessor;

// BattleObject — base class for Fighter, Weapon, Item
// Offsets derived from FUN_71003a7740 (activate) and FUN_71003a7850 (deactivate).
// [derived: +0x08 read as u32 in BOM register call (FUN_71003aeef0)]
// [derived: +0x10 read as u32 and passed to module vtable[0x28/8]]
// [derived: +0x20 dereferenced as void** (module group), vtable dispatch]
// [derived: +0x3a written as u8=4 (active) or u8=3 (inactive)]
// [derived: +0x3c written as u8=0xFF (no team)]
struct BattleObject {
    u8 pad_0x00[0x08];
    u32 object_id;                          // +0x08 [derived: FUN_71003a7740 reads +0x08 for BOM register]
    u8 pad_0x0C[0x04];
    u32 battle_object_id;                   // +0x10 [derived: FUN_71003a7740 reads +0x10 for module init param]
    u8 pad_0x14[0x0C];
    void** module_group;                    // +0x20 [derived: FUN_71003a7740/71003a7850 deref +0x20, vtable dispatch]
    u8 pad_0x28[0x12];
    u8 category;                            // +0x3a [derived: FUN_71003a7740 writes 4 (active), FUN_71003a7850 writes 3]
    u8 pad_0x3B;
    u8 team;                                // +0x3c [derived: FUN_71003a7740/a7850 writes 0xFF (none)]
    u8 pad_0x3D[0x153];
    u32 unk_0x190;                          // +0x190 [derived: FUN_7102208b10 reads as u32, passed to FUN_71003ab390]
    u8 pad_0x194[0xC];
    BattleObjectModuleAccessor* module_accessor; // +0x1a0 [derived: 261 occurrences across 31 src/ files via *(ctx+0x1a0)]
};

// AttackListContainer — internal container for attack entry arrays
// [derived: FUN_71003fffa0 reads count at +0x10, base pointer at +0x18,
//  dispatches vtable[0xe0/8] with stride-0x1c0 entries]
struct AttackListContainer {
    void** _vt;                             // +0x00 vtable
    u8 pad_0x08[0x08];
    s32 count;                              // +0x10 [derived: FUN_71003fffa0 reads as loop bound]
    u8* entries_base;                       // +0x18 [derived: FUN_71003fffa0 reads as base for stride-0x1c0 array]
};

} // namespace app
