# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 33 remaining, ~75 KB

## Progress (25/68 complete)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF
- 3 dispatch patterns: kill_all/kill_kind, req_on_joint, req_follow
- New patterns: LAST_EFFECT_SET_* family, EFFECT_DETACH_KIND
- CSE divergence: upstream Clang CSEs DAT_7104861960 loads, ~85-95% size

## Continue with
- EFFECT_FLIP, EFFECT_FOLLOW_FLIP, FOOT_EFFECT_FLIP, LANDING_EFFECT_FLIP (need shared arg parser FUN_7102288620)
- EFFECT_FLW_POS, EFFECT_FLW_POS_NO_STOP, EFFECT_FLW_POS_UNSYNC_VIS
- EFFECT_FOLLOW_COLOR, EFFECT_FOLLOW_ALPHA, EFFECT_FOLLOW_RND family
- EFFECT_BRANCH_SITUATION, EFFECT_COLOR, EFFECT_ALPHA
- EFFECT_WORK_R, EFFECT_GLOBAL family

## File Territory
- src/app/sv_animcmd_effect.cpp (continue)

## Quality Rules
- No naked asm, 3-attempt limit
