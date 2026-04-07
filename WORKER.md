# Worker: pool-d

## Model: Opus

## Task: Resource service — res_service_process_loop sub-functions

FUN_7103542f30 (12,496 bytes) is the combined ResLoadingThread/ResInflateThread processing loop — 6 of 9 ARCropolis hooks land here. It's too large for one session, so decomp the sub-functions it calls first.

### Target Sub-Functions (called by FUN_7103542f30)
Find and decomp functions called from within 0x7103542f30–0x71035460c0 that are:
- Under 2,000 bytes
- Related to file loading, decompression, or resource management
- Use ResServiceNX, FilesystemInfo, or LoadedArc structs

Start by decompiling FUN_7103542f30 in Ghidra (or reading disassembly) to identify its call targets, then decomp the smallest callees first.

### Known Sub-Functions in Area
- `FUN_710353d5e0` (384B) — copy_filepath_vector_from_loaded_directory
- `FUN_710353a8f0` (1,280B) — filesystem entry scanner/resolver
- Look for more in the 0x710353xxxx–0x710354xxxx range

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Derivation Chains (MANDATORY)
- `[derived: ARCropolis hook_name]` for functions matching ARCropolis hooks
- `[derived: smash-arc struct_field]` for ARC format fields
- `[inferred:]` for fields identified from decompilation patterns

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- Output: src/resource/res_load_helpers.cpp
- 3-attempt limit per function
- Do NOT use naked asm — write real C++ or skip the function
