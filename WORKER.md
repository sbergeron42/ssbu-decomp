# Worker: pool-a

## Model: Opus

## Task: Fix N-quality — optnone stubs (fun_easy_000) + batch_d5 -O0 code

### Proven techniques from pools C+D (USE THESE):
- `__attribute__((optnone))` for -O0 compiled functions (jemalloc, libc++ stubs)
- `__attribute__((visibility("hidden")))` on extern globals to eliminate GOT loads
- Correct function signatures (return type u32 vs u64, param types)
- `__atomic_load_n(&var, __ATOMIC_ACQUIRE)` for CXA-guard ldarb patterns

### Target Files
- `src/app/fun_easy_000.cpp` — 82 N-quality [optnone stubs — pool C proved this on easy_003]
- `src/app/fun_batch_d5_024.cpp` — 106 N-quality [likely -O0, pool D proved optnone works]

### Method per function
1. `python tools/compare_bytes.py FUN_name`
2. `mcp__ghidra__decompile_function_by_address("0x71XXXXXXXXX")`
3. Fix: add optnone, fix signatures, fix visibility, fix types
4. Re-compare. 3 attempts max.

### NO naked asm. Idiomatic C++ only.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
