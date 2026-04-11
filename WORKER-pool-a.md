# Worker: pool-a

## Model: Opus

## Task: ROLLBACK Round 10 — BattleObjectManager pool contents (the big one)

## Priority: HIGHEST — unblocks ~2 MB of rollback walker coverage

## Context
The Eden-side rollback snapshotter is live-validated against a real Smash process as of today. 3,772 bytes per snapshot currently captured. Next gap: the mutable gameplay state — fighter positions, items, effects, boss state. **Without BattleObject pool coverage, the first determinism test will diff on frame 1 and we won't know if it's walker incompleteness or a real correctness bug.**

`memory_map.md` confirms: `DAT_71052B7548` = array of 5 `PoolHeader*`, one per BattleObject category. Each header has `+0x08 base` and `+0x18 count`. This task maps the 5 categories concretely.

## What To Find

For **each of the 5 BattleObject pool categories** (indices 0-4):

1. **Category name** (what kind of object) — Fighter, Weapon, Item, Effect, Gimmick, etc.
2. **Per-object struct size** (min-known, conservative upper bound is fine)
3. **Stride between objects in the pool** (memory_map.md says cat 0 is stride 0x380 — verify + find the other 4)
4. **Live predicate** — what determines which entries in `base[0..count]` are live?
   - (a) the count field itself (everything [0..count) is live, [count..capacity) is dead)
   - (b) a generational ID pattern in each object
   - (c) an `is_active` bit somewhere in each object's header
   - (d) something else
5. **Representative steady-state count** for 1v1 match (2 fighters, no items, base stage)

## Methodology

### Start from the BattleObject registration/lookup functions
We already have:
- `tryFindBattleObjectById_71003ac560` — the lookup function (renamed in Round 2)
- `DAT_71052B7548` = pool-header array
- `get_battle_object_from_id @ 0x71003ac560` reads the high 4 bits of the object ID to select a pool category → that's the **category encoding**

Use `mcp__ghidra__decompile_function_by_address 0x71003ac560` — it's small and already partially named. The decompile will show:
- How the category index is extracted from the ID
- How the pool header is indexed (`DAT_71052B7548[category]`)
- How `base + index * stride` is computed (→ that's your stride per category)
- How the "is this entry live?" check works (→ that's your live predicate)

### Find the pool constructor
The sole writer of `DAT_71052B7548` is somewhere in the BattleObjectManager init. Use `tools/xref_bin_scan.py` on `0x71052B7548`:
```bash
python tools/xref_bin_scan.py store-offset 0x52B7548
```
The writer is the function that allocates the 5 pools. Decompile it — it will show:
- The allocation size per pool (`je_aligned_alloc(align, stride * capacity)`) → gives you both stride and max capacity per category
- The 5 distinct `je_aligned_alloc` calls, one per category

### Find the per-category name
Each pool's element class is named in `.dynsym` mangled symbols like `app::BattleObject::...`, `app::Weapon::...`, etc. Once you have the struct's vtable address from the constructor, use `mcp__ghidra__get_xrefs_to` on the vtable to find the concrete-object ctor, and the mangled ctor name reveals the class.

### Find the live predicate
Look at `tryFindBattleObjectById`'s logic. It either:
- Reads count and compares index → live predicate is count-based
- Reads a generational tag at a specific offset in the object → live predicate is generational (only live if `obj->gen == id_top_byte`)
- Reads an active flag → live predicate is flag-based

Document which, and the exact field offset + type.

### Steady-state count
For a 1v1 match, each category's count at runtime. You can estimate statically (by reading how the ctor initializes count to 0 and how fighter/weapon/item spawns increment it), or report "ask for dynamic confirmation" if static isn't conclusive.

## Output

Create `docs/rollback/battle_object_pools.md` with:

```markdown
# BattleObject pool layout — rollback walker reference

## TL;DR
5 categories, total live-object coverage in 1v1 steady state ≈ N objects × avg stride S = ~X KB

## Pool header struct (at *DAT_71052B7548[i])
| Offset | Type | Field | Notes |
|--------|------|-------|-------|
| +0x00 | ... | ... | ... |
| +0x08 | void* | base | start of pool array |
| +0x18 | u32 | count | current live count (or capacity — document which) |
| ...   | ...  | ...      | ... |

## Per-category layout

### Category 0 — [Fighter?]
- Class: `app::BattleObject_Fighter` (or similar)
- Vtable: `0x710XXXXX`
- Struct size: `0xNNN` bytes
- Stride: `0x380` (per memory_map.md)
- Max capacity: N
- 1v1 steady-state count: ~2
- Live predicate: [count-based / generational / flag-based] — details

### Category 1 — [Weapon? / Item?]
...

### Category 2 — ...

### Category 3 — ...

### Category 4 — ...

## Walker integration notes
[concrete pseudocode for the rollback walker to iterate all live objects]

## Open questions
[anything that needs dynamic confirmation]
```

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts on any address:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

**Fall-back priority**: if you can only answer ONE category fully in the time you have, make it **Category 0 (fighters)** — that's 90% of the walker's value.

## Quality Rules
- Documentation is the primary deliverable
- NO `FUN_` names in any committed src/ code (this task may not write any src/)
- If you do write src/, standard quality rules apply

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
