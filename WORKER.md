# Worker: pool-e

## Model: Opus

## Task: L2CValue/L2CAgent — continue decomp

## Progress
- Round 1: 10 L2CValue constructors, SetLuaStateAccessor, clear_lua_stack, etc.
- Round 2: 8 L2CValue operators/math (bitwise, division, atan, log) — 7 matching
- Round 3: 12 new functions (alloc helpers, copy ctor, tree ops, table cleanup)
  - 6 relocation/prologue-only match: alloc_aligned16, alloc_with_retry, FUN_71037339b0, FUN_7103728a40, FUN_7103729440, FUN_71037293d0
  - 6 structural diff (correct decomp): copy ctor, table cleanup, length, operator[], setmetatable, ShowError wrapper

## Continue with
- Fix non-matching functions (copy ctor 0x7103733fe0, table cleanup 0x7103733900, length 0x7103735ea0)
- operator! (0x7103734fa0) — switch/jump table, may need different approach
- push_lua_stack (0x710372e320, 252B) — switch on type, pushes to Lua stack
- L2CTable ctor (0x71037337f0, 268B) — vector alloc + loop init
- operator% (0x7103735920, 292B) — integer sdiv/msub + float fmodf
- math_fmod (0x7103733180, 288B) — integer + float paths
- ipairs (0x7103732a50, 296B)

## Skipped
- math_min/max — binary discrepancy (removed in commit 65240a8)
- operator+/- binary, operator* — table metamethod dispatch tail call
- operator- unary — metatable OOM retry
- math_deg/rad — constructs L2CValues, calls operator*
- L2CValue(char*) — OOM retry + SSO alloc

## File Territory
- src/app/lua_acmd.cpp

## Quality Rules
- No naked asm, 3-attempt limit

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o`
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
