# Worker: pool-a

## Model: Opus

## Task: Remaining stub conversions + near-miss fixes toward 75%

Pool B found 656 remaining stubs (28+ bytes) needing Ghidra decompilation. Focus on the 157 small ones (28-48 bytes) — likely simple getters/setters.

### Approach
1. Find N-quality functions in batch_b/c2/easy/med_final files that are 28-48 bytes
2. Decompile in Ghidra, write correct C++
3. Compare bytes, fix to match
4. Also fix any remaining abort→__throw_out_of_range in files not yet swept

### NO naked asm. Derivation chains on new offsets.

### Quick Reference
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o
```
