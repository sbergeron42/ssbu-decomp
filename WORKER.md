# Worker: pool-d

## Model: Opus

## Task: Rewrite Ghidra-paste files (round 3) — batch_d5 + batch_c mid-range

### Target Files
- `src/app/fun_batch_d5_050.cpp` — 12 funcs, 32 paste
- `src/app/fun_batch_d5_051.cpp` — 37 funcs, 27 paste
- `src/app/fun_batch_d5_043.cpp` — 92 funcs, 26 paste
- `src/app/fun_batch_d5_009.cpp` — 19 funcs, 23 paste
- `src/app/fun_batch_c_004.cpp` — 40 funcs, 19 paste
- `src/app/fun_batch_c_005.cpp` — 40 funcs, 19 paste

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
- CAN ONLY edit: fun_batch_d5_009.cpp, fun_batch_d5_043.cpp, fun_batch_d5_050.cpp, fun_batch_d5_051.cpp, fun_batch_c_004.cpp, fun_batch_c_005.cpp
