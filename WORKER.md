# Worker: pool-e

## Model: Opus

## Task: Item/weapon + Lua — continue

## Progress
- ~30 functions: ItemKinetic (7), ItemHelpers (16), lua_acmd (7)
- L2CValue accessors, ldrsw codegen fix, energy forwarders

## Continue with
- More L2C functions in 0x71037xxx range (math_toint, etc.)
- Medium Item functions 100-300B (accessor chain patterns)
- lua_ai_path_builder (4,388B) if time permits
- Try optnone for -O0 Lua functions

## Blocked (don't retry)
- NEON ItemKinetic functions, pop_lua_stack, ItemManager ctor, item_generate_position_in_rect

## File Territory
- src/app/lua_acmd.cpp, weapon_params.cpp, ItemKinetic.cpp, ItemHelpers.cpp
- include/lib/L2CValue.h

## Quality Rules
- optnone for -O0 Lua functions, no naked asm, 3-attempt limit
