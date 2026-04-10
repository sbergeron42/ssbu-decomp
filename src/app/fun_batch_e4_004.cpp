// Pool-e batch e4_004: recursive min + VirtualFreeHook destructors
// Addresses verified in Ghidra MCP against SSBU 13.0.4

#include "types.h"

extern "C" {
void jeFree_710392e590(void*);   // je_free
void FUN_71038f1750(void*);   // sub-object cleanup
void FUN_71039c1400(void*);   // nu::VirtualFreeHook dispatch
}

// ---- Data symbols ----------------------------------------------------------

// Vtable pointer for VirtualFreeHook destructor class
// [derived: adrp+add computes 0x7105238ae0 in FUN_71036a1470]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_7105238ae0;

// VirtualFreeHook function pointer (null = no hook installed)
// [derived: adrp+ldr at 0x71036a149c loads from 0x71052a7a70, checked for null]
__attribute__((visibility("hidden"))) extern void* PTR_VirtualFreeHook_71052a7a70;

// ---- Functions -------------------------------------------------------------

// FUN_7103542ad0 — moved to src/resource/res_load_helpers.cpp (typed version with LoadedDirectory struct)

// 0x71036a1470 (96 bytes) — destructor: set vtable, cleanup sub-object, VirtualFreeHook + free ptr
// param_1 [inferred: object with vtable at +0, sub-object at +0x28, owned-ptr at +0x10]
//   +0x00 [inferred: vtable ptr → PTR_FUN_7105238ae0]
//   +0x10 [inferred: owned-ptr, freed with optional VirtualFreeHook]
//   +0x18 [inferred: copy of +0x10 before free — move semantics]
//   +0x28 [inferred: sub-object passed to FUN_71038f1750 for cleanup]
void FUN_71036a1470(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_7105238ae0);
    FUN_71038f1750(reinterpret_cast<void*>(reinterpret_cast<u8*>(param_1) + 0x28));
    void* ptr = reinterpret_cast<void*>(param_1[2]);
    if (ptr != nullptr) {
        param_1[3] = reinterpret_cast<u64>(ptr);
        if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            FUN_71039c1400(ptr);
        }
        jeFree_710392e590(ptr);
    }
}

// 0x71036a14d0 (96 bytes) — destructor: same as FUN_71036a1470 but also frees self
void FUN_71036a14d0(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_7105238ae0);
    FUN_71038f1750(reinterpret_cast<void*>(reinterpret_cast<u8*>(param_1) + 0x28));
    void* ptr = reinterpret_cast<void*>(param_1[2]);
    if (ptr != nullptr) {
        param_1[3] = reinterpret_cast<u64>(ptr);
        if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            FUN_71039c1400(ptr);
        }
        jeFree_710392e590(ptr);
    }
    jeFree_710392e590(param_1);
}
