// res_pipeline_large.cpp — Large pipeline functions for resource service
// Pool-c assignment: functions in the resource loading/scheduling pipeline

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// External functions
// [derived: FUN_710354c720 — enqueue priority-based work item]
extern "C" void FUN_710354c720(u32 dispatch_id, void* count_ptr);

// Memory allocation
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free

// Globals
// [derived: DAT_7105332f58 — global array of pointers to dispatch info structs]
// [derived: accessed as DAT_7105332f58[slot.table_index], then +0x10 read as u32]
__attribute__((visibility("hidden"))) extern u64 DAT_7105332f58[];

// [derived: PTR_LAB_710522ec00 — vtable for PrioritySlot]
// [derived: stored at slot+0x00 during reset, address 0x710522ec00 in binary]
__attribute__((visibility("hidden"))) extern char PTR_LAB_710522ec00[];


// ============================================================================
// PrioritySlot — 0x78-byte per-priority work queue slot
// [derived: FUN_7103548310 iterates 32 of these at stride 0x78]
// [derived: field offsets from 13.0.4 disassembly of FUN_7103548310]
// ============================================================================
struct PrioritySlot {
    void* vtable;           // +0x00 [derived: set to &PTR_LAB_710522ec00 during reset]
    u8 pad1[0x10];         // +0x08 [unknown]
    s32 count;              // +0x18 [derived: checked > 0, passed to FUN_710354c720]
    u32 table_index;        // +0x1C [derived: indexes DAT_7105332f58 for dispatch lookup]
    u8 pad2[0x30];         // +0x20 [unknown]
    void* list_head;        // +0x50 [derived: linked list of work items, walked during reset]
    u8 lock;                // +0x58 [derived: atomic spinlock, ldaxrb/stxrb pattern]
    u8 pad3[0x1F];         // +0x59 [unknown]
};
static_assert(sizeof(PrioritySlot) == 0x78, "PrioritySlot must be 0x78 bytes");


// ============================================================================
// FUN_7103548310 — reset_all_priority_slots
// Iterates all 32 priority slots in reverse order. For each slot:
// 1. Sets the vtable pointer
// 2. Acquires the atomic spinlock
// 3. Walks the linked list of work items, setting each node's state to 2
// 4. Releases the spinlock
// 5. If the slot has pending work (count > 0), dispatches via FUN_710354c720
// [derived: called during resource service shutdown or priority reconfiguration]
// [derived: 32 slots × 0x78 bytes = 0xF00 bytes total array]
// Address: 0x7103548310 (3,680 bytes)
// ============================================================================
extern "C" void FUN_7103548310(PrioritySlot* slots) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
#pragma clang loop unroll(full)
    for (int i = 31; i >= 0; i--) {
        slots[i].vtable = PTR_LAB_710522ec00;

        // Acquire spinlock (atomic test-and-set)
        // [derived: ldaxrb/stxrb loop at slot+0x58]
        while (__atomic_exchange_n(&slots[i].lock, 1, __ATOMIC_ACQUIRE) & 1) {}

        // Walk linked list, set each node's state byte to 2
        // [derived: node+0x48 = next pointer, node+0x70 = state byte]
        u8* node = (u8*)slots[i].list_head;
        while (node != nullptr) {
            *(node + 0x70) = 2;
            node = *(u8**)(node + 0x48);
        }

        // Release spinlock
        // [derived: stlrb wzr at slot+0x58]
        __atomic_store_n(&slots[i].lock, 0, __ATOMIC_RELEASE);

        // Dispatch pending work if any
        if (slots[i].count > 0) {
            s32* cnt = &slots[i].count;
            u64 entry = DAT_7105332f58[slots[i].table_index];
            FUN_710354c720(*(u32*)(entry + 0x10), cnt);
        }
    }
}


// ============================================================================
// SKIPPED TARGETS — documented for future reference
// ============================================================================

// FUN_710353b490 (1,184B) — is_path_in_cache
// Strips URI scheme from path, searches global BST (DAT_7105331ec8) for the
// stripped path. Uses function-local static initialization (__cxa_guard pattern).
// BLOCKED: static local generates different guard code than NX binary; BST
// traversal uses libc++ __tree internals that don't match upstream Clang 8.
// BST node layout: +0x00=left, +0x08=right, +0x1a=FixedString256, +0x11a=length.

// FUN_710353ff00 (1,360B) — register_filepath_in_cache
// Registers a filepath in FilesystemInfo. The hash map at FilesystemInfo+0x70
// is a std::unordered_map + LRU cache (NOT the simple LoadedDataWrapper in the
// header). Fields: +0x00=enabled, +0x08=total_size, +0x10=mutex(0x20B),
// +0x30=buckets, +0x38=bucket_count, +0x48=size, +0x50=load_factor.
// BLOCKED: requires matching inlined std::unordered_map operations.

// FUN_710353f1b0 (3,344B) — process_pending_unloads
// Complex cleanup function for FilesystemInfo: processes directory unload
// queue (+0x50 CppVector), filepath release queue (+0x28 CppVector), manages
// std::set for deduplication, calls into the same hash map at +0x70.
// BLOCKED: combines std::set, std::unordered_map, and atomic operations.

// FUN_71035472b0 (3,872B) — zstd streaming decompression state machine
// Switch-based state machine (cases 0-14) wrapping zstd v1.3.7 functions.
// Per CLAUDE.md: do not byte-match library code. Uses FUN_710399d650 (decode
// header), FUN_710399d850 (decompress), FUN_710399ee20 (XXH64 update),
// FUN_710399efc0 (XXH64 digest), FUN_710399eb90 (XXH32).
// SKIPPED: library wrapper, document and move on.
