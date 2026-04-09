#pragma once

#include "types.h"

namespace app {

// ItemStateInfo — sub-object referenced at ItemEntry+0x90
// +0x18 [inferred: is_removed/dead flag, u8 — checked in find/iterate loops before matching id]
// [derived: Ghidra analysis of find_active_item_from_id (0x71015ca930), send_event_on_start_boss_entry (0x71015c8450)]
struct ItemStateInfo {
    u8 unk_0x00[0x18];
    u8 is_removed;    // +0x18 [inferred: nonzero = dead/removed, skip during active iteration]
};

// ItemEntry — individual item in the ItemManager lists
// +0x00: vtable pointer [derived: remove_item_from_id dispatches through vtable[0x520/8]]
// +0x08: battle_object_id [derived: matched against param in find/remove functions]
// +0x90: state_info pointer [derived: dereferenced then +0x18 checked for removed flag]
// +0x98: module_accessor [derived: find_active_item_from_id returns item+0x98]
// [derived: Ghidra analysis of 0x71015ca930, 0x71015ca990, 0x71015c8450]
struct ItemEntry {
    void** _vt;                     // +0x00
    u32 battle_object_id;           // +0x08 [derived: compared against param in find/iterate loops]
    u8 unk_0x0C[0x84];             // +0x0C
    ItemStateInfo* state_info;      // +0x90 [derived: deref'd then +0x18 checked in active list iteration]
    void* module_accessor;          // +0x98 [derived: find_active_item_from_id returns this as accessor ptr]

    // vtable dispatch for removal
    // [0x520/8 = slot 164]: remove(s32) — called by remove_item_from_id
    void remove(s32 param) { ((void(*)(ItemEntry*, s32))_vt[0x520/8])(this, param); }
};

// ItemManager — manages active and pending item lists
// +0x10/+0x18: pending remove list (begin/end pointers to ItemEntry*[])
// +0x28/+0x30: active item list (begin/end pointers to ItemEntry*[])
// Singleton at DAT_71052c25b0
// [derived: Ghidra analysis of find_active_item_from_id, remove_item_from_id, send_event_on_start_boss_entry]
struct ItemManager {
    u8 unk_0x00[0x10];
    ItemEntry** pending_begin;      // +0x10 [derived: remove_item_from_id iterates +0x10..+0x18]
    ItemEntry** pending_end;        // +0x18
    u8 unk_0x20[0x08];
    ItemEntry** active_begin;       // +0x28 [derived: find_active_item_from_id iterates +0x28..+0x30]
    ItemEntry** active_end;         // +0x30
};

} // namespace app
