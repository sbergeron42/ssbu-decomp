# Worker: pool-c

## Model: Opus

## Task: ROLLBACK CRITICAL PATH — heap/arena map (allocator init + arena boundaries)

## Priority: HIGH — needed to make savestating feasible

## Context
Rollback savestate cost is dominated by how much guest memory must be snapshotted per frame. Slippi only snapshots ~few MB of Melee's 24MB because the mutable regions are known. For Smash, we currently have to assume "everything," which is too slow. **A memory map turns savestating from "probably infeasible" into "probably fine."**

## What To Find

### Per-system arena boundaries
For each major gameplay system, find:
- The allocator init function
- Base address of its arena
- Size of its arena
- Whether it's persistent (CSS, stage data) or per-match (mutable, needs savestating)

Required systems:
1. **FighterManager** — fighter slot data, fighter info
2. **BattleObjectManager** — battle object pool, module accessors
3. **ItemManager** — item entry pool
4. **StageManager** — stage state, dynamic stage data
5. **Physics / kinetic** — physics world, collision data
6. **Effect system** — particle pool
7. **Sound system** — sound state
8. **Lua/ACMD** — Lua state (likely big — fighters have per-instance Lua VMs)

### Allocator init xref
- Find the top-level memory init that creates these arenas
- Look for `nn::os::SetMemoryHeapSize` or similar Switch SDK calls
- Look for `je_mallocx`, `je_aligned_alloc` xrefs near the manager singletons

## Output

Create `docs/rollback/memory_map.md` with:

```
| System              | Arena base       | Size      | Type       | Init function     | Notes |
|---------------------|------------------|-----------|------------|-------------------|-------|
| FighterManager      | 0xXXXXXXXX       | NNN MB    | per-match  | initFn @ 0xXXXX   | ...   |
| BattleObjectManager | 0xXXXXXXXX       | NNN MB    | per-match  | initFn @ 0xXXXX   | ...   |
| ...                 | ...              | ...       | ...        | ...               | ...   |
```

Plus a section listing **persistent** vs **per-match** regions clearly. Per-match regions are what savestating needs to capture.

## Approach
1. We already know the singletons:
   - `app::FighterManager` instance (find via .dynsym)
   - `BattleObjectManager` (DAT_71052b7ef8 area)
   - `ItemManager` (created by pool-c earlier in `include/app/ItemManager.h`)
   - `app::StageManager` (DAT_71052b7f00 area, also DAT_71053299d8)
2. For each singleton, find its **constructor** in Ghidra. The constructor reveals:
   - Inline allocations of inner pools
   - Calls to `je_aligned_alloc` or game-specific allocators with sizes
3. Trace the allocator calls back to their actual init in main startup
4. The Nintendo SDK heap setup is usually visible early in `nnMain` or equivalent

## Output Files
- `docs/rollback/memory_map.md` (primary deliverable)
- Optionally: extend `include/app/` headers with the singleton type definitions if you discover new layout info

## Quality Rules
- Documentation is the primary deliverable
- NO `FUN_` names, NO Ghidra vars in any committed code
- Cast density under 10%

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
