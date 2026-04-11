# Worker: pool-b

## Model: Opus

## Task: ROLLBACK — find the REAL match-active flag in `0x710593a___` block

## Priority: HIGH — `DAT_710593a530 == 3` is dead code; the real flag must exist elsewhere

## Context
Read `docs/rollback/sim_tick_hunt.md` first for full context. TL;DR:

- Pool C confirmed last session that `DAT_710593a530` is **never written non-zero** by static code. The only writer is a one-shot BSS clear from `.init_array`. The `== 3` test in `main_loop` (and 2 other readers) is dead under static analysis.
- The match-active flag MUST exist somewhere — `main_loop` must know whether to drive the sim during a match versus idle on the title screen.
- Pool C suggested two specific candidates in the same `0x710593a___` block:
  - **Byte cluster at `+0x540..+0x5a0`** — receives non-zero writes
  - **Integer at `+0x534`** — receives function-return values at `0x7103741bb4` and `0x71037472d0`

## What To Do

### 1. Audit `0x710593axxx` block globals
Use the binary scanner methodology Pool C documented in `docs/rollback/sim_tick_hunt.md` (search for "Methodology note for next pool" — Pool C wrote a step-by-step ADRP-propagation scanner spec).

Enumerate every global in the range `0x710593a000..0x710593b000`:
- Find every static writer for each one
- Filter: keep only globals with at least one **non-zero static writer** AND at least one reader inside `main_loop` or its direct child
- This narrows the candidate match-active flag set

### 2. Investigate the two specific Pool C candidates first
- `DAT_710593a534` (integer): trace `0x7103741bb4` and `0x71037472d0` — what function returns are stored here? What's the value range? Is `3` ever in the range?
- `DAT_710593a540..0x710593a5a0` (byte cluster): which bytes get written, with what values, by which functions? Look for a state-machine pattern (function that switches on input and stores phase markers).

### 3. Cross-reference with main_loop
For each candidate match-active flag found:
- Is it READ from `main_loop` (or its direct child)?
- If yes, what `cmp #N; b.eq/b.ne` follows the read?
- Does the branch lead to anything that walks fighters / dispatches per-frame work?

### 4. Trace the writer
For the most promising flag candidate, find the writer's function and identify:
- Is it a state machine? Document state values
- Is it called from a "match start" path? (e.g. CSS → load → match init)
- Is it called from a "match end" path?

This is the **rollback arm/disarm signal**.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool B — match-active flag hunt (next-pass)

### 0x710593axxx block audit
| Address | Writer count (non-zero) | Read by main_loop? | Best guess |
|---------|------------------------|---------------------|-----------|
| 0x710593a530 | 0 | YES (dead branch) | dead code |
| 0x710593a534 | N | YES/NO | ... |
| ... | ... | ... | ... |

### Most promising candidate
- Address: 0x710593aXXX
- Writers: [list of functions + values]
- Readers (main_loop chain): [...]
- State machine values: 0=idle, 1=..., N=match active
- Verdict: [FOUND match-active flag / WEAK CANDIDATE / NO MATCH]

### Rollback arm signal
- Function: setMatchActive_XXXX at 0xXXXXX
- Hook point: [address]
- State transition: idle → ... → active
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable
- The binary scanner is your friend — write it inline if needed (Pool C suggested productizing it as `tools/xref_bin_scan.py` but that's pool C's job, not yours)

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
