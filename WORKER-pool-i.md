# Worker: pool-i

## Model: Opus

## Task: Effect and visibility modules (VFX, particle systems, color blend)

## Priority: NEW DECOMP

## Context
Effect and visibility modules handle particle effects, color blending, visibility toggling, and visual feedback. Phase 1 and Phase 2 established typed EffectModule wrappers. `include/app/modules/EffectModule.h` has 89 methods. DO NOT touch `sv_animcmd_effect.cpp` — pool-c owns it.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find effect/visibility functions
2. Focus on EffectModule internal helpers, ColorBlendModule, VisibilityModule
3. Extend module headers with new vtable slot wrappers

## File Territory
- `src/app/modules/EffectModule.cpp` (extend)
- `src/app/modules/ColorBlendModule.cpp` (extend)
- `src/app/modules/VisibilityModule.cpp` (extend)
- `src/app/modules/ModelModule.cpp` (extend)
- `src/app/modules/InkPaintModule.cpp` (extend — deleted in Phase 4, recreate properly)
- `src/app/fighter_effects.cpp` (extend)
- `include/app/modules/EffectModule.h` (extend)
- `include/app/modules/ColorBlendModule.h` (extend)
- `include/app/modules/VisibilityModule.h` (extend)

## DO NOT touch
- `src/app/sv_animcmd_effect.cpp` (pool-c)

## Quality Rules
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Run `python tools/review_diff.py pool-i` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
