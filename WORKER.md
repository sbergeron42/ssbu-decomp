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

## Quality Rules
- No naked asm
- Large functions: document control flow structure even if match fails
- 3-attempt limit, N-quality is fine for these
