# Worker: pool-d

## Model: Opus

## Task: Phase 3 — Define BossManager struct + rewrite boss-related functions

## Status: MOSTLY COMPLETE (2026-04-09)
- BossManager.h created with BossManagerInner (8 fields mapped)
- 8 src/ files rewritten to use typed struct access (~30 casts eliminated)
- FighterParamAccessor2 placeholder struct created (15 fields)
- 4 new boss functions decomped (send_event_on_boss_defeat, FUN_7102208bf0, FUN_7102208b10)
- 2 naked asm functions removed (banned), 2 complex functions skipped (NX prologue mismatch)
- Next: more xref-driven decomps, extend BossManagerInner fields

## Priority: TYPE RECOVERY (struct definition + consumer rewrite)

## Context
`BossManager` is a singleton (~30 raw offset references across 3+ files). Its name is confirmed from .dynsym. Functions like `is_boss_stop` access it via `DAT_71052b7ef8` → deref → inner pointer → fields. The reviewer rejects >10% cast density, and placeholder structs go in `include/app/placeholders/`.

## File Territory
- `include/app/BossManager.h` (CREATE — name is .dynsym confirmed)
- Any `src/` files with boss manager raw offset access (fighter_core.cpp, BossManager.cpp, etc.)
- After BossManager: sweep remaining high-cast-density files and create placeholder structs for any unknown types to bring density under 10%

## What To Do

### Step 1: Map the BossManager struct layout
Known from existing code:
- Singleton at `DAT_71052b7ef8`
- +0x8: inner pointer (to BossManagerData or similar)
- inner+0x164: stop_count (s32, compared > 0)

Use `mcp__ghidra__search_functions_by_name` for "Boss" to find more boss functions, then decompile them to map additional fields.

### Step 2: Define the struct
```cpp
struct BossManagerInner {
    u8 unk_0x00[0x164];
    s32 stop_count;         // +0x164 [derived: is_boss_stop checks > 0]
    // ...
};

struct BossManager {
    u8 unk_0x00[0x8];
    BossManagerInner* inner; // +0x8 [derived: is_boss_stop derefs this]
    // ...
};
```

### Step 3: Rewrite boss functions
Replace raw offset chains with struct access:
```cpp
// BEFORE:
u8* bm = reinterpret_cast<u8*>(DAT_71052b7ef8_bm);
u8* inner = *reinterpret_cast<u8**>(bm + 8);
return *reinterpret_cast<s32*>(inner + 0x164) > 0;

// AFTER:
BossManager* bm = DAT_71052b7ef8_bm;
return bm->inner->stop_count > 0;
```

### Step 4: Sweep for remaining high-density files
After BossManager, grep `src/` for files with high reinterpret_cast density. For each unknown pointer type, create a placeholder struct in `include/app/placeholders/` and log it in `data/undefined_types.md`. Priority targets:
- `engine_functions.cpp` (260 casts)
- `lua_acmd.cpp` (253 casts)
- `fighter_motion.cpp` (281 casts)

Even creating `UnkType_ADDR.h` with a few known fields reduces cast count significantly.

## Rules
- Cast density must stay under 10% or your diff gets REJECTED
- Create placeholder structs for any new unknown types
- Every named field needs `[derived:]` or `[inferred:]` provenance
- Log all placeholder structs in `data/undefined_types.md`

## Self-Check
```bash
python tools/review_diff.py pool-d
```

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
