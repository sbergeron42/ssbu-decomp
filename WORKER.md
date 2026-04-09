# Worker: pool-b

## Model: Opus

## Task: Item/boss/fighter param readers + leaf functions

## Progress (80 functions this session)
- Commit 1: 29 functions (15 matching) — LINKBOMB params, boss, kinetic, item vtable
- Commit 2: 22 functions (21 matching) — HOLYWATER params, backshield, rocketbelt
- Commit 3: 8 functions (6 matching) — item field readers, misc leaf
- Commit 4: 21 functions (21 matching) — buddybomb params, FM readers
- Total: 80 functions, 63 matching (79% match rate)

## Key patterns found
- LINKBOMB params: if(kind==0x78) FPA2→+0xe0→+0x1a8→+off; else 0.0f (40B, reloc-only match)
- HOLYWATER params: FPA2→csel(0x44→0xf50,else→0xf18)→+0x240→+off (40B, reloc-only match)
- Buddybomb params: FPA2→+0x12d0→+off (20B, reloc-only match)
- Item field readers: lua[-8]→+0x1a0→+0x190→+0x220→+off (24B, 100% match)
- Boss singleton: BossManager→+8→+off (40B, reloc-only match)

## Continue with
- More 20-40B named param readers in 0x71015c-0x71022 range (83 total remaining)
- sv_* module impl functions (25 remaining, some need in_x10 investigation)
- FighterManager/StageManager singleton readers
- Item vtable dispatch functions (96-160B range)

## Skipped (3-attempt limit or compiler divergence)
- is_loaded_metamon_fighter (5%) — condition reordering
- LINK_LINKBOMB_IS_EXPLODE (4%) — ADRP vs CMP ordering
- get_item_swing_motion_rate (16%) — ldrsw vs ldrb jump table
- 0x710395xxxx cluster — compiled at -O0, won't match

## File Territory
- src/app/fighter_attack.cpp, fighter_core.cpp, fighter_status.cpp

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME`
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build`
- **WARNING:** Do NOT use `build.bat`

## Ghidra Cache
- Save ALL Ghidra results to `data/ghidra_cache/pool-b.txt`

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes
