// zstd v1.3.7 — Legacy format decompression (ZSTD_LEGACY_SUPPORT=4)
// Identified by Ghidra analysis of SSBU v13.0.4
//
// zstd bundles separate decompressors for legacy formats v0.4 through v0.7.
// Each version has its own copy of FSE/HUF/block decompression code.
// The streaming wrapper dispatches based on the magic number version nibble.
//
// Modern zstd (v0.8+/0xFD2FB528) is handled by the main ZSTD_decompressStream
// at 0x71039a4040 (already identified as directory_file_read in functions.csv).
//
// Reference: https://github.com/facebook/zstd/tree/v1.3.7/lib/legacy

// =====================================================================
// STREAMING DISPATCHER
// =====================================================================

// 0x71039a6cd0 (5612 bytes)
// ZSTD_decompressLegacyStream
// [derived: switch(param_2) on cases 4,5,6,7 matching legacy version numbers;
//  each case checks the corresponding magic (0xFD2FB524-0xFD2FB527) and
//  dispatches to version-specific decompressContinue functions]
// Source: lib/legacy/zstd_legacy.h — ZSTD_decompressLegacyStream()

// =====================================================================
// V0.4 CHAIN (magic 0xFD2FB524)
// Source: lib/legacy/zstd_v04.c
// DCtx struct at offset +0x2830 from context base
// =====================================================================

// 0x71039af600 (596 bytes)
// ZSTDv04_decompressContinue
// [derived: checks magic -0x2d04adc = 0xFD2FB524 (v0.4);
//  state machine: init(0) -> header(1) -> block_header(2) -> block_decomp(3);
//  block types: 0=compressed, 1=raw, 2=RLE, 3=end]

// 0x71039aab60 (5544 bytes)
// ZSTDv04_decompressBlock — called from ZSTDv04_decompressContinue case 3 (type 0)
// [derived: compressed block decoder for v0.4 format]

// 0x71039ac110 (692 bytes)
// ZSTDv04_FSE_readNCount — FSE normalization count reader
// [derived: bit-stream reader, run-length zero encoding, accuracy log = 0x20 << nibble,
//  output is short array of normalized weights; identical structure at 3 other addresses]

// 0x71039a82c0 (364 bytes)
// ZSTDv04_HUF_readHufWeight — reads Huffman symbol weights via FSE
// [derived: calls FSE_decompress (0x71039a0150), builds cumulative frequency sums,
//  outputs (symbol, bits) pairs for HUF decoding table]

// 0x71039a8430 (1440 bytes)
// ZSTDv04_HUF_readDTableX4 — Huffman multi-level decoding table builder
// [derived: packed entries = symbol | (bits << 16) | flag << 24;
//  unrolled 8x fill loop; two-level decode for long codes vs short codes]

// 0x71039a0150 (2948 bytes)
// FSE_decompress — common Finite State Entropy decompressor
// [derived: called by HUF_readHufWeight, shared across versions;
//  standard FSE: build decoding table from normalized counts, then stream-decode]

// 0x71039a0f50 (328 bytes)
// FSE_buildDTable — builds FSE decoding table from normalized counts
// [derived: confirmed by ZSTD_decompressBlock_internal analysis; called during
//  sequence header decoding for LL/OF/ML tables]

// 0x71039a10a0 (1248 bytes)
// FSE_decompress_wksp or related entropy helper
// [derived: mid-size function in FSE helper range]

// 0x71039a3ca0 (456 bytes)
// ZSTD_copy_match or wildcopy helper
// [derived: 8-byte aligned unrolled copy (4x8 bytes), overlap detection via memmove,
//  typical LZ match copy pattern]

// 0x71039a3e70 (452 bytes)
// ZSTD_copy_match variant (similar to 0x71039a3ca0)

// 0x71039a89d0 (556 bytes)
// HUF_decompress_variant1 — Huffman decompression variant
// [derived: called from ZSTD_decompressBlock_internal for literal decoding;
//  one of multiple HUF decode paths depending on stream count/size]

// 0x71039a8c00 (4600 bytes)
// HUF_decompress4X — Huffman 4-stream parallel decoder
// [derived: called from ZSTD_decompressBlock_internal for compressed literals;
//  largest HUF function, handles 4 independent bitstreams]

// 0x71039a9e00 (3420 bytes)
// HUF_decompress_variant2 — Huffman decompression variant
// [derived: called from ZSTD_decompressBlock_internal as alternate decode path]

// 0x71039ac3d0 (8180 bytes)
// ZSTDv04 large helper (likely decompressSequencesLong or similar)

// 0x71039ae3d0 (4028 bytes)
// ZSTDv04 helper (HUF or sequence related)

// 0x71039af390 (616 bytes)
// ZSTDv04_HUF_decompress helper
// [derived: 616-byte pattern repeats in each version]

// 0x71039af860 (692 bytes)
// ZSTDv04_FSE_readNCount (second copy, same 692-byte pattern)

// 0x71039afb20 (616 bytes)
// ZSTDv04_HUF helper (second copy of 616-byte pattern)

// 0x71039afd90 (3268 bytes)
// ZSTDv04 entropy or sequence helper

// =====================================================================
// V0.5 CHAIN (magic 0xFD2FB525)
// Source: lib/legacy/zstd_v05.c
// DCtx struct at offset +0x6830 from context base
// =====================================================================

// 0x71039b4fc0 (612 bytes)
// ZSTDv05_decompressContinue
// [derived: checks magic -0x2d04adb = 0xFD2FB525 (v0.5);
//  same state machine as v0.4; dispatches to ZSTDv05_decompressBlock for type 0]

// 0x71039b3370 (7248 bytes)
// ZSTDv05_decompressBlock
// [derived: called from ZSTDv05_decompressContinue case 3]

// 0x71039b5230 (692 bytes)
// ZSTDv05_FSE_readNCount (same 692-byte pattern)

// 0x71039b54f0 (376 bytes)
// ZSTDv05_match_copy — LZ match copy utility
// [derived: 376-byte pattern repeated per version]

// 0x71039b5670 (616 bytes)
// ZSTDv05_HUF helper (same 616-byte pattern)

// 0x71039b0a60 (3524 bytes)
// ZSTDv05 HUF_decompress or sequence decoder

// 0x71039b1830 (1192 bytes)
// ZSTDv05 helper

// 0x71039b1ce0 (668 bytes)
// ZSTDv05 sequence decoder
// [derived: 668-byte pattern repeated per version]

// 0x71039b2c70 (1780 bytes)
// ZSTDv05 helper

// 0x71039b58e0 (2704 bytes)
// ZSTDv05 helper

// 0x71039b6370 (3604 bytes)
// ZSTDv05 helper

// =====================================================================
// V0.6 CHAIN (magic 0xFD2FB526)
// Source: lib/legacy/zstd_v06.c
// DCtx struct at offset +0x5430 from context base
// =====================================================================

// 0x71039ba300 (792 bytes)
// ZSTDv06_decompressContinue
// [derived: checks magic -0x2d04ada = 0xFD2FB526 (v0.6);
//  state machine init(0)->header(1)->block_header(2)->block(3);
//  calls FUN_71039b88f0 for compressed block decompression]

// 0x71039b88f0 (6668 bytes)
// ZSTDv06_decompressBlock
// [derived: called from ZSTDv06_decompressContinue case 3]

// 0x71039ba620 (692 bytes)
// ZSTDv06_FSE_readNCount (same 692-byte pattern)

// 0x71039bb340 (376 bytes)
// ZSTDv06_match_copy (same 376-byte pattern)

// 0x71039bb680 (616 bytes)
// ZSTDv06_HUF helper (same 616-byte pattern)

// 0x71039bbed0 (668 bytes)
// ZSTDv06 sequence decoder (same 668-byte pattern)

// 0x71039b86d0 (532 bytes)
// ZSTDv06 small helper

// 0x71039ba8e0 (2648 bytes)
// ZSTDv06 HUF_decompress or entropy helper

// 0x71039bb4c0 (448 bytes)
// ZSTDv06 helper

// 0x71039bb8f0 (1496 bytes)
// ZSTDv06 helper

// =====================================================================
// V0.7 CHAIN (magic 0xFD2FB527)
// Source: lib/legacy/zstd_v07.c
// DCtx struct at offset +0x5430 from context base
// Adds XXH64 content checksumming (not present in v0.4-v0.6)
// =====================================================================

// 0x71039bf5f0 (1152 bytes)
// ZSTDv07_decompressContinue
// [derived: checks magic 0xFD2FB527; skippable frame check (*param_2 >> 4 == 0x184d2a5);
//  XXH64 init: v1=0x60ea27eeadc0b5d6, v2=0xc2b2ae3d27d4eb4f, v4=0x61c8864e7a143579;
//  calls ZSTDv07_decodeFrameHeader, ZSTDv07_decompressBlock, XXH64_update/digest]

// 0x71039bc6c0 (12072 bytes)
// ZSTDv07_decompressBlock — largest legacy decompressor
// [derived: called from ZSTDv07_decompressContinue case 3;
//  v0.7 has the most complex block format of the legacy versions]

// 0x71039bc200 (120 bytes)
// ZSTDv07_decodeFrameHeader
// [derived: checks exact magic 0xfd2fb527; parses FHD byte:
//  bits 6-7 = frame content size field length, bits 0-1 = dictionary ID field,
//  bit 5 = single segment, bit 2 = content checksum;
//  window descriptor: 0x400 << mantissa with fraction bits]

// 0x71039bc170 (120 bytes)
// ZSTDv07 small helper (near frame header parser)

// 0x71039bc3f0 (716 bytes)
// ZSTDv07 FSE/HUF helper

// =====================================================================
// XXH64 (used by zstd v0.7 for content checksums)
// Source: lib/common/xxhash.c (or xxhash.h with XXH_INLINE_ALL)
// =====================================================================

// 0x710399f530 (400 bytes)
// XXH64_update
// [derived: called from ZSTDv07_decompressContinue after block decompression;
//  processes 32-byte blocks with 4 accumulators]

// 0x710399f6c0 (436 bytes)
// XXH64_digest
// [derived: called from ZSTDv07_decompressContinue at frame end for checksum;
//  returns 22-bit truncated hash for comparison]

// 0x710399f880 (1464 bytes)
// XXH64 one-shot or merge/finalize helper

// =====================================================================
// XXH32 (used by LZ4 frame format)
// Already identified in memory — listed here for completeness
// =====================================================================

// 0x710399eb90 (648 bytes) = XXH32 one-shot
// 0x710399ee20 (412 bytes) = XXH32_update
// 0x710399efc0 (236 bytes) = XXH32_digest

// =====================================================================
// LZ4 v1.8.x (used for LZ4F frame decompression)
// Already identified in memory — listed here for completeness
// =====================================================================

// 0x710399d650 (508 bytes) = LZ4F_decodeHeader
// 0x710399d850 (4920 bytes) = LZ4_decompress_safe_usingDict

// =====================================================================
// UNIDENTIFIED IN ZSTD RANGE
// =====================================================================

// 0x71039a1580 (10012 bytes)
// ZSTD_decompressBlock_internal — modern zstd block decompressor (v0.8+/0xFD2FB528)
// [derived: ZSTD_decodeLiteralsBlock + ZSTD_decodeSeqHeaders + ZSTD_decompressSequences
//  fully inlined at -O2. Evidence:
//  - Error codes: -20 (corruption_detected), -72 (srcSize_wrong), -30 (dict_corrupted)
//  - Literal type dispatch: byte[0] & 3 → set_basic/set_rle/set_compressed/set_repeat
//  - FSE max symbols: 35 (MaxLL), 31 (MaxOff), 52 (MaxML) — exact zstd constants
//  - Three interleaved FSE states + offset repeat history[3]
//  - 1<<24 window size heuristic from zstd_decompress.c:1746
//  Source: lib/zstd/decompress/zstd_decompress.c:1715]
// 0x71039b7740 (668 bytes) — 668-byte pattern, likely v0.5/v0.6 boundary helper
