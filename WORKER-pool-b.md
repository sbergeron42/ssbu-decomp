# Worker: pool-b

## Model: Opus

## Task: ROLLBACK — DAT_710593a6a0 constructors (FUN_71022cd350, FUN_71022b7100)

## Priority: HIGH — reveals the scene-root singleton type and what state lives there

## Context
Your previous session found that Dispatcher A inside main_loop walks a list at `[**(DAT_710593a6a0+0x24e8)+0x2da8]` and dispatches `vtable[+0x28]` per node. See `docs/rollback/sim_tick_hunt.md` for the full breakthrough.

The two writers of `DAT_710593a6a0` are its **constructors**:
- `FUN_71022cd350` at `0x71022cd600` (write site)
- `FUN_71022b7100` at `0x71022c9fb4` (write site)

These will reveal:
- The singleton's actual type name (likely `app::Scene`, `app::GameMain`, or `app::WorldManager`)
- Its initial vtable
- Sub-objects installed at `+0x24d0`, `+0x24e8`, `+0x2da8`
- **Other state fields the snapshot walker must capture from this root** (potentially missing from the current `memory_map.md`)

Your previous session noted that `FUN_71022cd350` hit Ghidra MCP's size limit on the first attempt — it's >145KB of decompile output.

## What To Do

1. **Try `mcp__ghidra__decompile_function_by_address` on FUN_71022cd350 first**
2. **If it times out or errors**: STOP. Apply the stop-and-document rule below. Do NOT retry.
3. **If it succeeds**: extract the singleton type information and document the field installations
4. **Then try FUN_71022b7100** with the same approach

## Stop-and-document rule
If `mcp__ghidra__*` returns an error, timeout, or "request failed":
1. Note the address and error
2. Append to `data/ghidra_cache/manual_extraction_needed.md` (create if missing):
   ```
   ## 0xXXXXXXXX (FUN_XXXXXXXX)
   - Pool: pool-b
   - Reason: timeout / too large / unknown error
   - Why we need it: [one-line context]
   ```
3. **Move on to the next task.** Do NOT retry the same address. The orchestrator will manually extract.

## Fallback work if both constructors are uncrackable

If both `FUN_71022cd350` and `FUN_71022b7100` time out, work on:

**Service-call safety smoke test on `vtable[+0x28]` for one fighter node**

Pool A's previous session found `FighterStatus` vtable at `0x7104f7f2e8`. The list dispatched by Dispatcher A contains heterogeneous tickable objects — fighters/items/effects. For ONE fighter-shaped node:

1. Find the concrete BattleObject subclass that fighters use
2. Find its `vtable[+0x28]` slot
3. Decompile that slot
4. Trace through it (1-2 levels deep) and look for any synchronous call to:
   - `nn::os::Wait*` / `nn::os::*MessageQueue` / `nn::os::*Event`
   - `nn::audio::*`
   - `nn::gr::*` / `nn::gfx::*`
   - LDN-namespaced functions
   - Filesystem (`nn::fs::*`)
5. **Report**: clean (no host services touched) or dirty (specific service calls found)

This is the **critical-risk smoke test for the rollback resim approach**. If `vtable[+0x28]` is dirty, rollback needs a service shim layer; if clean, the design is straightforward.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool B — Scene root constructors / vtable[+0x28] safety

### FUN_71022cd350 (DAT_710593a6a0 constructor #1)
[verdict / extracted type info / OR uncrackable — see manual_extraction_needed.md]

### FUN_71022b7100 (DAT_710593a6a0 constructor #2)
[verdict / OR uncrackable]

### vtable[+0x28] service-call safety smoke test
- Node type tested: [fighter / item / effect]
- vtable[+0x28] address: 0xXXXXX
- Services touched: [list, or "clean"]
- Verdict: [SAFE for headless resim / DIRTY — needs service shim]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Cast density under 10%
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
