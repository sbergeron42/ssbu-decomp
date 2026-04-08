# Worker: pool-e

## Model: Opus

## Task: Fix N-quality functions to match — idiomatic C++ only

### Target Files
- `src/app/fun_med_final_c_007.cpp` — 33 N-quality functions
- `src/app/fun_batch_d5_049.cpp` — 32 N-quality functions
- `src/app/fun_batch_d_009.cpp` — 32 N-quality functions

### Method per function
1. `python tools/compare_bytes.py FUN_name` — see what doesn't match
2. `mcp__ghidra__decompile_function_by_address("0x71XXXXXXXXX")` — see what binary does
3. Fix source to match (types, control flow, expressions)
4. Re-compare. 3 attempts max.

### Rules
- **NO naked asm.** Idiomatic C++ only.
- **NO blind patterns.** Check each function individually.
- Derivation chains on any new offset tags

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
