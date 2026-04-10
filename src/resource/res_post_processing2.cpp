// res_post_processing2.cpp — Pool allocator, fiber dispatch, and task queue functions
// Pool-d assignment: large resource service post-processing functions
// Output for: FUN_71035461f0, FUN_7103546c40, FUN_7103546d90, FUN_7103549f00,
//             FUN_710354b4b0, FUN_710354b800, FUN_710354c720, FUN_710354cc80, FUN_710354ce10

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"
#include "resource/Fiber.h"

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

// Global resource service pointer
// [derived: DAT_7105331f28 at 0x7105331f28 — ResServiceNX*, distinct from filesystem_info global]
__attribute__((visibility("hidden"))) extern long DAT_7105331f28;

// External function references
extern "C" s32 FUN_7103542ad0(LoadedDirectory*);  // get_redirected_dir_loading_state_recursive
extern "C" s32 FUN_7103542f30(u32*);  // get_region_index_from_arc
void FUN_7103546000(long param_1, u32 param_2, u32 param_3);  // queue_single_file_load
int FUN_7103546180(long param_1, u64* param_2, u32 param_3, u32 param_4);  // count_and_queue_directory_loads_recursive

// Move internal state helper
extern "C" void FUN_7101f6f1f0(void* dst, void* src);

// Deque grow helper
// [derived: called when deque is at capacity to allocate new page]
extern "C" void FUN_710354a7e0(long deque_base);

// Fiber methods
namespace phx {
    extern "C" void _ZN3phx5Fiber5setupEv(Fiber*, void*, const char*, u64);  // placeholder
}

// nn::os methods
namespace nn::os {
    void FinalizeLightEvent(void*);
    long GetTlsValue(u32);
}

// std::__1 destructors
namespace std { namespace __1 {
    extern "C" void _ZNSt3__115recursive_mutexD1Ev(void*);  // ~recursive_mutex
    extern "C" void _ZNSt3__15mutexD1Ev(void*);             // ~mutex
    extern "C" void __shared_weak_count__release_weak(void*);
}}

// Vtable for task queue
// [derived: Ghidra shows PTR_FUN_710522ed28 assigned as vtable]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710522ed28;

// Vtable for task dispatch closure
// [derived: Ghidra shows DAT_710522ec98 used as closure vtable in FUN_7103549f00]
__attribute__((visibility("hidden"))) extern void* DAT_710522ec98;

// ============================================================================
// FUN_7103546c40 — pool_slab_init
// Initializes a pool slab: sets element size and count, copies a closure from
// param_5, allocates a slab of (count * elem_size) bytes via the allocator at
// param_4+0x20, zeroes the memory, and builds a singly-linked free list.
// [derived: param_1 = PoolSlab* (0x60 bytes), param_2 = element size (stride)]
// [derived: param_3 = element count, param_4 = allocator context]
// [derived: param_5 = std::function-like closure (5 qwords, [4] = impl ptr)]
// [derived: free list: each element's first 8 bytes point to next free element]
// Address: 0x7103546c40 (336 bytes)
// ============================================================================
void FUN_7103546c40(u64* param_1, long param_2, u32 param_3, long param_4, long* param_5) {
    // Store element size and count
    *(int*)(param_1 + 1) = (int)param_2;
    *(u32*)((u8*)param_1 + 0xc) = param_3;

    // Clone/move the closure from param_5 into a local
    long local_80[4];
    long* local_60;
    local_60 = (long*)local_80;

    long* impl = (long*)param_5[4];
    if (impl == nullptr) {
        local_60 = nullptr;
    } else if (param_5 == impl) {
        // Inline storage: move-construct into local
        (*(void(**)(long*, long*))(*(long*)impl + 0x18))(impl, local_80);
    } else {
        // Heap storage: clone
        local_60 = (long*)(*(long(**)())(*(long*)impl + 0x10))();
    }

    // Move local closure into param_1's closure slot at +0x30
    FUN_7101f6f1f0(local_80, param_1 + 6);

    // Destroy local closure
    if (local_80 == (long*)local_60) {
        (*(void(**)())(*(long*)local_60 + 0x20))();
    } else if (local_60 != nullptr) {
        (*(void(**)())(*(long*)local_60 + 0x28))();
    }

    // Allocate slab: total = count * elem_size, alignment = 8
    u64 total_size = (u64)param_3 * param_2;
    long local_48 = 8;
    long* allocator = *(long**)(param_4 + 0x20);
    long local_80_2[1];
    local_80_2[0] = (long)total_size;
    if (allocator != nullptr) {
        u8* slab = (u8*)(*(long(**)(long*, long*, long*))(*(long*)allocator + 0x30))
                        (allocator, local_80_2, &local_48);
        memset(slab, 0, total_size);
        u8* slab_end = slab + total_size;
        *param_1 = 0;           // free_list_head = null
        param_1[2] = (u64)slab;
        param_1[3] = (u64)slab_end;
        *(u32*)(param_1 + 4) = param_3;

        // Build free list: link elements forward, updating head each time
        if (slab + param_2 <= slab_end) {
            u8* prev = nullptr;
            u8* cur = slab;
            do {
                *(u8**)cur = prev;        // current->next = previous
                *param_1 = (u64)cur;      // head = current
                u8* next = cur + param_2;
                prev = cur;
                cur = next;
            } while (cur + param_2 <= slab_end);
        }
        return;
    }
    // Should not reach here — allocator missing
    __builtin_trap();
}

// ============================================================================
// FUN_7103546d90 — pool_pop_or_grow
// Pops an element from the pool's free list. If all slabs are exhausted,
// allocates a new 0x60-byte PoolSlab, initializes it via FUN_7103546c40,
// and appends it to the pool manager's slab vector (with OOM-retry growth).
// Returns a pointer to the popped element (zeroed fields at +0x00..+0x20, +0x50).
// [derived: param_1 = PoolManager* — element_size at [0], count at +0x08 (u32)]
// [derived: param_1[2..4] = CppVector<PoolSlab*> (start, end, capacity)]
// [derived: param_1[6..10] = std::function #1 (closure, impl at [10])]
// [derived: param_1[12..16] = std::function #2 (closure, impl at [16])]
// Address: 0x7103546d90 (816 bytes)
// ============================================================================
void* FUN_7103546d90(u64* param_1) {
    u64** slab_iter = (u64**)param_1[2];

    while (true) {
        if (slab_iter == (u64**)param_1[3]) {
            // All slabs exhausted — allocate a new one (0x60 bytes)
            long* new_slab = (long*)je_aligned_alloc(0x10, 0x60);
            if (new_slab == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_flags = 0;
                    s64 oom_size = 0x60;
                    u64 r = (*(u64(**)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_flags, &oom_size);
                    if ((r & 1) != 0) {
                        new_slab = (long*)je_aligned_alloc(0x10, 0x60);
                        if (new_slab != nullptr) goto slab_allocated;
                    }
                }
                new_slab = nullptr;
            }
        slab_allocated:
            // Zero-init new slab fields
            new_slab[10] = 0;
            *(u32*)(new_slab + 4) = 0;
            new_slab[2] = 0;
            new_slab[3] = 0;
            new_slab[0] = 0;
            new_slab[1] = 0;

            // Read element_size and count from pool manager
            u64 elem_size = *param_1;
            u32 count = *(u32*)(param_1 + 1);

            // Clone closure #1 from param_1[10] (offset +0x50)
            long local_90[4];
            long* local_70;
            long* closure1 = (long*)param_1[10];
            if (closure1 == nullptr) {
                local_70 = nullptr;
                goto check_closure2;
            } else if ((u64*)(param_1 + 6) == (u64*)closure1) {
                local_70 = (long*)local_90;
                (*(void(**)(long*, long*))(*(long*)closure1 + 0x18))(closure1, local_90);
            } else {
                local_70 = (long*)(*(long(**)())(*(long*)closure1 + 0x10))();
            }

        check_closure2:;
            // Clone closure #2 from param_1[16] (offset +0x80)
            long local_c0[4];
            long* local_a0;
            long* closure2 = (long*)param_1[16];
            if (closure2 == nullptr) {
                local_a0 = nullptr;
            } else if ((u64*)(param_1 + 12) == (u64*)closure2) {
                local_a0 = (long*)local_c0;
                (*(void(**)(long*, long*))(*(long*)closure2 + 0x18))(closure2, local_c0);
            } else {
                local_a0 = (long*)(*(long(**)())(*(long*)closure2 + 0x10))();
            }

            // Initialize the new slab
            FUN_7103546c40((u64*)new_slab, (long)elem_size, count, (long)local_90, local_c0);

            // Destroy cloned closure #2
            if (local_c0 == (long*)local_a0) {
                (*(void(**)())(*(long*)local_a0 + 0x20))();
            } else if (local_a0 != nullptr) {
                (*(void(**)())(*(long*)local_a0 + 0x28))();
            }
            // Destroy cloned closure #1
            if (local_90 == (long*)local_70) {
                (*(void(**)())(*(long*)local_70 + 0x20))();
            } else if (local_70 != nullptr) {
                (*(void(**)())(*(long*)local_70 + 0x28))();
            }

            // Push new_slab pointer onto the slab vector
            u64* vec_end = (u64*)param_1[3];
            if (vec_end == (u64*)param_1[4]) {
                // Vector full — grow
                void* old_start = (void*)param_1[2];
                u64 old_size = (u64)vec_end - (u64)old_start;
                u64 new_count = (old_size >> 3) + 1;
                if (new_count >> 0x3d != 0) {
                    // overflow — should not happen
                    __builtin_trap();
                }
                u64 old_cap_bytes = (u64)param_1[4] - (u64)old_start;
                u64 new_cap;
                if ((u64)(old_cap_bytes >> 3) < 0xfffffffffffffffULL) {
                    new_cap = old_cap_bytes >> 2;
                    if (new_count > new_cap) new_cap = new_count;
                } else {
                    new_cap = 0x1fffffffffffffffULL;
                }

                u64 alloc_bytes = new_cap * 8;
                if (alloc_bytes == 0) alloc_bytes = 1;

                void* new_buf = je_aligned_alloc(0x10, alloc_bytes);
                if (new_buf == nullptr) {
                    if (DAT_7105331f00 != nullptr) {
                        u32 oom_flags2 = 0;
                        s64 oom_size2 = (s64)alloc_bytes;
                        u64 r2 = (*(u64(**)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                  (DAT_7105331f00, &oom_flags2, &oom_size2);
                        if ((r2 & 1) != 0) {
                            new_buf = je_aligned_alloc(0x10, alloc_bytes);
                            if (new_buf != nullptr) goto vec_grow_done;
                        }
                    }
                    new_buf = nullptr;
                }
            vec_grow_done:
                u64* insert_pos = (u64*)((u8*)new_buf + ((old_size >> 3) * 8));
                *insert_pos = (u64)new_slab;
                if ((s64)old_size > 0) {
                    memcpy(new_buf, old_start, old_size);
                }
                param_1[2] = (u64)new_buf;
                param_1[3] = (u64)(insert_pos + 1);
                param_1[4] = (u64)((u8*)new_buf + new_cap * 8);
                if (old_start != nullptr) {
                    jeFree_710392e590(old_start);
                }
            } else {
                *vec_end = (u64)new_slab;
                param_1[3] = param_1[3] + 8;
            }

            // Get free list head from new slab
            long* free_head = (long*)*new_slab;
            if (free_head == nullptr) {
                return new_slab;
            }
            // Pop from free list
            *new_slab = *free_head;
            *(int*)(new_slab + 4) = (int)new_slab[4] - 1;
            return free_head;
        }

        // Try existing slab
        long* slab = (long*)*slab_iter;
        long* free_head = (long*)*slab;
        slab_iter++;
        if (free_head != nullptr) {
            // Pop from free list
            *slab = *free_head;
            *(int*)(slab + 4) = (int)slab[4] - 1;
            return free_head;
        }
    }
}

// FUN_71035461f0 — process_directory_file_loads
// REMOVED: duplicate definition — canonical version is in res_remaining_large.cpp
// (with proper ResServiceNX*/LoadedDirectory* typing)

#if 0  // Duplicate removed — see res_remaining_large.cpp
int FUN_71035461f0(long param_1, u32* param_2, u32 param_3, u32 param_4) {
    LoadedDirectory* dir = (LoadedDirectory*)param_2;

    // Early exit conditions:
    // If file_group_index is invalid, or the directory state check fails, skip
    if (dir->file_group_index == 0xffffff) return 0;

    char* state_ptr = (char*)((u8*)dir + 10);  // +0x0A = state-like field? Actually +0x0A in struct is pad[0]
    // Actually offset 10 from param_2. param_2 is u32*, so byte offset 10 = LoadedDirectory+0x0A
    // That's inside pad[2] of LoadedDirectory. Let me re-examine.
    // In Ghidra: pcVar1 = (char *)((long)param_2 + 10), which is byte offset 10
    // LoadedDirectory: +0x08 = flags (u8), +0x09 = state (u8), +0x0A = pad[2]
    // So byte offset 10 = pad[0]. But Ghidra checks *pcVar1 == '\0' as a condition.
    // Actually, looking more carefully at the Ghidra code, the check is:
    //   *pcVar1 == '\0' || ... various conditions ...
    // If *pcVar1 is '\0', the whole block runs. This seems like a "not loaded" check.
    // Wait, the logic is inverted — the block runs when the conditions are met (via short-circuit).
    // Let me re-read the Ghidra condition:
    //   if ((*param_2 != 0xffffff) &&
    //      (((((pcVar1 = byte+10, *pcVar1 == '\0' || *param_2 == 0xffffff ||
    //          (state < 1)) || ((int)param_3 < (int)(uint)*(byte *)(+0xb))) ||
    //         (*param_2 == 0xffffff)) ||
    //        ((state != 3 && state != 1 && state != 2))))) {
    //     ... main body ...
    //   }
    //   return 0;
    //
    // The outer condition *param_2 != 0xffffff gates everything.
    // The inner OR-chain means the body runs if ANY of these is true:
    //   1. byte at +0x0A == 0 (not loaded?)
    //   2. file_group_index == 0xffffff (redundant with outer)
    //   3. state < 1 (state == 0)
    //   4. param_3 < byte at +0x0B
    //   5. file_group_index == 0xffffff (redundant again)
    //   6. state is not 3,1,2 (i.e., state == 0 or state >= 4)
    //
    // So the body runs for most directories. The return 0 only happens when
    // the directory is fully loaded (state 1,2,3), byte+0xA != 0, and priority ok.
    // Actually wait, the conditions are ORed, so if ANY is true, body runs.
    // The body is SKIPPED only when ALL conditions are false, meaning:
    //   - byte+0xA != 0 AND state >= 1 AND param_3 >= byte+0xB AND state in {1,2,3}
    // In that case, return 0.
    //
    // This is getting confusing. Let me just faithfully reproduce the logic.

    u8* dir_bytes = (u8*)param_2;
    u8 byte_0xa = dir_bytes[0xa];
    s32 state = FUN_7103542ad0(dir);

    if (byte_0xa != 0 && dir->file_group_index != 0xffffff && state >= 1 &&
        !((s32)param_3 < (s32)(u32)dir_bytes[0xb]) &&
        dir->file_group_index != 0xffffff &&
        (state == 3 || state == 1 || state == 2)) {
        return 0;
    }

    // Main body: iterate child_path_indices
    u32* path_iter = dir->child_path_indices.start;
    u32* path_end = dir->child_path_indices.end;
    int local_count;

    if (path_iter == path_end) {
        local_count = 0;
    } else {
        u32 dir_group_idx = dir->file_group_index;
        u64 dir_group_idx64 = (u64)dir_group_idx;
        int file_offset = 0;
        local_count = 0;

        do {
            // Lock filesystem and look up filepath/data
            long fs_info = *(long*)(param_1 + 0xd0);
            u32 filepath_idx = *path_iter;
            lock_71039c1490(*(void**)fs_info);

            u32* filepath_entry = nullptr;
            long* data_entry = nullptr;

            if (filepath_idx == 0xffffff || filepath_idx >= *(u32*)(fs_info + 0x18)) {
                goto lookup_fail;
            }
            filepath_entry = (u32*)(*(long*)(fs_info + 8) + (u64)filepath_idx * 8);
            if ((u8)filepath_entry[1] == 0) goto lookup_fail;
            {
                u32 data_idx = *filepath_entry;
                if (*(u8*)(*(long*)(fs_info + 0x10) + (u64)data_idx * 0x18 + 0xc) == 0) {
                    goto lookup_fail;
                }
                data_entry = nullptr;
                if (data_idx != 0xffffff) {
                    data_entry = (long*)(*(long*)(fs_info + 0x10) + (u64)data_idx * 0x18);
                }
                goto lookup_done;
            }

        lookup_fail:
            filepath_entry = nullptr;
            data_entry = nullptr;

        lookup_done:
            unlock_71039c14a0(*(void**)fs_info);

            if (filepath_entry != nullptr && data_entry != nullptr && *data_entry == 0) {
                // Lookup ARC tables to determine if this file needs loading
                long path_info = **(long**)(*(long*)(param_1 + 0xd0) + 0x78);
                u32 folder_count = *(u32*)(*(long*)(path_info + 0x40) + 0xc);

                if (dir_group_idx < folder_count) {
                    // DirInfo path: file_info_start_index + file_offset
                    u64 file_info_global_idx = (u64)(u32)(
                        *(int*)(*(long*)(path_info + 0x78) + dir_group_idx64 * 0x34 + 0x20) + file_offset);

                    // Check FileInfo flags: bit 4 of flags byte at +0x0E
                    u8 file_flags = *(u8*)(*(long*)(path_info + 0x90) + file_info_global_idx * 0x10 + 0xe);
                    if (((file_flags >> 4) & 1) == 0) {
                        // Not region-locked, check FileData
                        goto check_file_data;
                    }
                    // Region-locked: check if the file data's region flag is set
                    u32 file_data_idx = *(u32*)(*(long*)(path_info + 0x90) + file_info_global_idx * 0x10 + 4);
                    u8 data_flags = *(u8*)(*(long*)(path_info + 0x98) + (u64)file_data_idx * 0xc + 0xb);
                    if ((data_flags >> 3) & 1) {
                        goto check_file_data;
                    }
                    // Fall through to queue
                    goto queue_file;
                } else {
                    // DirectoryOffset path: folder_offsets table
                    // (file_start_ptr computed below in the shared path)

                check_file_data:;
                    int* piVar13;
                    if (dir_group_idx < folder_count) {
                        piVar13 = (int*)(*(long*)(path_info + 0x78) + dir_group_idx64 * 0x34 + 0x20);
                    } else {
                        piVar13 = (int*)(*(long*)(path_info + 0x80) + dir_group_idx64 * 0x1c + 0x10);
                    }

                    long file_infos_base = *(long*)(path_info + 0x90);
                    u32 file_info_idx = (u32)(*piVar13 + file_offset);
                    long file_info_entry = file_infos_base + (u64)file_info_idx * 0x10;

                    // Follow the indirection chain: file_info -> file_info_indices -> folder_child_hashes
                    u32 fi2d_idx = *(u32*)(file_info_entry + 4);
                    u64 fchild_raw = *(u64*)(*(long*)(path_info + 0x68) + (u64)fi2d_idx * 8 + 4);
                    long target_entry = file_infos_base + ((fchild_raw & 0xffffff) * 0x10);

                    u32 file_data_index = *(u32*)(target_entry + 8);
                    u32 load_type = (*(u32*)(target_entry + 0xc) >> 15) & 3;

                    int locale_offset;
                    if (load_type == 2) {
                        locale_offset = *(int*)(DAT_7105331f28 + 0xd8);  // region_idx
                    } else if (load_type == 1) {
                        locale_offset = *(int*)(DAT_7105331f28 + 0xdc);  // language_idx
                    } else {
                        goto check_data_flag;
                    }
                    {
                        int adj = 0;
                        if (locale_offset != -1) adj = locale_offset;
                        file_data_index = file_data_index + adj + 1;
                    }

                check_data_flag:;
                    // Check if file data has the "loaded" flag (bit 4 at +0x0B)
                    u8 fd_flags = *(u8*)(*(long*)(path_info + 0x98) + (u64)file_data_index * 0xc + 0xb);
                    if ((fd_flags >> 4) & 1) {
                        goto queue_file;
                    }

                    // Check the file's folder group index and look up offset
                    u32 folder_group;
                    if (dir_group_idx < folder_count) {
                        piVar13 = (int*)(*(long*)(path_info + 0x78) + dir_group_idx64 * 0x34 + 0x20);
                    } else {
                        piVar13 = (int*)(*(long*)(path_info + 0x80) + dir_group_idx64 * 0x1c + 0x10);
                    }
                    file_info_idx = (u32)(*piVar13 + file_offset);
                    u32 fi_folder_idx = *(u32*)(file_infos_base + (u64)file_info_idx * 0x10);
                    // Get folder group from file_info_to_datas, mask to 24-bit
                    fchild_raw = *(u64*)(*(long*)(path_info + 0x68) +
                                         (u64)*(u32*)(file_infos_base + (u64)file_info_idx * 0x10 + 4) * 8 + 4);
                    folder_group = *(u32*)(file_infos_base + (fchild_raw & 0xffffff) * 0x10);

                    u64 file_offset_val;
                    if (folder_group == 0xffffff || folder_group >= *(u32*)(*(long*)(path_info + 0x40) + 4)) {
                        file_offset_val = 0;
                    } else {
                        file_offset_val = *(u64*)(*(long*)(path_info + 0x60) + (u64)folder_group * 0x20) & 0xffffffffffULL;
                    }

                    // Check extra/regional table for override
                    long extra_base = *(long*)(path_info + 0xe8);
                    if (extra_base != 0) {
                        s32 region_check = *(s32*)(path_info + 0x110);
                        if (region_check != (s32)0xffff) {
                            u32 local_68;
                            local_68 = *(u32*)(*(long*)(
                                **(long**)(DAT_7105331f20 + 0x78) + 0x40) + 0x3c) & 0xffffff;
                            s32 current_region = FUN_7103542f30(&local_68);
                            if (region_check != current_region) {
                                u32 extra_count_field = *(u32*)(path_info + 0x114);
                                if (extra_count_field < *(u32*)(*(long*)(path_info + 0xe0) + 4)) {
                                    long extra_entry = *(long*)(path_info + 0xf8) + (u64)extra_count_field * 0x30;
                                    u32* bucket = *(u32**)(extra_entry + 8);
                                    u64 bucket_count = (u64)*bucket;
                                    u64 quot = 0;
                                    if (bucket_count != 0) {
                                        quot = file_offset_val / bucket_count;
                                    }
                                    long remainder = file_offset_val - quot * bucket_count;
                                    u64 search_count = (u64)bucket[remainder * 2 + 3];
                                    u64* search_start = (u64*)(*(long*)(extra_entry + 0x10) +
                                                              (u64)bucket[remainder * 2 + 2] * 8);
                                    u64* search_ptr = search_start;

                                    if (search_count != 0) {
                                        do {
                                            u64 half = search_count;
                                            if ((s64)search_count < 0) half = search_count + 1;
                                            half = (s64)half >> 1;
                                            u64* mid = search_ptr + half + 1;
                                            u64 remaining = search_count + ~half;
                                            if (file_offset_val <= (search_ptr[half] & 0xffffffffffULL)) {
                                                mid = search_ptr;
                                                remaining = half;
                                            }
                                            search_ptr = mid;
                                            search_count = remaining;
                                        } while (search_count != 0);
                                    }

                                    if (search_ptr != nullptr &&
                                        (*search_ptr & 0xffffffffffULL) == file_offset_val) {
                                        long override_entry = *(long*)(*(long*)(path_info + 0xf8) +
                                                              (u64)extra_count_field * 0x30) +
                                                              (*search_ptr >> 0x28) * 0x14;
                                        if (override_entry != 0) {
                                            goto queue_file;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Mark file for loading: set state and priority in LoadedData
                    u8* data_state = (u8*)((u8*)data_entry + 0xd);
                    if (*data_state == 0) {
                        data_state[0] = 1;     // state = Unloaded
                        data_state[1] = 0;
                        data_state[2] = 0;
                        data_state[3] = 0;
                    }
                    *(u8*)((u8*)data_entry + 0xf) =
                        (*(u8*)((u8*)data_entry + 0xf) & 0xc7) | (u8)((param_3 & 7) << 3);
                }
                local_count++;
            }

            path_iter++;
            file_offset++;
            continue;

        queue_file:
            FUN_7103546000(param_1, filepath_idx, param_3);
            local_count++;
            path_iter++;
            file_offset++;
        } while (path_iter != path_end);
    }

    // Process redirection directory if present
    int* redir = *(int**)((u8*)param_2 + 0x40);
    if (redir != nullptr && *redir != (int)0xffffff) {
        int redir_count = FUN_7103546180(param_1, (u64*)redir, (u64)param_3, 1);
        local_count += redir_count;
    }

    // Check if we need to update service state and enqueue
    if (local_count == 0 && dir->file_group_index != 0xffffff) {
        s32 final_state = FUN_7103542ad0(dir);
        if (final_state == 3) {
            return 0;
        }
    }

    // Update service state
    if (*(s32*)(param_1 + 0xe0) != 2) {
        *(u32*)(param_1 + 0xe0) = 1;
    }

    // Set directory loaded state if not already loaded
    if (dir->file_group_index == 0xffffff || FUN_7103542ad0(dir) < 1) {
        *(u32*)((u8*)param_2 + 9) = 1;
    }

    // Atomic increment of incoming_request_count at +0x0C
    // [derived: ExclusiveMonitorPass = LDAXRB/STXRB pattern for atomic byte increment]
    __atomic_fetch_add((u8*)((u8*)param_2 + 0xa), 1, __ATOMIC_ACQ_REL);

    // Set priority
    *(u8*)((u8*)param_2 + 0xb) = (u8)param_3;

    // If skip_enqueue flag is set, return count without creating queue entry
    if (param_4 & 1) {
        return local_count;
    }

    // Allocate and enqueue a load request
    long* task = (long*)FUN_7103546d90((u64*)(*(u64*)(param_1 + 0x50)));
    task[0] = 0;
    task[1] = 0;
    task[2] = 0xffffff00000000LL;
    task[3] = 0xffffff;

    long list_base = param_1 + (u64)param_3 * 0x18;
    *(u32*)(task + 3) = dir->file_group_index;
    *(int*)((u8*)task + 0x1c) = local_count;

    u64* list_end = *(u64**)(list_base + 0x68);
    task[0] = list_base + 0x60;
    task[1] = (long)list_end;
    *(long**)(list_base + 0x68) = task;
    *list_end = (u64)task;
    *(long*)(list_base + 0x58) = *(long*)(list_base + 0x58) + 1;

    *(u8*)(param_1 + 0xe7) = 1;
    *(u8*)(param_1 + 0xe4) = 1;

    return local_count;
}
#endif  // Duplicate FUN_71035461f0

// ============================================================================
// FUN_7103549f00 — fiber_pool_get_or_create
// Gets a Fiber from the pool's deque cache. If the deque is empty, allocates a
// new 8-byte Fiber wrapper, calls phx::Fiber::setup with a task closure and the
// configured stack size. If the deque has entries, pops from the back and
// optionally shrinks the deque if excess pages accumulate.
// [derived: param_1 = TaskScheduler*, +0x118..+0x140 = std::deque<Fiber*>]
// [derived: +0x138 = deque size, +0x130 = deque front offset]
// [derived: +0x140 = fiber stack size for phx::Fiber::setup]
// [derived: deque page size = 512 entries (0x1000 bytes / 8 bytes per ptr)]
// Address: 0x7103549f00 (2,272 bytes — note: Ghidra may include inlined code)
// ============================================================================
extern "C" void phx__Fiber__setup(void*, void*, const char*, u64);

void* FUN_7103549f00(long param_1) {
    long deque_size = *(long*)(param_1 + 0x138);

    if (deque_size == 0) {
        // Deque empty — allocate a new Fiber
        void* fiber = je_aligned_alloc(0x10, 8);
        if (fiber == nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = 8;
            (*(void(**)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                (DAT_7105331f00, &oom_flags, &oom_size);
            fiber = je_aligned_alloc(0x10, 8);
        }
        *(u64*)fiber = 0;

        // Build closure: vtable + param_1 pointer, using inline storage
        // [derived: DAT_710522ec98 = vtable for task fiber entry closure]
        u8* closure_buf[40];
        void** local_70 = (void**)closure_buf;
        *local_70 = &DAT_710522ec98;
        *(long*)(closure_buf + 8) = param_1;
        void** local_50 = local_70;

        phx__Fiber__setup(fiber, local_70, "Task fiber", *(u64*)(param_1 + 0x140));

        // Destroy closure
        if (local_70 == local_50) {
            (*(void(**)())(*(long*)local_50 + 0x20))();
        } else if (local_50 != nullptr) {
            (*(void(**)())(*(long*)local_50 + 0x28))();
        }

        return fiber;
    }

    // Deque has entries — pop from back
    u64 back_idx = *(long*)(param_1 + 0x130) + deque_size - 1;
    long map_base = *(long*)(param_1 + 0x118);
    void* fiber = *(void**)(*(long*)(map_base + ((back_idx >> 6) & 0x3fffffffffffff8ULL)) +
                           (back_idx & 0x1ff) * 8);

    *(long*)(param_1 + 0x138) = deque_size - 1;

    // Check if we should shrink the deque (> 1024 excess slots)
    long map_end_off = *(long*)(param_1 + 0x120) - *(long*)(param_1 + 0x118);
    long map_capacity = 0;
    if (map_end_off != 0) {
        map_capacity = map_end_off * 0x40 - 1;
    }
    if ((u64)((1 - deque_size - *(long*)(param_1 + 0x130)) + map_capacity) > 0x3ff) {
        // Free the last page
        long* last_page = (long*)(*(long*)(param_1 + 0x120) - 8);
        if (*last_page != 0) {
            jeFree_710392e590((void*)*last_page);
            last_page = (long*)(*(long*)(param_1 + 0x120) - 8);
        }
        *(long*)(param_1 + 0x120) = (long)last_page;
    }

    return fiber;
}

// ============================================================================
// FUN_710354b800 — deque_triple_destructor
// Destroys three std::deque<T*> instances stored consecutively in a struct.
// Each deque has: map_start (+0x00 offset), map_end (+0x08), front_offset (+0x10),
// size (+0x18). Iterates each deque's map pages, frees allocations, resets counts,
// and adjusts the map pointers. Stride between deques is 0x30 (6 qwords).
// [derived: param_1 points to the first deque in a triplet]
// [derived: deque layout: [0]=unused, [1]=map_start, [2]=map_end, [3]=unused,
//  [4]=front_offset, [5]=size, [6]=map_pages_alloc]
// Address: 0x710354b800 (912 bytes)
// ============================================================================
// Macro for deque page cleanup — used 3 times for 3 deques in FUN_710354b800
// MS=map_start_idx, ME=map_end_idx, FO=front_offset_idx, SZ=size_idx, AL=alloc_idx
#define DEQUE_CLEANUP(p, MS, ME, FO, SZ, AL) do { \
    long* _ms = (long*)(p)[MS]; \
    long* _me = (long*)(p)[ME]; \
    long _diff = (long)_me - (long)_ms; \
    if (_diff != 0) { \
        u64 _front = (u64)(p)[FO]; \
        long* _pp = (long*)((u8*)_ms + ((_front >> 6) & 0x3fffffffffffff8ULL)); \
        long _it = *_pp + (_front & 0x1ff) * 8; \
        u64 _end = (p)[SZ] + _front; \
        while (*(long*)((u8*)_ms + ((_end >> 6) & 0x3fffffffffffff8ULL)) + \
               (_end & 0x1ff) * 8 != _it) { \
            _it += 8; \
            if (_it - *_pp == 0x1000) { _pp++; _it = *_pp; } \
        } \
    } \
    (p)[SZ] = 0; \
    while ((u64)(_diff >> 3) > 2) { \
        if (*_ms != 0) { \
            jeFree_710392e590((void*)*_ms); \
            _ms = (long*)(p)[MS]; \
            _me = (long*)(p)[ME]; \
        } \
        _ms++; \
        (p)[MS] = (long)_ms; \
        _diff = (long)_me - (long)_ms; \
    } \
    { u64 _pc = (u64)(_diff >> 3); \
    if (_pc == 1) { (p)[FO] = 0x100; } \
    else if (_pc == 2) { (p)[FO] = 0x200; } } \
    if (_ms != _me) { \
        do { \
            if (*_ms != 0) { jeFree_710392e590((void*)*_ms); } \
            _ms++; \
        } while (_me != _ms); \
        long _ev = (p)[ME]; \
        if (_ev != (p)[MS]) { \
            (p)[ME] = _ev + (~((_ev - 8) - (p)[MS]) & 0xfffffffffffffff8ULL); \
        } \
    } \
    if ((p)[AL] != 0) { jeFree_710392e590((void*)(p)[AL]); } \
} while(0)

void FUN_710354b800(long* param_1) {
    // Deque 3 (offsets +0x68..+0x88, alloc +0x60)
    DEQUE_CLEANUP(param_1, 0xd, 0xe, 0x10, 0x11, 0xc);
    // Deque 2 (offsets +0x38..+0x58, alloc +0x30)
    DEQUE_CLEANUP(param_1, 7, 8, 0xa, 0xb, 6);
    // Deque 1 (offsets +0x08..+0x28, alloc +0x00)
    DEQUE_CLEANUP(param_1, 1, 2, 4, 5, 0);
}

// ============================================================================
// FUN_710354b4b0 — task_scheduler_destructor
// Destroys a task scheduler: moves pending/ready task vectors into the fiber
// deque, destroys all cached fibers (calling phx::Fiber::~Fiber + je_free),
// shrinks the deque, finalizes the light event, destroys the mutex, and calls
// FUN_710354b800 to clean up the triple-deque structure.
// [derived: param_1 = TaskScheduler*]
// [derived: +0xe0/+0xe8 = pending_tasks vector (start/end)]
// [derived: +0xf8/+0x100 = ready_tasks vector (start/end)]
// [derived: +0x118..+0x138 = fiber deque (map_start, map_end, front_offset, size)]
// [derived: +0x148 = nn::os::LightEventType for wakeup signaling]
// [derived: +0xa0 = std::mutex for synchronization]
// Address: 0x710354b4b0 (848 bytes)
// ============================================================================
extern "C" void _ZN3phx5Fiber6dFiberEv(void*);  // phx::Fiber::~Fiber

void FUN_710354b4b0(long param_1) {
    // Push pending tasks (from +0xe0..+0xe8) into the fiber deque
    long pending_iter = *(long*)(param_1 + 0xe0);
    long pending_end = *(long*)(param_1 + 0xe8);
    if (pending_iter != pending_end) {
        long deque_size = *(long*)(param_1 + 0x138);
        do {
            long map_base = *(long*)(param_1 + 0x118);
            long map_diff = *(long*)(param_1 + 0x120) - map_base;
            u64 fiber_ptr = *(u64*)(pending_iter + 0x10);
            u64 back_idx = deque_size + *(long*)(param_1 + 0x130);

            u64 map_cap = 0;
            if (map_diff != 0) map_cap = map_diff * 0x40 - 1;

            if (map_cap == back_idx) {
                FUN_710354a7e0(param_1 + 0x110);
                map_base = *(long*)(param_1 + 0x118);
                back_idx = *(long*)(param_1 + 0x130) + *(long*)(param_1 + 0x138);
            }

            pending_iter += 0x20;
            *(u64*)(*(long*)(map_base + ((back_idx >> 6) & 0x3fffffffffffff8ULL)) +
                    (back_idx & 0x1ff) * 8) = fiber_ptr;
            deque_size = *(long*)(param_1 + 0x138) + 1;
            *(long*)(param_1 + 0x138) = deque_size;
        } while (pending_end != pending_iter);
    }

    // Push ready tasks (from +0xf8..+0x100) into the fiber deque
    long ready_iter = *(long*)(param_1 + 0xf8);
    long ready_end = *(long*)(param_1 + 0x100);
    long deque_size;
    if (ready_iter == ready_end) {
        deque_size = *(long*)(param_1 + 0x138);
    } else {
        deque_size = *(long*)(param_1 + 0x138);
        do {
            long map_base = *(long*)(param_1 + 0x118);
            long map_diff = *(long*)(param_1 + 0x120) - map_base;
            u64 fiber_ptr = *(u64*)(ready_iter + 0x10);
            u64 back_idx = deque_size + *(long*)(param_1 + 0x130);

            u64 map_cap = 0;
            if (map_diff != 0) map_cap = map_diff * 0x40 - 1;

            if (map_cap == back_idx) {
                FUN_710354a7e0(param_1 + 0x110);
                map_base = *(long*)(param_1 + 0x118);
                back_idx = *(long*)(param_1 + 0x130) + *(long*)(param_1 + 0x138);
            }

            ready_iter += 0x20;
            *(u64*)(*(long*)(map_base + ((back_idx >> 6) & 0x3fffffffffffff8ULL)) +
                    (back_idx & 0x1ff) * 8) = fiber_ptr;
            deque_size = *(long*)(param_1 + 0x138) + 1;
            *(long*)(param_1 + 0x138) = deque_size;
        } while (ready_end != ready_iter);
    }

    // Destroy all fibers in the deque
    if (deque_size != 0) {
        long* size_ptr = (long*)(param_1 + 0x138);
        long* map_end_ptr = (long*)(param_1 + 0x120);
        do {
            long front_off = *(long*)(param_1 + 0x130);
            long cur_size = deque_size;
            long back_idx = deque_size - 1;
            long map_base = *(long*)(param_1 + 0x118);

            void* fiber = *(void**)(*(long*)(map_base + (((back_idx + front_off) >> 6) & 0x3fffffffffffff8ULL)) +
                                    ((back_idx + front_off) & 0x1ff) * 8);
            if (fiber != nullptr) {
                _ZN3phx5Fiber6dFiberEv(fiber);
                jeFree_710392e590(fiber);
                deque_size = *size_ptr;
                front_off = *(long*)(param_1 + 0x130);
                back_idx = deque_size - 1;
                map_base = *(long*)(param_1 + 0x118);
            }

            *size_ptr = back_idx;

            long map_diff = *map_end_ptr - map_base;
            long excess = (1 - deque_size - front_off);
            long cap = 0;
            if (map_diff != 0) cap = map_diff * 0x40 - 1;

            deque_size = back_idx;
            if ((u64)(excess + cap) > 0x3ff) {
                long* last_page = (long*)(*map_end_ptr - 8);
                if (*last_page != 0) {
                    jeFree_710392e590((void*)*last_page);
                    back_idx = *size_ptr;
                    last_page = (long*)(*map_end_ptr - 8);
                }
                *map_end_ptr = (long)last_page;
                deque_size = back_idx;
            }
        } while (deque_size != 0);
    }

    // Finalize light event
    nn::os::FinalizeLightEvent((void*)(param_1 + 0x148));

    // Drain and clean up the deque map pages
    long* map_start = (long*)*(long*)(param_1 + 0x118);
    long* map_end = (long*)*(long*)(param_1 + 0x120);
    long map_diff = (long)map_end - (long)map_start;

    if (map_diff != 0) {
        u64 front = *(u64*)(param_1 + 0x130);
        long* page_ptr = (long*)((u8*)map_start + ((front >> 6) & 0x3fffffffffffff8ULL));
        long iter = *page_ptr + (front & 0x1ff) * 8;
        long end_idx = *(long*)(param_1 + 0x138) + front;
        while (*(long*)((u8*)map_start + ((end_idx >> 6) & 0x3fffffffffffff8ULL)) +
               (end_idx & 0x1ff) * 8 != iter) {
            iter += 8;
            if (iter - *page_ptr == 0x1000) {
                page_ptr++;
                iter = *page_ptr;
            }
        }
    }

    *(long*)(param_1 + 0x138) = 0;

    while ((u64)(map_diff >> 3) > 2) {
        if (*map_start != 0) {
            jeFree_710392e590((void*)*map_start);
            map_start = (long*)*(long*)(param_1 + 0x118);
            map_end = (long*)*(long*)(param_1 + 0x120);
        }
        map_start++;
        *(long*)(param_1 + 0x118) = (long)map_start;
        map_diff = (long)map_end - (long)map_start;
    }

    u64 remaining = (u64)(map_diff >> 3);
    if (remaining == 1) {
        *(long*)(param_1 + 0x130) = 0x100;
    } else if (remaining == 2) {
        *(long*)(param_1 + 0x130) = 0x200;
    }

    if (map_start != map_end) {
        do {
            if (*map_start != 0) {
                jeFree_710392e590((void*)*map_start);
            }
            map_start++;
        } while (map_end != map_start);
        long end_val = *(long*)(param_1 + 0x120);
        if (end_val != *(long*)(param_1 + 0x118)) {
            *(long*)(param_1 + 0x120) = end_val +
                (~((end_val - 8) - *(long*)(param_1 + 0x118)) & 0xfffffffffffffff8ULL);
        }
    }

    // Free deque map allocation
    if (*(long*)(param_1 + 0x110) != 0) {
        jeFree_710392e590((void*)*(long*)(param_1 + 0x110));
    }

    // Free ready_tasks vector
    if (*(long*)(param_1 + 0xf8) != 0) {
        *(long*)(param_1 + 0x100) = *(long*)(param_1 + 0xf8);
        jeFree_710392e590((void*)*(long*)(param_1 + 0xf8));
    }

    // Free pending_tasks vector
    if (*(long*)(param_1 + 0xe0) != 0) {
        *(long*)(param_1 + 0xe8) = *(long*)(param_1 + 0xe0);
        jeFree_710392e590((void*)*(long*)(param_1 + 0xe0));
    }

    // Destroy mutex
    std::__1::_ZNSt3__15mutexD1Ev((void*)(param_1 + 0xa0));

    // Clean up triple-deque at +0x10
    FUN_710354b800((long*)(param_1 + 0x10));
}

// ============================================================================
// FUN_710354c720 — dispatch_task_to_fiber
// Stores task parameters in TLS-local state, pushes a task descriptor onto the
// pending task vector (with vector growth + OOM retry), then gets or creates a
// Fiber from FUN_7103549f00 and switches to it.
// [derived: param_1 = TLS slot (nn::os::TlsSlot), 0xffffffff = invalid]
// [derived: param_2 = task descriptor (int* where [0] = task count)]
// [derived: TLS value = TaskSchedulerTLS*, with task vectors at various offsets]
// [derived: +0xc0 = current_task (8 bytes), +0xc8 = task_param, +0xd0 = fiber_ptr]
// [derived: +0xd8 = task_id (u32), +0xe0..+0xf0 = pending_tasks CppVector<TaskEntry>]
// [derived: TaskEntry is 0x20 bytes: [0]=current_task, [1]=task_param, [2]=fiber_ptr, [3]=task_id+pad]
// Address: 0x710354c720 (544 bytes)
// ============================================================================
void FUN_710354c720(u32 param_1, int* param_2) {
    long tls_val;
    if (param_1 == 0xffffffff) {
        tls_val = 0;
    } else {
        tls_val = nn::os::GetTlsValue(param_1);
    }

    if (*param_2 < 1) return;

    u64* vec_end = *(u64**)(tls_val + 0xe8);
    u64* task_state = (u64*)(tls_val + 0xc0);

    *(int**)(tls_val + 0xc8) = param_2;

    if (vec_end != *(u64**)(tls_val + 0xf0)) {
        // Space available in vector — push directly
        u64 val0 = *task_state;
        u64 val1 = *(u64*)(tls_val + 0xc8);
        u64 val2 = *(u64*)(tls_val + 0xd8);
        vec_end[2] = *(u64*)(tls_val + 0xd0);
        vec_end[3] = val2;
        vec_end[0] = val0;
        vec_end[1] = val1;
        *(long*)(tls_val + 0xe8) = *(long*)(tls_val + 0xe8) + 0x20;
    } else {
        // Vector full — grow with OOM retry
        void* old_start = *(void**)(tls_val + 0xe0);
        u64 old_size = (u64)vec_end - (u64)old_start;
        u64 new_count = (old_size >> 5) + 1;

        if (new_count >> 0x3b != 0) {
            __builtin_trap();
        }

        long cap_diff = (long)*(u64**)(tls_val + 0xf0) - (long)old_start;
        u64 new_cap;
        if ((u64)(cap_diff >> 5) < 0x3ffffffffffffffULL) {
            new_cap = cap_diff >> 4;
            if (new_count > new_cap) new_cap = new_count;
            if (new_cap == 0) goto alloc_null;
            if (new_cap >> 0x3b != 0) __builtin_trap();
        } else {
            new_cap = 0x7ffffffffffffffULL;
        }

        {
            long alloc_bytes = new_cap * 0x20;
            if (alloc_bytes == 0) alloc_bytes = 1;

            void* new_buf = je_aligned_alloc(0x10, alloc_bytes);
            if (new_buf == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_flags = 0;
                    s64 oom_size = alloc_bytes;
                    u64 r = (*(u64(**)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_flags, &oom_size);
                    if ((r & 1) != 0) {
                        new_buf = je_aligned_alloc(0x10, alloc_bytes);
                        if (new_buf != nullptr) goto vec_grow_done;
                    }
                }
                new_buf = nullptr;
            }
        vec_grow_done:
            {
                u64 val0 = *task_state;
                u64 val1 = *(u64*)(tls_val + 0xc8);
                u64* insert = (u64*)((u8*)new_buf + ((old_size >> 5) * 0x20));
                u64 val2 = *(u64*)(tls_val + 0xd8);
                insert[2] = *(u64*)(tls_val + 0xd0);
                insert[3] = val2;
                insert[0] = val0;
                insert[1] = val1;

                if ((s64)old_size > 0) {
                    memcpy(new_buf, old_start, old_size);
                }
                *(void**)(tls_val + 0xe0) = new_buf;
                *(u64**)(tls_val + 0xe8) = insert + 4;
                *(void**)(tls_val + 0xf0) = (void*)((u8*)new_buf + new_cap * 0x20);
                if (old_start != nullptr) {
                    jeFree_710392e590(old_start);
                }
            }
        }
    }

    if (0) {
    alloc_null:
        // This handles the new_cap == 0 case (same write pattern, null buffer)
        // Practically unreachable
        return;
    }

    // Get or create a fiber and switch to it
    long fiber_val = *(long*)(tls_val + 0xd0);
    if (fiber_val == 0) {
        void* fiber = FUN_7103549f00(tls_val);
        *(void**)(tls_val + 0xd0) = fiber;
        // phx::Fiber::switch_to_fiber
        extern void phx__Fiber__switch_to_fiber(void*);
        phx__Fiber__switch_to_fiber(fiber);

        // After fiber returns
        *(u64*)(tls_val + 0xc8) = 0;
        *(u64*)(tls_val + 0xd0) = 0;
        *task_state = 0;
        *(u32*)(tls_val + 0xd8) = 0xffffffff;
        return;
    }

    // Fiber already exists — reset state and switch
    *task_state = 0;
    *(u64*)(tls_val + 0xc8) = 0;
    *(u64*)(tls_val + 0xd0) = 0;
    *(u32*)(tls_val + 0xd8) = 0xffffffff;

    void* fiber = FUN_7103549f00(tls_val);
    *(void**)(tls_val + 0xd0) = fiber;
    extern void phx__Fiber__switch_to_fiber(void*);
    phx__Fiber__switch_to_fiber(fiber);
}

// ============================================================================
// FUN_710354cc80 — task_queue_destructor
// Destroys a task queue object: sets vtable, destroys recursive_mutex at +0x38,
// releases shared_ptrs in the completion callback vector at +0x20..+0x28,
// then unlinks all nodes from the doubly-linked list at +0x08..+0x18 and frees them.
// [derived: param_1 = TaskQueue* (vtable-bearing object)]
// [derived: +0x00 = vtable (set to PTR_FUN_710522ed28 for destructor)]
// [derived: +0x08..+0x10 = doubly-linked list (head/tail sentinel)]
// [derived: +0x18 = list count, +0x20..+0x28 = shared_ptr vector]
// [derived: +0x38 = std::recursive_mutex (56 bytes)]
// [derived: ExclusiveMonitorPass = atomic decrement for shared_ptr ref_count]
// Address: 0x710354cc80 (400 bytes)
// ============================================================================
// PLT stub for std::__1::__shared_weak_count::__release_weak
extern "C" void _ZNSt3__119__shared_weak_count14__release_weakEv(void*);
// PLT stub for std::__1::recursive_mutex::~recursive_mutex
extern "C" void _ZNSt3__115recursive_mutexD1Ev(void*);

void FUN_710354cc80(u64* param_1) {
    *param_1 = (u64)&PTR_FUN_710522ed28;

    // Destroy recursive_mutex at +0x38 (param_1+7)
    _ZNSt3__115recursive_mutexD1Ev(param_1 + 7);

    // Release shared_ptrs in the vector at +0x20 (start) / +0x28 (end)
    long vec_start = (long)param_1[4];
    if (vec_start != 0) {
        long vec_end = (long)param_1[5];
        if (vec_end == vec_start) {
            param_1[5] = (u64)vec_start;
            vec_end = vec_start;
        } else {
            do {
                long* ctrl_block = *(long**)(vec_end - 0x10);
                vec_end -= 0x18;
                if (ctrl_block != nullptr) {
                    // Atomic decrement of shared ref count (ldaxr/stlxr pattern)
                    long old_val = __atomic_fetch_sub(ctrl_block + 1, (long)1, __ATOMIC_ACQ_REL);
                    if (old_val == 0) {
                        (*(void(**)(long*))(*(long*)ctrl_block + 0x10))(ctrl_block);
                        _ZNSt3__119__shared_weak_count14__release_weakEv(ctrl_block);
                    }
                }
            } while (vec_end != vec_start);

            param_1[5] = (u64)vec_start;
        }

        long alloc = (long)param_1[4];
        if (alloc != 0) {
            jeFree_710392e590((void*)alloc);
        }
    }

    // Unlink and free doubly-linked list nodes
    if (param_1[3] != 0) {
        long head = (long)param_1[1];
        long* tail = (long*)param_1[2];
        long* sentinel = (long*)(param_1 + 1);

        // Unlink: tail->prev->next = head->next; head->next->prev = tail->prev
        *(u64*)(*tail + 8) = *(u64*)(head + 8);
        **(long**)(head + 8) = *tail;
        param_1[3] = 0;

        // Walk and free nodes
        long* node = tail;
        while (node != sentinel) {
            long* next = (long*)node[1];
            long* ctrl = (long*)node[3];
            if (ctrl != nullptr) {
                long old_val = __atomic_fetch_sub(ctrl + 1, (long)1, __ATOMIC_ACQ_REL);
                if (old_val == 0) {
                    (*(void(**)(long*))(*(long*)ctrl + 0x10))(ctrl);
                    _ZNSt3__119__shared_weak_count14__release_weakEv(ctrl);
                }
            }
            if (node != nullptr) {
                jeFree_710392e590(node);
            }
            node = next;
        }
    }
}

// ============================================================================
// FUN_710354ce10 — merge_sort_linked_list
// Performs merge sort on a doubly-linked list. Each node has:
// [0] = next, [1] = prev, [2] = data_ptr. Comparison is done via a vtable
// call at data_ptr's vtable offset 0x2a8 (returns a priority byte).
// Stable sort, O(n log n).
// [derived: nodes are doubly-linked, [0]=next, [1]=prev, [2]=data_ptr]
// [derived: comparison: (*(code **)(*(long *)node[2] + 0x2a8))() returns u8 priority]
// [derived: param_1 = list head, param_2 = list sentinel/end, param_3 = count]
// Address: 0x710354ce10 (704 bytes)
// ============================================================================
long* FUN_710354ce10(long* param_1, long* param_2, u64 param_3) {
    if (param_3 <= 1) {
        return param_1;
    }

    if (param_3 == 2) {
        // Base case: sort 2 elements
        long* second = (long*)*param_2;
        // Compare second vs first
        u8 pri_second = (*(u8(**)())(*(long*)second[2] + 0x2a8))();
        u8 pri_first = (*(u8(**)())(*(long*)param_1[2] + 0x2a8))();
        if (pri_second < pri_first) {
            // Swap: unlink second, insert before first
            *(long*)(*second + 8) = second[1];
            *(long*)second[1] = *second;
            *(long**)(*param_1 + 8) = (long*)second;
            *second = *param_1;
            *param_1 = (long)second;
            second[1] = (long)param_1;
            param_1 = second;
        }
        return param_1;
    }

    // Recursive case: split, sort halves, merge
    u64 half = param_3 >> 1;

    // Find midpoint
    long* mid = param_1;
    if (half != 0) {
        long count = half + 1;
        do {
            mid = (long*)mid[1];
            count--;
        } while (count > 1);
        param_1 = FUN_710354ce10(param_1, mid, half);
    }

    // Sort second half
    long* right = FUN_710354ce10(mid, param_2, param_3 - half);

    // Merge the two sorted halves
    u8 pri_right = (*(u8(**)())(*(long*)right[2] + 0x2a8))();
    u8 pri_left = (*(u8(**)())(*(long*)param_1[2] + 0x2a8))();

    long* left_next;
    long* right_scan;
    long* splice_end;
    long* result;

    if (pri_right < pri_left) {
        // Right head is smaller — find run of elements from right that are smaller
        long* scan;
        for (scan = (long*)right[1]; scan != param_2; scan = (long*)scan[1]) {
            u8 ps = (*(u8(**)())(*(long*)scan[2] + 0x2a8))();
            u8 pl = (*(u8(**)())(*(long*)param_1[2] + 0x2a8))();
            if (pl <= ps) break;
        }
        splice_end = (scan != param_2) ? scan : param_2;

        // Splice the run from right into before left
        long last = *splice_end;
        *(u64*)(*right + 8) = *(u64*)(last + 8);
        **(long**)(last + 8) = *right;

        left_next = (long*)param_1[1];
        *(long**)(*param_1 + 8) = right;
        *right = *param_1;
        *param_1 = last;
        *(long**)(last + 8) = param_1;

        right_scan = scan;
        result = right;

        if (splice_end == left_next) {
            return right;
        }
    } else {
        left_next = (long*)param_1[1];
        right_scan = right;
        splice_end = right;
        result = param_1;

        if (right == left_next) {
            return param_1;
        }
    }

    // Continue merging remaining elements
    do {
        if (right_scan == param_2) {
            return result;
        }

        u8 pr = (*(u8(**)())(*(long*)right_scan[2] + 0x2a8))();
        u8 pl = (*(u8(**)())(*(long*)left_next[2] + 0x2a8))();

        if (pr < pl) {
            // Find run from right
            long* scan;
            for (scan = (long*)right_scan[1]; scan != param_2; scan = (long*)scan[1]) {
                u8 ps = (*(u8(**)())(*(long*)scan[2] + 0x2a8))();
                u8 pln = (*(u8(**)())(*(long*)left_next[2] + 0x2a8))();
                if (pln <= ps) break;
            }
            long* run_end = (scan != param_2) ? scan : param_2;

            long* new_splice;
            if (splice_end != right_scan) {
                new_splice = (long*)((long)splice_end);  // keep old
            } else {
                new_splice = scan;  // update
            }

            // Splice run from right before left_next
            long last2 = *run_end;
            *(u64*)(*right_scan + 8) = *(u64*)(last2 + 8);
            **(long**)(last2 + 8) = *right_scan;

            long* left_after = (long*)left_next[1];
            *(long**)(*left_next + 8) = right_scan;
            *right_scan = *left_next;
            *left_next = last2;
            *(long**)(last2 + 8) = left_next;

            right_scan = scan;
            left_next = left_after;
            splice_end = new_splice;
        } else {
            left_next = (long*)left_next[1];
        }
    } while (left_next != splice_end);

    return result;
}
