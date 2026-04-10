# Worker: pool-c

## Model: Opus

## Task: Clean up sv_animcmd_effect.cpp + camera_functions.cpp — typed module access

## Priority: QUALITY CLEANUP

## Context
`sv_animcmd_effect.cpp` (195 casts, 288 offsets, 4,748 lines) had partial EffectModule cleanup in Phase 1 but still has 195 casts. `camera_functions.cpp` (73 casts, 514 offsets, 3,079 lines) has stage/camera offset access that needs CameraController and other placeholder structs.

## File Territory
- `src/app/sv_animcmd_effect.cpp` (CLEANUP)
- `src/app/camera_functions.cpp` (CLEANUP)
- `include/app/modules/EffectModule.h` (extend if needed)
- `include/app/placeholders/` (create placeholders)

## What To Do
- sv_animcmd_effect: remaining EffectModule raw dispatch → typed wrappers, L2CValue access → typed
- camera_functions: raw stage/camera offsets → CameraController/StageBase struct access
- Cast density under 10%, zero REJECT violations

## Do NOT
- Delete, add, or rename functions — internal cleanup only

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
