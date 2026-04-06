# Worker: pool-e

## Model: Opus

## Task: Resource service decomp — engine init + main_loop helpers

Decomp the engine initialization chain and main_loop related functions.

### Target Functions
- `FUN_710373e080` — 10,240 bytes (early init, before resource service)
- `FUN_7103740880` — 1,936 bytes
- `FUN_71037569c0` — 1,920 bytes
- `start_prepo_report` (0x710375f650) — if not taken by pool-d
- Any remaining functions in 0x710373e000–0x7103745000

### Type Headers Available
- `include/resource/ResServiceNX.h` — ResServiceNX struct
- `include/resource/LoadedArc.h` — ARC archive structures
- `include/resource/containers.h` — CppVector, ResList, ListNode, LoadInfo

### Key Context
- main_loop is at 0x7103747270 (24,576 bytes) — DO NOT attempt this function, it's too large for one session
- Focus on the helper functions that main_loop calls
- FUN_710373e080 may be early engine init (before resource service)

### Approach
1. Decompile in Ghidra, identify what each function initializes or manages
2. Map to resource service structs where applicable
3. Write C++ using the headers

### Output: src/resource/engine_init.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN create: src/resource/engine_init.cpp, and edit include/resource/*.h if needed
- Use ARCropolis field names with [derived: ARCropolis] provenance
- 3-attempt limit per function
- Do NOT attempt main_loop (0x7103747270) — too large
