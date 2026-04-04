#pragma once

#include "types.h"

namespace app {

struct StatusModule;

// Circular buffer for queued status change requests
struct StatusChangeQueue {
    void**  vtable;           // +0x00 (StatusModule+0x10)
    u64     capacity;         // +0x08 (StatusModule+0x18)
    u64     length;           // +0x10 (StatusModule+0x20)
    u64     start;            // +0x18 (StatusModule+0x28)
    u64     end;              // +0x20 (StatusModule+0x30)
    void*   status_changes;   // +0x28 (StatusModule+0x38) — array of {s32 kind, bool clear_cmd}
};

// Circular buffer for previous status kind history
struct PreviousStatusKinds {
    u8      pad_0x00[0x08];
    u64     capacity;         // +0x08
    u64     length;           // +0x10
    u64     start;            // +0x18
    u8      pad_0x20[0x08];
    s32*    array;            // +0x28
};

// StatusModule vtable — function pointer table for virtual dispatch
// Offsets are byte offsets into the vtable (divide by 8 for slot index)
struct StatusModuleVtbl {
    void  (*destructor)(StatusModule*);                                               // 0x00
    void* _vfn_0x08;                                                                  // 0x08
    void* _vfn_0x10;                                                                  // 0x10
    void* _vfn_0x18;                                                                  // 0x18
    void* _vfn_0x20;                                                                  // 0x20
    void* _vfn_0x28;                                                                  // 0x28
    void* _vfn_0x30;                                                                  // 0x30 Finalize
    void* _vfn_0x38;                                                                  // 0x38 StartModule
    void* _vfn_0x40;                                                                  // 0x40 EndModule
    void  (*ChangeStatusRequest)(StatusModule*, s32, bool);                           // 0x48
    void  (*ChangeStatusRequestFromScript)(StatusModule*, s32, bool);                 // 0x50
    void  (*DeleteStatusRequestFromScript)(StatusModule*);                            // 0x58
    void* (*StatusKindQueFromScript)(StatusModule*);                                  // 0x60
    void* _vfn_0x68;                                                                  // 0x68
    void* _vfn_0x70;                                                                  // 0x70 EnableLuaStatus
    void* _vfn_0x78;                                                                  // 0x78
    void* _vfn_0x80;                                                                  // 0x80
    void* _vfn_0x88;                                                                  // 0x88
    void* _vfn_0x90;                                                                  // 0x90
    void* _vfn_0x98;                                                                  // 0x98
    void* _vfn_0xa0;                                                                  // 0xA0
    void* _vfn_0xa8;                                                                  // 0xA8
    void* _vfn_0xb0;                                                                  // 0xB0
    void* _vfn_0xb8;                                                                  // 0xB8
    void* _vfn_0xc0;                                                                  // 0xC0
    void* _vfn_0xc8;                                                                  // 0xC8
    void* _vfn_0xd0;                                                                  // 0xD0
    void* _vfn_0xd8;                                                                  // 0xD8
    void* _vfn_0xe0;                                                                  // 0xE0
    void* _vfn_0xe8;                                                                  // 0xE8
    void* _vfn_0xf0;                                                                  // 0xF0
    void* _vfn_0xf8;                                                                  // 0xF8
    void* _vfn_0x100;                                                                 // 0x100
    void* _vfn_0x108;                                                                 // 0x108
    s32   (*StatusKind)(StatusModule*);                                                // 0x110
    s32   (*StatusKindNext)(StatusModule*);                                            // 0x118
    void  (*SetStatusKindInterrupt)(StatusModule*, s32);                              // 0x120
    s32   (*StatusKindInterrupt)(StatusModule*);                                       // 0x128
    void* _vfn_0x130;                                                                 // 0x130
    void* _vfn_0x138;                                                                 // 0x138
    bool  (*IsChanging)(StatusModule*);                                                // 0x140
    s32   (*PrevStatusKind)(StatusModule*, u64);                                       // 0x148
    void* _vfn_0x150;                                                                 // 0x150
    void  (*ChangeStatusForce)(StatusModule*, s32, bool);                             // 0x158
    void* _vfn_0x160;                                                                 // 0x160
    s32   (*SituationKind)(StatusModule*);                                              // 0x168
    s32   (*PrevSituationKind)(StatusModule*);                                          // 0x170
    void  (*SetSituationKind)(StatusModule*, s32, bool);                              // 0x178
    void* _vfn_0x180;                                                                 // 0x180 SetGroundKindInfo
    void  (*SetKeepSituationAir)(StatusModule*, bool);                                // 0x188
    void  (*SetAgentStatusData)(StatusModule*, void*);                                // 0x190
    void* _vfn_0x198;                                                                 // 0x198
    void  (*SetKineticType)(StatusModule*, s32);                                      // 0x1A0
    void  (*SetSucceedsBit)(StatusModule*, u64);                                      // 0x1A8
    void* _vfn_0x1b0;                                                                 // 0x1B0
    void* _vfn_0x1b8;                                                                 // 0x1B8
    void* _vfn_0x1c0;                                                                 // 0x1C0
    void  (*InitSettings)(StatusModule*, s32, s32, u32, s32, bool, s32, s32, s32, s32); // 0x1C8
    void* _vfn_0x1d0;                                                                 // 0x1D0 SetWorkKeep
    void* _vfn_0x1d8;                                                                 // 0x1D8
    void* _vfn_0x1e0;                                                                 // 0x1E0
    void* _vfn_0x1e8;                                                                 // 0x1E8
    void* _vfn_0x1f0;                                                                 // 0x1F0 ChangeStatus
};

// StatusModule — manages fighter state transitions
// Accessed via BattleObjectModuleAccessor at offset +0x40
struct StatusModule {
    StatusModuleVtbl*       vtbl;                           // +0x00
    void*                   owner;                          // +0x08 — BattleObject*
    StatusChangeQueue       status_change_queue;            // +0x10 — embedded, 0x30 bytes
    u8                      _pad_0x40[0x40];                // +0x40 — unknown gap
    PreviousStatusKinds*    previous_status_kinds;          // +0x80
    u8                      _pad_0x88[0x10];                // +0x88 — unknown
    s32                     status_kind;                    // +0x98
    s32                     status_kind_next;               // +0x9C
    s32                     status_kind_interrupt;          // +0xA0
    s32                     status_request_from_script;     // +0xA4
    void*                   agent_status_data;              // +0xA8
    u64                     _unknown_0xB0;                  // +0xB0
    s32                     kinetic_type;                   // +0xB8
    s32                     succeeds_bits;                  // +0xBC
    u32                     permanent_succeeds_bits;        // +0xC0
    u8                      _pad_0xC4[0x18];                // +0xC4 — unknown gap
    s32                     situation_kind;                  // +0xDC
    s32                     prev_situation_kind;             // +0xE0
    u8                      _pad_0xE4[0x04];                // +0xE4 — padding
    void*                   current_status_script;          // +0xE8 — StatusScript**
    bool                    flag_when_running_lua_main;     // +0xF0
    bool                    flag_when_lua_ending;           // +0xF1
    bool                    disable_lua_status;             // +0xF2
    u8                      _pad_0xF3;                      // +0xF3
    bool                    is_changing;                    // +0xF4
    bool                    disable_status;                 // +0xF5
    bool                    clear_command_from_script;      // +0xF6
    bool                    keep_situation_kind;            // +0xF7
    bool                    keep_situation_air;             // +0xF8
    bool                    flag_when_cpp_ending;           // +0xF9
    u8                      _pad_0xFA[0x06];                // +0xFA — padding to 0x100
};

} // namespace app
