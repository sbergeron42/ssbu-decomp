# Worker: pool-a

## Model: Opus

## Task: ROLLBACK Round 8 — service-call safety audit of FUN_7103724a80 (the sim tick entry)

## Priority: HIGHEST — BLOCKER for Eden-side resim prototype

## Context
Read `docs/rollback/sim_tick_FOUND.md` first. The sim tick entry is **`main_loop + 0x5384` → `bl FUN_7103724a80`**. This was captured by a GDB hardware watchpoint on the RNG state during live Switch gameplay.

Eden-side rollback resim plans to call `FUN_7103724a80` headlessly N times to replay frames after a misprediction. **This is only safe if the function and its call tree do NOT synchronously invoke any host service** — otherwise, resim re-fires side effects (audio, graphics, filesystem, LDN, wait primitives) that the host has already committed.

The rollback team is blocked on this safety question. Your answer unblocks the Eden prototype.

## The cached decomp
**`data/ghidra_cache/FUN_7103724a80.txt`** — 267 lines, full Ghidra decomp. The orchestrator manually extracted it. **Read this with the `Read` tool, do NOT call MCP on `0x7103724a80`.**

## What To Do

### 1. Read FUN_7103724a80 in full
It's only 267 lines — read the whole thing. Understand its structure.

### 2. Enumerate every BL call
For each direct BL and every indirect `blr` in the function body:
- What address / symbol is it calling?
- Is the callee a PLT stub to a `nn::*` or `nnsocket::*` symbol?
- Does the callee route to one of the known scheduler primitives (`FUN_7103548240`, `FUN_7103549170`, `FUN_710354c720`)?

### 3. One-level recursion — check the suspicious callees
For each BL target that isn't obviously safe (allocator, mutex, libc++ container helper), decompile it via `mcp__ghidra__decompile_function_by_address` and check its own BL set.

Known safe patterns (you can skip these):
- `je_aligned_alloc` / `jeFree_*` / `operator_delete_*` (jemalloc)
- `std::__1::*` libc++ containers
- `std::mutex::lock/unlock`, `recursive_mutex::*` (just CAS spinlocks)
- `phx::Fiber::switch_to_fiber` (just yields — NOT a host syscall at the coop level)
- `FUN_7103548240` / `FUN_7103549170` / `FUN_710354c720` (the scheduler plumbing Pool C already classified in Round 6)
- `ExclusiveMonitorPass` / `ExclusiveMonitorsStatus` (bare atomics)

**Known UNSAFE patterns** — flag these immediately:
- `nn::os::Wait*`, `nn::os::*MessageQueue`, `nn::os::*Event`, `nn::os::SleepThread`
- `nn::os::SignalLightEvent` / `WaitLightEvent` — this is how the scheduler wakes worker threads! **Any BL to this is a blocking side effect during resim.**
- `nn::audio::*` — audio state committed to hardware
- `nn::gr::*` / `nn::gfx::*` — graphics command submission
- `nn::fs::*` — filesystem
- `nn::ldn::*` / `nnsocket::*` — networking
- `nn::diag::*` / `nn::dbg::*` — logging (safe-ish but still a side effect)

### 4. Check the recursion depth
The captured backtrace shows `FUN_7103724a80` recurses through `FUN_7103724d94` ↔ `FUN_71022df070`. Check those too:
- Decompile `0x7103724d94` (small — should fit in MCP)
- Decompile `0x71022df070`
- Walk their BL sets for unsafe symbols

### 5. Write a verdict
Clean/dirty/conditional:
- **CLEAN**: no unsafe BL reachable. Eden can `dynarmic_call_guest(0x7103724a80, x24)` directly during resim.
- **DIRTY**: list the specific unsafe BLs. Eden needs a service-quarantine shim that stubs those functions during resim mode.
- **CONDITIONAL**: some branches are clean, others are dirty. List which paths are gated by what and whether the dirty paths are reachable in a normal gameplay frame.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts on any address:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Create `docs/rollback/sim_tick_safety.md`:

```markdown
# FUN_7103724a80 — service-call safety audit

## TL;DR
[CLEAN / DIRTY / CONDITIONAL]

[One-paragraph verdict — can Eden call this function headlessly during resim?]

## Direct BLs inside FUN_7103724a80
| Address | Target | Symbol | Verdict |
|---------|--------|--------|---------|
| 0xXXXX  | 0xYYYY | ...    | safe/unsafe/TBD |

## Recursive walk (1-2 levels)
| Path | Reaches service? |
|------|------------------|
| FUN_7103724a80 → FUN_XXXX → nn::os::... | YES — blocking |
| ...  | ... |

## Unsafe branches
[List of specific call sites with exact addresses and what service they hit]

## Service-quarantine shim requirements
[List of functions Eden must stub during resim mode, OR "no shim needed"]

## Confidence
[HIGH — all paths traced / MEDIUM — some timeouts / LOW — analysis incomplete]
```

## Quality Rules
- Documentation is the primary deliverable
- If you DO decomp anything to src/, standard rules apply (no FUN_ names, no Ghidra vars, no raw vtable dispatch, cast density under 10%)

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
