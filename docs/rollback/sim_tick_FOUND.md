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

## Round 8 — DAT_71053346d0 was a misread; the real address is DAT_710593a6d0

**Correction (2026-04-11, Pool C).** The Round 7 claim that main_loop's
indirect dispatch reads `DAT_71053346d0` is wrong. Verified by re-decoding
the ADRP+LDR from the binary:

```
0x710374c608:  d0010f68  adrp x8, 0x710593a000     ; NOT 0x7105334000
0x710374c60c:  f9436900  ldr  x0, [x8, #0x6d0]     ; ea = 0x710593a6d0
```

The raw ADRP `imm` bits are `0x21ee`, which produce page `0x710593a000`
when added to the page-aligned PC `0x710374c000`. The Round 7 writeup
transposed the page; the same typo then propagated through the "Pool C
investigated `DAT_710593a___` extensively but this is a different page"
remark in the Supporting singleton section. Both pages are the SAME page.

There are **two** reads of this global in main_loop, not one:
- `0x710374c3f8` (main_loop + `0x5188`)
- `0x710374c60c` (main_loop + `0x539c`) — the one Round 7 captured
Both run the identical 6-instruction indirect-dispatch sequence (`ldr` →
`cbz` → `ldr vt` → `ldr vt[+0x30]` → `blr`), and each is immediately
followed by the direct `bl 0x7103724a80` to `task_run_outer`.

### `DAT_710593a6d0` identity — it is a `std::function<void()>` field

`DAT_710593a6d0` is NOT the start of a subsystem singleton; it is the
`__f_` pointer inside a libc++ `std::function<void()>` object stored at
`0x710593a6b0`. Layout (SBO, 48 B):

```
0x710593a6b0  vptr        = 0x7105182268           // __func<> vtable
0x710593a6b8  bound[0]    = 0x71032ca620           // the captured free-fn pointer
0x710593a6c0  bound[1]    = 0                       // unused
0x710593a6c8  pad/align
0x710593a6d0  __f_        = 0x710593a6b0 (self)    // SBO points back to *this
```

main_loop reads `__f_`, loads `*(*__f_)` to get the vtable, then calls
`vt[+0x30]`, which for this specific `__func<>` instantiation is the
bog-standard libc++ "free-fn-ptr" invoker:

```
0x71032ca760:  ldr x0, [x0, #0x8]
0x71032ca764:  br  x0
```

i.e. load the free-fn-ptr from the SBO at `this+8` and tail-jump to it.
So `vt[+0x30]` is really just `(*FreeFnPtr)()` — the call lands at
`0x71032ca620`.

### Full `__func<>` vtable at `0x7105182268` (via `.rela.dyn`)

```
vt[+0x00] = 0x71003cb1c0   slot 0 — __clone (heap alloc new copy)
vt[+0x08] = 0x71032ca690   slot 1 — destroy (trivial SBO)
vt[+0x10] = 0x71032ca6a0   slot 2 — destroy_deallocate
vt[+0x18] = 0x71032ca720   slot 3 — __clone(dst) (placement copy: 6 insns)
vt[+0x20] = 0x71032ca740   slot 4 — `ret` (nullary no-op body)
vt[+0x28] = 0x71032ca750   slot 5 — cbz + tail to 0x710392e590 (`operator delete`)
vt[+0x30] = 0x71032ca760   slot 6 — INVOKER (`ldr x0,[x0,#8]; br x0`)
```

### `FUN_71032ca620` — the bound callable

Decoded from raw bytes (Ghidra misattributes these addresses to the
large `FUN_71032ca0a0` above because the auto-analyzer never carved the
trailing tail of that CU). The body is unmistakable:

```cpp
void tick_broadcast_710532e7a8(void) {
    auto* owner = *(void**)(0x710532e7a8);      // singleton, installed below
    lock(&owner->mutex_at_0x18);                 // FUN_71039c1410
    owner = *(void**)(0x710532e7a8);             // reload under lock
    void** it  = *(void***)(owner + 0x00);       // vector::begin
    void** end = *(void***)(owner + 0x08);       // vector::end
    while (it != end) {
        auto* obj = *it;
        if (*(u8*)(obj + 0x70) != 1) {           // skip-flag (deleted? paused?)
            (*(void(**)(void*))(*(void**)obj + 0x18))(obj);  // vt[+0x18] = slot 3
        }
        ++it;
    }
    return unlock(&owner->mutex_at_0x18);         // tail-call FUN_71039c1420
}
```

### Writers of `DAT_710593a6d0` (= install / teardown path)

- **Init (BSS zero only)**: `FUN_71004468a0 + 0x2c` — `str xzr, [x1, #0x20]`.
  This same function registers three sibling `std::function`s via
  `FUN_71000001c0` (a no-op stub, which means `.init_array` just nulls
  the slots; the real install happens later).
- **Real install**: `FUN_71022b7100` at `0x71022bce90..0x71022bced8`.
  Builds a local `std::function` on the stack (vptr `0x7105182268`,
  captured ptr `0x71032ca620`), calls the libc++ `std::function::swap`
  helper `FUN_71003cb050` with `arg1 = 0x710593a6b0`, moving the built
  object into the global. `FUN_71022b7100` is the same 1.7 MB ctor Pool
  B identified as the Mii-FighterDatabase (`DAT_710593a6a0`) installer —
  it is too large for Ghidra MCP and is already listed in
  `manual_extraction_needed.md`.
- **Teardown**: `FUN_71022cd350` at `0x71022cf3e8` / `0x71022cf41c`.
  Pool A confirmed `FUN_71022cd350` is a global/match teardown; it also
  nulls `DAT_710593a6a0` and `0x710532e7a8` in the same function.

The singleton `0x710532e7a8` (the collection the broadcast walks) has
the same installer+teardown pair, confirming it is part of the same
subsystem as `DAT_710593a6a0`'s Mii database.

### Is this indirect dispatch sim-safe for resim?

**Provisional classification — PRESENTATION (skip during resim).**
Evidence:

1. **Not on the sim path.** The RNG-watchpoint trace in this document
   returned via `lr = 0x710374c628` — the return site of the DIRECT
   `bl 0x7103724a80`, not the return site of the `blr x8` indirect
   dispatch. The sim RNG fired through the direct call, not the
   indirect one.
2. **Sibling, not nested.** The indirect dispatch and the direct BL
   are sequential peers in main_loop — if the indirect were part of
   the sim, the direct BL would not run unconditionally right after.
3. **Same ctor as the Mii fighter database.** Pool A/B retired the
   "scene root" identity of `DAT_710593a6a0` and settled on Mii-related
   (it embeds `nn::mii::Database`). The collection iterated here is
   almost certainly Mii cache entries or Mii-asset stream tasks.
4. **Body shape matches asset-update, not sim-advance.** Locked
   iteration + per-entry `vt[+0x18]` with a skip-flag at `+0x70` is the
   canonical "update each cached asset" shape. No RNG advance, no
   counter bump, no writes to anything a BattleObject would observe.

**Resim recommendation**: Eden should call ONLY the direct BL to
`0x7103724a80` per resim tick. Skip the indirect `vt[+0x30]` dispatch
at `0x710374c61c` (and its twin at `0x710374c408`). Confirm live with
a second GDB watchpoint on any byte inside the Mii-cache collection
during a rollback resim — if that byte moves while resim is active,
the callback is NOT safe to skip and we need a partial shim.

### Open questions that remain

2. **What is `x24` at main_loop `0x710374c620`?** The argument to
   `task_run_outer`. It's loaded elsewhere earlier in main_loop's body;
   needs a backward scan to find its source.
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

---

## x24 source — Round 8 (answer to open question #2)

### TL;DR

**`x24` at the sim BL is `main_loop`'s first argument (`param_1` / entry `x0`).**
It is captured once in the prologue, stored to a fixed stack slot, and
reloaded into `x24` right before each sim dispatch. It is ALSO mirrored
to a .bss global at `DAT_710593A4C0` in the same prologue, giving Eden a
stable handle it can read without touching main_loop's stack frame.

### Assignment site (last write before the sim BL)

| PC | Instruction |
|----|-------------|
| `0x710374c3c0` | `ldr x24, [sp, #608]` |
| `0x710374c620` | `mov x0, x24`           (first sim BL arg setup) |
| `0x710374c624` | `bl 0x7103724a80`        (the sim BL itself) |

Between `0x374c3c0` and `0x374c624` there are **no further writes** to
`x24` on any reachable control path. (There are earlier reloads at
`0x374c044` and `0x374c0f4` reading the same stack slot; the entire body
of main_loop has exactly ONE store to `[sp, #608]`, so all three reloads
fetch the same value.) The second sim BL at `0x710374c74c` (catch-up
path) also uses the same `x24`.

### Stack slot source

The slot is written exactly once, in the prologue region:

```
0x710374 72ac:  mov  x21, x0              ; x21 = param_1 (x0 on entry)
0x710374 72b0:  blr  x8                    ; early init callback
0x710374 72b4:  adrp x8, #35598336         ; raw bytes: 88 0f 01 f0
0x710374 72b8:  str  x21, [x8, #1216]      ; *DAT_710593A4C0 = param_1
0x710374 72bc:  bl   nn::oe::FinishStartupLogo@plt
...
0x710374 73c0:  str  x21, [sp, #608]       ; spill param_1 to the reload slot
```

Decoding the ADRP at `0x37472b4` by hand (raw: `88 0f 01 f0`):
- `immhi = 0x87C`, `immlo = 3` → `imm21 = 0x21F3`
- `imm21 << 12 = 0x21F3000`
- PC page = `0x3747000`, target = `0x3747000 + 0x21F3000 = 0x593A000`
- `str x21, [x8, #1216]` → `*(u64*)0x593A4C0 = param_1`
- Runtime: `*(u64*)0x710593A4C0 = main_loop's param_1`

This address lands in `.bss` (`.bss` = `0x52A8570..0x7446FFF`), same page
(`0x593A000`) as the previously-identified frame counter `DAT_710593AA90`
(pool-b Round 7). All three are peers in the **pead::MainThread singleton
block**.

### Source chain (for Eden rollback)

```cpp
// At match start (or main_loop hook), cache the sim root:
void* sim_root = *(void**)(guest_memory + 0x593A4C0);  // host-side read of DAT_710593A4C0

// Every resim frame, call the sim BL directly:
dynarmic_call_guest(0x7103724a80, sim_root);
```

Equivalent alternate recipe (no global read, catches value right at the
source):

```cpp
// Hook main_loop entry (0x7103747270) once at startup:
on_main_loop_entry(uint64_t x0) { sim_root = x0; }  // runs exactly once
```

### Stability

- **STABLE — loaded once at game startup, reused for every frame in the
  session.**
- `main_loop` is `pead::MainThread`'s `Run` body (pool-b Round 7 cross-
  referenced `pead_framework_init` → this thread adopts the current thread
  instead of creating a new one, so main_loop is invoked exactly once
  across the process lifetime).
- The spill at `0x37473c0` happens inside main_loop's **boot/prologue
  region** (`0x3747270..0x3747504`), before any frame loop. No later
  instruction rewrites `[sp, #608]` until `0x374ea98`, which is FAR after
  the last sim BL (`0x374c74c`) — inside a post-sim teardown block where
  the slot is reused for a SIMD spill.
- `DAT_710593A4C0` is written exactly once (at `0x37472b8`, in the same
  prologue). No other write to that address was observed in main_loop.
  A global xref scan is still advisable before shipping, but the value
  is functionally immutable for Eden's purposes — it's the pead thread's
  `this` pointer and would only change if the pead framework were
  reinitialized, which never happens during gameplay.
- **Cacheable by Eden: YES.**

### Root singleton

- Address: `DAT_710593A4C0` (= `*(u64*)(main_base + 0x593A4C0)`)
- Section: `.bss`
- Page peers in the pead::MainThread singleton block:
  - `DAT_710593A4C0` — **NEW (Round 8)** — sim_root / main_loop's `param_1`
  - `DAT_710593A6D0` — first-dispatch vtable root (see correction below)
  - `DAT_710593AA90` — frame counter (pool-b Round 7)
- Already known? **NEW.** Round 8 first identification.
- Runtime address on Switch: `$main + 0x593A4C0` (= `0x710593A4C0` at the
  canonical `$main = 0x7100000000` from `reference_binary`).

### Bonus finding — address correction to Round-7 doc

The "Supporting singleton" section above describes the first-dispatch
root as `DAT_71053346d0`. **This is an address-decoding error.** The
ADRP at `0x710374c608` has raw bytes `68 0f 01 d0`:

- `immhi = 0x87B`, `immlo = 2` → `imm21 = 0x21EE`
- `imm21 << 12 = 0x21EE000`
- PC page = `0x374c000`, target = `0x374c000 + 0x21EE000 = 0x593A000`
- `ldr x0, [x8, #1744]` → `x0 = *(u64*)(0x593A000 + 0x6D0) = *(u64*)0x593A6D0`

So the correct address is **`DAT_710593A6D0`**, NOT `DAT_710533 46D0`.
This is the SAME page as `DAT_710593A4C0` (sim_root) and `DAT_710593AA90`
(frame counter) — all three are peers in the pead::MainThread singleton
block, which is architecturally much more plausible than the original
doc's cross-page placement. The original calculation appears to have
mistakenly added the ADRP immediate directly to a `0x5334000` page base
instead of decoding the instruction.

Recommend updating the "Supporting singleton" section in the main body
once verified by whoever owns that doc.

### How the sim BL is reached (control-flow notes)

For future readers who want to understand which code path executes the
sim:

```
main_loop body (frame loop):
  0x374c118: ldr  w22, [x8]            ; w22 = num sim ticks this frame
  0x374c11c: b.lt #1312 → 0x374c63c    ; if 0, skip sim entirely (paused/menu)
  0x374c120: b.ne #220  → 0x374c1fc    ; if >1, goto catch-up loop
  -- fall through: w22 == 1 (normal frame) --
  0x374c124..0x374c1f4:                ; 10x vtable[+0x28] dispatch on x28[0..72]
                                         (pre-sim prep for 10 children)
  0x374c1f8: b    #788  → 0x374c50c    ; unconditional skip to sim path
  -- 0x374c50c..0x374c5dc: sim dispatch prep (submit_task, exclusive monitor) --
  -- 0x374c608..0x374c61c: vtable[+0x30] on DAT_710593A6D0 (sibling subsystem) --
  0x374c620: mov  x0, x24              ; x24 = param_1 (main_loop's arg)
  0x374c624: bl   0x7103724a80         ; THE sim BL (first call site)

  -- fall through to 0x374c628+: frame counter increment, second vtable barrage --
  0x374c664: b.gt #336  → 0x374c7b4    ; if frame condition, skip second sim
  0x374c668..0x374c744: 10x vtable[+0x28] dispatch on x28[0..72]
  0x374c748: mov  x0, x24              ; same x24 — unchanged since 0x374c3c0
  0x374c74c: bl   0x7103724a80         ; sim BL (SECOND call site!)
```

There are thus **two sim BL sites inside main_loop**, not one. Both use
the same `x24`. Round 7's captured backtrace fired on the FIRST
(`0x374c628` return site). Eden should call the sim BL twice per
frame ONLY if it's emulating the exact main_loop control flow; for
simple resim replay, one call at `0x7103724a80` with `sim_root` is
functionally equivalent because both calls are just running the same
task subtree.

The `w22 > 1` catch-up path at `0x374c1fc..0x374c504` is an orphaned
loop reached from `b.ne #220` at `0x374c120`. It runs 10x vtable + a
separate submit_task sequence `w22` times and then `b #312` to
`0x374c63c`, bypassing the sim BL path. This is the **multi-tick
catch-up** branch. It reloads `x24 = [sp+608]` at `0x374c3c0` every
iteration but does not itself invoke the sim BL — the sim ticks are
dispatched via `submit_task(FUN_7103548240, ...)` at `0x374c394` on
each iteration, routing through the generic task runner Pool C Round 6
identified.

### Confirmation bytes (for independent verification)

If you dump the first few instructions of main_loop from `data/main.elf`:

```
$ llvm-objdump -d --start-address=0x3747270 --stop-address=0x37472c0 data/main.elf
 3747270:  ff ... stp d15, d14, [sp, #-160]!   ; prologue stack frame
 37472ac:  f5 03 00 aa  mov  x21, x0            ; <-- CAPTURE param_1
 37472b0:  00 01 3f d6  blr  x8                  ; early vt[3] call
 37472b4:  88 0f 01 f0  adrp x8, #35598336       ; page(0x593A000)
 37472b8:  15 61 02 f9  str  x21, [x8, #1216]    ; <-- MIRROR to DAT_710593A4C0
 37472bc:  ed 00 0a 94  bl   FinishStartupLogo@plt
```

And the reload + sim BL:

```
$ llvm-objdump -d --start-address=0x374c3c0 --stop-address=0x374c628 data/main.elf
 374c3c0:  f8 33 41 f9  ldr  x24, [sp, #608]     ; <-- RELOAD into x24
 ...
 374c620:  e0 03 18 aa  mov  x0, x24              ; sim arg
 374c624:  17 61 ff 97  bl   0x3724a80            ; <-- SIM BL
```

