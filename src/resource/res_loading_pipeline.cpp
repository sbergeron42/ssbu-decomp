// res_loading_pipeline.cpp — Loading pipeline functions for resource service
// Pool-c assignment: functions in the 0x7103540xxx-0x7103542xxx range
// These are filesystem/directory/filepath management and loading helpers.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// PLT stubs for std::__1::recursive_mutex
// [derived: Ghidra shows std::__1::recursive_mutex::lock/unlock at these PLT entries]
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// Memory allocation
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free

// Error handlers
extern "C" [[noreturn]] void __throw_length_error(void*);
extern "C" [[noreturn]] void abort();

// Globals
// [derived: DAT_7105331f20 — global FilesystemInfo* used by all resource helpers]
// [derived: DAT_7105331f28 — global ResServiceNX* used by ARCropolis hooks]
// [derived: DAT_7105331f00 — OOM handler singleton, vtable dispatch at +0x30]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;
__attribute__((visibility("hidden"))) extern ResServiceNX* DAT_7105331f28;

// External functions (defined elsewhere in the binary, not yet decomped)
extern "C" void FUN_710353ff00(void*, u64);
extern "C" void FUN_71035461f0(void*, void*, u32, u32);

// Cross-file references
void FUN_7103540560(FilesystemInfo*, u32);  // defined in res_load_helpers.cpp


// ============================================================================
// FUN_7103540450 — add_idx_to_table1_and_table2
// Adds a filepath index reference. If the filepath is already loaded and its
// data entry is in use, atomically increments the ref count. Otherwise, looks
// up the hash40 from the ARC file path table and calls FUN_710353ff00 to
// register the filepath+hash pair.
// [derived: called from vector resize/push_back helpers during directory loading]
// [derived: FilesystemInfo +0x08=loaded_filepaths, +0x10=loaded_datas, +0x78=path_info]
// [derived: PathInformation.arc at +0x00, LoadedArc.fs_header at +0x40, .file_paths at +0x60]
// Address: 0x7103540450 (272 bytes)
// ============================================================================
extern "C" void FUN_7103540450(FilesystemInfo* fs, u32 filepath_index) {
    if (filepath_index >= fs->loaded_filepath_len) return;

    void* mtx = fs->mutex;
    u64 idx = (u64)filepath_index;
    lock_71039c1490(mtx);

    if (fs->loaded_filepaths[idx].is_loaded != 0) {
        u64 data_idx = (u64)fs->loaded_filepaths[idx].loaded_data_index;
        if (fs->loaded_datas[data_idx].is_used) {
            __atomic_fetch_add(&fs->loaded_datas[data_idx].ref_count, 1, __ATOMIC_ACQ_REL);
            unlock_71039c14a0(mtx);
            return;
        }
    }

    unlock_71039c14a0(mtx);

    if (filepath_index == 0xffffff) return;

    PathInformation* pi = (PathInformation*)fs->path_info;
    LoadedArc* arc = pi->arc;
    u64 hash40;
    if (filepath_index < arc->fs_header->file_info_path_count) {
        hash40 = arc->file_paths[idx].path.raw & 0xFFFFFFFFFFULL;
    } else {
        hash40 = 0;
    }

    lock_71039c1490(mtx);
    FUN_710353ff00(fs, hash40 | (idx << 40));
    unlock_71039c14a0(mtx);
}


// ============================================================================
// FUN_71035427e0 — set_directory_state_recursive
// Locks the resource service mutex, calls FUN_71035461f0 to update this
// directory's state, then recurses through all child folders.
// [derived: LoadedDirectory.child_folders CppVector<LoadedDirectory*> at +0x28]
// [derived: DAT_7105331f28 = global ResServiceNX*, mutex at +0x000]
// Address: 0x71035427e0
// ============================================================================
void FUN_71035427e0(LoadedDirectory* dir, u32 param_2) {
    ResServiceNX* svc = DAT_7105331f28;
    void* mtx = svc->mutex;
    lock_71039c1490(mtx);
    FUN_71035461f0(svc, dir, param_2, 0);
    unlock_71039c14a0(mtx);

    LoadedDirectory** child = dir->child_folders.start;
    LoadedDirectory** child_end = dir->child_folders.end;
    while (child != child_end) {
        FUN_71035427e0(*child, param_2);
        child++;
    }
}


// ============================================================================
// FUN_7103541080 — reserve_filepath_index_vector
// Reallocates a CppVector<u32> of filepath indices to ensure at least new_cap
// elements can fit. Copies existing elements with add_ref (FUN_7103540450)
// and releases old elements (FUN_7103540560) during the transfer.
// [derived: same vector grow pattern as FUN_7103542d80 in res_load_helpers.cpp]
// [derived: sentinel value 0xffffff = invalid filepath index]
// Address: 0x7103541080 (384 bytes)
// ============================================================================
void FUN_7103541080(CppVector<u32>* vec, u64 new_cap) {
    u32* old_start = vec->start;
    if (new_cap <= (u64)(vec->eos - old_start)) return;

    if (new_cap >> 62 != 0) {
        abort();
    }

    u32* old_end = vec->end;
    u64 alloc_size = new_cap * 4;
    if (alloc_size == 0) alloc_size = 1;
    u32* new_buf = (u32*)je_aligned_alloc(0x10, alloc_size);
    if (new_buf == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = (s64)alloc_size;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (new_buf = (u32*)je_aligned_alloc(0x10, alloc_size), new_buf != nullptr))
                goto LAB_after_alloc;
        }
        new_buf = nullptr;
    }
LAB_after_alloc:
    {
        u64 old_byte_count = (u64)((u8*)old_end - (u8*)old_start);
        u32* new_end = (u32*)((u8*)new_buf + (old_byte_count >> 2) * 4);
        u32* new_eos = (u32*)((u8*)new_buf + new_cap * 4);
        u32* dst = new_end;

        if (old_end == old_start) {
            vec->start = new_end;
            vec->end = new_end;
            vec->eos = new_eos;
        } else {
            do {
                dst--;
                *dst = 0xffffff;
                old_end--;
                u32 val = *old_end;
                *dst = val;
                if (val != 0xffffff) {
                    FUN_7103540450(DAT_7105331f20, val);
                }
            } while (old_start != old_end);

            u32* prev_start = vec->start;
            u32* prev_end = vec->end;
            vec->start = dst;
            vec->end = new_end;
            vec->eos = new_eos;

            while (prev_end != prev_start) {
                u32* p = prev_end;
                prev_end = p - 1;
                if (*(p - 1) != 0xffffff) {
                    FUN_7103540560(DAT_7105331f20, *(p - 1));
                    *(p - 1) = 0xffffff;
                }
            }
            old_start = prev_start;
        }

        if (old_start != nullptr) {
            FUN_710392e590(old_start);
        }
    }
}


// ============================================================================
// FUN_7103542b10 — push_filepath_index
// Pushes a filepath index to a LoadedDirectory's child_path_indices vector.
// If the vector has space, writes directly (sentinel init + assign + add_ref).
// Otherwise reallocates with the standard capacity-doubling strategy, copying
// elements with add_ref and releasing old ones.
// [derived: LoadedDirectory.child_path_indices CppVector<u32> at +0x10]
// [derived: fast path stores sentinel 0xffffff then overwrites — matches constructor pattern]
// Address: 0x7103542b10 (528 bytes)
// ============================================================================
void FUN_7103542b10(LoadedDirectory* dir, u32* src) {
    u32* end_ptr = dir->child_path_indices.end;
    if (end_ptr < dir->child_path_indices.eos) {
        // Fast path: space available
        *end_ptr = 0xffffff;
        u32 val = *src;
        *end_ptr = val;
        if (val != 0xffffff) {
            FUN_7103540450(DAT_7105331f20, val);
        }
        dir->child_path_indices.end = end_ptr + 1;
        return;
    }

    // Slow path: reallocation needed
    u64 old_count = (u64)((u8*)end_ptr - (u8*)dir->child_path_indices.start) >> 2;
    u64 new_count = old_count + 1;

    if (new_count >> 62 != 0) {
        __throw_length_error(dir);
    }

    u64 old_cap_bytes = (u64)((u8*)dir->child_path_indices.eos -
                              (u8*)dir->child_path_indices.start);
    u64 new_cap;
    u32* new_buf;

    if ((old_cap_bytes >> 2) < 0x1fffffffffffffffULL) {
        u64 half_cap = old_cap_bytes >> 1;
        new_cap = (new_count <= half_cap) ? half_cap : new_count;
        if (new_cap != 0) {
            if (new_cap >> 62 != 0) {
                abort();
            }
            goto LAB_alloc;
        }
    } else {
        new_cap = 0x3fffffffffffffffULL;
    LAB_alloc:
        ;
    }

    {
        u64 alloc_bytes = new_cap * 4;
        if (alloc_bytes == 0) alloc_bytes = 1;
        new_buf = (u32*)je_aligned_alloc(0x10, alloc_bytes);
        if (new_buf != nullptr) goto LAB_insert;
        if (DAT_7105331f00 != nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = (s64)alloc_bytes;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (new_buf = (u32*)je_aligned_alloc(0x10, alloc_bytes), new_buf != nullptr))
                goto LAB_insert;
        }
    }
    new_buf = nullptr;

LAB_insert:
    {
        u32 val = *src;
        u32* insert_pos = (u32*)((u8*)new_buf + old_count * 4);
        *insert_pos = val;
        if (val != 0xffffff) {
            FUN_7103540450(DAT_7105331f20, val);
        }

        u32* old_start = dir->child_path_indices.start;
        u32* old_end = dir->child_path_indices.end;
        u32* new_end = insert_pos + 1;
        u32* release_end = old_start;

        if (old_end != old_start) {
            do {
                insert_pos--;
                *insert_pos = 0xffffff;
                old_end--;
                u32 v = *old_end;
                *insert_pos = v;
                if (v != 0xffffff) {
                    FUN_7103540450(DAT_7105331f20, v);
                }
            } while (old_start != old_end);
            old_start = dir->child_path_indices.start;
            release_end = dir->child_path_indices.end;
        }

        dir->child_path_indices.start = insert_pos;
        dir->child_path_indices.end = new_end;
        dir->child_path_indices.eos = (u32*)((u8*)new_buf + new_cap * 4);

        while (release_end != old_start) {
            u32* p = release_end;
            release_end = p - 1;
            if (*(p - 1) != 0xffffff) {
                FUN_7103540560(DAT_7105331f20, *(p - 1));
                *(p - 1) = 0xffffff;
            }
        }

        if (old_start != nullptr) {
            FUN_710392e590(old_start);
        }
    }
}
