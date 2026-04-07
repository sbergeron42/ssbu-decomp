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
    u8 pad2[0x28];         // +0x20 [unknown]
    PrioritySlot* next;     // +0x48 [derived: linked list next pointer, FUN_71035481d0]
    PrioritySlot* list_head;// +0x50 [derived: head of child linked list]
    u8 lock;                // +0x58 [derived: atomic spinlock, ldaxrb/stxrb pattern]
    u8 pad3a[0x0F];        // +0x59 [unknown]
    u32 recursive_param;    // +0x68 [derived: set recursively by FUN_71035481d0]
    u8 pad3b[0x04];        // +0x6C [unknown]
    u8 state;               // +0x70 [derived: set to 2 during reset in FUN_7103548310]
    u8 pad3c[0x07];        // +0x71 [unknown]
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
        PrioritySlot* node = slots[i].list_head;
        while (node != nullptr) {
            node->state = 2;
            node = node->next;
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
// FUN_71035481d0 — set_recursive_param
// Recursively sets the u32 field at +0x68 on this node and all children.
// Acquires spinlock at +0x58, walks child list at +0x50 (next at +0x48),
// recurses on each child, then releases the lock.
// [derived: called to propagate a parameter value through a priority tree]
// [derived: same struct layout as PrioritySlot — nodes are recursive]
// Address: 0x71035481d0 (112 bytes)
// ============================================================================
extern "C" void FUN_71035481d0(PrioritySlot* slot, u32 param) {
    u8* lock_ptr = &slot->lock;
    slot->recursive_param = param;

    // Acquire spinlock
    // [derived: ldaxrb/stxrb loop at +0x58]
    while (__atomic_exchange_n(lock_ptr, 1, __ATOMIC_ACQUIRE) & 1) {}

    // Recurse on all children in the linked list
    // [derived: walks list_head at +0x50, next at +0x48]
    PrioritySlot* child = slot->list_head;
    while (child != nullptr) {
        FUN_71035481d0(child, param);
        child = child->next;
    }

    // Release spinlock
    // [derived: stlrb wzr at +0x58]
    __atomic_store_n(lock_ptr, 0, __ATOMIC_RELEASE);
}


// Global ResServiceNX pointer
// [derived: DAT_7105331f28 at 0x7105331f28, referenced from all resource functions]
__attribute__((visibility("hidden"))) extern ResServiceNX* DAT_7105331f28;


// ============================================================================
// FUN_7103541200 — resolve_stream_entry
// Binary searches stream_hash_to_entries for a hash40 key. If found, resolves
// the locale-adjusted stream data (offset + size) and copies the ARC path
// string to the output FixedString256.
// [derived: param_1=output FixedString256, param_2=LoadedArc*, param_3=out_offset,
//           param_4=out_size, param_5=hash40 search key]
// [derived: binary search on HashToIndex array (8-byte entries, lower 40 = hash)]
// [derived: locale_type 1=language (+0xDC), 2=region (+0xD8) from ResServiceNX]
// [derived: copies arc_string FixedString256 from ResServiceNX+0xE8 to output]
// Address: 0x7103541200 (704 bytes)
// ============================================================================
extern "C" void FUN_7103541200(FixedString256* out, LoadedArc* arc,
                                u64* out_offset, u64* out_size, u64 hash40_key) {
    // Binary search stream_hash_to_entries for hash40_key
    // [derived: lower_bound pattern with signed half computation]
    HashToIndex* base = arc->stream_hash_to_entries;
    u32 count_u = arc->stream_header->stream_hash_count;
    HashToIndex* end_ptr = base + count_u;

    if (count_u != 0) {
        s64 n = (s64)(u64)count_u;
        do {
            s64 half = n / 2;
            HashToIndex* mid = base + half;
            u64 mid_hash = mid->raw & 0xFFFFFFFFFFULL;
            s64 remaining = n + ~half;
            if (mid_hash < hash40_key) {
                base = mid + 1;
                n = remaining;
            } else {
                n = half;
            }
        } while (n != 0);
    }

    // Check if key was found
    // [derived: b.ne to found handler placed after ret — cold path layout]
    u64 found_index;
    if (base != end_ptr) {
        u64 found_raw = base->raw;
        u64 found_hash = found_raw & 0xFFFFFFFFFFULL;
        found_index = found_raw >> 40;
        if (found_hash == hash40_key && found_index != 0xffffff)
            goto found;
    }

    // Not found — set outputs to zero, fall through to copy
    *out_offset = 0;
    *out_size = 0;

copy_string:
    // Copy arc_string from ResServiceNX to output
    // [derived: FixedString256 copy with 2-char unrolled loop]
    {
        ResServiceNX* svc = DAT_7105331f28;
        out->data[0] = '\0';
        u16 src_len = svc->arc_string.length;
        out->length = 0;
        if (src_len != 0) {
            const char* src = svc->arc_string.data;
            for (u64 i = 0; i < (u64)src_len; i++) {
                out->data[out->length] = src[i];
                out->length++;
            }
        }
        char* end_ch = out->data + out->length;
        *end_ch = '\0';
    }
    return;

found:
    {
        // Resolve locale-adjusted stream data
        // [derived: StreamEntry at +0xC8, 12-byte stride, locale_type at +0x08]
        u8 locale_type = arc->stream_entries[found_index].locale_type;

        s32 locale_offset;
        if (locale_type == 2) {
            locale_offset = (s32)DAT_7105331f28->region_idx;
            if (locale_offset == -1) locale_offset = 0;
        } else if (locale_type == 1) {
            locale_offset = (s32)DAT_7105331f28->language_idx;
            if (locale_offset == -1) locale_offset = 0;
        } else {
            locale_offset = 0;
        }

        // Compute final data index
        // [derived: stream_entries[idx].file_group_index() + locale_offset]
        u32 file_group_idx = (u32)(arc->stream_entries[found_index].raw >> 40);
        u32 final_idx = (u32)locale_offset + file_group_idx;

        // [derived: stream_file_indices at +0xD0, stream_datas at +0xD8]
        u32 data_idx = arc->stream_file_indices[final_idx];
        StreamData* sd = &arc->stream_datas[data_idx];
        *out_size = sd->size;
        *out_offset = sd->offset;
        goto copy_string;
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
