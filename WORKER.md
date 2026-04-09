# Worker: pool-a

## Model: Opus

## Task: Effect template functions — 15 remaining, ~31 KB

## Progress (53/68 complete, 78%)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF
- Patterns: kill_all/kill_kind, req_on_joint, req_follow, FLW_POS, FLIP+hash swap, COLOR/ALPHA post-process
- FUN_7102288620 shared parser decomped: EFFECT_COLOR, COLOR_WORK, ALPHA, FLIP, FLIP_ALPHA
- CSE divergence: upstream Clang CSEs DAT_7104861960 loads, ~85-95% size
- NEW: EFFECT (86%), EFFECT_WORK_R (84%), EFFECT_BRANCH_SITUATION (86%) — 16-arg inline readers with vec packing
- NEW: EFFECT_FOLLOW_RND (91%), FOLLOW_RND_WORK (93%), FOLLOW_FLIP_RND (87%) — XOR-shift128 PRNG + randomization
- NEW: LANDING_EFFECT (102%), LANDING_EFFECT_FLIP (100.5%), FOOT_EFFECT_FLIP (97%) — terrain-aware with StageManager

## Continue with (15 remaining)
- FOOT_EFFECT (~4.1 KB, inline 16-arg + terrain logic, needs StageManager)
- DOWN_EFFECT (~4.0 KB, inline 16-arg + terrain at offset 0x78)
- EFFECT_GLOBAL_BACK_GROUND, EFFECT_GLOBAL_BACK_GROUND_CENTER_TOP_NODE, EFFECT_GLOBAL_BACK_GROUND_CUT_IN_CENTER_POS (~4 KB, need FUN_710228ea70)
- EFFECT_FOLLOW_LIGHT (NEON + PostureModule, ~4 KB)
- Remaining smaller functions from original 24 list

## File Territory
- src/app/sv_animcmd_effect.cpp

## Quality Rules
- No naked asm, 3-attempt limit

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
- Use `run_in_background` for any build that takes >10 seconds
- **WARNING:** Do NOT use `build.bat` — it runs deprecated post-processors that inflate match counts

## Ghidra Cache
- Save ALL Ghidra decompilation results to `data/ghidra_cache/pool-a.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work
- Append new results after each `mcp__ghidra__decompile_function_by_address` call

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `pool-a: decomp MODULE functions (N new, M matching)`
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
