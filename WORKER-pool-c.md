# Worker: pool-c

## Model: Opus

## Task: ROLLBACK Round 10 — ItemManager + BossManager struct sizes, plus allocator-reachability confirmation

## Priority: HIGH — completes singleton struct-size table, confirms sim path is allocation-free

## Context
The Eden-side rollback snapshotter is live. Two singleton slots are resolved (`DAT_71052C3070` for ItemManager, `DAT_71052B7EF8` for BossManager) but the walker doesn't know how many bytes to snapshot from each instance. We need conservative upper bounds on struct size.

Secondary task: confirm statically that `FUN_7103724a80`'s subtree doesn't hit `je_aligned_alloc` in steady-state gameplay. If yes, Eden can skip the OOM-retry shim entirely (cleanup win, not a blocker).

You have two tasks. Do them in parallel if you have capacity; Task 1 is the primary.

---

## Task 1 — ItemManager + BossManager struct sizes

### ItemManager
- Singleton slot: `DAT_71052C3070` (confirmed per memory_map.md)
- Header: `include/app/ItemManager.h` exists from Phase 1 (pool-c wrote it). Read it first — it may already have partial layout info.
- Need: **min-known struct size** (conservative upper bound — safe under-estimate is fine)

### BossManager
- Singleton slot: `DAT_71052B7EF8` (confirmed)
- Header: `include/app/BossManager.h` exists from Phase 3 (pool-d wrote BossManager + BossManagerInner). Read it first.
- Already known from Phase 3: `BossManagerInner` ≥ 0x170 bytes
- Need: confirm the full `BossManager` struct (outer wrapper, NOT BossManagerInner) size

### Methodology

For each singleton:
1. Read the existing header to see what's already typed
2. Find the constructor: `tools/xref_bin_scan.py store-offset <slot_offset>`
3. Decompile the constructor — the `je_aligned_alloc(align, size)` call at the top gives you the **exact allocation size**, which is the definitive struct size upper bound
4. If the ctor is too large, just find the `je_aligned_alloc` call specifically — it's what we care about
5. Cross-check against the largest field offset written by the ctor (field writes past the allocation size would indicate a partial match)

### Output

Update `docs/rollback/memory_map.md`:
- Fill in the `Root struct size` column for ItemManager and BossManager in the Singleton Root Set table
- If the sizes differ from what memory_map.md currently claims, add a correction note
- Write the **walker snapshot range** for each: "snapshot `*DAT_71052C3070` for N bytes" and "snapshot `*DAT_71052B7EF8` for M bytes"

Also extend `include/app/ItemManager.h` and `include/app/BossManager.h` with the confirmed full struct size via a `static_assert(sizeof(...) == ...)` or a comment `// size = 0xNNN [derived: ctor je_aligned_alloc]`.

---

## Task 2 — je_aligned_alloc reachability from FUN_7103724a80 subtree

### The question
Does any function in the `FUN_7103724a80 → FUN_7103724d94 → FUN_71022df070 → vt[+0x60/+0x40/+0x90]` subtree call `je_aligned_alloc` **in steady state** (1v1, two fighters, no items, no new spawns)?

If no: Eden can skip the OOM shim entirely (cleanup win).
If yes: the shim stays load-bearing. List the specific callers.

### Methodology

This is a static xref walk. The target address is `je_aligned_alloc` at `0x710392dce0`.

1. `mcp__ghidra__get_function_xrefs FUN_710392dce0` — enumerate every caller
2. For each caller, is it inside the `FUN_7103724a80` subtree? The subtree addresses:
   - `0x7103724a80` (audited, has 1 je_aligned_alloc call in an OOM-retry branch — already known)
   - `0x7103724d94` (audited recursing, cached in `data/ghidra_cache/FUN_71022df070.txt`)
   - `0x71022df070` (audited, 49 lines, no direct alloc calls)
   - The vt[+0x60/+0x40/+0x90] target functions on fighter-task classes
3. For each subtree caller of `je_aligned_alloc`, decompile the containing function and check the gate — is it on a hot path, or is it gated on an allocation-failure fallback / first-use lazy init?
4. Steady-state definition: a gate that is TRUE only on the first frame of a match (e.g. "if this->buffer == nullptr, allocate") is NOT a steady-state alloc. A gate that is TRUE every frame is.

### Output

Append to `docs/rollback/sim_tick_safety.md` Round 9 addendum a new subsection `### Allocator reachability — Round 10`:

```markdown
### Allocator reachability — Round 10

Static audit: does FUN_7103724a80's subtree reach je_aligned_alloc
in steady state (1v1 match, two fighters, no new spawns)?

**Verdict**: [CLEAN — no steady-state allocs / DIRTY — list of callers]

#### Callers of je_aligned_alloc inside the subtree
| Caller | Gate | Steady-state? |
|--------|------|--------------|
| ...    | ...  | ...          |

#### Eden implication
[Shim can be dropped / shim stays load-bearing]
```

---

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Priorities if time is short
Task 1 > Task 2. Task 1 is a concrete walker requirement; Task 2 is a cleanup optimization.

## Quality Rules
- Documentation is the primary deliverable
- If you do modify `include/app/ItemManager.h` or `BossManager.h`, follow the project rules (derivation comments, struct field access, etc.)
- `tools/xref_bin_scan.py` is available for binary scans

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
