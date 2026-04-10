#pragma once

#include "types.h"
#include "app/placeholders/BossEntity.h"

namespace app {

// BossManagerInner — the data block pointed to by BossManager+0x8.
// Name is NOT confirmed from .dynsym; "Inner" is a placeholder.
// Fields mapped from: is_boss_stop, is_boss_no_dead, is_stoppable_se_impl,
//   notify_on_boss_defeat_impl, send_event_on_boss_dead, send_event_on_boss_defeat.
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
};

// BossManager — singleton accessed via lib::Singleton<app::BossManager>::instance_.
// Name confirmed from .dynsym: _ZN3lib9SingletonIN3app11BossManagerEE9instance_E
struct BossManager {
    u8  unk_0x00[0x8];
    BossManagerInner* inner; // +0x8 [derived: all boss functions deref this first]
};

} // namespace app
