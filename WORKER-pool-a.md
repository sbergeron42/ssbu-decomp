# Worker: pool-a

## Model: Opus

## Task: ROLLBACK CO-PRIORITY-1 — Decompile FUN_71014f10c0 (the 40-read serializer)

## Priority: HIGHEST — potentially reveals built-in walker / save-state implementation

## Context
The sim tick hunt converged on a list-walking dispatcher inside main_loop (Dispatcher A) that calls `vtable[+0x28]` on every node in a list rooted at `[**(DAT_710593a6a0+0x24e8)+0x2da8]`. See `docs/rollback/sim_tick_hunt.md` for full context.

`FUN_71014f10c0` reads `DAT_710593a6a0` ~40 times in a row. That's almost certainly a **serializer**. The rollback team identifies three plausible identities:

1. **Match replay encoder** — RULED OUT (Smash replays store inputs, not state)
2. **LDN sync/resync encoder** — would be a bombshell. Smash already having an "encode match state" function would mean rollback save-state is a wrapper around a built-in function.
3. **Debug/telemetry dumper** — still useful as a structural reference; enumerates what's reachable from the root.

**Either way, this function tells us the spec for the savestate walker.**

## What To Do

1. **Decompile `FUN_71014f10c0`** via `mcp__ghidra__decompile_function_by_address 0x71014f10c0`
2. **CRITICAL — STOP-AND-DOCUMENT RULE**: If Ghidra MCP fails (timeout, "too large", error), **DO NOT retry**. Immediately:
   - Append the address + error message to `data/ghidra_cache/manual_extraction_needed.md`
   - Move on to the next function in your workplan
   - The orchestrator will manually extract and the pool can read it from `data/ghidra_cache/<addr>.txt` next session

3. **Classify the function**:
   - Does it call `nn::os::SendMessageQueue` or LDN-namespaced functions? → LDN sync encoder (bombshell)
   - Does it call `nn::diag` / `nn::dbg` / `printf` / log functions? → Debug dumper
   - Does it write to a buffer parameter? → Encoder of some kind (good either way)
   - Does it have a counterpart `FUN_XXX` that decodes? → Round-trip serializer (most useful)

4. **Document the field walk**:
   - For each `DAT_710593a6a0` deref, what offset is being accessed?
   - This gives us the **list of all live state fields** the walker enumerates from the scene root
   - This IS the spec for the snapshotter, regardless of identity

## Output

Append a new section to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool A — FUN_71014f10c0 classification (next-session)

### Identity verdict
[LDN sync encoder / Debug dumper / Other] — evidence

### Field walk from DAT_710593a6a0
| Read # | Offset | Type read | Purpose |
|--------|--------|-----------|---------|
| 1 | +0xNN | u32 | ... |
| ... | ... | ... | ... |

### Implications for rollback walker
[bombshell scenario / spec reference / dead end]
```

If it's the LDN sync encoder, ALSO write `docs/rollback/savestate_walker.md` documenting how to call it from rollback.

## Stop-and-document rule (applies to ALL Ghidra calls)
If `mcp__ghidra__*` returns an error, timeout, or "request failed":
1. Note the address and error
2. Append to `data/ghidra_cache/manual_extraction_needed.md` (create if missing) in this format:
   ```
   ## 0xXXXXXXXX (FUN_XXXXXXXX or known name)
   - Pool: pool-a
   - Reason: timeout / too large / unknown error
   - Why we need it: [one-line context]
   ```
3. Move on. Do NOT retry the same address.

## Quality Rules
- NO `FUN_` names in committed src/ code (research docs may reference them)
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
