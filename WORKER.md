# Worker: pool-a

## Model: Opus

## Task: AI module helpers + weapon param readers

## Progress
- Round 1-5: 68 effect functions (FOOT_EFFECT, DOWN_EFFECT, etc.) — COMPLETE
- Round 6a: 30 AI helper functions in ai_helpers_a.cpp
  - 16 perfect byte matches (100%)
  - 14 non-matching (relocation diffs or scheduling diffs — structurally correct)
  - Key patterns: AI_CTX/AI_STATE macros, indexed param tables, analyst double-deref
- Round 6b-d: 93 weapon param readers in weapon_params_a.cpp
  - All structurally correct (diffs are ADRP+LDR relocations only)
  - FPA2 singleton at 0x71052bb3b0
  - Domains: daisydaikon(16), kroolcrown(6), log(13), buddybomb(17),
    explosionbomb(1), pickelobject(12), rockman_metalblade(11),
    pacman(5), poweresa(4), robotgyro(3), wiifitball(4)

## Continue with
- More AI helpers: floor_moves (16B return), add_stick_abs (NEON), width (52B)
- distance_x_to_target, distance_y_to_target (60B each) — need FUN_7100314030 extern
- get_safe_fall / get_safe_fall_current (52B each, stack local pattern)
- More weapon param readers — check 0x71016* for remaining uncompiled
- Larger AI functions: check_line_segment, most_earliest_weapon, floor_lr

## Skipped
- floor_moves (20B) — returns 16-byte struct, ABI complexity
- add_stick_abs (24B) — NEON vector add, needs float vector type matching

## File Territory
- src/app/ai_helpers_a.cpp (AI module helper functions)
- src/app/weapon_params_a.cpp (FPA2 weapon/fighter param readers)

## Quality Rules
- No naked asm, 3-attempt limit
- Use AI_CTX/AI_STATE macros for pointer chains
- Use FPA2_2/FPA2_3 macros for param reader chains
- Verify return type via ldr encoding: bd = float (s0), b9 = int (w0)
- HIDDEN on all extern data symbols (prevents GOT indirection)
- disable_tail_calls attribute when original uses bl (not b)

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
