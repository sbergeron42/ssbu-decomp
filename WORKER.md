# Worker: pool-e

## Model: Opus

## Task: Item/weapon + Lua medium functions — continue

## Progress from current session
- 25+ new functions across ItemKinetic, ItemHelpers, lua_acmd
- ItemKinetic: 7 scalar functions (mul_accel 72B, set_accel/stable_speed/limit_speed 64B x3, sleep_speed 64B x2)
- ItemHelpers: common_param_hash (60B), 10 energy forwarders (52-60B), is_normal_gravity (40B), remove_ground_collision (48B), regist_life_status_ignore_lost (44B), have_no_set_team (52B), common_param_int boss (60B)
- lua_acmd: L2CAgent ctor (32B), as_integer (56B), as_number (56B), as_string (52B), sort (32B)
- Fixed ldrsw codegen for all common_param functions
- NEON vector functions (76-100B) skipped: NX Clang vectorization divergence

## Blocked targets (too complex or NX-specific)
- NEON ItemKinetic set_speed/add_speed (76-100B): NX Clang generates NEON for adjacent float writes
- pop_lua_stack (1,324B): 6 inlined index resolutions, very hard to match
- ItemManager ctor (6,428B): OOM retry chains, atomics, cxa_guard, 432-item init loop
- item_generate_position_in_rect (2,140B): heavy NEON geometry

## Next targets (if continuing)
- More small L2C functions in 0x71037xxx range (operator[], math_toint, etc.)
- Medium Item functions 100-300B that follow accessor chain patterns

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
