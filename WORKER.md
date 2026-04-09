# Worker: pool-d

## Model: Opus

## Task: BST entry manager + stage functions + small scattered functions

## Progress (26 functions total across all sessions)
- 8 param reader functions from prior session (all compiled)
- 14 BST entry manager + stage functions this session:
  - 7 BST-at-0x58 set/clear (all size-match): 7103176f70, 7103177160, 7103177250, 7103177430, 7103177520, 7103177610, 7103177850
  - 1 BST-at-0x58 set+check+notify: 7103177060 (248B vs 256B, 8B short)
  - 1 fiber switch: 710317f0a0 (88B size-match, likely byte-match after linking)
  - 3 stage reversal BST-at-0x50: 71031796f0, 7103179860, 71031799e0 (16B short)
  - 1 death boundary: 710317b2e0 (244B vs 264B)
  - 1 team param: 710317b3f0 (280B vs 312B — NEON ABI)
- 4 small scattered functions (all size-match):
  - FUN_7100082500 (76B), FUN_7100083d10 (76B) — float getter via vtable
  - FUN_710048c1d0 (80B) — conditional vtable dispatch
  - FUN_7100225b10 (84B) — mutex-locked field accessor

## Key patterns discovered
- BST-at-0x58 manager: +0x20 current_id, +0x38 mode, +0x58 BST root
- BST node layout: left[0], right[8], ..., key[0x20], value[0x28]
- Set/clear template: BST find → set field → if match + mode<3 → find again → notify via vtable[6]
- Stage reversal: BST-at-0x50, dispatches to Stage_Rev table + FUN_710240cd00
- Team param: uses NEON v0 for first arg, ldarb for guard, ccmp for && chains
- All data globals need __attribute__((visibility("hidden"))) to avoid GOT indirection

## Continue with
- FUN_710317b530 (320B) — float interpolation, calls FUN_710317b2e0
- FUN_710317b000 (464B) — BST lookup + flag + camera request
- FUN_710317cc20 (304B) — std::string comparison + update
- Named: set_offset (848B), set_zone (960B), SituationLink (1588B)
- Remaining small HARD targets are mostly jemalloc (skip per rules)

## Skipped
- FUN_7103176e64, FUN_71031776ec — Ghidra shows abort(), but CSV lists 244B/356B
- All 0x710395xxxx functions — jemalloc 5.1.0 library code

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
