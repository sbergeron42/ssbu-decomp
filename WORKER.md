# Worker: pool-d

## Model: Opus

## Task: Resource service — remaining post-processing and large functions

### Targets (from previous assignment + new large functions)
- `FUN_71035461f0` (1,472B), `FUN_71035467b0` (848B)
- `FUN_7103546b00` (320B), `FUN_7103546c40` (336B), `FUN_7103546d90` (816B)
- `FUN_7103549f00` (2,272B)
- `FUN_710354b4b0` (848B), `FUN_710354b800` (912B)
- `FUN_710354c720` (544B), `FUN_710354cc80` (400B), `FUN_710354ce10` (704B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_post_processing2.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
