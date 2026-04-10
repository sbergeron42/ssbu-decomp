# Worker: pool-h

## Model: Opus

## Task: Physics and kinetic energy systems

## Priority: NEW DECOMP

## Context
Physics and kinetic energy drive fighter movement — gravity, friction, collision response, knockback trajectories. The .dynsym has `KineticModule__*_impl` and `PhysicsModule__*_impl` names. `include/app/modules/KineticModule.h` and `include/app/modules/PhysicsModule.h` have typed wrappers. `KineticEnergy` struct has partial fields.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find `KineticEnergy`, `Physics`, `gravity`, `friction` functions
2. Focus on KineticEnergy subclasses (Motion, Gravity, Normal, etc.)
3. Extend KineticModule.h wrappers and KineticEnergy struct as you discover new fields

## File Territory
- `src/app/FighterKineticEnergy*.cpp` (extend)
- `src/app/WeaponKineticEnergy*.cpp` (extend)
- `src/app/modules/KineticModule.cpp` (extend)
- `src/app/modules/PhysicsModule.cpp` (extend)
- `src/app/modules/ItemKineticModuleImpl.cpp` (extend)
- `include/app/modules/KineticModule.h` (extend)
- `include/app/modules/PhysicsModule.h` (extend)
- `include/app/placeholders/` (new types as needed)

## Quality Rules
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Run `python tools/review_diff.py pool-h` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
