# Worker: pool-b

## Model: Opus

## Task: ROLLBACK Round 5 — investigate the 10-slot per-player broadcaster FUN_71037857f0

## Priority: HIGHEST — strongest tick-shaped lead from your own Round 4 work

## Context
Read `docs/rollback/sim_tick_hunt.md` first. In Round 4 you found `FUN_71037857f0` is called **10 times consecutively** in main_loop at `0x710374bd9c..0x710374bfe8`, once per slot index 0..9 (= 8 players + 2 pad). Each call:

1. Loads x0 via `ldr x8, [x28, #0xa90]; ldr x0, [x8]`
2. Passes a per-slot config record from `[0x710593a7c8 + i*0x40]`
3. Passes a local probe struct whose vtable is `0x710522eea0`
4. Inside `FUN_71037857f0`, builds up to 5 packets via factories and calls `plVar6->vt[3](plVar6, packet)` on each
5. The receiver maintains 3 parallel ring-buffer cursors at `+0x3f0`, `+0x418`, `+0x4a0` — classic command-stream backing store

**10 slots × per-frame = per-player tick.** This is the strongest tick-shaped lead you have. Your previous reading was "could be replay-recording tick rather than simulation tick proper" — round 5 is to determine which.

## What To Do

### 1. Decompile FUN_71037857f0 in full
- `mcp__ghidra__decompile_function_by_address 0x71037857f0`
- Document its structure, the per-slot logic, and what `plVar6->vt[3]` actually does
- Find where it loops over the 5 packets — what does each represent?

### 2. Identify the receiver class (the thing held by `[x28, #0xa90]`)
- `x28` is set in main_loop's prologue. What's at offset `+0xa90`?
- Use `tools/xref_bin_scan.py` to find writers to `[anything+0xa90]` near the start of main_loop
- The constructor of whatever is at `[*[x28+0xa90]]` will reveal the type

### 3. Decompile vt[3] of the receiver
- `plVar6 = *(long **)(param_3 + 8)` — find what `param_3` is and what `param_3->[8]` points to
- The vtable at `0x710522eea0` (the "probe struct" vtable) is the local interface
- The receiver's vt[3] takes the packet — decompile it
- **Does vt[3] mutate fighter state? Iterate BattleObjects? Call into FighterStatus?**
- If yes: **THIS IS THE SIM TICK** (per-player variant)
- If no but it touches LDN-related globals: it's the replay/sync recorder

### 4. Connect to a fighter
- The packet builders (`FUN_710363f4a0`, `FUN_710381ba20`, etc.) clone source data — what's the source for slot N?
- If the source is `FighterManager.entries[N]` or `BattleObject* fighters[N]`, this directly proves the per-player connection

## CRITICAL — Stop and ask if this round dies
This is round 5. If FUN_71037857f0 turns out to be replay/recording (not sim), **STOP** and write a clear "this is recording, not sim" verdict. Don't pivot to another lead. We need to know definitively whether to switch to dynamic analysis.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool B — Round 5: FUN_71037857f0 deep dive

### Function structure
[full decomp summary]

### Receiver type
- Held at: [x28 + 0xa90 → ?]
- Class: [name or description]
- vtable: 0x710522eea0 → [identified target]

### vt[3] body
[what it actually does]

### Per-slot source data
- Slot 0..9 source: [FighterManager entries / replay ring / other]

### VERDICT
[SIM TICK FOUND — vt[3] iterates fighter state and mutates it]
[OR: REPLAY RECORDING — vt[3] only writes to ring buffers, no fighter mutation]
[OR: STATIC ANALYSIS EXHAUSTED — recommend GDB watchpoint approach]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
