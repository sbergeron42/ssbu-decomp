#pragma once
#include "app/placeholders/StageBase.h"

// StagePictochat2 — extends StageBase directly
// Vtable: PTR_LAB_7105135670
// Destructor: FUN_7102d5bbf0
// [derived: dtor at 0x7102d5bbf0, container + vector of unique_ptrs + vec free + 3 unique_ptrs + embedded sub]

struct StagePictochat2 : StageBase {
    u8 unk_0x728[0x18];         // +0x728
    u64 embedded_sub_0x740;     // +0x740 [derived: embedded sub-object, cleanup via FUN_7102d5a8f0]
    u8 unk_0x748[0x4C8];        // +0x748
    void* unique_ptr_0xC10;     // +0xC10 [derived: unique_ptr, vt[1] dtor call]
    void* owned_0xC18;          // +0xC18 [derived: owned object, inner alloc at +0x28]
    void* unique_ptr_0xC20;     // +0xC20 [derived: unique_ptr, vt[1] dtor call]
    u8 unk_0xC28[0x8];          // +0xC28
    void* alloc_0xC30;          // +0xC30 [derived: vector-style begin]
    void* end_0xC38;            // +0xC38 [derived: vector-style end]
    u8 unk_0xC40[0x10];         // +0xC40
    void* vec_begin_0xC50;      // +0xC50 [derived: vector of unique_ptrs begin]
    void* vec_end_0xC58;        // +0xC58 [derived: vector end]
    u8 unk_0xC60[0x10];         // +0xC60
    void* container_0xC70;      // +0xC70 [derived: owned container with inner ptr]
};
static_assert(sizeof(StagePictochat2) == 0xC78, "StagePictochat2 size mismatch");
