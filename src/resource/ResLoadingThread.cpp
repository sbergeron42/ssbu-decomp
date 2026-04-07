// ResLoadingThread.cpp — The critical-path resource loading/processing loop
// Address: 0x7103542f30, Size: 12,496 bytes
// [derived: Ghidra 13.0.1 decompilation of ResLoadingThread]
// This is the main loop for ResLoadingThread — processes file/directory load requests
// from 5 request queues in ResServiceNX. All 6 ARCropolis hooks in the loading
// pipeline land in this function.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"
#include "resource/LZ4Frame.h"

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
extern "C" void* memset(void*, int, u64);
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
// [note: 13.0.1 address is 0x7103544CA0, 13.0.4 address is 0x71035456D0]
extern "C" u64 FUN_71035456d0(ResServiceNX* svc, FileNX** file, u32 dir_idx, u32 mode, u32 extra);
#define FUN_7103544ca0 FUN_71035456d0
// [derived: recursive directory loading state check — returns min state in chain]
s32 FUN_7103542ad0(LoadedDirectory* dir);
// [derived: reset/update loaded directory state]
extern "C" void FUN_7103541e30(LoadedDirectory* dir);

// Additional subfunctions for ResInflateThread (FUN_71035444C0)
// [derived: process pending stream releases on FilesystemInfo]
extern "C" void FUN_710353f1b0(FilesystemInfo*);
// [derived: resolve version with filesystem default — if *ver==0xFFFF, replaces with ARC header version]
extern "C" s32 FUN_7103542f30(s32* ver);
// [derived: directory state update helper]
extern "C" void FUN_7103542860(LoadedDirectory* dir);
// [derived: LZ4F_decompress — LZ4 frame streaming decompression state machine]
// [identified: LZ4 v1.8.x library, lz4frame.c:LZ4F_decompress() — NOT zstd]
// [evidence: XXH32 seed constants 0x24234428/0x85EBCA77/0x61C8864F, 15-state machine]
// defined below at line ~1215
extern "C" u32 FUN_71035472b0(LZ4F_wrapper* ctx, void* dstBuffer, u64* dstSizePtr, u8* srcBuffer, u64* srcSizePtr);
// [derived: free decompression context — frees both sub-contexts and buffers]
extern "C" void FUN_7103547220(void** state);
// [derived: init decompression state — returns 0 on success, 0x80000004 on alloc failure]
extern "C" u32 FUN_7103541ae0(void** state);
// [derived: ZSTD custom free wrapper — calls je_free(ptr) if ptr != null]
extern "C" void FUN_7103541c80(void* opaque, void* ptr);
// [derived: alloc_with_oom_retry — calls je_aligned_alloc(8, size) with OOM retry]
extern "C" void* FUN_7103541c00(u64 unused, u64 size);
// [derived: cleanup decompression filepath/dir pair]
extern "C" void FUN_7103541a60(void** state);
// nn::os PLT stubs used by ResInflateThread
extern "C" void _ZN2nn2os16ReleaseSemaphoreEPNS0_13SemaphoreTypeE(void*);
extern "C" void _ZN2nn2os9WaitEventEPNS0_9EventTypeE(void*);
extern "C" void _ZN2nn2os11YieldThreadEv(void);
// [derived: ZSTD_decompressStream — streaming decompression step]
extern "C" s64 ZSTD_decompressStream_71039a3a50(void* dstream, void* output, void* input);
// [derived: ZSTD_freeDStream]
extern "C" s64 ZSTD_freeDStream_71039a38e0(void* dstream);
// [derived: ZSTD_DStream cleanup helper]
extern "C" void FUN_71039a2200(void* ctx);
// [derived: ZSTD finalize decomp context]
extern "C" void FUN_710399f880(void* ctx);

// LZ4 library functions (LZ4 v1.8.x, bundled in Nintendo SDK 8.2.1)
// [derived: called from FUN_71035472b0 (LZ4F_decompress)]
// [derived: LZ4F_decodeHeader — parses frame header, returns bytes consumed]
extern "C" u64 FUN_710399d650(LZ4F_dctx* dctx, const u8* src);
// [derived: LZ4_decompress_safe_usingDict — block decompression with dictionary]
extern "C" s32 FUN_710399d850(const u8* src, u8* dst, u32 compressedSize,
                               u64 maxDecompressedSize, const u8* dictStart, u32 dictSize);
// [derived: XXH32_update — streaming hash update]
extern "C" void FUN_710399ee20(XXH32_state_t* state, const void* input, u64 length);
// [derived: XXH32_digest — finalize streaming hash, return 32-bit hash]
extern "C" u32 FUN_710399efc0(XXH32_state_t* state);
// [derived: XXH32 — one-shot hash computation]
extern "C" s32 FUN_710399eb90(const void* input, u64 length);

// Error code lookup table for LZ4F_decompress
// [derived: adrp+add at 0x7103547fd0, indexed by (hint + 18)]
__attribute__((visibility("hidden"))) extern u32 DAT_7104560990[];

// Globals
__attribute__((visibility("hidden"))) extern ResServiceNX* DAT_7105331f28;
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// ============================================================================
// Helper: vector push_back with OOM retry (inlined by compiler 3 times)
// Pushes a u32 to a { start, end, cap } triple with growth.
// ============================================================================
static __attribute__((always_inline)) void vec_push_u32(
    u32** start, u32** end, u32** cap, u32 value,
    s32* oom_flags_p, s64* oom_size_p)
{
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
                *oom_flags_p = 0;
                *oom_size_p = (s64)alloc_size;
                u64 r = ((u64(*)(s64*, s32*, s64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                         (DAT_7105331f00, oom_flags_p, oom_size_p);
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

    // Function-scope temporaries — reused across multiple paths
    // [derived: Ghidra aiStack_78[2] at fp-0x78, uStack_70 at fp-0x70]
    // Address-taken locals that must persist on the stack
    s32 temp_pair[2];
    s64 temp_val;

    do {
        // ================================================================
        // Wait for update event (unless already in processing state)
        // [derived: unk_event2 at +0x020 is EventType** wrapper]
        // ================================================================
        if (service->unk4 != 2) {
            void* event = **(void***)service->res_update_event;
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
        service->unk4 = 2;

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
        // [derived: binary at 0x35431a4–0x35432b8: full doubly-linked list swap with null handling]
        for (u64 qi = 0; qi < 5; qi++) {
            ResList* svc = &service->res_lists[qi];
            ResList* local = &local_lists[qi];
            ListNode* svc_sentinel = (ListNode*)&svc->next;
            s32 count = (s32)svc->size;

            {
                ListNode* local_head = local->next;
                ListNode* svc_head = svc->next;

                // Determine swap participants (handle null/sentinel cases)
                ListNode* sw_local;
                ListNode* sw_svc;
                ListNode* sw_svc_end;

                if (local_head == nullptr) {
                    // Reinitialize local sentinel
                    ListNode* lsent = (ListNode*)&local->next;
                    local->next = lsent;
                    local->end = lsent;
                    sw_local = lsent;
                    if (svc_head == nullptr) goto null_both;
                    sw_svc_end = svc->end;
                    sw_svc = svc_head;
                } else if (svc_head == nullptr) {
                null_both:
                    svc->next = svc_sentinel;
                    sw_svc = svc_sentinel;
                    sw_svc_end = svc_sentinel;
                    svc->end = svc_sentinel;
                    sw_local = local_head ? local_head : (ListNode*)&local->next;
                } else {
                    sw_local = local_head;
                    sw_svc_end = svc->end;
                    sw_svc = svc_head;
                }

                // 4-way pointer swap
                ListNode* lhp = sw_local->prev;
                ListNode* shp = sw_svc->prev;
                ListNode* local_end_ptr = local->end;
                sw_local->prev = shp;
                sw_svc->prev = lhp;

                ListNode* se_next = sw_svc_end->next;
                ListNode* le_next = local_end_ptr->next;
                local_end_ptr->next = se_next;
                sw_svc_end->next = le_next;

                ListNode* ln = local->next;
                ListNode* sn = svc->next;
                local->next = sn;
                svc->next = ln;

                ListNode* le = local->end;
                ListNode* se = svc->end;
                local->end = se;
                svc->end = le;

                // Null fixup
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

            // Clear remaining nodes in service list
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
        service->state = 0;   // +0x0E4: clear processing sub-state (byte access)

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

            // Re-drain all 5 queues from service into local lists
            // [derived: binary shows 5 unrolled while loops at 0x3543fd0-0x354419c]
            for (int rq = 0; rq < 5; rq++) {
                ListNode* svc_sent_rq = (ListNode*)&service->res_lists[rq].next;
                ListNode* rq_node = service->res_lists[rq].next;
                while (rq_node != svc_sent_rq) {
                    ListNode* rq_next = rq_node->next;
                    // Unlink from service list
                    ListNode* rq_prev = rq_node->prev;
                    ListNode* rq_nxt = rq_node->next;
                    rq_nxt->prev = rq_prev;
                    rq_prev->next = rq_nxt;
                    service->res_lists[rq].size--;
                    // Clear and relink to local list tail
                    rq_node->next = nullptr;
                    rq_node->prev = nullptr;
                    ListNode* local_sent_rq = (ListNode*)&local_lists[rq].next;
                    ListNode* old_end = local_lists[rq].end;
                    rq_node->next = local_sent_rq;
                    rq_node->prev = old_end;
                    old_end->next = rq_node;
                    local_lists[rq].end = rq_node;
                    local_lists[rq].size++;
                    rq_node = rq_next;
                }
            }

            service->unk5 = 0;
            service->state = 0;
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
                            temp_pair[0] = (s32)(arc->fs_header->version & 0x00ffffff);
                            FUN_710353b050(&temp_pair[0]);
                            if (temp_pair[0] == version) {
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
                            temp_pair[0] = version;
                            FUN_710353b050(&temp_pair[0]);
                            datas[data_idx].version = (u32)temp_pair[0];
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
                            temp_pair[0] = (s32)(arc->fs_header->version & 0x00ffffff);
                            FUN_710353b050(&temp_pair[0]);
                            if (arc_ver == temp_pair[0]) goto standard_file_resolve;

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
                                    temp_val = 0;
                                    FUN_71039c7680(&temp_val,
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
                                void* swap_event = **(void***)service->io_swap_event;
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
                                                 node->data.directory_index,
                                                 temp_pair, &temp_val);
                                }
                            } else {
                                // Bit 26 set: directory has sub-directory reference
                                if ((node->data.files_to_load != 0) &&
                                    (FUN_7103544ca0(service, service->data_arc_filenx,
                                        (u32)dir_info_idx, 0, 0xffffff) & 1) == 0) {
                                    goto next_node;
                                }
                                vec_push_u32(&dir_buf, &dir_buf_end, &dir_buf_cap,
                                             node->data.directory_index,
                                             temp_pair, &temp_val);

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
                                         node->data.directory_index,
                                         temp_pair, &temp_val);
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
                if (service->unk4 != (u32)-1) {
                    lock_71039c1490(service->mutex);
                    service->unk4 = 3;
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
                service->unk4 = (u32)-1;
                unlock_71039c14a0(service->mutex);
            }
            goto cleanup_lists;

        } else {
            // No items to process
            service->unk4 = 3;
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

// ============================================================================
// FUN_7103542F30 — resolve_version_or_default
// If *ver is the sentinel 0xFFFF, replaces it with the filesystem header's
// version (masked to 24 bits). Self-recursive: the recursive call returns
// the non-sentinel value unchanged.
// [derived: called from ResInflateThread at 0x35447EC via bl #-6332]
// [derived: accesses DAT_7105331f20 (FilesystemInfo*) → path_info → arc → fs_header → version]
// Address: 0x7103542F30, Size: 100 bytes
// ============================================================================
s32 FUN_7103542f30(s32* ver) {
    s32 val = *ver;
    if (val != (s32)0xFFFF) return val;

    // Load default version from filesystem
    FilesystemInfo* fs = DAT_7105331f20;
    if (fs == nullptr) return (s32)0xFFFF;

    PathInformation* pi = (PathInformation*)fs->path_info;
    LoadedArc* arc = pi->arc;
    s32 default_ver = (s32)(arc->fs_header->version & 0xFFFFFF);

    if (default_ver == (s32)0xFFFF) return (s32)0xFFFF;

    // Recursive call: since default_ver != 0xFFFF, this just returns it
    s32 temp = default_ver;
    s32 result = FUN_7103542f30(&temp);
    *ver = result;
    return result;
}

// ============================================================================
// FUN_7103547220 — free_decomp_context
// Frees a two-level decompression context structure:
//   state[0] → container with two sub-contexts at [0] and [8]
//   Sub-context 0 has allocated buffers at +0xA8 and +0x58
//   Sub-context 1 has allocated buffers at +0x40 and +0x58
// All freed via je_free, then container itself freed.
// [derived: called from ResInflateThread cleanup paths]
// [derived: sub-context buffer offsets confirmed by Ghidra field analysis]
// Address: 0x7103547220, Size: 140 bytes
// ============================================================================
void FUN_7103547220(void** state) {
    void* ctx = *state;
    if (ctx != nullptr) {
        // Free first sub-context (decompression workspace)
        void* sub0 = ((void**)ctx)[0];
        if (sub0 != nullptr) {
            void* buf_a8 = *(void**)((u8*)sub0 + 168);  // +0xA8
            if (buf_a8 != nullptr) FUN_710392e590(buf_a8);
            void* buf_58 = *(void**)((u8*)sub0 + 88);   // +0x58
            if (buf_58 != nullptr) FUN_710392e590(buf_58);
            FUN_710392e590(sub0);
        }
        // [derived: store null BEFORE loading next sub-context, matching binary at 0x3547264]
        ((void**)ctx)[0] = nullptr;

        // Free second sub-context (ZSTD DStream or similar)
        void* sub1 = ((void**)ctx)[1];
        if (sub1 != nullptr) {
            void* buf_40 = *(void**)((u8*)sub1 + 64);   // +0x40
            if (buf_40 != nullptr) FUN_710392e590(buf_40);
            void* buf_58b = *(void**)((u8*)sub1 + 88);  // +0x58
            if (buf_58b != nullptr) FUN_710392e590(buf_58b);
            FUN_710392e590(sub1);
            // [derived: null store inside if-block — target skips it when sub1 was already null]
            ((void**)ctx)[1] = nullptr;
        }

        // Free container
        FUN_710392e590(ctx);
    }
    *state = nullptr;
}

// ============================================================================
// FUN_7103541A60 — cleanup_decomp_state
// Cleans up a decompression state: finalizes the decomp context (if owned),
// closes the ZSTD stream, frees the container.
// [derived: implements CLEANUP_CTX + CLOSE_STREAM + free pattern]
// [derived: field_0x1A8 == 0 means "we own it" → finalize + dealloc]
// [derived: field_0x198 = dealloc function, field_0x1A0 = dealloc arg]
// Address: 0x7103541A60, Size: 128 bytes
// ============================================================================
void FUN_7103541a60(void** state) {
    void* ctx = *state;
    if (ctx == nullptr) { *state = nullptr; return; }

    // Clean up sub-context 0 (decompression workspace)
    void* sub0 = ((void**)ctx)[0];
    if (sub0 != nullptr) {
        u64 ext_flag = *(u64*)((u8*)sub0 + 0x1A8);
        if (ext_flag != 0) {
            // Externally managed — just free container and return
            FUN_710392e590(ctx);
            *state = nullptr;
            return;
        }
        // Owned: finalize decomp context
        FUN_710399f880(sub0);
        typedef void (*DeallocFn)(void*, void*);
        DeallocFn dealloc = *(DeallocFn*)((u8*)sub0 + 0x198);
        if (dealloc != nullptr) {
            void* dealloc_arg = *(void**)((u8*)sub0 + 0x1A0);
            dealloc(dealloc_arg, sub0);
        } else {
            FUN_710392e590(sub0);
        }
    }
    ((void**)ctx)[0] = nullptr;

    // Close ZSTD stream (sub-context 1)
    void* stream = ((void**)ctx)[1];
    if (stream != nullptr) {
        ZSTD_freeDStream_71039a38e0(stream);
    }

    // Free container
    FUN_710392e590(ctx);
    *state = nullptr;
}

// ============================================================================
// FUN_7103541C80 — ZSTD custom free callback
// Simple wrapper: if ptr is non-null, calls je_free(ptr).
// Used as ZSTD_customMem.customFree in the decompression context.
// [derived: stored at DCtx+0x7128 by FUN_7103541AE0]
// Address: 0x7103541C80, Size: 16 bytes
// ============================================================================
void FUN_7103541c80(void* /*opaque*/, void* ptr) {
    if (ptr != nullptr) {
        FUN_710392e590(ptr);
    }
}

// ============================================================================
// FUN_7103541AE0 — init_decomp_state
// Initializes (or re-initializes) a ZSTD streaming decompression state.
// State is a 2-element array: state[0] = decomp workspace, state[1] = DCtx.
// If state[0] is owned (field_0x1A8 == 0), finalizes and frees it.
// If state[0] is externally managed, skips cleanup entirely.
// Closes any existing state[1] stream, then allocates a fresh 160,240-byte
// ZSTD DCtx and initializes its custom allocator and internal fields.
// [derived: called from ResInflateThread decompression paths]
// [derived: DCtx allocation = 160,240 bytes = zstd v1.3.7 ZSTD_sizeof_DCtx()]
// [derived: custom alloc at DCtx+0x7120, custom free at DCtx+0x7128, opaque at DCtx+0x7130]
// Address: 0x7103541AE0, Size: 284 bytes
// ============================================================================
u32 FUN_7103541ae0(void** state) {
    void* sub0 = *state;
    void** stream_slot;  // tracks &state[1] for final storage

    if (sub0 != nullptr) {
        u64 ext_flag = *(u64*)((u8*)sub0 + 0x1A8);
        if (ext_flag != 0) {
            // Externally managed — skip all cleanup, go straight to allocation
            stream_slot = &state[1];
            goto alloc_dctx;
        }
        // Owned: finalize and free decomp context (CLEANUP_CTX)
        FUN_710399f880(sub0);
        typedef void (*DeallocFn)(void*, void*);
        DeallocFn dealloc = *(DeallocFn*)((u8*)sub0 + 0x198);
        if (dealloc != nullptr) {
            void* dealloc_arg = *(void**)((u8*)sub0 + 0x1A0);
            dealloc(dealloc_arg, sub0);
        } else {
            FUN_710392e590(sub0);
        }
        state[0] = nullptr;
    }

    // Close existing ZSTD stream (state[1])
    stream_slot = &state[1];
    {
        void* stream = *stream_slot;
        if (stream != nullptr) {
            s64 result = ZSTD_freeDStream_71039a38e0(stream);
            // Only clear if close succeeded (not an error)
            if ((u64)result <= 0xFFFFFFFFFFFFFF88ULL) {
                *stream_slot = nullptr;
            }
        }
    }

alloc_dctx:
    {
        // Allocate ZSTD DCtx (160,240 bytes)
        void* buf = FUN_7103541c00((u64)state, 160240);
        if (buf == nullptr) {
            *stream_slot = nullptr;
            return 0x80000004;
        }

        // Initialize custom allocator (ZSTD_customMem at DCtx+0x7120)
        u8* p = (u8*)buf;
        *(void**)(p + 0x7120) = (void*)FUN_7103541c00;  // customAlloc
        *(void**)(p + 0x7128) = (void*)FUN_7103541c80;  // customFree
        *(void**)(p + 0x7130) = (void*)state;            // opaque (backlink)

        // Clear internal state fields
        *(u32*)(p + 0x7114) = 0;
        *(u64*)(p + 0x7188) = 0x08000001ULL;  // stage/version flags
        *(u64*)(p + 0x7148) = 0;
        *(u64*)(p + 0x7198) = 0;
        *(u64*)(p + 0x71C8) = 0;
        *(u32*)(p + 0x71C0) = 0;
        *(u32*)(p + 0x7150) = 0;
        *(u64*)(p + 0x7158) = 0;
        *(u64*)(p + 0x7160) = 0;
        *(u64*)(p + 0x7178) = 0;
        *(u64*)(p + 0x7170) = 0;

        // Store DCtx pointer
        *stream_slot = buf;

        // More field clears (redundant but present in binary — must not be optimized away)
        *(u32*)(p + 0x7168) = 0;
        *(u32*)(p + 0x71DC) = 0;
        *(volatile u64*)(p + 0x7160) = 0;
        *(volatile u64*)(p + 0x7158) = 0;

        return 0;
    }
}

// ============================================================================
// FUN_71035472B0 — LZ4F_decompress (modified for game)
// LZ4 frame streaming decompression state machine with 15 states.
// [identified: LZ4 library v1.8.x, lz4frame.c:LZ4F_decompress()]
// [modified: je_aligned_alloc(0x10, size) + OOM retry replaces standard malloc/free]
// [modified: return convention: 0=done, 1=continue, 0x80000001=bad_param,
//  0x80000002=decomp_error, 0x80000003=uninitialized]
// [evidence: XXH32 reset constants at +0x88/+0xB8 match XXH32_reset(state, 0)]
//
// Parameters:
//   ctx:        LZ4F_wrapper* — wrapper[1] = LZ4F_dctx*
//   dstBuffer:  output buffer base pointer
//   dstSizePtr: in: available output size; out: bytes produced
//   srcBuffer:  compressed input data
//   srcSizePtr: in: available input size; out: bytes consumed
//
// State machine stages:
//   0: getFrameHeader     — decode LZ4 frame header from src
//   1: storeFrameHeader   — buffer partial frame header
//   2: init               — allocate tmpIn/tmpOutBuffer based on maxBlockSize
//   3: getBlockHeader     — read 4-byte block header (size + compressed flag)
//   4: storeBlockHeader   — buffer partial block header
//   5: copyDirect         — copy uncompressed block to output
//   6: getBlockChecksum   — read 4-byte block checksum
//   7: getCBlock          — decompress compressed block (direct or via tmpIn)
//   8: storeCBlock        — buffer partial compressed block into tmpIn
//   9: flushOut           — flush decompressed data from tmpOut to output
//  10: getSuffix          — read content checksum at end of frame
//  11: storeSuffix        — buffer partial content checksum
//  12: getSFrameSize      — read skippable frame size
//  13: storeSFrameSize    — buffer partial skippable frame size
//  14: skipSkippable      — skip over skippable frame data
//
// Address: 0x71035472B0, Size: 3,860 bytes
// ============================================================================

// Ring buffer window management helper (inlined in original)
// Updates dict/dictSize when output crosses the ring buffer boundary.
// Window size capped at 64KB (LZ4 maximum).
static inline void lz4f_update_window_copy(
    LZ4F_dctx* dctx, u8* dstPtr, u8* dstBuffer, u8* srcData, u64 copyLen)
{
    u8* dictPtr;
    u64 dSize = dctx->dictSize;

    if (dSize == 0) {
        dctx->dict = dstPtr;
        dictPtr = dstPtr;
    } else {
        dictPtr = dctx->dict;
    }

    u8* dictEnd = dictPtr + dSize;
    if (dictEnd == dstPtr) {
        // Contiguous — just extend
        dctx->dictSize = dSize + copyLen;
        return;
    }

    // Non-contiguous — check if output wraps into ring buffer range
    u64 outputOffset = copyLen + (u64)(dstPtr - dstBuffer);
    if (outputOffset >= 0x10000) {
        // Output too far from ring buffer — reset to dstBuffer
        dctx->dict = dstBuffer;
        return;
    }

    u8* ringBase = dctx->tmpOutBuffer;
    if (dictPtr == ringBase) {
        // Dict starts at ring buffer base
        if (dctx->maxBufferSize < dSize + copyLen) {
            // Overflow — shift ring buffer contents
            u64 keep = 0x10000 - copyLen;
            memcpy(dictPtr, dictEnd - keep, keep);
            dctx->dictSize = keep;
            dictEnd = ringBase + keep;
        }
        memcpy(dictEnd, dstPtr, copyLen);
        dctx->dictSize = dctx->dictSize + copyLen;
    } else {
        // Dict not at ring buffer base — consolidate
        u64 keep = dSize;
        if (0x10000 - copyLen <= dSize) {
            keep = 0x10000 - copyLen;
        }
        memcpy(ringBase, dictEnd - keep, keep);
        memcpy(ringBase + keep, dstPtr, copyLen);
        dctx->dictSize = keep + copyLen;
        dctx->dict = ringBase;
    }
}

// Flush-path window update for decompressed data routed through tmpOut
static inline void lz4f_update_window_flush(
    LZ4F_dctx* dctx, u8* dstPtr, u8* dstBuffer, u64 copyLen)
{
    u8* dictPtr;
    u64 dSize = dctx->dictSize;

    if (dSize == 0) {
        dctx->dict = dstPtr;
        dictPtr = dstPtr;
    } else {
        dictPtr = dctx->dict;
    }

    u8* dictEnd = dictPtr + dSize;
    if (dictEnd == dstPtr) {
        dctx->dictSize = dSize + copyLen;
        return;
    }

    u64 outputOffset = copyLen + (u64)(dstPtr - dstBuffer);
    if (outputOffset >= 0x10000) {
        dctx->dict = dstBuffer;
        return;
    }

    u8* ringBase = dctx->tmpOutBuffer;
    if (dictPtr != ringBase) {
        // Consolidate window around tmpOut
        u64 tmpOutOff = (u64)(dctx->tmpOut - ringBase);
        u64 outTotal = dctx->tmpOutSize;
        u64 window = outTotal;
        if (outTotal < 0x10001) window = 0x10000;
        u64 backCopy = window - outTotal;
        if (backCopy > tmpOutOff) backCopy = tmpOutOff;
        if (backCopy != 0) {
            memcpy(dctx->tmpOut - backCopy,
                   dictEnd - (dctx->tmpOutStart + backCopy),
                   backCopy);
        }
        dctx->dict = ringBase;
        dctx->dictSize = dctx->tmpOutStart + tmpOutOff + copyLen;
    } else {
        dctx->dictSize = dSize + copyLen;
    }
}

extern "C" u32 FUN_71035472b0(LZ4F_wrapper* wrapper, void* dstBuffer, u64* dstSizePtr,
                               u8* srcBuffer, u64* srcSizePtr)
{
    // Parameter validation
    if (dstBuffer == nullptr) return 0x80000001;
    if (srcBuffer == nullptr) return 0x80000001;
    u64 srcSize = *srcSizePtr;
    if (srcSize == 0) return 0x80000001;

    LZ4F_dctx* dctx = wrapper->dctx;
    if (dctx == nullptr) return 0x80000003;

    // Setup tracking pointers
    u8* srcPtr = srcBuffer;
    u8* const srcEnd = srcBuffer + srcSize;
    u8* dstPtr = (u8*)dstBuffer;
    u8* const dstEnd = (u8*)dstBuffer + *dstSizePtr;

    // Function-scope variables for cross-goto communication
    // (matches register usage in original: hint in x26, consumed in x8, produced in x9)
    u64 hint = 0;
    u8* parseBuf = nullptr;

    // Cross-goto shared variables (declared here to avoid bypassing initialization)
    u64 copyDone, target, remaining, need, copyLen, newSize, srcRem;
    u64 blockTarget, dstAvail, totalDecoded, alreadyFlushed, flushRem;
    u64 outAlloc;
    u8* copyDst;
    u8* nextSrc;
    u8* outBuf;
    u8* blockData;
    s32 bcFlag;

    // Main state machine loop
next_stage:
    switch (dctx->dStage) {

    // ---- Stage 0: getFrameHeader ----
    case 0: {
        u64 remaining = srcEnd - srcPtr;
        if (remaining < 19) { // LZ4F_HEADER_SIZE_MAX
            dctx->tmpInSize = 0;
            if (remaining == 0) {
                hint = 7; // LZ4F_HEADER_SIZE_MIN
                goto return_progress_zero;
            }
            copyDone = 0;
            dctx->tmpInTarget = 7;
            dctx->dStage = 1;
            copyDst = dctx->header;
            goto do_store_header;
        }
        u64 consumed = FUN_710399d650(dctx, srcPtr);
        srcPtr += consumed;
        if (consumed > (u64)(-19)) goto return_decode_error;
        goto next_stage;
    }

    // ---- Stage 1: storeFrameHeader ----
    case 1: {
        copyDone = dctx->tmpInSize;
        target = dctx->tmpInTarget;
        remaining = srcEnd - srcPtr;
        copyDst = dctx->header + copyDone;
    do_store_header:
        need = target - copyDone;
        copyLen = (remaining < need) ? remaining : need;
        memcpy(copyDst, srcPtr, copyLen);
        newSize = copyLen + dctx->tmpInSize;
        srcPtr += copyLen;
        dctx->tmpInSize = newSize;
        if (newSize < dctx->tmpInTarget) {
            hint = (4 - newSize) + dctx->tmpInTarget;
            goto return_exit;
        }
        u64 consumed = FUN_710399d650(dctx, dctx->header);
        if (consumed > (u64)(-19)) goto return_decode_error;
        goto next_stage;
    }

    // ---- Stage 2: init ----
    case 2: {
        if (dctx->frameInfo.contentChecksumFlag != 0) {
            // XXH32_reset(&dctx->xxh, 0)
            dctx->xxh.total_len_32 = 0;
            dctx->xxh.large_len = 0;
            dctx->xxh.v1 = 0x24234428;
            dctx->xxh.v2 = 0x85EBCA77;
            dctx->xxh.v3 = 0;
            dctx->xxh.v4 = 0x61C8864F;
            memset(dctx->xxh.mem32, 0, sizeof(dctx->xxh.mem32));
            dctx->xxh.memsize = 0;
        }

        u64 blockSize = dctx->maxBlockSize;
        u64 bufferSize = blockSize + (u64)(dctx->frameInfo.blockMode == 0) * 0x20000;
        if (bufferSize <= dctx->maxBufferSize) {
            outBuf = dctx->tmpOutBuffer;
            goto init_done;
        }

        dctx->maxBufferSize = 0;
        if (dctx->tmpIn != nullptr) {
            FUN_710392e590(dctx->tmpIn);
            blockSize = dctx->maxBlockSize;
        }

        {
            u64 tmpInAlloc = blockSize + 4;
            if (tmpInAlloc == 0) tmpInAlloc = 1;
            u8* tmpInBuf = (u8*)je_aligned_alloc(0x10, tmpInAlloc);
            if (tmpInBuf == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    s32 oom_flags = 0;
                    u64 oom_size = tmpInAlloc;
                    u64 r = ((u64(*)(s64*, s32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_flags, &oom_size);
                    if ((r & 1) != 0) {
                        tmpInBuf = (u8*)je_aligned_alloc(0x10, tmpInAlloc);
                        if (tmpInBuf != nullptr) goto got_tmpin;
                    }
                }
                dctx->tmpIn = nullptr;
                hint = 9;
                goto do_lookup;
            }
        got_tmpin:
            dctx->tmpIn = tmpInBuf;
        }

        if (dctx->tmpOutBuffer != nullptr) {
            FUN_710392e590(dctx->tmpOutBuffer);
        }

        {
            outAlloc = bufferSize;
            if (outAlloc == 0) outAlloc = 1;
            outBuf = (u8*)je_aligned_alloc(0x10, outAlloc);
            if (outBuf == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    s32 oom_flags2 = 0;
                    u64 oom_size2 = outAlloc;
                    u64 r2 = ((u64(*)(s64*, s32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                              (DAT_7105331f00, &oom_flags2, &oom_size2);
                    if ((r2 & 1) != 0) {
                        outBuf = (u8*)je_aligned_alloc(0x10, outAlloc);
                        if (outBuf != nullptr) goto got_outbuf;
                    }
                }
                dctx->tmpOutBuffer = nullptr;
                hint = 9;
                goto do_lookup;
            }
        got_outbuf:
            dctx->tmpOutBuffer = outBuf;
            dctx->maxBufferSize = bufferSize;

        init_done:
            dctx->tmpInSize = 0;
            dctx->tmpInTarget = 0;
            dctx->tmpOut = outBuf;
            dctx->tmpOutSize = 0;
            dctx->tmpOutStart = 0;
            dctx->dStage = 3;
        }
        // fall through to case 3
    }

    // ---- Stage 3: getBlockHeader ----
    case 3: {
        remaining = srcEnd - srcPtr;
        if (remaining >= 4) {
            parseBuf = srcPtr;
            srcPtr += 4;
            goto parse_block_header;
        }
        dctx->tmpInSize = 0;
        dctx->dStage = 4;
        copyDone = 0;
        srcRem = remaining;
        goto do_store_block_header;
    }

    // ---- Stage 4: storeBlockHeader ----
    case 4: {
        copyDone = dctx->tmpInSize;
        srcRem = srcEnd - srcPtr;
    do_store_block_header:
        need = 4 - copyDone;
        copyLen = (srcRem < need) ? srcRem : need;
        memcpy(dctx->tmpIn + copyDone, srcPtr, copyLen);
        newSize = dctx->tmpInSize + copyLen;
        srcPtr += copyLen;
        dctx->tmpInSize = newSize;
        if (newSize < 4) {
            hint = 4 - newSize;
            goto return_exit;
        }
        parseBuf = dctx->tmpIn;

    parse_block_header:;
        u64 val = (u64)parseBuf[0];
        val |= (u64)parseBuf[1] << 8;
        val |= (u64)parseBuf[2] << 16;
        val |= (u64)parseBuf[3] << 24;
        u64 blockSize = val & 0x7FFFFFFF;

        if ((u32)blockSize == 0) {
            dctx->dStage = 10;
            goto next_stage;
        }
        if (blockSize > dctx->maxBlockSize) {
            hint = 0x10;
            goto do_lookup;
        }

        if ((s32)(u32)val < 0) {
            // Uncompressed block
            dctx->tmpInTarget = blockSize;
            if (dctx->frameInfo.blockChecksumFlag != 0) {
                dctx->blockChecksum.total_len_32 = 0;
                dctx->blockChecksum.large_len = 0;
                dctx->blockChecksum.v1 = 0x24234428;
                dctx->blockChecksum.v2 = 0x85EBCA77;
                dctx->blockChecksum.v3 = 0;
                dctx->blockChecksum.v4 = 0x61C8864F;
                memset(dctx->blockChecksum.mem32, 0, sizeof(dctx->blockChecksum.mem32));
                dctx->blockChecksum.memsize = 0;
            }
            dctx->dStage = 5;
        } else {
            // Compressed block
            u64 target = blockSize + (u32)(dctx->frameInfo.blockChecksumFlag << 2);
            dctx->dStage = 7;
            dctx->tmpInTarget = target;
            if (dstPtr == dstEnd) {
                hint = target + 4;
                goto return_exit;
            }
        }
        goto next_stage;
    }

    // ---- Stage 5: copyDirect (uncompressed block) ----
    case 5: {
        u64 srcRem = srcEnd - srcPtr;
        u64 dstRem = dstEnd - dstPtr;
        u64 avail = (srcRem < dstRem) ? srcRem : dstRem;
        u64 blockRem = dctx->tmpInTarget;
        u64 copyLen = (avail > blockRem) ? blockRem : avail;

        memcpy(dstPtr, srcPtr, copyLen);

        if (dctx->frameInfo.blockChecksumFlag != 0)
            FUN_710399ee20(&dctx->blockChecksum, srcPtr, copyLen);
        if (dctx->frameInfo.contentChecksumFlag != 0)
            FUN_710399ee20(&dctx->xxh, srcPtr, copyLen);
        if (dctx->frameInfo.contentSize != 0)
            dctx->frameRemainingSize -= copyLen;

        if (dctx->frameInfo.blockMode == 0)
            lz4f_update_window_copy(dctx, dstPtr, (u8*)dstBuffer, srcPtr, copyLen);

        u8* nextSrc = srcPtr + copyLen;
        dstPtr += copyLen;
        u64 newRem = dctx->tmpInTarget - copyLen;
        if (newRem != 0) {
            dctx->tmpInTarget = newRem;
            hint = newRem + (u64)((u32)(dctx->frameInfo.contentChecksumFlag) << 2);
            srcPtr = nextSrc;
            goto return_exit;
        }
        srcPtr = nextSrc;
        if (dctx->frameInfo.blockChecksumFlag == 0) {
            dctx->dStage = 3;
        } else {
            dctx->tmpInSize = 0;
            dctx->dStage = 6;
        }
        goto next_stage;
    }

    // ---- Stage 6: getBlockChecksum ----
    case 6: {
        u64 copyDone = dctx->tmpInSize;
        u64 remaining = srcEnd - srcPtr;
        if (remaining >= 4 && copyDone == 0) {
            u8* nextSrc = srcPtr + 4;
            u32 stored = *(u32*)srcPtr;
            u32 computed = FUN_710399efc0(&dctx->blockChecksum);
            if (stored != computed) { hint = 0xb; goto do_lookup; }
            dctx->dStage = 3;
            srcPtr = nextSrc;
            goto next_stage;
        }
        u64 need = 4 - copyDone;
        u64 copyLen = (remaining < need) ? remaining : need;
        memcpy(dctx->header + copyDone, srcPtr, copyLen);
        u64 newSize = copyLen + dctx->tmpInSize;
        u8* nextSrc = srcPtr + copyLen;
        dctx->tmpInSize = newSize;
        if (newSize < 4) {
            hint = 1;
            srcPtr = nextSrc;
            goto return_exit;
        }
        {
            u32 stored = *(u32*)dctx->header;
            u32 computed = FUN_710399efc0(&dctx->blockChecksum);
            if (stored != computed) { hint = 0xb; goto do_lookup; }
        }
        dctx->dStage = 3;
        srcPtr = nextSrc;
        goto next_stage;
    }

    // ---- Stage 7: getCBlock (compressed block) ----
    case 7: {
        blockTarget = dctx->tmpInTarget;
        remaining = srcEnd - srcPtr;
        if (blockTarget <= remaining) {
            bcFlag = dctx->frameInfo.blockChecksumFlag;
            nextSrc = srcPtr + blockTarget;
            blockData = srcPtr;
            goto do_decompress;
        }
        dctx->tmpInSize = 0;
        dctx->dStage = 8;
        goto next_stage;
    }

    // ---- Stage 8: storeCBlock ----
    case 8: {
        copyDone = dctx->tmpInSize;
        target = dctx->tmpInTarget;
        remaining = srcEnd - srcPtr;
        need = target - copyDone;
        copyLen = (remaining < need) ? remaining : need;

        memcpy(dctx->tmpIn + copyDone, srcPtr, copyLen);
        blockTarget = dctx->tmpInTarget;
        newSize = dctx->tmpInSize + copyLen;
        dctx->tmpInSize = newSize;
        if (newSize < blockTarget) {
            hint = (4 - newSize) + blockTarget;
            srcPtr += copyLen;
            goto return_exit;
        }
        {
            bcFlag = dctx->frameInfo.blockChecksumFlag;
            nextSrc = srcPtr + copyLen;
            blockData = dctx->tmpIn;

        do_decompress:
            srcPtr = nextSrc;
            if (bcFlag != 0) {
                blockTarget -= 4;
                dctx->tmpInTarget = blockTarget;
                s32 stored = *(s32*)(blockData + blockTarget);
                s32 computed = FUN_710399eb90(blockData, blockTarget);
                if (stored != computed) { hint = 0xb; goto do_lookup; }
            }

            u64 maxDecomp = dctx->maxBlockSize;
            u64 dstAvail = dstEnd - dstPtr;
            if (dstAvail < maxDecomp) {
                // Decompress into ring buffer (tmpOut)
                if (dctx->frameInfo.blockMode == 0) {
                    u8* ringBase = dctx->tmpOutBuffer;
                    u8* dictPtr = dctx->dict;
                    u64 dSize = dctx->dictSize;
                    if (dictPtr == ringBase) {
                        if (dSize > 0x20000) {
                            memcpy(dictPtr, dictPtr + (dSize - 0x10000), 0x10000);
                            blockTarget = dctx->tmpInTarget;
                            dictPtr = dctx->tmpOutBuffer;
                            maxDecomp = dctx->maxBlockSize;
                            dctx->dictSize = 0x10000;
                            dSize = 0x10000;
                        }
                        dctx->tmpOut = dictPtr + dSize;
                    } else {
                        u64 capped = dSize;
                        if (dSize > 0xFFFF) capped = 0x10000;
                        dctx->tmpOut = ringBase + capped;
                    }
                } else {
                    // independent mode — reuse existing positions
                }

                u8* dp = dctx->dict;
                u64 ds = dctx->dictSize;
                u8* dictStart; u32 dictLen;
                if (dp != nullptr && ds > 0x40000000ULL) {
                    dictStart = dp + ds - 0x10000;
                    dictLen = 0x10000;
                } else {
                    dictStart = dp;
                    dictLen = (u32)ds;
                }

                s32 decompResult = FUN_710399d850(blockData, dctx->tmpOut,
                                                   (u32)blockTarget, maxDecomp,
                                                   dictStart, dictLen);
                if (decompResult < 0) { hint = 2; goto do_lookup; }

                if (dctx->frameInfo.contentChecksumFlag != 0)
                    FUN_710399ee20(&dctx->xxh, dctx->tmpOut, (u64)(s64)decompResult);
                u64 decompLen = (u64)(s64)decompResult;
                if (dctx->frameInfo.contentSize != 0)
                    dctx->frameRemainingSize -= decompLen;

                u64 flushed = 0;
                dctx->dStage = 9;
                dctx->tmpOutSize = decompLen;
                dctx->tmpOutStart = 0;
                goto do_flush;
            } else {
                // Decompress directly into output buffer
                u8* dp2 = dctx->dict;
                u64 ds2 = dctx->dictSize;
                u8* dictStart2; u32 dictLen2;
                if (dp2 != nullptr && ds2 > 0x40000000ULL) {
                    dictStart2 = dp2 + ds2 - 0x10000;
                    dictLen2 = 0x10000;
                } else {
                    dictStart2 = dp2;
                    dictLen2 = (u32)ds2;
                }

                s32 decompResult = FUN_710399d850(blockData, dstPtr,
                                                   (u32)blockTarget, maxDecomp,
                                                   dictStart2, dictLen2);
                if (decompResult < 0) return 0x80000002;

                if (dctx->frameInfo.contentChecksumFlag != 0)
                    FUN_710399ee20(&dctx->xxh, dstPtr, (u64)(s64)decompResult);
                u64 decompLen = (u64)(s64)decompResult;
                if (dctx->frameInfo.contentSize != 0)
                    dctx->frameRemainingSize -= decompLen;

                if (dctx->frameInfo.blockMode == 0)
                    lz4f_update_window_copy(dctx, dstPtr, (u8*)dstBuffer, dstPtr, decompLen);
                dstPtr += decompLen;
            }
        }
        dctx->dStage = 3;
        goto next_stage;
    }

    // ---- Stage 9: flushOut ----
    case 9: {
        dstAvail = dstEnd - dstPtr;
        totalDecoded = dctx->tmpOutSize;
        alreadyFlushed = dctx->tmpOutStart;
    do_flush:
        flushRem = totalDecoded - alreadyFlushed;
        copyLen = (dstAvail < flushRem) ? dstAvail : flushRem;

        memcpy(dstPtr, dctx->tmpOut + alreadyFlushed, copyLen);

        if (dctx->frameInfo.blockMode == 0)
            lz4f_update_window_flush(dctx, dstPtr, (u8*)dstBuffer, copyLen);

        u64 newFlushed = dctx->tmpOutStart + copyLen;
        dstPtr += copyLen;
        dctx->tmpOutStart = newFlushed;
        if (newFlushed != dctx->tmpOutSize) {
            hint = 4;
            goto return_exit;
        }
        dctx->dStage = 3;
        goto next_stage;
    }

    // ---- Stage 10: getSuffix ----
    case 10: {
        if (dctx->frameRemainingSize != 0) { hint = 4; goto do_lookup; }
        if (dctx->frameInfo.contentChecksumFlag == 0) {
            hint = 0;
            dctx->dStage = 0;
            dctx->dict = nullptr;
            dctx->dictSize = 0;
            goto return_final;
        }
        u64 remaining = srcEnd - srcPtr;
        if (remaining >= 4) {
            u8* nextSrc = srcPtr + 4;
            u32 stored = *(u32*)srcPtr;
            u32 computed = FUN_710399efc0(&dctx->xxh);
            if (stored != computed) { hint = 0; goto do_lookup; }
            hint = 0;
            dctx->dStage = 0;
            dctx->dict = nullptr;
            dctx->dictSize = 0;
            srcPtr = nextSrc;
            goto return_final;
        }
        dctx->tmpInSize = 0;
        dctx->dStage = 11;
        goto do_store_suffix;
    }

    // ---- Stage 11: storeSuffix ----
    case 11: {
        copyDone = dctx->tmpInSize;
        remaining = srcEnd - srcPtr;
    do_store_suffix:
        need = 4 - copyDone;
        copyLen = (remaining < need) ? remaining : need;
        memcpy(dctx->tmpIn + copyDone, srcPtr, copyLen);
        u64 newSize = dctx->tmpInSize + copyLen;
        u8* nextSrc = srcPtr + copyLen;
        dctx->tmpInSize = newSize;
        if (newSize < 4) {
            hint = 4 - newSize;
            srcPtr = nextSrc;
            goto return_exit;
        }
        {
            u32 stored = *(u32*)dctx->tmpIn;
            u32 computed = FUN_710399efc0(&dctx->xxh);
            if (stored != computed) { hint = 0; goto do_lookup; }
        }
        hint = 0;
        dctx->dStage = 0;
        dctx->dict = nullptr;
        dctx->dictSize = 0;
        srcPtr = nextSrc;
        goto return_final;
    }

    // ---- Stage 12: getSFrameSize ----
    case 12: {
        remaining = srcEnd - srcPtr;
        if (remaining >= 4) {
            parseBuf = srcPtr;
            nextSrc = srcPtr + 4;
            srcPtr = nextSrc;
            goto parse_sframe_size;
        }
        dctx->tmpInSize = 4;
        dctx->tmpInTarget = 8;
        copyDone = 4;
        target = 8;
        dctx->dStage = 13;
        copyDst = dctx->header + 4;
        goto do_store_sframe;
    }

    // ---- Stage 13: storeSFrameSize ----
    case 13: {
        copyDone = dctx->tmpInSize;
        target = dctx->tmpInTarget;
        remaining = srcEnd - srcPtr;
        copyDst = dctx->header + copyDone;
    do_store_sframe:
        need = target - copyDone;
        copyLen = (remaining < need) ? remaining : need;
        memcpy(copyDst, srcPtr, copyLen);
        newSize = copyLen + dctx->tmpInSize;
        nextSrc = srcPtr + copyLen;
        hint = dctx->tmpInTarget - newSize;
        dctx->tmpInSize = newSize;
        if (dctx->tmpInTarget > newSize && hint != 0) {
            srcPtr = nextSrc;
            goto return_exit;
        }
        parseBuf = dctx->header + 4;

    parse_sframe_size:;
        {
            u64 skipSize = (u64)*(u32*)parseBuf;
            dctx->frameInfo.contentSize = skipSize;
            dctx->tmpInTarget = skipSize;
            dctx->dStage = 14;
            srcPtr = nextSrc;
            goto next_stage;
        }
    }

    // ---- Stage 14: skipSkippable ----
    case 14: {
        u64 skipRem = dctx->tmpInTarget;
        u64 srcRem = srcEnd - srcPtr;
        u64 skipLen = (srcRem < skipRem) ? srcRem : skipRem;
        srcPtr += skipLen;
        u64 newRem = skipRem - skipLen;
        dctx->tmpInTarget = newRem;
        if (newRem != 0) goto return_final;
        dctx->dStage = 0;
        dctx->dict = nullptr;
        dctx->dictSize = 0;
        goto return_final;
    }

    default:
        goto next_stage;
    } // end switch

    // ---- Return paths ----

return_exit:
    // When blockMode == linked, consolidate ring buffer if dict pointer drifted
    if (dctx->frameInfo.blockMode == 0) {
        u8* ringBase = dctx->tmpOutBuffer;
        u8* dictPtr = dctx->dict;
        if (dictPtr != ringBase) {
            u32 stage = dctx->dStage;
            if (stage >= 2 && stage <= 9) {
                if (stage == 9) {
                    u64 tmpOutOff = (u64)(dctx->tmpOut - ringBase);
                    u64 outTotal = dctx->tmpOutSize;
                    u64 window = outTotal;
                    if (outTotal < 0x10001) window = 0x10000;
                    u64 backCopy = window - outTotal;
                    if (backCopy > tmpOutOff) backCopy = tmpOutOff;
                    if (backCopy != 0) {
                        memcpy(ringBase + (tmpOutOff - backCopy),
                               dictPtr + (dctx->dictSize - dctx->tmpOutStart) - backCopy,
                               backCopy);
                        ringBase = dctx->tmpOutBuffer;
                    }
                    dctx->dict = ringBase;
                    dctx->dictSize = dctx->tmpOutStart + tmpOutOff;
                } else {
                    u64 dSize = dctx->dictSize;
                    u64 keep = dSize;
                    if (dSize > 0xFFFF) keep = 0x10000;
                    if (keep != 0) {
                        memcpy(ringBase, dictPtr + dSize - keep, keep);
                        ringBase = dctx->tmpOutBuffer;
                    }
                    dctx->dict = ringBase;
                    dctx->dictSize = keep;
                    dctx->tmpOut = ringBase + keep;
                }
            }
        }
    }

    {
        u64 consumed = (u64)(srcPtr - srcBuffer);
        u64 produced = (u64)(dstPtr - (u8*)dstBuffer);
        u64 total_hint = hint + 18;
        if (total_hint > 0x10) {
            if (hint > (u64)(-20)) return 0x80000002;
            *srcSizePtr = consumed;
            *dstSizePtr = produced;
            return (u32)(hint != 0);
        }
        goto do_lookup;
    }

return_final:
    {
        hint = 0;
        dctx->dStage = 0;
        dctx->dict = nullptr;
        dctx->dictSize = 0;
        goto return_exit;
    }

return_progress_zero:
    {
        *srcSizePtr = 0;
        *dstSizePtr = 0;
        return (u32)(hint != 0);
    }

return_decode_error:
    {
        hint = 0;
        *srcSizePtr = 0;
        *dstSizePtr = 0;
        u64 total_hint = hint + 18;
        goto do_lookup;
    }

do_lookup:
    {
        u32 bitmask = 0x11CE3;
        u32 idx = (u32)hint;
        if (((bitmask >> (idx & 0x1F)) & 1) == 0) return 0x80000002;
        return DAT_7104560990[idx];
    }
}

// ============================================================================
// FUN_71035456D0 — directory_load_dispatch
// Directory loading dispatch with 4-case switch. Resolves directory data
// through ARC tables, checks directory loading state, seeks to file data,
// and performs double-buffered I/O read with semaphore synchronization.
// [derived: Ghidra 13.0.1 decompilation of FUN_7103544CA0 — same function,
//  address shifted between 13.0.1 and 13.0.4]
// [derived: called from ResLoadingThread directory loading path]
//
// Parameters:
//   svc:      ResServiceNX* — service state
//   file:     FileNX** — data_arc_filenx handle
//   dir_idx:  directory index to load
//   mode:     0=standard, 1=sub-directory, 2=locale-aware, 3=chained
//   extra:    extra parameter (directory index for state tracking)
//
// Returns: 1 on success, 0 on failure
//
// Address: 0x71035456D0, Size: 1,940 bytes
// ============================================================================
extern "C" u64 FUN_71035456d0(ResServiceNX* svc, FileNX** file, u32 dir_idx, u32 mode, u32 extra) {
    if (mode > 3) return 0;

    FilesystemInfo* fs = svc->filesystem_info;
    LoadedArc* arc = ((PathInformation*)fs->path_info)->arc;
    DirInfo* dir_infos = arc->dir_infos;
    DirInfo* di = &dir_infos[dir_idx];
    DirectoryOffset* folder_offsets = arc->folder_offsets;

    LoadedDirectory* target_dir = nullptr;
    DirectoryOffset* dir_offset = nullptr;
    u32 file_info_start = 0;
    u32 file_count = 0;
    u32 tracking_dir_idx = 0xffffff;
    u32 read_type = 0;

    switch (mode) {
    case 0: {
        // Standard directory load
        u8 flags_byte = *(u8*)((u8*)di + 0x33);
        if ((flags_byte >> 4) & 1) return 1;  // already handled

        dir_offset = &folder_offsets[di->path.raw >> 40];

        // Get loaded directory
        if (dir_idx == 0xffffff || fs->loaded_directory_len <= dir_idx) {
            target_dir = nullptr;
        } else {
            void* mtx = fs->mutex;
            lock_71039c1490(mtx);
            LoadedDirectory* dirs = fs->loaded_directories;
            target_dir = nullptr;
            if (dirs[dir_idx].flags & 1) {
                target_dir = &dirs[dir_idx];
            }
            unlock_71039c14a0(mtx);
        }

        file_info_start = di->file_info_start_index;
        file_count = di->file_count;
        tracking_dir_idx = 0xffffff;
        read_type = 0;
        if (target_dir == nullptr) return 0;
        break;
    }
    case 1: {
        // Sub-directory load — follow directory_index from folder_offsets
        u32 folder_dir_idx = folder_offsets[di->path.raw >> 40].directory_index;

        u8 flags_byte = *(u8*)((u8*)&dir_infos[dir_idx] + 0x33);
        if (folder_dir_idx == 0xffffff && (flags_byte & 3) != 0) return 1;

        bool use_subdir = (flags_byte >> 4) & 1;

        DirInfo* target_di;
        u64 folder_idx;

        if (use_subdir) {
            target_di = &dir_infos[folder_dir_idx];
            file_info_start = target_di->file_info_start_index;
            file_count = target_di->file_count;
            folder_idx = target_di->path.raw >> 40;
        } else {
            DirectoryOffset* fo = &folder_offsets[folder_dir_idx];
            u32 sub_dir_idx = fo->directory_index;
            file_info_start = fo->file_start_index;
            file_count = fo->file_count;
            folder_idx = folder_dir_idx;
        }

        read_type = use_subdir ? 0 : 1;

        if (folder_dir_idx == 0xffffff || fs->loaded_directory_len <= folder_dir_idx) {
            return 0;
        }

        void* mtx = fs->mutex;
        lock_71039c1490(mtx);
        LoadedDirectory* dirs = fs->loaded_directories;
        u8 dir_flags = dirs[folder_dir_idx].flags;
        unlock_71039c14a0(mtx);

        if (!(dir_flags & 1)) return 0;

        dir_offset = &folder_offsets[folder_idx];
        target_dir = &fs->loaded_directories[folder_dir_idx];
        tracking_dir_idx = folder_dir_idx;
        break;
    }
    case 2: {
        // Locale-aware resolution with hash lookup
        u8 locale_type = *(u8*)((u8*)di + 0x33) & 3;
        u64 folder_idx;

        if (locale_type == 2) {
            u32 ridx = DAT_7105331f28->region_idx;
            s32 adj = (ridx != 0xffffffff) ? (s32)ridx + 1 : 1;
            folder_idx = adj + (u32)(di->path.raw >> 40);
        } else if (locale_type == 1) {
            u32 lidx = DAT_7105331f28->language_idx;
            s32 adj = (lidx != 0xffffffff) ? (s32)lidx + 1 : 1;
            folder_idx = adj + (u32)(di->path.raw >> 40);
        } else {
            folder_idx = di->path.raw >> 40;
        }

        dir_offset = &folder_offsets[folder_idx];
        u64 hash40 = di->path.raw & 0xFFFFFFFFFFULL;

        if (hash40 == 0) {
            target_dir = nullptr;
        } else {
            // Binary search in dir_hash_to_info_index
            HashToIndex* hash_table = arc->dir_hash_to_info_index;
            u32 table_size = arc->fs_header->folder_count;
            HashToIndex* end = hash_table + table_size;
            HashToIndex* cur = hash_table;

            if (table_size != 0) {
                do {
                    u64 half = table_size;
                    if ((s64)table_size < 0) half = table_size + 1;
                    half >>= 1;
                    HashToIndex* mid = cur + half + 1;
                    u64 remaining = table_size + ~half;
                    if (hash40 <= (cur[half].raw & 0xFFFFFFFFFFULL)) {
                        mid = cur;
                        remaining = half;
                    }
                    cur = mid;
                    table_size = (u32)remaining;
                } while (table_size != 0);
            }

            if (cur == end || (cur->raw & 0xFFFFFFFFFFULL) != hash40) {
                target_dir = nullptr;
            } else {
                u32 found_idx = (u32)(cur->raw >> 32) >> 8;
                if (found_idx == 0xffffff || fs->loaded_directory_len <= found_idx) {
                    target_dir = nullptr;
                } else {
                    void* mtx = fs->mutex;
                    lock_71039c1490(mtx);
                    LoadedDirectory* dirs = fs->loaded_directories;
                    target_dir = nullptr;
                    if (dirs[found_idx].flags & 1) {
                        target_dir = &dirs[found_idx];
                    }
                    unlock_71039c14a0(mtx);
                }
            }
        }

        file_info_start = di->file_info_start_index;
        file_count = di->file_count;
        read_type = 2;
        tracking_dir_idx = 0xffffff;
        break;
    }
    case 3: {
        // Chained directory — follow through two levels with locale
        u8 flags_byte = *(u8*)((u8*)di + 0x33);
        u8 locale_type = flags_byte & 3;
        u64 folder_idx = di->path.raw >> 40;

        if (locale_type == 2) {
            u32 ridx = DAT_7105331f28->region_idx;
            s32 adj = (ridx != 0xffffffff) ? (s32)ridx + 1 : 1;
            folder_idx = adj + (u32)(di->path.raw >> 40);
        } else if (locale_type == 1) {
            u32 lidx = DAT_7105331f28->language_idx;
            s32 adj = (lidx != 0xffffffff) ? (s32)lidx + 1 : 1;
            folder_idx = adj + (u32)(di->path.raw >> 40);
        }

        if (folder_offsets[folder_idx].directory_index == 0xffffff ||
            (flags_byte & 0x14) != 0x14) {
            return 1;
        }

        // Follow to sub-directory
        u32 sub_dir_idx = folder_offsets[di->path.raw >> 40].directory_index;
        di = &dir_infos[sub_dir_idx];

        // Apply locale again for sub-directory
        u8 sub_locale = *(u8*)((u8*)di + 0x33) & 3;
        u64 sub_folder_idx;
        if (sub_locale == 2) {
            u32 ridx = DAT_7105331f28->region_idx;
            s32 adj = (ridx != 0xffffffff) ? (s32)ridx + 1 : 1;
            sub_folder_idx = adj + (u32)(di->path.raw >> 40);
        } else if (sub_locale == 1) {
            u32 lidx = DAT_7105331f28->language_idx;
            s32 adj = (lidx != 0xffffffff) ? (s32)lidx + 1 : 1;
            sub_folder_idx = adj + (u32)(di->path.raw >> 40);
        } else {
            sub_folder_idx = di->path.raw >> 40;
        }

        if (sub_dir_idx == 0xffffff || fs->loaded_directory_len <= sub_dir_idx) {
            return 0;
        }

        file_info_start = di->file_info_start_index;
        file_count = di->file_count;

        void* mtx = fs->mutex;
        lock_71039c1490(mtx);
        LoadedDirectory* dirs = fs->loaded_directories;
        u8 dir_flags = dirs[sub_dir_idx].flags;
        unlock_71039c14a0(mtx);

        if (!(dir_flags & 1)) return 0;

        dir_offset = &folder_offsets[sub_folder_idx];
        target_dir = &fs->loaded_directories[sub_dir_idx];
        read_type = 2;
        tracking_dir_idx = sub_dir_idx;
        break;
    }
    }

    // ---- Common path: check directory state and perform I/O ----
    if (target_dir == nullptr) return 0;
    if (!(target_dir->flags & 1)) return 0;

    if (dir_offset->decomp_size == 0 || dir_offset->size == 0) return 1;

    // Lock mutex, reset directory state, check loading state
    void* svc_mtx = svc->mutex;
    lock_71039c1490(svc_mtx);
    FUN_7103541e30(target_dir);

    if (target_dir->file_group_index == 0xffffff ||
        FUN_7103542ad0(target_dir) != 3) {

        if (*(u8*)((u8*)target_dir + 10) == 0) {
            // Directory not ready — clear flags and return
            target_dir->flags &= 0xf9;
            unlock_71039c14a0(svc_mtx);
            return 0;
        }

        unlock_71039c14a0(svc_mtx);

        // ---- Perform file I/O ----
        FileNX* f = *file;
        u32 comp_size = dir_offset->size;
        u32 buf_size = (u32)svc->buffer_size;

        // Seek to data position
        if (*(u8*)((u8*)f + 0x22c) && f->is_open) {
            s64 pos = dir_offset->offset + svc->filesystem_info->loaded_data->arc->file_section_offset;
            f->position = pos;
            if (pos >= 0) {
                s64 fsize = 0;
                FUN_71039c7680(&fsize, *(u64*)&f->file_handle);
            }
        }

        if (svc->is_loader_thread_running) return 0;

        // Double-buffered read loop
        s32 iteration = 0;
        u32 total_read = 0;
        while (true) {
            u32 remaining = comp_size - buf_size;
            u32 to_read = buf_size;
            if (comp_size < buf_size || remaining == 0) {
                to_read = comp_size;
            }

            // Acquire I/O semaphore
            FUN_71039c0740(*(void**)(*(u64*)svc->semaphore1 + 8));

            f = *file;
            if (!*(u8*)((u8*)f + 0x22c) ||
                FUN_71037c58c0(f, svc->buffer_array[(int)svc->buffer_array_idx], (u64)to_read) != (u64)to_read) {
                *(u8*)((u8*)svc + 0xE5) = 1;
                return 1;
            }

            total_read += to_read;

            // Acquire processing semaphore
            FUN_71039c0740(*(void**)(*(u64*)svc->semaphore2 + 8));

            if (iteration == 0) {
                svc->processing_file_idx_start = file_info_start;
                svc->processing_file_idx_curr = 0;
                svc->processing_file_idx_count = file_count;
                svc->offset_into_read = 0;
                svc->processing_dir_idx_start = dir_idx;
                *(u32*)((u8*)svc + 0x23C) = extra;
                svc->current_index = tracking_dir_idx;
                svc->current_dir_index = dir_idx;
                svc->processing_type = read_type;
            }

            svc->offset_into_read = (u64)total_read;
            svc->data_ptr = svc->buffer_array[(int)svc->buffer_array_idx];

            // Signal inflate thread
            void* swap_event = **(void***)svc->io_swap_event;
            if (swap_event != nullptr) {
                FUN_71039c0720(swap_event);
            }

            // Toggle double buffer
            svc->buffer_array_idx = ~svc->buffer_array_idx & 1;

            if (remaining == 0 || comp_size <= buf_size) return 1;
            if (svc->is_loader_thread_running) return 0;

            iteration--;
            comp_size = remaining;
            buf_size = to_read;
        }
    }

    unlock_71039c14a0(svc_mtx);
    return 0;
}

// ============================================================================
// FUN_71035444C0 — ResInflateThread entry point
// Address: 0x71035444C0, Size: 4,608 bytes (0x35444C0–0x35456C0)
// Thread function for ResInflateThread — receives buffered data from the
// loading thread and processes (decompresses/inflates) it into target buffers.
// [derived: DATA xref from FUN_710374f360 (init) at 0x7103751b9c — thread entry]
// [derived: ARCropolis hooks inflate, inflate_dir_file, memcpy_1/2/3 in this function]
//
// Processing types (switch on self->processing_type):
//   0: Directory file data — resolve through file_infos, decompress into LoadedData
//   1: Single file data — same resolution, full decompress path
//   2: Directory with sub-dirs — conditional directory setup
//   3: Similar to type 2 with different resolution
//   4: Raw memcpy — no decompression
//
// For each file index from processing_file_idx_curr to processing_file_idx_count:
//   1. Resolve FileInfo through ARC tables (with locale/region adjustment)
//   2. Get FileData (offset, comp_size, decomp_size, flags)
//   3. Allocate output buffer
//   4. Decompress (zstd streaming, memcpy, or read+decompress)
//   5. Store result in LoadedData entry
// ============================================================================
void FUN_71035444C0(ResServiceNX* self) {
    if (self->is_loader_thread_running) return;

    const u32 SENTINEL = 0xFFFFFF;
    const u32 STREAM_ENTRY_SIZE = 12;

    do {
        // Wait for data from loading thread via io_swap_event
        // [derived: +0x018 io_swap_event is EventType** wrapper]
        void* event = **(void***)self->io_swap_event;
        if (event != nullptr) {
            _ZN2nn2os9WaitEventEPNS0_9EventTypeE(event);
        }
        if (self->is_loader_thread_running) return;

        // One-time init: process pending stream releases if filesystem dirty
        // [derived: +0x248 is init_done flag (byte), filesystem_info->unk3 at +0x68]
        u8* init_flag = (u8*)((u8*)self + 0x248);
        if (!*init_flag) {
            FilesystemInfo* fs = self->filesystem_info;
            if (fs->unk3) {
                void* mtx = self->mutex;
                lock_71039c1490(mtx);
                FUN_710353f1b0(self->filesystem_info);
                unlock_71039c14a0(mtx);
            }
            *init_flag = 1;
        }

        // Load processing state from service fields
        u32 processing_type = self->processing_type;
        u8* data_ptr = self->data_ptr;
        u32 file_count = self->processing_file_idx_count;
        u32 file_start = self->processing_file_idx_start;
        u32 file_curr = self->processing_file_idx_curr;
        u32 saved_type = processing_type;

        if (file_curr >= file_count) goto post_process;

        // ================================================================
        // MAIN FILE PROCESSING LOOP
        // Iterates from file_curr to file_count, processing each file
        // ================================================================
        for (; file_curr < file_count; file_curr++) {
            if (self->is_loader_thread_running) return;

            u32 combined_idx = file_start + file_curr;
            u32 proc_type = saved_type;

            // ---- Phase 1: Resolve FileInfo through ARC tables ----
            // The resolution differs based on processing_type but all paths
            // produce: comp_size, decomp_size, offset_in_folder, flags, folder_offset_idx
            FilesystemInfo* fs = self->filesystem_info;
            LoadedArc* arc = ((PathInformation*)fs->path_info)->arc;
            FileInfo* fi_table = arc->file_infos;
            FileInfoToFileData* fitfd_table = arc->file_info_to_datas;
            FileData* fd_table = arc->file_datas;
            DirectoryOffset* fo_table = arc->folder_offsets;

            u32 info_to_data_idx;
            u32 fi_flags;
            u32 folder_offset_idx;
            u32 file_data_idx;
            u32 comp_size;
            u32 decomp_size;
            u32 offset_in_folder;
            u32 fd_flags;
            u32 is_compressed;
            LoadedData* target_entry = nullptr;
            u32 loaded_data_idx_for_entry = 0;

            // Resolve FileInfo at combined_idx and apply locale adjustment
            {
                FileInfo* fi = &fi_table[combined_idx];
                info_to_data_idx = fi->info_to_data_index;
                fi_flags = fi->flags;

                u32 region_type = (fi_flags >> 15) & 3;
                if (region_type == 2) {
                    u32 ridx = DAT_7105331f28->region_idx;
                    u32 adj = (ridx != 0xFFFFFFFF) ? ridx : 0;
                    info_to_data_idx += adj + 1;
                } else if (region_type == 1) {
                    u32 lidx = DAT_7105331f28->language_idx;
                    u32 adj = (lidx != 0xFFFFFFFF) ? lidx : 0;
                    info_to_data_idx += adj + 1;
                }

                // Get FileInfoToFileData entry
                FileInfoToFileData* fitfd = &fitfd_table[info_to_data_idx];
                file_data_idx = fitfd->file_data_index;
                folder_offset_idx = fitfd->folder_offset_index;
            }

            // Handle sentinel file_data_idx
            if (file_data_idx == SENTINEL) {
                // Resolve through stream entries instead
                // [derived: stream_entries at arc+0xC8, 12-byte stride]
                StreamEntry* streams = arc->stream_entries;
                StreamEntry* se = &streams[combined_idx];
                u32 se_idx = se->file_group_index();
                u32 se_region = (se->raw >> 15) & 3;

                if (se_region == 2) {
                    u32 ridx = DAT_7105331f28->region_idx;
                    u32 adj = (ridx != 0xFFFFFFFF) ? ridx : 0;
                    se_idx += adj + 1;
                } else if (se_region == 1) {
                    u32 lidx = DAT_7105331f28->language_idx;
                    u32 adj = (lidx != 0xFFFFFFFF) ? lidx : 0;
                    se_idx += adj + 1;
                }

                FileInfoToFileData* fitfd2 = &fitfd_table[se_idx];
                file_data_idx = fitfd2->file_data_index;
                folder_offset_idx = fitfd2->folder_offset_index;
            }

            // Load file data
            {
                FileData* fd = &fd_table[file_data_idx];
                offset_in_folder = fd->offset_in_folder;
                comp_size = fd->comp_size;
                decomp_size = fd->decomp_size;
                fd_flags = fd->flags;
                is_compressed = fd_flags & 7;
            }

            // Get decomp_size — if zero, load from filesystem header
            u32 actual_decomp_size = decomp_size & 0x7FFF;
            if (actual_decomp_size == 0) {
                // Load default from loaded_data->arc->uncompressed_fs
                LoadedArc* arc2 = ((PathInformation*)fs->path_info)->arc;
                FileSystemHeader* hdr = arc2->uncompressed_fs;
                actual_decomp_size = hdr->file_data_count; // placeholder
            }

            u32 file_offset = offset_in_folder << 2;
            u32 aligned_decomp = (comp_size + 15) & ~15u;
            u32 actual_comp = comp_size;

            // ---- Phase 2: Check LoadedData target (for types 1,3) ----
            // [derived: LoadedData access via filesystem_info for file types]
            if (proc_type == 1 || proc_type == 3) {
                // Check LoadedData entry validity
                if (target_entry != nullptr) {
                    s32 refcount = (s32)__atomic_load_n(&target_entry->ref_count, __ATOMIC_ACQUIRE);
                    if (refcount >= 1) {
                        u8 state = __atomic_load_n(&target_entry->state, __ATOMIC_ACQUIRE);
                        if (state != 0 && target_entry->data != nullptr) {
                            __atomic_store_n(&target_entry->state, 3, __ATOMIC_RELEASE);
                        }
                    }
                }
            }

            // ---- Phase 3: Process data based on type ----
            bool error_flag = false;

            switch (proc_type) {
            case 0: {
                // Simple flag set — used for directory data
                error_flag = (folder_offset_idx != 0);
                break;
            }
            case 1: {
                // Full decompress path with allocation
                if (target_entry == nullptr) goto next_file;
                if (folder_offset_idx == 0) goto next_file;

                // Allocate output buffer
                u64 alloc_size = actual_decomp_size;
                if (alloc_size == 0) alloc_size = 1;
                void* out_buf = je_aligned_alloc(0x10, alloc_size);
                if (out_buf == nullptr) {
                    // OOM retry
                    if (DAT_7105331f00 != nullptr) {
                        s32 oom_flags = 0;
                        s64 oom_size = (s64)alloc_size;
                        u64 r = ((u64(*)(s64*, s32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                 (DAT_7105331f00, &oom_flags, &oom_size);
                        if ((r & 1) != 0) {
                            out_buf = je_aligned_alloc(0x10, alloc_size);
                        }
                    }
                    if (out_buf == nullptr) goto next_file;
                }

                // Store buffer pointer
                target_entry->data = (u8*)out_buf;
                target_entry->flags &= ~0x40;

                // Dispatch on compression type
                u64 end_offset = file_offset + actual_comp;
                u64 avail = self->offset_into_read;

                if (is_compressed == 0) {
                    // Uncompressed: memcpy
                    if (end_offset <= avail) {
                        memcpy(out_buf, data_ptr + file_offset, actual_comp);
                    } else {
                        // Chunked read with semaphore sync
                        u64 chunk = avail - file_offset;
                        memcpy(out_buf, data_ptr + file_offset, chunk);
                        u64 remaining = actual_comp - chunk;
                        u8* dst = (u8*)out_buf + chunk;
                        u64 src_offset = file_offset + chunk;

                        while (remaining > 0) {
                            _ZN2nn2os16ReleaseSemaphoreEPNS0_13SemaphoreTypeE(
                                *(void**)(*(u64*)self->semaphore2 + 8));
                            _ZN2nn2os16ReleaseSemaphoreEPNS0_13SemaphoreTypeE(
                                *(void**)(*(u64*)self->semaphore1 + 8));
                            if (self->is_loader_thread_running) return;
                            event = **(void***)self->io_swap_event;
                            if (event != nullptr) {
                                _ZN2nn2os9WaitEventEPNS0_9EventTypeE(event);
                            }
                            data_ptr = self->data_ptr;
                            avail = self->offset_into_read;
                            u64 this_chunk = avail - src_offset;
                            if (this_chunk > remaining) this_chunk = remaining;
                            _ZN2nn2os11YieldThreadEv();
                            memcpy(dst, data_ptr, this_chunk);
                            dst += this_chunk;
                            remaining -= this_chunk;
                            src_offset += this_chunk;
                        }
                    }
                } else if (is_compressed == 3) {
                    // zstd compressed: streaming decompress
                    // Allocate decompression context (80 bytes)
                    void* decomp_ctx = je_aligned_alloc(0x10, 80);
                    if (decomp_ctx == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            s32 oom_flags = 0;
                            s64 oom_size = 80;
                            u64 r = ((u64(*)(s64*, s32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                     (DAT_7105331f00, &oom_flags, &oom_size);
                            if ((r & 1) != 0) {
                                decomp_ctx = je_aligned_alloc(0x10, 80);
                            }
                        }
                        if (decomp_ctx == nullptr) decomp_ctx = nullptr;
                    }

                    // Zero out context
                    memset(decomp_ctx, 0, 80);
                    *(void**)((u8*)decomp_ctx + 64) = nullptr;  // sp+64

                    // Allocate ZSTD DStream (256 bytes)
                    void* dstream = je_aligned_alloc(0x10, 256);
                    if (dstream == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            s32 oom_flags = 0;
                            s64 oom_size = 256;
                            u64 r = ((u64(*)(s64*, s32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                     (DAT_7105331f00, &oom_flags, &oom_size);
                            if ((r & 1) != 0) {
                                dstream = je_aligned_alloc(0x10, 256);
                            }
                        }
                        if (dstream == nullptr) goto next_file;
                    }

                    // Init and decompress
                    // ... streaming decompression loop ...
                    // (complex state machine, placeholder)
                    break;
                } else {
                    // Other compression types
                    // Allocate small context (16 bytes)
                    void* ctx = je_aligned_alloc(0x10, 16);
                    if (ctx == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            s32 oom_flags = 0;
                            s64 oom_size = 16;
                            u64 r = ((u64(*)(s64*, s32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                     (DAT_7105331f00, &oom_flags, &oom_size);
                            if ((r & 1) != 0) {
                                ctx = je_aligned_alloc(0x10, 16);
                            }
                        }
                        if (ctx == nullptr) ctx = nullptr;
                    }
                    // Init and read+decompress
                    break;
                }
                break;
            }
            case 2:
            case 3: {
                // Conditional decompress
                if (folder_offset_idx == 0 && !error_flag) goto next_file;
                break;
            }
            case 4: {
                // Raw data — no decompression needed
                if (folder_offset_idx != 0) goto next_file;
                break;
            }
            default:
                break;
            }

            // Write back result state
            if (target_entry != nullptr) {
                u8 final_state;
                if (*(u8*)((u8*)self + 0xE5)) {  // error occurred
                    final_state = 3;
                } else {
                    final_state = (u8)-1;  // 0xFF = error
                }
                __atomic_store_n(&target_entry->state, final_state, __ATOMIC_RELEASE);
            }

            // Advance position
            data_ptr += aligned_decomp;
            _ZN2nn2os11YieldThreadEv();

        next_file:;
        }

    post_process:
        // ================================================================
        // POST-PROCESSING: update directory loading states
        // [derived: checks current_index (+0x240) and processing_dir_idx_start (+0x238)]
        // ================================================================
        {
            u32 cur_idx = self->current_index;
            if (cur_idx != SENTINEL) {
                FilesystemInfo* fs = self->filesystem_info;
                u32 dir_data_idx = self->current_index;
                if (dir_data_idx != SENTINEL && dir_data_idx < fs->loaded_directory_len) {
                    void* fs_mtx = fs->mutex;
                    lock_71039c1490(fs_mtx);
                    LoadedDirectory* dirs = fs->loaded_directories;
                    u8 dir_flags = dirs[dir_data_idx].flags;
                    unlock_71039c14a0(fs_mtx);

                    if ((dir_flags & 1) && &dirs[dir_data_idx] != nullptr) {
                        if (*(u8*)((u8*)self + 0xE5)) {
                            // Error: set state to -1
                            u8* state_ptr = &dirs[dir_data_idx].state;
                            __atomic_load_n(state_ptr, __ATOMIC_ACQUIRE);
                            __atomic_store_n(state_ptr, (u8)-1, __ATOMIC_RELEASE);
                        } else {
                            FUN_7103541e30(&dirs[dir_data_idx]);
                        }
                    }
                }

                // Check processing_dir_idx_single (+0x23C)
                u32 dir_single = self->processing_dir_idx_single;
                if (dir_single != SENTINEL) {
                    FilesystemInfo* fs2 = self->filesystem_info;
                    u32 dir_idx2 = self->processing_dir_idx_single;
                    if (dir_idx2 != SENTINEL && dir_idx2 < fs2->loaded_directory_len) {
                        void* fs_mtx2 = fs2->mutex;
                        lock_71039c1490(fs_mtx2);
                        LoadedDirectory* dirs2 = fs2->loaded_directories;
                        u8 dir_flags2 = dirs2[dir_idx2].flags;
                        unlock_71039c14a0(fs_mtx2);

                        if ((dir_flags2 & 1) && &dirs2[dir_idx2] != nullptr) {
                            if (*(u8*)((u8*)self + 0xE5)) {
                                u8* state_ptr2 = &dirs2[dir_idx2].state;
                                __atomic_load_n(state_ptr2, __ATOMIC_ACQUIRE);
                                __atomic_store_n(state_ptr2, (u8)-1, __ATOMIC_RELEASE);
                            } else {
                                u32 fg_idx = dirs2[dir_idx2].file_group_index;
                                if (fg_idx != SENTINEL) {
                                    s32 load_state = FUN_7103542ad0(&dirs2[dir_idx2]);
                                    if (load_state == 2) {
                                        FUN_7103541e30(&dirs2[dir_idx2]);
                                    }
                                }
                            }
                        }
                    }
                }

                // Check processing_dir_idx_start (+0x238)
                if (!*(u8*)((u8*)self + 0xE5)) {
                    u32 saved_proc = saved_type;
                    if ((saved_proc | 2) == 2) {
                        FilesystemInfo* fs3 = self->filesystem_info;
                        u32 dir_idx3 = self->processing_dir_idx_start;
                        if (dir_idx3 != SENTINEL && dir_idx3 < fs3->loaded_directory_len) {
                            void* fs_mtx3 = fs3->mutex;
                            lock_71039c1490(fs_mtx3);
                            LoadedDirectory* dirs3 = fs3->loaded_directories;
                            u8 dir_flags3 = dirs3[dir_idx3].flags;
                            unlock_71039c14a0(fs_mtx3);

                            if ((dir_flags3 & 1) && &dirs3[dir_idx3] != nullptr) {
                                u8* flags_byte = &dirs3[dir_idx3].flags;
                                if (saved_proc == 0) {
                                    *flags_byte |= 0x02;
                                } else {
                                    *flags_byte |= 0x04;
                                }
                            }
                        }
                    }
                }
            }

            // Clear init flag and signal semaphores
            *init_flag = 0;
            _ZN2nn2os16ReleaseSemaphoreEPNS0_13SemaphoreTypeE(
                *(void**)(*(u64*)self->semaphore2 + 8));
            _ZN2nn2os16ReleaseSemaphoreEPNS0_13SemaphoreTypeE(
                *(void**)(*(u64*)self->semaphore1 + 8));
        }
    } while (!self->is_loader_thread_running);
}
