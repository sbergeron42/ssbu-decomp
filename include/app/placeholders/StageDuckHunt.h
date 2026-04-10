#pragma once
#include "app/placeholders/StageBase.h"

// Inner types used by StageDuckHunt destructor

// DuckHuntOwnedObj — sub-object at StageDuckHunt +0x850
// [derived: dtor zeros +0x20/+0x28 before free]
struct DuckHuntOwnedObj {
    u8 unk_0x00[0x20];          // +0x00
    u64 field_0x20;             // +0x20 [derived: zeroed in dtor]
    u64 field_0x28;             // +0x28 [derived: zeroed in dtor]
};

// DuckHuntSubObj — complex sub-object at StageDuckHunt +0x858
// [derived: dtor frees inner allocs at +0x40, +0x58, +0x70]
struct DuckHuntSubObj {
    u8 unk_0x00[0x40];          // +0x00
    void* inner_alloc_0x40;     // +0x40 [derived: freed in dtor]
    u8 unk_0x48[0x10];          // +0x48
    void* inner_alloc_0x58;     // +0x58 [derived: freed in dtor]
    u8 unk_0x60[0x10];          // +0x60
    void* inner_alloc_0x70;     // +0x70 [derived: freed in dtor]
};

// StageDuckHunt — extends StageBase directly
// Vtable: PTR_LAB_71050e6d60
// Destructor: FUN_7102826d30
// [derived: dtor at 0x7102826d30, frees 4 vector pairs + sub-objects + 3 owned ptrs]

struct StageDuckHunt : StageBase {
    u8 unk_0x728[0x18];                // +0x728
    void* vec0_begin;                   // +0x740 [derived: vector-style begin]
    void* vec0_end;                     // +0x748 [derived: vector-style end]
    u8 unk_0x750[0x38];                // +0x750
    void* vec1_begin;                   // +0x788 [derived: vector-style begin]
    void* vec1_end;                     // +0x790 [derived: vector-style end]
    u8 unk_0x798[0x78];                // +0x798
    void* vec2_begin;                   // +0x810 [derived: vector-style begin]
    void* vec2_end;                     // +0x818 [derived: vector-style end]
    u8 unk_0x820[0x8];                 // +0x820
    void* vec3_begin;                   // +0x828 [derived: vector-style begin]
    void* vec3_end;                     // +0x830 [derived: vector-style end]
    u8 unk_0x838[0x18];                // +0x838
    DuckHuntOwnedObj* owned_obj_0x850;  // +0x850 [derived: owned, inner +0x20/+0x28 cleared]
    DuckHuntSubObj* complex_sub_0x858;  // +0x858 [derived: complex sub, inner allocs at +0x40/+0x58/+0x70]
    void* owned_0x860;                  // +0x860 [derived: simple free]
    void* owned_0x868;                  // +0x868 [derived: simple free]
    void* owned_0x870;                  // +0x870 [derived: simple free]
};
static_assert(sizeof(StageDuckHunt) == 0x878, "StageDuckHunt size mismatch");
