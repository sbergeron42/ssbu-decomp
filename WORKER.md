# Worker: pool-b

## Model: Opus

## Task: Resource service — medium functions + inflate chain

### Target Functions
- `FUN_7103753fc0` — 1,344 bytes (singleton init)
- `FUN_7103755cb0` — 2,448 bytes (friends profile init)
- `deal_with_inputs?` (0x710375ea70) — 2,576 bytes
- `inflate` (0x710002c1f0) — 5,936 bytes (zlib core inflate function)
- `zlib_unencode` (0x71000281d0) — 576 bytes

The `inflate` function is the zlib decompression core used by ResInflateThread. It's open-source (zlib), so match against known zlib source like we did with jemalloc.

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Derivation Chains (MANDATORY)
Every function and every struct field MUST have provenance:
- For zlib: `// zlib 1.2.11: inflate.c:1234` — exact upstream file and line
- For resource funcs: `[derived: ARCropolis field_name]` or `[inferred: pattern description]`
- For SDK functions: `[derived: nn::prepo/friends/account SDK call]`
- Any offset like `+0x10`, `+0x68` MUST get a confidence tag — no bare offsets

### Rules
- Output: src/resource/res_medium_funcs.cpp (resource), src/lib/zlib_inflate.cpp (zlib)
- For zlib: use upstream source with `// zlib: inflate.c:line` provenance
- For resource funcs: use resource headers with derivation chains
- 3-attempt limit per function
