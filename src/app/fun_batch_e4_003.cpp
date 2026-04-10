// Pool-e batch e4_003: more HARD tier destructors + bitfield cleanup
// Addresses verified in Ghidra MCP against SSBU 13.0.4

#include "types.h"

extern "C" void jeFree_710392e590(void*);  // je_free

// ---- Data symbols ----------------------------------------------------------

// Vtable for class destroyed by FUN_7101b4d700
// [derived: adrp+add computes 0x71050a9eb8 in destructor]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_71050a9eb8;

// Sub-object vtable reset pointer (same as batch_e4_002)
// [derived: adrp+add computes 0x710523c9e8 in FUN_7101b4d700]
__attribute__((visibility("hidden"))) extern void* PTR_LAB_710523c9e8;

// ---- Functions -------------------------------------------------------------

// 0x7101b4d700 (96 bytes) — destructor: set class vtable + reset 2 sub-object vtables
// param_1 [inferred: object with class vtable at +0, 2 sub-objects with vtable+ptr pairs]
//   +0x00 [inferred: class vtable → PTR_FUN_71050a9eb8]
//   +0x08/+0x10 [inferred: sub-object 1 — vtable at +0x08, owned-ptr at +0x10]
//   +0x18/+0x20 [inferred: sub-object 2 — vtable at +0x18, owned-ptr at +0x20]
void FUN_7101b4d700(void* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    void* class_vt = &PTR_FUN_71050a9eb8;
    void* sub_vt = &PTR_LAB_710523c9e8;

    *p = reinterpret_cast<u64>(class_vt);

    // Sub-object 2 (+0x18/+0x20)
    p[3] = reinterpret_cast<u64>(sub_vt);
    void* ptr1 = reinterpret_cast<void*>(p[4]);
    p[4] = 0;
    if (ptr1 != nullptr) jeFree_710392e590(ptr1);

    // Sub-object 1 (+0x08/+0x10)
    void* ptr0 = reinterpret_cast<void*>(p[2]);
    p[1] = reinterpret_cast<u64>(sub_vt);
    p[2] = 0;
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);
}

// 0x7103576360 (96 bytes) — destructor: conditional frees based on flag bits
// param_1 [inferred: struct with flags(u16) at +0x02, ptrs at +0x60/+0x68/+0x70]
//   +0x02 [inferred: u16 flags; bits 1-3 control +0x68 free]
//   +0x60 [inferred: owned-ptr, freed unconditionally if non-null]
//   +0x68 [inferred: owned-ptr, freed only if any of bits 1,2,3 in flags are set]
//   +0x70 [inferred: owned-ptr, zeroed and freed if non-null]
void FUN_7103576360(void* param_1)
{
    void* ptr0 = *(void**)((u8*)param_1 + 0x60);
    if (ptr0 != nullptr) jeFree_710392e590(ptr0);

    u16 flags = *(u16*)((u8*)param_1 + 0x02);
    if (((flags >> 1) & 1) || ((flags >> 2) & 1) || ((flags >> 3) & 1)) {
        void* ptr1 = *(void**)((u8*)param_1 + 0x68);
        if (ptr1 != nullptr) jeFree_710392e590(ptr1);
    }

    void* ptr2 = *(void**)((u8*)param_1 + 0x70);
    *(void**)((u8*)param_1 + 0x70) = nullptr;
    if (ptr2 != nullptr) jeFree_710392e590(ptr2);
}
