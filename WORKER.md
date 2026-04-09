# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 24 remaining, ~46 KB

## Progress (44/68 complete, 65%)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF
- Patterns: kill_all/kill_kind, req_on_joint, req_follow, FLW_POS, FLIP+hash swap, COLOR/ALPHA post-process
- FUN_7102288620 shared parser decomped: EFFECT_COLOR, COLOR_WORK, ALPHA, FLIP, FLIP_ALPHA
- CSE divergence: upstream Clang CSEs DAT_7104861960 loads, ~85-95% size

## Continue with (24 remaining)
- EFFECT, EFFECT_WORK_R, EFFECT_BRANCH_SITUATION (~10.5 KB, use FUN_7102288620)
- EFFECT_FOLLOW_RND, FOLLOW_RND_WORK, FOLLOW_FLIP_RND (inline XOR-shift RNG, ~11.3 KB)
- FOOT_EFFECT, FOOT_EFFECT_FLIP, LANDING_EFFECT, LANDING_EFFECT_FLIP, DOWN_EFFECT (~10.5 KB, need StageManager singleton)
- EFFECT_GLOBAL variants (need FUN_710228ea70 + EffectManager singleton, ~4 KB)
- EFFECT_FOLLOW_LIGHT (NEON + PostureModule, ~4 KB)

## File Territory
- src/app/sv_animcmd_effect.cpp

## Quality Rules
- No naked asm, 3-attempt limit
