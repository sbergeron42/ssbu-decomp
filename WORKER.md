# Worker: pool-b

## Model: Opus

## Task: Rewrite Ghidra-paste files (round 2) — batch_d series

### Target Files
- `src/app/fun_batch_d_002.cpp` — 23 funcs, 57 paste, 8 module offsets
- `src/app/fun_batch_d_015.cpp` — 26 funcs, 54 paste, 18 module offsets
- `src/app/fun_batch_d_016.cpp` — 19 funcs, 56 paste
- `src/app/fun_batch_d_012.cpp` — 37 funcs, 42 paste, 21 module offsets
- `src/app/fun_batch_d_005.cpp` — 12 funcs, 34 paste, 7 module offsets
- `src/app/fun_batch_d_008.cpp` — 48 funcs, 33 paste, 8 module offsets

### Workflow (per function)
1. Read the function — identify which module it accesses via offset (check BattleObjectModuleAccessor.h)
2. Rewrite using the module's struct definition (e.g., `acc->status_module` not `*(param_1 + 0x40)`)
3. Replace Ghidra variable names (uVar1, lVar2) with meaningful names
4. Single-file compile, compare_bytes, move on. 3-attempt limit.

### Goal
Replace unreadable code with readable code. Non-matching rewrites are still improvements.

### DO NOT
- Run full build.bat until end of session
- Attempt functions with .inst, naked asm, or SIMD
- Use sleep-polling loops — use run_in_background

### Quick Reference
```
# Single-file compile:
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

# Compare bytes (takes FUNCTION NAME, not address):
python tools/compare_bytes.py FUN_7102xxxxxx

# Module offsets: +0x38 posture, +0x40 status, +0x48 control, +0x50 work, +0x58 ground
# +0x60 camera, +0x68 kinetic, +0x88 motion, +0xA0 attack, +0xA8 damage
# +0xC0 area, +0x140 effect, +0x148 sound — full list: include/app/BattleObjectModuleAccessor.h
```

### Rules
- CAN ONLY edit: fun_batch_d_002.cpp, fun_batch_d_005.cpp, fun_batch_d_008.cpp, fun_batch_d_012.cpp, fun_batch_d_015.cpp, fun_batch_d_016.cpp
- 3-attempt limit per function, then move on
