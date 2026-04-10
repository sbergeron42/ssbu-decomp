# Worker: pool-b

## Model: Opus

## Task: Clean up fighter_motion.cpp + fighter_core.cpp — typed module access

## Priority: QUALITY CLEANUP

## Status: IN PROGRESS — Cast density within limits

### Progress
- `fighter_motion.cpp`: 246 → 122 casts (50% reduction, 6.4% density)
- `fighter_core.cpp`: 134 → 105 casts (22% reduction, 7.6% density)
- Both under 10% cast density threshold

### Created/Extended
- `include/types.h` — Added `Vector2f` struct
- `include/app/placeholders/WeaponParams.h` — 9 param structs (Mechakoopa, PeachDaikon, Doll, DollShape, ExplosionBomb, Holywater, LinkArrow, LinkBomb, Spawn)
- `include/app/modules/KineticModule.h` — Added gravity energy subclass fields (+0x34/+0x38/+0x3c)
- `include/app/placeholders/FighterAI.h` — Added fighter_kind_for_cmd at +0x988
- `include/app/placeholders/FighterParamAccessor2.h` — Added 3 physics param fields

### Remaining casts (irreducible)
- L-8 context extraction (FighterAI/BattleObject from lua_State)
- FPA2 singleton dereference chains
- Vtable dispatch casts
- AI attack info table raw access (target struct untyped)
- Boss energy subclass fields at +0x88/+0x8c/+0x90/+0xa0/+0xa4

## File Territory
- `src/app/fighter_motion.cpp` (CLEANUP)
- `src/app/fighter_core.cpp` (CLEANUP)
- `include/app/modules/*.h` (extend if needed)
- `include/app/placeholders/` (create placeholders for non-module types)

## Do NOT
- Delete, add, or rename functions — internal cleanup only

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
