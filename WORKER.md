# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress
- 37 functions total (camera + stage + boss wrappers)
- StageWufuIsland constructor (1,832B), ~CameraQuake (3,088B)
- 16 camera leaf functions this round

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
