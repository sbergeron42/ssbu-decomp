// res_medium_helpers.cpp — Medium-size resource service helper functions
// Pool-b assignment: functions from WORKER.md target list
// Address range: 0x710353a... — 0x710353f...

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"
#include "resource/containers.h"

using namespace resource;

// ---- External function declarations ----

// libc
extern "C" void* memcpy(void*, const void*, u64);
extern "C" u64 strlen(const char*);
extern "C" char* strncpy(char*, const char*, u64);
extern "C" char* strcpy(char*, const char*);
extern "C" void* bsearch(const void*, const void*, u64, u64, int(*)(const void*, const void*));

// jemalloc (NX fork 5.1.0)
extern "C" void* je_aligned_alloc(u64 alignment, u64 size);
extern "C" void FUN_710392e590(void*);  // je_free

// libc++ recursive_mutex PLT stubs
// [derived: Ghidra shows std::__1::recursive_mutex::lock/unlock at these PLT entries]
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// libc++ error handling
extern "C" [[noreturn]] void __throw_length_error(void*);

// libc++ tree balancing
namespace std { namespace __1 {
    struct __tree_node_base_void {
        void* left;
        void* right;
        void* parent;
    };
    void __tree_balance_after_insert(void* root, void* node);
}}

// Resource service helpers (already implemented in other files)
extern "C" void FUN_7103540450(FilesystemInfo* fs_info, u32 index);  // increment ref count
void FUN_7103540560(FilesystemInfo*, u32);  // release filepath entry
void FUN_7103542d80(LoadedDirectory* dir, CppVector<u32>* release_vec);  // decrement + collect
LoadedDirectory* FUN_71035407a0(FilesystemInfo* fs, u32 dir_index);  // get_or_init directory

// bsearch comparator for packed hash entries
// [derived: LAB_7103541c90 is a comparator that compares lower 40 bits of u64]
extern "C" int FUN_7103541c90(const void*, const void*);

// ---- Global externs ----

// FilesystemInfo singleton
// [derived: DAT_7105331f20 used across all resource helpers]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// OOM handler singleton
// [derived: DAT_7105331f00 at 0x7105331f00, vtable dispatch at +0x30]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// ResServiceNX singleton
// [derived: DAT_7105331f28 at 0x7105331f28, used by language/region resolution]
__attribute__((visibility("hidden"))) extern void* DAT_7105331f28;

// CRC32 lookup table (256 u32 entries)
// [derived: DAT_7104753084 used by case-insensitive CRC32 hash in path lookups]
__attribute__((visibility("hidden"))) extern u32 DAT_7104753084[];

// ============================================================================
// FUN_710353eff0 — release_loaded_directory_entries
// Decrements ref counts for the directory tree via FUN_7103542d80, collecting
// file_group_indices. Then pushes all collected indices to FilesystemInfo.unk2
// vector (the pending-release queue). Sets unk3 flag after each push.
// [derived: called from FUN_710353e150, FUN_710353eab0, FUN_710353eb70, FUN_710353e980]
// [derived: param_1=FilesystemInfo*, param_2=LoadedDirectory*]
// Address: 0x710353eff0 (448 bytes)
// ============================================================================
void FUN_710353eff0(FilesystemInfo* fs, LoadedDirectory* dir) {
    CppVector<u32> release_vec;
    release_vec.start = nullptr;
    release_vec.end = nullptr;
    release_vec.eos = nullptr;

    FUN_7103542d80(dir, &release_vec);

    u32* puVar2 = release_vec.end;
    if (release_vec.start != puVar2) {
        u32* puVar5 = release_vec.start;
        do {
            u32* puVar1 = fs->unk2.end;
            if (puVar1 == fs->unk2.eos) {
                // Vector grow — same pattern as FUN_7103542d80 / FUN_7103540560
                u32* __src = fs->unk2.start;
                u64 __n = (u64)((u8*)puVar1 - (u8*)__src);
                u64 uVar6 = (__n >> 2) + 1;

                if (uVar6 >> 62 != 0) {
                    __throw_length_error(fs);
                }

                s64 lVar3 = (s64)((u8*)fs->unk2.eos - (u8*)__src);
                void* __dest;
                if ((u64)(lVar3 >> 2) < 0x1fffffffffffffffULL) {
                    u64 uVar4 = (u64)lVar3 >> 1;
                    if (uVar6 <= uVar4) {
                        uVar6 = uVar4;
                    }
                    if (uVar6 == 0) {
                        __dest = nullptr;
                        goto do_insert;
                    }
                } else {
                    uVar6 = 0x3fffffffffffffffULL;
                }

                {
                    if (uVar6 >> 62 != 0) {
                        // abort — unreachable
                    }
                    lVar3 = (s64)(uVar6 * 4);
                    if (lVar3 == 0) lVar3 = 1;
                    __dest = (void*)je_aligned_alloc(0x10, (u64)lVar3);
                    if (__dest == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            u32 oom_flags = 0;
                            s64 oom_size = lVar3;
                            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                     (DAT_7105331f00, &oom_flags, &oom_size);
                            if (((r & 1) != 0) &&
                                (__dest = (void*)je_aligned_alloc(0x10, (u64)lVar3),
                                 __dest != nullptr))
                                goto do_insert;
                        }
                        __dest = nullptr;
                    }
                }
            do_insert:
                puVar1 = (u32*)((u8*)__dest + (__n >> 2) * 4);
                *puVar1 = *puVar5;
                if (0 < (s64)__n) {
                    memcpy(__dest, __src, __n);
                }
                fs->unk2.start = (u32*)__dest;
                fs->unk2.end = puVar1 + 1;
                fs->unk2.eos = (u32*)((u8*)__dest + uVar6 * 4);
                if (__src != nullptr) {
                    FUN_710392e590(__src);
                }
            } else {
                *puVar1 = *puVar5;
                fs->unk2.end = (u32*)((u8*)fs->unk2.end + 4);
            }
            puVar5++;
            fs->unk3 = 1;
        } while (puVar2 != puVar5);
    }

    if (release_vec.start != nullptr) {
        release_vec.end = release_vec.start;
        FUN_710392e590(release_vec.start);
    }
}

// ============================================================================
// FUN_710353dc20 — find_filepath_in_directory_by_hash
// Given a directory index and a filename string, computes a case-insensitive
// CRC32 hash, then searches the directory's child_path_indices for a matching
// filepath entry. Sets *out to the matching filepath index, or 0xffffff.
// [derived: CRC32 table at DAT_7104753084, case-insensitive (uppercase→lowercase)]
// [derived: LoadedDirectory at +0x40 in FilesystemInfo, stride 0x48]
// [derived: child_path_indices CppVector<u32> at +0x10 in LoadedDirectory]
// Address: 0x710353dc20 (432 bytes)
// ============================================================================
void FUN_710353dc20(u32* out, u32* dir_index_ptr, const u8* filename) {
    FilesystemInfo* fs = DAT_7105331f20;

    // Compute case-insensitive CRC32 hash of filename
    u32 ch = (u32)*filename;
    u64 hash_lo;
    u64 len_hi;
    if (*filename == 0) {
        hash_lo = 0;
        len_hi = 0;
    } else {
        len_hi = 0;
        u32 crc = 0xffffffff;
        const u8* p = filename + 1;
        do {
            u32 c = ch + 0x20;
            if (ch - 0x41 > 0x19) {
                c = ch;
            }
            crc = DAT_7104753084[(c ^ crc) & 0xff] ^ (crc >> 8);
            ch = (u32)*p;
            len_hi += 0x100000000ULL;
            p++;
        } while (ch != 0);
        hash_lo = (u64)(~crc);
        len_hi &= 0xff00000000ULL;
    }

    u32 dir_idx = *dir_index_ptr;
    if (dir_idx == 0xffffff) {
        *out = 0xffffff;
        return;
    }

    if (dir_idx < fs->loaded_directory_len) {
        lock_71039c1490(fs->mutex);
        LoadedDirectory* dirs = fs->loaded_directories;
        LoadedDirectory* entry = &dirs[dir_idx];
        u8 flags = entry->flags;
        unlock_71039c14a0(fs->mutex);

        if ((flags & 1) && entry != nullptr) {
            LoadedDirectory* dir = &dirs[dir_idx];
            u32* child_start = dir->child_path_indices.start;
            u32* child_end = dir->child_path_indices.end;

            if (child_start != child_end) {
                do {
                    u32 filepath_idx = *child_start;
                    if (filepath_idx == 0xffffff ||
                        filepath_idx >= *(u32*)(*(u64*)(*(u64*)(fs->path_info) + 0x40) + 4)) {
                        if ((len_hi | hash_lo) == 0) goto found;
                    } else {
                        u64 entry_hash = *(u64*)(*(u64*)(*(u64*)(fs->path_info) + 0x60) +
                                                 (u64)filepath_idx * 0x20 + 0x18);
                        if (entry_hash == (len_hi | hash_lo)) {
                            goto found;
                        }
                    }
                    child_start++;
                    continue;
                found:
                    *out = 0xffffff;
                    u32 val = *child_start;
                    *out = val;
                    if (val == 0xffffff) return;
                    FUN_7103540450(DAT_7105331f20, val);
                    return;
                } while (child_end != child_start);
            }
            *out = 0xffffff;
            return;
        }
    }
    *out = 0xffffff;
}

// ============================================================================
// FUN_710353e330 — normalize_path_and_lookup_directory_index
// Normalizes a path string (backslash → slash, strip trailing slash), computes
// a case-insensitive CRC32 hash, and looks up the directory index via bsearch
// in the LoadedArc's path_group table.
// [derived: path normalization pattern, CRC32 hash, bsearch with LAB_7103541c90]
// [derived: LoadedArc accessed via fs->path_info->search (+0x78 in fs, +8 in PathInfo)]
// Address: 0x710353e330 (432 bytes)
// ============================================================================
void FUN_710353e330(u32* out, const char* path) {
    FilesystemInfo* fs = DAT_7105331f20;

    // Copy and normalize path
    char buf[256];
    char sentinel;  // byte right after buf — forms cStack_131 in Ghidra

    strncpy(buf, path, 0xff);
    strcpy(buf, path);

    u64 len = strlen(buf);

    // Replace backslashes with forward slashes
    if (len != 0) {
        if (len == 1) {
            if (buf[0] == '\\') buf[0] = '/';
        } else {
            char* p = buf;
            s64 remaining = (s64)((len & 1) - len);
            do {
                if (*p == '\\') *p = '/';
                if (p[1] == '\\') p[1] = '/';
                p += 2;
                remaining += 2;
            } while (remaining != 0);
            if ((len & 1) != 0) {
                if (*p == '\\') *p = '/';
            }
        }
        // Strip trailing slash
        if ((&sentinel)[len] == '/') {
            (&sentinel)[len] = '\0';
        }
    }

    // Compute case-insensitive CRC32 hash
    u32 ch = (u32)(u8)buf[0];
    u64 hash_lo;
    u64 len_hi;
    if ((u8)buf[0] == 0) {
        hash_lo = 0;
        len_hi = 0;
    } else {
        len_hi = 0;
        u32 crc = 0xffffffff;
        u8* p = (u8*)buf + 1;
        do {
            u32 c = ch + 0x20;
            if (ch - 0x41 > 0x19) {
                c = ch;
            }
            crc = DAT_7104753084[(c ^ crc) & 0xff] ^ (crc >> 8);
            ch = (u32)*p;
            len_hi += 0x100000000ULL;
            p++;
        } while (ch != 0);
        hash_lo = (u64)(~crc);
        len_hi &= 0xff00000000ULL;
    }

    // Build search key: default is 0x179d3d2d4 (hash for empty path)
    u64 search_key = 0x179d3d2d4ULL;
    if ((len_hi | hash_lo) != 0) {
        search_key = len_hi | hash_lo;
    }

    // bsearch in path_group table
    u64 search_section = *(u64*)(*(u64*)(fs->path_info) + 8);  // search = PathInfo->search
    u64* result = (u64*)bsearch(
        &search_key,
        *(void**)(search_section + 0x20),       // path_group array
        (u64)*(u32*)(*(u64*)(search_section + 8) + 8),  // count from header
        8,
        (int(*)(const void*, const void*))FUN_7103541c90
    );

    u32 dir_index = 0xffffff;
    if (result != nullptr) {
        u32 shifted = (u32)(*result >> 0x20);
        u32 idx = shifted >> 8;
        if (idx != 0xffffff) {
            u32 limit = *(u32*)(*(u64*)(search_section + 8) + 4);
            dir_index = shifted >> 8;
            if (idx >= limit) {
                dir_index = 0xffffff;
            }
        }
    }

    *out = dir_index;
}

// ============================================================================
// FUN_710353e5d0 — filepath_index_to_file_info_combined
// Takes a filepath index, resolves through the search section tables via
// two bsearch lookups (file_path_to_idx, then path_to_idx), returning a
// combined u64 encoding both the hash40 and file group index.
// Returns 0xFFFFFFFFFFFFFFFF on failure.
// [derived: uses bsearch with LAB_7103541c90 comparator on packed u64 entries]
// [derived: search section offsets: +0x10=file_path_to_idx, +0x18=path_to_idx, +0x20=path_group]
// Address: 0x710353e5d0 (400 bytes)
// ============================================================================
u64 FUN_710353e5d0(u32 param_1) {
    u64 lVar8 = (u64)DAT_7105331f20;

    if (param_1 != 0xffffff) {
        u64 lVar9 = *(u64*)(*(u64*)(lVar8 + 0x78) + 8);
        u32* puVar3 = *(u32**)(lVar9 + 8);

        if (param_1 < puVar3[1]) {
            u64 lVar5 = *(u64*)(lVar9 + 0x28);
            u32 uVar6 = param_1;
            if (lVar5 != 0) {
                uVar6 = *(u32*)(lVar5 + (u64)param_1 * 4);
            }

            if (uVar6 != 0xffffff && uVar6 < puVar3[2]) {
                u64 lVar1 = *(u64*)(lVar9 + 0x30) + (u64)uVar6 * 0x20;
                if (lVar1 != 0 && ((*(u8*)(lVar1 + 0xf) >> 6) & 1)) {
                    if (lVar5 != 0) {
                        param_1 = *(u32*)(lVar5 + (u64)param_1 * 4);
                    }

                    u64 uVar7 = 0;
                    if (param_1 != 0xffffff && param_1 < puVar3[2]) {
                        u64* puVar2 = (u64*)(*(u64*)(lVar9 + 0x30) + (u64)param_1 * 0x20);
                        if (puVar2 == nullptr) {
                            uVar7 = 0;
                        } else {
                            uVar7 = *puVar2 & 0xffffffffffULL;
                        }
                    }

                    u64 local_28 = uVar7;
                    u64* puVar2 = (u64*)bsearch(
                        &local_28, *(void**)(lVar9 + 0x10),
                        (u64)*puVar3, 8,
                        (int(*)(const void*, const void*))FUN_7103541c90);

                    u64 first_entry = 0;
                    if (puVar2 != nullptr && (*puVar2 >> 0x28) != 0xffffff) {
                        first_entry = *(u64*)(lVar9 + 0x18) + (*puVar2 >> 0x28) * 0x20;
                    }
                    if (first_entry == 0) {
                        uVar7 = 0xffffffffffULL;
                    }

                    lVar8 = *(u64*)(*(u64*)(lVar8 + 0x78) + 8);
                    local_28 = uVar7;
                    puVar2 = (u64*)bsearch(
                        &local_28, *(void**)(lVar8 + 0x10),
                        (u64)**(u32**)(lVar8 + 8), 8,
                        (int(*)(const void*, const void*))FUN_7103541c90);

                    if (puVar2 != nullptr) {
                        u64 uVar4 = *puVar2 >> 0x28;
                        if (uVar4 != 0xffffff) {
                            u64 entry_base = *(u64*)(lVar8 + 0x18) + uVar4 * 0x20;
                            if (entry_base != 0) {
                                uVar6 = *(u32*)(entry_base + 0x18);
                                if (uVar6 != 0xffffff && uVar6 < *(u32*)(*(u64*)(lVar8 + 8) + 4)) {
                                    return uVar7 | ((u64)uVar6 << 0x28);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0xFFFFFFFFFFFFFFFFULL;
}

// ============================================================================
// FUN_710353e760 — resolve_region_language_index
// Converts a byte string (up to 8 chars) to lowercase, computes a hash via
// FUN_710399eb90, then looks up the hash in a tree structure to find the
// region index. Sets the region and language indices on the ResServiceNX.
// [derived: DAT_7105331f28 = ResServiceNX*, region_idx at +0xD8, language_idx at +0xDC]
// [derived: tree is at LoadedArc+0x130 (tree root) with keys at +0x1C, values at +0x20]
// Address: 0x710353e760 (544 bytes)
// ============================================================================

// Hash function for 8-byte strings
// [derived: called with (buf, len) — FUN_710399eb90]
extern "C" u32 FUN_710399eb90(u8* buf, u64 len);

void FUN_710353e760(u8* param_1) {
    u64 lVar1 = (u64)DAT_7105331f28;
    if (lVar1 == 0) return;

    u64 lVar11 = *(u64*)(lVar1 + 0xd0);
    u64* plVar12 = *(u64**)(lVar11 + 0x78);

    // Lowercase up to first 8 chars
    u8 local_28[8];
    u8 bVar6 = *param_1;
    u64 lVar9;
    u64 uVar5;

    if (bVar6 == 0) {
        uVar5 = 0;
        lVar9 = 0;
    } else {
        // Unrolled lowercase for up to 8 chars
        u8 c = bVar6;
        if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20;
        local_28[0] = c;

        bVar6 = param_1[1];
        if (bVar6 == 0) { uVar5 = 1; lVar9 = 1; }
        else {
            c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20; local_28[1] = c;
            bVar6 = param_1[2];
            if (bVar6 == 0) { uVar5 = 2; lVar9 = 2; }
            else {
                c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20; local_28[2] = c;
                bVar6 = param_1[3];
                if (bVar6 == 0) { uVar5 = 3; lVar9 = 3; }
                else {
                    c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20; local_28[3] = c;
                    bVar6 = param_1[4];
                    if (bVar6 == 0) { uVar5 = 4; lVar9 = 4; }
                    else {
                        c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20; local_28[4] = c;
                        bVar6 = param_1[5];
                        if (bVar6 == 0) { uVar5 = 5; lVar9 = 5; }
                        else {
                            c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20; local_28[5] = c;
                            bVar6 = param_1[6];
                            if (bVar6 == 0) { uVar5 = 6; lVar9 = 6; }
                            else {
                                c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20; local_28[6] = c;
                                bVar6 = param_1[7];
                                if (bVar6 == 0) { uVar5 = 7; lVar9 = 7; }
                                else {
                                    lVar9 = 7;
                                    c = bVar6; if (c >= 0x41 && c - 0x41 <= 0x19) c += 0x20;
                                    bVar6 = c;
                                    uVar5 = 8;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    local_28[lVar9] = bVar6;
    u32 uVar4 = FUN_710399eb90(local_28, uVar5);

    // Tree lookup
    u64 lVar9_tree = *plVar12;
    u32 result_idx;
    if (*(u64*)(lVar9_tree + 0x48) != 0) {
        u64 lVar10 = *(u64*)(lVar9_tree + 0x130);
        if (lVar10 != 0) {
            u64 lVar7 = lVar9_tree + 0x130;
            do {
                bool bVar3 = *(u32*)(lVar10 + 0x1c) < uVar4;
                if (!bVar3) {
                    lVar7 = lVar10;
                }
                lVar10 = *(u64*)(lVar10 + (u64)bVar3 * 8);
            } while (lVar10 != 0);
            if (lVar7 != lVar9_tree + 0x130 && *(u32*)(lVar7 + 0x1c) <= uVar4) {
                result_idx = *(u32*)(lVar7 + 0x20);
                goto set_region;
            }
        }
    }
    {
        // Tree lookup failed
        u32 val = 0xffffffff;
        *(u32*)(lVar1 + 0xdc) = val;
        *(u32*)(lVar1 + 0xd8) = val;
        return;
    }

set_region:
    {
        u32 uVar8 = 0xffffffff;
        *(u32*)(lVar1 + 0xdc) = result_idx;
        if ((s32)result_idx >= 0) {
            u64 lVar9_2 = **(u64**)(lVar11 + 0x78);
            u64 lVar11_2 = *(u64*)(lVar9_2 + 0x48);
            if (lVar11_2 != 0) {
                if (result_idx < *(u8*)(*(u64*)(lVar9_2 + 0x40) + 0x38)) {
                    uVar8 = *(u32*)(lVar11_2 + (s64)(s32)result_idx * 0xc + 8);
                } else {
                    uVar8 = 0xffffffff;
                }
            }
        }
        *(u32*)(lVar1 + 0xd8) = uVar8;
    }
}

// ============================================================================
// FUN_710353ddd0 — find_filepath_by_hash_in_loaded_directory
// Searches a loaded directory's child paths for a filepath matching a given
// hash40 value. Copies the directory's children, iterates them comparing
// hash values, and returns the matching file_group_index via FUN_71035407a0.
// [derived: LoadedDirectory at +0x40, stride 0x48, flags at +0x08]
// [derived: child_path_indices at +0x10 (CppVector<u32>), iterated for hash match]
// Address: 0x710353ddd0 (608 bytes)
// ============================================================================

// Default value when no match found
// [derived: UNK_7104470f50 contains 0xffffff as u32]
__attribute__((visibility("hidden"))) extern u32 UNK_7104470f50;

void FUN_710353ddd0(u32* param_1, u32 param_2, u64 param_3) {
    FilesystemInfo* fs = DAT_7105331f20;

    if (param_2 == 0xffffff || fs->loaded_directory_len <= param_2) {
        *param_1 = 0xffffff;
        return;
    }

    lock_71039c1490(fs->mutex);
    LoadedDirectory* dirs = fs->loaded_directories;
    LoadedDirectory* entry = &dirs[param_2];
    u8 flags = entry->flags;
    unlock_71039c14a0(fs->mutex);

    if (!(flags & 1) || entry == nullptr) {
        *param_1 = 0xffffff;
        return;
    }

    // Copy child path indices vector
    LoadedDirectory* dir = &dirs[param_2];
    u64* plVar13 = (u64*)&dir->child_path_indices.start;  // +0x10
    u64* plVar15 = (u64*)&dir->child_path_indices.end;     // +0x18
    s64 lVar12 = *plVar15 - *plVar13;
    if (lVar12 == 0) {
        *param_1 = 0xffffff;
        return;
    }

    if ((u64)(lVar12 >> 3) >> 61 != 0) {
        __throw_length_error(fs);
    }

    void* __dest = (void*)je_aligned_alloc(0x10, (u64)lVar12);
    if (__dest == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = lVar12;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (__dest = (void*)je_aligned_alloc(0x10, (u64)lVar12),
                 __dest != nullptr))
                goto do_search;
        }
        __dest = nullptr;
    }
do_search:
    {
        void* __src = (void*)*plVar13;
        u64 uVar5 = (u64)(*plVar15 - (u64)__src);
        if (0 < (s64)uVar5 && (memcpy(__dest, __src, uVar5), uVar5 != 0)) {
            u64 uVar7 = 0;
            do {
                u64* puVar10 = (u64*)(*(u64*)(*(u64*)(*(u64*)(fs->path_info) + 0x78) +
                                    (u64)**(u32**)((u8*)__dest + uVar7) * 0x34));
                if (((puVar10[1] ^ param_3) & 0xffffffffffULL) == 0) {
                    u64 uVar5_hash = *puVar10 & 0xffffffffffULL;
                    u64 result_hash;

                    if (uVar5_hash == 0) {
                        result_hash = 0xffffff;
                    } else {
                        // Binary search (lower_bound) in filepath table
                        u64* puVar8 = *(u64**)(*(u64*)(*(u64*)(DAT_7105331f20->path_info) + 0x70));
                        u32 uVar2 = *(u32*)(*(u64*)(*(u64*)(DAT_7105331f20->path_info) + 0x40) + 0xc);
                        u64 bscount = (u64)uVar2;
                        u64* puVar10_end = puVar8 + bscount;
                        u64* puVar9 = puVar8;
                        if (uVar2 != 0) {
                            do {
                                u64 uVar11 = bscount;
                                if ((s64)bscount < 0) {
                                    uVar11 = bscount + 1;
                                }
                                uVar11 >>= 1;
                                u64* puVar8_mid = puVar9 + uVar11 + 1;
                                u64 remaining = bscount + ~uVar11;
                                if (uVar5_hash <= (puVar9[uVar11] & 0xffffffffffULL)) {
                                    puVar8_mid = puVar9;
                                    remaining = uVar11;
                                }
                                puVar9 = puVar8_mid;
                                bscount = remaining;
                            } while (bscount != 0);
                        }

                        if (puVar9 == puVar10_end || (*puVar9 & 0xffffffffffULL) != uVar5_hash) {
                            result_hash = 0xffffff;
                        } else {
                            result_hash = *puVar9 >> 0x28;
                        }
                    }

                    LoadedDirectory* puVar6 = FUN_71035407a0(DAT_7105331f20, (u32)result_hash);
                    u32* puVar1 = &UNK_7104470f50;
                    if (puVar6 != nullptr) {
                        puVar1 = (u32*)puVar6;
                    }
                    *param_1 = *puVar1;
                    if (__dest != nullptr) {
                        FUN_710392e590(__dest);
                    }
                    return;
                }
                uVar7 += 8;
            } while ((uVar5 & 0xfffffffffffffff8ULL) != uVar7);
        }
    }

    if (__dest != nullptr) {
        FUN_710392e590(__dest);
    }
    *param_1 = 0xffffff;
}
