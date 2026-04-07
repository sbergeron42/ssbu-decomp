# Worker: pool-e

## Model: Opus

## Task: Resource service — fiber/thread + large pipeline functions

### Targets
- `~Fiber` (320B) — 0x710353c210
- `finalize` (176B) — 0x710353c350
- `switch_to_fiber` (384B) — 0x710353c400
- `setup` (1,504B) — 0x710353c5b0
- `get_hit_entry_id` (944B) — 0x710353cb90
- `FUN_710353d000` (864B) — thread creation wrapper
- `FUN_710353d760` (1,216B)
- `FUN_710353b490` (1,184B)
- `FUN_710353f1b0` (3,344B) — if time permits
- `FUN_710353ff00` (1,360B) — if time permits

### Headers: include/resource/*.h
### Derivation Chains MANDATORY: [derived:] or [inferred:] on every offset
### Output: src/resource/res_fiber_thread.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
