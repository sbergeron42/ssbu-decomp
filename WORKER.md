# Worker: pool-a

## Model: Opus

## Task: Resource service decomp — ResServiceNX init (FUN_710374f360, 19,552 bytes)

This is the C2ResourceServiceNX initialization function. It mounts the ROM filesystem, creates three worker threads (ResUpdateThread, ResLoadingThread, ResInflateThread), and initializes the resource loading queues.

### Type Headers Available
- `include/resource/ResServiceNX.h` — ResServiceNX struct (all fields named from ARCropolis community RE)
- `include/resource/LoadedArc.h` — ARC archive structures
- `include/resource/containers.h` — CppVector, ResList, ListNode, LoadInfo

### Key Context
- Service name string "C2ResourceServiceNX" at 0x710437acf3
- Thread names: "ResUpdateThread" (0x710439aab7), "ResLoadingThread" (0x710426d64f), "ResInflateThread" (0x71042d3cf2)
- Calls nn::fs::MountRom at 0x71039c76c0
- Calls FUN_7103549620 (task worker pool creator) twice for thread spawning
- All field names are [derived: ARCropolis community RE, validated by mod loader hooks]

### Approach
1. Decompile FUN_710374f360 in Ghidra
2. Map the initialization logic to ResServiceNX struct fields
3. Write C++ using the resource headers — use `svc->filesystem_info`, `svc->res_loading_thread`, etc.
4. This function is 19,552 bytes — it will need to be broken into logical sections
5. Focus on getting the structure right; matching may require multiple attempts on a function this large

### Output: src/resource/ResServiceNX_init.cpp

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN create: src/resource/ResServiceNX_init.cpp, and edit include/resource/*.h if needed
- Use ARCropolis field names with [derived: ARCropolis] provenance
- 3-attempt limit per sub-section, but document what you learn even if non-matching
