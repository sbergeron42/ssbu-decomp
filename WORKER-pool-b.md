# Worker: pool-b

## Model: Opus

## Task: ROLLBACK Round 8 — find where main_loop loads x24 before the sim BL

## Priority: HIGH — Eden rollback needs the sim_root pointer source

## Context
Read `docs/rollback/sim_tick_FOUND.md` first. The sim tick entry is **`main_loop + 0x5384` → `bl FUN_7103724a80`** with `x0 = x24`. We have the BL target but we don't know what `x24` is or how it was set.

From the captured disassembly at `main_loop + 0x5380..+0x5388`:
```
0x710374c620:  mov  x0, x24        ; x24 is the sim root
0x710374c624:  bl   0x7103724a80   ; THE sim BL
0x710374c628:  ...                 ; return site (backtrace lr)
```

Eden rollback needs to cache `x24` at match start and pass it every resim call. To do that, we need:
1. The exact earlier instruction in `main_loop` that assigns `x24`
2. The source of the value (global / chain / function return)
3. If it's a global: the address, so Eden can read it directly
4. If it's a chain off another singleton: the chain, so Eden can walk it

## What To Do

### 1. Read main_loop body from the top
**`data/ghidra_cache/main_loop_7103747270.txt`** — already cached (3,947 lines). Read with the `Read` tool, NOT MCP.

Scan the body backwards from the sim BL at `0x374c624` looking for:
- Any `mov x24, xN` (copy from another register)
- Any `ldr x24, [...]` (load from memory)
- Any `adrp x24, ...; add x24, x24, ...` (address-of-global setup)
- Function calls whose return value goes into `x24` (via `mov x24, x0` after a `bl`)

The assignment could be far back — main_loop is 22 KB of body. Start by grepping the cached file for the string `x24` and filter out all reads (we want writes only).

### 2. Identify the value source
Once you find the assignment, classify it:
- **Global singleton**: `adrp + ldr` from a DAT address → document the DAT
- **Chain deref**: `ldr x24, [xN, #imm]` where xN is a known singleton → document the chain
- **Function return**: `bl FUN_XXXX; mov x24, x0` → the function identifies the owner subsystem
- **Constructor output**: stack-allocated object → this would be a red flag (means x24 is per-frame, not stable)

### 3. Verify it's stable across frames
The assumption for Eden rollback is that `x24` is cached at match start and reused every frame. If it's loaded once and never reassigned between frames, we can cache it. If it's reassigned every frame (from a chain of derefs from some singleton), Eden needs to walk the chain every resim too.

Check whether the assignment happens inside main_loop's **boot/prologue region** (`0x3747270..0x3747504` — one-shot boot per Pool C Round 5) or inside the **frame loop body** (`0x3747504..0x374cbc0`).
- If in boot: loaded once, stable, Eden caches it at match start.
- If in frame loop: reloaded every frame, Eden must walk whatever chain main_loop walks.

### 4. If x24 comes from a chain, identify the root singleton
Trace back until you hit a DAT address. That's the cacheable handle Eden uses.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts on any address:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_FOUND.md` (create a new `## x24 source` section):

```markdown
## x24 source — Round 8

### Assignment site
- Address: `0x710374XXXX` (inside main_loop boot / frame body)
- Instruction: `[exact insn]`

### Source chain
Eden can get x24 at resim time via:
```c
<code snippet showing how to compute x24 from a cacheable root>
```

### Stability
- [STABLE — loaded once at match start / PER-FRAME — reloaded every tick]
- Cacheable by Eden: [YES / walk-every-frame]

### Root singleton
- Address: `DAT_710XXXXX`
- Already known? [list which Pool round first found it, or NEW]
- Runtime address on Switch (add to $main): [$main + offset]
```

## Quality Rules
- Documentation is the primary deliverable
- Use the cached main_loop file, do NOT call MCP on `0x7103747270`

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
