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
- NEW: Bitwise binary operators: &, |, ^, <<, >> (5 funcs, all PERFECT MATCH 100%)
- NEW: math_atan (relocation-only diff, 34/35)
- NEW: operator/ division (relocation-only diff, 41/42)
- NEW: math_log (prologue scheduling diff, 37/46 — body matches)
- NEW: FUN_71037347d0 metamethod dispatch declared as extern

## Continue with
- operator== (0x7103734520, 680 bytes) — complex equality, multiple type paths
- copy ctor 0x7103733fe0 (OOM retry pattern, complex)
- operator= assignment (0x7103734330, 356 bytes)
- math_min/max (160 bytes each) — copy ctor tail call
- length (136 bytes) — SSO string + table
- Medium Item functions if time permits

## Blocked (don't retry)
- NEON ItemKinetic functions, pop_lua_stack, ItemManager ctor, item_generate_position_in_rect
- as_bool / operator_cast_to_bool (jump table format: upstream ldrb vs NX ldrsw)
- operator- binary, operator* (12% match — metamethod tail call codegen doesn't match)

## File Territory
- src/app/lua_acmd.cpp, weapon_params.cpp, ItemKinetic.cpp, ItemHelpers.cpp
- include/lib/L2CValue.h

## Quality Rules
- optnone for -O0 Lua functions, no naked asm, 3-attempt limit
- Use asm volatile("") barriers for post-call store scheduling
- L2CValue struct return via x8: requires non-trivial copy ctor declaration
- Use FUN_7103733fe0 for explicit copy ctor calls (floor/ceil integer path)

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
- Use `run_in_background` for any build that takes >10 seconds
- **WARNING:** Do NOT use `build.bat` — it runs deprecated post-processors that inflate match counts

## Ghidra Cache
- Save ALL Ghidra decompilation results to `data/ghidra_cache/pool-e.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work
- Append new results after each `mcp__ghidra__decompile_function_by_address` call

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `pool-e: decomp MODULE functions (N new, M matching)`
- If session crashes, uncommitted work will be auto-recovered by the launcher script

## Rewrite Quality Standard
BAD (rename only — NOT acceptable):
```cpp
void FUN_710228d930(void* param_1) {
    void* result = *(void**)((u8*)param_1 + 0x40);
    (*(void(**)(void*))(*(u8**)result + 0x38))(result);
}
```

GOOD (struct access + derivation chain):
```cpp
void StatusModule_change_status(BattleObjectModuleAccessor* acc) {
    StatusModule* mod = acc->status_module;  // +0x40 [derived: .dynsym StatusModule vtable]
    mod->change_status();  // vtable[7] [derived: StatusModule.h]
}
```
