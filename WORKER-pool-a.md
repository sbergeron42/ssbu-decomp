# Worker: pool-a

## Model: Opus

## Task: ROLLBACK — find what writes to `mii_manager + 0x24e8` (the back-reference to the real scene root)

## Priority: HIGH — most valuable lead after the previous breakthrough was demolished

## Context
Read `docs/rollback/sim_tick_hunt.md` first for full context. TL;DR:

- The previous "Dispatcher A is the sim tick" finding was wrong. `DAT_710593a6a0` is the **Mii fighter face database** (`MiiFighterDatabase`), not the scene root. Pool A confirmed this last session via its destructor.
- BUT — Dispatcher A's chain is `mii_manager + 0x24e8 → some other subsystem → +0x2da8 → list head`. The `+0x24e8` field is a **non-owning back-reference** to some other subsystem that the Mii manager needs a handle to.
- Whatever subsystem `+0x24e8` points to has its own list at `+0x2da8`. **If that subsystem turns out to be FighterManager, BattleObjectWorld, or the actual scene root, the original sim-tick hypothesis is rescued** (modulo the `DAT_710593a530 == 3` dead-flag issue, which is pool B's problem now).

## What To Do

### 1. Find the writer of `MiiFighterDatabase + 0x24e8`
The Mii manager singleton is at `*DAT_710593a6a0`. We need to find what code stores into `(*DAT_710593a6a0) + 0x24e8`.

**Methodology** (Pool C established this last session — Ghidra's xref index misses code in undefined regions, so use direct binary scanning):

1. Read `data/ghidra_cache/pool-c.txt` first — Pool C's session notes describe the ADRP-propagation scanner technique
2. Scan the ELF `.text` segment for ADRP+offset patterns that compute `*DAT_710593a6a0 + 0x24e8`
3. The key pattern to find: a function that does `LDR Xn, [DAT_710593a6a0]; STR Xm, [Xn, #0x24e8]`
4. The writer is almost certainly inside `FUN_71022b7100` (the Mii manager constructor — Pool B's previous session said it was 1.7 MB of disassembly and timed out Ghidra MCP — log to `manual_extraction_needed.md` if it times out again)

### 2. Identify the back-referenced subsystem
Once you find the value being stored at `+0x24e8`:
- What's its source? An ADRP-loaded global? A function return? Another singleton?
- If it's a known singleton (FighterManager, BattleObjectWorld, etc.), document the cross-reference
- If it's a new singleton, find ITS constructor and identify the type

### 3. Sanity-check Dispatcher A
With the back-referenced subsystem identified:
- Does it actually have a list at `+0x2da8`?
- What's the list element type (look at the destructor or constructor)?
- Are list elements polymorphic (vtable + various concrete types)?
- Does any element type look like a "fighter" or "battle object"?

## Stop-and-document rule
If `mcp__ghidra__*` returns an error/timeout/"too large":
1. Append to `data/ghidra_cache/manual_extraction_needed.md`:
   ```
   ## 0xXXXXXXXX (FUN_XXXXXXXX)
   - Pool: pool-a
   - Reason: timeout / too large / unknown error
   - Why we need it: [one-line context]
   ```
2. **Do NOT retry.** Move on.

`FUN_71022b7100` already failed once; expect it to fail again. The binary-scanner approach is your primary tool for this task — Ghidra is the fallback.

## Output

Append a new section to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool A — mii_manager+0x24e8 back-reference (next-pass)

### Writer site
- Address: 0xXXXXXXXX (in FUN_XXXXXXXX or undefined region)
- Stored value source: [ADRP global / function return / other]
- Source identification: [global address / called function / constant]

### Back-referenced subsystem
- Type: [identified class name OR "unknown subsystem at 0xXXXX"]
- Constructor: 0xXXXXXXXX
- Has list at +0x2da8: YES/NO
- List element type: [class name / size / vtable presence]

### Dispatcher A revisited
[REHABILITATED — list contains tickable game objects, sim tick lives here]
[OR: STILL DEAD — back-reference is to a non-tick subsystem (e.g. UI, audio)]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
