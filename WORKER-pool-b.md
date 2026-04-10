# Worker: pool-b

## Model: Opus

## Task: ROLLBACK CRITICAL PATH — main_loop dispatch skeleton @ 0x7103747270

## Priority: HIGH — needed for rollback resimulation

## Context
A rollback netcode fork needs to identify the "advance one simulation tick" call inside the main game loop, so it can call it N times to resim after misprediction. We need the **dispatch skeleton**, not the bodies.

## IMPORTANT: Pre-cached decomps
**main_loop has already been decompiled to disk** — Ghidra MCP times out on it. Read this file instead:
- **`data/ghidra_cache/main_loop_7103747270.txt`** (3947 lines, full Ghidra decomp)

A second related giant function is also cached:
- **`data/ghidra_cache/FUN_7101344cf0.txt`** (5891 lines — likely per-frame fighter update, called from main_loop)

**Use the `Read` tool on these files. Do NOT call `mcp__ghidra__decompile_function_by_address` on `0x7103747270` or `0x7101344cf0` — they will time out.**

For sub-calls inside main_loop that you want to inspect, you CAN use Ghidra MCP — they should be smaller and won't time out.

## What To Find

### 1. The simulation tick sub-call
- Read `data/ghidra_cache/main_loop_7103747270.txt`
- Identify the sub-call that advances simulation by one tick
- This is what rollback would call N times during resim

### 2. Simulation vs presentation classification
- Walk through every sub-call in main_loop
- Classify each as **simulation** (game state mutation) or **presentation** (render/audio/UI/haptics)
- For unfamiliar sub-calls, decompile them via MCP (they should be smaller than main_loop itself)

### 3. Frame counter
- Find the global frame counter increment site
- Document the address of the counter and where it's incremented

### 4. Relationship to FUN_7101344cf0
- The 65KB FUN_7101344cf0 is probably called by main_loop (or by something main_loop calls)
- Check `main_loop_7103747270.txt` for any reference to `0x7101344cf0` or `FUN_7101344cf0`
- If main_loop → FUN_7101344cf0 → tick advance, document the chain

## Output

Create `docs/rollback/main_loop.md` with:
1. **Dispatch skeleton**: pseudo-code of the top-level loop showing every sub-call in order
2. **Sim/present table**: `address | function | category | notes`
3. **Tick advance call**: specific call(s) that constitute "advance one frame"
4. **Frame counter**: address + increment site

## Quality Rules
- Documentation is the primary deliverable
- The cached files are Ghidra paste — reference material, NOT to commit as src/
- If you DO decomp parts into committed src/, follow standard rules (no FUN_, no Ghidra vars, no raw casts)

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
