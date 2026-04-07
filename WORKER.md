# Worker: pool-a

## Model: Opus

## Task: Resource service — loading pipeline functions (continued)

Pick up remaining uncompiled functions in the loading pipeline area.

### Targets (from pool-c's range that wasn't finished)
- `FUN_7103541ae0` (288B), `FUN_7103541cb0` (528B)
- `get_info_to_data` (608B) — 0x7103541ec0
- `FUN_7103542120` (1,056B), `FUN_7103542540` (672B)
- `FUN_71035427e0` (752B), `FUN_7103542b10` (528B)
- `FUN_7103540860` (2,080B) — initialize_loaded_directories

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_loading_pipeline.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
