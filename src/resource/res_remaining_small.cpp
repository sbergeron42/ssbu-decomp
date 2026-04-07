// res_remaining_small.cpp — remaining small resource service functions
// Pool-a assignment: resource service small functions + fiber lifecycle
// [derived: Ghidra 13.0.4 decompilation + disassembly]

#include "types.h"
#include "resource/Fiber.h"
#include "resource/ResServiceNX.h"

// nn::os TLS API (PLT stubs)
extern "C" u64 FUN_71039c0510(u32);          // nn::os::GetTlsValue

// Memory management
extern "C" void FUN_710392e590(void*);       // je_free

// VirtualFreeHook (PLT)
extern "C" void FUN_71039c1400(void*);

// Hook pointers
__attribute__((visibility("hidden"))) extern void* PTR_VirtualFreeHook_71052a7a70;

// Globals
__attribute__((visibility("hidden"))) extern u32 DAT_7105331f10;    // nn::os::TlsSlot
__attribute__((visibility("hidden"))) extern resource::FilesystemInfo* DAT_7105331f20;

// bsearch (PLT stub)
extern "C" void* FUN_71039c2080(const void* key, const void* base,
    u64 nmemb, u64 size, int(*compar)(const void*, const void*));

// [derived: comparator function for 8-byte hash entries, at 0x7103541c90]
__attribute__((visibility("hidden"))) extern "C" int FUN_7103541c90(const void*, const void*);

// ============================================================================
// phx::Fiber::get_current_fiber()
// Address: 0x710353c580 (48 bytes)
// STATUS: MATCH (100% non-relocation match, 73% raw — 3 diffs are relocations)
// [derived: Ghidra "phx::Fiber::get_current_fiber", also named "status" in 13.0.1]
// Returns the current fiber from thread-local storage, or nullptr if TLS
// slot is uninitialized.
// ============================================================================
void* get_current_fiber_353c580() {
    if (DAT_7105331f10 != 0xFFFFFFFF) {
        return (void*)FUN_71039c0510(DAT_7105331f10);
    }
    return nullptr;
}

// ============================================================================
// FUN_710353e1e0 — resource filepath-to-directory index resolver
// Address: 0x710353e1e0 (324 bytes)
// STATUS: 34% raw — correct logic, prologue interleaving + missing NX-specific
//   mov w8,w8 zero-extend + phase2 instruction scheduling differences.
// [derived: Ghidra 13.0.4 decompilation + disassembly]
// Resolves a packed filepath hash (param_2) into a directory group index
// stored in *param_1. Two phases:
//   Phase 1: resolve filepath hash to path entry via LoadedFsSearch tables
//   Phase 2: look up the path entry in idx_to_group via bsearch
// Uses 0xFFFFFF as sentinel for invalid/not-found indices.
// [derived: search table accessed via DAT_7105331f20->path_info(+0x78)->search(+0x08)]
// [derived: LoadedFsSearch offsets: +0x08 body, +0x10 fpi, +0x18 pti,
//   +0x20 itg, +0x28 pg, +0x30 ipgi]
// [derived: body sub-fields: +0x00 count0, +0x04 count1, +0x08 count2]
// ============================================================================
void FUN_710353e1e0_353e1e0(u32* param_1, u64 param_2) {
    u64 search = *(u64*)(*(u64*)((u64)DAT_7105331f20 + 0x78) + 8);
    u64 group_idx = param_2 >> 0x28;
    u64 local_key;
    u64 entry;

    if ((u32)group_idx == 0xFFFFFF) {
        // Sentinel path: binary search in file_path_to_idx
        local_key = param_2 & 0xFFFFFFFFFFULL;
        u64 body = *(u64*)(search + 8);
        u64 fpi = *(u64*)(search + 0x10);
        u32 count = *(u32*)body;
        u64* result = (u64*)FUN_71039c2080(&local_key, (void*)fpi, count, 8, FUN_7103541c90);
        if (result == nullptr || (*result >> 0x28) == 0xFFFFFF)
            goto null_result;
        u64 pti = *(u64*)(search + 0x18);
        entry = pti + (*result >> 0x28) * 0x20;
        if (entry != 0) goto extract;
        goto phase2_with_zero;
    }
    {
        // Direct index path
        u64 body = *(u64*)(search + 8);
        u32 count1 = *(u32*)(body + 4);
        if (count1 <= (u32)group_idx)
            goto null_result;
        u64 pg = *(u64*)(search + 0x28);
        if (pg != 0) {
            group_idx = (u64)*(u32*)(pg + group_idx * 4);
            if ((u32)group_idx == 0xFFFFFF)
                goto null_result;
        }
        u32 count2 = *(u32*)(body + 8);
        if (count2 <= (u32)group_idx)
            goto null_result;
        u64 ipgi = *(u64*)(search + 0x30);
        entry = ipgi + (u64)(u32)group_idx * 0x20;
        if (entry != 0) goto extract;
        goto phase2_with_zero;
    }

extract:
    local_key = *(u64*)entry & 0xFFFFFFFFFFULL;
    goto phase2;

null_result:
phase2_with_zero:
    local_key = 0;

phase2:
    {
        // Phase 2: look up resolved path in idx_to_group
        u64 search2 = *(u64*)(*(u64*)((u64)DAT_7105331f20 + 0x78) + 8);
        u64 body2 = *(u64*)(search2 + 8);
        u64 itg = *(u64*)(search2 + 0x20);
        u32 count2b = *(u32*)(body2 + 8);
        u64* result2 = (u64*)FUN_71039c2080(&local_key, (void*)itg, count2b, 8, FUN_7103541c90);
        u32 final_result = 0xFFFFFF;
        if (result2 != nullptr) {
            u32 rgroup = (u32)(*result2 >> 0x28);
            if (rgroup != 0xFFFFFF) {
                u32 rcount1 = *(u32*)(*(u64*)(search2 + 8) + 4);
                if (rcount1 > rgroup) {
                    final_result = rgroup;
                }
            }
        }
        *param_1 = final_result;
    }
}

// ============================================================================
// FUN_710354f900 — recursive tree node destructor
// Address: 0x710354f900 (116 bytes)
// STATUS: MATCH (90% non-reloc — 3 diffs are prologue scheduling, 8 relocs)
// [derived: Ghidra 13.0.4 decompilation + disassembly]
// Recursively destroys a BST node: recurse left, recurse right, free long
// string data if present (SSO bit 0 at +0x20), then free the node itself.
// Used by std::__1::__tree<std::string,...>::destroy.
// [derived: node layout from std::__1::__tree_node<std::string>:
//   +0x00 left, +0x08 right, +0x10 parent, +0x18 is_black,
//   +0x20 string SSO byte, +0x30 heap data ptr when long]
// ============================================================================
void FUN_710354f900_354f900(u64* param_1) {
    if (param_1 == nullptr) return;
    FUN_710354f900_354f900((u64*)param_1[0]);
    FUN_710354f900_354f900((u64*)param_1[1]);
    if (*((u8*)(param_1 + 4)) & 1) {
        void* heap_ptr = (void*)param_1[6];
        if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            FUN_71039c1400(heap_ptr);
        }
        FUN_710392e590(heap_ptr);
    }
    if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        FUN_71039c1400(param_1);
    }
    FUN_710392e590(param_1);
}

// ============================================================================
// Skipped targets — documented for future reference
// ============================================================================
// FUN_710353c130 (164B) — event wrapper allocator. 36% match after 3 attempts.
//   Issues: prologue scheduling, stack slot allocation (sp+0 vs sp+8), no tail
//   call to FUN_71037cc390. All compiler-level divergences.
//
// FUN_710354b370 (312B) — thread pool manager destructor. 19% match.
//   Issues: vtable call at vt[3] uses hidden x8 indirect return pointer that
//   changes stack frame from 0x30 to 0x40 bytes. Without the correct return
//   type, all register saves and sp offsets are wrong. Needs struct definition
//   for the vtable return type.
//
// FUN_710354f380 (240B) — libc++ __hash_table::rehash. Not attempted.
//   Uses std::__1::__next_prime and bucket resizing internals.
//
// FUN_710354fa40 (304B) — libc++ __tree::__find_equal with string comparison.
//   Not attempted. Complex BST traversal with memcmp.
//
// FUN_710354ff10 (368B) — hash table lookup with game-specific matching logic.
//   Not attempted. Complex control flow with nested hash bucket traversal.
