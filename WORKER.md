# Worker: pool-e

## Model: Opus

## Task: Resource service — thread creation + remaining utility functions

### Targets
- `FUN_710353d000` (864B) — thread creation wrapper (creates ResUpdateThread/LoadingThread/InflateThread)
- `FUN_710353d760` (1,216B)
- `FUN_710353b490` (1,184B)
- `FUN_710353f1b0` (3,344B) — large pipeline function
- `FUN_710353ff00` (1,360B)
- `FUN_7103546000` (384B), `FUN_71035472b0` (3,872B) — if time permits

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_thread_utils.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
