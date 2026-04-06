# Worker: pool-b

## Model: Opus

## Task: Resource service decomp — game_ldn_initialize helpers

### Status
- **FUN_7103741520** (1,136 bytes) — Language detection — **VERIFIED MATCH** (101/117 instructions, 16 diffs are BL relocations only)
- **game_ldn_initialize** (22,464 bytes) — **BLOCKED**: Ghidra decompilation fails (function too complex for Ghidra's decompiler engine). Also FUN_710374f360 (ResServiceNX init, 19,552 bytes) and FUN_7103747270 fail similarly.
- Smaller helper functions (FUN_7103741010, FUN_7103741260, FUN_7103741330, FUN_7103741410, FUN_7103740880) decompiled in Ghidra, cached at /tmp/ghidra_results.txt.

### Blocker: 3 largest resource service functions exceed Ghidra decompiler limits
- game_ldn_initialize (22,464 bytes) — Full game init, 143 direct calls, ~6000 instructions
- FUN_7103747270 (~22K bytes) — Unknown, decompilation failed
- FUN_710374f360 (19,552 bytes) — ResServiceNX init, decompilation failed

All three return "Decompilation failed" even with 120s timeout. These need either:
1. Manual decomp from raw disassembly (saved in /tmp/fun_7103741990_disasm.txt)
2. Ghidra function splitting (break into sub-functions)
3. Alternative decompiler (IDA/Binary Ninja)

### Analysis of game_ldn_initialize structure (from disassembly)
1. nn::oe init (performance config, focus, recording)
2. STL container/string setup
3. nn::os event init + thread creation
4. Language detection (FUN_7103741520 — DECOMPED)
5. 5x mutex init at struct offsets
6. nn::nifm network init with error handling
7. nn::account init, user enumeration loop
8. nn::hid init (8 controller objects, vibration, touchscreen, gyro)
9. nn::prepo init
10. Resource hash table binary search + mutex poll loop
11. ResServiceNX allocation (13,176 bytes) + init
12. Post-init buffer configuration

### Type Headers Available
- `include/resource/ResServiceNX.h` — ResServiceNX struct
- `include/resource/LoadedArc.h` — ARC archive structures
- `include/resource/containers.h` — CppVector, ResList, ListNode, LoadInfo

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
