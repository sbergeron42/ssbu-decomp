# Worker: pool-c

## Model: Opus

## Task: ROLLBACK Round 6 — walk the frame-loop body and classify each per-task vt[0x28] dispatch

## Priority: HIGHEST — directly identifies which task(s) the sim tick lives in

## Context
Read `docs/rollback/sim_tick_hunt.md` first. You found the actual frame loop in Round 5: `0x7103747504..0x710374cbc0` inside main_loop. The loop iterates a task list and dispatches `task->vt[0x28]` (or alt `vt[0x20]`) on each.

Pool A is decoding the task-list initializer. Pool B is decoding the add/remove helpers and enumerating registrants. **Your job: walk the actual frame-loop body and identify the concrete tasks dispatched per-frame**, by tracing each per-task BL through to a concrete vtable.

## What To Do

### 1. Re-read the frame-loop body
- Use `Read` on `data/ghidra_cache/main_loop_7103747270.txt` and find the section corresponding to `0x7103747504..0x710374cbc0`
- This is ~22 KB of body — find every BL inside the loop
- Pay special attention to the indirect dispatches (`blr xN` after vtable loads), and the `0x710374cb68 task->vt[0x28]` dispatch you identified in Round 5

### 2. Enumerate the indirect dispatches inside the loop
For each `blr` inside the frame loop:
- What's loaded into the called register?
- Is it a vtable slot off a task pointer? Off a different singleton?
- Document the dispatch shape

### 3. Trace the task vtable concretely
At the loop tail (`0x710374cb68`), `task->vt[0x28]` is called. The task is `*(start)` where `start = task_list[0x20]`. Each loop iteration advances `start += 8` (single-pointer step), so the vector elements are `Task*` pointers.

To find the concrete task vtables:
- Use `tools/xref_bin_scan.py` to find every store of any value into the offset range `[*DAT_7105332fe8 + 0x20..+0x28]`
- Each writer is an `add_task` callsite
- Each writer's source value (the `Task*` being stored) traces back to a constructor with a vtable
- That vtable is a concrete task type

### 4. For each concrete task vtable, decompile vt[0x28]
- Each vt[0x28] is a per-frame tick method
- Look for sim-shaped patterns:
  - Iterating `FighterManager` entries
  - Touching `BattleObjectModuleAccessor` vtable slots `+0x38..+0x188`
  - Calling `FighterStatus::*` (vtable at `0x7104f7f2e8` from Pool A's earlier find)
  - Reading/writing RNG state (`DAT_71052c25b0` area)
  - Touching `FighterAI` state
- The first vt[0x28] that hits ANY of these IS the sim tick

### 5. Cross-validate
- If Pool A or Pool B finished first, read their committed findings
- Pool A names the task-list type and possibly initial registered tasks
- Pool B names every add_task caller
- Cross-reference: which subsystems' add_task calls match the per-task vtables you found?

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool C — Round 6: frame-loop body walk + per-task classification

### Indirect dispatches inside frame loop body (0x7103747504..0x710374cbc0)
| BL site | Target | Source | Notes |
|---------|--------|--------|-------|
| 0xXXXX  | task->vt[0x28] | task list | per-task tick |
| 0xXXXX  | other->vt[N]   | ...      | ...           |

### Concrete task vtables
| Vtable | Class | vt[0x28] target | Sim-shaped? |
|--------|-------|------------------|-------------|
| 0xXXXX | ...   | 0xXXXX          | YES/NO      |

### Sim tick verdict
[FOUND at task vtable 0xXXXX, vt[0x28] = FUN_YYYY, registered by subsystem Z]
[OR: Multiple sim-shaped tasks — list candidates]
```

If you find the sim tick, write a TL;DR at the top of the section so the rollback team can read it instantly.

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
