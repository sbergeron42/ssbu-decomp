// res_loading_callees.cpp — Functions called by ResLoadingThread
// Pool-b assignment: decomp callees that support ResLoadingThread (pool-a)
// See WORKER.md for assignment details.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

// Forward declarations for nn::fs (avoid SDK header type conflicts)
namespace nn { namespace fs {
    struct FileHandle { u64 _internal; };
    u32 ReadFile(FileHandle handle, long position, void* buffer, u64 size);
    u32 GetFileSize(long* size, FileHandle handle);
}}

using namespace resource;

// Global FilesystemInfo singleton
// [derived: 13.0.1 Ghidra address 0x7105330f20 -> 13.0.4 address 0x7105331f20]
// [derived: used in FUN_7103542500 to access arc->fs_header->version]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// ============================================================================
// FUN_71037c58c0 — file_read_from_arc
// Reads data from an open FileNX file at the current position.
// On success, advances the file position. If the new position is non-negative,
// queries the file size (likely for bounds checking or cache invalidation).
// [derived: called from ResLoadingThread for streaming reads from data.arc]
// [derived: ldr w8,[x0,#0x14] = is_open; ldr x0,[x0,#0x18] = file_handle;
//           ldr x1,[x20,#0x20] = position; adds x8,x8,x19 = position+size]
// Address: 0x71037c58c0 (128 bytes)
// ============================================================================
u64 FUN_71037c58c0(FileNX* file, void* buffer, u64 size) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    if (file->is_open == 0) {
        return 0;
    }

    nn::fs::FileHandle fh;
    fh._internal = (u64)file->file_handle;

    u32 result = nn::fs::ReadFile(fh, file->position, buffer, size);
    if (result != 0) {
        return 0;
    }

    if (file->is_open != 0) {
        s64 new_pos = file->position + (s64)size;
        file->position = new_pos;
        if (new_pos >= 0) {
            long file_size = 0;
            nn::fs::FileHandle fh2;
            fh2._internal = (u64)file->file_handle;
            nn::fs::GetFileSize(&file_size, fh2);
        }
    }

    return size;
}

// ============================================================================
// FUN_7103542500 — something_file_version (resolve_file_version)
// Resolves a version value: if the input version is 0xFFFF (unset), looks up
// the default version from the ARC filesystem header. Recursive in structure
// but always terminates in one level since the looked-up version is != 0xFFFF.
// [derived: called from ResLoadingThread to resolve Table2Entry version fields]
// [derived: accesses FilesystemInfo->path_info->arc->fs_header->version (masked 24-bit)]
// [derived: returns s32 in w0 despite Ghidra inferring void — callers use w0]
// Address: 0x7103542500 (100 bytes)
// ============================================================================
s32 FUN_7103542500(s32* version) {
    s32 val = *version;
    if (val != (s32)0xFFFF) {
        return val;
    }
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    if (DAT_7105331f20 == nullptr) {
        return (s32)0xFFFF;
    }
    PathInformation* path_info = (PathInformation*)DAT_7105331f20->path_info;
    s32 local[2];
    local[0] = (s32)(path_info->arc->fs_header->version & 0xFFFFFF);
    if (local[0] == (s32)0xFFFF) {
        return (s32)0xFFFF;
    }
    val = FUN_7103542500(local);
    *version = val;
    return val;
}
