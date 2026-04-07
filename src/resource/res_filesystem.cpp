// Resource filesystem functions — ResServiceNX file/directory operations
// [derived: Ghidra 13.0.4 decompilation]

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"
#include "resource/containers.h"
#include "resource/PathResolver.h"

// Forward declarations for nn::fs (avoid SDK header conflicts)
namespace nn { namespace fs {
    enum DirectoryEntryType { DirectoryEntryType_Directory = 0, DirectoryEntryType_File = 1 };
    struct FileHandle { u64 _internal; };
    struct DirectoryHandle { u64 _internal; };
    int GetEntryType(DirectoryEntryType* out, const char* path);
    int OpenDirectory(DirectoryHandle* out, const char* path, s32 mode);
    void CloseDirectory(DirectoryHandle handle);
    int OpenFile(FileHandle* out, const char* path, int mode);
    void CloseFile(FileHandle handle);
    int GetFileSize(long* size, FileHandle handle);
}}

using namespace resource;

// jemalloc allocator (NX fork 5.1.0)
extern "C" void* je_aligned_alloc(u64 alignment, u64 size);

// libc++ recursive_mutex
namespace std { namespace __1 {
struct recursive_mutex {
    void lock();
    void unlock();
};
template<bool> struct __vector_base_common {
    [[noreturn]] void __throw_length_error() const;
};
}}

// Globals (defined here — we only compile .o files, never link)
// Using hidden visibility to force direct addressing with -fPIC
__attribute__((visibility("hidden"))) FilesystemInfo* DAT_7105331f20;
__attribute__((visibility("hidden"))) void* DAT_7105331f00;

// Singleton globals for path resolver
__attribute__((visibility("hidden"))) PathResolverBase* DAT_710593c288;  // singleton pointer
__attribute__((visibility("hidden"))) u32 DAT_710593c280;               // CAS spinlock
__attribute__((visibility("hidden"))) void* DAT_710593c2b0;             // OOM callback for singleton
__attribute__((visibility("hidden"))) extern char PTR_VirtualAllocHook_71052a7a78[];

// Derived vtable for singleton (applied after base constructor)
__attribute__((visibility("hidden"))) extern char PathResolverDerived_vtable[];  // PTR_LAB_7105240cb8

// Increment loaded filepath reference count
// [derived: called with (FilesystemInfo*, u32 filepath_index) from copy loops]
extern "C" void FUN_7103540450(FilesystemInfo* fs_info, u32 index);

// je_aligned_alloc variant — returns error code (0xc = success needs OOM retry)
extern "C" int FUN_710392dc40(void** out, u32 alignment, u64 size);

// VirtualAllocHook notification
namespace nu {
    void VirtualAllocHook(u64 size, u32 alignment, void* ptr);
}

// AArch64 exclusive monitor intrinsics (for CAS spinlock)
extern "C" void ClearExclusiveLocal();
extern "C" u32 ExclusiveMonitorPass(volatile u32* addr, u32 size);
extern "C" u32 ExclusiveMonitorsStatus();

// ============================================================================
// FUN_710353d5e0 — copy child filepath indices from LoadedDirectory
// ============================================================================
// [derived: Ghidra 13.0.4 decompilation, 384 bytes]
// [derived: reads LoadedDirectory.child_path_indices (CppVector<u32> at +0x10)]
// [derived: 0xFFFFFF is invalid/sentinel filepath index]
// [derived: increments ref count for each valid index via FUN_7103540450]

void FUN_710353d5e0_353d5e0(CppVector<u32>* output, u32 dir_index) {
    FilesystemInfo* fs;
    LoadedDirectory* dirs;
    LoadedDirectory* entry;
    u8 flags;

    if (__builtin_expect(dir_index == 0xFFFFFF, 0)) goto empty;

    fs = DAT_7105331f20;
    if (__builtin_expect(dir_index >= fs->loaded_directory_len, 0)) goto empty;

    // Lock, read flags, unlock
    {
        auto* mtx = reinterpret_cast<std::__1::recursive_mutex*>(fs->mutex);
        mtx->lock();
        dirs = fs->loaded_directories;
        entry = dirs + dir_index;
        flags = entry->flags;
        mtx->unlock();
    }

    // NX Clang fork emits separate tbz+cbz; upstream Clang 8 merges into ccmp chain (+2 insns)
    if (__builtin_expect((flags & 1) == 0, 0)) goto empty;
    if (__builtin_expect(entry == nullptr, 0)) goto empty;

    {
        LoadedDirectory* dir = dirs + dir_index;

        output->end = nullptr;
        output->eos = nullptr;
        output->start = nullptr;

        u32* vec_start = dir->child_path_indices.start;
        u32* vec_end = dir->child_path_indices.end;
        long byte_size = (char*)vec_end - (char*)vec_start;

        if (byte_size == 0) return;

        long count = byte_size >> 2;
        if ((u64)count >> 62 != 0) {
            reinterpret_cast<const std::__1::__vector_base_common<true>*>(output)
                ->__throw_length_error();
        }

        u32* buf = (u32*)je_aligned_alloc(0x10, (u64)byte_size);
        if (buf != nullptr) goto setup;

        if (DAT_7105331f00 != nullptr) {
            u32 param = 0;
            u64 size = (u64)byte_size;
            void** vtable = *(void***)DAT_7105331f00;
            auto fn = reinterpret_cast<u64(*)(void*, u32*, u64*)>(vtable[6]);
            u64 result = fn(DAT_7105331f00, &param, &size);
            if (result & 1) {
                buf = (u32*)je_aligned_alloc(0x10, (u64)byte_size);
                if (buf != nullptr) goto setup;
            }
        }
        buf = nullptr;

    setup:
        output->start = buf;
        output->end = buf;
        output->eos = buf + count;

        vec_start = dir->child_path_indices.start;
        vec_end = dir->child_path_indices.end;

        for (u32* src = vec_start; src != vec_end; src++) {
            *buf = 0xFFFFFF;
            u32 val = *src;
            *buf = val;
            if (val != 0xFFFFFF) {
                FUN_7103540450(DAT_7105331f20, val);
            }
            buf = (u32*)((char*)output->end + 4);
            output->end = buf;
        }
    }
    return;

empty:
    output->end = nullptr;
    output->eos = nullptr;
    output->start = nullptr;
}

// ============================================================================
// FUN_71037c5ff0 — PathResolverBase constructor
// ============================================================================
// [derived: Ghidra 13.0.4 decompilation, 2,288 bytes]
// [derived: initializes vtable + 64 FixedString<512> + trailing state fields]
// [derived: called from singleton creation in FUN_71037c3db0 and FUN_710374f360]
// [note: 572 instructions, fully unrolled stores — no loop in original binary]

__attribute__((visibility("hidden"))) extern char PathResolverBase_vtable[];  // PTR_LAB_7105240d28

// Forward declaration
void FUN_71037c5ff0_37c5ff0(PathResolverBase* self);

// Result type that forces x8 indirect return on AArch64 (> 16 bytes)
// [inferred: caller passes result address in x8, function writes int to *x8]
struct SretResult {
    int code;
    int _pad[4];
};

// ============================================================================
// FUN_71037c3db0 — ResServiceNX path resolution wrapper (2 params)
// ============================================================================
// [derived: Ghidra 13.0.4 decompilation, 368 bytes]
// [derived: gets-or-creates PathResolver singleton, resolves path, dispatches to handler]
// [derived: handler->vtable[6] called on success, error code written on failure]
// [note: x8 = indirect return address, x0 = handler, x1 = path string]

SretResult FUN_71037c3db0_37c3db0(long* handler, const char* path) {
    FixedString<512> src_path;
    FixedString<512> dst_path;

    dst_path.length = 0;
    dst_path.data[0] = 0;
    src_path.length = 0;
    src_path.data[0] = 0;

    src_path.assign_str(path);

    // Get-or-create PathResolver singleton
    // Original layout: creation code is fall-through, "exists" branches forward
    PathResolverBase* singleton = DAT_710593c288;
    if (singleton != nullptr) goto resolve;

    // CAS spinlock acquire — nu::ModuleInitializer<T>::Instance() pattern
    // [derived: same pattern at 0x71037c3db0 and 0x71037c4010 — singleton creation with exclusive monitor]
    // NOTE: not refactored to helper because inlining must match binary exactly
    do {
        u32 val = __builtin_arm_ldaex(&DAT_710593c280);
        if (val != 0) {
            __builtin_arm_clrex();
            goto resolve;
        }
    } while (__builtin_arm_stlex(1, &DAT_710593c280));

    {
        void* mem;
        int err = FUN_710392dc40(&mem, 0x10, 0x8148);
        if (err == 0xc && DAT_710593c2b0 != nullptr) {
            u64 req_size = 0x8148;
            void** vt = *(void***)DAT_710593c2b0;
            auto cb = reinterpret_cast<u64(*)(void*, u64*)>(vt[6]);
            u64 r = cb(DAT_710593c2b0, &req_size);
            if (r & 1) {
                FUN_710392dc40(&mem, 0x10, 0x8148);
            }
        }
        if (*(void**)&PTR_VirtualAllocHook_71052a7a78 != nullptr) {
            nu::VirtualAllocHook(0x8148, 0x10, mem);
        }
        FUN_71037c5ff0_37c5ff0(reinterpret_cast<PathResolverBase*>(mem));
        *reinterpret_cast<void**>(mem) = &PathResolverDerived_vtable;
        reinterpret_cast<u64*>(mem)[0x1027] = 0;
        reinterpret_cast<u64*>(mem)[0x1028] = 0;
        reinterpret_cast<u64*>(mem)[0x1026] = 0;
        DAT_710593c288 = reinterpret_cast<PathResolverBase*>(mem);
    }

resolve:
    {
        singleton = DAT_710593c288;
        void** vtable = reinterpret_cast<void**>(singleton->vtable);
        auto resolve_fn = reinterpret_cast<SretResult(*)(PathResolverBase*, FixedString<512>*, FixedString<512>*)>(vtable[4]);
        SretResult resolve_result = resolve_fn(singleton, &dst_path, &src_path);

        if (resolve_result.code < 0) {
            SretResult r;
            r.code = resolve_result.code;
            return r;
        }

        // Success: dispatch to handler
        auto dispatch = reinterpret_cast<SretResult(*)(long*, FixedString<512>*)>(
            reinterpret_cast<void**>(*handler)[6]);
        return dispatch(handler, &dst_path);
    }
}

void FUN_71037c5ff0_37c5ff0(PathResolverBase* self) {
    self->vtable = &PathResolverBase_vtable;

    // Initialize 64 FixedString<512> slots
    // Original binary stores these fully unrolled (alternating length=0, data[0]=0)
#pragma clang loop unroll(full)
    for (int i = 0; i < 64; i++) {
        self->paths[i].length = 0;
        self->paths[i].data[0] = 0;
    }

    self->path_count = 0;
    self->field_8128 = 0;
    self->field_8120 = 0;
    self->field_8118 = 0;
    // Zero 8 bytes at +0x8110, then set state=1, flag=0
    *reinterpret_cast<u64*>(&self->state) = 0;
    self->state = 1;
    self->flag = 0;
}

// ============================================================================
// FUN_710353a8f0 — filesystem entry scanner/resolver
// ============================================================================
// [derived: Ghidra 13.0.4 decompilation, 1,280 bytes]
// [derived: reads DirectoryEntry array via scanner state, resolves paths via singleton]
// [derived: probes filesystem with nn::fs APIs (GetEntryType, Open/Close, GetFileSize)]
// [derived: outputs filename, size, and flags to param_2 struct]

extern "C" unsigned long strlen(const char*);
extern "C" char* strrchr(const char*, int);
extern "C" void* memcpy(void*, const void*, unsigned long);

// Directory scanner state
// [inferred: Ghidra 13.0.4 decompilation of FUN_710353a8f0]
// [inferred: entries at +0x20 are nn::fs::DirectoryEntry (0x310 bytes each)]
struct DirScannerState {
    u8 pad_0x00[8];             // +0x000
    s32 entry_count;            // +0x008
    u8 pad_0x0c[0xC];           // +0x00C
    s64 total_to_scan;          // +0x018
    u8* entries_ptr;            // +0x020 [inferred: nn::fs::DirectoryEntry array]
    s64 current_index;          // +0x028
    char base_path[514];        // +0x030
    u16 base_path_len;          // +0x232
    u8 is_active;               // +0x234
};

// Filesystem entry output
// [inferred: Ghidra 13.0.4 decompilation of FUN_710353a8f0]
struct FsEntryOutput {
    char filename[256];         // +0x000
    u16 filename_length;        // +0x100
    u8 pad_0x102[6];            // +0x102
    u64 file_size;              // +0x108
    u32 flags;                  // +0x110
    u8 pad_0x114[4];            // +0x114
    u64 field_118;              // +0x118
    u64 field_120;              // +0x120
    u64 field_128;              // +0x128
};

u64 FUN_710353a8f0_353a8f0(DirScannerState** param_1, FsEntryOutput* output) {
    DirScannerState* state = *param_1;

    if (state->is_active == 0) return 0;

    // Init local result state
    FixedString<512> filename_buf;
    filename_buf.data[0] = 0;
    filename_buf.length = 0;
    u64 file_size = 0;
    u64 local_688 = 0;
    u64 local_680 = 0;
    u64 local_678 = 0;
    u32 entry_flags = 0;

    if (state->entry_count == 0) return 0;
    if (state->total_to_scan <= state->current_index) return 0;

    // Build path: base_path + "/" + entry_name
    FixedString<512> full_path;
    full_path.data[0] = 0;
    full_path.length = 0;
    full_path.assign_buf(reinterpret_cast<const u8*>(state->base_path), state->base_path_len);
    full_path.append("/");
    full_path.append(reinterpret_cast<const char*>(
        state->entries_ptr + state->current_index * 0x310));

    // Resolve path via singleton
    FixedString<512> resolved_path;
    resolved_path.data[0] = 0;
    resolved_path.length = 0;
    FixedString<512> resolve_input;
    resolve_input.data[0] = 0;
    resolve_input.length = 0;
    resolve_input.assign_str(full_path.data);

    // Get-or-create singleton (same pattern as FUN_71037c3db0)
    PathResolverBase* singleton = DAT_710593c288;
    if (singleton == nullptr) {
        do {
            u32 val = __builtin_arm_ldaex(&DAT_710593c280);
            if (val != 0) {
                __builtin_arm_clrex();
                goto singleton_ready;
            }
        } while (__builtin_arm_stlex(1, &DAT_710593c280));

        void* mem;
        int err = FUN_710392dc40(&mem, 0x10, 0x8148);
        if (err == 0xc && DAT_710593c2b0 != nullptr) {
            u64 req_size = 0x8148;
            void** vt = *(void***)DAT_710593c2b0;
            auto cb = reinterpret_cast<u64(*)(void*, u64*)>(vt[6]);
            u64 r = cb(DAT_710593c2b0, &req_size);
            if (r & 1) {
                FUN_710392dc40(&mem, 0x10, 0x8148);
            }
        }
        if (*(void**)&PTR_VirtualAllocHook_71052a7a78 != nullptr) {
            nu::VirtualAllocHook(0x8148, 0x10, mem);
        }
        FUN_71037c5ff0_37c5ff0(reinterpret_cast<PathResolverBase*>(mem));
        *reinterpret_cast<void**>(mem) = &PathResolverDerived_vtable;
        reinterpret_cast<u64*>(mem)[0x1027] = 0;
        reinterpret_cast<u64*>(mem)[0x1028] = 0;
        reinterpret_cast<u64*>(mem)[0x1026] = 0;
        DAT_710593c288 = reinterpret_cast<PathResolverBase*>(mem);
    }

singleton_ready:
    {
        singleton = DAT_710593c288;
        void** vtable = reinterpret_cast<void**>(singleton->vtable);
        auto resolve = reinterpret_cast<int(*)(PathResolverBase*, char*, FixedString<512>*)>(vtable[4]);
        int resolve_result = resolve(singleton, resolved_path.data, &resolve_input);
        if (resolve_result < 0) return 0;
    }

    // Probe filesystem
    nn::fs::DirectoryEntryType entry_type;
    int fs_result = nn::fs::GetEntryType(&entry_type, resolved_path.data);
    if (fs_result != 0) return 0;

    if (entry_type == nn::fs::DirectoryEntryType_Directory) {
        nn::fs::DirectoryHandle dir_handle;
        fs_result = nn::fs::OpenDirectory(&dir_handle, resolved_path.data, 1);
        if (fs_result != 0) return 0;
        nn::fs::CloseDirectory(dir_handle);
    } else if (entry_type == nn::fs::DirectoryEntryType_File) {
        nn::fs::FileHandle file_handle;
        fs_result = nn::fs::OpenFile(&file_handle, resolved_path.data, 1);
        if (fs_result != 0) return 0;
        long fsize;
        fs_result = nn::fs::GetFileSize(&fsize, file_handle);
        if (fs_result != 0) return 0;
        nn::fs::CloseFile(file_handle);
        file_size = (u64)fsize;
    } else {
        return 0;
    }

    // Copy resolved path to filename buffer
    unsigned long path_len = strlen(resolved_path.data);
    filename_buf.assign_buf(reinterpret_cast<const u8*>(resolved_path.data), path_len);

    // Extract filename: find last path separator ('/' or '\\')
    // [rewritten: original was Ghidra reverse-scan with decrement-from-zero pattern]
    u64 buf_len = (u64)filename_buf.length;
    if (buf_len != 0) {
        // Scan backwards for last '/' and last '\\'
        u64 slash_pos = 0xFFFFFFFFFFFFFFFF;
        u64 backslash_pos = 0xFFFFFFFFFFFFFFFF;
        for (u64 j = buf_len; j > 0; j--) {
            char c = filename_buf.data[j - 1];
            if (c == '/' && slash_pos == 0xFFFFFFFFFFFFFFFF) {
                slash_pos = j - 1;
            }
            if (c == '\\' && backslash_pos == 0xFFFFFFFFFFFFFFFF) {
                backslash_pos = j - 1;
            }
            if (slash_pos != 0xFFFFFFFFFFFFFFFF && backslash_pos != 0xFFFFFFFFFFFFFFFF) {
                break;
            }
        }

        // Take the later separator position
        u64 sep_pos;
        if (slash_pos == 0xFFFFFFFFFFFFFFFF) {
            sep_pos = backslash_pos;
        } else if (backslash_pos == 0xFFFFFFFFFFFFFFFF || backslash_pos <= slash_pos) {
            sep_pos = slash_pos;
        } else {
            sep_pos = backslash_pos;
        }

        if (sep_pos != 0xFFFFFFFFFFFFFFFF) {
            // Extract substring after separator
            FixedString<512> temp;
            temp.data[0] = 0;
            temp.length = 0;
            u64 start = sep_pos + 1;
            u64 sub_len = buf_len - start;
            if (buf_len <= sub_len) sub_len = buf_len;
            temp.assign_buf(reinterpret_cast<const u8*>(filename_buf.data + start), sub_len);
            memcpy(filename_buf.data, temp.data, 0x201);
            filename_buf.length = temp.length;
        }
    }

    // Set entry flags
    entry_flags = 0x10;  // file flag
    if (entry_type != nn::fs::DirectoryEntryType_File) {
        entry_flags = 0x08;  // directory flag
    }

    // Increment scanner index
    state->current_index++;

    // Extract just the filename (after last '/')
    char* last_slash = strrchr(filename_buf.data, '/');
    const char* name_start = filename_buf.data;
    if (last_slash != nullptr) {
        name_start = last_slash;
    }
    name_start++;

    unsigned long name_len = strlen(name_start);

    // Copy filename to output (char-by-char with length tracking)
    output->filename_length = 0;
    for (unsigned long i = 0; i < name_len; i++) {
        output->filename_length++;
        output->filename[i] = name_start[i];
    }
    output->filename[output->filename_length] = 0;

    // Set flags
    if (!(entry_flags & 2)) {
        output->flags |= 1;
    }
    if (entry_flags & 8) {
        output->flags |= 0x10;
    }

    // Write remaining output fields
    output->file_size = file_size;
    output->field_118 = local_688;
    output->field_120 = local_680;
    output->field_128 = local_678;

    return 1;
}
