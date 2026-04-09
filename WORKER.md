# Worker: pool-c

## Model: Opus

## Task: Stage + camera — continue

## Progress (82 functions total)
- 20 leaf functions from round 2 (3 perfect matches)
- 4 new functions from round 3 (size matches, minor scheduling diffs)
- 17 new functions this round (batch 3):
  - 10 relocation-only matches: screen_width, screen_height, screen_to_world,
    can_exist (shio/darz), add_movement (PERFECT), get_assist_respawn_position,
    create_weapon, calc_offset_with_gravity, search_range
  - 7 non-matching but correct: start_zoom_out (3 variants), start_bgm, end_bgm,
    get_bgm_kind, set_dead_range (2 variants — NEON vectorization diff)
- Key patterns: fcvtzu for unsigned float conversion, ternary for csel ne,
  asm("") barrier for tail-call prevention

## Continue with
- set_camera_param (2,344B), set_pause_camera_param (3,996B) — param tree lookups
- ~StageWufuIsland destructor (2,700B) — event listener cleanup
- convert_pos_dead_range_gravity (296B) — NEON math, may not match
- restore_pos_dead_range_gravity (196B) — sin/cos rotation
- change_camera_range (300B) / change_dead_range (292B) — BST lookup in StageManager
- More item leaf functions in 0x71015c0000-0x71015d0000 range

## Skipped
- create_stage (114,600B), StageBase ctor (14,820B) — too large
- IT_MOVE_CAMERA, is_clip_in_camera, is_dark_stage — shared_ptr refcount patterns
- set_camera_range variants (flyandhand/shiokarazu/crazyhand/marx) — shared_ptr atomics
- powf stub (4B) — GOT indirect, can't match
- is_flat_stage — guard variable __cxa_guard pattern

## File Territory
- src/app/camera_functions.cpp, StageManager.cpp, StageWufuIsland.cpp

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
- Save ALL Ghidra decompilation results to `data/ghidra_cache/pool-c.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work
- Append new results after each `mcp__ghidra__decompile_function_by_address` call

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `pool-c: decomp MODULE functions (N new, M matching)`
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
