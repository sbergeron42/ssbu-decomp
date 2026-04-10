# Worker: pool-c

## Model: Opus

## Task: ROLLBACK SIM TICK HUNT — pead::Delegate framework mapping (Item 3)

## Priority: HIGHEST — sim tick hunt, blocks rollback resimulation

## Context
You wrote `docs/rollback/memory_map.md` in the previous pass. Pool B's `main_loop.md` § 6e flagged that **rollback resim probably needs to plug into `pead::Delegate` rather than call a sim advance function directly**. This task maps the pead delegate dispatch framework so we can either:
1. Find the sim tick posted as a delegate (would explain why it doesn't appear as a direct BL in main_loop), OR
2. Identify the delegate runner so rollback can intercept at that level

Pools A and B are doing the same hunt via different angles in parallel — whoever finds it first ends the hunt.

## What To Find

### 1. The pead::Delegate dispatch entry point
- Search Ghidra for `pead::Delegate`, `pead::Thread`, `runDelegates`, `processDelegates`
- Use `mcp__ghidra__search_functions_by_name pead`
- Look for `pead::Delegate::operator()` or equivalent (a function that calls a stored function pointer)
- Look for `pead::Thread::runDelegates()` or equivalent (a loop that drains a queue of delegates)

### 2. Posting sites — who calls `pead::MainThread::postDelegate(...)` (or equivalent)?
- Find the `pead::MainThread` singleton
- Find every callsite that posts a delegate to it
- **Critical: enumerate every posting site reachable from inside `main_loop`'s call chain**
- Cross-reference with `data/ghidra_cache/main_loop_7103747270.txt`

### 3. Determine if the sim tick is posted as a delegate
- If yes, document:
  - The function being posted (this IS the sim tick entry point)
  - Where it's posted from (which child of main_loop)
  - When it's posted (every frame? once at start?)
- If no, document the delegates that ARE posted (rollback may still need to intercept here)

## Output

Append to `docs/rollback/sim_tick_hunt.md` (create if not exists). Pools A and B are also writing here:

```markdown
## Pool C — pead::Delegate framework approach

### Delegate dispatch
- pead::Delegate::operator(): 0xXXXXX
- pead::Thread::runDelegates equivalent: 0xXXXXX
- MainThread singleton: DAT_71XXXXXXXX

### Delegates posted from main_loop's call chain
| Posted from (caller in main_loop chain) | Delegate target | Frequency | Purpose |
|---|---|---|---|
| FUN_XXXX | FUN_XXXX | per-frame | ... |

### Verdict
[FOUND SIM TICK as delegate / SIM TICK NOT A DELEGATE / DEAD END]
```

If one of the posted delegates iterates fighters, that's the sim tick. Document the call chain.

## Reference Material
- `docs/rollback/main_loop.md` (pool B's previous work — read this first)
- `docs/rollback/memory_map.md` (your own previous work)
- `data/ghidra_cache/main_loop_7103747270.txt` (use `Read` tool, do NOT call MCP on this address)

## Quality Rules
- Documentation is the primary deliverable
- NO `FUN_` names in committed src/
- Cast density under 10%

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
