#pragma once

#include "types.h"

namespace app {

struct StatusModule;

// Circular buffer for queued status change requests
// [derived: change_status_request_impl (.dynsym) dispatches to vtable+0x48 (ChangeStatusRequest),
//  which enqueues into this embedded struct at StatusModule+0x10]
struct StatusChangeQueue {
    void**  vtable;           // +0x00 (StatusModule+0x10) [derived: standard vtable ptr, first field]
    u64     capacity;         // +0x08 (StatusModule+0x18) [inferred: circular buffer size field, pattern matches nn::util::RingBuffer]
    u64     length;           // +0x10 (StatusModule+0x20) [inferred: current element count in circular buffer]
    u64     start;            // +0x18 (StatusModule+0x28) [inferred: read cursor for circular buffer]
    u64     end;              // +0x20 (StatusModule+0x30) [inferred: write cursor for circular buffer]
    void*   status_changes;   // +0x28 (StatusModule+0x38) [inferred: backing array pointer, elements are {s32 kind, bool clear_cmd}]
};

// Circular buffer for previous status kind history
// [derived: prev_status_kind_impl (.dynsym) dispatches to vtable+0x148 (PrevStatusKind),
//  which indexes into this buffer via the pointer at StatusModule+0x80]
struct PreviousStatusKinds {
    u8      pad_0x00[0x08];
    u64     capacity;         // +0x08 [inferred: circular buffer max size, same pattern as StatusChangeQueue]
    u64     length;           // +0x10 [inferred: current element count]
    u64     start;            // +0x18 [inferred: read cursor index]
    u8      pad_0x20[0x08];
    s32*    array;            // +0x28 [inferred: backing s32 array, indexed by PrevStatusKind(depth)]
};

// StatusModule vtable — function pointer table for virtual dispatch
// Offsets are byte offsets into the vtable (divide by 8 for slot index)
// All named entries derived from .dynsym lua_bind dispatchers:
//   StatusModule__METHOD_impl (.dynsym) → accessor+0x40 → vtable+OFFSET → concrete impl
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
// [derived: all lua_bind::StatusModule__*_impl (.dynsym) load module from accessor+0x40]
// All vtable method names derived from .dynsym lua_bind::StatusModule__*_impl dispatcher analysis.
struct StatusModule {
    StatusModuleVtbl*       vtbl;                           // +0x00 [derived: standard vtable pointer]
    void*                   owner;                          // +0x08 [inferred: BattleObject* owner, all modules store owner at +0x08]
    StatusChangeQueue       status_change_queue;            // +0x10 [derived: change_status_request_impl (.dynsym) → vtable+0x48 enqueues here] — embedded, 0x30 bytes
    u8                      _pad_0x40[0x40];                // +0x40 — unknown gap
    PreviousStatusKinds*    previous_status_kinds;          // +0x80 [derived: prev_status_kind_impl (.dynsym) → vtable+0x148 dereferences this pointer]
    u8                      _pad_0x88[0x10];                // +0x88 — unknown
    s32                     status_kind;                    // +0x98 [derived: status_kind_impl (.dynsym) → vtable+0x110 (StatusKind) reads this as s32]
    s32                     status_kind_next;               // +0x9C [derived: status_kind_next_impl (.dynsym) → vtable+0x118 (StatusKindNext) reads this as s32]
    s32                     status_kind_interrupt;          // +0xA0 [derived: status_kind_interrupt_impl (.dynsym) → vtable+0x128 reads; set_status_kind_interrupt_impl → vtable+0x120 writes]
    s32                     status_request_from_script;     // +0xA4 [derived: status_kind_que_from_script_impl (.dynsym) → vtable+0x60 reads; delete_status_request_from_script_impl → vtable+0x58 clears]
    void*                   agent_status_data;              // +0xA8 [derived: vtable+0x190 (SetAgentStatusData) writes pointer here]
    u64                     _unknown_0xB0;                  // +0xB0
    s32                     kinetic_type;                   // +0xB8 [derived: vtable+0x1A0 (SetKineticType) writes s32 here]
    s32                     succeeds_bits;                  // +0xBC [derived: set_succeeds_bit_impl (.dynsym) → vtable+0x1A8 (SetSucceedsBit) ORs bits here]
    u32                     permanent_succeeds_bits;        // +0xC0 [inferred: sibling to succeeds_bits, not cleared on status change — written by init_settings_impl → vtable+0x1C8]
    u8                      _pad_0xC4[0x18];                // +0xC4 — unknown gap
    s32                     situation_kind;                  // +0xDC [derived: situation_kind_impl (.dynsym) → vtable+0x168 (SituationKind) reads this as s32]
    s32                     prev_situation_kind;             // +0xE0 [derived: prev_situation_kind_impl (.dynsym) → vtable+0x170 (PrevSituationKind) reads this as s32]
    u8                      _pad_0xE4[0x04];                // +0xE4 — padding
    void*                   current_status_script;          // +0xE8 [inferred: pointer loaded during Lua status script execution, StatusScript**]
    bool                    flag_when_running_lua_main;     // +0xF0 [inferred: set/cleared around Lua main status callback execution]
    bool                    flag_when_lua_ending;           // +0xF1 [inferred: set when Lua status ending callback runs]
    bool                    disable_lua_status;             // +0xF2 [inferred: toggled by vtable+0x70 (EnableLuaStatus), skips Lua status scripts when true]
    u8                      _pad_0xF3;                      // +0xF3
    bool                    is_changing;                    // +0xF4 [derived: is_changing_impl (.dynsym) → vtable+0x140 (IsChanging) reads this as bool]
    bool                    disable_status;                 // +0xF5 [inferred: checked during ChangeStatus to skip status transitions]
    bool                    clear_command_from_script;      // +0xF6 [inferred: set by ChangeStatusRequestFromScript when clear_cmd=true]
    bool                    keep_situation_kind;            // +0xF7 [inferred: prevents situation_kind update on ground/air transition, sibling to keep_situation_air]
    bool                    keep_situation_air;             // +0xF8 [derived: set_keep_situation_air_impl (.dynsym) → vtable+0x188 (SetKeepSituationAir) writes this bool]
    bool                    flag_when_cpp_ending;           // +0xF9 [inferred: set when C++ status ending callback runs, mirrors flag_when_lua_ending for native path]
    u8                      _pad_0xFA[0x06];                // +0xFA — padding to 0x100
};

} // namespace app
