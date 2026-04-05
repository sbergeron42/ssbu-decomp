# Worker: pool-b

## Model: Opus

## Task: Rewrite Ghidra-paste batch_d + batch_d2 files with struct access

Replace raw Ghidra decompiler output with clean C++ using recovered module struct headers.

### Target Files (highest paste density)
- `src/app/fun_batch_d_001.cpp` — 11 funcs, 441 paste score
- `src/app/fun_batch_d2_001.cpp` — 3 funcs, 400 paste
- `src/app/fun_batch_d2_002.cpp` — 2 funcs, 296 paste
- `src/app/fun_batch_d2_007.cpp` — 2 funcs, 231 paste
- `src/app/fun_batch_d2_008.cpp` — 1 func, 525 paste (dense)
- `src/app/fun_batch_d2_005.cpp` — 7 funcs, 156 paste
- `src/app/fun_batch_d2_006.cpp` — 4 funcs, 297 paste

### Workflow (per function)
1. Read the function — identify which module it accesses via offset (check BattleObjectModuleAccessor.h)
2. Rewrite using the module's struct definition (e.g., `acc->status_module` not `*(param_1 + 0x40)`)
3. Replace Ghidra variable names (uVar1, lVar2) with meaningful names
4. Compile the single file: see Quick Reference below
5. Run `python tools/compare_bytes.py <FUN_name>` to check match
6. If it matches → great. If close but not matching → commit anyway (better source is the goal)
7. Move to the next function. Do NOT spend more than 3 attempts on matching.

### Goal
Replace unreadable code with readable code. Both matching AND non-matching rewrites are improvements over Ghidra paste. Do NOT obsess over flipping N→M.

### DO NOT
- Run full build.bat until end of session
- Attempt functions with .inst, naked asm, or SIMD
- Spend time on verify_local.py during iteration
- Use sleep-polling loops for builds — use run_in_background if needed

### Quick Reference
```
# Single-file compile (use this during iteration, NOT full build):
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

# Compare bytes (takes FUNCTION NAME, not address):
python tools/compare_bytes.py FUN_7102xxxxxx

# Module offset cheat sheet (BattleObjectModuleAccessor):
# +0x38 posture, +0x40 status, +0x48 control, +0x50 work, +0x58 ground
# +0x60 camera, +0x68 kinetic, +0x88 motion, +0xA0 attack, +0xA8 damage
# +0xC0 area, +0x140 effect, +0x148 sound
# Full list: include/app/BattleObjectModuleAccessor.h
```

### Rules
- Use struct field access from include/app/modules/
- CAN ONLY edit: fun_batch_d_001.cpp, fun_batch_d2_001.cpp through fun_batch_d2_008.cpp
- 3-attempt limit per function, then move on
- Save Ghidra results to /tmp/ghidra_results.txt
