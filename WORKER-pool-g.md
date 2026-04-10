# Worker: pool-g

## Model: Opus

## Task: Camera and stage systems (StageManager, CameraManager, stage transitions)

## Priority: NEW DECOMP

## Context
Stage and camera systems are a high-traffic area. Pool-b created `StageBase` placeholder struct in Phase 3 with 8 stage subclass headers. Pool-c created `CameraController`. Existing work in `src/app/camera_functions.cpp` and `src/app/StageManager.cpp`. DO NOT touch `camera_functions.cpp` — pool-c owns it.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find stage/camera functions
2. Focus on StageManager methods, stage lifecycle (load/unload/transition)
3. Extend StageBase and stage subclass placeholders as you discover new fields

## File Territory
- `src/app/StageManager.cpp` (extend)
- `src/app/Stage*.cpp` (all stage implementation files EXCEPT stages pool-b already touched)
- `include/app/placeholders/StageBase.h` (extend)
- `include/app/placeholders/Stage*.h` (extend subclass headers)
- `include/app/placeholders/` (new types as needed)

## DO NOT touch
- `src/app/camera_functions.cpp` (pool-c)
- `src/app/sv_animcmd_effect.cpp` (pool-c)

## Quality Rules
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Run `python tools/review_diff.py pool-g` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
