#pragma once
#include "app/placeholders/StageBase.h"

// StageStreetPass — extends StageBase directly
// Vtable: PTR_LAB_71051520f8
// Destructor: FUN_7102f33f20
// [derived: dtor at 0x7102f33f20, releases unique_ptr + vector + 2 allocation pairs]

struct StageStreetPass : StageBase {
    u8 unk_0x728[0x170];        // +0x728
    void* alloc_0x898;          // +0x898 [derived: allocation, freed in ~StageStreetPass]
    void* end_0x8a0;            // +0x8a0 [derived: set to alloc_0x898 before free]
    u8 unk_0x8a8[0x10];         // +0x8a8
    void* alloc_0x8b8;          // +0x8b8 [derived: allocation, freed in ~StageStreetPass]
    void* end_0x8c0;            // +0x8c0 [derived: set to alloc_0x8b8 before free]
    u8 unk_0x8c8[0x40];         // +0x8c8
    void* vec_begin_0x908;      // +0x908 [derived: vector begin, elements 0x18 bytes each]
    void* vec_end_0x910;        // +0x910 [derived: vector end]
    u8 unk_0x918[0x38];         // +0x918
    void* unique_ptr_0x950;     // +0x950 [derived: unique_ptr, vt[1] dtor call]
};
static_assert(sizeof(StageStreetPass) == 0x958, "StageStreetPass size mismatch");
