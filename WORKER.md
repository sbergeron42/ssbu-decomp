# Worker: pool-a

## Model: Opus

## Task: Resource service — remaining small functions + Fiber lifecycle

### Targets
- `get_current_fiber` (48B) — 0x710353c580
- `finalize` (176B) — 0x710353c350
- `~Fiber` (320B) — 0x710353c210
- `FUN_710353e1e0` (336B)
- `FUN_710353c130` (208B)
- `FUN_710354f380` (240B), `FUN_710354fa40` (304B)
- `FUN_710354b370` (320B), `FUN_710354f900` (320B)
- `FUN_710354ff10` (368B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_remaining_small.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
