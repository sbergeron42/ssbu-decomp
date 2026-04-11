# Worker: pool-b

## Model: Opus

## Task: ROLLBACK Round 10 — EffectManager head struct + match-runtime sub-allocation sizes

## Priority: HIGH — unblocks walker coverage for particles + match runtime

## Context
The Eden-side rollback snapshotter is live. 3,772 bytes covered so far. The walker is blind to the EffectManager particle pool head bytes (reads from the wrong offset) and to the sub-allocations chained off the match-runtime singletons.

You have two independent tasks. Do **Task 1** first (EffectManager) since it's the immediate walker blocker; **Task 2** is layout enumeration that expands coverage but doesn't fix a bug.

---

## Task 1 — EffectManager head struct (from `memory_map.md`)

### What memory_map.md says
- Singleton: `*DAT_7105333920` → `EffectManager*`
- Pool stride: `0x300` per particle record
- Max entries: `<= 256` (top byte of u32 id is the slot index)
- **UNKNOWN**: the head-struct bytes in `[0, first_particle_offset]`. Is it `{vtable, ptr, ptr, count, array_base}`? Does the array start at `+0x20`? `+0x40`? Somewhere else?

### What To Find
1. Decompile the EffectManager constructor (via `mcp__ghidra__get_xrefs_to 0x7105333920`, find the sole non-null writer). The ctor will allocate the EffectManager object and initialize its fields. The field writes immediately after the vtable store give you the head layout.
2. Enumerate field offsets `[0, first_particle]`:
   - +0x00: vtable
   - +0x08, +0x10, ...: what?
3. Identify where the particle array `base` pointer lives (might be at +0x10, +0x18, +0x20 — ctor shows which).
4. Identify whether there's a `count` field or a free-list head.
5. **Check for adjacent .data slots**: `memory_map.md` noted `DAT_710533394X..DAT_710533395X` might be parallel pools (sound FX, trail meshes) but wasn't sure. Use `tools/xref_bin_scan.py` to enumerate globals in that range (`0x7105333920..0x7105333980`) and see if any are written by the same ctor or adjacent constructors.

### Output (append to `docs/rollback/memory_map.md`)
New section `## EffectManager head struct — Round 10`:

```markdown
### EffectManager head layout (before particle array)
| Offset | Width | Field | Notes |
|--------|-------|-------|-------|
| +0x00  | u64   | vtable | |
| ...    | ...   | ...    | |
| +0xNN  | void* | particles[] base | |

First particle at offset: 0xNN
Head struct size (snapshot range): 0xNN

### Adjacent .data slots
- DAT_71053339XX: [what it is / unused]
- ...
```

---

## Task 2 — Match-runtime sub-allocation sizes

### What memory_map.md says
Five match-runtime singletons listed with **wrapper sizes** but NOT **sub-allocation sizes**:
- `DAT_710593A6A0` (Mii fighter database — Round 4/6/7 content, some sizes already documented but verify sub-linked-list entries)
- `DAT_71052C26C0` (match-state entry list)
- `DAT_71052C2800` (sub-objects: `0x2e0`, `0x80`, `0xc8`)
- Plus the other two the doc lists

### What To Find
For each singleton that points to a wrapper struct containing a linked list or array of sub-allocations:
1. What's the sub-allocation size?
2. How many sub-allocations exist in steady state (1v1)?
3. Are they heap-allocated via `je_aligned_alloc` (walker snapshots each) or embedded inline (walker snapshots whole wrapper)?

### Methodology
Use `tools/xref_bin_scan.py store-offset <slot>` to find the sole non-init writer for each singleton. Decompile that writer — it allocates the wrapper and populates fields. The `je_aligned_alloc` calls inside the ctor give you the sub-allocation sizes directly.

### Output
New section in `docs/rollback/memory_map.md`:

```markdown
### Match-runtime sub-allocation sizes — Round 10

| Singleton | Wrapper size | Sub-allocs | Total |
|-----------|-------------|-----------|-------|
| DAT_71052C2800 | 0x... | 0x2e0 + 0x80 + 0xc8 | 0x... |
| ...            | ...   | ...       | ...   |

Aggregate match-runtime snapshot: ~X KB
```

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Priorities if time is short
Task 1 > Task 2. Task 1 fixes an active walker bug. Task 2 expands coverage.

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
