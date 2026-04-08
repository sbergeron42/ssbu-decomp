# Worker: pool-b

## Model: Opus

## Task: Near-miss matching + optnone sweep on fun_med_final_d files

### Phase 1: optnone for remaining -O0 functions
Check fun_med_final_d_*.cpp files for functions in 0x71039xxxxx that need __attribute__((optnone)).

### Phase 2: Near-miss fixes
Find N-quality functions close to matching (80%+). Fix types, visibility, barriers.

### NO naked asm. Compare each function against binary before fixing.

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
