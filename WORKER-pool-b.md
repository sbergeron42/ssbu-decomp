# Worker: pool-b

## Model: Opus

## Task: ROLLBACK Round 7 — decomp the 5 callers of FUN_7101344cf0 (task_tree_add)

## Priority: HIGHEST — directly identifies the registered task vtables

## Context
Read `docs/rollback/sim_tick_hunt.md` first. **Round 6 architectural breakthrough**: main_loop is a fiber-scheduled task pump, sim runs as a task on a worker thread. Tasks are registered through `FUN_7101344cf0`. The 5 callers are the entire task registration set. **One of them registers the sim tick.**

Pool A is reading the cached `FUN_7101344cf0.txt` to understand the gatekeeper. Pool C is investigating one of the callers + the 3 vtable-slot xrefs. **Your job: decomp the other two callers, identify the task vtables they register, and look at vt[2].**

## Targets

### `FUN_71014b2a40` (primary caller)
- Pool C noted this is "a large init routine that constructs a 0x50 ModuleSet container with `PTR_FUN_7105069db0` and 4 shared_ptr slots"
- It's the **biggest** caller — most likely to be registering multiple tasks
- Decompile and find every call to `FUN_7101344cf0` inside it
- For each call, document the object being registered

### `FUN_7101523b60` (secondary registrar)
- Smaller than 71014b2a40
- Decompile and find what task it registers
- Document the object's vtable

## What To Do

### 1. Decompile `FUN_71014b2a40`
- `mcp__ghidra__decompile_function_by_address 0x71014b2a40`
- Find every `FUN_7101344cf0` call inside it
- For each call, look at the argument: what's being registered?
- The argument's vtable IS a candidate sim task

### 2. Decompile `FUN_7101523b60`
- Same approach, smaller function

### 3. For each registered object, find its vtable's vt[2]
- `vtable[+0x10]` is the per-frame tick (Pool C confirmed this in Round 6)
- Decompile vt[2] for each candidate
- Look for sim-shaped patterns:
  - Iterating fighters via `FighterManager`
  - Touching `BattleObjectModuleAccessor` modules
  - Reading/writing RNG (`DAT_71052c25b0` area)
  - Calling `app::sv_math::rand` (`0x7102275320`)
  - Calling FighterStatus vtable methods (`0x7104f7f2e8`)
- **The first vt[2] that hits ANY sim-state IS the sim tick.**

### 4. Document the sim task
If you find it, document:
- The registering function (`FUN_71014b2a40` or `FUN_7101523b60`)
- The task object's vtable address
- The class name (if `.dynsym`-confirmed)
- The vt[2] target address (the sim function)
- A summary of what vt[2] does (what state it touches)

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

`FUN_71014b2a40` is large — if it times out, log it and move to `FUN_7101523b60`.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool B — Round 7: task_tree_add caller decomps

### FUN_71014b2a40 (primary registrar)
- Registers N tasks
- Task vtables: [list]
- vt[2] of each:
  - vtable 0xXXXXX vt[2] = FUN_YYYY — does Z (sim-shaped: Y/N)
  - ...

### FUN_7101523b60 (secondary registrar)
- Registers N tasks
- Task vtables: [list]
- vt[2] of each: ...

### VERDICT
[FOUND SIM TASK at vtable 0xXXXX, registered by FUN_YYYY, vt[2] = FUN_ZZZZ touches A/B/C]
[OR: All 5 callers decomped, none register a sim-shaped task — sim might be registered dynamically not statically]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
