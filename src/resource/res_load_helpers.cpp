// res_load_helpers.cpp — Sub-functions of the resource loading/inflate processing loop
// Pool-d assignment: functions called from FUN_7103542f30 (res_service_process_loop)
// These are filesystem/directory/filepath management helpers used by ResLoadingThread/ResInflateThread.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// PLT stubs for std::__1::recursive_mutex
// [derived: Ghidra shows std::__1::recursive_mutex::lock/unlock at these PLT entries]
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// Forward declarations for functions in this file and nearby
void FUN_7103540560(FilesystemInfo*, u32);   // release/unload filepath entry (defined below)
extern "C" void FUN_710353eff0(FilesystemInfo*, LoadedDirectory*);  // release loaded directory entry
extern "C" long FUN_7103540860(FilesystemInfo*, u64);   // initialize_loaded_directories
extern "C" void FUN_7103540450(FilesystemInfo*, u32);   // add_idx_to_table1_and_table2
extern "C" void FUN_710353f1b0(FilesystemInfo*);        // process_stream_release

// Allocator and helpers
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free

// SDK
extern "C" long GetCurrentThread();  // nn::os::GetCurrentThread — PLT at 0x71039c0840

// Error handler (libc++ vector overflow)
extern "C" [[noreturn]] void __throw_length_error(void*);

// Global filesystem info singleton
// [derived: DAT_7105331f20 used across all resource helpers, accessed as FilesystemInfo*]
// [derived: +0x00=mutex, +0x40=loaded_directories, +0x48=loaded_directory_len matches FilesystemInfo layout]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// Main thread handle (for is_main_thread check)
// [derived: compared against nn::os::GetCurrentThread() result]
__attribute__((visibility("hidden"))) extern long DAT_7105331f18;

// OOM handler singleton
// [derived: DAT_7105331f00 at 0x7105331f00, 40+ refs in binary, vtable dispatch at +0x30]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// ============================================================================
// FUN_710353d5a0 — release_filepath_index
// If the filepath index is valid (!= 0xffffff), calls unload on it via the
// global FilesystemInfo, then invalidates the index.
// [derived: called before overwriting filepath indices — cleanup pattern]
// Address: 0x710353d5a0 (64 bytes)
// ============================================================================
void FUN_710353d5a0(u32* param_1) {
    if (*param_1 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, *param_1);
        *param_1 = 0xffffff;
    }
}

// ============================================================================
// FUN_7103542ad0 — get_redirected_dir_loading_state_recursive
// Returns the minimum loading state between this directory and its
// redirection chain. Uses atomic acquire load on state byte.
// [derived: LoadedDirectory.state at +0x09, redirection_directory at +0x40]
// [derived: ldarb instruction = __atomic_load_n ACQUIRE]
// Address: 0x7103542ad0 (64 bytes)
// ============================================================================
s32 FUN_7103542ad0(LoadedDirectory* dir) {
    s32 state = (s32)(s8)__atomic_load_n(&dir->state, __ATOMIC_ACQUIRE);
    if (dir->redirection_directory != nullptr) {
        s32 redir_state = FUN_7103542ad0(dir->redirection_directory);
        if (redir_state < state) {
            state = redir_state;
        }
    }
    return state;
}

// ============================================================================
// FUN_7103542d20 — directory_and_child_increment_ref_count
// Atomically increments ref_count for this directory and recursively for
// all child directories in child_folders vector.
// [derived: ldaxr/stlxr pair = __atomic_fetch_add ACQ_REL on ref_count at +0x04]
// [derived: child_folders CppVector<LoadedDirectory*> at +0x28]
// Address: 0x7103542d20 (96 bytes)
// ============================================================================
void FUN_7103542d20(LoadedDirectory* dir) {
    if (dir->file_group_index != 0xffffff) {
        __atomic_fetch_add(&dir->ref_count, 1, __ATOMIC_ACQ_REL);
        LoadedDirectory** child = dir->child_folders.start;
        LoadedDirectory** child_end = dir->child_folders.end;
        while (child != child_end) {
            FUN_7103542d20(*child);
            child++;
        }
    }
}

// ============================================================================
// FUN_710353e150 — release_loaded_directory_index
// If dir_index is valid and in bounds, locks the filesystem mutex,
// releases the directory entry if active (flags & 1), then invalidates the index.
// [derived: loaded_directories at +0x40, loaded_directory_len at +0x48 in FilesystemInfo]
// [derived: LoadedDirectory stride = 0x48, flags at +0x08]
// Address: 0x710353e150 (144 bytes)
// ============================================================================
void FUN_710353e150(u32* param_1) {
    u32 dir_index = *param_1;
    if (dir_index != 0xffffff) {
        FilesystemInfo* fs = DAT_7105331f20;
        if (dir_index < fs->loaded_directory_len) {
            void* mtx = fs->mutex;
            lock_71039c1490(mtx);
            LoadedDirectory* dir = &fs->loaded_directories[dir_index];
            if (dir->flags & 1) {
                FUN_710353eff0(fs, dir);
            }
            unlock_71039c14a0(mtx);
        }
        *param_1 = 0xffffff;
    }
}

// ============================================================================
// FUN_71035407a0 — get_or_init_loaded_directory
// Returns a pointer to the LoadedDirectory at the given index. If it's already
// active (flags & 1), increments its ref count tree. Otherwise, initializes it.
// [derived: bounds check against loaded_directory_len at +0x48]
// [derived: calls FUN_7103542d20 (ref count increment) or FUN_7103540860 (init)]
// Address: 0x71035407a0 (192 bytes)
// ============================================================================
LoadedDirectory* FUN_71035407a0(FilesystemInfo* fs, u32 dir_index) {
    if (dir_index == 0xffffff || fs->loaded_directory_len <= dir_index) {
        return nullptr;
    }

    void* mtx = fs->mutex;
    lock_71039c1490(mtx);
    LoadedDirectory* dir = &fs->loaded_directories[dir_index];
    if (dir->flags & 1) {
        FUN_7103542d20(dir);
        unlock_71039c14a0(mtx);
        if (dir != nullptr) {
            return dir;
        }
    } else {
        unlock_71039c14a0(mtx);
    }

    lock_71039c1490(mtx);
    LoadedDirectory* result = (LoadedDirectory*)FUN_7103540860(fs, (u64)dir_index);
    unlock_71039c14a0(mtx);
    return result;
}

// ============================================================================
// FUN_710353eab0 — move_assign_filepath_pair
// Moves a filepath index from src to dst (releasing dst's old value first),
// then releases dst's directory index. Acts like a move-assignment for a
// { filepath_index, directory_index } pair.
// [derived: calls FUN_7103540560 to release filepath, FUN_710353eff0 to release directory]
// [derived: pattern: release old, assign new, invalidate source]
// Address: 0x710353eab0 (192 bytes)
// ============================================================================
u32* FUN_710353eab0(u32* dst, u32* src) {
    u32 new_filepath = *src;

    // Release dst's old filepath if valid
    if (*dst != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, *dst);
    }
    *dst = new_filepath;
    *src = 0xffffff;

    // Release dst's old directory index if valid
    u32 dir_index = dst[1];
    if (dir_index != 0xffffff) {
        FilesystemInfo* fs = DAT_7105331f20;
        if (dir_index < fs->loaded_directory_len) {
            void* mtx = fs->mutex;
            lock_71039c1490(mtx);
            LoadedDirectory* dir = &fs->loaded_directories[dir_index];
            if (dir->flags & 1) {
                FUN_710353eff0(fs, dir);
            }
            unlock_71039c14a0(mtx);
        }
        dst[1] = 0xffffff;
    }

    return dst;
}

// ============================================================================
// FUN_710353d5e0 — copy_filepath_vector_from_loaded_directory
// Canonical version in res_filesystem.cpp (as FUN_710353d5e0_353d5e0)

// ============================================================================
// FUN_7103542d80 — directory_decrement_ref_count_and_collect
// Atomically decrements ref_count. If it reaches 0, pushes file_group_index
// to a release vector (with vector grow/realloc if needed).
// Recurses through child_folders.
// [derived: ldaxr/stlxr pair = __atomic_fetch_sub ACQ_REL on ref_count at +0x04]
// [derived: child_folders CppVector<LoadedDirectory*> at +0x28]
// [derived: release vector is CppVector<u32> passed as param_2]
// Address: 0x7103542d80 (432 bytes)
// ============================================================================
extern "C" void* memcpy(void*, const void*, u64);

void FUN_7103542d80(LoadedDirectory* dir, CppVector<u32>* release_vec) {
    if (dir->file_group_index == 0xffffff) return;

    __atomic_fetch_sub(&dir->ref_count, 1, __ATOMIC_ACQ_REL);

    if (!((s32)dir->ref_count > 0)) {
        // Push file_group_index to release vector
        u32* vec_end = release_vec->end;
        if (vec_end != release_vec->eos) {
            *vec_end = dir->file_group_index;
            release_vec->end = vec_end + 1;
        } else {
            // Vector grow needed
            u32* old_start = release_vec->start;
            u64 old_byte_count = (u64)((u8*)vec_end - (u8*)old_start);
            u64 new_count = (old_byte_count >> 2) + 1;

            if (new_count >> 62 != 0) {
                __throw_length_error(release_vec);
            }

            u64 old_cap_bytes = (u64)((u8*)release_vec->eos - (u8*)old_start);
            u64 new_cap;
            u32* new_buf;

            if ((old_cap_bytes >> 2) >= 0x1fffffffffffffff) {
                new_cap = 0x3fffffffffffffff;
            } else {
                u64 half_cap = old_cap_bytes >> 1;
                new_cap = (new_count <= half_cap) ? half_cap : new_count;
                if (new_cap == 0) {
                    new_buf = nullptr;
                    goto LAB_insert;
                }
            }

            {
                if (new_cap >> 62 != 0) {
                    // would abort, unreachable in practice
                }
                u64 alloc_size = new_cap * 4;
                if (alloc_size == 0) alloc_size = 1;
                new_buf = (u32*)je_aligned_alloc(0x10, alloc_size);
                if (new_buf == nullptr) {
                    if (DAT_7105331f00 != nullptr) {
                        u32 oom_flags = 0;
                        s64 oom_size = (s64)alloc_size;
                        u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                 (DAT_7105331f00, &oom_flags, &oom_size);
                        if (((r & 1) != 0) &&
                            (new_buf = (u32*)je_aligned_alloc(0x10, alloc_size),
                             new_buf != nullptr))
                            goto LAB_insert;
                    }
                    new_buf = nullptr;
                }
            }
        LAB_insert:
            {
                u32* insert_pos = new_buf + (old_byte_count >> 2);
                *insert_pos = dir->file_group_index;
                if ((s64)old_byte_count > 0) {
                    memcpy(new_buf, old_start, old_byte_count);
                }
                release_vec->start = new_buf;
                release_vec->end = insert_pos + 1;
                release_vec->eos = (u32*)((u8*)new_buf + new_cap * 4);
                if (old_start != nullptr) {
                    FUN_710392e590(old_start);
                }
            }
        }
    }

    // Recurse through child directories
    LoadedDirectory** child = dir->child_folders.start;
    LoadedDirectory** child_end = dir->child_folders.end;
    while (child != child_end) {
        FUN_7103542d80(*child, release_vec);
        child++;
    }
}

// ============================================================================
// FUN_710353cfd0 — is_main_thread
// Returns true if the current thread matches the stored main thread handle.
// [derived: compares nn::os::GetCurrentThread() with DAT_7105331f18]
// Address: 0x710353cfd0 (48 bytes)
// ============================================================================
bool FUN_710353cfd0() {
    long current = GetCurrentThread();
    return DAT_7105331f18 == current;
}

// ============================================================================
// FUN_710353b1c0 — tree_free_recursive
// Recursively frees a binary tree node: left child, right child, then self.
// [derived: post-order traversal with je_free at each node]
// Address: 0x710353b1c0 (64 bytes)
// ============================================================================
void FUN_710353b1c0(void** node) {
    if (node != nullptr) {
        FUN_710353b1c0((void**)node[0]);
        FUN_710353b1c0((void**)node[1]);
        FUN_710392e590(node);
    }
}

// ============================================================================
// FUN_710353fec0 — tree_free_recursive_2
// Recursively frees a binary tree node (identical pattern to FUN_710353b1c0,
// separate function for a different tree type).
// [derived: post-order traversal with je_free at each node]
// Address: 0x710353fec0 (64 bytes)
// ============================================================================
void FUN_710353fec0(void** node) {
    if (node != nullptr) {
        FUN_710353fec0((void**)node[0]);
        FUN_710353fec0((void**)node[1]);
        FUN_710392e590(node);
    }
}

// ============================================================================
// FUN_7103541c00 — alloc_with_oom_retry
// Allocates memory with 8-byte alignment. If allocation fails, invokes
// the OOM handler and retries once.
// [derived: je_aligned_alloc(8, size) with OOM handler pattern]
// [derived: first param is unused (possibly 'this' from caller)]
// Address: 0x7103541c00 (176 bytes)
// ============================================================================
void* FUN_7103541c00(u64 /*unused*/, u64 size) {
    if (size == 0) size = 1;
    void* ptr = je_aligned_alloc(8, size);
    if (ptr == nullptr && DAT_7105331f00 != nullptr) {
        u32 oom_flags = 0;
        s64 oom_size = (s64)size;
        u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                 (DAT_7105331f00, &oom_flags, &oom_size);
        if ((r & 1) == 0) {
            ptr = nullptr;
        } else {
            ptr = je_aligned_alloc(8, size);
        }
    }
    return ptr;
}

// ============================================================================
// FUN_710353eb70 — release_filepath_and_directory_pair
// Releases a filepath index, then a directory index, then the filepath
// index again (redundant third check — original source artifact).
// [derived: same release patterns as FUN_710353d5a0 and FUN_710353e150]
// Address: 0x710353eb70 (208 bytes)
// ============================================================================
void FUN_710353eb70(u32* param_1) {
    // Release first filepath index
    if (*param_1 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, *param_1);
        *param_1 = 0xffffff;
    }

    // Release directory index
    u32 dir_index = param_1[1];
    if (dir_index != 0xffffff) {
        FilesystemInfo* fs = DAT_7105331f20;
        if (dir_index < fs->loaded_directory_len) {
            void* mtx = fs->mutex;
            lock_71039c1490(mtx);
            LoadedDirectory* dir = &fs->loaded_directories[dir_index];
            if (dir->flags & 1) {
                FUN_710353eff0(fs, dir);
            }
            unlock_71039c14a0(mtx);
        }
        param_1[1] = 0xffffff;
    }

    // Release filepath index again (redundant but matches original)
    if (*param_1 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, *param_1);
        *param_1 = 0xffffff;
    }
}

// ============================================================================
// FUN_710353e980 — swap_directory_and_release_filepath
// Swaps the directory index in param_1[1] with a new value. Acquires the new
// directory (increment ref or init), releases the old directory, then releases
// the filepath index at param_1[0].
// [derived: combines get_or_init, increment_ref, release patterns]
// [derived: operates on { filepath_idx, directory_idx } pair struct]
// Address: 0x710353e980 (304 bytes)
// ============================================================================
u32* FUN_710353e980(u32* param_1, u32 new_dir_index) {
    u32 old_dir_index = param_1[1];
    param_1[1] = new_dir_index;

    // Acquire new directory
    if (new_dir_index != 0xffffff) {
        FilesystemInfo* fs = DAT_7105331f20;
        if (new_dir_index < fs->loaded_directory_len) {
            void* mtx = fs->mutex;
            lock_71039c1490(mtx);
            LoadedDirectory* dir = &fs->loaded_directories[new_dir_index];
            if (dir->flags & 1) {
                FUN_7103542d20(dir);
                unlock_71039c14a0(mtx);
            } else {
                unlock_71039c14a0(mtx);
                FUN_71035407a0(fs, new_dir_index);
            }
        }
    }

    // Release old directory
    if (old_dir_index != 0xffffff) {
        FilesystemInfo* fs = DAT_7105331f20;
        if (old_dir_index < fs->loaded_directory_len) {
            void* mtx = fs->mutex;
            lock_71039c1490(mtx);
            LoadedDirectory* dir = &fs->loaded_directories[old_dir_index];
            if (dir->flags & 1) {
                FUN_710353eff0(fs, dir);
            }
            unlock_71039c14a0(mtx);
        }
    }

    // Release filepath index
    if (*param_1 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, *param_1);
        *param_1 = 0xffffff;
    }

    return param_1;
}

// ============================================================================
// FUN_7103540560 — release_filepath_entry
// Decrements ref_count on the LoadedData entry for this filepath. If the ref
// count reaches 0, pushes the filepath index to loaded_filepath_list for
// deferred cleanup. Sets unk3 flag and optionally calls stream release.
// [derived: FilesystemInfo +0x08=loaded_filepaths, +0x10=loaded_datas]
// [derived: loaded_filepath_list CppVector<u32> at +0x28 in FilesystemInfo]
// [derived: LoadedFilepath stride=8, LoadedData stride=0x18]
// [derived: ldaxr/stlxr = __atomic_fetch_sub ACQ_REL on LoadedData.ref_count]
// Address: 0x7103540560 (576 bytes)
// ============================================================================
void FUN_7103540560(FilesystemInfo* fs, u32 filepath_index) {
    void* mtx = fs->mutex;
    lock_71039c1490(mtx);

    LoadedFilepath* fp = &fs->loaded_filepaths[filepath_index];
    if (!fp->is_loaded) {
        unlock_71039c14a0(mtx);
        return;
    }

    u32 data_idx = fp->loaded_data_index;
    LoadedData* data = &fs->loaded_datas[data_idx];
    if (!data->is_used) {
        unlock_71039c14a0(mtx);
        return;
    }

    __atomic_fetch_sub(&data->ref_count, 1, __ATOMIC_ACQ_REL);
    if ((s32)data->ref_count > 0) {
        unlock_71039c14a0(mtx);
        return;
    }

    // Ref count hit 0 — push to release list
    u32* vec_end = fs->loaded_filepath_list.end;
    if (vec_end < fs->loaded_filepath_list.eos) {
        *vec_end = filepath_index;
        fs->loaded_filepath_list.end = vec_end + 1;
    } else {
        // Vector grow
        u32* old_start = fs->loaded_filepath_list.start;
        u64 old_byte_count = (u64)((u8*)vec_end - (u8*)old_start);
        u64 new_count = (old_byte_count >> 2) + 1;

        if (new_count >> 62 != 0) {
            __throw_length_error(fs);
        }

        u64 old_cap_bytes = (u64)((u8*)fs->loaded_filepath_list.eos - (u8*)old_start);
        u64 new_cap;
        u32* new_buf;

        if ((old_cap_bytes >> 2) >= 0x1fffffffffffffff) {
            new_cap = 0x3fffffffffffffff;
        } else {
            u64 half_cap = old_cap_bytes >> 1;
            new_cap = (new_count <= half_cap) ? half_cap : new_count;
            if (new_cap == 0) {
                new_buf = nullptr;
                goto LAB_insert;
            }
        }

        {
            if (new_cap >> 62 != 0) {
                // abort
            }
            u64 alloc_size = new_cap * 4;
            if (alloc_size == 0) alloc_size = 1;
            new_buf = (u32*)je_aligned_alloc(0x10, alloc_size);
            if (new_buf == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_flags = 0;
                    s64 oom_size = (s64)alloc_size;
                    u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_flags, &oom_size);
                    if (((r & 1) != 0) &&
                        (new_buf = (u32*)je_aligned_alloc(0x10, alloc_size),
                         new_buf != nullptr))
                        goto LAB_insert;
                }
                new_buf = nullptr;
            }
        }
    LAB_insert:
        u32* insert_pos = new_buf + (old_byte_count >> 2);
        *insert_pos = filepath_index;
        if ((s64)old_byte_count > 0) {
            memcpy(new_buf, old_start, old_byte_count);
        }
        fs->loaded_filepath_list.start = new_buf;
        fs->loaded_filepath_list.end = insert_pos + 1;
        fs->loaded_filepath_list.eos = (u32*)((u8*)new_buf + new_cap * 4);
        if (old_start != nullptr) {
            FUN_710392e590(old_start);
        }
    }

    fs->unk3 = 1;
    u8 flags = data->flags;
    unlock_71039c14a0(mtx);

    if ((flags >> 6) & 1) {
        FUN_710353f1b0(fs);
    }
}
