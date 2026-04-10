# Worker: pool-c

## Model: Opus

## Task: ROLLBACK CRITICAL PATH — heap/arena map

## Priority: HIGH — needed to make savestating feasible

## Context
Rollback savestate cost is dominated by how much guest memory must be snapshotted per frame. A memory map of mutable per-match arenas turns savestating from "probably infeasible" into "probably fine."

## IMPORTANT: Pre-cached decomps
**Two huge functions have already been decompiled to disk** (Ghidra MCP times out):
- `data/ghidra_cache/main_loop_7103747270.txt` (3947 lines)
- `data/ghidra_cache/FUN_7101344cf0.txt` (5891 lines — likely per-frame fighter update)

**Read these files with `Read` instead of calling Ghidra MCP for those addresses.**

## What To Find

For each major gameplay system, find:
- Allocator init function
- Base address of its arena
- Size of its arena
- Persistent (CSS, stage data) vs per-match (mutable, needs savestating)

Required systems:
1. **FighterManager** — fighter slot data, fighter info
2. **BattleObjectManager** — battle object pool, module accessors
3. **ItemManager** — item entry pool
4. **StageManager** — stage state, dynamic stage data
5. **Physics / kinetic** — physics world, collision data
6. **Effect system** — particle pool
7. **Sound system** — sound state
8. **Lua/ACMD** — Lua state (likely big — fighters have per-instance Lua VMs)

## Approach
1. We already know the singletons:
   - `app::FighterManager` (find via .dynsym)
   - `BattleObjectManager` (DAT_71052b7ef8 area)
   - `ItemManager` (`include/app/ItemManager.h` exists)
   - `app::StageManager` (DAT_71052b7f00 area, DAT_71053299d8)
2. Find each constructor in Ghidra → reveals inline allocations and `je_aligned_alloc` sizes
3. Trace allocator calls back to startup
4. Nintendo SDK heap setup is usually visible early in `nnMain` or equivalent
5. The cached `main_loop_7103747270.txt` shows the per-frame access patterns — useful for confirming which arenas are touched per tick

## Output

Create `docs/rollback/memory_map.md`:

```
| System              | Arena base       | Size      | Type       | Init function     | Notes |
|---------------------|------------------|-----------|------------|-------------------|-------|
| FighterManager      | 0xXXXXXXXX       | NNN MB    | per-match  | initFn @ 0xXXXX   | ...   |
| ...                 | ...              | ...       | ...        | ...               | ...   |
```

Plus a section listing **persistent** vs **per-match** regions clearly. Per-match regions are what savestating needs to capture.

## Quality Rules
- Documentation is the primary deliverable
- Cached Ghidra files are reference material, NOT to commit as src/
- NO `FUN_` names, NO Ghidra vars, NO raw casts in committed code

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
