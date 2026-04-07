// res_remaining_large.cpp — Large remaining resource service functions
// Pool-c assignment: functions >928B in resource loading/scheduling

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// PLT stubs
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// Allocator and helpers
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free
extern "C" void* memcpy(void*, const void*, u64);

// Globals
// [derived: DAT_7105331f20 — global FilesystemInfo*]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;
// [derived: DAT_7105331f28 — global ResServiceNX*, used for region/language idx]
__attribute__((visibility("hidden"))) extern ResServiceNX* DAT_7105331f28;
// [derived: DAT_7105331f00 — OOM handler singleton, vtable dispatch at +0x30]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// Forward declarations for functions in this file — order matters for codegen
int FUN_71035461f0(ResServiceNX* service, LoadedDirectory* dir, u32 priority, u32 flags);
void FUN_7103546000(ResServiceNX* service, u32 filepath_index, u32 priority);

// Forward declarations for external functions
extern "C" s32 FUN_7103542ad0(LoadedDirectory* dir);  // get_redirected_dir_loading_state_recursive
extern "C" void FUN_7103542f30(u32* version_out);     // resolve_arc_version
extern "C" void* FUN_7103546d90(void* task_dispatch);  // alloc_list_node_from_pool

// ============================================================================
// FUN_7103546180 — load_directory_tree_recursive
// Calls FUN_71035461f0 on the given directory, then recursively processes
// all child directories via child_folders vector.
// [derived: entry point for recursive directory tree loading]
// [derived: iterates child_folders CppVector<LoadedDirectory*> at +0x28]
// Address: 0x7103546180 (112 bytes)
// NOTE: Placed before FUN_71035461f0 to prevent interprocedural optimization
// ============================================================================
int FUN_7103546180(ResServiceNX* service, LoadedDirectory* dir, u32 priority, u32 flags) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    flags &= 1;
    int count = FUN_71035461f0(service, dir, priority, flags);

    LoadedDirectory** child = dir->child_folders.start;
    LoadedDirectory** child_end = dir->child_folders.end;
    while (child != child_end) {
        int child_count = FUN_7103546180(service, *child, priority, 0);
        count += child_count;
        child++;
    }

    return count;
}

// ============================================================================
// FUN_7103546000 — enqueue_single_filepath_load
// Checks if a single filepath needs loading, and if so enqueues it into the
// appropriate priority res_list. Updates LoadedData state and flags.
// [derived: called from FUN_71035461f0 for each filepath that needs loading]
// [derived: param_1 = ResServiceNX*, param_2 = filepath_index, param_3 = priority]
// Address: 0x7103546000 (496 bytes)
// ============================================================================
void FUN_7103546000(long param_1, u32 param_2, u32 param_3) {
    if (param_2 == 0xffffff) {
        return;
    }

    long lVar7 = *(long *)(param_1 + 0xd0);
    // [derived: FilesystemInfo.mutex at +0x00, saved in local for lock/unlock pair]
    void* mtx = *(void**)lVar7;
    lock_71039c1490(mtx);

    u32* puVar1;
    long* plVar8;
    bool bVar4;
    if ((param_2 < *(u32 *)(lVar7 + 0x18)) &&
        (puVar1 = (u32 *)(*(long *)(lVar7 + 8) + (u64)param_2 * 8),
         (char)puVar1[1] != '\0')) {
        u32 uVar3 = *puVar1;
        if (*(char *)(*(long *)(lVar7 + 0x10) + (u64)uVar3 * 0x18 + 0xc) != '\0') {
            plVar8 = nullptr;
            if (uVar3 != 0xffffff) {
                plVar8 = (long *)(*(long *)(lVar7 + 0x10) + (u64)uVar3 * 0x18);
            }
            bVar4 = puVar1 == nullptr;
            goto LAB_done;
        }
    }
    plVar8 = nullptr;
    bVar4 = true;

LAB_done:
    unlock_71039c14a0(mtx);

    if (bVar4 || plVar8 == nullptr || *plVar8 != 0) {
        return;
    }

    // [derived: LoadedData.state at +0x0D, flags at +0x0F]
    char cVar7 = *(char *)((long)plVar8 + 0xd);
    if (cVar7 != '\0' &&
        !(cVar7 == '\x01' && (s32)param_3 < (s32)(u32)(*(u8 *)((long)plVar8 + 0xf) & 7))) {
        return;
    }

    // [derived: ResServiceNX+0xE0 = unk4 state flag]
    if (*(s32 *)(param_1 + 0xe0) != 2) {
        *(u32 *)(param_1 + 0xe0) = 1;
    }

    if (cVar7 == '\0') {
        *(u32 *)((long)plVar8 + 0xd) = 1;
    }

    // [derived: FUN_7103546d90 allocates a ListNode from task_dispatch pool at +0x50]
    long* plVar5 = (long *)FUN_7103546d90(*(void**)(param_1 + 0x50));
    *plVar5 = 0;
    plVar5[1] = 0;
    plVar5[2] = 0xffffff00000001LL;
    plVar5[3] = 0xffffff;

    long lVar9 = param_1 + (u64)param_3 * 0x18;

    // [derived: LoadedData.flags bits 0-2 = priority]
    *(u8 *)((long)plVar8 + 0xf) = (*(u8 *)((long)plVar8 + 0xf) & 0xf8) | ((u8)param_3 & 7);

    // [derived: ListNode+0x14 = filepath_index field]
    *(u32 *)((long)plVar5 + 0x14) = param_2;

    // Insert into doubly-linked list at res_lists[priority]
    // [derived: +0x60 = list head sentinel, +0x68 = tail ptr, +0x58 = size]
    long* puVar6 = *(long **)(lVar9 + 0x68);
    *plVar5 = lVar9 + 0x60;
    plVar5[1] = (long)puVar6;
    *(long **)(lVar9 + 0x68) = plVar5;
    *puVar6 = (long)plVar5;
    *(long *)(lVar9 + 0x58) = *(long *)(lVar9 + 0x58) + 1;

    *(u8 *)(param_1 + 0xe7) = 1;
    *(u8 *)(param_1 + 0xe4) = 1;
}

// ============================================================================
// FUN_71035461f0 — load_directory_files
// Iterates through a directory's child filepath indices, checks each file's
// loading state, and enqueues files that need loading. Handles regional/
// language file resolution via LoadedArc extra entries.
// [derived: called from FUN_7103546180 for each directory in the tree]
// [derived: param_1 = ResServiceNX*, param_2 = LoadedDirectory*]
// [derived: param_3 = priority (0-4, indexes into res_lists)]
// [derived: param_4 = flags (bit 0: skip enqueue, just count)]
// Address: 0x71035461f0 (1,472 bytes)
// ============================================================================
int FUN_71035461f0(ResServiceNX* service, LoadedDirectory* dir, u32 priority, u32 flags) {
    if (dir->file_group_index == 0xffffff) {
        return 0;
    }

    // [derived: +0x0A in LoadedDirectory is a request counter/flag (pad[0] in struct)]
    // [derived: +0x0B is current priority level (pad[1] in struct)]
    u8* request_flag = (u8*)((u8*)dir + 0x0A);
    u8* current_priority = (u8*)((u8*)dir + 0x0B);

    // Check if processing is needed:
    // - not yet requested (*request_flag == 0)
    // - state < 1 (unused/unloaded)
    // - new priority is higher (lower number) than current
    // - state is not in {1, 2, 3} (loaded states)
    bool should_process = false;
    if (*request_flag == 0 || dir->file_group_index == 0xffffff) {
        should_process = true;
    } else {
        s32 state = FUN_7103542ad0(dir);
        if (state < 1) {
            should_process = true;
        } else if ((s32)priority < (s32)(u32)*current_priority) {
            should_process = true;
        } else if (dir->file_group_index == 0xffffff) {
            should_process = true;
        } else {
            state = FUN_7103542ad0(dir);
            if (state != 3) {
                if (dir->file_group_index == 0xffffff) {
                    should_process = true;
                } else {
                    state = FUN_7103542ad0(dir);
                    if (state != 1) {
                        if (dir->file_group_index == 0xffffff) {
                            should_process = true;
                        } else {
                            state = FUN_7103542ad0(dir);
                            if (state != 2) {
                                should_process = true;
                            }
                        }
                    }
                }
            }
        }
    }

    if (!should_process) {
        return 0;
    }

    // Count files that need loading
    int load_count = 0;
    u32* child_start = dir->child_path_indices.start;
    u32* child_end = dir->child_path_indices.end;

    if (child_start != child_end) {
        u32 file_group_idx = dir->file_group_index;
        u64 fg_idx64 = (u64)file_group_idx;
        int file_offset = 0;

        do {
            FilesystemInfo* fs = service->filesystem_info;
            u32 filepath_idx = *child_start;
            lock_71039c1490(fs->mutex);

            LoadedFilepath* fp = nullptr;
            LoadedData* data = nullptr;

            if (filepath_idx == 0xffffff || fs->loaded_filepath_count <= filepath_idx ||
                (fp = &fs->loaded_filepaths[filepath_idx], fp->is_loaded == 0)) {
                fp = nullptr;
                data = nullptr;
            } else {
                u32 data_idx = fp->loaded_data_index;
                if (*(u8*)((u8*)fs->loaded_datas + (u64)data_idx * 0x18 + 0xc) == 0) {
                    fp = nullptr;
                    data = nullptr;
                } else {
                    data = nullptr;
                    if (data_idx != 0xffffff) {
                        data = (LoadedData*)((u8*)fs->loaded_datas + (u64)data_idx * 0x18);
                    }
                }
            }

            unlock_71039c14a0(fs->mutex);

            if (fp != nullptr && data != nullptr && data->data == nullptr) {
                // File data not loaded yet — check if it needs regional resolution
                // [derived: path_info->arc gives the LoadedArc]
                LoadedArc* arc = *(LoadedArc**)service->filesystem_info->path_info;
                u32 folder_count = arc->fs_header->folder_count;
                int* fi_start_ptr;
                bool do_enqueue = false;

                if (file_group_idx < folder_count) {
                    // Standard directory: use dir_infos
                    u32 fi_idx = (u32)(arc->dir_infos[fg_idx64].file_info_start_index + file_offset);

                    // [derived: FileInfo.flags bit 20: is_regional flag]
                    u8 fi_flags_byte = *(u8*)((u8*)&arc->file_infos[fi_idx] + 0x0e);
                    if ((fi_flags_byte >> 4) & 1) {
                        // Regional — check if already resolved
                        // [derived: FileInfoToFileData via file_info_indices chain]
                        u32 fii_idx = arc->file_infos[fi_idx].file_info_indice_index;
                        u32 resolved_fi = arc->file_info_indices[fii_idx].file_info_index & 0xffffff;
                        u8 resolved_flags = *(u8*)((u8*)&arc->file_info_to_datas[resolved_fi] + 0x0b);
                        if ((resolved_flags >> 3) & 1) {
                            do_enqueue = true;
                            goto enqueue_or_count;
                        }
                    }
                    fi_start_ptr = (int*)&arc->dir_infos[fg_idx64].file_info_start_index;
                } else {
                    // Extended directory: use folder_offsets
                    fi_start_ptr = (int*)&arc->folder_offsets[fg_idx64].file_start_index;
                }

                // Common file data lookup path
                {
                    u32 fi_idx2 = (u32)(*fi_start_ptr + file_offset);

                    // Resolve through file_info -> file_info_indices -> file_info chain
                    u32 fii = arc->file_infos[fi_idx2].file_info_indice_index;
                    u32 resolved_fi = arc->file_info_indices[fii].file_info_index & 0xffffff;
                    FileInfo* resolved_info = &arc->file_infos[resolved_fi];

                    u32 info_to_data_idx = resolved_info->info_to_data_index;
                    u32 region_type = (resolved_info->flags >> 15) & 3;

                    if (region_type == 2) {
                        s32 ridx = (s32)DAT_7105331f28->region_idx;
                        s32 offset = (ridx != -1) ? ridx : 0;
                        info_to_data_idx += offset + 1;
                    } else if (region_type == 1) {
                        s32 lidx = (s32)DAT_7105331f28->language_idx;
                        s32 offset = (lidx != -1) ? lidx : 0;
                        info_to_data_idx += offset + 1;
                    }

                    // [derived: FileInfoToFileData flags byte at +0xB, bit 4]
                    u8 fitfd_flags = *(u8*)((u8*)&arc->file_info_to_datas[info_to_data_idx] + 0x0b);
                    if ((fitfd_flags >> 4) & 1) {
                        do_enqueue = true;
                        goto enqueue_or_count;
                    }

                    // Get file path hash for extra entry lookup
                    if (file_group_idx < folder_count) {
                        fi_start_ptr = (int*)&arc->dir_infos[fg_idx64].file_info_start_index;
                    } else {
                        fi_start_ptr = (int*)&arc->folder_offsets[fg_idx64].file_start_index;
                    }
                    u32 file_info_idx = (u32)(*(u32*)(arc->file_infos +
                                       (u64)(u32)(*(u32*)((u8*)arc->file_info_indices +
                                       (u64)*(u32*)((u8*)arc->file_infos + (u64)(u32)(*fi_start_ptr + file_offset) * 0x10 + 4) * 8 + 4)
                                       & 0xffffff)));
                    u64 path_hash;
                    if (file_info_idx == 0xffffff || file_info_idx >= arc->fs_header->file_info_path_count) {
                        path_hash = 0;
                    } else {
                        path_hash = arc->file_paths[file_info_idx].path.raw & 0xFFFFFFFFFFULL;
                    }

                    // Check extra/regional entries
                    u64 extra_vec_start = arc->extra_entries;
                    if (extra_vec_start != 0) {
                        u32 arc_version = arc->version;
                        if (arc_version != 0xffff) {
                            u32 resolved_version = arc->fs_header->version & 0xffffff;
                            FUN_7103542f30(&resolved_version);

                            if ((s32)arc_version != (s32)resolved_version) {
                                u32 extra_count = arc->extra_count;
                                if (extra_count < *(u32*)((u8*)arc->extra_buckets + 4)) {
                                    // Binary search through extra entries
                                    u64 extra_base = *(u64*)(extra_vec_start + (u64)extra_count * 0x30 + 8);
                                    u32 bucket_count = *(u32*)extra_base;
                                    u64 hash_div = 0;
                                    if (bucket_count != 0) {
                                        hash_div = path_hash / (u64)bucket_count;
                                    }
                                    u64 bucket_idx = path_hash - hash_div * (u64)bucket_count;

                                    u64 search_count = (u64)*(u32*)((u8*)extra_base + bucket_idx * 8 + 0xC);
                                    u64* search_start = (u64*)(*(u64*)(extra_vec_start + (u64)extra_count * 0x30 + 0x10) +
                                                       (u64)*(u32*)((u8*)extra_base + bucket_idx * 8 + 8) * 8);
                                    u64* found = search_start;

                                    if (search_count != 0) {
                                        do {
                                            u64 cnt = search_count;
                                            if ((s64)search_count < 0) {
                                                cnt = search_count + 1;
                                            }
                                            u64 half = (s64)cnt >> 1;
                                            u64* mid = found + half + 1;
                                            u64 rem = search_count + ~half;
                                            if (path_hash <= (found[half] & 0xFFFFFFFFFFULL)) {
                                                mid = found;
                                                rem = half;
                                            }
                                            found = mid;
                                            search_count = rem;
                                        } while (search_count != 0);
                                    }

                                    if (found != nullptr && (*found & 0xFFFFFFFFFFULL) == path_hash) {
                                        u64 extra_data_base = *(u64*)(extra_vec_start + (u64)extra_count * 0x30);
                                        u64 extra_data_ptr = extra_data_base + (*found >> 40) * 0x14;
                                        if (extra_data_ptr != 0) {
                                            do_enqueue = true;
                                            goto enqueue_or_count;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Set LoadedData state if unused
                    // [derived: 4-byte write at +0x0D sets state=1, file_flags2=0, flags=0, version_byte0=0]
                    if (data->state == 0) {
                        data->state = 1;
                        data->file_flags2 = 0;
                        data->flags = 0;
                        *(u8*)((u8*)data + 0x10) = 0;
                    }
                    // [derived: LoadedData.flags bits 3-5 = priority]
                    data->flags = (data->flags & 0xc7) | (u8)((priority & 7) << 3);
                }

            enqueue_or_count:
                if (do_enqueue) {
                    FUN_7103546000(service, filepath_idx, priority);
                }
                load_count++;
            }

        next_child:
            child_start++;
            file_offset++;
        } while (child_start != child_end);
    }

    // Recursively process redirection directory
    LoadedDirectory* redir = dir->redirection_directory;
    if (redir != nullptr && redir->file_group_index != 0xffffff) {
        int redir_count = FUN_7103546180(service, redir, priority, 1);
        load_count += redir_count;
    }

    // Enqueue directory load request
    if (load_count != 0 || dir->file_group_index == 0xffffff ||
        FUN_7103542ad0(dir) != 3) {
        // Set unk4 to 1 if not already 2
        if (service->unk4 != 2) {
            service->unk4 = 1;
        }

        // Set state to 1 if not yet loaded
        if (dir->file_group_index == 0xffffff || FUN_7103542ad0(dir) < 1) {
            // [derived: 4-byte write at +0x09 sets state=1, pad bytes=0]
            *(u32*)(&dir->state) = 1;
        }

        // Atomically increment request counter at +0x0A
        // [derived: ldxr/stxr loop on byte at LoadedDirectory+0x0A]
        __atomic_fetch_add(request_flag, 1, __ATOMIC_RELAXED);

        // Store priority
        *current_priority = (u8)priority;

        if ((flags & 1) != 0) {
            return load_count;
        }

        // Allocate ListNode and enqueue to res_lists[priority]
        ListNode* node = (ListNode*)FUN_7103546d90(service->task_dispatch);
        node->next = nullptr;
        node->prev = nullptr;
        *(u64*)(&node->data) = 0xffffff00000000ULL;
        node->data.directory_index = 0xffffff;

        // [derived: ListNode.data at +0x18 = directory file_group_index]
        node->data.ty = dir->file_group_index;
        node->data.files_to_load = load_count;

        ResList* list = &service->res_lists[priority];
        ListNode* tail = list->end;
        node->next = (ListNode*)(&list->next);  // sentinel: points to list head
        node->prev = tail;
        list->end = node;
        *(ListNode**)tail = node;
        list->size += 1;

        service->unk5 = 1;
        *(u8*)((u8*)service + 0xe4) = 1;
        return load_count;
    }

    return 0;
}

// ============================================================================
// Remaining targets analysis:
// - FUN_710353c5b0 (1504B): phx::Fiber::setup — libc++ std::function SBO machinery
// - FUN_710354fb70 (928B): std::__hash_table::rehash — libc++ template instantiation
// - FUN_710354f470 (1168B): std::__tree::__emplace_unique — libc++ template instantiation
// - FUN_7103549f00 (2272B): fiber pool pop/create — 80% is std::function SBO wrapping
// - FUN_710354a7e0 (2960B): std::deque<void*>::push_back — libc++ template
// - FUN_710354bb90 (2960B): std::deque<void*>::push_front — libc++ template
// - FUN_710354e4e0 (3360B): complex game update w/ unordered_map + vector + strings
//
// These are either libc++ template instantiations or deeply intertwined with
// std::function/std::deque/std::unordered_map internal machinery that cannot
// be byte-matched without reproducing the exact NintendoSDK libc++ headers.
// ============================================================================

