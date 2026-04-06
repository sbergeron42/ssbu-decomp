# Worker: pool-e

## Model: Opus

## Task: Resource service — filesystem utility functions (0x710353xxxx range)

Decomp the filesystem utility functions that support the resource loading pipeline. These are called by the main processing loop and handle file lookup, path resolution, and loaded-data management.

### Target Functions
Scan the 0x710353xxxx range for uncompiled functions related to:
- File path/hash lookup
- LoadedArc table access
- FilesystemInfo operations
- LoadedData/LoadedDirectory state management

Start with the smallest functions and work up. Use Ghidra to identify which ones access resource service structs.

### Known Targets
- `FUN_710353d5e0` (384B) — copy_filepath_vector_from_loaded_directory (if not done by pool-c)
- `FUN_710353a8f0` (1,280B) — filesystem entry scanner/resolver (if not done by pool-c)
- Any other uncompiled functions in 0x710353xxxx that access LoadedArc/FilesystemInfo

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Derivation Chains (MANDATORY)
- `[derived: ARCropolis field_name]` or `[derived: smash-arc field_name]` for known fields
- `[inferred:]` for fields identified from decompilation patterns
- Any offset `+0xNN` MUST get a confidence tag

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- Output: src/resource/res_filesystem_utils.cpp
- 3-attempt limit per function
- Do NOT use naked asm
