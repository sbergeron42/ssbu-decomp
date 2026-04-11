# Worker: pool-a

## Model: Opus

## Task: ROLLBACK Round 4 — identify the MatchRunner type at *DAT_710593a510

## Priority: HIGH — directly identifies the rollback arm signal owner

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Last round, Pool B found that `DAT_710593a510` is a singleton pointer that:
- Is null on boot
- Gets installed by a helper at `0x7103741a60`
- Is read by `main_loop` immediately before a `cbz x0, skip` (skip if null) followed by a per-frame vtable dispatch via slot `+0x30` taking `(this, int* phase)`

This is the strongest match-active gate candidate. We need to identify the **type** at `*DAT_710593a510` to know what class owns the per-frame driver.

## What To Do

### 1. Decompile the installer at `0x7103741a60`
- The store is `STR X0, [X8, #0x510]` inside `FUN_7103741988` (or similar — find the containing function)
- Decompile that function via `mcp__ghidra__decompile_function_by_address`
- Find what `X0` is — is it the return of an `Instance()` singleton getter? An allocator call followed by a constructor?
- Whatever returns `X0` IS the runner constructor

### 2. Identify the runner class
- Find the constructor of the type being installed
- The constructor's first store will be the vtable: `STR Xn, [X0, #0]` — that's the vtable address
- Use `mcp__ghidra__get_xrefs_to <vtable_address>` to find where else this vtable is used
- That tells you the class name (or at least the class's static methods)

### 3. Verify the per-frame method at vtable slot +0x30
- vtable[+0x30 / 8] = vtable[6]
- Decompile vtable slot 6 (the function pointer at `vtable + 0x30`)
- Confirm the signature is `void method(this, int* phase)` matching what main_loop calls
- What does this method do? **Does it iterate fighters / dispatch per-tick work?**
- If yes, **THIS IS THE SIM TICK** — document the call chain inside it

### 4. Find the clear/destroy path
- Find any code that stores `xzr` to `[..., #0x510]` or calls `delete`/`free` on the runner
- This is the rollback disarm signal

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

Use `tools/xref_bin_scan.py` (Pool C committed it last round) for any binary scanning needs.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool A — Round 4: MatchRunner type identification

### Installer at 0x7103741a60
- Containing function: FUN_XXXX (renamed: installCurrentMatch_XXXX)
- Source of installed pointer: [singleton getter / new + ctor / other]
- Type returned: [class name or vtable address]

### Runner class
- Vtable address: 0xXXXXX
- Class name (if .dynsym): [name]
- Vtable slot 6 (+0x30): [decomp summary]
- IS THIS THE SIM TICK? [YES — iterates fighters / NO — only does X / INCONCLUSIVE]

### Disarm path
- Function: 0xXXXX clears DAT_710593a510 / OR no clear path found
```

If you find the sim tick, write a TL;DR at the top of the section so the rollback team can find it instantly.

## Quality Rules
- NO `FUN_` names in committed src/ code
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
