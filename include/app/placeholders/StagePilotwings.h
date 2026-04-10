#pragma once
#include "app/placeholders/StageBase.h"

// StagePilotwings — extends StageBase directly
// Vtable: PTR_LAB_710513be98
// Destructor: FUN_7102de49b0
// [derived: dtor at 0x7102de49b0, embedded sub + shared_ptr container + 2 vec frees + element vector]

struct StagePilotwings : StageBase {
    u8 unk_0x728[0x10];         // +0x728
    void* vec_begin_0x738;      // +0x738 [derived: vector begin, elements 0x60 bytes with vtable dtor]
    void* vec_end_0x740;        // +0x740 [derived: vector end]
    u8 unk_0x748[0x8];          // +0x748
    void* alloc_0x750;          // +0x750 [derived: vector-style begin, freed in ~StagePilotwings]
    void* end_0x758;            // +0x758 [derived: vector-style end]
    u8 unk_0x760[0x8];          // +0x760
    void* alloc_0x768;          // +0x768 [derived: vector-style begin, freed in ~StagePilotwings]
    void* end_0x770;            // +0x770 [derived: vector-style end]
    u8 unk_0x778[0x18];         // +0x778
    void* shared_container_0x790; // +0x790 [derived: shared_ptr container, has 2 shared_ptrs inside]
    u8 unk_0x798[0x10];         // +0x798
    u64 embedded_sub_0x7A8;     // +0x7A8 [derived: embedded sub-object, cleanup via FUN_7102de8120]
};
static_assert(sizeof(StagePilotwings) == 0x7B0, "StagePilotwings size mismatch");
