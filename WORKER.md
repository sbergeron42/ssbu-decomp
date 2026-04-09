# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress from last session
- 21 camera functions + StageWufuIsland constructor (5.9 KB total)
- Large constructors/destructors have NX codegen divergence (constant-store ordering)
- verify_local.py only processes lua_bind names — extern "C" not auto-verified

## Continue with
- Camera param functions: set_camera_param (2,344B), set_pause_camera_param (3,996B), CHECK_VALID_START_CAMERA (2,812B)
- Stage destructors: ~StageWufuIsland (2,700B), ~~StageBase (2,572B)
- More stage leaf functions in StageManager.cpp

## Skipped (don't retry)
- create_stage (114,600B) — too large
- StageBase constructor (14,820B) — too large for this round

## File Territory
- src/app/camera_functions.cpp (continue)
- src/app/StageManager.cpp (continue)
- src/app/StageWufuIsland.cpp (continue)

## Quality Rules
- No naked asm
- 3-attempt limit
