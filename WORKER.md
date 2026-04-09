# Worker: pool-e

## Model: Opus

## Task: Item/weapon + Lua — continue

## Progress
- ~55 functions total: ItemKinetic (7), ItemHelpers (16), lua_acmd (7+25)
- L2CValue accessors, ldrsw codegen fix, energy forwarders
- L2CValue math functions: toint, abs, floor, ceil, sin, cos, tan, acos, sqrt (9 funcs, all matching)
- L2CValue operator~, operator[](Hash40) (2 funcs)
- L2CAgent: ~L2CAgent D1+D0, sort, lock, unlock, find_metatable (5 funcs)
- Added L2CValue copy ctor declaration to force x8 struct return ABI
- 14/17 earlier functions byte-match (relocation-only diffs)
- NEW: L2CValue constructors: int, uint, L2CTable*, L2CInnerFunctionBase*, Hash40 (5 funcs, all PERFECT MATCH)
- NEW: ~L2CValue destructor (codegen diff: tail merge saves 1 insn, 40/41)
- NEW: operator< and operator<= (codegen diff: block layout differs, 43/43 instructions each)

## Continue with
- as_bool / operator_cast_to_bool need ldrsw jump table (NX Clang uses 32-bit offsets, upstream uses byte)
- sort_71037301b0 has extra mov x0,x8 in target (52B vs our 48B)
- copy ctor 0x7103733fe0 (OOM retry pattern, complex)
- operator== and other comparison operators
- Medium Item functions if time permits

## Blocked (don't retry)
- NEON ItemKinetic functions, pop_lua_stack, ItemManager ctor, item_generate_position_in_rect
- as_bool / operator_cast_to_bool (jump table format: upstream ldrb vs NX ldrsw)

## File Territory
- src/app/lua_acmd.cpp, weapon_params.cpp, ItemKinetic.cpp, ItemHelpers.cpp
- include/lib/L2CValue.h

## Quality Rules
- optnone for -O0 Lua functions, no naked asm, 3-attempt limit
- Use asm volatile("") barriers for post-call store scheduling
- L2CValue struct return via x8: requires non-trivial copy ctor declaration
- Use FUN_7103733fe0 for explicit copy ctor calls (floor/ceil integer path)
