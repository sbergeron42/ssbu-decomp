# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress (61 functions total)
- 20 leaf functions from round 2 (3 perfect matches)
- 4 new functions this round:
  - is_camera_off_final2 (188B) — size match, prologue scheduling only diff
  - get_final_camera_pos (196B) — size match, register alloc diff
  - update_dead_up_camera_hit_first_distance_group (124B) — size match, tbz fixed
  - camera (sv_module_access) (180B target, 184B compiled) — 1 instr diff (mov+add vs add sp)
- Key patterns: do-while for cbz elimination, __builtin_expect for branch polarity, #pragma clang loop unroll(disable)

## Continue with
- set_camera_param (2,344B), set_pause_camera_param (3,996B) — param tree lookups
- ~StageWufuIsland destructor (2,700B) — event listener cleanup
- More camera leaf functions (set_camera_range variants, revert_camera)
- Stage destructors (~StageFlatZoneX, ~StageNintendogs, ~StageStreetPass)

## Skipped
- create_stage (114,600B), StageBase ctor (14,820B) — too large
- IT_MOVE_CAMERA, is_clip_in_camera, is_dark_stage — shared_ptr refcount patterns

## File Territory
- src/app/camera_functions.cpp, StageManager.cpp, StageWufuIsland.cpp

## Quality Rules
- No naked asm, 3-attempt limit
