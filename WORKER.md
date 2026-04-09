# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 33 remaining, ~75 KB

## Progress
- 25/68 done (5 existing + 20 new this session)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF (existing)
- Remaining 16 have known CSE divergence (upstream Clang CSEs DAT_7104861960 loads, ~85-95% of target size)
- 3 dispatch patterns confirmed: kill_all/kill_kind, req_on_joint, req_follow
- New patterns: LAST_EFFECT_SET_* family (rate/alpha/scale/color), EFFECT_DETACH_KIND

## Functions implemented this session
- EFFECT_REMOVE_ATTR (180/180 perfect), EFFECT_OFF_HANDLE (180/180 perfect)
- EFFECT_OFF_KIND_WORK, EFFECT_FOLLOW_WORK, EFFECT_FOLLOW_VARIATION, EFFECT_ATTR
- EFFECT_DETACH_KIND, EFFECT_DETACH_KIND_WORK, EFFECT_LIGHT_END
- LAST_EFFECT_SET_RATE, LAST_EFFECT_SET_RATE_WORK, LAST_EFFECT_SET_ALPHA
- LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW (280/284), LAST_EFFECT_SET_WORK_INT (212/212 perfect)
- LAST_EFFECT_SET_SCALE_W, LAST_EFFECT_SET_COLOR
- EFFECT_FOLLOW_NO_STOP, EFFECT_FOLLOW_arg11, EFFECT_FOLLOW_NO_SCALE
- EFFECT_FOLLOW_UNSYNC_VIS_WHOLE

## Continue with
- EFFECT_FLIP, EFFECT_FOLLOW_FLIP, FOOT_EFFECT_FLIP, LANDING_EFFECT_FLIP (need shared arg parser FUN_7102288620)
- EFFECT_FLW_POS, EFFECT_FLW_POS_NO_STOP, EFFECT_FLW_POS_UNSYNC_VIS, EFFECT_FLW_UNSYNC_VIS
- EFFECT_FOLLOW_COLOR, EFFECT_FOLLOW_ALPHA, EFFECT_FOLLOW_RND family
- EFFECT_FOLLOW_FLIP_*, EFFECT_BRANCH_SITUATION
- EFFECT_COLOR, EFFECT_COLOR_WORK, EFFECT_ALPHA (need shared arg parser)
- EFFECT_WORK_R, EFFECT_GLOBAL family
- LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT, LAST_EFFECT_SET_TOP_OFFSET
- EFFECT_FOLLOW_arg12 (uses jump table via PTR_FUN_7104f68c38)

## File Territory
- src/app/sv_animcmd_effect.cpp (continue)
- src/app/fighter_effects.cpp

## Quality Rules
- No naked asm
- 3-attempt limit per function
