#pragma once
#include "types.h"

// Placeholder type for the stage subclass with vtable DAT_71051624a8.
// Unknown stage class — the vtable address is close to StageWufuIsland's
// sub-object vtables (0x710515f3b0 StageWufuIsland, 0x71051618a0/0x7105161860
// WufuIsland embedded sub-objects), so this is likely a peer or nested
// class in the WufuIsland family.
//
// Field map is from the D0/D1 destructor pair:
//   0x7103036720 — D1 destructor (fun_hard_c_010.cpp)
//   0x7103036770 — D0 destructor (StageCollections.cpp)
// Both clear a single owned sub-object at +0x738 and chain to ~StageBase.
//
// [derived: disasm at 0x7103036770 — ldr x20,[x0, #0x738]; str xzr,[x0, #0x738]]
struct StageVt71051624a8 {
    void* vtable;           // +0x000 [derived: set to DAT_71051624a8 in dtor]
    u8 unk_0x008[0x730];    // +0x008..+0x737 (likely StageBase inherited fields)
    void* owned_sub_0x738;  // +0x738 [derived: unique_ptr; cleaned via stage_vt71051624a8_cleanup_710303be40 + jeFree]
};
