# Worker: pool-e

## Model: Opus

## Task: Item/weapon + Lua medium functions — continue

## Progress from last session
- 82 functions (3.7 KB): ItemKinetic.cpp, ItemHelpers.cpp, weapon_params.cpp fixes
- Remaining small: 8 energy-from-param forwarders (56B each), common_param_hash

## Continue with larger targets
### Lua/ACMD
1. lua_ai_path_builder (4,388B @ 0x71017e88d0)
2. lua_copy (2,212B @ 0x71038f29d0)
3. pop_lua_stack (1,324B @ 0x710372e420)
- Lua functions in 0x71038f-0x71039x may be -O0 → try __attribute__((optnone))

### Item
1. ItemManager constructor (6,428B @ 0x71015d2260)
2. lot_create_item (5,716B @ 0x71015bcde0)
3. item_generate_position_in_rect (2,140B @ 0x71015ce870)

## File Territory
- src/app/lua_acmd.cpp (continue)
- src/app/weapon_params.cpp (continue)
- src/app/Item.cpp
- src/app/ItemManager.cpp
- src/app/ItemKinetic.cpp (continue)
- src/app/ItemHelpers.cpp (continue)
- include/lib/L2CValue.h (continue)

## Quality Rules
- Use optnone for -O0 Lua functions
- No naked asm
- 3-attempt limit
