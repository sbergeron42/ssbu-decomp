// res_version_resolver.cpp — Recursive ARC filesystem version resolver
// Address: 0x7103542f30 (104 bytes)

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// Global FilesystemInfo singleton
// [derived: 13.0.1 Ghidra address 0x7105330f20 -> 13.0.4 address 0x7105331f20]
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// ============================================================================
// FUN_7103542f30 — resolve_arc_version
// If *version == 0xFFFF (unresolved sentinel), resolves it from the global
// ARC filesystem header version (masked to 24 bits). Recurses once to
// handle chained resolution, then caches the result back to *version.
// [derived: access chain: DAT_7105331f20->path_info(+0x78)->arc(+0x00)->fs_header(+0x40)->version(+0x3C)]
// [derived: recursive bl at 0x7103542f84, single-exit-point with tail-merged returns]
// [derived: callers in res_loading_pipeline.cpp, res_post_processing.cpp use s32 return]
// Address: 0x7103542f30 (104 bytes)
// ============================================================================
extern "C" s32 FUN_7103542f30(u32* version) {
    s32 val = (s32)*version;
    if (val != (s32)0xFFFF) {
        return val;
    }
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    if (DAT_7105331f20 == nullptr) {
        return (s32)0xFFFF;
    }
    u32 local[2];
    local[0] = ((PathInformation*)DAT_7105331f20->path_info)->arc->fs_header->version & 0xFFFFFF;
    if (local[0] == 0xFFFF) {
        return (s32)0xFFFF;
    }
    val = FUN_7103542f30(local);
    *version = (u32)val;
    return val;
}
