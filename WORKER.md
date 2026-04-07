# Worker: pool-e

## Model: Opus

## Task: Resource service — remaining scattered functions

### Targets
- `FUN_710353b490` (1,184B) — if not done by pool-c
- `FUN_7103549620` (1,568B) — task worker pool creator
- `FUN_7103549c40` (704B)
- `FUN_710354b370` (320B)
- `FUN_710354e180` (416B), `FUN_710354e320` (448B)
- `FUN_710354d130` (720B)

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_scattered.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
