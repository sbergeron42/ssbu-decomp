# Worker: pool-d

## Model: Opus

## Task: Rewrite Ghidra-paste batch_d4 (011-026) files with struct access

Replace raw Ghidra decompiler output with clean C++ using recovered module struct headers.

### Target Files (highest paste density + module offset patterns)
- `src/app/fun_batch_d4_013.cpp` — 25 funcs, 653 paste (highest in project), 66 module offsets
- `src/app/fun_batch_d4_017.cpp` — 13 funcs, 311 paste, 20 module offsets
- `src/app/fun_batch_d4_019.cpp` — 18 funcs, 169 paste, 70 module offsets (highest modoff!)
- `src/app/fun_batch_d4_012.cpp` — 19 funcs, 101 paste, 20 module offsets
- `src/app/fun_batch_d4_011.cpp` — 15 funcs, 134 paste, 9 module offsets
- `src/app/fun_batch_d4_016.cpp` — 13 funcs, 165 paste
- `src/app/fun_batch_d4_014.cpp` — 16 funcs, 51 paste, 16 module offsets

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
- CAN ONLY edit: fun_batch_d4_011.cpp through fun_batch_d4_026.cpp
- 3-attempt limit per function, then move on
- Save Ghidra results to /tmp/ghidra_results.txt
