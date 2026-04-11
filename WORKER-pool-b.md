# Worker: pool-b

## Model: Opus

## Task: ROLLBACK Round 6 — decompile add_task / remove_task helpers (FUN_7103559340, FUN_7103559220)

## Priority: HIGHEST — directly identifies the task base class and registration API

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Round 5 found the actual per-frame loop is a task-system pump iterating `[*DAT_7105332fe8 + 0x20..+0x28]`. Two small helpers were identified as task add/remove candidates:

- `FUN_7103559340` (probable `add_task()`) — caller `0x7103559360` reads `DAT_7105332fe8`
- `FUN_7103559220` (probable `remove_task()`) — caller `0x7103559240` reads `DAT_7105332fe8`

Both are small. Decomping them reveals:
1. The task base class shape (from the argument vtable)
2. The registration API (so we can xref it to find every task registration in the binary — that's the list of all per-frame ticks)

## What To Do

### 1. Decompile FUN_7103559340 (add_task candidate)
- `mcp__ghidra__decompile_function_by_address 0x7103559340`
- Document its parameters
- The `Task*` argument's vtable layout (look for any `task->vt[N]` or `param->vt[N]` calls)
- Where in `DAT_7105332fe8`'s container the new task gets inserted

### 2. Decompile FUN_7103559220 (remove_task candidate)
- Same approach
- Confirm symmetry with add_task
- Document any cleanup the remove path does (destructor calls, refcount, etc.)

### 3. Identify the task base class
- The vtable addresses revealed by the add/remove paths
- Use `mcp__ghidra__get_xrefs_to <vtable_address>` to find every constructor that uses this vtable
- Each constructor is a concrete task type
- **One of those task types IS the sim tick** (or contains it)

### 4. Enumerate all add_task callers
This is the goldmine query:
```
mcp__ghidra__get_function_xrefs FUN_7103559340
```
- Every caller is a function that registers a task to the per-frame pump
- Each caller's identity tells you what subsystem registers a tick
- **The caller that registers the sim tick is the sim system's init function**

### 5. For each add_task caller, classify the task being registered
- Look at the function the caller is in
- What subsystem does it belong to? (FighterManager? BattleObjectWorld? Stage? Camera? UI?)
- The argument being added — is it a known type or a new one?
- If you find one whose class touches `BattleObjectModuleAccessor`, `FighterManager`, or other sim-shaped state — **that's the sim tick caller**

### 6. Cross-reference with Pool A (if they finish first)
Pool A is decoding `FUN_71035a4130` (the task-list initializer). If they identify any tasks registered directly by the initializer, cross-reference with your add_task caller list.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool B — Round 6: task add/remove helpers + caller enumeration

### Task base class
- Vtable: 0xXXXXX
- Methods inferred from add/remove + frame-loop dispatch:
  - vt[0x28]: tick (per-frame method called by main_loop)
  - vt[0x20]: alt tick path
  - vt[N]: ...

### add_task signature
- Function: FUN_7103559340 (renamed: addTask)
- Signature: (TaskList* this, Task* task)
- Container insertion: vector push_back / linked list / other

### remove_task signature
- Function: FUN_7103559220 (renamed: removeTask)
- Signature: ...

### Every add_task caller (the task registration site list)
| Caller fn | Task subsystem | Sim-shaped? |
|-----------|----------------|-------------|
| FUN_XXXX  | ...            | YES/NO      |

### VERDICT
[FOUND SIM TICK — task X registered by FUN_YYYY which belongs to subsystem Z]
[OR: Task system mapped but no sim-shaped task registrant found yet — next step: walk vt[0x28] of each registered task]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
