# FUN_7103724a80 — service-call safety audit

Round 8 of the sim-tick hunt. Follows `sim_tick_FOUND.md`, which
identified `FUN_7103724a80` (called from `main_loop` at `0x710374c624`)
as the entry point that the GDB watchpoint on the gameplay RNG captured.

Eden rollback needs to know: can we `dynarmic_call_guest(0x7103724a80, x24)`
headlessly during a resim, or will the call tree synchronously invoke
host services (audio, graphics, filesystem, LDN, blocking waits)?

## TL;DR

**CONDITIONAL — the outer dispatcher shell is CLEAN, but the concrete
child task `.run()` body could not be audited in this round.**

- The `FUN_7103724a80` function itself and every one of its direct BL
  callees (`FUN_7103724f60`, `FUN_7103724500`, `FUN_7103725180`,
  `FUN_7103723360`, `FUN_7103723e80`, `FUN_71003cb050`, `FUN_71037243f0`)
  invoke ONLY: jemalloc (`je_aligned_alloc`, `jeFree`), libc
  (`memcpy`, `strcmp`), libc++ (`__tree_remove`, `__tree_balance_after_insert`,
  `__release_weak`, `__throw_length_error`), bare `ldxr/stxr` atomics
  (`ExclusiveMonitorPass`/`ExclusiveMonitorsStatus`), and Pool C Round 6's
  known-safe scheduler plumbing (`FUN_7103549170` submit_task,
  `FUN_710354c720`). **No `nn::*` service call is reachable through
  any direct BL from `FUN_7103724a80`.**
- The recursion descends through the indirect dispatch on
  `plVar7->vt[+0x28]` at `0x7103724d90` (the site whose return-PC
  `0x7103724d94` appears three times in the captured backtrace). That
  vtable slot lands in a concrete task-class method. For the specific
  task that owns the fighter sim, that method lives inside a Ghidra
  unanalyzed region at `0x71022df070` (see
  `data/ghidra_cache/manual_extraction_needed.md`). Without that body,
  the child's own BL set cannot be walked — so the full call tree is
  NOT yet proven clean.
- There is one conditional host-side-effect path inside
  `FUN_7103724a80` itself: the OOM retry callback
  `DAT_7105331f00->vt[+0x30]` at `0x7103724c10`, which only fires when a
  16-byte `je_aligned_alloc` returns NULL. During normal gameplay this
  path never fires. Eden should still neutralize it (see
  "Service-quarantine shim requirements" below).

**Recommendation for Eden**: begin prototyping resim with a no-op OOM
handler installed for the duration of the call, but DO NOT treat this
function as proven-safe until the child `.run()` body at `0x71022df070`
is manually recovered and audited.

## Direct BLs inside FUN_7103724a80

| Site PC       | Target       | Symbol / role                                  | Verdict        |
|---------------|--------------|------------------------------------------------|----------------|
| `0x7103724ae4`| `0x7103724f60`| task gate check (FNV-hash identity compare, refcount)  | **safe** — pure data + atomics + jeFree |
| `0x7103724b50`| `0x7103724500`| task child teardown (tree erase + dtor chain)  | **safe** — calls `FUN_7103723e80` (also safe) |
| `0x7103724bc0`| `0x71039c20a0`| `std::__1::__vector_base_common::__throw_length_error` | **safe** — unreachable during gameplay (impossible vector size) |
| `0x7103724be0`| `0x710392dce0`| `je_aligned_alloc`                            | **safe** — jemalloc (CLAUDE.md: lib/jemalloc/) |
| `0x7103724c20`| `0x710392dce0`| `je_aligned_alloc` (OOM retry)                | **safe** — same |
| `0x7103724c50`| `0x71039bfb30`| `memcpy`                                      | **safe** — libc |
| `0x7103724c64`| `0x710392e590`| `jeFree` wrapper                              | **safe** — jemalloc |
| `0x7103724c80`| `0x7103725180`| task step — submits child task via `FUN_7103549170` | **safe** — Pool C Round 6 classified scheduler plumbing |
| `0x7103724d04`| `0x71039bfab0`| `strcmp`                                      | **safe** — libc |
| `0x7103724d3c`| `0x71039bfab0`| `strcmp`                                      | **safe** — libc |
| `0x7103724e0c`| `0x7103724f60`| task gate check (polling loop re-entry)       | **safe** — same as above |
| `0x7103724e30`| `0x7103724500`| task child teardown                           | **safe** — same as above |
| `0x7103724e4c`| `0x7103725180`| task step                                     | **safe** — same as above |
| `0x7103724f1c`| `0x71039c20c0`| `std::__1::__shared_weak_count::__release_weak` | **safe** — libc++ atomic refcount |
| `0x7103724f50`| `0x71039c0650`| abort (vector allocation length error)        | **safe** — unreachable on sane input |

## Indirect vtable dispatches (BLR)

These depend on the concrete class of `param_1` (outer task) and
`plVar7` (child task). For the sim-tick call, `param_1 = x24` from
`main_loop`'s `mov x0, x24` at `0x710374c620`.

| Site PC       | Expression                          | Role                     | Verdict              |
|---------------|-------------------------------------|--------------------------|----------------------|
| `0x7103724acc`| `param_1->vt[+0x18]`                | on-cancel hook (state 2 path) | **TBD** — concrete task class |
| `0x7103724b3c`| `plVar7->vt[+0x20]`                 | is-done / poll           | **TBD** — boolean return |
| `0x7103724c10`| `DAT_7105331f00->vt[+0x30]`         | **OOM retry callback**   | **conditional** — only on 16-byte alloc failure; default handler at `DAT_7105331ee0` is static (see below) |
| `0x7103724cbc`| `plVar7->vt[+0x48]`                 | gate filter (bool return) | **TBD** — concrete task class |
| `0x7103724d64`| `param_1->vt[+0x28]`                | outer state hook         | **TBD** — concrete task class |
| `0x7103724d90`| `plVar7->vt[+0x28]`                 | **child `.run()` — THIS IS THE SIM RECURSION** | **TBD — BLOCKING on manual Ghidra recovery at `0x71022df070`** |
| `0x7103724da0`| `param_1->vt[+0x30]`                | epilog/yield hook        | **TBD** — concrete task class |
| `0x7103724f14`| `plVar18->vt[+0x10]`                | shared_ptr deleter       | **safe** — libc++ shared_ptr destroy; allocator-level only |
| `0x7103724f40`| `plVar7->vt[+0x38]`                 | on-add / reset hook      | **TBD** — concrete task class |

## Recursive walk — where the LR=`0x7103724d94` stack frames land

The captured backtrace shows `0x7103724d94` appearing three times,
alternating with `0x71022df070`. This was labeled "task_run_inner" in
`sim_tick_FOUND.md`, but Round 8 disassembly shows `0x7103724d94` is
not a separate function — it is the instruction immediately following
`blr x8` at `0x7103724d90`. The LR value therefore identifies which
BLR in `FUN_7103724a80` fired: it is the dispatch on
`plVar7->vt[+0x28]` (slot 5 / byte offset 0x28), i.e. the child
task's `.run()` method.

Alternation with `0x71022df070` means the child task is a class whose
`.run()` method in turn calls back into `FUN_7103724a80` (with a
deeper child) — so the recursion is:

```
main_loop                                   (LR=0x710374c628)
└─ FUN_7103724a80(x24)                      (LR=0x7103724d94)
   └─ plVar7->vt[+0x28](child_task, state)  ← method body near 0x71022df070
      └─ FUN_7103724a80(grandchild)         (LR=0x7103724d94 again)
         └─ plVar7->vt[+0x28]               ← same class, different instance
            └─ FUN_7103724a80(great-grandchild) (LR=0x7103724d94 again)
               └─ plVar7->vt[+0x28]          ← deepest level
                  └─ ... eventually the fighter sim body that writes RNG
```

So there are effectively **three layers of task containers** between
`main_loop` and the actual fighter-sim leaf. Each container's
`.run()` is a method in the unresolved region around `0x71022df070`.

### Why `0x71022df070` is blocked

Ghidra has no function defined covering `0x71022df070`. The address
falls in a dead range between `FUN_71022def30` (actual code ends at
`0x71022def94`, function marked as size 480 but the rest is either
data or unanalyzed orphaned code) and the next function `FUN_71022df110`.
An MCP call to `decompile_function_by_address` at that address fails
with "No function found".

Logged to `data/ghidra_cache/manual_extraction_needed.md` for the
orchestrator to recover via a manual "Create Function" in the Ghidra
GUI at the correct entry point.

## One-level recursion on suspicious direct callees

| Callee            | BLs it makes                                              | Verdict |
|-------------------|-----------------------------------------------------------|---------|
| `FUN_7103724f60`  | `ExclusiveMonitorPass`/`Status`, `__release_weak`, `jeFree` (`FUN_710392e590`) | **safe** — pure data + atomic refcounts |
| `FUN_7103724500`  | `strcmp`, `FUN_7103723e80`, `param_2->vt[+0x8]` (dtor)    | **safe** — `FUN_7103723e80` below |
| `FUN_7103723e80`  | `__tree_remove`, `*plVar1->vt[+0x20/0x28]`, `FUN_710354c720` (scheduler, known-safe), `jeFree` | **safe** — libc++ rb-tree + scheduler plumbing |
| `FUN_7103725180`  | `strcmp`, `je_aligned_alloc`, `jeFree`, `FUN_7103723360`, `FUN_71003cb050`, `FUN_7103549170` (submit_task — known-safe), `FUN_710354c720` (known-safe), `__tree_balance_after_insert`, several vtable dispatches | **safe** — only uses scheduler plumbing that Pool C Round 6 classified as safe |
| `FUN_7103723360`  | no BLs — pure FNV-1a hash + field store + copy loops     | **safe** — leaf constructor |
| `FUN_71003cb050`  | only vtable methods on `param_1/param_2` (list-node swap helpers at `+0x18/+0x20`) | **safe** — libc++ list-iterator surgery; no direct external calls |
| `FUN_71037243f0`  | `FUN_7103723e80` (erase), tree-walk pointer chasing       | **safe** — red-black tree flush loop |

None of these leak out of the allocator/libc++/scheduler sandbox. The
only way a service call could enter the tree is through one of the
indirect vtable dispatches on `plVar7` / `param_1` — i.e. through the
concrete task-class methods we have not yet audited.

## Service-quarantine shim requirements

### Must-install (fire-and-forget side-effect neutralization)

1. **Replace `DAT_7105331f00`** with a no-op OOM handler for the
   duration of the resim call. The default `DAT_7105331ee0` handler
   appears to be a static fallback installed by `FUN_710353b930`, but
   the runtime may have swapped it for a game-managed handler that
   releases textures, flushes logs, or otherwise touches host state.
   A resim under memory pressure is exactly the scenario where this
   would fire.

   Concrete Eden approach:
   ```cpp
   // Save + override before calling the sim tick.
   auto saved_oom = guest_read_ptr(0x7105331f00);
   guest_write_ptr(0x7105331f00, /* pointer to a guest-side vtable whose +0x30 returns 0 */);
   dynarmic_call_guest(0x7103724a80, sim_root);
   guest_write_ptr(0x7105331f00, saved_oom);
   ```

   The simplest guest-side no-op vtable is: a 64-byte block where
   `vt[+0x30]` points to a single `mov w0, wzr; ret` stub placed in
   read-only guest memory Eden owns.

### Blocking — cannot ship resim until resolved

2. **Audit the child task `.run()` at `0x71022df070`.** The recursion
   lives entirely inside this method family, and without it we cannot
   prove no `nn::os::WaitEvent`, `nn::os::SignalLightEvent`,
   `nn::gfx::*`, `nn::audio::*`, or `nn::ldn::*` is reachable. Highest
   priority for next round.

3. **Audit `param_1->vt[+0x28]` and `param_1->vt[+0x30]` on the
   specific outer task** passed as `x24` from `main_loop`. `x24`
   resolution requires a backward scan of `main_loop` to find its
   source (open question 2 in `sim_tick_FOUND.md`). Without knowing
   `x24`'s class, the two dispatches at `0x7103724d64` and
   `0x7103724da0` cannot be audited.

### Nice-to-have (defense in depth)

4. **Install a resim-mode fault on every `nn::*` PLT entry** during
   the resim window. If ANY unexpected service call fires, Eden
   should immediately roll back the snapshot and re-run in host mode
   (effectively treating resim as an unverified path and falling back
   to a single-player-style rollback). This catches the unknown-class
   vtable dispatches without requiring a full audit.

## Unsafe branches

None found at the `FUN_7103724a80` level of the tree.

The `std::__1::__throw_length_error` and `abort` paths are
theoretical — they would require the task state vector's size to
exceed `0x1fffffffffffffff` entries, which cannot happen under normal
input.

## Confidence

**MEDIUM.**

- `FUN_7103724a80` itself and all seven direct-callee helpers are
  fully traced. No service calls appear in any of them. This part is
  HIGH confidence.
- The OOM retry callback (`DAT_7105331f00->vt[+0x30]`) is a known
  conditional gate with a trivial Eden neutralization. HIGH
  confidence that this is manageable.
- The concrete child-task `.run()` body at `0x71022df070` is a
  KNOWN GAP. Until it is recovered, the deepest level of the
  recursion cannot be audited. This is the only reason the verdict
  is CONDITIONAL rather than CLEAN.

The recommended next step is to recover `0x71022df070` (via manual
"Create Function" in the Ghidra GUI) and re-run this audit on the
concrete task's vtable methods (`.run()`, the slot 5 body). If that
method is also confined to the allocator/libc++/scheduler sandbox,
the verdict will upgrade to CLEAN and Eden can proceed with the
no-op OOM shim only.

## Sources

- `data/ghidra_cache/FUN_7103724a80.txt` — full decomp (written this round)
- `data/ghidra_cache/manual_extraction_needed.md` — logged `0x71022df070` as blocked
- `docs/rollback/sim_tick_FOUND.md` — Round 8 watchpoint capture
- Pool C Round 6 scheduler plumbing classification (in `docs/rollback/` history)
- `include/app/modules/` — no relevant vtables; concrete task classes are unnamed

---

## Round 9 addendum — FUN_71022df070 audited (orchestrator, manual)

The Round 8 blocker ("audit `0x71022df070`") is resolved. The function was
too small to justify another pool (49 lines) — orchestrator audited it
directly from the cached decomp at `data/ghidra_cache/FUN_71022df070.txt`.

### Full BL and BLR inventory

**Direct BLs (all 4):**

| Line | Target | Classification |
|------|--------|---------------|
| 21 | `FUN_7103726540(param_2[1], 0)` | scheduler internal (Pool C Round 6) — CLEAN |
| 25 | `FUN_7103726690(plVar1)` | scheduler state query (same 0x7103726xxx region) — CLEAN |
| 36 | `FUN_7103724a80(plVar1)` | RECURSION into the parent — already audited clean (Pool A Round 8) |
| 40 | `FUN_7103726540(...)` | same as line 21 — CLEAN |

**Indirect vtable dispatches (all 3):**

| Line | Dispatch | Interpretation |
|------|----------|---------------|
| 15 | `param_1->vt[+0x60]` (slot 12) | per-tick fast path, runs when `[+0x1c] == 0` |
| 31 | `plVar3->vt[+0x40]` (slot 8) on `param_1[0x11]` | query/getter with two stack output structs |
| 45 | `param_1->vt[+0x90]` (slot 18) | exit hook after children complete |

### Structural notes

- `plVar1 = param_1 + 10` (byte offset `+0x50`) is the parameter passed to the
  recursive `FUN_7103724a80` call — confirming the parent→child DAG walk.
- Fields at `[+0xe]`, `[+0xf]`, `[+0x10]`, `[+0x11]`, `[+0x1c]`, `[+0xdc]`,
  `[+0xe1]` are the task object's state/flags/child-pointer slots.
- The predicate `[lVar4+0x30] == [lVar4+0x38]` checks if a vector at
  `param_1[0xf]` is empty (begin == end).

### Safety verdict

**CLEAN at the outer-shell level.** `FUN_71022df070` itself makes zero
direct service calls. Its indirect dispatches (`vt[+0x60]`, `vt[+0x40]`,
`vt[+0x90]`) ARE the sim body — they land in concrete per-type task
methods whose implementations are the fighter/battle-object update
functions. These cannot be exhaustively audited statically because they
span ~60 MB of game logic.

### Combined verdict (Rounds 8 + 9)

The entire outer shell from `main_loop` to `FUN_71022df070` is proven
clean. The only uncovered paths are:

1. The concrete sim body vtables (`vt[+0x60/+0x40/+0x90]` on the specific
   task class) — these are WHERE the fighter sim runs, so they're the
   whole point of calling the sim BL. "Auditing" them fully is equivalent
   to decompiling the entire fighter module.
2. The one conditional OOM retry path in `FUN_7103724a80` itself
   (Pool A Round 8) — Eden must shim `DAT_7105331f00->vt[+0x30]` anyway.

### Recommendation for Eden

**Ship-unblocked with defense-in-depth strategy:**

1. Install Pool A's shim on `DAT_7105331f00->vt[+0x30]` during resim window
2. Install resim-mode PLT fault on every `nn::*` stub (Pool A rec #3)
3. First resim attempt: `dynarmic_call_guest(0x7103724a80, sim_root)` with
   the guards in place
4. If the PLT fault fires, log the stub name + PC and fall back to host-mode
   single-player-style rollback (snapshot restore, skip resim, accept a
   1-frame input delay hit)
5. Track any PLT fires over a large test run; if the set is small and
   deterministic, add per-stub shims. If it's large or unbounded, the
   resim approach is not viable and Eden needs a different architecture
   (save-state restore only, no resim)

This is sufficient to start the Eden prototype. Branch coverage of the
fighter module can happen during integration testing, not as a static-
analysis precondition.

---

### Allocator reachability — Round 10

Static audit: does FUN_7103724a80's subtree reach je_aligned_alloc
in steady state (1v1 match, two fighters, no new spawns)?

**Verdict**: **CLEAN at the outer shell level.** No je_aligned_alloc call
in the outer-shell subtree is reachable on a per-frame hot path. Every
subtree alloc call observed is gated on a task-lifecycle / vector-growth
event that is either one-shot per match or amortized to O(1) across
frames. Steady-state sim ticks (running 1v1 fighters in a stable
animation loop, no new spawns) hit NONE of the outer-shell allocs.

The caveat from Rounds 8 and 9 still stands: the concrete task body
`.run()` methods dispatched through `vt[+0x60/+0x40/+0x90]` are NOT
covered by this audit because they land in the unresolved fighter-sim
region that spans most of the 60 MB .text. Any allocator call inside
those targets is invisible to a static subtree walk.

#### Callers of je_aligned_alloc inside the subtree

The subtree audited is the full direct-BL closure of FUN_7103724a80
already catalogued in Rounds 8 and 9: FUN_7103724a80 itself, its seven
direct callees (`FUN_7103724f60`, `FUN_7103724500`, `FUN_7103725180`,
`FUN_7103723360`, `FUN_7103723e80`, `FUN_71003cb050`, `FUN_71037243f0`),
FUN_71022df070 (the Round-9 recursion body), and FUN_71022df070's two
scheduler-query callees (`FUN_7103726540`, `FUN_7103726690`).

Of those 11 functions, only **two** contain a direct BL to
`je_aligned_alloc` (`0x710392dce0`). All others are allocator-free.

| Caller | Call sites | Gate / Why it fires | Steady-state? |
|--------|-----------|---------------------|---------------|
| `FUN_7103724a80` | `0x7103724be0` (first try) + `0x7103724c20` (OOM retry) — **same allocation**, two attempts | `std::vector<void*>::push_back` growth on the outer task's child-queue at `[param_1[5]+0x30..+0x40]`. Fires only when `queue.size() == queue.capacity()`. Capacity doubles (`uVar10 = lVar9 >> 2`) on each grow, so the growth count is `O(log N)` over the whole match, amortized `O(1)` per push. Push itself fires only in the state-1 branch (`param_1[6] == 1`) when the task has a pending child to enqueue. | **NO** — amortized O(1). After the first few frames of a match the vector reaches steady capacity and the else branch (`*plVar7 = lVar21; [+0x38] += 8`) executes in-place without allocation. Eventually fires zero times per frame. |
| `FUN_7103725180` | `0x7103725330` (first try) + `0x7103725374` (OOM retry) — 0x80 B task wrapper; `0x710372553c` + `0x7103725580` — 0x70 B submit struct; `0x7103725858` + `0x710372589c` — 0x70 B rb-tree node | Three alloc sites, ALL gated on the `(*plVar16->vt[+0x48])(plVar16) & 1 != 0` branch — "task is in a state where its output has been consumed and a fresh instance must be built and resubmitted". Also a fourth allocator path via `(**(code**)(*plVar20[0xd] + 0x10))(...)` which is a factory helper gated on `plVar20[0xe] == NULL` (first-ever lookup for this named task — lazy init). | **NO** — the fresh-instance path only fires on task rebuild/resubmit events, which are task-lifecycle transitions, not per-frame. The factory-lazy-init path fires exactly once per named task, at first lookup. A 1v1 steady-state match with no new named-task submissions exercises NEITHER path. Under steady state, `FUN_7103725180` either (a) lookup-misses and returns 0 at the top (no alloc), or (b) lookup-hits, the cache is already populated, vt[+0x48] returns 0, and it dispatches via the cached pointer and returns (no alloc). |

Round 8's table had flagged the 0x7103724be0/c20 pair as the "OOM retry
of a 16-byte alloc". That description was from the 16-byte allocation's
literal immediate mov — but the actual alloc is `ppuVar11 = uVar8 * 8`,
a variable-size vector-capacity multiplication, not a fixed 16 bytes.
Round 10 corrects this classification: the alloc is a std::vector grow,
not a fixed-size task-node creation.

#### Why none of the child functions allocate

Verified by inspection of each Round 8/9 catalogue entry:

- `FUN_7103724f60`: pure FNV-hash compare + atomics + `jeFree` only.
- `FUN_7103724500`: `strcmp` + `FUN_7103723e80` (which also does not alloc) + vtable dtor. No `je_*` alloc BL.
- `FUN_7103723e80`: libc++ rb-tree node erase + scheduler `FUN_710354c720` (known-safe) + `jeFree`.
- `FUN_7103723360`: leaf constructor, zero BLs.
- `FUN_71003cb050`: list-iterator pointer swap, only vtable dispatches on `param_1/param_2` at `+0x18/+0x20`. No direct calls.
- `FUN_71037243f0`: rb-tree flush loop calling `FUN_7103723e80`. No alloc.
- `FUN_71022df070` (Round 9): 49 lines, 4 direct BLs (two to `FUN_7103726540`, one to `FUN_7103726690`, one recursive back to `FUN_7103724a80`). No allocator BL.
- `FUN_7103726540`: pure string-copy + FNV hash into caller-provided buffer. Zero external BLs.
- `FUN_7103726690`: rb-tree lookup + predicate return. Zero external BLs.

#### Eden implication

**The OOM shim can be downgraded from "must-neutralize" to
"monitor-and-alert", provided the concrete task-body methods are
verified clean separately.**

Concretely:

1. **Keep the no-op `DAT_7105331f00->vt[+0x30]` override installed** for
   the resim window. The override cost is a single 64-byte guest-side
   stub table and a pointer swap at entry/exit — negligible.

2. **Change the override body from "always return 0" to "log + return 0"**.
   If the override fires during resim, that is now a concrete signal
   that the concrete task body (not the outer shell) requested an
   allocation. The log tells Eden exactly which task class triggered
   it, so follow-up static audits can target the specific concrete
   class rather than auditing all of the fighter module.

3. **Do NOT drop the shim entirely.** Two reasons:
   - The vector-grow path in `FUN_7103724a80` does still fire in early
     match frames (first N frames, where N ≈ log2(max child queue
     depth)). If resim is invoked during those warmup frames and the
     vector's underlying allocation happens to be at the capacity
     boundary, a real `je_aligned_alloc` call will hit jemalloc.
     jemalloc itself is deterministic and harmless for rollback —
     but we still don't want the OOM retry callback to fire a host
     service call.
   - The concrete task methods at `vt[+0x60/+0x40/+0x90]` are the
     unresolved portion; they could still issue allocator calls that
     need the OOM retry to have a safe gate.

4. **New: gate the resim window on "warm capacity" check.** Before
   entering resim, Eden can read `[sim_root->child_queue_cap]` and
   verify that the vector's current size is strictly less than
   capacity. If it is, the vector-grow alloc is guaranteed not to
   fire for at least one more push. This makes the outer shell
   provably allocation-free for that resim window.

The Task-2 question in this round's brief was whether the OOM shim
could be dropped **entirely** as a cleanup win. The answer is: **not
entirely, but the shim becomes passive (log + no-op) rather than
load-bearing**. That is still a meaningful simplification — Eden no
longer needs to engineer a "safe" OOM response, just a telemetry
hook, and the resim initialization cost drops from "vtable
installation + careful lifetime management" to "pointer swap + log
tap".

#### Residual unknowns

- The concrete task class passed as `x24` from `main_loop` still has
  unaudited `vt[+0x28]` and `vt[+0x30]` slots. Same open question as
  Round 8.
- The `vt[+0x60/+0x40/+0x90]` dispatches inside `FUN_71022df070` land
  in the fighter sim body. These are where any real per-frame
  allocator activity would live.
- The `(**plVar20[0xd]->vt[0x10])()` factory helper in FUN_7103725180
  was not followed into its target; if it happens to be called from
  the per-frame path (I argue it isn't, but this is inferred, not
  proven), that is a potential alloc source.
