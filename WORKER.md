# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 16 remaining, ~40 KB

## Progress (44/68 complete)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF
- 3 dispatch patterns: kill_all/kill_kind, req_on_joint, req_follow
- New patterns: LAST_EFFECT_SET_* family, EFFECT_DETACH_KIND
- FLW_POS family (4 functions): float-position req_follow variant, 14-param call
- FOLLOW_COLOR/ALPHA: req_follow → handle → set_color/set_alpha vtable call
- LAST_PARTICLE_SET_COLOR, LAST_EFFECT_SET_OFFSET_TO_CAMERA_FLAT
- CSE divergence: upstream Clang CSEs DAT_7104861960 loads, ~85-95% size

## Continue with
- EFFECT_FOLLOW_FLIP, EFFECT_FOLLOW_FLIP_arg13, EFFECT_FOLLOW_NO_STOP_FLIP (motion flip check + hash swap)
- EFFECT_FOLLOW_FLIP_COLOR, EFFECT_FOLLOW_FLIP_ALPHA (flip + color/alpha)
- EFFECT_FOLLOW_RND, EFFECT_FOLLOW_RND_WORK, EFFECT_FOLLOW_FLIP_RND (inline XOR-shift RNG)
- EFFECT_FOLLOW_LIGHT (3976B, complex)
- FUN_7102288620 used as extern: EFFECT_COLOR/WORK, EFFECT_ALPHA, EFFECT_FLIP, EFFECT_FLIP_ALPHA done
- Remaining FUN_7102288620 users: EFFECT (3624B), EFFECT_WORK_R (3216B), EFFECT_BRANCH_SITUATION (3664B)
- EFFECT_GLOBAL family (needs FUN_710228ea70 + EffectManager singleton)
- FOOT_EFFECT, LANDING_EFFECT, DOWN_EFFECT (complex unique patterns)

## File Territory
- src/app/sv_animcmd_effect.cpp (continue)

## Quality Rules
- No naked asm, 3-attempt limit
