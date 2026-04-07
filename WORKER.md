# Worker: pool-a

## Model: Opus

## Task: Resource service — small helpers in 0x710353xxxx (under 400 bytes)

Decomp the smallest remaining resource service functions. These are building blocks for the processing loop.

### Targets (pick from these, smallest first)
- `operator.new/delete` variants (16-128B each) — 0x710353bc20 through 0x710353be70
- `malloc/free/realloc/calloc/aligned_alloc` (16-240B) — 0x710353be80 through 0x710353c0b0
- `get_current_fiber` (48B) — 0x710353c5b0
- `FUN_710353cf40` (112B)
- `get_filepathidx_by_hash40` (288B) — 0x710353d480
- `FUN_710353e030` (288B), `FUN_710353e4e0` (240B), `FUN_710353e1e0` (336B)
- `FUN_710353adf0` (320B), `FUN_710353a790` (352B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_small_helpers.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
