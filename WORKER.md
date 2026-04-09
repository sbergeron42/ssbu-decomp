# Worker: pool-b

## Model: Opus

## Task: Fighter core — continue item/fighter utility functions

## Progress
- get_fighter_id_from_fighter_kind (3,604B) — 100%, get_entry_in_fighter_param_kind_struct (15,848B) — 78%
- change_status_lost (108B) — 100%, set_force_flashing (124B) — 100%
- 10 item/fighter utility functions (get_item_kind 94%, remove_item_from_id 91%, etc.)
- FighterEntry struct: +0x591F partner_flags, +0x5935 is_unloaded
- Key: asm("") barriers, u32 vs u64, csel vs branch divergence

## Continue with
- More small item/fighter utility functions (100-200B, vtable-chain pattern)
- is_fighter_enabled (88B), get_fighter_entry_id (172B), item_throw (136B)
- fighter_status.cpp AI functions
- Hash-to-value switch pattern functions (match well)

## Skipped (don't retry)
- NEON functions, Ghidra jump table failures, global-ref ADRP mismatches
- is_loaded_fighter — NX reorders singleton check

## File Territory
- src/app/fighter_core.cpp, fighter_status.cpp, fighter_attack.cpp

## Quality Rules
- No naked asm, 3-attempt limit, derivation chains

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
- Use `run_in_background` for any build that takes >10 seconds
- **WARNING:** Do NOT use `build.bat` — it runs deprecated post-processors that inflate match counts

## Ghidra Cache
- Save ALL Ghidra decompilation results to `data/ghidra_cache/pool-b.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work
- Append new results after each `mcp__ghidra__decompile_function_by_address` call

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `pool-b: decomp MODULE functions (N new, M matching)`
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
