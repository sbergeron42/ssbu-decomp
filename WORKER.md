# Worker: pool-b

## Model: Opus

## Task: Near-miss matching grind + optnone sweep

### Phase 1: Find and fix near-miss functions (80%+ match)
Use compare_bytes.py on N-quality functions to find ones that are close. Fix the 1-2 instruction diffs.

### Phase 2: optnone sweep for remaining -O0 regions
Check fun_med_final_d_*.cpp files for functions in the 0x71039xxxxx range that need optnone.

### NO naked asm. Compare each function against binary before fixing.

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
