# Worker: pool-b

## Model: Opus

## Task: Fighter logic — attack processing and damage calculations

## Priority: NEW DECOMP (community high-value)

## Context
Attack and damage processing — hitbox creation, knockback calculation, shield interactions. The .dynsym has `AttackModule__*_impl` and `DamageModule__*_impl` names. `include/app/modules/AttackModule.h` has 176 typed wrappers. `include/app/AttackData.h` and `include/app/DamageInfo.h` have partial struct definitions.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find `attack` and `damage` functions
2. Start with the AttackModule and DamageModule dispatcher functions
3. Extend `AttackData.h` and `DamageInfo.h` as you discover new fields
4. Use typed module access throughout

## File Territory
- `src/app/fighter_attack.cpp` (extend)
- `src/app/fighter_damage.cpp` (create if needed)
- `include/app/AttackData.h` (extend)
- `include/app/DamageInfo.h` (extend)
- `include/app/modules/AttackModule.h` (extend with new slot wrappers)
- `include/app/modules/DamageModule.h` (create — currently just a forward decl)
- `include/app/placeholders/` (new types as needed)

## Quality Rules
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Create placeholder structs, log in `data/undefined_types.md`
- Run `python tools/review_diff.py pool-b` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
