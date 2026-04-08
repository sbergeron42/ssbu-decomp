# Worker: pool-e

## Model: Opus

## Task: Item/weapon + parameter loading — community priority #4

## Strategy
Weapon parameters and item behavior are heavily used by modders who create custom fighters and items. Parameter loading is how the game reads .prc files, which modders replace constantly. Both areas have strong community knowledge to leverage.

## Targets
1. **weapon_params.cpp** — Continue weapon param accessor decomp. Already have BUDDYBOMB, PICKELBOMB, MECHAKOOPA, HOLYWATER, PEACH, DOLL, EXPLOSIONBOMB, LINKARROW. Target remaining weapon types.
2. **Item functions** — 97 undecompiled (53 KB). Item spawning, behavior, collision.
3. **Parameter loading** — 87 undecompiled (65 KB). ParamAccessor, prc file reading, hash lookups.
4. **FighterParamAccessor2.cpp** — Existing file, extend with more param accessors.

## Approach
- Weapon params follow consistent patterns (see existing weapon_params.cpp)
- Use Ghidra to identify param accessor vtable patterns
- ItemModule vtable methods in include/app/modules/
- Parameter loading may use hash40 lookups — cross-reference with community hash tables

## File Territory
- src/app/weapon_params.cpp
- src/app/Item.cpp
- src/app/ItemManager.cpp
- src/app/FighterParamAccessor2.cpp
- include/app/ (struct updates)

## Quality Rules
- Weapon params are templated patterns — document the template
- No naked asm
- Use existing module headers for vtable dispatch
