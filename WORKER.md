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

### Summary
- 6 size-matched helper functions (total ~700 bytes of matched code)
- 2 structural decomps of large functions (documenting ~6,500 bytes of logic)
- All code compiles cleanly

## Headers: include/resource/*.h
## Output: src/resource/ResLoadingThread.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o
```
