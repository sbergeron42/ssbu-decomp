# Worker: pool-c

## Model: Opus

## Task: Stage + camera + effects decomp — community priority #2

## Strategy
Stage modding is a growing community area. Stage loading, gimmick events, camera control, and visual effects are all interconnected. Types-first: recover StageManager, GimmickEvent, CameraModule structs, then decomp functions.

## Targets
1. **Stage functions** — 92 undecompiled (178 KB). create_stage (115 KB!) is the biggest single function — skip it, focus on smaller stage helpers first.
2. **Effect functions** — 122 undecompiled (134 KB). EffectModule vtable methods, particle spawning.
3. **Camera functions** — 92 undecompiled (41 KB). CameraModule vtable methods.
4. **GimmickEvent** — Multiple GimmickEvent*.cpp files exist. Continue filling in missing functions.

## Approach
- Use Ghidra to decompile, cross-reference with existing headers
- StageManager struct needs investigation — check include/app/ for existing layout
- Camera/Effect modules have vtable headers in include/app/modules/
- Focus on functions modders call: effect spawning, camera shake, stage queries

## File Territory
- src/app/StageManager.cpp
- src/app/Gimmick*.cpp
- src/app/fighter_effects.cpp
- src/app/graphics_functions.cpp
- src/app/particle_functions.cpp
- include/app/ (struct updates)

## Quality Rules
- Use module vtable method wrappers from headers
- No naked asm
- Document derivation chains
