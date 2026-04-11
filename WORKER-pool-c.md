# Worker: pool-c

## Model: Opus

## Task: ROLLBACK Round 7 — investigate FUN_710151a5d0 + the 3 vtable-slot xrefs to FUN_7101344cf0

## Priority: HIGHEST — vtable slots reveal the abstract Task base class

## Context
Read `docs/rollback/sim_tick_hunt.md` first. **Round 6 architectural breakthrough**: main_loop is a fiber-scheduled task pump, sim runs as a task on a worker thread. Tasks register through `FUN_7101344cf0` (the gatekeeper).

You found in Round 6 that there are 5 callers of `FUN_7101344cf0`:
- 2 normal function callers (Pool B is decomping these)
- 1 inline registrar `FUN_710151a5d0`
- **3 vtable slots: `0x7105060680`, `0x710506b0f8`, `0x710506c5b8`**

The 3 vtable slots are the most interesting — **they mean some base class has a method that calls `task_tree_add` from inside a virtual method**. That base class is a Task framework class (probably `pead::Task` or similar). Identifying it would name the abstract type the entire task system uses.

## What To Do

### 1. Decompile FUN_710151a5d0 (inline registrar)
- `mcp__ghidra__decompile_function_by_address 0x710151a5d0`
- Document parameters and what task it registers
- Identify the task's vtable

### 2. For each of the 3 vtable slots, find the owning vtable
- The slot addresses are `0x7105060680`, `0x710506b0f8`, `0x710506c5b8`
- Each is a single function pointer entry inside some vtable
- Use `tools/xref_bin_scan.py` or `mcp__ghidra__get_xrefs_to` on each address
- Find the **start** of each vtable (look backward for an aligned `.rodata` boundary)
- Once you have the vtable address, use `mcp__ghidra__get_xrefs_to <vtable_addr>` to find the **constructor** that uses it
- The constructor names the class

### 3. Identify the abstract Task base class
- All 3 vtable slots probably belong to **the same vtable** (the abstract Task base class)
- Or they're 3 sibling derived classes that share an interface
- Either way, the parent class is a candidate for the task base type
- Look for FNV-hashed string constants in the constructor that might encode the class name

### 4. For each task vtable found, decompile vt[2]
- `vtable[+0x10]` is the per-frame tick
- Decompile vt[2] for each candidate
- Sim-shaped patterns:
  - Iterating fighters via `FighterManager`
  - Touching `BattleObjectModuleAccessor` modules
  - Reading/writing RNG (`DAT_71052c25b0` area)
  - Calling `app::sv_math::rand` (`0x7102275320`)
- **Stop and report immediately if you find one that hits sim state.**

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool C — Round 7: vtable slot investigation + FUN_710151a5d0

### FUN_710151a5d0
- Registers task: [vtable 0xXXXX]
- Task class: [name or unknown]

### Vtable slots pointing at FUN_7101344cf0
| Slot address | Owning vtable | Class | Method offset within vtable |
|--------------|---------------|-------|----------------------------|
| 0x7105060680 | 0xXXXX | ... | +0xNN |
| 0x710506b0f8 | 0xXXXX | ... | +0xNN |
| 0x710506c5b8 | 0xXXXX | ... | +0xNN |

### Abstract Task base class
- Vtable: 0xXXXX
- Class: [name or "abstract Task — no symbol"]
- Method that calls task_tree_add: [purpose]

### vt[2] of each candidate task
| Vtable | vt[2] target | Sim-shaped? | Notes |
|--------|--------------|-------------|-------|
| 0xXXXX | FUN_YYYY | YES/NO | ... |

### VERDICT
[FOUND SIM TASK at vtable 0xXXXX]
[OR: vtables identified but none sim-shaped]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
