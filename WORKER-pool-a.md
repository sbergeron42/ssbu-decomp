# Worker: pool-a

## Model: Opus

## Task: ROLLBACK Round 6 — analyze FUN_71035a4130 (the task-list initializer)

## Priority: HIGHEST — directly identifies the task-list singleton type

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Round 5 found:

- The actual per-frame loop in `main_loop` runs from `0x7103747504` to `0x710374cbc0` (everything before that is one-shot boot)
- The loop is a **task-system pump**: iterates a `vector<Task*>` at `[*DAT_7105332fe8 + 0x20..+0x28]`, dispatches `task->vt[0x28]` (or alt `vt[0x20]`) on each, loops back
- **The sim tick is one of the registered tasks**
- `FUN_71035a4130` is the sole writer of `DAT_7105332fe8` (and also of `DAT_7105335e10` from Round 4) — it's a top-level subsystem-cluster initializer

**The orchestrator manually extracted `FUN_71035a4130` to disk** (it timed out on Ghidra MCP at 5,861 lines / 204 KB). The extracted decomp is at:

- **`data/ghidra_cache/FUN_71035a4130.txt`** — read this with the `Read` tool, do NOT call MCP

## What To Do

### 1. Read the cached decomp
Read `data/ghidra_cache/FUN_71035a4130.txt` and find the section that:
- Allocates a struct
- Stores the struct pointer to `DAT_7105332fe8` (the task-list singleton)
- Initializes its fields (especially the vector at `+0x20/+0x28`, the mutex at `+0x38`, and the per-entry byte flag array at `+0x1f8`)

### 2. Identify the task-list class
- The store will be `STR Xn, [adrp+ldr resolving to 0x7105332fe8]`
- Right before that store, find the constructor call
- The constructor's first instruction stores a vtable pointer — that's the task system's vtable
- Look up the vtable address; if it has a class name in `.dynsym` or via xref to a known string, document it
- Likely candidates: `pead::TaskSystem`, `cross2app::TaskManager`, `app::FrameTaskList`

### 3. Identify the task-list element type
The frame-loop dispatches `task->vt[0x28]` on each element. We need to know what concrete type a "task" is:
- Find the `add_task` / `register` helpers (Round 5 noted `FUN_7103559340` and `FUN_7103559220` as candidates)
- These likely take a `Task*` argument and append to the vector
- The argument's vtable IS the task base class

### 4. Document the registered tasks (if visible in this function)
If `FUN_71035a4130` itself registers any initial tasks (constructors usually do), document each:
- Task constructor address
- Task class name (if recoverable)
- vt[0x28] target — what does this task DO when ticked?
- Is any of them sim-shaped? (touches `BattleObjectModuleAccessor`, `FighterManager`, etc.)

### 5. List of all `DAT_7105332fe8` writers we should care about
Use `tools/xref_bin_scan.py` to confirm the writer set. Round 5 found only one (this function) — verify there are no others.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts on any OTHER address you investigate (not the cached one), apply the standard rule.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool A — Round 6: FUN_71035a4130 task-list initializer

### Task-list singleton type
- Address: DAT_7105332fe8
- Class: [name]
- Constructor: 0xXXXXX
- Vtable: 0xXXXXX

### Task-list layout
| Offset | Field | Notes |
|--------|-------|-------|
| +0x00  | ?     | ...   |
| +0x20  | begin | vector start |
| +0x28  | end   | vector end |
| +0x38  | mutex | per Round 5 |
| +0x1f8 | flag array | per Round 5 |

### Task base class
- Vtable address: 0xXXXXX
- vt[0x28]: per-frame tick method
- vt[0x20]: alt path (purpose?)

### Initial tasks registered (if any)
| Task class | vt[0x28] target | Sim-shaped? |
|------------|-----------------|-------------|
| ...        | ...             | ...         |

### VERDICT
[FOUND SIM TICK at FUN_XXXX (registered as task by FUN_71035a4130)]
[OR: Task system identified, sim tick is a task registered by SOME OTHER function — next step: enumerate all add_task callers]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
