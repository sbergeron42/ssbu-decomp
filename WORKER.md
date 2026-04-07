# Worker: pool-b

## Model: Opus

## Task: Identify zstd library in binary — COMPLETE

### Findings

`directory_file_read` at 0x71039a4040 (11,408 bytes) is **ZSTD_decompressStream** from **zstd v1.3.7**.

- **Library**: facebook/zstd v1.3.7 (October 2018)
- **Config**: `ZSTD_LEGACY_SUPPORT=4` (supports format versions 0.4–0.7)
- **Function**: `ZSTD_decompressStream` with inlined legacy dispatch
- **Struct**: `ZSTD_DCtx` at 0x271F0 bytes (matches binary exactly)
- **Source added**: `lib/zstd/` (common, decompress, legacy directories)

### Evidence
- ZSTD_DCtx field offsets match v1.3.7 struct layout exactly
- `WILDCOPY_OVERLENGTH=8` (0x20008 litBuffer) confirms 1.3.x (changed to 32 in 1.4.x)
- `sizeof(ZSTD_DCtx)=0x271F0` matches `staticSize - 0x271F0` check in binary
- State machine matches `ZSTD_dStreamStage` enum (zdss_init through zdss_flush)
- All fields present: hostageByte, noForwardProgress, ddictIsCold, bmi2
- Legacy magic numbers 0xfd2fb524-527, XXH64 constants confirmed
- Stall detection at 15 iterations matches `ZSTD_NO_FORWARD_PROGRESS_MAX`

### Why not byte-matching
NX clang fork generates different prologue scheduling, register allocation, and
instruction ordering vs upstream clang 8.0.0. For an 11,408-byte function with
extensive inlined legacy code, manual asm barrier fixups are impractical (~2,852
instructions, 0.2% natural match rate).

### Sub-function mapping
| Binary Address | Size | zstd Function |
|---|---|---|
| 0x71039a4040 | 11,408 | ZSTD_decompressStream |
| 0x71039a6cd0 | ~336 | ZSTD_decompressLegacyStream |
| 0x71039a0ce0 | ~564 | ZSTD_getFrameHeader_advanced |
| 0x71039a10a0 | ~1,136 | ZSTD_decompressContinue |
| 0x71039a1580 | ~5,960 | ZSTD_decompressBlock_internal |
| 0x710399fe40 | — | FSE_readNCount (FSE table decode) |
| 0x71039a0f50 | — | ZSTD_buildFSETable |
| 0x71039a8430 | — | ZSTD_loadEntropy (dictionary) |
| 0x710399f530 | — | XXH64_update |
| 0x710399f6c0 | — | XXH64_digest |
| 0x71039b2c70 | — | ZSTDv05_init (legacy v0.5) |
| 0x71039b86d0 | — | ZSTDv06_init (legacy v0.6) |
| 0x71039bc3f0 | — | ZSTDv07_init (legacy v0.7) |
| 0x71039aab60 | — | ZSTDv04_decompress (block decoder) |
| 0x71039b3370 | — | ZSTDv05_decompress (block decoder) |
| 0x71039b88f0 | — | ZSTDv06_decompress (block decoder) |
| 0x71039bc6c0 | — | ZSTDv07_decompress (block decoder) |

### Next assignment
Awaiting new target from orchestrator.
