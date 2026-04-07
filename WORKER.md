# Worker: pool-c

## Model: Opus

## Task: Resource service — large remaining functions (>1500B)

### Targets
- `FUN_71035461f0` (1,472B)
- `FUN_710353c5b0` (1,504B) — setup/init
- `FUN_710354fb70` (928B), `FUN_710354f470` (1,168B)
- `FUN_7103549f00` (2,272B)
- `FUN_710354a7e0` (2,960B), `FUN_710354bb90` (2,960B)
- `FUN_710354e4e0` (3,360B) — if time permits

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_remaining_large.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
