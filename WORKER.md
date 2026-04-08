# Worker: pool-a

## Model: Opus

## Task: Near-miss matching grind + abort thunk sweep in batch_b/c2 files

### Phase 1: abort→__throw_out_of_range in batch_b and batch_c2
Check if remaining batch_b_*.cpp and batch_c2_*.cpp files have abort() thunks that should be __throw_out_of_range(). Verify against binary before fixing.

### Phase 2: Near-miss grind on fun_easy/fun_medium files
Fix N-quality functions at 80%+ match. Common fixes: return type, condition polarity, visibility("hidden"), asm volatile barriers, optnone.

### NO naked asm. Compare each function against binary before fixing.

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
