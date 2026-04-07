// res_filesystem_utils.cpp — Filesystem utility functions for resource service
// Pool-e assignment: 0x710353xxxx range, resource service filesystem operations

#include "types.h"
#include "resource/ResServiceNX.h"

using namespace resource;

// ---- Globals ----
// [derived: FilesystemInfo* — global resource table pointer, 40+ refs in resource service]
// [derived: field accesses match FilesystemInfo exactly: +0x00=mutex, +0x40=dirs, +0x48=dir_len]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// ---- External functions ----
// [derived: release_loaded_filepath — atomic decrement LoadedData ref_count, push to free list]
extern void FUN_7103540560(FilesystemInfo*, u32);

// [derived: release_loaded_directory entry — decrements ref_count, releases child resources]
extern void FUN_710353eff0(FilesystemInfo*, LoadedDirectory*);

// [derived: activate_loaded_directory — sets up directory for loading if not already active]
extern void FUN_71035407a0(FilesystemInfo*, u32);

// [derived: addref_loaded_directory — increments ref_count on already-active directory]
extern void FUN_7103542d20(LoadedDirectory*);

// [derived: std::__1::recursive_mutex::lock/unlock — PLT stubs at 0x71039c1490/0x71039c14a0]
extern void FUN_71039c1490(void*);
extern void FUN_71039c14a0(void*);

// ============================================================================
// FUN_710353e150 — 0x710353e150 (144 bytes)
// Release directory handle: lock mutex, check flags, unref, unlock, invalidate.
// [derived: accesses FilesystemInfo.loaded_directories (+0x40), count at +0x48]
// [derived: LoadedDirectory.flags (+0x08) bit 0 = active, checked before release]
// [derived: sizeof(LoadedDirectory) = 0x48, confirmed by madd stride in disassembly]
// ============================================================================
void FUN_710353e150(u32* dir_handle) {
    u32 idx = *dir_handle;
    if (idx != 0xFFFFFF) {
        FilesystemInfo* fs_info = DAT_7105331f20;
        if (fs_info->loaded_directory_len > idx) {
            void* mutex = fs_info->mutex;
            FUN_71039c1490(mutex);
            LoadedDirectory* dirs = fs_info->loaded_directories;
            if ((dirs[idx].flags & 1) != 0) {
                FUN_710353eff0(fs_info, &dirs[idx]);
            }
            FUN_71039c14a0(mutex);
        }
        *dir_handle = 0xFFFFFF;
    }
}

// ============================================================================
// FUN_710353eb70 — 0x710353eb70 (208 bytes)
// Full handle destructor: releases filepath, directory, then filepath again.
// Operates on a {u32 filepath_index, u32 directory_index} pair.
// The second filepath release is a base-class destructor pattern.
// [derived: handle[0] = filepath_index, handle[1] = directory_index]
// [derived: directory release is inline copy of FUN_710353e150 logic]
// ============================================================================
void FUN_710353eb70(u32* handle) {
    // Release filepath index
    if (*handle != 0xFFFFFF) {
        FUN_7103540560(DAT_7105331f20, *handle);
        *handle = 0xFFFFFF;
    }
    // Release directory index
    u32 dir_idx = handle[1];
    if (dir_idx != 0xFFFFFF) {
        FilesystemInfo* fs_info = DAT_7105331f20;
        if (fs_info->loaded_directory_len > dir_idx) {
            void* mutex = fs_info->mutex;
            FUN_71039c1490(mutex);
            LoadedDirectory* dirs = fs_info->loaded_directories;
            if ((dirs[dir_idx].flags & 1) != 0) {
                FUN_710353eff0(fs_info, &dirs[dir_idx]);
            }
            FUN_71039c14a0(mutex);
        }
        handle[1] = 0xFFFFFF;
    }
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" ::: "memory");
#endif
    // Release filepath index again (base-class destructor)
    if (*handle != 0xFFFFFF) {
        FUN_7103540560(DAT_7105331f20, *handle);
        *handle = 0xFFFFFF;
    }
}

// ============================================================================
// FUN_710353eab0 — 0x710353eab0 (192 bytes)
// Move-assign filepath: transfers src filepath to dest, releases old dest
// filepath and directory, invalidates src.
// [derived: *src is moved to *dest, then *src set to 0xFFFFFF]
// [derived: dest[1] (old directory) is released with lock/check/unlock pattern]
// [derived: returns dest pointer in x0]
// ============================================================================
u32* FUN_710353eab0(u32* dest, u32* src) {
    u32 new_filepath = *src;
    if (*dest != 0xFFFFFF) {
        FUN_7103540560(DAT_7105331f20, *dest);
    }
    *dest = new_filepath;
    *src = 0xFFFFFF;
    u32 dir_idx = dest[1];
    if (dir_idx != 0xFFFFFF) {
        FilesystemInfo* fs_info = DAT_7105331f20;
        if (fs_info->loaded_directory_len > dir_idx) {
            void* mutex = fs_info->mutex;
            FUN_71039c1490(mutex);
            LoadedDirectory* dirs = fs_info->loaded_directories;
            if ((dirs[dir_idx].flags & 1) != 0) {
                FUN_710353eff0(fs_info, &dirs[dir_idx]);
            }
            FUN_71039c14a0(mutex);
        }
        dest[1] = 0xFFFFFF;
    }
    return dest;
}

// ============================================================================
// FUN_710353e980 — 0x710353e980 (304 bytes) — set_directory_index
// Sets a new directory index on a handle, activating or addref-ing the new
// directory, releasing the old directory and filepath.
// [derived: handle[1] = directory_index, handle[0] = filepath_index]
// [derived: if new dir active (flags & 1): addref via FUN_7103542d20]
// [derived: if new dir not active: activate via FUN_71035407a0]
// [derived: old dir released via FUN_710353eff0 (same pattern as FUN_710353e150)]
// ============================================================================
u32* FUN_710353e980(u32* handle, u32 new_dir) {
    u32 old_dir = handle[1];
    handle[1] = new_dir;

    // Activate/addref new directory
    if (new_dir != 0xFFFFFF) {
        FilesystemInfo* fs_info = DAT_7105331f20;
        if (fs_info->loaded_directory_len > new_dir) {
            void* mutex = fs_info->mutex;
            FUN_71039c1490(mutex);
            LoadedDirectory* dirs = fs_info->loaded_directories;
            if ((dirs[new_dir].flags & 1) == 0) {
                // Not active: unlock first, then activate
                FUN_71039c14a0(mutex);
                FUN_71035407a0(fs_info, new_dir);
            } else {
                // Active: addref, then unlock
                FUN_7103542d20(&dirs[new_dir]);
                FUN_71039c14a0(mutex);
            }
        }
    }

    // Release old directory
    if (old_dir != 0xFFFFFF) {
        FilesystemInfo* fs_info = DAT_7105331f20;
        if (fs_info->loaded_directory_len > old_dir) {
            void* mutex = fs_info->mutex;
            FUN_71039c1490(mutex);
            LoadedDirectory* dirs = fs_info->loaded_directories;
            if ((dirs[old_dir].flags & 1) != 0) {
                FUN_710353eff0(fs_info, &dirs[old_dir]);
            }
            FUN_71039c14a0(mutex);
        }
    }

    // Release filepath
    if (*handle != 0xFFFFFF) {
        FUN_7103540560(DAT_7105331f20, *handle);
        *handle = 0xFFFFFF;
    }

    return handle;
}

// ============================================================================
// FUN_710353d360 — already in fun_easy_final_005.cpp
// FUN_710353d5e0 — SKIPPED after 3 attempts
// copy_filepath_vector_from_loaded_directory (384 bytes)
// Fundamental block ordering mismatch: upstream Clang 8.0.0 places early-exit
// blocks inline while NX Clang puts them at end-of-function. 96 instructions,
// ~15 branch targets affected. Logic verified correct via manual inspection.
// ============================================================================
