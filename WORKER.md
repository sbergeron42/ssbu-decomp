# Worker: pool-b

## Model: Opus

## Task: Fix N-quality — batch_d5 -O0 jemalloc functions

### Proven techniques (USE THESE):
- `__attribute__((optnone))` for -O0 compiled functions
- `__attribute__((visibility("hidden")))` on extern globals
- `__atomic_load_n(&var, __ATOMIC_ACQUIRE)` for CXA-guard patterns
- `#pragma clang loop unroll(disable)` to prevent unwanted unrolling
- Inline intermediate variables to avoid extra stack spills at -O0

### Target Files
- `src/app/fun_batch_d5_020.cpp` — 94 N-quality
- `src/app/fun_batch_d5_018.cpp` — 84 N-quality
- `src/app/fun_batch_d5_019.cpp` — 82 N-quality

### Method per function
1. `python tools/compare_bytes.py FUN_name`
2. `mcp__ghidra__decompile_function_by_address("0x71XXXXXXXXX")`
3. Fix with optnone + signature corrections
4. Re-compare. 3 attempts max.

### NO naked asm. Idiomatic C++ only.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
