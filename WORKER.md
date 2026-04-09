# Worker: pool-a

## Model: Opus

## Task: AI module helpers — small getter/accessor functions

## Progress
- Round 1-5: 68 effect functions (FOOT_EFFECT, DOWN_EFFECT, etc.) — COMPLETE
- Round 6: 27 AI helper functions in ai_helpers_a.cpp
  - 14 perfect byte matches (100%)
  - 13 non-matching (relocation diffs or scheduling diffs — structurally correct)
  - Key patterns: AI_STATE chain, ai_param indexed tables, analyst double-deref

## Continue with
- More AI helpers: floor_moves (16B return), add_stick_abs (NEON), add_button, change_mode, change_mode_action
- Larger AI functions: width (52B), check_line_segment (32B), most_earliest_weapon (36B)
- get_safe_fall / get_safe_fall_current (52B each, stack local pattern)
- distance_x_to_target, distance_y_to_target (60B each)
- Weapon param readers at 0x71016* (20-24B, ~60 functions)

## Skipped
- floor_moves (20B) — returns 16-byte struct, ABI complexity
- add_stick_abs (24B) — NEON vector add, needs float vector type matching

## File Territory
- src/app/ai_helpers_a.cpp (AI module helper functions)

## Quality Rules
- No naked asm, 3-attempt limit
- Use AI_CTX/AI_STATE macros for pointer chains
- Verify return type via ldr encoding: bd = float (s0), b9 = int (w0)
- HIDDEN on all extern data symbols (prevents GOT indirection)

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
