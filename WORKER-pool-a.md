# Worker: pool-a

## Model: Opus

## Task: ROLLBACK Round 5 — bottom-up RNG-driven sim tick walk

## Priority: HIGHEST — methodologically different approach after 4 rounds of dead ends

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Round 4 retired all four phase-6/7 candidates AND demolished `DAT_710593a510` as a match-active gate. Top-down "find a dispatcher in main_loop" has failed 4 rounds in a row.

**New approach: bottom-up from RNG.** We KNOW (from `docs/rollback/rng.md`) that `app::sv_math::rand @ 0x7102275320` is the deterministic gameplay RNG. **The sim tick MUST contain code that calls rand** (or one of its variants `randf @ 0x71022756c0`, the namespaced wrappers `app::random::*`). If we work upward from the rand callsites and find a chain that reaches `main_loop`, the deepest function in that chain that reaches main_loop IS the sim tick (or its immediate parent).

Rand was inlined aggressively (rng.md notes "the compiler aggressively inlined this function at every C++ call site"), but the **non-inlined dispatch wrappers** still exist:
- `FUN_710213a360` — Lua-binding wrapper for `rand`
- `FUN_710213a9f4` — Lua-binding wrapper for `randf`
- The 9 channel-specific accessors at `app::random::get_float`, `range_int`, etc. (see rng.md table)

## What To Do

### 1. Find every caller of every rand variant
For each of these addresses, use `mcp__ghidra__get_function_xrefs`:
- `0x7102275320` (`app::sv_math::rand`)
- `0x71022756c0` (`app::sv_math::randf`)
- `0x71015cf234` (`app::random::get_float`)
- `0x71015cf294` (`app::random::range_int`)
- `0x710213a360` (lua wrapper rand)
- `0x710213a9f4` (lua wrapper randf)

Plus xref the **9 channel constants** (the FNV hashes) — these are `Hash40` values like `0x41f1b251e` from rng.md. Search the binary for ADRP+ADD constants matching those hashes.

### 2. Build the call graph
For each caller, recurse up:
- Caller → who calls caller → who calls THEIR caller → ...
- Stop when you hit either:
  - A function in main_loop's known direct-BL set (84 unique targets — see `data/ghidra_cache/main_loop_7103747270.txt`)
  - A function whose name suggests it's per-frame (e.g. `update`, `tick`, `frame`, `process`, `advance`, `exec`)
  - A function reached via an indirect dispatch from main_loop (look for it in vtable slots)

### 3. Identify the sim tick
The function we want is the **deepest** node in the call graph that:
- Has a path to main_loop
- Eventually transitively calls rand
- Iterates fighters / battle objects (look for loops with `BattleObjectModuleAccessor*` arguments)

If multiple functions match, prioritize:
1. Functions that take `BattleObject*` or `BattleObjectModuleAccessor*` as a parameter
2. Functions that call other functions on the FighterStatus vtable (`0x7104f7f2e8` — Pool A's earlier find)
3. Functions in the `0x71036xxxxx` or `0x71037xxxxx` range (where the sim driver is most likely to live)

## CRITICAL — Stop and ask if this round dies
This is round 5 of the hunt. If your bottom-up walk also produces only dead ends (e.g. all rand callers are Lua/script context, none reach main_loop directly), **STOP** and write a clear "static analysis is exhausted" verdict. We will switch to GDB watchpoints from a running emulator instead of doing round 6.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

Use `tools/xref_bin_scan.py` for binary scans.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool A — Round 5: bottom-up RNG-driven sim tick walk

### Direct rand callers (xref results)
| Caller fn | Address | Reaches main_loop? | Iterates fighters? |
|-----------|---------|---------------------|--------------------| 
| FUN_XXXX  | 0xXXXX  | YES via FUN_XXXX    | YES                |
| ...       | ...     | ...                 | ...                |

### Call graph
[ASCII tree showing rand → caller1 → caller2 → ... → main_loop]

### Sim tick verdict
[FOUND at FUN_XXXX (which calls rand transitively, iterates BattleObject vtable, reachable from main_loop)]
[OR: STATIC ANALYSIS EXHAUSTED — recommend GDB watchpoint from running emulator]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
