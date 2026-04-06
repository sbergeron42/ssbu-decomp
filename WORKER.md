# Worker: pool-c

## Model: Opus

## Task: Resource service — actual ResServiceNX functions (identified by pool-c previous round)

These are real resource service functions found by module affinity analysis, NOT address proximity.

### Target Functions
- `FUN_71037c3db0` (368 bytes) — ResServiceNX singleton path resolution wrapper
- `FUN_71037c4010` (1,344 bytes) — ResServiceNX singleton path resolution (4 params)
- `FUN_71037c5ff0` (2,288 bytes) — ResServiceNX singleton constructor
- `FUN_710353d5e0` (384 bytes) — copy_filepath_vector_from_loaded_directory
- `FUN_710353a8f0` (1,280 bytes) — filesystem entry scanner/resolver

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Derivation Chains (MANDATORY)
Every function and every struct field MUST have provenance:
- `[derived: ARCropolis field_name]` — field name from ARCropolis community RE
- `[derived: smash-arc field_name]` — field from smash-arc ARC format library
- `[inferred: pattern description]` — field name guessed from usage
- `[unknown]` — offset used but no name determinable, use `field_0xNN`
- Any offset like `+0x10`, `+0x68` appearing in code MUST get a confidence tag

### Rules
- Output: src/resource/res_filesystem.cpp
- Use resource headers with derivation chains as above
- 3-attempt limit per function
- These functions may reveal new struct fields — add them to the headers with proper tags
