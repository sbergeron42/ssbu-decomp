# Worker: pool-d

## Model: Opus

## Task: Game core + params — continue (misc remaining targets)

## Progress
- Previous sessions: param_loading.cpp (6824 lines), game_core.cpp (185 lines), global_param_init.cpp (2339 lines)
- Previous batches: fun_batch_d_001-020, fun_batch_d2_001-008, fun_batch_d3_001-023, fun_batch_d4_001-026, fun_batch_d5_001-054
- Previous hard batches: fun_hard_d_001-029, fun_hard_d3_001, fun_med_final_d_001-043
- Current round: misc remaining EASY/HARD functions (allocator hooks, effect cleanup, destructors, optnone wrappers)

## Continue with
- Remaining EASY/HARD targets from next_batch.py
- FUN_7100228110/7100228130 (32B) — allocator dispatch hooks
- FUN_7101958da0/710195f150 (96B) — effect cleanup (chain of accessor reads)
- FUN_7101b799b0 (80B) — destructor with sub-object cleanup
- FUN_7103600360/7103609340 (80B) — destructor patterns
- 0x71039500 cluster — optnone wrappers (simple thunks, bool returns, index dispatch)
- FUN_7103946160 (80B) — jemalloc background_thread check

## Skipped
- 4-byte EASY stubs (FUN_7100407e0c etc.) — actually large scene init functions, CSV sizes wrong
- FUN_7100155670 (12B listed but actually huge) — CSV size mismatch
- FUN_71001c0740 — networking (nn::socket), complex
- FUN_7102f77000 — deque container manipulation, too complex
- FUN_7101d0b940 — ldaxr/stlxr atomic refcount, can't match CAS

## File Territory
- src/app/param_loading.cpp, game_core.cpp, global_param_init.cpp
- src/app/fun_hard_d_030.cpp+ (new batch files)

## Quality Rules
- No naked asm, 3-attempt limit
- Struct access over raw offsets where headers exist
- Derivation chains for named fields

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
- Use `run_in_background` for any build that takes >10 seconds
- **WARNING:** Do NOT use `build.bat` — it runs deprecated post-processors that inflate match counts

## Ghidra Cache
- Save ALL Ghidra decompilation results to `data/ghidra_cache/pool-d.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work
- Append new results after each `mcp__ghidra__decompile_function_by_address` call

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `pool-d: decomp MODULE functions (N new, M matching)`
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
