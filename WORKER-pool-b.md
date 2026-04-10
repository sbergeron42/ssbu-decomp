# Worker: pool-b

## Model: Opus

## Task: ROLLBACK SIM TICK HUNT — decompile 4 unknown phase-6/7 children of main_loop (Item 1)

## Priority: HIGHEST — sim tick hunt, blocks rollback resimulation

## Context
You wrote `docs/rollback/main_loop.md` in the previous pass. The "sim tick is in here" hypothesis now points by elimination at four unknown sub-calls of main_loop. Read your own main_loop.md first for the context.

Pools A and C are doing the same hunt via different angles in parallel — whoever finds it first ends the hunt.

## What To Decompile

The four candidates (in elimination priority):

1. **`FUN_7103593c40`** (792 B, phase 5)
2. **`FUN_71035c13d0`** (1,048 B, after scene state machine)
3. **`FUN_71036186d0`** (1,188 B)
4. **`FUN_7103619080`** (432 B)

## What To Look For

For each function, classify:
- **Does it iterate fighters?** (loop over `FighterManager.entries[]`, or walk a list of `BattleObject*`)
- **Does it touch BattleObject vtable slots?** (calls through `_vt[N]` on `BattleObject*` or `BattleObjectModuleAccessor*`)
- **Does it advance any per-match state?** (writes to fighter info, status, motion frame, etc.)
- **Are the arguments scene objects?** (look at the parameters — if param_1 has scene-like fields, this could be the bridge)

**Any one positive answer ends the hunt.**

## Confirmed dead ends — DO NOT re-investigate
From the rollback team's notes:
- `FUN_710356d7a0` (particle dt)
- `FUN_710355b540` (resource streaming)
- `FUN_71035763c0` (animation sampler)
- `FUN_71036f2c00` / `FUN_71036f2d40` (audio state machines)
- `FUN_7101344cf0` (Randomizer singleton ctor)
- `FUN_710386fc30` (= `nu::GraphicsModule::BeginFrame`)

## Output

Append to `docs/rollback/sim_tick_hunt.md` (create if not exists). Pools A and C are also writing here:

```markdown
## Pool B — phase-6/7 child decomps

### FUN_7103593c40 (792 B, phase 5)
- Iterates fighters: YES/NO
- Touches BattleObject vtable: YES/NO
- Per-match state mutation: YES/NO
- Verdict: [FOUND SIM TICK / DEAD END / NEEDS DEEPER LOOK]
- Notes: ...

### FUN_71035c13d0 (1048 B)
... etc

### Final verdict
[FOUND at FUN_XXXX / ALL FOUR DEAD] — handoff notes
```

If one is positive, document the call chain inside it that constitutes the actual fighter iteration. Don't decompile to source files yet — research first.

## Reference Material
- `docs/rollback/main_loop.md` (your own previous work)
- `data/ghidra_cache/main_loop_7103747270.txt` (use `Read` tool, do NOT call MCP on this address)
- `data/ghidra_cache/FUN_7101344cf0.txt` (already classified as Randomizer ctor, dead end)

## Quality Rules
- Documentation is the primary deliverable
- NO `FUN_` names in committed src/ (research docs can reference them)
- Cast density under 10%

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
