# Worker: pool-d

## Model: Opus

## Task: BST entry manager + stage functions — 0x710317xxxx range

## Progress (22 functions total from prior + this session)
- 8 param reader functions from prior session (all compiled)
- 14 new functions this session:
  - 7 BST-at-0x58 set/clear functions (all size-match): FUN_7103176f70, 7103177160, 7103177250, 7103177430, 7103177520, 7103177610, 7103177850
  - 1 BST-at-0x58 set+check+notify: FUN_7103177060 (248B vs 256B, 8B short — 2 extra optimizations)
  - 1 fiber switch: FUN_710317f0a0 (88B size-match, likely byte-match after linking)
  - 3 stage reversal BST-at-0x50: FUN_71031796f0, 7103179860, 71031799e0 (16B short — GOT/guard patterns)
  - 1 death boundary: FUN_710317b2e0 (244B vs 264B)
  - 1 team param: FUN_710317b3f0 (280B vs 312B — NEON ABI mismatch)

## Key patterns discovered
- BST-at-0x58 manager struct: +0x20 current_id, +0x38 mode, +0x58 BST root
- BST node: left[0], right[8], ..., key[0x20], value[0x28]
- Set/clear functions follow template: BST lookup → set field → if match + mode<3 → second lookup → notify via vtable[6]
- Stage reversal uses BST-at-0x50, dispatches to Stage_Rev string table and FUN_710240cd00
- Team param function uses NEON v0 for first arg (not integer), ldarb for guard acquisition

## Continue with
- More uncompiled HARD functions in 0x710317xxxx range (~20 remaining)
- FUN_7103177960 (960B) — larger BST function
- FUN_710317c0f0 (2160B), FUN_710317dc70 (848B set_offset), FUN_710317dfc0 (960B set_zone)
- SituationLink (1588B), StageColorCorrectionController (704B)

## Skipped
- FUN_7103176e64 (244B), FUN_71031776ec (356B) — listed as functions but Ghidra shows only abort(), likely alignment padding

## File Territory
- src/app/param_loading.cpp

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
