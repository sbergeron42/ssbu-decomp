# Worker: pool-d

## Model: Opus

## Task: Resource service — post-processing loop functions (0x7103546xxx-0x710354fxxx)

Functions after the main processing loop — likely handle post-load processing, verification, and cleanup.

### Targets (pick from these)
- `FUN_7103546000` (384B), `FUN_7103546180` (112B)
- `FUN_71035461f0` (1,472B), `FUN_71035467b0` (848B)
- `FUN_7103546b00` (320B), `FUN_7103546c40` (336B), `FUN_7103546d90` (816B)
- `FUN_7103547110` (176B), `FUN_71035471c0` (240B)
- `FUN_71035481d0` (112B), `FUN_7103548240` (208B)
- `FUN_7103549620` (1,568B) — task worker pool creator
- `FUN_7103549c40` (704B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_post_processing.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
