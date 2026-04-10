#pragma once
#include "types.h"

// StageBase -- base class for all stage types in SSBU
// Constructor: FUN_71025d2dc0 (14,820 bytes)
// Destructor:  StageBase_dtor_71025d7310 (1,560 bytes)
// Vtable:      PTR_LAB_71050c44c8
// Size:        0x728 bytes (last field at +0x720)
//
// Inheritance hierarchy (known):
//   StageBase (0x728 bytes)
//     +-- StageBattleBase (vtable PTR_LAB_71050c4d70, adds +0x740/+0x750/+0x768)
//     |     +-- StageEnd (vtable PTR_LAB_71050e7a18, adds +0x778/+0x908-0x918)
//     +-- StageNintendogs (vtable PTR_LAB_710512e5e0, adds +0x738 sub-object)
//     +-- StageFlatZoneX (vtable PTR_LAB_71050f2f78, adds +0x830/+0x850/+0xC78)
//     +-- StageStreetPass (vtable PTR_LAB_71051520f8, adds +0x898/+0x908/+0x950)
//     +-- StageWufuIsland (vtable PTR_LAB_710515f3b0, adds +0x734..+0xF5C)
//     +-- StageDuckHunt (vtable PTR_LAB_71050e6d60, adds +0x740..+0x870)
//     +-- StageLuigiMansion (vtable PTR_LAB_710510dcf0, adds +0x7C0..+0x858)
//     +-- StagePictochat2 (vtable PTR_LAB_7105135670, adds +0x740..+0xC70)
//     +-- StageWreckingCrew (vtable PTR_LAB_710515d6e0, adds +0x738..+0xAF0)
//     +-- StagePilotwings (vtable PTR_LAB_710513be98, adds +0x738..+0x7A8)
//
// [derived: field map from constructor FUN_71025d2dc0, destructor StageBase_dtor_71025d7310,
//  and virtual functions FUN_71025d7970/FUN_71025d8750]

struct StageBase {
    void** vtable;                  // +0x000 [derived: set in ctor/dtor]
    u8 unk_0x008[0xC8];            // +0x008 unknown (includes init params at +0xB8..+0xC9)

    void* stage_ref;               // +0x0D0 [derived: set to self in ctor, passed to StageManager::unregister in dtor]
    u32 flags;                     // +0x0D8 [derived: bitmask field, bit 4 checked/bit 2 set in FUN_71025d7970]
    u32 unk_flag_0xDC;             // +0x0DC [derived: set from bool in ctor]

    u8 unk_0x0E0[0xA0];           // +0x0E0 hash groups + params (3 groups of hash40 values at +0xF8/+0x128/+0x158)

    u64 buffer_begin;              // +0x180 [derived: freed in dtor]
    u64 buffer_end;                // +0x188 [derived: freed in dtor]
    u8  unk_0x190[8];              // +0x190
    u64 shared_ref_next;           // +0x198 [derived: set to alloc+3 in ctor]
    void* shared_ref;              // +0x1A0 [derived: shared_ptr, atomic release in dtor]
    void* vec_ptrs_begin;          // +0x1A8 [derived: vector of ptrs, dtor iterates + frees]
    void* vec_ptrs_end;            // +0x1B0 [derived: vector end]
    u64 vec_ptrs_cap;              // +0x1B8 [derived: init 0]
    void* vec_shared_begin;        // +0x1C0 [derived: vector of shared_ptrs, dtor does atomic release]
    void* vec_shared_end;          // +0x1C8 [derived: vector end]
    u64 vec_shared_cap;            // +0x1D0 [derived: init 0]
    u8  flag_0x1D8;                // +0x1D8 [derived: u8 flag, cleared in dtor]
    u8  unk_0x1D9[0x93];           // +0x1D9 (gap to +0x26C)
    u8  flag_0x26C;                // +0x26C [derived: u8 flag, cleared in dtor]
    u8  unk_0x26D[0x93];           // +0x26D (gap to +0x300)

    // --- Owned module/subsystem pointers ---
    void* subsys_0x300;            // +0x300 [derived: unique_ptr, dtor calls vt[1]]
    void* subsys_0x308;            // +0x308 [derived: unique_ptr; FUN_71025d7970 dispatches vt[5]]
    void* subsys_0x310;            // +0x310 [derived: unique_ptr; FUN_71025d7970 dispatches vt[3]]
    void* subsys_0x318;            // +0x318 [derived: unique_ptr, dtor calls vt[1]]
    void* container_0x320;         // +0x320 [derived: linked list container, dtor walks + frees nodes]
    void* owned_0x328;             // +0x328 [derived: owned ptr, simple free in dtor]
    void* owned_0x330;             // +0x330 [derived: owned ptr, cleanup via FUN_7102630e50 in dtor]
    void* stage_render;            // +0x338 [derived: complex owned object; FUN_71025d7970 dereferences twice]
    void* owned_0x340;             // +0x340 [derived: owned ptr, simple free in dtor]
    void* allocated_0x348;         // +0x348 [derived: allocated in ctor, freed in dtor]
    void* vec_container;           // +0x350 [derived: ptr to vector container; FUN_71025d7970/FUN_71025d8750 iterate it]
    void* owned_0x358;             // +0x358 [derived: owned object with +0x50 flag in dtor]

    u8 unk_0x360[0x70];            // +0x360 (event hash pairs, embedded sub-struct)

    // --- Embedded event listener (StageEventListener) ---
    void** event_listener_vt;      // +0x3D0 [derived: set to PTR_FUN_71050c5ac0 in ctor; FUN_7102619730 called on this in dtor]
    void* event_listener_owner;    // +0x3D8 [derived: set to self in ctor]

    u8 unk_0x3E0[0x100];           // +0x3E0 (listener data + second embedded sub-struct at +0x4A0)

    u32 stage_object_id;           // +0x4E0 [derived: checked/cleared in FUN_71025d7970, used as scene handle]
    u8  unk_0x4E4[0x104];          // +0x4E4

    u8  stage_active_flag;         // +0x5E8 [derived: cleared in FUN_71025d7970]
    u8  unk_0x5E9[0x17];           // +0x5E9

    // --- Stage parameter block (u32 float values) ---
    // [derived: regular pattern of u32 writes in ctor, likely float params for stage geometry]
    u32 stage_params[0x2C];        // +0x600 (0x2C u32s = 0xB0 bytes, ends at 0x6B0)

    u8  unk_0x6B0[0x8];            // +0x6B0
    void** sub_listener_vt;        // +0x6B8 [derived: set to PTR_LAB_71050c5aa0 in ctor]
    void* sub_listener_target;     // +0x6C0 [derived: set to &event_listener_vt (+0x3D0)]

    u8  unk_0x6C8[0x2C];           // +0x6C8
    u32 init_color_param;          // +0x6F4 [derived: init 0x876500 in ctor]
    u64 unk_0x6F8;                 // +0x6F8
    u32 unk_0x700;                 // +0x700
    u32 invalid_marker;            // +0x704 [derived: init 0xFFFFFFFF, sentinel value]
    u64 unk_0x708;                 // +0x708
    u64 unk_0x710;                 // +0x710
    void* allocated_0x718;         // +0x718 [derived: allocated in ctor]
    u64 unk_0x720;                 // +0x720 [derived: init 0]
};

static_assert(sizeof(StageBase) == 0x728, "StageBase size mismatch");
