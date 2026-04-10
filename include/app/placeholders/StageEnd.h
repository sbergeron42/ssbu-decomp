#pragma once
#include "app/placeholders/StageBase.h"

// StageBattleBase — intermediate class between StageBase and battle-related stages
// Vtable: PTR_LAB_71050c4d70
// Destructor: FUN_71025e55a0
// [derived: ctor/dtor patterns, field map from dtor FUN_71025e55a0]

struct StageBattleBase : StageBase {
    u8 unk_0x728[0x18];         // +0x728
    void* shared_ref_0x740;     // +0x740 [derived: shared_ptr with embedded ref, freed in ~StageBattleBase]
    u8 unk_0x748[0x8];          // +0x748
    void* vec_0x750;            // +0x750 [derived: vector-style free in ~StageBattleBase]
    u8 unk_0x758[0x10];         // +0x758
    void* owned_0x768;          // +0x768 [derived: unique_ptr, cleanup via FUN_71025f5c90]
};
static_assert(sizeof(StageBattleBase) == 0x770, "StageBattleBase size mismatch");

// StageEnd — extends StageBattleBase
// Vtable: PTR_LAB_71050e7a18
// Destructor: FUN_71028350b0
// [derived: dtor at 0x71028350b0, releases 3 owned ptrs + embedded sub cleanup]

struct StageEnd : StageBattleBase {
    u8 unk_0x770[0x8];              // +0x770
    u64 embedded_sub_0x778[50];     // +0x778 [derived: embedded sub-object, 0x190 bytes, cleanup via FUN_7102834b90]
    void* owned_0x908;              // +0x908 [derived: owned object, cleanup via FUN_7102837e00 + free]
    void* owned_0x910;              // +0x910 [derived: owned ptr, simple free]
    void* owned_0x918;              // +0x918 [derived: owned ptr, simple free]
};
static_assert(sizeof(StageEnd) == 0x920, "StageEnd size mismatch");
