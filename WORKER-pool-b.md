# Worker: pool-b

## Model: Opus

## Task: ROLLBACK Round 4 — identify what FUN_7103619080 dispatches (caller + tags)

## Priority: HIGH — Pool C identified this as the strongest sim-tick fallback candidate

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Last round, Pool C found that `FUN_7103619080` is a 432-byte visitor reachable from `main_loop @ 0x710374b124`. It walks a `vector<obj*>`, builds command packets per element via `vt[6]` factory + 2 copy-constructs, then dispatches each packet via `obj->vt[3]`. Per-element `flags[0xf1]` is the enabled gate. **This is the exact shape of a per-tick broadcast.**

We need to identify:
1. **What subsystem owns the vector** — by decomping the caller in main_loop and seeing what `x0` is
2. **What command packet type** — by resolving the static type tags `DAT_7105266f80` and `DAT_7105230f18`

## What To Do

### 1. Decompile the caller of FUN_7103619080
- The call site is `main_loop @ 0x710374b124`
- Read `data/ghidra_cache/main_loop_7103747270.txt` (already cached) and find the line at offset ~0x710374b124
- Look for the load of `x0` immediately before the BL: `LDR X0, [X21, #0xce8]` or similar
- What does `X21 + 0xce8` resolve to? Is `X21` a singleton pointer? An ADRP-loaded global?
- That's the subsystem object — identify its type

### 2. Identify the type tags
- `DAT_7105266f80` — used as `new_node->hdr` (first 8 bytes of the packet)
- `DAT_7105230f18` — used as `new_node->type_tag` (later in the packet)
- Use `mcp__ghidra__get_xrefs_to` on each address
- These are likely pointers to RTTI / type info / static descriptor objects
- If they're vtables, the type they belong to names the packet class

### 3. Identify the element type
- The vector elements are pointers to objects with:
  - A flag byte at `+0xf1`
  - A vtable with at least slot `[3]` taking `(this, packet*)`
- Find what class has these characteristics
- If it has a `+0xf1 flag` and `vt[3] = onTick(packet*)`, it's a tickable game object

### 4. Cross-reference with Pool A's MatchRunner finding
- Pool A is identifying `*DAT_710593a510` as the rollback arm signal
- If `FUN_7103619080`'s subsystem object is the same as `*DAT_710593a510`, then **Pool B's match-active gate AND Pool C's sim-tick candidate are the same code path** — that's the converged answer
- If they're different objects, the sim tick is somewhere else (likely Pool C's second strongest candidate `FUN_71035c13d0`)

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

Use `tools/xref_bin_scan.py` for binary scans.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool B — Round 4: FUN_7103619080 caller + tag identification

### Caller in main_loop @ 0x710374b124
- Subsystem object source: [global / x21 chain / ADRP load]
- Subsystem type: [class name / placeholder]
- Vector at +0x500/+0x508: holds [type] elements

### Type tags
- DAT_7105266f80: [identified class / RTTI / unknown]
- DAT_7105230f18: [identified class / RTTI / unknown]
- Command packet type: [name]

### Element type (vt[3] receivers)
- Class: [name]
- vt[3] signature: void (this, packet*)
- IS THIS A FIGHTER / BATTLE OBJECT? [YES / NO / INCONCLUSIVE]

### Cross-reference with Pool A's MatchRunner
- Same object as *DAT_710593a510? [YES — converged / NO — different paths / UNKNOWN]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
