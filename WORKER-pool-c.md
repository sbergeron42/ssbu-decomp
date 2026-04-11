# Worker: pool-c

## Model: Opus

## Task: ROLLBACK Round 4 — investigate FUN_71035c13d0 (second strongest candidate) + cross-validation

## Priority: HIGH — backup angle in case Pool A and Pool B's leads converge or both fail

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Last round you found that `FUN_71035c13d0` is the **second strongest sim-tick candidate** — a 1048-byte function with 7 indirect dispatches in an observer-pattern double-broadcast over weak_ptr lists. Pool A and Pool B are working on the strongest candidate (`FUN_7103619080` + `DAT_710593a510`) this round. Your job is to:

1. **Decompile FUN_71035c13d0 in detail** so we have a fallback if Pool A/B's leads don't converge
2. **Cross-validate** Pool A and Pool B's findings if they finish before you do (read their committed diffs)

## What To Do

### 1. Deep-dive on FUN_71035c13d0
You already noted last round that this function dispatches:
- `vtable[3]`, `vtable[2]`, `vtable[7]`, `vtable[8]` through weak-ref `lock()`
- It's a **double observer broadcast over weak_ptr lists**

Now decompile the FULL function and answer:
- What's the type of param_1? (the subsystem holding the observer lists)
- What are the two lists being walked? Where do they live in param_1?
- What are the listeners observing? (event objects? state changes? per-frame ticks?)
- The `weak_ptr::lock()` pattern means listeners can be auto-removed when their owner dies — this is consistent with "subscribers register and unsubscribe over a match lifecycle"
- Look for any field touch on the dispatched objects that resembles fighter state mutation

### 2. Find the caller
- `FUN_71035c13d0 ← FUN_7103747270 @ 0x710374af6c` — that's main_loop
- Decompile the load of x0 immediately before the BL at `0x710374af6c`
- What subsystem owns this observer dispatcher?
- Same question as Pool B is asking about FUN_7103619080's caller

### 3. Cross-validate Pool A and Pool B (if they commit before you finish)
After your initial deep-dive, check if Pool A and Pool B have committed:
```bash
git log --oneline master..worker/pool-a
git log --oneline master..worker/pool-b
git fetch origin && git log --oneline master..origin/master  # if pushed
```

If they have findings, read them and check:
- Does Pool B's `FUN_7103619080` caller object match Pool A's `*DAT_710593a510` runner?
- If yes: **converged** — the sim tick is identified
- If no: which one is more likely to actually be on a per-frame path? Cast a tiebreak vote based on your observer/visitor pattern context
- Does FUN_71035c13d0 share any state with either of those? (Same singleton? Same vtable address? Same element type?)

### 4. Verdict
Rank the three candidates by likelihood of being the sim tick:
1. FUN_7103619080 (Pool B working on this)
2. FUN_71035c13d0 (your task)
3. ??? (any other lead you spot)

Document your ranking and the evidence.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool C — Round 4: FUN_71035c13d0 deep dive + cross-validation

### FUN_71035c13d0 detailed analysis
- Subsystem owner type: [class name / placeholder]
- Observer list 1: [contents / what's being observed]
- Observer list 2: [contents / what's being observed]
- Per-frame fighter state mutation? [YES / NO / INCONCLUSIVE]

### Caller in main_loop @ 0x710374af6c
- Subsystem object: [global / chain]
- Same as FUN_7103619080's caller? [YES / NO]

### Cross-validation
- Pool A finding: [summary]
- Pool B finding: [summary]
- Converged? [YES — sim tick identified / NO — leads diverge]

### Final ranking (most → least likely sim tick)
1. ...
2. ...
3. ...
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
