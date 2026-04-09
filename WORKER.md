# Worker: pool-d

## Model: Opus

## Task: Game core + params — continue

## Progress
- populate_parameters_for_hash40 (13,536B) — compiled, N-quality (85% size match)
- 6 prior functions: apply_lift_param, sub_rage_system, get_magic_ball_param, UpdateParams, global_param_init_sets_team_flag, nnMain
- Ghidra size mislabeling found on 2 functions

## Continue with
- read_file (17,488B) — 20 versioned deserialization sections, hard but attempt it
- Look for more medium param functions
- Any game core functions reachable from nnMain

## Deferred
- game_tick (15,376B) — impossible, 94-case switches
- round_manager_update (29,496B) — jump table, too large

## File Territory
- src/app/param_loading.cpp, game_core.cpp, global_param_init.cpp

## Quality Rules
- No naked asm, 3-attempt limit, N-quality is fine for large functions
