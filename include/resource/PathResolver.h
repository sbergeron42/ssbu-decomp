#pragma once
#include "types.h"
#include "resource/FixedString.h"

// PathResolverBase — singleton path resolution object (0x8148 bytes total)
// [inferred: Ghidra 13.0.4 decompilation of FUN_71037c5ff0 (constructor, 2,288 bytes)]
// [inferred: allocated at je_aligned_alloc(0x10, 0x8148) in FUN_71037c3db0]
// [inferred: vtable at PTR_LAB_7105240d28 (base), PTR_LAB_7105240cb8 (derived)]
// [derived: 64 FixedString<512> slots for path components, used by singleton resolve method]

namespace resource {

struct PathResolverBase {
    void* vtable;                     // +0x0000
    FixedString<512> paths[64];       // +0x0008 (64 * 0x204 = 0x8100 bytes, ends at +0x8108)
    u32 path_count;                   // +0x8108 [inferred: u32, zeroed in constructor]
    u32 pad0;                         // +0x810C
    u16 state;                        // +0x8110 [inferred: initialized to 1]
    u8 flag;                          // +0x8112 [inferred: initialized to 0]
    u8 pad1[5];                       // +0x8113
    u64 field_8118;                   // +0x8118 [inferred: zeroed in constructor]
    u64 field_8120;                   // +0x8120 [inferred: zeroed in constructor]
    u64 field_8128;                   // +0x8128 [inferred: zeroed in constructor]
    u64 field_8130;                   // +0x8130 [inferred: zeroed by derived class]
    u64 field_8138;                   // +0x8138 [inferred: zeroed by derived class]
    u64 field_8140;                   // +0x8140 [inferred: zeroed by derived class]
};
// static_assert(sizeof(PathResolverBase) == 0x8148); // can't verify without full alignment

} // namespace resource
