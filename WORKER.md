# Worker: pool-d

## Model: Opus

## Task: Resource service — remaining medium pipeline functions

### Targets
- `FUN_710354d400` (3,456B)
- `FUN_710354e4e0` (3,360B)
- `FUN_710354f200` (384B), `FUN_710354f380` (240B)
- `FUN_710354f470` (1,168B)
- `FUN_710354f900` (320B), `FUN_710354fa40` (304B)
- `FUN_710354ff10` (368B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_pipeline_medium.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
