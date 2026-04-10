#pragma once

#include "types.h"

namespace app {

struct BossEntity;

// BossEntityVtable — vtable layout for boss entity objects.
// Only slots confirmed from binary evidence are typed; others are void*.
// Slot indices are byte-offset / 8 (pointer size).
struct BossEntityVtable {
    void*  slot_0;                          // 0x00
    void*  slot_1;                          // 0x08
    bool (*is_expired)(BossEntity*);        // 0x10 [derived: resolve_entity in BossManager.cpp checks !vtable[2](entity)]
    void*  slot_3;                          // 0x18
    void*  slot_4;                          // 0x20
    void*  slot_5;                          // 0x28
    s32  (*get_hash)(BossEntity*);          // 0x30 [derived: boss iteration checks vtable[6](entity) == hash]
    void*  slot_7;                          // 0x38
    void*  slot_8;                          // 0x40
    void*  slot_9;                          // 0x48
    void (*on_defeat)(BossEntity*);         // 0x50 [derived: boss iteration calls vtable[10](entity) on match]
};

// BossEntity — managed boss entity object.
// Accessed via shared_ptr slots in BossManagerInner entity list.
// Real class name unknown; entity is resolved from shared_ptr or falls back
// to default singleton at 0x7104f73b70.
struct BossEntity {
    BossEntityVtable* _vt;                  // +0x00 vtable pointer
    // Remaining fields unknown — entity is only accessed via vtable dispatch
    // in currently decompiled functions.
};

// BossEntitySlot — shared_ptr<BossEntity> storage slot (0x10 stride).
// The entity list in BossManagerInner is a std::vector of these.
// [derived: send_event_on_boss_dead/defeat iterate with 0x10 stride,
//  slot[0] = managed pointer, slot[1] = control block]
struct BossEntitySlot {
    BossEntity* entity;                     // +0x00 managed pointer
    void*       control_block;              // +0x08 shared_ptr control block
};

} // namespace app
