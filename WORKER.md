# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 15 remaining, ~31 KB

## Progress (53/68 complete, 78%)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF
- Patterns: kill_all/kill_kind, req_on_joint, req_follow, FLW_POS, FLIP+hash swap, COLOR/ALPHA post-process
- FUN_7102288620 shared parser decomped: EFFECT_COLOR, COLOR_WORK, ALPHA, FLIP, FLIP_ALPHA
- CSE divergence: upstream Clang CSEs DAT_7104861960 loads, ~85-95% size
- NEW: EFFECT (86%), EFFECT_WORK_R (84%), EFFECT_BRANCH_SITUATION (86%) — 16-arg inline readers with vec packing
- NEW: EFFECT_FOLLOW_RND (91%), FOLLOW_RND_WORK (93%), FOLLOW_FLIP_RND (87%) — XOR-shift128 PRNG + randomization
- NEW: LANDING_EFFECT (102%), LANDING_EFFECT_FLIP (100.5%), FOOT_EFFECT_FLIP (97%) — terrain-aware with StageManager

## Continue with (15 remaining)
- FOOT_EFFECT (~4.1 KB, inline 16-arg + terrain logic, needs StageManager)
- DOWN_EFFECT (~4.0 KB, inline 16-arg + terrain at offset 0x78)
- EFFECT_GLOBAL_BACK_GROUND, EFFECT_GLOBAL_BACK_GROUND_CENTER_TOP_NODE, EFFECT_GLOBAL_BACK_GROUND_CUT_IN_CENTER_POS (~4 KB, need FUN_710228ea70)
- EFFECT_FOLLOW_LIGHT (NEON + PostureModule, ~4 KB)
- Remaining smaller functions from original 24 list

## File Territory
- src/app/sv_animcmd_effect.cpp

## Quality Rules
- No naked asm, 3-attempt limit
