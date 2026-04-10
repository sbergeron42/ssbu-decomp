# Worker: pool-a

## Model: Opus

## Task: Phase 4 — Naked asm audit (batch A: files A-F + fun_batch_c2_019)

## Priority: REMOVE NAKED ASM (banned by project rules)

## Context
`__attribute__((naked))` is banned. 218 naked asm functions exist across 51 non-jemalloc files. Your job: delete them. Naked asm inflates progress metrics without recovering source code. Jemalloc files are excluded (library code).

## File Territory
All non-jemalloc files from A through F that contain naked asm:
- `src/app/AreaContactLog.cpp`
- `src/app/AttackAbsoluteData.cpp`
- `src/app/AttackData.cpp`
- `src/app/audio_functions.cpp`
- `src/app/BattleObjectSlow.cpp`
- `src/app/BattleObjectWorld.cpp`
- `src/app/BossManager.cpp`
- `src/app/Circle.cpp`
- `src/app/DamageInfo.cpp`
- `src/app/DamageLog.cpp`
- `src/app/FighterBayonettaFinalModule.cpp`
- `src/app/FighterCutInManager.cpp`
- `src/app/FighterInformation.cpp`
- `src/app/FighterKineticEnergyMotion.cpp`
- `src/app/FighterManager.cpp`
- `src/app/FighterParamAccessor2.cpp`
- `src/app/fun_batch_c2_019.cpp` (55 naked functions — biggest single file)
- `src/app/fun_batch_c_001.cpp`
- `src/app/fun_batch_c_003.cpp`

## What To Do

For each file:
1. Find all `__attribute__((naked))` functions
2. **DELETE the entire function** — do not try to decomp it, do not replace it with a stub
3. If the file becomes empty after deletion, delete the file itself
4. If the file has non-naked functions that are valuable, keep those

## Important
- Do NOT touch jemalloc files (`src/app/jemalloc_*.cpp`, `src/resource/jemalloc_*.cpp`)
- Do NOT try to re-decomp these functions — that's future work, not this task
- The goal is honest accounting: remove fake progress from the metrics
- Build must still pass after deletions

## Self-Check
```bash
python tools/build.py 2>&1 | tee build_output.txt
grep -r '__attribute__.*naked' src/app/AreaContactLog.cpp src/app/AttackData.cpp  # should find nothing
```

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
