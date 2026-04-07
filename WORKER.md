# Worker: pool-b

## Model: Opus

## Task: Decomp FUN_7103542f30 (version resolver, 104 bytes) + ResLoadingThread callees

### Primary target
`FUN_7103542f30` — 104-byte recursive version resolver. Confirmed by disassembly:
- Prologue at 0x3542f30, ret at 0x3542f94
- `bl #-84` at 0x3542f84 = recursive self-call
- Takes `u32*` param, returns `s32`
- Resolves ARC filesystem version by reading fs_header->version

This should be a quick match — it's small and self-contained.

### Secondary: remaining ResLoadingThread callees
- `FUN_7103544ca0` (~840B) — directory dispatch function (4-case switch), deferred from last round
- Any other undecomped functions called from ResLoadingThread

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_version_resolver.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
