# Worker: pool-a

## Model: Opus

## Completed Work

### ResInflateThread (FUN_71035444C0, 4,608B)
- Structural decomp: compiles, captures full logic, not byte-matched
- All 5 helper functions size-matched:
  - FUN_7103542F30 (104B) — resolve_version_or_default
  - FUN_7103547220 (144B) — free_decomp_context
  - FUN_7103541A60 (128B) — cleanup_decomp_state
  - FUN_7103541AE0 (288B) — init_decomp_state
  - FUN_7103541C80 (16B) — ZSTD custom free wrapper

### Directory Dispatch (FUN_71035456D0, 1,940B)
- Structural decomp: 4-case switch with locale resolution, I/O loop
- Maps to FUN_7103544CA0 in 13.0.1 (address shifted between versions)
- Compiles at 1644/1940 bytes — missing some detail logic

### FUN_71035472b0 — LZ4F_decompress (3,860B target, 3,640B compiled)
- **LIBRARY CODE IDENTIFIED**: LZ4 v1.8.x (Nintendo SDK 8.2.1), lz4frame.c:LZ4F_decompress()
- Previous comment said "zstd streaming decompression" — CORRECTED to LZ4F
- Evidence: XXH32 seed constants (0x24234428, 0x85EBCA77, 0x61C8864F), 15-state machine
- LZ4F_dctx struct fully mapped with verified offsets matching standard lz4frame.c
- Structural decomp: all 15 decompression stages, ring buffer, checksums, OOM retry
- Compiles at 3,640/3,860 bytes (94.3%) — not byte-matched per library code policy
- New header: include/resource/LZ4Frame.h (LZ4F_dctx, XXH32_state_t, LZ4F_frameInfo_t)
- Identified 5 LZ4 library subfunctions in 0x710399xxxx range:
  - FUN_710399d650 = LZ4F_decodeHeader (508B)
  - FUN_710399d850 = LZ4_decompress_safe_usingDict (4,920B)
  - FUN_710399ee20 = XXH32_update (412B)
  - FUN_710399efc0 = XXH32_digest (236B)
  - FUN_710399eb90 = XXH32 (648B)

### Summary
- 6 size-matched helper functions (total ~700 bytes of matched code)
- 3 structural decomps of large functions (documenting ~10,360 bytes of logic)
- All code compiles cleanly

## Headers: include/resource/*.h
## Output: src/resource/ResLoadingThread.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o
```
