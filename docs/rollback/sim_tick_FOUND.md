# Sim tick — FOUND (2026-04-11)

After 7 rounds of static analysis that exhausted the top-down approach, a **GDB
hardware watchpoint on the gameplay RNG state during live training-mode
gameplay** captured the exact call stack at the moment a sim-state mutation
happened. This document is the definitive answer.

## TL;DR — the sim tick entry

**`main_loop` (`FUN_7103747270`) calls the sim at offset `+0x5384`:**

```
0x710374c624:  bl  0x7103724a80        ; call task_run_outer
0x710374c628:  ...                      ; return site (= lr when RNG fires)
```

The target `FUN_7103724a80` is a generic task-subtree runner (sibling of
`FUN_7103548240` / `FUN_7103549170` — Pool C Round 6's scheduler family).
It takes a root task in `x0` and walks its children recursively, dispatching
`vt[+0x30]` (slot 6) on each leaf task. One of those leaf tasks IS the
fighter sim.

## Full backtrace at RNG capture

Captured on Switch hardware via `$main = 0x7e7d804000`, watchpoint on
`*(uint32_t*)(channel_array + 0x14)` (xorshift128 channel 1 state[0]):

| Offset | ELF address | Role |
|--------|-------------|------|
| `0x4a99e8` | `0x71004a99e8` | **PC** — inlined xorshift128 advance (`w = t`) |
| `0x4a9958` | `0x71004a9958` | RNG wrapper (the inlined `sv_math::rand` body's caller) |
| `0x4a9358` | `0x71004a9358` | fighter logic |
| `0x4a6894` | `0x71004a6894` | fighter logic |
| `0x6180d0` | `0x710060​80d0` | BattleObject subsystem |
| `0x3ad244` | `0x71003ad244` | BattleObject method |
| `0x137b5a8` | `0x7101 37b5a8` | L2C / ACMD layer |
| `0x135cc1c` | `0x7101 35cc1c` | L2C / ACMD layer |
| `0x135f76c` | `0x7101 35f76c` | L2C / ACMD layer |
| `0x1850f74` | `0x71018 50f74` | Task state-machine tick (inner) |
| `0x1850e68` | `0x71018 50e68` | Task state-machine tick (return site) |
| `0x3724d94` | `0x71037 24d94` | `task_run_inner` — children DAG walker |
| `0x22df070` | `0x71022 df070` | per-fighter iterator body |
| `0x3724d94` | `0x71037 24d94` | (recursion — DAG walk) |
| `0x22df070` | `0x71022 df070` | (recursion — DAG walk) |
| `0x3724d94` | `0x71037 24d94` | (recursion — DAG walk) |
| **`0x374c628`** | `0x71037 4c628` | **main_loop — return site of the sim dispatch BL** |
| `0x2c5cf0` | `0x71002 c5cf0` | `nnMain` |
| nnSdk `0x29da2c` | — | OS thread main |
| nnrtld `0xc0` | — | runtime loader entry |

## The sim dispatch sequence inside main_loop

At `0x710374c5a0..0x710374c628`:

```
; Load queue_id / priority from the task at x0+0x68/+0x6c
0x710374c5a0:  ldp  w2, w3, [x0, #104]          ; q, pri
0x710374c5a4:  add  x8, x0, #0x8                ; x8 = &task->node (= task+8)
0x710374c5a8:  mov  x0, x8
0x710374c5ac:  adrp x1, 0x710374c000
0x710374c5b0:  add  x1, x1, #0x240              ; x1 = FUN_7103548240 (task runner)
0x710374c5b4:  bl   FUN_7103549170              ; submit_task(&node, runner, q, pri)

; ... subsequent code that runs the scheduler ...

0x710374c608:  adrp x8, DAT_7105334000          ; singleton page
0x710374c60c:  ldr  x0, [x8, #0x6d0]            ; x0 = *(0x7105334 6d0) — task root
0x710374c610:  cbz  x0, 0x710374c620            ; skip if null
0x710374c614:  ldr  x8, [x0]                    ; x8 = x0->vtable
0x710374c618:  ldr  x8, [x8, #48]               ; x8 = vtable[+0x30]
0x710374c61c:  blr  x8                          ; vtable dispatch (1st call path)
0x710374c620:  mov  x0, x24                     ; x24 = another task root
0x710374c624:  bl   0x7103724a80                ; *** THE SIM TICK ENTRY ***
0x710374c628:  ...
```

**Two sibling calls** — an indirect vt[+0x30] dispatch (first) and a direct BL
to `task_run_outer` (second). The captured RNG write came through the SECOND
call (lr = `0x710374c628`).

## Supporting singleton

- **`DAT_7105334 6d0`** — newly identified. Pool C investigated the
  `DAT_710593a___` block extensively in Rounds 4–6; this one is in a
  different page (`0x710533 4___` vs `0x71059 3a___`). It holds the root
  task pointer for the main_loop's first (indirect) dispatch. Not yet
  named; worth investigating as it is the peer of the directly-called
  `task_run_outer` root.

## Pool C Round 6's architecture was right, not wrong

Pool C Round 6 identified `FUN_7103548240` as the generic task runner and
`FUN_7103549170` as `submit_task`. Pool C then concluded "main_loop is a
fiber-scheduled task pump, sim lives elsewhere" — but that conclusion was
based on decompiling ONE task's `vt[2]` and finding NEON math.

**The correct reading**: main_loop IS a fiber-scheduled task pump. Many
different tasks register through the scheduler, each with its own `vt[+0x30]`
body. Pool C's sampled task was the transform pool (NEON math). The fighter
sim is a DIFFERENT task in the same scheduler, reached by the direct BL at
`0x710374c624` (NOT through the `DAT_7105332120` transform task tree Pool C
was walking).

Also: **the correct vtable slot is `+0x30` (byte offset, slot index 6)**, not
`+0x10` (slot 2) that Pool C guessed at the end of Round 6. The generic
runner `FUN_7103548240` dispatches `vt[+0x30]`, and main_loop's own direct
indirect-call uses the same `+0x30` slot.

## For Eden rollback

The resim loop becomes:

```cpp
// Precondition: state snapshot restored; RNG restored.
void* sim_root = guest_memory[x24_during_sim_frame];  // cache at match start

// Call the sim tick directly (skip scheduler — we're single-threaded under rollback)
dynarmic_call_guest(0x7103724a80, sim_root);
```

This is **one BL target**, not the whole task graph. It advances the sim
subtree via its own internal scheduler calls, which (during rollback) will
execute synchronously because the rollback fork runs without worker threads.

## Cross-checks

1. **RNG state mutation**: confirmed (hardware watchpoint fired on a channel-1
   write at PC `0x71004a99e8`).
2. **Call is from main_loop**: confirmed (lr `0x710374c628` is inside main_loop's
   body `0x3747270..0x374ee68`).
3. **Uses Pool C's scheduler plumbing**: confirmed (same `submit_task` at
   `0x7103549170` and same runner `0x7103548240`).
4. **Vtable slot**: confirmed `+0x30` (byte) / slot 6 (both the direct
   `vt[+0x30]` dispatch in main_loop and `task_run_outer`'s internal dispatch
   use this offset).

## Open questions for Round 8

1. **What is the singleton at `DAT_71053346d0`?** (the indirect-dispatch
   root). First hint: its vtable at `+0x30` gets called IMMEDIATELY before
   the direct BL to `task_run_outer`. Likely a sibling subsystem whose tick
   runs in parallel — possibly the stage tick, the effect tick, or the
   fighter tick itself.
2. **What is `x24` at main_loop `0x710374c620`?** The argument to
   `task_run_outer`. It's loaded elsewhere earlier in main_loop's body;
   needs a backward scan to find its source.
3. **Decompile `0x7103724a80` (`task_run_outer`)** fully. The partial we
   have shows a state-machine gate on `[this+0x30]` and child-list walk at
   `[this+0x38]`, but the full body should reveal how it finds the fighter
   subsystem node.
4. **Confirm which task in the tree is the sim** by setting a second
   watchpoint on `FighterManager.entries[]` and catching a mutation. The
   RNG write confirmed SIM runs through this path; a Fighter field write
   confirms WHICH leaf is the per-fighter stepper.
