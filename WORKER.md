# Worker: pool-e

## Model: Opus

## Task: Rewrite Ghidra-paste files (round 3) — batch_e + batch_c + batch_d remaining

### Target Files
- `src/app/fun_batch_e_002.cpp` — 5 funcs, 24 paste
- `src/app/fun_batch_e3_004.cpp` — 15 funcs, 13 paste
- `src/app/fun_batch_e2_012.cpp` — 24 funcs, 12 paste
- `src/app/fun_batch_c_002.cpp` — 30 funcs, 16 paste
- `src/app/fun_batch_d_010.cpp` — 36 funcs, 13 paste
- `src/app/fun_batch_d_014.cpp` — 19 funcs, 12 paste

### Workflow
1. Identify module access via offset → rewrite with struct field access
2. Replace Ghidra variable names with meaningful names
3. Single-file compile, compare_bytes, move on. 3-attempt limit.

### Goal
Readable code > matching. Commit improvements even if non-matching.

### DO NOT
- Run full build.bat until end of session
- Attempt functions with .inst, naked asm, or SIMD
- Use sleep-polling loops — use run_in_background

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name  # NOT address

# +0x38 posture, +0x40 status, +0x48 control, +0x50 work, +0x58 ground
# +0x60 camera, +0x68 kinetic, +0x88 motion, +0xA0 attack, +0xA8 damage
# +0xC0 area, +0x140 effect, +0x148 sound
```

### Rules
- CAN ONLY edit: fun_batch_e_002.cpp, fun_batch_e2_012.cpp, fun_batch_e3_004.cpp, fun_batch_c_002.cpp, fun_batch_d_010.cpp, fun_batch_d_014.cpp
