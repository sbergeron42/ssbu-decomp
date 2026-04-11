# Worker: pool-c

## Model: Opus

## Task: ROLLBACK — DAT_710593a530 match-state transition function

## Priority: HIGH — match-start signal for rollback arm/disarm

## Context
Pool B's breakthrough showed Dispatcher A inside main_loop is gated on `DAT_710593a530 == 3` (match active). See `docs/rollback/sim_tick_hunt.md`.

We need the **writer** of `DAT_710593a530` — the function that sets it to 3 when a match starts and resets it when a match ends. This:

1. Is the rollback arm/disarm signal — when value transitions to 3, rollback should activate
2. Answers the original "match-start signal" nice-to-have ask in one shot (two-for-one)
3. Verifies the flag isn't racy (atomic? sync primitive? plain store?)

## What To Do

### 1. Find the writer
- Use `mcp__ghidra__get_xrefs_to 0x710593a530`
- Filter for WRITE references (the read references include `main_loop` itself which we already know)
- For each writer: identify the surrounding function, the value being written, and the conditions

### 2. Identify the match-state state machine
- The writer is part of a state machine. Find all the states it can write (0, 1, 2, 3, ...)
- Each value is a phase of game lifecycle (boot? title? CSS? load? match active? results?)
- Document the state diagram

### 3. Verify atomicity
- Is the write `STR` (plain store), `STLR` (release), or `LDXR/STXR` (atomic CAS)?
- If atomic: the flag is safe to read from another thread without synchronization
- If plain: rollback must read it from the same thread or accept a stale read

### 4. Follow up — match-start callsite
- Where in the lifecycle does `3` get written?
- Is it inside a "load match" function? Right after the player slots are populated?
- Document the function chain so rollback knows the exact moment to arm

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool C — DAT_710593a530 match-state transition

### Writers
| Function | Address | Value written | Condition |
|----------|---------|---------------|-----------|
| FUN_XXXX | 0xXXXX  | 3 (active) | match start |
| FUN_XXXX | 0xXXXX  | 0 (idle) | match end |
| ...      | ...     | ...        | ... |

### State diagram
- 0 = ?
- 1 = ?
- 2 = ?
- 3 = match active
- ...

### Atomicity
- Store type: [STR / STLR / atomic CAS]
- Thread-safe to read: [yes / no]

### Match-start signal for rollback
- Function chain: ... → setMatchActive(3) at 0xXXXX
- Recommended hook point: [address] for rollback arm
```

Also update `docs/rollback/memory_map.md` if you discover the match-state global is part of a larger state struct that should be in the snapshot region.

## Stop-and-document rule
If `mcp__ghidra__*` returns an error, timeout, or "request failed":
1. Note the address and error
2. Append to `data/ghidra_cache/manual_extraction_needed.md` (create if missing):
   ```
   ## 0xXXXXXXXX (FUN_XXXXXXXX)
   - Pool: pool-c
   - Reason: timeout / too large / unknown error
   - Why we need it: [one-line context]
   ```
3. **Move on.** Do NOT retry the same address.

## Quality Rules
- NO `FUN_` names in committed src/ code
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
