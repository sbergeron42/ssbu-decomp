# Worker: pool-b

## Model: Opus

## Task: Fighter core + sv_kinetic_energy — continue game-logic utility functions

## Progress (104 functions total)
- 82 functions from previous sessions
- 22 new functions this round (batch 025):
  - 2 relocation-only matches: FUN_71003e5ba0 (BST delete), FUN_71003de250 (IsAttack/container reset)
  - 9 high-match (79-85%): sv_kinetic_energy readers (speed_x/y/xy/xyz, accel/brake/stable/limit xy),
    FUN_71003f8c50, FUN_71003dd500 (GetOffset2)
  - 11 non-matching but correct logic: flag toggle, BattleObject activate/deactivate,
    conditional vtable dispatchers, destructors, effect spawn
  - Key insight: sv_kinetic functions use float registers (LDR S) in binary but our u32 reads
    use integer registers (LDR W). Float vs int register selection is a type-system difference.

## Continue with
- Fighter core named functions: SetGrCollisionMode (160B), SetInvalidInvincible (176B),
  IsFlagFromNo (164B), IsIgnoreDistance (200B), SetAttackCameraQuakeForced (164B)
- CancelMainColor (128B), CreateArticles (128B), ResetSafePos (100B)
- calc_reaction_frame (152B) — DamageTransactorImpl param lookup
- More sv_kinetic_energy functions in 0x71022 range

## Skipped
- Set2ndPrecede (92B), Set2ndDisableCollision (92B) — cxa_guard_acquire pattern
- GenerateArticleForTarget (180B) — complex article creation with multiple fallback paths
- FUN_71003fd310 (96B) — effect module call, 0% match (param type mismatch)

## File Territory
- src/app/fun_batch_b_*.cpp (batch files)
- src/app/fighter_core.cpp

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
