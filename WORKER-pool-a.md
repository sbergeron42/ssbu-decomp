# Worker: pool-a

## Model: Opus

## Task: ROLLBACK SIM TICK HUNT — FighterManager vtable xref walk (Item 2)

## Priority: HIGHEST — sim tick hunt, blocks rollback resimulation

## Context
Pool B's `docs/rollback/main_loop.md` confirmed `main_loop` @ `0x7103747270` is the **presentation loop**, not the sim dispatcher. The actual "advance one fighter frame" call lives elsewhere — reachable from main_loop's call chain but not on any direct child path investigated yet.

You're hunting it via the **bottom-up FighterManager vtable approach**. Pools B and C are doing the same hunt via different angles in parallel — whoever finds it first ends the hunt.

## Background — what we already know
- `Singleton<FighterManager>::instance_` @ `0x71052b84f8`
- Every field-reader of this singleton pulls **single fields** (hp, entry_id, pos), never iterates the array
- The sim dispatcher therefore reaches fighters via a **cached pointer stored in a scene object**, not via the singleton
- Read `docs/rollback/main_loop.md` first — especially the "open questions" section — for full context
- Pool C confirmed `BattleObjectWorld` singleton @ `0x71052b7558` (was misdocumented as `DAT_71052b7ef8` which is actually BossManager)
- Pool C also confirmed `BattleObjectManager` pool-header array @ `DAT_71052b7548`

## What To Do

### 1. Find the FighterManager vtable
- Use `mcp__ghidra__decompile_function_by_address` on the FighterManager constructor (find via `mcp__ghidra__search_functions_by_name FighterManager`)
- The vtable is the first store in the constructor (`*this = &PTR_LAB_XXX`)
- Document the vtable address

### 2. Xref vtable slots
- Use `mcp__ghidra__get_xrefs_to` on the vtable address
- Look for slots shaped like `update`, `exec`, `process`, `advance`, `tick`, `frame`
- For each interesting slot, follow the function pointer to find the actual implementation

### 3. Walk callers bottom-up
- For each tick-shaped vtable slot, find all callers via `mcp__ghidra__get_function_xrefs`
- Walk up the call chain
- **Goal**: find a caller that is reachable from `main_loop` (cross-reference with `data/ghidra_cache/main_loop_7103747270.txt` if needed)
- That caller IS the bridge between the scene object and the per-fighter tick

### 4. Same sweep for adjacent vtables
- `BattleObjectWorldManager` vtable
- `BattleObject` vtable (the `_vt[0]` we already identified — what other slots exist?)
- Whichever is called per-frame from a main_loop descendant is your target

## Output

Append to `docs/rollback/sim_tick_hunt.md` (create if not exists). Other pools (B, C) are also writing to this file — use clearly labeled sections:

```markdown
## Pool A — FighterManager vtable approach

### FighterManager vtable
- Address: 0xXXXXX
- Constructor: 0xXXXXX (FUN_XXXX)
- Tick-shaped slots:
  - +0xNN: name (purpose)

### Caller chain to main_loop
1. vtable[0xNN] called by FUN_XXXX
2. FUN_XXXX called by FUN_XXXX
3. ... reaches main_loop at FUN_XXXX (which BL in main_loop?)

### Verdict
[FOUND / NOT FOUND / DEAD END] — explanation
```

If you find the sim tick, DO NOT decompile it yet — just document the address and how it's reached. The rollback team needs the entry point first; full decomp comes later.

## Quality Rules
- Documentation is the primary deliverable
- The cached `data/ghidra_cache/main_loop_7103747270.txt` and `FUN_7101344cf0.txt` are reference material — read with `Read` tool, do not call MCP
- NO `FUN_` names, NO Ghidra vars in any committed code
- Cast density under 10%

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
