// res_post_processing.cpp — Post-processing loop functions for resource service
// Pool-d assignment: functions at 0x7103546xxx–0x710354fxxx
// These handle post-load processing, tree cleanup, task dispatch, and pool management.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// PLT stubs for std::__1::recursive_mutex
// [derived: Ghidra shows std::__1::recursive_mutex::lock/unlock at these PLT entries]
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// Allocator and helpers
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void jeFree_710392e590(void*);  // je_free
extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" void* memset(void*, int, unsigned long);

// Global resource service singleton
// [derived: DAT_7105331f20 — global FilesystemInfo* used across all resource helpers]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// OOM handler singleton
// [derived: DAT_7105331f00 at 0x7105331f00, 40+ refs in binary, vtable dispatch at +0x30]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// Forward declarations for functions defined elsewhere
extern "C" void FUN_710353eff0(FilesystemInfo*, LoadedDirectory*);  // release loaded directory
void FUN_7103540560(FilesystemInfo*, u32);  // release_filepath_entry

// Forward declarations for functions in this file
int FUN_71035461f0(long param_1, u32* param_2, u32 param_3, u32 param_4);
int FUN_7103546180(long param_1, u64* param_2, u32 param_3, u32 param_4);
void FUN_71035481d0(long param_1, u32 param_2);
void* FUN_7103546d90(u64* param_1);

// SDK
namespace nn::os {
    void InitializeSemaphore(void* sema, int initial, int max);
}

// Global resource service pointer
// [derived: DAT_7105331f28 at 0x7105331f28 — ResServiceNX*, distinct from filesystem_info global]
__attribute__((visibility("hidden"))) extern long DAT_7105331f28;

// External function references
extern "C" s32 FUN_7103542ad0(LoadedDirectory*);  // get_redirected_dir_loading_state_recursive
extern "C" s32 FUN_7103542f30(u32*);  // get_region_index_from_arc

// Vtable pointer for pool entry type
// [derived: Ghidra shows PTR_FUN_710522eb40 assigned as vtable at entry[0]]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710522eb40;

// Move internal state helper
extern "C" void FUN_7101f6f1f0(void* dst, void* src);

// ============================================================================
// FUN_71035471c0 — tree_release_filepaths_recursive
// Recursively traverses a binary tree (post-order). For each node with a valid
// directory index (+0x1c != 0xffffff), releases the filepath entry via
// FUN_7103540560, then invalidates the index. Frees node memory.
// [derived: node[0]=left, node[1]=right, offset +0x1c = directory index (u32)]
// [derived: same BST traversal pattern as FUN_710353b1c0 but with filepath release]
// Address: 0x71035471c0 (240 bytes)
// ============================================================================
void FUN_71035471c0(u64* param_1) {
    if (param_1 != nullptr) {
        FUN_71035471c0((u64*)param_1[0]);
        FUN_71035471c0((u64*)param_1[1]);
        if (*(u32*)((u8*)param_1 + 0x1c) != 0xffffff) {
            FUN_7103540560(DAT_7105331f20, *(u32*)((u8*)param_1 + 0x1c));
            *(u32*)((u8*)param_1 + 0x1c) = 0xffffff;
        }
        jeFree_710392e590(param_1);
    }
}

// ============================================================================
// FUN_7103547110 — tree_release_directories_recursive
// Recursively traverses a binary tree (post-order). For each node with a valid
// directory index (+0x1c != 0xffffff) and within bounds, locks the filesystem
// mutex, releases the directory if active (flags & 1), then invalidates the index.
// [derived: DAT_7105331f20 = global FilesystemInfo*, +0x48 = loaded_directory_len]
// [derived: +0x40 = loaded_directories, stride 0x48, flags at +0x08]
// [derived: FUN_710353eff0 = release loaded directory entry]
// Address: 0x7103547110 (176 bytes)
// ============================================================================
void FUN_7103547110(u64* param_1) {
    if (param_1 != nullptr) {
        FUN_7103547110((u64*)param_1[0]);
        FUN_7103547110((u64*)param_1[1]);
        FilesystemInfo* fs = DAT_7105331f20;
        u32 dir_index = *(u32*)((u8*)param_1 + 0x1c);
        if (dir_index != 0xffffff) {
            if (dir_index < fs->loaded_directory_len) {
                lock_71039c1490(fs->mutex);
                LoadedDirectory* dir = (LoadedDirectory*)((u8*)fs->loaded_directories + (u64)dir_index * 0x48);
                if (dir->flags & 1) {
                    FUN_710353eff0(fs, dir);
                }
                unlock_71039c14a0(fs->mutex);
            }
            *(u32*)((u8*)param_1 + 0x1c) = 0xffffff;
        }
        jeFree_710392e590(param_1);
    }
}

// FUN_71035481d0 — set_state_recursive
// REMOVED: duplicate definition — canonical version is in res_pipeline_large.cpp
// (with proper PrioritySlot* typing)

// FUN_7103546180 — count_and_queue_directory_loads_recursive
// REMOVED: duplicate definition — canonical version is in res_remaining_large.cpp
// (with proper ResServiceNX*/LoadedDirectory* typing)

// ============================================================================
// FUN_71035467b0 — alloc_pool_entry_and_semaphore
// Allocates a 0x10-byte pool entry (vtable + ptr), sets vtable to
// PTR_FUN_710522eb40, stores at *param_1. If param_3 != 0, also allocates
// a 0x28-byte SemaphoreType, initializes with (param_2, param_3), and
// stores at entry+0x08.
// [derived: je_aligned_alloc(0x10, 0x10) for entry, (0x10, 0x28) for semaphore]
// [derived: PTR_FUN_710522eb40 = vtable for pool entry type]
// [derived: nn::os::InitializeSemaphore(sema, initial=param_2, max=param_3)]
// Address: 0x71035467b0 (848 bytes)
// ============================================================================
void FUN_71035467b0(u64* param_1, int param_2, int param_3) {
    u64* entry = (u64*)je_aligned_alloc(0x10, 0x10);
    if (entry == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = 0x10;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (entry = (u64*)je_aligned_alloc(0x10, 0x10), entry != nullptr))
                goto LAB_alloc_done;
        }
        entry = nullptr;
    }
LAB_alloc_done:
    entry[0] = (u64)&PTR_FUN_710522eb40;
    entry[1] = 0;
    *param_1 = (u64)entry;

    if (param_3 == 0) {
        return;
    }

    void* sema = je_aligned_alloc(0x10, 0x28);
    if (sema == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = 0x28;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (sema = je_aligned_alloc(0x10, 0x28), sema != nullptr))
                goto LAB_sema_done;
        }
        sema = nullptr;
    }
LAB_sema_done:
    nn::os::InitializeSemaphore(sema, param_2, param_3);
    entry[1] = (u64)sema;
}

// FUN_7103546000 — queue_single_file_load
// REMOVED: duplicate definition — canonical version is in res_remaining_large.cpp

// ============================================================================
// FUN_7103546b00 — swap_any_like
// Swaps two std::any-like objects. Each object has 5 qwords; [4] is a self-ptr
// (inline storage) or external ptr (heap storage). Dispatches move/destroy
// via vtable at *ptr: +0x10=clone, +0x18=move, +0x20=destroy, +0x28=dealloc.
// [derived: param_1/param_2 are 40-byte objects with vtable-dispatched storage]
// [derived: self-referencing pointer at offset [4] indicates inline storage]
// Address: 0x7103546b00 (320 bytes)
// ============================================================================
void FUN_7103546b00(long* param_1, long* param_2) {
    if (param_2 == param_1) return;

    long* plVar1 = (long*)param_1[4];
    if (plVar1 == param_1) {
        // param_1 has inline storage
        if ((long*)param_2[4] == param_2) {
            // Both inline: swap via temporary
            long local_40[4];
            (*(void(**)(long*, long*))(*(long*)plVar1 + 0x18))(plVar1, local_40);
            (*(void(**)(void))(*(long*)param_1[4] + 0x20))();
            param_1[4] = 0;
            (*(void(**)(long*, long*))(*(long*)param_2[4] + 0x18))((long*)param_2[4], param_1);
            (*(void(**)(void))(*(long*)param_2[4] + 0x20))();
            param_2[4] = 0;
            param_1[4] = (long)param_1;
            (*(void(**)(long*, long*))(local_40[0] + 0x18))(local_40, param_2);
            (*(void(**)(long*))(local_40[0] + 0x20))(local_40);
        } else {
            // param_1 inline, param_2 heap: move param_1 to param_2
            (*(void(**)(long*, long*))(*(long*)plVar1 + 0x18))(plVar1, param_2);
            (*(void(**)(void))(*(long*)param_1[4] + 0x20))();
            param_1[4] = param_2[4];
        }
        param_2[4] = (long)param_2;
    } else {
        long* plVar2 = (long*)param_2[4];
        if (param_2 == plVar2) {
            // param_1 heap, param_2 inline: move param_2 to param_1
            (*(void(**)(long*, long*))(*(long*)plVar2 + 0x18))(plVar2, param_1);
            (*(void(**)(void))(*(long*)param_2[4] + 0x20))();
            param_2[4] = param_1[4];
            param_1[4] = (long)param_1;
        } else {
            // Both heap: just swap pointers
            param_1[4] = (long)plVar2;
            param_2[4] = (long)plVar1;
        }
    }
}

// ============================================================================
// FUN_7103548240 — process_task_queue
// Calls the flush vtable method on param_1-8, then acquires a spinlock at
// param_1+0x50. Walks the linked list at +0x48, processing each task node:
// - State 0x01: skip (already processing)
// - State 0x02: unlink from list, call destructor vtable
// - Other: enqueue for re-processing via FUN_7103549170
// Releases the spinlock when done.
// [derived: param_1 is offset +8 into a task queue object (vtable at -8)]
// [derived: +0x48 = task list head, +0x50 = spinlock, +0x70/+0x6c = task params]
// Address: 0x7103548240 (208 bytes)
// ============================================================================
extern "C" void FUN_7103549170(long*, void(*)(long), int, u32);

void FUN_7103548240(long param_1) {
    // Call vtable[2] (flush/cleanup) on the parent object at param_1-8
    long* parent = (long*)(param_1 - 8);
    (*(void(**)(long*))(*(long*)parent + 0x10))(parent);

    // Acquire spinlock at +0x50
    u8* lock = (u8*)(param_1 + 0x50);
    u8 old;
    do {
        old = __atomic_exchange_n(lock, 1, __ATOMIC_ACQUIRE);
    } while (old & 1);

    // Walk linked list at +0x48
    long* list_ptr = (long*)(param_1 + 0x48);
    long* cur = (long*)*list_ptr;

    while (true) {
        if (cur == nullptr) {
            // Release spinlock
            __atomic_store_n(lock, (u8)0, __ATOMIC_RELEASE);
            return;
        }

        long* next = (long*)cur[9];  // next at +0x48
        s8 state = (s8)cur[0xe];     // state at +0x70

        if (state == 1) {
            // Skip — already processing
            list_ptr = (long*)(*list_ptr + 0x48);
            cur = next;
            continue;
        }

        if (state != 2) {
            // Enqueue for re-processing
            FUN_7103549170(cur + 1, (void(*)(long))FUN_7103548240,
                           (int)cur[0xd], *(u32*)((u8*)cur + 0x6c));
            list_ptr = (long*)(*list_ptr + 0x48);
            cur = next;
            continue;
        }

        // State 2: unlink from list and destroy
        *list_ptr = (long)next;
        (*(void(**)(void))(*(long*)cur + 8))();
        cur = next;
    }
}
