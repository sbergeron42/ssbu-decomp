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

// Decompression / streaming I/O
// [derived: FUN_710399f880 finalizes a decompression context (~160KB workspace)]
// [derived: FUN_71039a3e70 closes a decompression stream, returns status code]
// [derived: FUN_7103541c00 allocates decompression workspace, hidden (same TU)]
// [derived: FUN_7103541c80 is an internal callback entry within FUN_7103541c00]
extern "C" void FUN_710399f880(void*);
extern "C" u64 FUN_71039a3e70(void*);
__attribute__((visibility("hidden"))) void* FUN_7103541c00(void*, u32);
__attribute__((visibility("hidden"))) void FUN_7103541c80(void);

// File I/O
// [derived: FUN_71037c6940 reads bytes from a FileNX, returns bytes actually read]
extern "C" s64 FUN_71037c6940(void*, void*, u64);

// Decompression stream operations
// [derived: FUN_71039a4040 performs streaming decompression step]
extern "C" s64 FUN_71039a4040(void*, void*, void*);

// Version lookup
// [derived: FUN_7103542f30 takes u32* of masked version, returns int version index]
extern "C" s32 FUN_7103542f30(u32*);

// libc++ internal
namespace std { namespace __1 {
    unsigned long __next_prime(unsigned long);
}}

// nn::fs functions
namespace nn { namespace fs {
    extern "C" void GetFileSize(s64*, void*);
}}

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


// ============================================================================
// FUN_7103541ae0 — init_decomp_stream
// Resets and reinitializes a streaming decompression state. The state is a
// 2-element pointer array: [0]=workspace context, [1]=stream handle.
// Cleans up any existing context (finalize + custom dealloc or je_free),
// closes any existing stream, then allocates a fresh 0x271f0-byte workspace
// (consistent with ZSTD_DStream size in zstd v1.3.7) and initializes it.
// [derived: called from FUN_71035414c0 with zeroed 16-byte local struct]
// [derived: workspace +0x7120/+0x7128 store alloc/callback function pointers]
// [derived: workspace +0x7130 stores back-pointer to the state array]
// Address: 0x7103541ae0 (288 bytes)
// ============================================================================
u32 FUN_7103541ae0(s64* param_1) {
    s64 ctx = *param_1;

    if (ctx != 0) {
        if (*(s64*)(ctx + 0x1a8) != 0) goto LAB_alloc;
        FUN_710399f880((void*)ctx);
        typedef void (*DeallocFn)(void*, void*);
        DeallocFn dealloc = *(DeallocFn*)(ctx + 0x198);
        if (dealloc == nullptr) {
            FUN_710392e590((void*)ctx);
        } else {
            dealloc(*(void**)(ctx + 0x1a0), (void*)ctx);
        }
        *param_1 = 0;
    }

    if (param_1[1] != 0) {
        u64 r = FUN_71039a3e70((void*)param_1[1]);
        if (r < 0xffffffffffffff89ULL) {
            param_1[1] = 0;
        }
    }

LAB_alloc:
    {
        s64 c = (s64)FUN_7103541c00(param_1, 0x271f0);
        if (c == 0) {
            param_1[1] = 0;
            return 0x80000004;
        }

        // Initialize workspace — function pointers and back-pointer
        // [derived: +0x7120 = allocator, +0x7128 = callback, +0x7130 = state backref]
        *(void*(**)(void*, u32))(c + 0x7120) = FUN_7103541c00;
        *(void(**)(void))(c + 0x7128) = &FUN_7103541c80;
        *(s64**)(c + 0x7130) = param_1;
        *(u32*)(c + 0x7114) = 0;
        *(u64*)(c + 0x7188) = 0x8000001;
        *(u64*)(c + 0x7148) = 0;
        *(u64*)(c + 0x7198) = 0;
        *(u64*)(c + 0x71b8) = 0;
        *(u32*)(c + 0x71c0) = 0;
        *(u32*)(c + 0x7150) = 0;
        *(u64*)(c + 0x7158) = 0;
        *(u64*)(c + 0x7160) = 0;
        *(u64*)(c + 0x7178) = 0;
        *(u64*)(c + 0x7170) = 0;
        param_1[1] = c;
        *(u32*)(c + 0x7168) = 0;
        *(u32*)(c + 0x71cc) = 0;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
        *(u64*)(c + 0x7160) = 0;
        *(u64*)(c + 0x7158) = 0;

        return 0;
    }
}


// ============================================================================
// FUN_7103541860 — get_info_to_data_with_locale
// Resolves a FileInfo to its FileInfoToFileData pointer with locale-aware
// index adjustment. For regional/language content, offsets the info_to_data
// index by region_idx/language_idx + 1.
// When a version mismatch against the global ARC is detected, searches
// the extra entries via hash table binary search (lower_bound on hash40).
// [derived: uses LoadedArc tables: file_info_indices, file_infos, file_paths,
//  extra_buckets, extra_entry_vector, file_info_to_datas]
// [derived: binary search matches std::lower_bound pattern with signed division]
// [derived: locale_type field = (FileInfo.flags >> 15) & 3: 0=none, 1=language, 2=region]
// Address: 0x7103541860 (640 bytes)
// ============================================================================
FileInfoToFileData* FUN_7103541860(LoadedArc* arc, FileInfo* fi, int version) {
    // Resolve file_path_index through the indice chain
    // [derived: file_info_indices[fii].file_info_index masked to 24 bits]
    u32 fii = fi->file_info_indice_index;
    u32 fi_idx = arc->file_info_indices[fii].file_info_index & 0xffffff;
    u32 fp_idx = arc->file_infos[fi_idx].file_path_index;

    // Extract hash40 from the resolved file path
    u64 hash40;
    if (fp_idx == 0xffffff || arc->fs_header->file_info_path_count <= fp_idx) {
        hash40 = 0;
    } else {
        hash40 = arc->file_paths[fp_idx].path.raw & 0xFFFFFFFFFFULL;
    }

    u32 itd_idx;
    u32 flags;

    // Check if locale-specific extra entry lookup is needed
    if (version == (int)0xffff || arc->fs_header->version == (u32)version ||
        arc->extra_entries == 0) {
        goto LAB_default;
    }

    {
        // [derived: arc->version at +0x110 saved across function call in w22]
        u32 arc_ver = arc->version;
        if (arc_ver == (u32)0xffff) goto LAB_default;

        // Compare local arc version against global filesystem version
        // [derived: DAT_7105331f20->path_info->arc->fs_header->version & 0xffffff]
        // [derived: Ghidra shows local as uint[2] (8 bytes) at SP+0x08]
        u32 gver[2];
        gver[0] = ((PathInformation*)DAT_7105331f20->path_info)->arc->fs_header->version
                   & 0xffffff;
        int ver_id = FUN_7103542f30(gver);
        if ((int)arc_ver == ver_id) goto LAB_default;

        // Bounds check on extra entry index
        u32 ec = arc->extra_count;
        if (ec >= arc->extra_buckets[0].count) goto LAB_default;

        // Hash table lookup in extra entries
        // [derived: extra_entry_vector is CppVector of 48-byte entries]
        // [derived: entry+0x08 = hash table ptr, entry+0x10 = values array ptr]
        u8* entries = (u8*)arc->extra_entry_vector[0];
        u8* entry = entries + (u64)ec * 48;
        u8* ht = *(u8**)(entry + 8);
        u8* vals = *(u8**)(entry + 16);

        // Hash into bucket
        // [derived: hash table: u32 bucket_count at +0, then bucket pairs at +8]
        u32 bcount = *(u32*)ht;
        u64 brem = hash40 % (u64)bcount;

        // Load bucket start index and count
        u32 start = *(u32*)(ht + brem * 8 + 8);
        u32 count = *(u32*)(ht + brem * 8 + 12);

        // Binary search (lower_bound) on hash40 values within bucket
        // [derived: values are u64: lower 40 bits = hash40, upper 24 bits = sub-index]
        u64* lo = (u64*)(vals + (u64)start * 8);
        s64 len = (s64)(u64)count;

        if (count != 0) {
            do {
                s64 half = len / 2;
                u64* mid = lo + half;
                u64 mid_val = *mid++;
                u64 mid_hash = mid_val & 0xFFFFFFFFFFULL;
                s64 upper = len + ~half;

                if (mid_hash < hash40) {
                    lo = mid;
                    len = upper;
                } else {
                    len = half;
                }
            } while (len != 0);
        }

        // Verify exact match
        if (lo == nullptr) goto LAB_default;
        u64 found = *lo;
        if ((found & 0xFFFFFFFFFFULL) != hash40) goto LAB_default;

        // Get sub-entry from the extra entries
        // [derived: entry+0x00 = sub-entries base, stride 20 bytes, +8 = file info index]
        u8* sub_base = *(u8**)(entries + (u64)ec * 48);
        u64 sub_idx = found >> 40;
        if (sub_base + sub_idx * 20 == nullptr) goto LAB_default;

        // Resolve alternate file info from sub-entry
        u32 alt_fi_idx = *(u32*)(sub_base + sub_idx * 20 + 8);
        FileInfo* alt = &arc->file_infos[alt_fi_idx];
        itd_idx = alt->info_to_data_index;
        flags = alt->flags;
        goto LAB_compute;
    }

LAB_default:
    itd_idx = fi->info_to_data_index;
    flags = fi->flags;

LAB_compute:
    {
        // Locale-aware index adjustment
        // [derived: locale_type 2=region (region_idx at ResServiceNX+0xD8)]
        // [derived: locale_type 1=language (language_idx at ResServiceNX+0xDC)]
        u32 locale_type = (flags >> 15) & 3;
        if (locale_type == 2) {
            int r = (int)DAT_7105331f28->region_idx;
            int adj = (r == -1) ? 0 : r;
            itd_idx = itd_idx + (u32)adj + 1;
        } else if (locale_type == 1) {
            int l = (int)DAT_7105331f28->language_idx;
            int adj = (l == -1) ? 0 : l;
            itd_idx = itd_idx + (u32)adj + 1;
        }

        return &arc->file_info_to_datas[itd_idx];
    }
}


// ============================================================================
// Hash table node used by the resource service hash map
// [derived: Ghidra shows node+0x00 = next, node+0x08 = hash, node+0x10 = key(u32)]
// [derived: FUN_7103542540 and FUN_7103542120 both operate on this layout]
// ============================================================================
struct HashNode {
    HashNode* next;  // +0x00
    u64 hash;        // +0x08
    u32 key;         // +0x10
};

// Hash table structure (similar to std::__1::__hash_table)
// [derived: param_1 layout in FUN_7103542540/FUN_7103541ec0]
struct ResHashTable {
    HashNode** buckets;     // +0x00 — bucket array (pointers to previous node's next)
    u64 bucket_count;       // +0x08
    HashNode head;          // +0x10 — sentinel head node (first.next is actual first)
    u64 element_count;      // +0x28
    float max_load_factor;  // +0x30
};


// ============================================================================
// FUN_7103542540 — hash_table_rehash
// Reallocates the bucket array and rehashes all entries. Allocates a new
// pointer array of size new_count*8, zeros it, then walks the linked list
// and redistributes nodes into new buckets. Uses power-of-2 fast path
// (bitmask) when bucket_count is a power of two.
// [derived: std::__1::__hash_table::__rehash() pattern from libc++]
// [derived: identical OOM retry pattern as FUN_7103541080]
// Address: 0x7103542540 (672 bytes)
// ============================================================================
void FUN_7103542540(ResHashTable* ht, u64 new_count) {
    if (new_count == 0) {
        // Clear the table
        HashNode** old = ht->buckets;
        ht->buckets = nullptr;
        if (old != nullptr) {
            FUN_710392e590(old);
        }
        ht->bucket_count = 0;
        return;
    }

    if (new_count >> 61 != 0) {
        abort();
    }

    // Allocate new bucket array
    u64 alloc_size = new_count * 8;
    if (alloc_size == 0) alloc_size = 1;
    HashNode** new_buf = (HashNode**)je_aligned_alloc(0x10, alloc_size);
    if (new_buf == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_flags = 0;
            s64 oom_size = (s64)alloc_size;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (new_buf = (HashNode**)je_aligned_alloc(0x10, alloc_size),
                 new_buf != nullptr))
                goto LAB_allocated;
        }
        new_buf = nullptr;
    }
LAB_allocated:
    {
        // Replace bucket array
        HashNode** old = ht->buckets;
        ht->buckets = new_buf;
        if (old != nullptr) {
            FUN_710392e590(old);
        }

        // Zero the new bucket array (unrolled by 4)
        u64 count_m1 = new_count - 1;
        u64 rem = new_count & 3;
        ht->bucket_count = new_count;

        u64 i;
        if (count_m1 < 3) {
            i = 0;
        } else {
            i = 0;
            u64 aligned_count = new_count - rem;
            do {
                u64 off = i * 8;
                i += 4;
                *(u64*)((u8*)ht->buckets + off) = 0;
                *(u64*)((u8*)ht->buckets + off + 8) = 0;
                *(u64*)((u8*)ht->buckets + off + 16) = 0;
                *(u64*)((u8*)ht->buckets + off + 24) = 0;
            } while (aligned_count != i);
        }
        if (rem != 0) {
            u64 off = i << 3;
            s64 neg_rem = -(s64)rem;
            do {
                *(u64*)((u8*)ht->buckets + off) = 0;
                off += 8;
                neg_rem += 1;
            } while (neg_rem != 0);
        }

        // Rehash all entries from the linked list
        HashNode* node = ht->head.next;
        if (node == nullptr) return;

        // Compute bucket index for first node
        u64 hash = node->hash;
        u64 is_pow2 = count_m1 & new_count;
        u64 bucket_idx;
        if (is_pow2 == 0) {
            bucket_idx = hash & count_m1;
        } else {
            bucket_idx = hash;
            if (new_count <= hash) {
                bucket_idx = hash % new_count;
            }
        }

        // Point bucket to the head sentinel's next pointer
        ht->buckets[bucket_idx] = (HashNode*)&ht->head;

        HashNode* next_node = node->next;
        if (next_node == nullptr) return;

        HashNode* prev = node;
        HashNode* advance;
        if (is_pow2 == 0) {
            // Power-of-2 path: use bitmask for bucket index
            do {
                u64 next_bucket = next_node->hash & count_m1;
                if (next_bucket != bucket_idx) {
                    HashNode* cursor = next_node;
                    if (ht->buckets[next_bucket] == nullptr) {
                        ht->buckets[next_bucket] = prev;
                        bucket_idx = next_bucket;
                    } else {
                        HashNode* last = cursor;
                        do {
                            last = cursor;
                            cursor = cursor->next;
                            if (cursor == nullptr) break;
                        } while ((int)next_node->key == (int)cursor->key);
                        prev->next = cursor;
                        HashNode* existing = ht->buckets[next_bucket];
                        last->next = existing->next;
                        ht->buckets[next_bucket]->next = next_node;
                        next_node = prev;
                    }
                }
                advance = next_node->next;
                prev = next_node;
                next_node = advance;
            } while (advance != nullptr);
        } else {
            // Non-power-of-2 path: use division for bucket index
            do {
                u64 next_hash = next_node->hash;
                u64 next_bucket = next_hash;
                if (new_count <= next_hash) {
                    next_bucket = next_hash % new_count;
                }
                if (next_bucket != bucket_idx) {
                    HashNode* cursor = next_node;
                    if (ht->buckets[next_bucket] == nullptr) {
                        ht->buckets[next_bucket] = prev;
                        bucket_idx = next_bucket;
                    } else {
                        HashNode* last = cursor;
                        do {
                            last = cursor;
                            cursor = cursor->next;
                            if (cursor == nullptr) break;
                        } while ((int)next_node->key == (int)cursor->key);
                        prev->next = cursor;
                        HashNode* existing = ht->buckets[next_bucket];
                        last->next = existing->next;
                        ht->buckets[next_bucket]->next = next_node;
                        next_node = prev;
                    }
                }
                advance = next_node->next;
                prev = next_node;
                next_node = advance;
            } while (advance != nullptr);
        }
    }
}


// ============================================================================
// FUN_7103541ec0 — hash_table_rehash_wrapper
// Adjusts a requested bucket count (to next prime or power-of-2), then
// either grows or shrinks the hash table via FUN_7103542540. When shrinking,
// computes the minimum buckets needed from element_count / max_load_factor.
// [derived: std::__1::__hash_table::rehash() pattern from libc++]
// [derived: calls std::__1::__next_prime for non-power-of-2 bucket counts]
// [derived: uses fcvtpu (ceiling) for float-to-u64 conversion of load ratio]
// Address: 0x7103541ec0 (228 bytes)
// ============================================================================
void FUN_7103541ec0(ResHashTable* ht, u64 new_count) {
    // Adjust to valid bucket count
    if (new_count - 1 == 0) {
        new_count = 2;
    } else if (((new_count - 1) & new_count) != 0) {
        // Not power of 2 — use next prime
        new_count = std::__1::__next_prime(new_count);
    }

    u64 cur = ht->bucket_count;
    u64 target = new_count;

    if (cur < new_count) {
        FUN_7103542540(ht, target);
        return;
    }

    if (new_count >= cur) return;

    {
        // Compute minimum needed buckets from load factor
        bool is_pow2;
        if (cur < 3 || ((cur - 1) & cur) != 0) {
            is_pow2 = false;
        } else {
            is_pow2 = true;
        }

        // min_needed = ceil((float)element_count / max_load_factor)
        // [derived: ucvtf + fdiv + fcvtpu sequence in disassembly]
        float ratio = (float)ht->element_count / ht->max_load_factor;
        u64 min_needed;
        asm("fcvtpu %x0, %s1" : "=r"(min_needed) : "w"(ratio));

        if (!is_pow2) {
            min_needed = std::__1::__next_prime(min_needed);
        } else if (min_needed >= 2) {
            u64 bits = -(u64)__builtin_clzll(min_needed - 1);
            min_needed = 1ULL << (bits & 63);
        }

        if (min_needed < new_count) {
            min_needed = new_count;
        }
        if (min_needed < cur) {
            FUN_7103542540(ht, min_needed);
        }
    }
}


// nn::os::YieldThread
extern "C" void _ZN2nn2os11YieldThreadEv(void);

// nn::fs::GetFileSize
extern "C" void _ZN2nn2fs11GetFileSizeEPxNS0_10FileHandleE(s64*, void*);


// ============================================================================
// FUN_71035414c0 — read_and_decompress_from_arc
// Reads compressed data from the ARC file and decompresses it using a
// streaming decompression context (zstd-compatible).
// Flow: seek → read 16-byte header → alloc decomp buf → alloc comp buf →
//   seek to data → read compressed → init decomp stream → stream decompress
//   in loop → cleanup → return decompressed buffer or null.
// [derived: header layout: u32 offset_skip, u32 decomp_size, u32 comp_size]
// [derived: allocation alignment is 4 (not 16 like other resource allocs)]
// [derived: file object accessed at +0x14 (is_open), +0x18 (file_handle),
//  +0x20 (position), +0x22c (is_valid)]
// [derived: decompression uses FUN_71039a4040 with progress tracking and
//  error codes: 0x80000000=generic, 0x80000005=specific, 0x80000006=timeout]
// Address: 0x71035414c0 (928 bytes)
// ============================================================================
u64 FUN_71035414c0(s64* param_1, s64 param_2) {
    s64 file = *param_1;

    // Seek to initial offset
    if (*(u8*)(file + 0x22c) != 0 && *(u32*)(file + 0x14) != 0) {
        *(s64*)(file + 0x20) = param_2;
        if (param_2 >= 0) {
            s64 fsize = 0;
            _ZN2nn2fs11GetFileSizeEPxNS0_10FileHandleE(&fsize, *(void**)(file + 0x18));
        }
    }

    // Read 16-byte header
    if (*(u8*)(*param_1 + 0x22c) == 0) return 0;
    u32 header[4];
    if (FUN_71037c6940((void*)*param_1, header, 0x10) != 0x10) return 0;

    // Parse header
    u32 decomp_size = header[1];
    u32 comp_size = header[2];

    // Allocate decompressed buffer
    u64 decomp_alloc = (decomp_size == 0) ? 1 : (u64)decomp_size;
    u8* decomp_buf = (u8*)je_aligned_alloc(4, decomp_alloc);
    if (decomp_buf == nullptr) {
        if (DAT_7105331f00 == nullptr) return 0;
        u32 oom_flags = 0;
        s64 oom_size = (s64)decomp_alloc;
        u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                 (DAT_7105331f00, &oom_flags, &oom_size);
        if ((r & 1) == 0) return 0;
        decomp_buf = (u8*)je_aligned_alloc(4, decomp_alloc);
        if (decomp_buf == nullptr) { FUN_710392e590(decomp_buf); return 0; }
    }

    {
        // Allocate compressed buffer
        u64 comp_alloc = (comp_size == 0) ? 1 : (u64)comp_size;
        u8* comp_buf;
        comp_buf = (u8*)je_aligned_alloc(4, comp_alloc);
        if (comp_buf == nullptr) {
            if (DAT_7105331f00 == nullptr) goto LAB_free_both_fail;
            u32 oom_flags = 0;
            s64 oom_size = (s64)comp_alloc;
            u64 r = ((u64(*)(s64*, u32*, s64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if ((r & 1) == 0) goto LAB_free_both_fail;
            comp_buf = (u8*)je_aligned_alloc(4, comp_alloc);
            if (comp_buf == nullptr) goto LAB_free_both_fail;
        }

        // Seek to data start (base_offset + header[0])
        file = *param_1;
        if (*(u8*)(file + 0x22c) != 0 && *(u32*)(file + 0x14) != 0) {
            s64 data_pos = (u64)header[0] + param_2;
            *(s64*)(file + 0x20) = data_pos;
            if (data_pos >= 0) {
                s64 fsize = 0;
                _ZN2nn2fs11GetFileSizeEPxNS0_10FileHandleE(&fsize, *(void**)(file + 0x18));
            }
        }

        s64 state[2];
        u32 err;

        // Read compressed data
        if (*(u8*)(*param_1 + 0x22c) == 0 ||
            FUN_71037c6940((void*)*param_1, comp_buf, (u64)comp_size) != (s64)(u64)comp_size) {
            FUN_710392e590(decomp_buf);
            decomp_buf = comp_buf;
            goto LAB_free_both_fail;
        }

        // Check sizes are valid
        if (comp_size == 0 || decomp_size == 0) {
            FUN_710392e590(comp_buf);
            goto LAB_free_both_fail;
        }

        // Initialize streaming decompression
        state[0] = 0;
        state[1] = 0;
        err = FUN_7103541ae0(state);

        // Helper lambdas for cleanup
        // [derived: cleanup pattern: finalize context → custom dealloc or je_free]
        #define CLEANUP_CTX(ctx_val) do { \
            if (*(s64*)((ctx_val) + 0x1a8) == 0) { \
                FUN_710399f880((void*)(ctx_val)); \
                typedef void (*DFn)(void*,void*); \
                DFn d = *(DFn*)((ctx_val) + 0x198); \
                if (d == nullptr) FUN_710392e590((void*)(ctx_val)); \
                else d(*(void**)((ctx_val) + 0x1a0), (void*)(ctx_val)); \
                state[0] = 0; \
            } \
        } while(0)
        #define CLOSE_STREAM() do { \
            if (state[1] != 0) { \
                u64 cr = FUN_71039a3e70((void*)state[1]); \
                if (cr < 0xffffffffffffff89ULL) state[1] = 0; \
            } \
        } while(0)

        if (err == 0 && state[1] != 0) {
            // Streaming decompression loop
            u8* out_ptr = comp_buf;
            u64 out_rem = (u64)comp_size;
            u8* in_ptr = decomp_buf;
            u64 in_rem = (u64)decomp_size;

            do {
                s64 io_out[4];
                io_out[0] = (s64)out_ptr;
                io_out[1] = (s64)out_rem;
                io_out[2] = (s64)in_ptr;
                io_out[3] = (s64)in_rem;
                u64 consumed_out = 0;
                u64 consumed_in = 0;
                s64 res = FUN_71039a4040((void*)state[1], io_out, &io_out[2]);
                s64 ctx = state[0];
                u64 c_in = (u64)io_out[3];
                u64 c_out = (u64)io_out[1];

                if ((u64)res < 0xffffffffffffff89ULL) {
                    consumed_in = c_in;
                    consumed_out = c_out;
                    if (c_in >= consumed_out) {
                        err = (res != 0) ? (u32)res : 0;
                        if (err == 0) goto LAB_check_done;
                    }
                } else {
                    s32 neg = -(s32)res;
                    u32 code = 0x80000000;
                    if (neg == 0x48) code = 0x80000006;
                    err = 0x80000005;
                    if (neg != 0x46) err = code;
                    consumed_in = in_rem;
                    consumed_out = out_rem;
                    if (err != 1) goto LAB_check_done;
                }

                out_ptr += consumed_out;
                out_rem -= consumed_out;
                in_ptr += consumed_in;
                in_rem -= consumed_in;
                _ZN2nn2os11YieldThreadEv();
            } while (state[1] != 0);
        }

        err = 0x80000003;
        if (state[0] != 0) { CLEANUP_CTX(state[0]); }
        CLOSE_STREAM();
        goto LAB_free_comp;

    LAB_check_done:
        if (err != 0) {
            if (state[0] != 0) { CLEANUP_CTX(state[0]); }
            CLOSE_STREAM();
        } else {
            if (state[0] != 0) {
                if (*(s64*)(state[0] + 0x1a8) == 0) {
                    CLEANUP_CTX(state[0]);
                    CLOSE_STREAM();
                    err = 0;
                    if (state[0] != 0) { CLEANUP_CTX(state[0]); }
                    CLOSE_STREAM();
                }
            }
        }

    LAB_free_comp:
        #undef CLEANUP_CTX
        #undef CLOSE_STREAM
        FUN_710392e590(comp_buf);
        if (err != 0) {
        LAB_free_both_fail:
            FUN_710392e590(decomp_buf);
        LAB_return_null:
            return 0;
        }
        return (u64)decomp_buf;
    }
}
