# Worker: pool-a

## Model: Opus

## Task: Fix remaining abort thunks + near-miss grind toward 75%

### Phase 1: Check batch_b/c2/easy files for abort→__throw_out_of_range
Many files still call `abort()` where the binary calls `__throw_out_of_range()`. Check each file — if the binary really calls __throw_out_of_range, fix it.

Files to check: fun_batch_b_*.cpp, fun_batch_c2_*.cpp, fun_easy_*.cpp

### Phase 2: Near-miss grind
For N-quality functions at 80%+ match, find the 1-2 instruction differences and fix them.
Common fixes: return type (u64→u32), condition polarity, visibility("hidden"), asm volatile barriers.

### NO naked asm. Compare each function against binary before fixing.

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
