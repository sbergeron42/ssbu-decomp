# Worker: pool-d

## Model: Opus

## Task: Game core + params — continue

## Progress from last session
- 6 functions compiled (16.4 KB): apply_lift_param, sub_rage_system, get_magic_ball_param, UpdateParams, global_param_init_sets_team_flag, nnMain
- Found Ghidra mislabeled sizes: apply_lift_param (92B not 11KB), sub_rage_system (180B not 13KB)
- game_tick is actually resource handle cleanup, not game simulation tick

## Best remaining target
- populate_parameters_for_hash40 (13,536B @ 0x71032ed9c0) — fully decompiled, no jump tables, ~15 repeated PRC binary search blocks. PRIORITIZE THIS.

## Deferred
- read_file (17,488B) — 20 versioned deserialization sections, hard
- game_tick (15,376B) — impossible, 94-case switches
- round_manager_update (29,496B) — jump table, 135K chars decompilation

## File Territory
- src/app/param_loading.cpp (continue)
- src/app/game_core.cpp (continue)
- src/app/global_param_init.cpp (continue)

## Quality Rules
- No naked asm
- Large functions: document control flow even if match fails
- 3-attempt limit, N-quality is fine
