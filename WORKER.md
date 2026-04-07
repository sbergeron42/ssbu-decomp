# Worker: pool-c

## Model: Opus

## Task: Resource service — remaining pipeline functions from previous assignment

Continue with the remaining functions from your previous assignment that weren't finished.

### Remaining Targets
- `FUN_71035414c0` (928B)
- `FUN_7103541860` (640B) — lookup_stream_hash variant
- `FUN_7103541ae0` (288B)
- `FUN_7103541cb0` (528B)
- `FUN_7103541ec0` (608B) — get_info_to_data
- `FUN_7103542120` (1,056B)
- `FUN_7103542540` (672B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_loading_pipeline.cpp (append to existing)
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
