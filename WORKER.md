# Worker: pool-a

## Model: Opus

## Task: Fighter specializer + sv_information/sv_fighter_util readers

## Progress (12 functions this session)
- 6 FighterSpecializer_Reflet functions (all size-matching):
  - get_final_chrom_pos (76B), set_final_chrom_pos (76B), get_final_chrom_lr (68B)
  - set_final_chrom_lr (116B), set_final_chrom_joint_rotate (100B), get_magickind (108B)
  - Pattern: ArticleModule→get_article(5)→posture/model dispatch on Chrom article
- 3 sv_information FighterInformation readers (all size-matching):
  - is_dead_up_force_crush (84B), sleep_time_mul (84B), get_dead_up_star_fall_prob (84B)
  - Pattern: WorkModule→get_int(0x10000000)→FM entries[id]→FI data→field
- 3 sv_fighter_util FPA2 param readers (all size-matching, LEAF on fast path):
  - get_default_fighter_param_walk_speed_max (72B), ground_brake (72B), air_brake_x (72B)
  - Pattern: BattleObject+0x198 kind → FPA2 index table → param entry → field
- Key patterns: prologue scheduling is only NX divergence, logic matches 100%

## Continue with
- More FighterInformation readers (same template, different field offsets)
- More FPA2 param readers (same template, different param offsets)
- owner_handi (104B), owner_rank (88B) — similar but use FUN_ calls
- set_on_rebirth (116B), set_dead_rumble (112B) — setters instead of getters
- More unnamed small functions in 0x71022xxxxx range

## Skipped
- vec2/vec3 math functions (NEON-only, impossible to match without NX compiler)
- slope/effect/sound/article/cancel/etc 180B sv_module_access (call FUN_71003cb840 private)
- create_burner_effect, is_ownered_item (Robot specializer, call private FUN_)

## File Territory
- src/app/fighter_specializer_reflet.cpp
- src/app/sv_information_a.cpp
- src/app/weapon_params_a.cpp (previous sessions)
- src/app/ai_helpers_a.cpp (previous sessions)

## Quality Rules
- No naked asm, 3-attempt limit
- All functions use typed struct access (PostureModule, WorkModule, ArticleModule, ModelModule)
- Derivation chains documented for every field offset

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
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
