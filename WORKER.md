# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 68 functions, 120 KB

## Strategy
The EFFECT_* functions (FOOT_EFFECT, DOWN_EFFECT, EFFECT_FOLLOW_*, EFFECT_BRANCH_*, etc.) appear to share template patterns. If one matches, the pattern likely applies to many. This is the highest KB-per-effort ratio available.

## Targets (by size, descending)
1. FOOT_EFFECT (4,148 bytes @ 0x7102297600)
2. DOWN_EFFECT (3,996 bytes @ 0x7102298fa0)
3. EFFECT_FOLLOW_LIGHT (3,976 bytes @ 0x7102296410)
4. EFFECT_FOLLOW_FLIP_RND (3,968 bytes @ 0x710229ff20)
5. EFFECT_VARIATION (3,736 bytes @ 0x710228cc90)
6. EFFECT_ATTR (3,716 bytes @ 0x710228db30)
7. EFFECT_FOLLOW_RND (3,672 bytes @ 0x710229e280)
8. EFFECT_BRANCH_SITUATION (3,664 bytes @ 0x71022a1a20)
... and 60 more in the 0x71022xxxxx range

## Approach
- Start with ONE function (e.g., EFFECT_VARIATION). Use Ghidra to decompile.
- Identify the shared pattern/template across the group.
- Once the template matches, apply it to all 68 functions.
- These are ACMD effect dispatchers — cross-reference with existing fighter_effects.cpp.
- Use EffectModule vtable methods from include/app/modules/EffectModule.h if available.

## File Territory
- src/app/fighter_effects.cpp (extend existing)
- src/app/effect_dispatchers.cpp (new, if too many for one file)
- include/app/modules/ (struct updates)

## Quality Rules
- Document the template pattern once, reference it for variants
- No naked asm
- 3-attempt limit per function
