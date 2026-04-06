# Worker: pool-b

## Model: Opus

## Task: Resource service decomp — game_ldn_initialize (FUN_7103741990, 22,672 bytes)

This is the parent initialization function that calls the resource service init. It sets up LDN (local network), initializes the game engine subsystems, and triggers resource loading.

### Type Headers Available
- `include/resource/ResServiceNX.h` — ResServiceNX struct
- `include/resource/LoadedArc.h` — ARC archive structures
- `include/resource/containers.h` — CppVector, ResList, ListNode, LoadInfo

### Key Context
- Called from nnMain (0x71002c5620)
- Calls FUN_710374f360 (ResServiceNX init)
- 22,672 bytes — the largest function in the resource service area
- Likely initializes multiple engine subsystems before resource loading begins

### Approach
1. Decompile FUN_7103741990 in Ghidra
2. Identify the subsystem initialization calls and map to known engine types
3. Write C++ using resource headers where applicable
4. Cross-reference with ARCropolis hooks to identify which parts touch the resource service

### Output: src/resource/game_init.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN create: src/resource/game_init.cpp, and edit include/resource/*.h if needed
- Use ARCropolis field names with [derived: ARCropolis] provenance
- 3-attempt limit per sub-section
