# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress from last session
- 21 camera functions + StageWufuIsland constructor (5.9 KB total)
- Large constructors/destructors have NX codegen divergence (constant-store ordering)
- verify_local.py only processes lua_bind names — extern "C" not auto-verified

## This session's progress
- 16 new functions added to camera_functions.cpp (~1.1 KB total)
  - 4 pickelobject camera_range_damag_mul getters (32B each) — likely match
  - get_camera_range_center_pos (72B) — likely match
  - get_camera_subject_range (100B) — matches expected disasm
  - camera_sleep (104B) — matches (orr→movz via fix_orr_movz.py)
  - app::camera::get_camera_range (114B) — near-match (register allocation diff)
  - set_dead_up_camera_hit_vis_change (80B) — matches
  - get_dead_up_camera_hit_prob (84B) — matches
  - entry_to_stage (88B) — near-match (instruction reordering)
  - 5 boss energy wrappers (56-60B each) — near-match (minor instruction ordering)

## Continue with
- ~StageWufuIsland destructor (2,700B) — complex, 5 event listener unregistrations + many field frees
- ~~StageBase destructor (2,572B) — complex, red-black tree traversal, effect cleanup
- set_camera_param (2,344B) — complex param lookup with binary search
- set_pause_camera_param (3,996B) — even more complex
- CHECK_VALID_START_CAMERA (2,812B) — complex param lookup

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
