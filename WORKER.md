# Worker: pool-a

## Model: Opus

## Task: Resource service — small/medium uncompiled functions

Decomp the remaining small/medium resource area functions using the resource headers.

### Target Functions (sorted by size, smallest first)
- `FUN_7103741010` — 336 bytes
- `FUN_7103757140` — 336 bytes
- `start_prepo_report` (0x710375a4e0) — 336 bytes (already named)
- `FUN_7103754500` — 304 bytes
- `FUN_7103758e20` — 304 bytes
- `FUN_7103755270` — 288 bytes
- `FUN_710375f480` — 464 bytes
- `FUN_7103754ef0` — 624 bytes
- `FUN_7103755a50` — 608 bytes
- `GlobalParameter` (0x7103756640) — 896 bytes (already named)

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- Output: src/resource/res_small_funcs.cpp
- Use resource headers with [derived: ARCropolis] or [inferred:] tags on every offset
- 3-attempt limit per function
- Not every function here is resource-related — if it's nn::friends or nn::mii, document what it is and move on
