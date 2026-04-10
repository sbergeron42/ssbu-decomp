// Pool-e batch e4_002: more HARD tier functions
// Addresses verified in Ghidra MCP against SSBU 13.0.4

#include "types.h"

// ---- Callee declarations ---------------------------------------------------

extern "C" {
void jeFree_710392e590(void*);   // je_free
void FUN_71038b4b70(void*);   // tree node cleanup helper
void FUN_7101958da0_cleanup(void*); // placeholder
}

// ---- Data symbols ----------------------------------------------------------

// Sub-object vtable reset pointer (used in multiple field-reset destructors)
// [derived: adrp+add computes 0x710523c9a8 in FUN_7101b784a0 and FUN_7101bc8800]
__attribute__((visibility("hidden"))) extern void* PTR_DAT_710523c9a8;

// ---- Functions -------------------------------------------------------------

// 0x71038b4b10 (96 bytes) — recursive tree node cleanup with container_of offset
// Red-black tree traversal: children at +0xa8/+0xb0 point INTO node at +0xa0,
// so we subtract 0xa0 (container_of) to get node base.
// param_1 [inferred: RB-tree node]
//   +0x0a8 [inferred: left child link, points to node+0xa0 or null]
//   +0x0b0 [inferred: right child link, points to node+0xa0 or null]
void FUN_71038b4b10(void* param_1)
{
    if (param_1 == nullptr) return;

    void* left = *(void**)((u8*)param_1 + 0xa8);
    FUN_71038b4b10(left != nullptr ? (void*)((u8*)left - 0xa0) : nullptr);

    void* right = *(void**)((u8*)param_1 + 0xb0);
    FUN_71038b4b10(right != nullptr ? (void*)((u8*)right - 0xa0) : nullptr);

    FUN_71038b4b70(param_1);
    jeFree_710392e590(param_1);
}

// 0x7101bc8800 (80 bytes) — destructor: reset 2 sub-object vtables + conditional free
// param_1 [inferred: object containing 2 sub-objects with vtable+ptr pairs]
//   +0x08/+0x10 [inferred: sub-object 1 — vtable at +0x08, owned-ptr at +0x10]
//   +0x18/+0x20 [inferred: sub-object 2 — vtable at +0x18, owned-ptr at +0x20]
// Each sub-object's vtable is reset to PTR_DAT_710523c9a8, ptr zeroed, old ptr freed
void FUN_7101bc8800(void* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    void* vtbl = &PTR_DAT_710523c9a8;

    // Sub-object 2 (+0x18/+0x20): reset vtable, zero ptr, free old
    p[3] = reinterpret_cast<u64>(vtbl);
    void* ptr1 = reinterpret_cast<void*>(p[4]);
    p[4] = 0;
    if (ptr1 != nullptr) jeFree_710392e590(ptr1);

    // Sub-object 1 (+0x08/+0x10): reset vtable, zero ptr, free old
    void* ptr0 = reinterpret_cast<void*>(p[2]);
    p[1] = reinterpret_cast<u64>(vtbl);
    p[2] = 0;
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);
}

// 0x7101b784a0 (96 bytes) — destructor: reset 3 sub-object vtables + conditional free
// Same pattern as FUN_7101bc8800 but with 3 sub-objects
//   +0x08/+0x10, +0x18/+0x20, +0x28/+0x30
void FUN_7101b784a0(void* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    void* vtbl = &PTR_DAT_710523c9a8;

    // Sub-object 3 (+0x28/+0x30)
    p[5] = reinterpret_cast<u64>(vtbl);
    void* ptr2 = reinterpret_cast<void*>(p[6]);
    p[6] = 0;
    if (ptr2 != nullptr) jeFree_710392e590(ptr2);

    // Sub-object 2 (+0x18/+0x20)
    void* ptr1 = reinterpret_cast<void*>(p[4]);
    p[3] = reinterpret_cast<u64>(vtbl);
    p[4] = 0;
    if (ptr1 != nullptr) jeFree_710392e590(ptr1);

    // Sub-object 1 (+0x08/+0x10)
    void* ptr0 = reinterpret_cast<void*>(p[2]);
    p[1] = reinterpret_cast<u64>(vtbl);
    p[2] = 0;
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);
}

// 0x7101b78e40 (80 bytes) — destructor: same pattern, 2 sub-objects
// Uses PTR_LAB_710523c9e8 instead of PTR_DAT_710523c9a8
// [derived: adrp+add computes 0x710523c9e8 in FUN_7101b78e40]
__attribute__((visibility("hidden"))) extern void* PTR_LAB_710523c9e8;

void FUN_7101b78e40(void* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    void* vtbl = &PTR_LAB_710523c9e8;

    // Sub-object 2 (+0x18/+0x20)
    p[3] = reinterpret_cast<u64>(vtbl);
    void* ptr1 = reinterpret_cast<void*>(p[4]);
    p[4] = 0;
    if (ptr1 != nullptr) jeFree_710392e590(ptr1);

    // Sub-object 1 (+0x08/+0x10)
    void* ptr0 = reinterpret_cast<void*>(p[2]);
    p[1] = reinterpret_cast<u64>(vtbl);
    p[2] = 0;
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);
}

// 0x7101b785d0 (96 bytes) — destructor: 3 sub-objects with PTR_LAB_710523c9e8
void FUN_7101b785d0(void* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    void* vtbl = &PTR_LAB_710523c9e8;

    p[5] = reinterpret_cast<u64>(vtbl);
    void* ptr2 = reinterpret_cast<void*>(p[6]);
    p[6] = 0;
    if (ptr2 != nullptr) jeFree_710392e590(ptr2);

    void* ptr1 = reinterpret_cast<void*>(p[4]);
    p[3] = reinterpret_cast<u64>(vtbl);
    p[4] = 0;
    if (ptr1 != nullptr) jeFree_710392e590(ptr1);

    void* ptr0 = reinterpret_cast<void*>(p[2]);
    p[1] = reinterpret_cast<u64>(vtbl);
    p[2] = 0;
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);
}

// 0x7101b78630 (96 bytes) — destructor: 3 sub-objects with PTR_LAB_710523c9e8 + free self
// Same as FUN_7101b785d0 but also calls je_free(param_1) at the end
void FUN_7101b78630(void* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    void* vtbl = &PTR_LAB_710523c9e8;

    p[5] = reinterpret_cast<u64>(vtbl);
    void* ptr2 = reinterpret_cast<void*>(p[6]);
    p[6] = 0;
    if (ptr2 != nullptr) jeFree_710392e590(ptr2);

    void* ptr1 = reinterpret_cast<void*>(p[4]);
    p[3] = reinterpret_cast<u64>(vtbl);
    p[4] = 0;
    if (ptr1 != nullptr) jeFree_710392e590(ptr1);

    void* ptr0 = reinterpret_cast<void*>(p[2]);
    p[1] = reinterpret_cast<u64>(vtbl);
    p[2] = 0;
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);

    jeFree_710392e590(param_1);
}
