# Worker: pool-a

## Model: Opus

## Task: Effect template functions — ALL COMPLETE (68/68)

## Progress (68/68 complete, 100%)
- 4 perfect byte matches: EFFECT_REMOVE_ATTR, EFFECT_OFF_HANDLE, LAST_EFFECT_SET_WORK_INT, EFFECT_OFF
- Patterns: kill_all/kill_kind, req_on_joint, req_follow, FLW_POS, FLIP+hash swap, COLOR/ALPHA post-process
- FUN_7102288620 shared parser decomped: EFFECT_COLOR, COLOR_WORK, ALPHA, FLIP, FLIP_ALPHA
- CSE divergence: upstream Clang CSEs DAT_7104861960 loads, ~85-95% size
- 16-arg inline readers: EFFECT (86%), EFFECT_WORK_R (84%), EFFECT_BRANCH_SITUATION (86%)
- PRNG: EFFECT_FOLLOW_RND (91%), FOLLOW_RND_WORK (93%), FOLLOW_FLIP_RND (87%)
- Terrain: LANDING_EFFECT (102%), LANDING_EFFECT_FLIP (100.5%), FOOT_EFFECT_FLIP (97%)
- Final batch: PLAY_LANDING_SE, REG_LANDING_SE, REMOVE_FINAL_SCREEN_EFFECT (60% prologue sched)
- EFFECT_FOLLOW_arg12 (86% size, joint function table)
- EFFECT_FOLLOW_LIGHT (90% size, 17-arg + PostureModule LR + light vtable)
- CENTER_TOP_NODE (106% size, scalar math vs NEON rsqrt in original)
- FOOT_EFFECT (24% size, helper vs inline 16-arg), DOWN_EFFECT (16% size, same)

## Status: COMPLETE — no remaining targets in sv_animcmd_effect.cpp

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
