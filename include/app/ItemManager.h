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
// Singleton at DAT_71052c3070 [derived: find_active_item_from_id @ 0x71015ca930
//   disasm `adrp x8, 0x71052c3000; ldr x9, [x8, #0x70]`; NOT DAT_71052c25b0
//   which is the RNG state singleton; NOT DAT_71052c2b88 which is the .begin
//   of a static std::vector<u32>{0xe3} lookup table — see memory_map.md correction]
// Total size = 0xD8 = 216 bytes
//   [derived: FUN_7101344cf0 @ 0x71013494d4..0x710134953c:
//     je_aligned_alloc(align=0x10, size=0xd8) → ctor 0x71015d2260 → store to slot]
// Fields past +0x30 (0xA0 bytes, +0x38..+0xD7) are uncharted; they are populated
// by ctor helper 0x71015d2260 and hold additional sub-state pointers / config.
// [derived: Ghidra analysis of find_active_item_from_id, remove_item_from_id, send_event_on_start_boss_entry]
struct ItemManager {
    u8 unk_0x00[0x10];
    ItemEntry** pending_begin;      // +0x10 [derived: remove_item_from_id iterates +0x10..+0x18]
    ItemEntry** pending_end;        // +0x18
    u8 unk_0x20[0x08];
    ItemEntry** active_begin;       // +0x28 [derived: find_active_item_from_id iterates +0x28..+0x30]
    ItemEntry** active_end;         // +0x30
    u8 unk_0x38[0xA0];              // +0x38..+0xD7 [unknown, populated by ctor helper 0x71015d2260]
};
static_assert(sizeof(ItemManager) == 0xD8,
              "ItemManager root size is 0xD8 (derived: je_aligned_alloc in FUN_7101344cf0)");

} // namespace app
