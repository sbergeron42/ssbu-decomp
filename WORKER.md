# Worker: pool-d

## Model: Opus

## Task: Game core + params medium functions — targeting 130+ KB

## Targets (by size, descending)
### Game core
1. round_manager_update (29,496 bytes @ 0x7101c35b80)
2. read_file (17,488 bytes @ 0x7103180ad0)
3. game_tick (15,376 bytes @ 0x71002c5cf0)
4. sub_rage_system (13,524 bytes @ 0x7100937030)
5. nnMain (1,744 bytes @ 0x71002c5620)

### Params (54 KB)
1. populate_parameters_for_hash40 (13,536 bytes @ 0x71032ed9c0)
2. apply_lift_param (11,044 bytes @ 0x7100995040)
3. global_param_init_sets_team_flag (6,796 bytes @ 0x71017641a0)
4. UpdateParams (4,564 bytes @ 0x710008b480)
5. get_magic_ball_param (3,184 bytes @ 0x710165fcb0)

## Approach
- game_tick and round_manager_update are the game's main loop — high community value
- These are VERY large functions. Focus on structural understanding first.
- read_file likely relates to resource service (check existing res_*.cpp files)
- Param functions may use hash40 lookup patterns — check community hash tables
- nnMain is the entry point — small but structurally important

## File Territory
- src/app/game_core.cpp (new)
- src/app/param_loading.cpp (new)
- src/app/lua_acmd.cpp (continue from prior round)
- include/app/ (struct updates)

## Progress
### Completed (compiled, in src/app/param_loading.cpp + game_core.cpp + global_param_init.cpp)
1. apply_lift_param (92B actual, was mislabeled 11KB) — NEAR-MATCH, prologue + orr diffs only
2. sub_rage_system (180B actual, was mislabeled 13KB) — close match, minor clamping codegen diff
3. get_magic_ball_param (3,184B) — compiles, needs matching iteration
4. UpdateParams (4,564B) — compiles, missing NEON rotation matrix section (~35%)
5. global_param_init_sets_team_flag (6,796B) — compiles, massive BSS init
6. nnMain (1,744B) — documented stub, 94-case switches prevent matching

### Findings
- apply_lift_param and sub_rage_system were both mislabeled as 11KB/13KB functions.
  Ghidra misidentified their tail-call `br x3` instructions as jump tables.
  They are actually tiny functions (92B and 180B respectively).
- game_tick shares the same 94-case resource type switches as nnMain.
  Both use discriminant at application_object+0xC04 with base offset 0x728, stride 0x50.
- populate_parameters_for_hash40 is fully decompiled (no jump tables) but is 13.5KB.

### Remaining (deferred to next session)
- populate_parameters_for_hash40 (13,536B) — fully decompiled, large but tractable
- read_file (17,488B) — needs analysis
- game_tick (15,376B) — blocked by 94-case switches
- round_manager_update (29,496B) — has jump table warning

## Quality Rules
- No naked asm
- Large functions: document control flow structure even if match fails
- 3-attempt limit, N-quality is fine for these
