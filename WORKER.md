# Worker: pool-d

## Model: Opus

## Task: Resource service decomp — small functions (<1,000 bytes)

Decomp the smaller resource service helper functions using the ARCropolis type headers.

### Target Functions
- `GlobalParameter` (0x7103756640) — 896 bytes (already named)
- `FUN_7103754ef0` — 624 bytes
- `FUN_7103755a50` — 608 bytes
- `FUN_7103754c70` — 480 bytes
- `FUN_710375f480` — 464 bytes
- `FUN_710375db40` — 3,888 bytes
- `FUN_710375f650` — 3,840 bytes
- `deal_with_inputs?` (0x710375ea70) — 2,576 bytes
- Plus any remaining small functions in 0x710373e000–0x7103760000

### Type Headers Available
- `include/resource/ResServiceNX.h` — ResServiceNX struct
- `include/resource/LoadedArc.h` — ARC archive structures
- `include/resource/containers.h` — CppVector, ResList, ListNode, LoadInfo

### Approach
1. Start with the smallest functions — these are likely helpers/accessors that reveal struct patterns
2. Decompile in Ghidra, identify which resource structs they access
3. Write C++ using the resource headers
4. Use insights from small functions to help understand larger ones

### Output: src/resource/res_helpers.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN create: src/resource/res_helpers.cpp, and edit include/resource/*.h if needed
- Use ARCropolis field names with [derived: ARCropolis] provenance
- 3-attempt limit per function
