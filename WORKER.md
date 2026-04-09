# Worker: pool-e

## Model: Opus

## Task: Item/weapon + Lua medium functions — targeting 130+ KB

## Targets (by size, descending)
### Lua/ACMD (92 KB)
1. lua_ai_path_builder (4,388 bytes @ 0x71017e88d0)
2. lua_copy (2,212 bytes @ 0x71038f29d0)
3. luaopen_string (1,892 bytes @ 0x7103917450)
4. luaL_loadfilex (1,760 bytes @ 0x71038f7ae0)
5. ~~LuaModule (1,640 bytes @ 0x710372d390)
6. pop_lua_stack (1,324 bytes @ 0x710372e420)
7. luaL_setfuncs (1,304 bytes @ 0x71038f8f60)

NOTE: Skip lua_ai_init (62,524 bytes) — too large for this round.

### Item (42 KB)
1. ItemManager (6,428 bytes @ 0x71015d2260)
2. lot_create_item (5,716 bytes @ 0x71015bcde0)
3. final_rand_create_item (5,024 bytes @ 0x7100e8aef0)
4. ResetHaveItemConstraintNode (2,728 bytes @ 0x7100473480)
5. item_generate_position_in_rect (2,140 bytes @ 0x71015ce870)

Continue weapon_params.cpp for smaller accessors between the big targets.

## Approach
- Lua functions in 0x71038f-0x71039x may be -O0 → try __attribute__((optnone))
- Continue building on L2CValue.h from prior round
- ItemManager constructor reveals struct layout — prioritize it
- lot_create_item is the item spawn function — high modder value

## File Territory
- src/app/lua_acmd.cpp (continue)
- src/app/weapon_params.cpp (continue)
- src/app/Item.cpp
- src/app/ItemManager.cpp
- include/lib/L2CValue.h (continue)
- include/app/ (struct updates)

## Quality Rules
- Use optnone for -O0 Lua functions
- No naked asm
- 3-attempt limit per function
