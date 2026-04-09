# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress
- 57 functions total (camera + stage + boss + ground)
- StageWufuIsland constructor (1,832B), ~CameraQuake (3,088B)
- 16 camera leaf functions (prior round)
- 20 new leaf functions this round:
  - 6 matching: lr_to_stage_center, is_looking_at_stage_center, get_rotation_with_calc_camera_direction, get_area_down, get_rhombus_down_y, is_enable_capture_baitocrane
  - 14 compiled with NX Clang prologue/optimization diffs

## Continue with
- ~StageWufuIsland destructor (2,700B) — complex, deferred
- set_camera_param (2,344B), set_pause_camera_param (3,996B) — param binary search pattern
- More leaf functions from camera/stage/boss territory

## Skipped
- create_stage (114,600B), StageBase ctor (14,820B) — too large

## File Territory
- src/app/camera_functions.cpp, StageManager.cpp, StageWufuIsland.cpp

## Quality Rules
- No naked asm, 3-attempt limit
