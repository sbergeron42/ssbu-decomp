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
