// Resource filesystem functions — ResServiceNX file/directory operations
// [derived: Ghidra 13.0.4 decompilation]

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"
#include "resource/containers.h"
#include "resource/PathResolver.h"

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

    // CAS spinlock acquire
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
