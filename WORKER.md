# Worker: pool-c

## Model: Opus

## Task: Fix N-quality — more optnone stubs + batch_d5

### Your techniques from last round worked — keep using them:
- `__attribute__((optnone))` for -O0 stubs
- Correct function signatures
- Hidden visibility on externs

### Target Files
- `src/app/fun_batch_d5_021.cpp` — 80 N-quality
- `src/app/fun_batch_d5_023.cpp` — 62 N-quality
- `src/app/fun_batch_d5_016.cpp` — 48 N-quality

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
