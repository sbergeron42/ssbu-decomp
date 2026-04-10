#pragma once
#include "app/placeholders/StageBase.h"

// StageFlatZoneX — extends StageBase directly
// Vtable: PTR_LAB_71050f2f78
// Destructor: FUN_71029240a0
// [derived: dtor at 0x71029240a0, releases unique_ptr + vector + allocation pair]

struct StageFlatZoneX : StageBase {
    u8 unk_0x728[0x108];        // +0x728
    void* alloc_0x830;          // +0x830 [derived: allocation begin, freed in ~StageFlatZoneX]
    void* end_0x838;            // +0x838 [derived: set to alloc_0x830 before free]
    u8 unk_0x840[0x10];         // +0x840
    void* vec_begin_0x850;      // +0x850 [derived: vector begin, elements 0x18 bytes each]
    void* vec_end_0x858;        // +0x858 [derived: vector end]
    u8 unk_0x860[0x418];        // +0x860
    void* unique_ptr_0xC78;     // +0xC78 [derived: unique_ptr, vt[1] dtor call]
};
static_assert(sizeof(StageFlatZoneX) == 0xC80, "StageFlatZoneX size mismatch");
