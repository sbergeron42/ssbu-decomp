# Worker: pool-e

## Model: Opus

## Task: Phase 4 — Naked asm audit (batch E: files G-Z + fun_hard/fun_batch remainder)

## Priority: REMOVE NAKED ASM (banned by project rules)

## Context
`__attribute__((naked))` is banned. Your batch covers all non-jemalloc files from G onward. Delete all naked asm functions — they inflate progress without recovering source.

## File Territory
All non-jemalloc files from G through Z that contain naked asm. Run this to find them:
```bash
grep -rl '__attribute__.*naked' src/ | grep -v jemalloc | sort
```
Your batch is everything NOT in pool-a's territory (pool-a has A-F files + fun_batch_c2_019 + fun_batch_c_001 + fun_batch_c_003). You handle:
- `src/app/fun_hard_b_001.cpp`
- `src/app/fun_hard_d_*.cpp` (any with naked)
- `src/app/gameplay_functions.cpp`
- `src/app/GimmickEventPresenter.cpp`
- `src/app/input_mapping.cpp`
- `src/app/ItemHelpers.cpp`
- `src/app/lib.cpp`
- `src/app/Rhombus2.cpp`
- `src/app/stWaterAreaInfo.cpp`
- `src/app/sv_animcmd_effect.cpp`
- `src/app/WeaponKineticEnergyGravity.cpp`
- `src/resource/*.cpp` (any non-jemalloc with naked)
- Any other non-jemalloc files with naked asm not listed in pool-a's territory

## What To Do

For each file:
1. Find all `__attribute__((naked))` functions
2. **DELETE the entire function**
3. If the file becomes empty, delete it
4. Keep non-naked functions in the same file

## Important
- Do NOT touch jemalloc files
- Do NOT try to re-decomp — just delete
- Build must pass after deletions

## Self-Check
```bash
python tools/build.py 2>&1 | tee build_output.txt
# Verify no naked asm remains in your territory:
grep -rl '__attribute__.*naked' src/ | grep -v jemalloc
```

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
