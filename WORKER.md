# Worker: pool-e

## Model: Opus

## Task: L2CValue / L2CAgent methods — continue

## Progress (all sessions combined)
- ~65 functions in lua_acmd.cpp covering L2CValue constructors, operators, math wrappers, trig functions, table operations, tree traversal, alloc helpers
- Small leaf functions (8-124 bytes): most byte-match or are relocation-only mismatches
- Medium functions (164-368 bytes): typically non-matching due to instruction scheduling (NX Clang prologue divergence)
- Key patterns established: type tag extraction (7/3/2 check order), SSO string layout, OOM retry, refcount management, RB tree search

## Latest round (session 3)
- operator= (0x7103734330, 356B): copy assignment — destroy old + copy from source. 13% match (scheduling diffs).
- L2CValue(char*) (0x71037341c0, 368B): string constructor with SSO alloc + OOM retry. 8% match.

## Remaining targets in L2C range
- operator== (0x7103734520, 680B) — very complex, many code paths, stretch goal
- operator! (0x7103734fa0, 132B) — jump table, ~8% match expected (same as as_bool)
- operator= copy (0x7103734330, done as non-matching)
- math_min/max (0x71037336b0/750, 160B each) — removed in commit 65240a8 due to binary discrepancy
- FUN_7103733d50 (328B) — RB tree hash insert (needs __tree_balance_after_insert extern)
- FUN_71037339f0 (860B) — table index vector growth + RB tree fallback (too large)
- math_deg/rad (356B each) — construct L2CValues + call operator*, complex
- L2CTable ctor (268B) — vector alloc + loop init + OOM retry

## BLOCKED / SKIP
- Jump table functions: operator!, operator bool, as_bool — ldrsw encoding differs
- Shared_ptr atomics: various camera/stage functions
- Large functions (>500B): CallFunctionByHash, push_lua_stack, pop_lua_stack, ipairs, to_string
- Library code: __tree_balance_after_insert (can't match libc++ separately)

## File Territory
- src/app/lua_acmd.cpp

## Quality Rules
- No naked asm, 3-attempt limit
- Non-matching functions still committed (structural decomp, not cosmetic renames)

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/lua_acmd.cpp -o build/lua_acmd.o`
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
