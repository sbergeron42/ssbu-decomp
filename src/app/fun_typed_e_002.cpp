#include "types.h"

// pool-e: HARD tier — recursive tree node deletion functions
// Pattern: check null, recurse left/right, [optional cleanup], tail-call delete

extern "C" void FUN_710392e590(void*);  // operator delete

// Cleanup helpers for pattern-B variants
extern "C" void FUN_71015336e0(void*);
extern "C" void FUN_7101cb54a0(void*);
extern "C" void FUN_710353eb70(void*);
extern "C" void FUN_7101cb5600(void*);

// ---------------------------------------------------------------------------
// Pattern A: recurse left/right, delete node
// ---------------------------------------------------------------------------

// 0x71014106f0  64B
void FUN_71014106f0_14106f0(void** node) {
    if (!node) return;
    FUN_71014106f0_14106f0(reinterpret_cast<void**>(node[0]));
    FUN_71014106f0_14106f0(reinterpret_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x710175cd20  64B
void FUN_710175cd20_175cd20(void** node) {
    if (!node) return;
    FUN_710175cd20_175cd20(reinterpret_cast<void**>(node[0]));
    FUN_710175cd20_175cd20(reinterpret_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x71017626c0  64B
void FUN_71017626c0_17626c0(void** node) {
    if (!node) return;
    FUN_71017626c0_17626c0(reinterpret_cast<void**>(node[0]));
    FUN_71017626c0_17626c0(reinterpret_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// 0x7101cbb310  64B
void FUN_7101cbb310_1cbb310(void** node) {
    if (!node) return;
    FUN_7101cbb310_1cbb310(reinterpret_cast<void**>(node[0]));
    FUN_7101cbb310_1cbb310(reinterpret_cast<void**>(node[1]));
    FUN_710392e590(node);
}

// ---------------------------------------------------------------------------
// Pattern B: recurse left/right, cleanup(node+offset), delete node
// ---------------------------------------------------------------------------

// 0x71015336a0  96B  cleanup at node+0x28
void FUN_71015336a0_15336a0(void** node) {
    if (!node) return;
    FUN_71015336a0_15336a0(reinterpret_cast<void**>(node[0]));
    FUN_71015336a0_15336a0(reinterpret_cast<void**>(node[1]));
    FUN_71015336e0(reinterpret_cast<u8*>(node) + 0x28);
    FUN_710392e590(node);
}

// 0x7101cbb290  96B  cleanup at node+0x28
void FUN_7101cbb290_1cbb290(void** node) {
    if (!node) return;
    FUN_7101cbb290_1cbb290(reinterpret_cast<void**>(node[0]));
    FUN_7101cbb290_1cbb290(reinterpret_cast<void**>(node[1]));
    FUN_7101cb54a0(reinterpret_cast<u8*>(node) + 0x28);
    FUN_710392e590(node);
}

// 0x71017e2ab0  96B  cleanup at node+0x2c
void FUN_71017e2ab0_17e2ab0(void** node) {
    if (!node) return;
    FUN_71017e2ab0_17e2ab0(reinterpret_cast<void**>(node[0]));
    FUN_71017e2ab0_17e2ab0(reinterpret_cast<void**>(node[1]));
    FUN_710353eb70(reinterpret_cast<u8*>(node) + 0x2c);
    FUN_710392e590(node);
}

// ---------------------------------------------------------------------------
// Pattern C: recurse left/right, cleanup(node->field), delete node
// ---------------------------------------------------------------------------

// 0x7101cbb2d0  64B  cleanup with node[6] (offset 0x30)
void FUN_7101cbb2d0_1cbb2d0(void** node) {
    if (!node) return;
    FUN_7101cbb2d0_1cbb2d0(reinterpret_cast<void**>(node[0]));
    FUN_7101cbb2d0_1cbb2d0(reinterpret_cast<void**>(node[1]));
    FUN_7101cb5600(node[6]);
    FUN_710392e590(node);
}
