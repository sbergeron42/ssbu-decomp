# Worker: pool-b

## Model: Opus

## Task: Remaining stub conversions (48-100 byte range) toward 75%

Continue from last session — 656 stubs remaining. Focus on 48-100 byte functions.

### Approach
1. Find N-quality functions that are 48-100 bytes in batch/easy/med_final files
2. Decompile in Ghidra, write correct C++
3. Compare bytes, fix to match

### NO naked asm. Derivation chains on new offsets.

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
