# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress (57 functions total)
- 20 new leaf functions last round (3 perfect matches: get_area_down, get_rhombus_down_y, is_enable_capture_baitocrane)
- gt vs hi condition: use > directly instead of <= to prevent LLVM negation
- NX Clang prologue scheduling (add x29) is most common remaining diff

## Continue with
- ~StageWufuIsland destructor (2,700B)
- ~~StageBase destructor (2,572B)
- set_camera_param (2,344B), set_pause_camera_param (3,996B)
- CHECK_VALID_START_CAMERA (2,812B)
- More stage/camera leaf functions

## Skipped
- create_stage (114,600B), StageBase ctor (14,820B) — too large

## File Territory
- src/app/camera_functions.cpp, StageManager.cpp, StageWufuIsland.cpp

## Quality Rules
- No naked asm, 3-attempt limit
