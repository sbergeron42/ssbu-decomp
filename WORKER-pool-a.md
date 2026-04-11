# Worker: pool-a

## Model: Opus

## Task: ROLLBACK Round 7 — analyze FUN_7101344cf0 (task_tree_add gatekeeper)

## Priority: HIGHEST — names the sim task class definitively

## Context
Read `docs/rollback/sim_tick_hunt.md` first. **Round 6 was the architectural breakthrough.** Pool C found:

- main_loop is a fiber-scheduled task pump, NOT the sim loop
- The actual sim runs as a task on a worker thread
- Tasks are registered via `FUN_7101344cf0` (the sole non-init writer of `DAT_7105332120`, the task tree root)
- The per-tick method is `vt[2]` (byte offset +0x10), invoked by the generic runner `FUN_7103548240` on a worker thread behind `nn::os::SignalLightEvent`
- **Only ~5 callers register tasks** through `FUN_7101344cf0` — one of them registers the sim tick

**The rollback team identified `FUN_7101344cf0` as the gatekeeper. We already have it cached on disk** (it's the same 65 KB function we identified at the very start of this hunt and the orchestrator extracted earlier):

- **`data/ghidra_cache/FUN_7101344cf0.txt`** — 5,891 lines, full Ghidra decomp. Read with `Read` tool, do NOT call MCP.

## What To Do

### 1. Read FUN_7101344cf0 from cache
- Open `data/ghidra_cache/FUN_7101344cf0.txt` with `Read`
- It's 5,891 lines — read it in chunks if needed
- Pool C identified it as `task_tree_add` based on xrefs (sole writer of `DAT_7105332120`, called by 5 distinct sites)
- **Confirm or refute** that classification by reading the function body

### 2. Find the linked-list insertion logic
- `DAT_7105332120` is a singly-linked list head
- Find the insertion: `LDR Xn, [DAT_7105332120]; STR new_node, [DAT_7105332120]; STR Xn, [new_node + 0x48]`
- Document the parameters: what's the new node? Where does its data come from?
- Specifically: is the function `task_tree_add(Task* task)` or `task_tree_add(SomeOtherType* obj)`?

### 3. Find the vtable enforcement (if any)
- Does the function check the new node's vtable?
- Does it call any method on the new node before/after insertion?
- The vtable methods called here narrow down the abstract Task base class

### 4. Look for state-machine logic
This function is 5,891 lines — much bigger than a simple linked-list add. It probably does much more than just registration:
- State transitions on the task being added
- Initialization of subsystems
- Maybe entire fighter/match setup
- Look for patterns that touch `BattleObjectModuleAccessor`, `FighterManager`, `BattleObjectWorld`, RNG state
- **If FUN_7101344cf0 itself touches sim state, the caller chain is shorter than we thought**

### 5. Cross-reference with the 5 callers
The 5 callers Pool C found are:
- `FUN_71014b2a40` — primary, large init (constructs a 0x50 ModuleSet container)
- `FUN_7101523b60` — secondary registrar (Pool B is investigating this)
- `FUN_710151a5d0` — inline registrar (Pool C is investigating this)
- 3 vtable slots: `0x7105060680`, `0x710506b0f8`, `0x710506c5b8`

For each caller, check what type of object is being passed in. Cross-reference with the cached file you're reading.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts on any address:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool A — Round 7: FUN_7101344cf0 task_tree_add gatekeeper

### Function identity
- Real name: [task_tree_add / something else]
- Parameters: [list]
- Body summary: [what it actually does in 5,891 lines]

### Linked list insertion
- Insertion site: line N of cached file
- Logic: [push_front / push_back / sorted insert / other]
- Vtable enforcement: [yes/no — what's checked]

### Touched state
- Touches RNG? [yes/no]
- Touches FighterManager? [yes/no]
- Touches BattleObjectWorld? [yes/no]
- Touches BattleObjectModuleAccessor? [yes/no]

### Caller objects
| Caller | Object type | Vtable | Sim-shaped? |
|--------|-------------|--------|-------------|
| FUN_71014b2a40 | ... | ... | ... |
| ...    | ...         | ...    | ...         |

### VERDICT
[FOUND SIM TASK at vtable 0xXXXX — registered by FUN_YYYY]
[OR: FUN_7101344cf0 is task_tree_add but the sim task is registered by a caller we haven't decomped yet — recommend Round 8 with target X]
[OR: STATIC ANALYSIS EXHAUSTED — recommend GDB watchpoint approach]
```

If you find the sim task, write a TL;DR at the top so the rollback team can find it instantly.

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
