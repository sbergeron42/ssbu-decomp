# Worker: pool-d

## Model: Opus

## Task: Fix N-quality — batch_d5 + med_final files

### Your techniques from last round worked — keep using them:
- `__attribute__((optnone))` for -O0 jemalloc/libc++ code
- `__attribute__((visibility("hidden")))` on externs
- `__atomic_load_n` for CXA-guard patterns
- `#pragma clang loop unroll(disable)`

### Target Files
- `src/app/fun_batch_d5_025.cpp` — 47 N-quality
- `src/app/fun_batch_d5_049.cpp` — 32 N-quality
- `src/app/fun_med_final_c_007.cpp` — 36 N-quality
- `src/app/fun_med_final_c_008.cpp` — 35 N-quality

### Method per function
1. `python tools/compare_bytes.py FUN_name`
2. `mcp__ghidra__decompile_function_by_address("0x71XXXXXXXXX")`
3. Fix with proven techniques
4. Re-compare. 3 attempts max.

### NO naked asm. Idiomatic C++ only.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -mllvm -enable-shrink-wrap=false -mllvm -enable-post-misched=false -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/quick_verify.py build/FILE.o
```

**NOTE**: `-mllvm -enable-shrink-wrap=false -mllvm -enable-post-misched=false` are required to match NX Clang behavior (no shrink-wrapping, no prologue instruction reordering).
