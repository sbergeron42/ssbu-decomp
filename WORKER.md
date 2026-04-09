# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 63 remaining, 120 KB

## Progress from last session
- 5/68 done: EFFECT_OFF, EFFECT_OFF_KIND, EFFECT_WORK, EFFECT_VARIATION, EFFECT_FOLLOW
- 3 dispatch patterns established: kill_all/kill_kind, req_on_joint, req_follow
- Known CSE divergence: upstream Clang CSEs DAT_7104861960 loads, making functions 5-11% smaller than NX
- Ghidra results for 6 targets saved in /tmp/ghidra_results.txt

## Continue with
- Apply the 3 established patterns to the remaining 63 EFFECT_* functions
- EFFECT_ATTR, EFFECT_FLIP, EFFECT_FOLLOW_WORK, EFFECT_FOLLOW_VARIATION, etc.
- All in the 0x71022xxxxx range

## File Territory
- src/app/sv_animcmd_effect.cpp (continue)
- src/app/fighter_effects.cpp

## Quality Rules
- No naked asm
- 3-attempt limit per function
