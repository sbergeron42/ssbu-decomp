# Worker: pool-c

## Model: Opus

## Task: Resource service — loading pipeline functions (0x7103540xxx-0x7103542xxx)

These are the functions in the loading pipeline that feed into the main processing loop.

### Targets
- `add_idx_to_table1_and_table2` (272B) — 0x7103540450
- `load_file_by_hash40` (576B) — 0x7103540560
- `load_directory_files` (384B) — 0x7103541080
- `FUN_71035414c0` (928B)
- `lookup_stream_hash` (640B) — 0x7103541860 (different from the one pool-a decomped)
- `FUN_7103541ae0` (288B), `FUN_7103541cb0` (528B)
- `get_info_to_data` (608B) — 0x7103541ec0
- `FUN_7103542120` (1,056B), `FUN_7103542540` (672B), `FUN_71035427e0` (752B)
- `FUN_7103542b10` (528B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_loading_pipeline.cpp
### Do NOT use naked asm. 3-attempt limit.

### Progress
- `add_idx_to_table1_and_table2` (0x7103540450, 272B) — COMPILED, 34% match (register alloc diff)
- `load_file_by_hash40` (0x7103540560, 576B) — already done in res_load_helpers.cpp
- `FUN_71035427e0` (0x71035427e0, 120B) — COMPILED, 67% match (scheduling diff)
- `FUN_7103541080` (0x7103541080, 384B) — COMPILED, 8% match (complex vector pattern)
- `FUN_7103542b10` (0x7103542b10, 528B) — COMPILED, 1% match (complex vector pattern)
- Remaining: FUN_71035414c0, FUN_7103541860, FUN_7103541ae0, FUN_7103541cb0, FUN_7103541ec0, FUN_7103542120, FUN_7103542540

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
