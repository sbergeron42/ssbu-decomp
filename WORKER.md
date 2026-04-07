# Worker: pool-b

## Model: Opus

## Task: Fix N-quality functions to match — idiomatic C++ only

### Goal
Grind through N-quality functions one by one. For each function:
1. Run `python tools/compare_bytes.py FUN_name` to see what doesn't match
2. Decompile the original in Ghidra to see what it SHOULD be
3. Fix the source to match — correct types, control flow, expression order
4. Verify with compare_bytes again
5. 3-attempt limit, then move on

### Target Files (highest N-quality density, 16-200 byte functions)
- `src/app/fun_batch_d5_052.cpp` — 61 N-quality functions
- `src/app/fun_batch_d_008.cpp` — 44 N-quality functions
- `src/app/fun_easy_000.cpp` — 43 N-quality functions

### Rules
- **NO naked asm.** Every function must be idiomatic C++.
- **NO blind pattern application.** Check each function against the binary FIRST.
- Compare bytes → identify the SPECIFIC mismatch → fix it
- Common fixes: wrong return type (u64→u32), wrong param type (s64→u64), wrong store target, missing/extra cast, expression reordering
- If a function matches except for prologue scheduling, add `asm volatile("" ::: "x29")` barrier
- Derivation chains on any new offset tags

### Quick Reference
```
# Compare a specific function:
python tools/compare_bytes.py FUN_71XXXXXXXXX

# Single-file compile:
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

# Decompile original in Ghidra:
mcp__ghidra__decompile_function_by_address("0x71XXXXXXXXX")
```
