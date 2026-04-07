#pragma once
#include "types.h"

// LZ4 Frame decompression context
// [derived: LZ4 library v1.8.x, lz4frame.c — struct LZ4F_dctx_s]
// [derived: offset verification from Ghidra 13.0.4 FUN_71035472b0 (LZ4F_decompress)]
// [derived: XXH32 seed constants 0x24234428, 0x85EBCA77, 0x61C8864F confirm XXH32_reset(0)]
// Nintendo SDK 8.2.1 bundles LZ4; game modifies allocator (je_aligned_alloc + OOM retry)

namespace resource {

// XXH32_state_t — xxHash32 streaming state
// [derived: xxHash library, xxhash.h — sizeof = 0x30 (48 bytes)]
struct XXH32_state_t {
    u32 total_len_32;  // +0x00
    u32 large_len;     // +0x04
    u32 v1;            // +0x08
    u32 v2;            // +0x0C
    u32 v3;            // +0x10
    u32 v4;            // +0x14
    u32 mem32[4];      // +0x18
    u32 memsize;       // +0x28
    u32 reserved;      // +0x2C
};
static_assert(sizeof(XXH32_state_t) == 0x30, "XXH32_state_t size mismatch");

// LZ4F_frameInfo_t — decoded frame header information
// [derived: LZ4 library, lz4frame.h — LZ4F_frameInfo_t]
struct LZ4F_frameInfo_t {
    u32 blockSizeID;           // +0x00 [derived: LZ4F_blockSizeID_t enum]
    s32 blockMode;             // +0x04 [derived: 0=blockLinked, 1=blockIndependent]
    s32 contentChecksumFlag;   // +0x08 [derived: 1=whole-frame XXH32 at end]
    u32 frameType;             // +0x0C [derived: LZ4F_frameType_t enum]
    u64 contentSize;           // +0x10 [derived: total uncompressed content size]
    u32 dictID;                // +0x18 [derived: dictionary ID from header]
    s32 blockChecksumFlag;     // +0x1C [derived: 1=per-block XXH32]
};
static_assert(sizeof(LZ4F_frameInfo_t) == 0x20, "LZ4F_frameInfo_t size mismatch");

// LZ4F decompression stages
// [derived: LZ4 library, lz4frame.c — dStage_t enum]
enum LZ4F_dStage : u32 {
    dstage_getFrameHeader    = 0,
    dstage_storeFrameHeader  = 1,
    dstage_init              = 2,
    dstage_getBlockHeader    = 3,
    dstage_storeBlockHeader  = 4,
    dstage_copyDirect        = 5,
    dstage_getBlockChecksum  = 6,
    dstage_getCBlock         = 7,
    dstage_storeCBlock       = 8,
    dstage_flushOut          = 9,
    dstage_getSuffix         = 10,
    dstage_storeSuffix       = 11,
    dstage_getSFrameSize     = 12,
    dstage_storeSFrameSize   = 13,
    dstage_skipSkippable     = 14,
};

// LZ4F_dctx — LZ4 frame decompression context
// [derived: LZ4 library v1.8.x, lz4frame.c — struct LZ4F_dctx_s]
// [derived: all offsets verified against Ghidra 13.0.4 FUN_71035472b0]
// LZ4F_HEADER_SIZE_MIN = 7, LZ4F_HEADER_SIZE_MAX = 19
struct LZ4F_dctx {
    LZ4F_frameInfo_t frameInfo;   // +0x00 (0x20 bytes)
    u32 version;                   // +0x20
    u32 dStage;                    // +0x24 [derived: switch variable in FUN_71035472b0]
    u64 frameRemainingSize;        // +0x28 [derived: decremented after each block]
    u64 maxBlockSize;              // +0x30 [derived: from frame header decode]
    u64 maxBufferSize;             // +0x38 [derived: tmpOutBuffer capacity]
    u8* tmpIn;                     // +0x40 [derived: temp input buffer for partial reads]
    u64 tmpInSize;                 // +0x48 [derived: bytes accumulated in tmpIn]
    u64 tmpInTarget;               // +0x50 [derived: bytes needed to process]
    u8* tmpOutBuffer;              // +0x58 [derived: ring buffer base allocation]
    u8* dict;                      // +0x60 [derived: dictionary/ring buffer current ptr]
    u64 dictSize;                  // +0x68 [derived: dictionary/ring buffer fill level]
    u8* tmpOut;                    // +0x70 [derived: decompressed output ptr]
    u64 tmpOutSize;                // +0x78 [derived: total bytes in tmpOut]
    u64 tmpOutStart;               // +0x80 [derived: bytes already flushed from tmpOut]
    XXH32_state_t xxh;             // +0x88 [derived: content checksum state, 0x30 bytes]
    XXH32_state_t blockChecksum;   // +0xB8 [derived: block checksum state, 0x30 bytes]
    u8 header[20];                 // +0xE8 [derived: frame/block header staging, up to 19+1]
};
static_assert(sizeof(LZ4F_dctx) == 0x100, "LZ4F_dctx size mismatch");

// LZ4F decompression wrapper
// [derived: FUN_71035472b0 accesses param_1[1] as dctx pointer]
// [derived: init_decomp_state (FUN_7103541ae0) uses void** with state[0]/state[1]]
struct LZ4F_wrapper {
    void* workspace;     // +0x00 [derived: ZSTD workspace or LZ4 workspace]
    LZ4F_dctx* dctx;    // +0x08 [derived: ldr x23,[x8,#0x8] at 0x71035472e8]
};

} // namespace resource
