#pragma once

#include "types.h"
#include "app/placeholders/BossEntity.h"

namespace app {

// BossManagerInner — the data block pointed to by BossManager+0x8.
// Name is NOT confirmed from .dynsym; "Inner" is a placeholder.
// Fields mapped from: is_boss_stop, is_boss_no_dead, is_stoppable_se_impl,
//   notify_on_boss_defeat_impl, send_event_on_boss_dead, send_event_on_boss_defeat.
//
// Total size = 0x238 = 568 bytes
//   [derived: FUN_7101344cf0 @ 0x710134b1d0..0x710134b220:
//     je_aligned_alloc(align=0x10, size=0x238); ctor writes observed
//     up to offset +0x230. Ctor also allocates a 0x30 B sub-object (three
//     pairs of s32 boss-kind ids {0x18e,0x16f / 0x188,0x180 / 0x175,0x172})
//     and stores its pointer at +0x10 (overwriting part of the unk window).]
// Known fields end at +0x164 (stop_count); bytes +0x168..+0x237 are the
// runtime task/list heads + static kind-id sub pointer — uncharted but
// safe for rollback to snapshot opaquely.
struct BossManagerInner {
    u8  unk_0x00[0x100];
    s32 state;              // +0x100 [derived: is_stoppable_se_impl checks == 4]
    u8  unk_0x104[0xC];
    BossEntitySlot* entity_list_begin; // +0x110 [derived: boss entity vector data, 0x10-stride shared_ptr entries]
    BossEntitySlot* entity_list_end;   // +0x118 [derived: boss entity vector end]
    u8  unk_0x120[0x8];
    u64 boss_kind_id;       // +0x128 [derived: FUN_7101798450 reads as u64, compares low word to 0x19a/0x169]
    u8  unk_0x130[0x8];
    s32 boss_target_id;     // +0x138 [derived: FUN_7101798450 checks == -1 (0xFFFFFFFF = no target)]
    u8  unk_0x13C[0x8];
    u32 finish_param_1;     // +0x144 [derived: send_event_on_boss_dead passes to vtable[0x28] callback]
    u32 finish_param_2;     // +0x148 [derived: send_event_on_boss_dead passes to vtable[0x60] callback]
    u8  unk_0x14C[0x2];
    u8  no_dead_flag;       // +0x14E [derived: is_boss_no_dead checks != 0]
    u8  unk_0x14F[0x15];
    s32 stop_count;         // +0x164 [derived: is_boss_stop checks > 0]
    u8  unk_0x168[0xD0];    // +0x168..+0x237 [uncharted tail; ctor writes linked-list heads
                            //  and vtable-pointer constants here — see docs/rollback/memory_map.md §7]
};
static_assert(sizeof(BossManagerInner) == 0x238,
              "BossManagerInner size is 0x238 (derived: je_aligned_alloc in FUN_7101344cf0 @ 0x710134b1d0)");

// BossManager — singleton accessed via lib::Singleton<app::BossManager>::instance_.
// Name confirmed from .dynsym: _ZN3lib9SingletonIN3app11BossManagerEE9instance_E
// Singleton slot: DAT_71052b7ef8 [derived: FUN_7101344cf0 @ 0x710134b440
//   `str x20, [x19, #0xef8]` where x19 = 0x71052b7000]
// Total size = 0x10 = 16 bytes (outer wrapper; all real state lives in `inner`)
//   [derived: FUN_7101344cf0 @ 0x710134b16c..0x710134b1b8:
//     je_aligned_alloc(align=0x10, size=0x10); vtable stored at +0x00, inner at +0x08]
struct BossManager {
    void** _vt;              // +0x00 [derived: ctor writes 0x7104f73b60 here before storing inner]
    BossManagerInner* inner; // +0x08 [derived: all boss functions deref this first]
};
static_assert(sizeof(BossManager) == 0x10,
              "BossManager outer wrapper size is 0x10 (derived: je_aligned_alloc in FUN_7101344cf0 @ 0x710134b174)");

} // namespace app
