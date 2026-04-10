# Worker: pool-b

## Model: Opus

## Task: ROLLBACK CRITICAL PATH — main_loop dispatch skeleton @ 0x7103747270

## Priority: HIGH — needed for rollback resimulation

## Context
A rollback netcode fork needs to identify the "advance one simulation tick" call inside the main game loop, so it can call it N times to resim after misprediction. The function is 24KB — too big for full decomp, but we only need the **dispatch skeleton**, not the bodies.

## What To Find

### 1. The simulation tick sub-call
- Decompile the top-level dispatcher at `0x7103747270`
- Identify the sub-call that advances simulation by one tick
- This is what rollback would call N times during resimulation

### 2. Simulation vs presentation classification
- Walk through every sub-call in main_loop
- Classify each as **simulation** (game state mutation) or **presentation** (render/audio/UI/haptics)
- Rollback skips presentation during resim — needs to know which is which

### 3. Frame counter
- Find the global frame counter increment site (if there is one)
- Document the address of the counter and where it's incremented

## Output

Create `docs/rollback/main_loop.md` with:
1. **Dispatch skeleton**: pseudo-code of the top-level loop showing every sub-call in order
2. **Sim/present table**: `address | function (name or FUN_) | category | notes`
3. **Tick advance call**: the specific call(s) that constitute "advance one frame"
4. **Frame counter**: address + increment site if found

You don't need to decomp the bodies of sub-calls — just identify them by name/address and what they do at a high level.

## Approach
1. `mcp__ghidra__decompile_function_by_address` on `0x7103747270` — read the top-level
2. For each sub-call, look up its name with `mcp__ghidra__get_function_by_address` and a quick decompile of just the entry to understand its purpose
3. Cross-reference with `gameplay_functions.cpp` for related context
4. The 24KB size suggests heavy inlining — work top-down, you don't need to follow every branch

## Quality Rules
- Documentation is the primary deliverable, not new C++ code
- If you DO decomp parts of main_loop into a new src/ file, follow the standard rules
- NO `FUN_` names in any committed code
- NO Ghidra vars

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
