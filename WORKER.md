# Worker: pool-c

## Model: Opus

## Task: Resource service decomp — medium functions (1,000–14,000 bytes)

Decomp the mid-size resource service functions using the ARCropolis type headers.

### Target Functions
- `FUN_710375a630` — 13,584 bytes
- `FUN_710374d270` — 8,432 bytes (called from main_loop)
- `FUN_7103757290` — 7,056 bytes
- `FUN_7103758f50` — 5,520 bytes
- `FUN_7103755cb0` — 2,448 bytes
- `set_format` (0x7103755390) — 1,728 bytes (already named)
- `FUN_7103753fc0` — 1,344 bytes
- `FUN_7103741520` — 1,136 bytes

### Type Headers Available
- `include/resource/ResServiceNX.h` — ResServiceNX struct
- `include/resource/LoadedArc.h` — ARC archive structures
- `include/resource/containers.h` — CppVector, ResList, ListNode, LoadInfo

### Results
- `FUN_7103741520` (get_language_index) — **VERIFIED MATCH** (100% modulo relocations)
- `set_format` (0x7103755390) — **COMPILED**, body matches, prologue divergence (NX Clang fork)
- `FUN_7103753fc0` — SKIPPED: compiler-generated singleton init, not resource service
- `FUN_7103755cb0` — SKIPPED: 100 unrolled memcpy for nn::friends::Profile init
- `FUN_7103758f50` — SKIPPED: graphics rendering setup with exclusive monitors
- `FUN_7103757290` — SKIPPED: Mii renderer init (nn::mii::Database)
- `FUN_710374d270` — SKIPPED: graphics rendering update loop
- `FUN_710375a630` — SKIPPED: massive singleton init (13,584 bytes)

**Note:** 6/8 assigned targets were not resource service functions — they were selected by address proximity, not module affinity. Only get_language_index and set_format are resource-service related.

### Approach
1. Decompile each function in Ghidra
2. Identify which ResServiceNX/FilesystemInfo/LoadedArc fields it accesses
3. Write C++ using the resource headers
4. Start with smaller functions and work up

### Output: src/resource/res_service_funcs.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN create: src/resource/res_service_funcs.cpp, and edit include/resource/*.h if needed
- Use ARCropolis field names with [derived: ARCropolis] provenance
- 3-attempt limit per function
