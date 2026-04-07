// ResLoadingThread.cpp — The critical-path resource loading/processing loop
// Address: 0x7103542f30, Size: 12,496 bytes
// [derived: Ghidra 13.0.1 decompilation of ResLoadingThread]
// This is the main loop for ResLoadingThread — processes file/directory load requests
// from 5 request queues in ResServiceNX. All 6 ARCropolis hooks in the loading
// pipeline land in this function.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// PLT stubs
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// nn::os PLT stubs
// [derived: PLT entries referenced from ResLoadingThread disassembly]
extern "C" void FUN_71039c0710(void*);  // FUN_71039c0710(EventType*)
extern "C" void FUN_71039c0720(void*);  // FUN_71039c0720(EventType*)
extern "C" void FUN_71039c0740(void*);  // FUN_71039c0740(SemaphoreType*)
extern "C" void FUN_71039c0750(void*);  // FUN_71039c0750(SemaphoreType*)
extern "C" void FUN_71039c07c0(u64);    // nn::os::SleepThread(TimeSpan)
// nn::fs PLT stub
extern "C" void FUN_71039c7680(s64*, u64);  // nn::fs::GetFileSize(long*, FileHandle)

// Memory
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free
extern "C" void* memcpy(void*, const void*, u64);
extern "C" void* memmove(void*, const void*, u64);

// Error handlers
extern "C" [[noreturn]] void __throw_length_error(void*);
extern "C" [[noreturn]] void abort();

// Resource service subfunctions
// [derived: version lookup for file path hash — returns version number, 0xffff if not found]
extern "C" s32 FUN_7103540960(LoadedArc* arc, u64 hash40);
// [derived: transforms raw version to canonical form — modifies in place]
extern "C" void FUN_710353b050(s32* version);
// [derived: reads data from FileNX into buffer, returns bytes actually read]
extern "C" u64 FUN_71037c58c0(FileNX* file, void* buffer, u64 size);
// [derived: directory loading dispatch — returns success flag in bit 0]
extern "C" u64 FUN_7103544ca0(ResServiceNX* svc, FileNX** file, u32 dir_idx, u32 mode, u32 extra);
// [derived: recursive directory loading state check — returns min state in chain]
s32 FUN_7103542ad0(LoadedDirectory* dir);
// [derived: reset/update loaded directory state]
extern "C" void FUN_7103541e30(LoadedDirectory* dir);

// Globals
__attribute__((visibility("hidden"))) extern ResServiceNX* DAT_7105331f28;
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// ============================================================================
// Helper: vector push_back with OOM retry (inlined by compiler 3 times)
// Pushes a u32 to a { start, end, cap } triple with growth.
// ============================================================================
static inline void vec_push_u32(u32** start, u32** end, u32** cap, u32 value) {
    if (*end != *cap) {
        **end = value;
        *end = *end + 1;
        return;
    }
    u32* old_start = *start;
    u64 old_bytes = (u64)((u8*)*end - (u8*)old_start);
    u64 new_count = (old_bytes >> 2) + 1;
    if (new_count >> 62 != 0) {
        __throw_length_error(start);
    }
    u64 old_cap_bytes = (u64)((u8*)*cap - (u8*)old_start);
    u64 new_cap;
    u32* new_buf;

    if ((old_cap_bytes >> 2) >= 0x1fffffffffffffffULL) {
        new_cap = 0x3fffffffffffffffULL;
    } else {
        u64 half_cap = old_cap_bytes >> 1;
        new_cap = (new_count <= half_cap) ? half_cap : new_count;
        if (new_cap == 0) {
            new_buf = nullptr;
            goto insert;
        }
    }
    {
        if (new_cap >> 62 != 0) abort();
        u64 alloc_size = new_cap * 4;
        if (alloc_size == 0) alloc_size = 1;
        new_buf = (u32*)je_aligned_alloc(0x10, alloc_size);
        if (new_buf == nullptr) {
            if (DAT_7105331f00 != nullptr) {
                u32 oom_flags = 0;
                s64 oom_size = (s64)alloc_size;
                u64 r = ((u64(*)(s64*, u32*, s64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                         (DAT_7105331f00, &oom_flags, &oom_size);
                if (((r & 1) != 0) &&
                    (new_buf = (u32*)je_aligned_alloc(0x10, alloc_size), new_buf != nullptr))
                    goto insert;
            }
            new_buf = nullptr;
        }
    }
insert:
    {
        u32* ins = new_buf + (old_bytes >> 2);
        *ins = value;
        if ((s64)old_bytes > 0) {
            memcpy(new_buf, old_start, old_bytes);
        }
        *start = new_buf;
        *end = ins + 1;
        *cap = (u32*)((u8*)new_buf + new_cap * 4);
        if (old_start != nullptr) {
            FUN_710392e590(old_start);
        }
    }
}

// ============================================================================
// ResLoadingThread — main loading thread entry point
// Address: 0x7103542f30
// ============================================================================
void ResLoadingThread(ResServiceNX* service) {
    if (service->is_loader_thread_running) return;

    do {
        // ================================================================
        // Wait for update event (unless already in processing state)
        // [derived: unk_event2 at +0x020 is EventType** wrapper]
        // ================================================================
        if (service->state != 2) {
            void* event = *(void**)service->unk_event2;
            if (event != nullptr) {
                FUN_71039c0710(event);
            }
        }
        if (service->is_loader_thread_running) return;

        // ================================================================
        // Lock mutex, set processing state, drain 5 request queues
        // ================================================================
        lock_71039c1490(service->mutex);
        s32 total_items = 0;
        service->state = 2;

        // Initialize 5 local lists as empty sentinel-based doubly-linked lists
        // Layout: [size(u64), next(ListNode*), end(ListNode*)] per list
        // Sentinel = (ListNode*)&list.next — when empty, next and end both point to sentinel
        ResList local_lists[5];
        for (int i = 0; i < 5; i++) {
            local_lists[i].size = 0;
            ListNode* sentinel = (ListNode*)&local_lists[i].next;
            local_lists[i].next = sentinel;
            local_lists[i].end = sentinel;
        }

        // Swap each service queue into corresponding local list, accumulate counts
        // [derived: res_lists at +0x058, 5 queues of 0x18 bytes each]
        for (u64 qi = 0; qi < 5; qi++) {
            ResList* svc = &service->res_lists[qi];
            ResList* local = &local_lists[qi];
            ListNode* svc_sentinel = (ListNode*)&svc->next;
            ListNode* local_sentinel = (ListNode*)&local->next;
            s32 count = (s32)svc->size;

            // Swap linked list pointers (handles both-empty, one-empty, both-populated)
            ListNode* local_head = local->next;
            ListNode* svc_head = svc->next;

            if (local_head == nullptr) {
                local->next = local_sentinel;
                local->end = local_sentinel;
                if (svc_head != nullptr) {
                    // Service has nodes, local is null → transfer
                    ListNode* local_tail = local->end;
                    ListNode* svc_tail = svc->end;
                    local_head->prev = (ListNode*)svc_tail->prev;
                    svc_tail->prev = (ListNode*)local_head->prev;
                    // ... (simplified — full swap is complex)
                }
                svc->next = svc_sentinel;
                svc->end = svc_sentinel;
            } else if (svc_head == nullptr) {
                svc->next = svc_sentinel;
                svc->end = svc_sentinel;
                ListNode* local_tail = local->end;
                ListNode* svc_tail = svc->end;
                local_head->prev = (ListNode*)svc_tail->prev;
                svc_tail->prev = (ListNode*)local_head->prev;
            } else {
                // Both non-null: full swap
                ListNode* local_tail = local->end;
                ListNode* svc_tail = svc->end;

                // Swap last->next and first->prev links
                ListNode* tmp1 = (ListNode*)local_head->prev;
                ListNode* tmp2 = local->end;
                local_head->prev = (ListNode*)svc_tail->prev;
                svc_tail->prev = (ListNode*)tmp1;

                ListNode* tmp3 = *(ListNode**)tmp2;
                *(ListNode**)tmp2 = *(ListNode**)svc_tail;
                *(ListNode**)svc_tail = tmp3;

                ListNode* tmp4 = local->next;
                local->next = svc->next;
                svc->next = tmp4;

                ListNode* tmp5 = local->end;
                local->end = svc->end;
                svc->end = tmp5;

                if (local_head == nullptr) {
                    svc->next = nullptr;
                    svc->end = nullptr;
                }
                if (svc_head == nullptr) {
                    local->next = nullptr;
                    local->end = nullptr;
                }
            }

            // Swap sizes
            u64 old_local_size = local->size;
            local->size = svc->size;
            svc->size = old_local_size;

            // Clear any remaining nodes in service list
            ListNode* clear_node = svc->next;
            while (clear_node != svc_sentinel) {
                ListNode* next_clear = clear_node->next;
                clear_node->next = nullptr;
                clear_node->prev = nullptr;
                clear_node = next_clear;
            }

            total_items += count;
            svc->next = svc_sentinel;
            svc->end = svc_sentinel;
            svc->size = 0;
        }

        service->unk5 = 0;     // +0x0E7: clear re-queue flag
        service->unk4 = 0;     // +0x0E0: clear processing sub-state

        if (total_items != 0) {
            unlock_71039c14a0(service->mutex);

            // Variables for directory post-processing vector
            u64 queue_idx = 0;
            u32* dir_buf = nullptr;
            u32* dir_buf_end = nullptr;
            u32* dir_buf_cap = nullptr;

            // Variables used across sections (declared here for goto compatibility)
            FileNX** arc_file_ptr;
            u32 dir_dispatch_idx;
            u64 dir_dispatch_mode;

            goto begin_processing;

            // ==============================================================
            // RE-QUEUE: Move newly-arrived service items to local lists
            // Reached via goto when field_0xe7 is set during processing
            // [derived: code_r0x0071035435a0 in Ghidra]
            // ==============================================================
        re_queue:
            lock_71039c1490(service->mutex);

            // Re-drain each of the first 4 queues
            for (int rq = 0; rq < 4; rq++) {
                ListNode* svc_sent_rq = (ListNode*)&service->res_lists[rq].next;
                ListNode* rq_node = service->res_lists[rq].next;
                while (rq_node != svc_sent_rq) {
                    ListNode* rq_next = rq_node->next;
                    // Unlink from service
                    rq_node->next->prev = rq_node->prev;
                    rq_node->prev->next = rq_node->next;
                    service->res_lists[rq].size--;
                    // Link to local list tail
                    ListNode* local_sent_rq = (ListNode*)&local_lists[rq].next;
                    rq_node->next = local_sent_rq;
                    rq_node->prev = local_lists[rq].end;
                    local_lists[rq].end->next = rq_node;
                    local_lists[rq].end = rq_node;
                    local_lists[rq].size++;
                    rq_node = rq_next;
                }
            }
            // Re-drain queue 4 (at +0xC0)
            {
                ListNode* svc_sent_4 = (ListNode*)&service->res_lists[4].next;
                ListNode* rq_node = service->res_lists[4].next;
                while (rq_node != svc_sent_4) {
                    ListNode* rq_next = rq_node->next;
                    rq_node->next->prev = rq_node->prev;
                    rq_node->prev->next = rq_node->next;
                    service->res_lists[4].size--;
                    ListNode* local_sent_4 = (ListNode*)&local_lists[4].next;
                    rq_node->next = local_sent_4;
                    rq_node->prev = local_lists[4].end;
                    local_lists[4].end->next = rq_node;
                    local_lists[4].end = rq_node;
                    local_lists[4].size++;
                    rq_node = rq_next;
                }
            }

            service->unk5 = 0;
            service->unk4 = 0;
            unlock_71039c14a0(service->mutex);
            queue_idx = 0;

            // ==============================================================
            // MAIN PROCESSING LOOP: iterate through each queue's linked list
            // ==============================================================
        begin_processing:
            {
                ListNode* local_sentinel = (ListNode*)&local_lists[queue_idx].next;
                ListNode* node = local_lists[queue_idx].next;

                while (node != local_sentinel) {
                    if (service->is_loader_thread_running) goto cleanup;

                    if (node->data.ty == 1) {
                        // ======================================================
                        // FILE LOADING PATH
                        // [derived: LoadInfo.ty == 1 means file load request]
                        // ======================================================
                        u32 filepath_idx = node->data.filepath_index;
                        if (filepath_idx == 0xffffff) goto next_node;

                        FilesystemInfo* fs = service->filesystem_info;
                        void* fs_mtx = fs->mutex;
                        FileNX** ppFile = service->data_arc_filenx;
                        lock_71039c1490(fs_mtx);

                        // Check filepath is valid and loaded
                        if (filepath_idx >= fs->loaded_filepath_len ||
                            !fs->loaded_filepaths[filepath_idx].is_loaded) {
                            unlock_71039c14a0(fs_mtx);
                            goto next_node;
                        }

                        LoadedData* datas = fs->loaded_datas;
                        u32 data_idx = fs->loaded_filepaths[filepath_idx].loaded_data_index;
                        if (!datas[data_idx].is_used || data_idx == 0xffffff) {
                            unlock_71039c14a0(fs_mtx);
                            goto next_node;
                        }

                        unlock_71039c14a0(fs_mtx);

                        // Check if entry needs loading: state != Unused, refcount >= 1, no data yet
                        LoadedData* entry = &datas[data_idx];
                        if (entry == nullptr || entry->state == 0 ||
                            (s32)entry->ref_count < 1 || entry->data != nullptr) {
                            goto next_node;
                        }

                        // ---- ARC path resolution ----
                        fs = service->filesystem_info;
                        LoadedArc* arc = fs->loaded_data->arc;
                        FilePath* file_paths = arc->file_paths;

                        // Get version for this filepath's hash40
                        u64 path_hash = file_paths[filepath_idx].path.raw & 0xFFFFFFFFFFULL;
                        s32 version = FUN_7103540960(arc, path_hash);

                        if (version != (s32)0xffff) {
                            // Check if version matches filesystem version
                            s32 fs_ver = (s32)(arc->fs_header->version & 0x00ffffff);
                            FUN_710353b050(&fs_ver);
                            if (fs_ver == version) {
                                goto alt_path_lookup;
                            }
                        } else {
                        alt_path_lookup:
                            // Alternate: use file_info indirect path
                            u32 fii_raw_idx = (u32)(file_paths[filepath_idx].path.raw >> 40);
                            u32 fi_idx = arc->file_info_indices[fii_raw_idx].file_info_index & 0xffffff;
                            u32 alt_fp_idx = arc->file_infos[fi_idx].file_path_index;
                            arc = fs->loaded_data->arc;
                            u64 alt_hash;
                            if (alt_fp_idx == 0xffffff || alt_fp_idx >= arc->fs_header->file_info_path_count) {
                                alt_hash = 0;
                            } else {
                                alt_hash = arc->file_paths[alt_fp_idx].path.raw & 0xFFFFFFFFFFULL;
                            }
                            version = FUN_7103540960(arc, alt_hash);
                        }

                        // Store version on the LoadedData entry
                        {
                            s32 ver_buf = version;
                            FUN_710353b050(&ver_buf);
                            datas[data_idx].version = (u32)ver_buf;
                        }

                        // ---- Resolve file data location ----
                        fs = service->filesystem_info;
                        arc = fs->loaded_data->arc;
                        u32 fii_idx = (u32)(arc->file_paths[filepath_idx].path.raw >> 40);
                        FileInfo* fi = &arc->file_infos[arc->file_info_indices[fii_idx].file_info_index & 0xffffff];
                        u32 fi_fp_idx = fi->file_path_index;
                        u64 path_hash2;
                        u32 info_to_data_idx;
                        u32 folder_offset_idx;

                        if (fi_fp_idx == 0xffffff || fi_fp_idx >= arc->fs_header->file_info_path_count) {
                            path_hash2 = 0;
                            // No extra entries path
                            goto standard_file_resolve;
                        } else {
                            path_hash2 = arc->file_paths[fi_fp_idx].path.raw & 0xFFFFFFFFFFULL;
                        }

                        // Check for extra entries (DLC/updates)
                        if (arc->extra_entries == 0) {
                            goto standard_file_resolve;
                        }
                        {
                            s32 arc_ver = (s32)arc->version;
                            if (arc_ver == (s32)0xffff) goto standard_file_resolve;
                            s32 fs_ver2 = (s32)(arc->fs_header->version & 0x00ffffff);
                            FUN_710353b050(&fs_ver2);
                            if (arc_ver == fs_ver2) goto standard_file_resolve;

                            // Extra entry hash table lookup
                            u32 extra_idx = arc->extra_count;
                            u8* extra_vec_start = (u8*)arc->extra_entry_vector[0]; // CppVector.start
                            u32* buckets = *(u32**)(extra_vec_start + extra_idx * 0x20);
                            // [derived: extra entry stride = 0x20, bucket ptr at +0x00]
                            if (arc->extra_buckets->count <= extra_idx) goto standard_file_resolve;

                            u64 bucket_count = (u64)*buckets;
                            u64 slot = 0;
                            if (bucket_count != 0) {
                                slot = path_hash2 / bucket_count;
                            }
                            u64 remainder = path_hash2 - slot * bucket_count;

                            u64 search_count = (u64)buckets[remainder * 2 + 3];
                            HashToIndex* search_base = *(HashToIndex**)(extra_vec_start + extra_idx * 0x20 + 0x08)
                                                       + buckets[remainder * 2 + 2];
                            HashToIndex* found = search_base;

                            // Binary search within bucket
                            if (search_count != 0) {
                                do {
                                    u64 half = search_count;
                                    if ((s64)search_count < 0) half = search_count + 1;
                                    half >>= 1;
                                    HashToIndex* mid = found + half + 1;
                                    u64 remaining = search_count + ~half;
                                    if (path_hash2 <= (found[half].raw & 0xFFFFFFFFFFULL)) {
                                        mid = found;
                                        remaining = half;
                                    }
                                    found = mid;
                                    search_count = remaining;
                                } while (search_count != 0);
                            }

                            if (found == nullptr || (found->raw & 0xFFFFFFFFFFULL) != path_hash2) {
                                goto standard_file_resolve;
                            }

                            // Found in extra entries
                            u32 extra_data_idx = (u32)(found->raw >> 40);
                            u8* extra_info = (u8*)(*(u64*)(extra_vec_start + extra_idx * 0x20)) + extra_data_idx * 0x14;
                            if (extra_info == nullptr) goto standard_file_resolve;
                            u32 extra_fi_idx = *(u32*)(extra_info + 8);

                            info_to_data_idx = arc->file_infos[extra_fi_idx].info_to_data_index;
                            u32 region_type = (arc->file_infos[extra_fi_idx].flags >> 15) & 3;
                            if (region_type == 2) {
                                u32 ridx = DAT_7105331f28->region_idx;
                                u32 offset = (ridx != 0xffffffff) ? ridx : 0;
                                info_to_data_idx += offset + 1;
                            } else if (region_type == 1) {
                                u32 lidx = DAT_7105331f28->language_idx;
                                u32 offset = (lidx != 0xffffffff) ? lidx : 0;
                                info_to_data_idx += offset + 1;
                            }

                            FileInfoToFileData* fitfd = arc->file_info_to_datas;
                            if (fitfd[info_to_data_idx].file_data_index == 0xffffff) {
                                // Fallback to standard path
                                goto standard_file_resolve;
                            }
                            folder_offset_idx = fitfd[info_to_data_idx].folder_offset_index;
                            arc = fs->loaded_data->arc;
                            goto do_file_read;
                        }

                    standard_file_resolve:
                        {
                            info_to_data_idx = fi->info_to_data_index;
                            u32 region_type = (fi->flags >> 15) & 3;
                            if (region_type == 2) {
                                u32 ridx = DAT_7105331f28->region_idx;
                                u32 offset = (ridx != 0xffffffff) ? ridx : 0;
                                info_to_data_idx += offset + 1;
                            } else if (region_type == 1) {
                                u32 lidx = DAT_7105331f28->language_idx;
                                u32 offset = (lidx != 0xffffffff) ? lidx : 0;
                                info_to_data_idx += offset + 1;
                            }
                            LoadedDataWrapper* ldw = fs->loaded_data;
                            FileInfoToFileData* fitfd = arc->file_info_to_datas + info_to_data_idx;
                            arc = ldw->arc;
                            folder_offset_idx = fitfd->folder_offset_index;
                        }

                    do_file_read:
                        {
                            u32 raw_fii = arc->file_info_indices[fii_idx].file_info_index;
                            u32 file_data_idx = arc->file_info_to_datas[info_to_data_idx].file_data_index;
                            u32 comp_size = arc->file_datas[file_data_idx].comp_size;
                            FileNX* file = *ppFile;
                            u64 file_offset = (u64)(arc->file_datas[file_data_idx].offset_in_folder) << 2;
                            u64 buf_size = service->buffer_size;

                            // Seek: compute absolute position in archive
                            // [derived: position = folder_offset + arc->file_section_offset + file_data_offset]
                            u8 is_readable = *(u8*)((u8*)file + 0x22c);
                            if (is_readable && file->is_open) {
                                u64 abs_pos = arc->folder_offsets[folder_offset_idx].offset
                                              + service->filesystem_info->loaded_data->arc->file_section_offset
                                              + file_offset;
                                file->position = abs_pos;
                                if ((s64)abs_pos >= 0) {
                                    s64 file_size = 0;
                                    FUN_71039c7680(&file_size,
                                        *(u64*)&file->file_handle);
                                }
                            }

                            if (service->is_loader_thread_running) goto next_node;

                            // Double-buffered read loop
                            s32 iteration = 0;
                            u32 read_chunk = (u32)buf_size;
                            while (true) {
                                u32 remaining = comp_size - read_chunk;
                                u32 to_read = read_chunk;
                                if (comp_size < read_chunk || remaining == 0) {
                                    to_read = comp_size;
                                }
                                u64 read_size = (u64)to_read;

                                // Acquire I/O semaphore
                                // [derived: semaphore1 at +0x028, wrapper struct with sem at +0x08]
                                FUN_71039c0740(
                                    *(void**)(*(u64*)service->semaphore1 + 8));

                                file = *ppFile;
                                u8 still_readable = *(u8*)((u8*)file + 0x22c);
                                if (!still_readable) {
                                    // Read failed — mark error
                                    *(u8*)((u8*)service + 0x248) = 1;  // is_file_read_error
                                    *(u32*)&datas[data_idx].state = 0xffffffff;
                                    goto next_node;
                                }

                                u64 bytes_read = FUN_71037c58c0(file,
                                    service->buffer_array[(int)service->buffer_array_idx],
                                    read_size);
                                if (bytes_read != read_size) {
                                    *(u8*)((u8*)service + 0x248) = 1;
                                    *(u32*)&datas[data_idx].state = 0xffffffff;
                                    goto next_node;
                                }

                                file_offset += read_size;

                                // Acquire processing semaphore
                                FUN_71039c0740(
                                    *(void**)(*(u64*)service->semaphore2 + 8));

                                if (iteration == 0) {
                                    service->processing_file_idx_start = raw_fii & 0xffffff;
                                    service->processing_file_idx_curr = 0;
                                    service->processing_file_idx_count = 1;
                                    service->processing_type = 4;
                                    service->processing_dir_idx_start = 0xffffff;
                                    service->processing_dir_idx_single = 0xffffff;
                                    service->current_dir_index = 0xffffff;
                                }

                                service->offset_into_read = file_offset;
                                service->data_ptr = service->buffer_array[(int)service->buffer_array_idx];

                                // Signal inflate thread
                                void* swap_event = *(void**)service->io_swap_event;
                                if (swap_event != nullptr) {
                                    FUN_71039c0720(swap_event);
                                }

                                // Swap buffer index (double-buffer toggle)
                                service->buffer_array_idx = ~service->buffer_array_idx & 1;

                                if (remaining == 0 || comp_size <= read_chunk) goto next_node;
                                iteration--;
                                comp_size = remaining;
                                read_chunk = to_read;
                                if (service->is_loader_thread_running) goto next_node;
                            }
                        }
                    } else if (node->data.ty == 0) {
                        // ======================================================
                        // DIRECTORY LOADING PATH
                        // [derived: LoadInfo.ty == 0 means directory load request]
                        // ======================================================
                        u32 dir_load_idx = node->data.directory_index;
                        if (dir_load_idx != 0xffffff) {
                            FilesystemInfo* fs = service->filesystem_info;
                            if (dir_load_idx < fs->loaded_directory_len) {
                                void* fs_mtx = fs->mutex;
                                lock_71039c1490(fs_mtx);
                                LoadedDirectory* dirs = fs->loaded_directories;
                                LoadedDirectory* dir = &dirs[dir_load_idx];
                                u8 dir_flags = dir->flags;
                                unlock_71039c14a0(fs_mtx);

                                if ((dir_flags & 1) && dir != nullptr &&
                                    dir->file_group_index != 0xffffff) {
                                    s32 load_state = FUN_7103542ad0(dir);
                                    if (load_state == 1) {
                                        *(u32*)&dirs[dir_load_idx].state = 2;
                                    }
                                }
                            }
                        }

                        // Look up directory in ARC
                        LoadedArc* arc = service->filesystem_info->loaded_data->arc;
                        u64 dir_info_idx = (u64)node->data.directory_index;
                        DirInfo* dir_info = &arc->dir_infos[dir_info_idx];

                        // Check DirInfo flags (byte 3 of flags field)
                        u8* flags_ptr = (u8*)&dir_info->flags + 3;
                        u8 flags_byte = *flags_ptr;

                        if ((flags_byte & 0xb) == 0) {
                            // Normal directory (bits 24,25,27 clear)
                            if ((flags_byte & 0x4) == 0) {
                                // Bit 26 clear: simple directory
                                if (node->data.files_to_load == 0 ||
                                    (FUN_7103544ca0(service, service->data_arc_filenx,
                                        (u32)dir_info_idx, 0, (u32)dir_info_idx) & 1) != 0) {
                                    vec_push_u32(&dir_buf, &dir_buf_end, &dir_buf_cap,
                                                 node->data.directory_index);
                                }
                            } else {
                                // Bit 26 set: directory has sub-directory reference
                                if ((node->data.files_to_load != 0) &&
                                    (FUN_7103544ca0(service, service->data_arc_filenx,
                                        (u32)dir_info_idx, 0, 0xffffff) & 1) == 0) {
                                    goto next_node;
                                }
                                vec_push_u32(&dir_buf, &dir_buf_end, &dir_buf_cap,
                                             node->data.directory_index);

                                // Check if sub-dir reference is valid
                                u32 folder_dir_idx = arc->folder_offsets[
                                    (u64)(dir_info->path.raw >> 40)].directory_index;
                                if (folder_dir_idx > 0xfffffe) {
                                    arc_file_ptr = service->data_arc_filenx;
                                    dir_dispatch_idx = node->data.directory_index;
                                    dir_dispatch_mode = 1;
                                } else {
                                    arc_file_ptr = service->data_arc_filenx;
                                    dir_dispatch_idx = node->data.directory_index;

                                    // Load the referenced sub-directory
                                    u64 result = FUN_7103544ca0(service, arc_file_ptr,
                                        dir_dispatch_idx, 2, 0xffffff);
                                    if ((result & 1) == 0) goto next_node;
                                    arc_file_ptr = service->data_arc_filenx;
                                    dir_dispatch_idx = node->data.directory_index;
                                    dir_dispatch_mode = 3;
                                }
                                goto dir_dispatch;
                            }
                        } else {
                            // Special directory (some of bits 24,25,27 set)
                            if (node->data.files_to_load != 0 &&
                                (FUN_7103544ca0(service, service->data_arc_filenx,
                                    (u32)dir_info_idx, 0, 0xffffff) & 1) == 0) {
                                goto next_node;
                            }
                            vec_push_u32(&dir_buf, &dir_buf_end, &dir_buf_cap,
                                         node->data.directory_index);
                            flags_byte = *flags_ptr;

                            if ((flags_byte >> 2) & 1) {
                                FUN_7103544ca0(service, service->data_arc_filenx,
                                    node->data.directory_index, 1, 0xffffff);
                                flags_byte = *flags_ptr;
                            }

                            if ((flags_byte >> 3) & 1) {
                                // Has offset reference
                                LoadedArc* arc2 = service->filesystem_info->loaded_data->arc;
                                DirectoryOffset* dir_off;
                                if ((flags_byte & 3) == 2) {
                                    u32 ridx = DAT_7105331f28->region_idx;
                                    s32 offset = 1;
                                    if (ridx != 0xffffffff) offset = (s32)ridx + 1;
                                    dir_off = &arc2->folder_offsets[
                                        offset + (s32)(dir_info->path.raw >> 40)];
                                } else if ((flags_byte & 3) == 1) {
                                    u32 lidx = DAT_7105331f28->language_idx;
                                    s32 offset = 1;
                                    if (lidx != 0xffffffff) offset = (s32)lidx + 1;
                                    dir_off = &arc2->folder_offsets[
                                        offset + (s32)(dir_info->path.raw >> 40)];
                                } else {
                                    dir_off = &arc2->folder_offsets[
                                        (u64)(dir_info->path.raw >> 40)];
                                }

                                arc_file_ptr = service->data_arc_filenx;
                                dir_dispatch_idx = node->data.directory_index;

                                if (dir_off->directory_index != 0xffffff) {
                                    u64 result = FUN_7103544ca0(service, arc_file_ptr,
                                        dir_dispatch_idx, 2, 0xffffff);
                                    if ((result & 1) == 0) goto next_node;
                                    arc_file_ptr = service->data_arc_filenx;
                                    dir_dispatch_idx = node->data.directory_index;
                                    dir_dispatch_mode = 3;
                                    goto dir_dispatch;
                                }
                                dir_dispatch_mode = 2;
                            } else {
                                arc_file_ptr = service->data_arc_filenx;
                                dir_dispatch_idx = node->data.directory_index;
                                dir_dispatch_mode = 2;
                            }
                        dir_dispatch:
                            FUN_7103544ca0(service, arc_file_ptr,
                                dir_dispatch_idx, dir_dispatch_mode, dir_dispatch_idx);
                        }
                    }

                next_node:
                    // ======================================================
                    // Unlink processed node from local list, return to pool
                    // [derived: standard doubly-linked list remove + slab return]
                    // ======================================================
                    {
                        // Save next pointer BEFORE unlinking
                        ListNode* next_saved = node->next;
                        ListNode* prev_saved = node->prev;
                        // Unlink from list
                        next_saved->prev = prev_saved;
                        prev_saved->next = next_saved;
                        local_lists[queue_idx].size--;
                        node->next = nullptr;
                        node->prev = nullptr;

                        // Return node to pool (service->task_dispatch at +0x050)
                        lock_71039c1490(service->mutex);
                        {
                            u64* pool_obj = (u64*)service->task_dispatch;
                            u64* cur = *(u64**)(pool_obj + 2);      // vector start at +0x10
                            u64* vec_end = *(u64**)(pool_obj + 3);  // vector end at +0x18
                            if (cur != vec_end) {
                                s32 counter = 0;
                                do {
                                    u64* pool_entry = (u64*)*cur;
                                    if ((ListNode*)pool_entry[2] <= node &&
                                        node < (ListNode*)pool_entry[3]) {
                                        // Push node to pool's free list
                                        node->next = (ListNode*)pool_entry[0];
                                        pool_entry[0] = (u64)node;
                                        *(s32*)((u8*)pool_entry + 0x20) =
                                            *(s32*)((u8*)pool_entry + 0x20) + 1;

                                        // If pool is full, remove from vector and free
                                        if (counter != 0) {
                                            void* ptr = (void*)*cur;
                                            if (*(s32*)((u8*)ptr + 0x0c) ==
                                                *(s32*)((u8*)ptr + 0x20)) {
                                                u64 shift_bytes = (u8*)vec_end - (u8*)(cur + 1);
                                                if (shift_bytes != 0) {
                                                    memmove(cur, cur + 1, shift_bytes);
                                                }
                                                *(u64**)(pool_obj + 3) =
                                                    cur + ((s64)shift_bytes >> 3);
                                                if (ptr != nullptr) {
                                                    u64 mem_size = *(u64*)((u8*)ptr + 0x10);
                                                    u64* alloc = *(u64**)((u8*)ptr + 0x50);
                                                    if (alloc == nullptr) abort();
                                                    ((void(*)(u64*, u64*))(*(u64*)(*alloc + 0x30)))
                                                        (alloc, &mem_size);
                                                    *(u64*)((u8*)ptr + 0x10) = 0;
                                                    *(u64*)((u8*)ptr + 0x18) = 0;
                                                    u64* alloc2 = *(u64**)((u8*)ptr + 0x50);
                                                    if (alloc2 == (u64*)((u8*)ptr + 0x30)) {
                                                        ((void(*)())(*(u64*)(*alloc2 + 0x20)))();
                                                    } else if (alloc2 != nullptr) {
                                                        ((void(*)())(*(u64*)(*alloc2 + 0x28)))();
                                                    }
                                                    FUN_710392e590(ptr);
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    cur++;
                                    counter--;
                                } while (vec_end != cur);
                            }
                        }
                        unlock_71039c14a0(service->mutex);

                        node = next_saved;
                    }

                    if (service->unk5 != 0) goto re_queue;
                } // end while (node != sentinel)
            }

            queue_idx++;
            if (queue_idx < 5) goto begin_processing;

            // ================================================================
            // POST-PROCESSING: sleep, signal events, update directory states
            // [derived: runs after all 5 queues are drained]
            // ================================================================
            if (service->is_loader_thread_running == 0) {
                FUN_71039c07c0(16000000);

                // Acquire and release processing semaphore (sync barrier)
                FUN_71039c0740(
                    *(void**)(*(u64*)service->semaphore2 + 8));
                FUN_71039c0750(
                    *(void**)(*(u64*)service->semaphore2 + 8));

                // Signal completion event
                void* comp_event = *(void**)
                    (*(u64*)service->unk_event1);
                if (comp_event != nullptr) {
                    FUN_71039c0720(comp_event);
                }

                // Update directory loading states
                void* svc_mtx = service->mutex;
                lock_71039c1490(svc_mtx);

                u32* dp = dir_buf;
                for (; dp != dir_buf_end; dp++) {
                    u32 didx = *dp;
                    if (didx == 0xffffff) continue;
                    FilesystemInfo* fs = service->filesystem_info;
                    if (didx >= fs->loaded_directory_len) continue;

                    void* fs_mtx = fs->mutex;
                    lock_71039c1490(fs_mtx);
                    LoadedDirectory* dirs = fs->loaded_directories;
                    LoadedDirectory* dir = &dirs[didx];
                    u8 dir_flags = dir->flags;
                    unlock_71039c14a0(fs_mtx);

                    if (!(dir_flags & 1) || dir == nullptr) continue;

                    if (dir->file_group_index != 0xffffff) {
                        s32 state = FUN_7103542ad0(dir);
                        if (state == 3) {
                            dirs[didx].flags &= 0xf9;
                            continue;
                        }
                        if (state > 0) {
                            FUN_7103541e30(dir);
                            continue;
                        }
                    }

                    if (dirs[didx].incoming_request_count == 0) {
                        *(u32*)&dirs[didx].incoming_request_count = 0;
                        dirs[didx].flags &= 0xf9;
                        *(u32*)&dirs[didx].state = 0;
                    }
                }

                dir_buf_end = dir_buf;
                unlock_71039c14a0(svc_mtx);

                // Update loading thread state
                if (service->state != (s16)-1) {
                    lock_71039c1490(service->mutex);
                    service->state = 3;
                    unlock_71039c14a0(service->mutex);
                }
            }

        cleanup:
            // Free directory index buffer
            if (dir_buf != nullptr) {
                dir_buf_end = dir_buf;
                FUN_710392e590(dir_buf);
            }
            // Check for file read errors
            if (*(u8*)((u8*)service + 0x248)) {
                lock_71039c1490(service->mutex);
                service->state = -1;
                unlock_71039c14a0(service->mutex);
            }
            goto cleanup_lists;

        } else {
            // No items to process
            service->state = 3;
            unlock_71039c14a0(service->mutex);
            // Signal completion event
            void* comp_event = *(void**)
                (*(u64*)service->unk_event1);
            if (comp_event != nullptr) {
                FUN_71039c0720(comp_event);
            }
        }

    cleanup_lists:
        // Destroy all 5 local list nodes
        for (int ci = 4; ci >= 0; ci--) {
            ListNode* local_sentinel = (ListNode*)&local_lists[ci].next;
            local_lists[ci].size = 0;
            ListNode* cnode = local_lists[ci].next;
            while (cnode != local_sentinel) {
                ListNode* cnext = cnode->next;
                cnode->next = nullptr;
                cnode->prev = nullptr;
                cnode = cnext;
            }
            local_lists[ci].next = nullptr;
            local_lists[ci].end = nullptr;
        }

    } while (!service->is_loader_thread_running);
}
