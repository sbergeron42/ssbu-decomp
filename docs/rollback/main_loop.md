# `main_loop` @ 0x7103747270 — dispatch skeleton for rollback research

**Scope.** This document maps the top-level function at `0x7103747270` (24,424 bytes, Ghidra: `FUN_7103747270`) so that a rollback-netcode fork can identify which sub-calls constitute "advance one simulation tick" and which are render/audio/UI/housekeeping work that must be skipped during resimulation.

**TL;DR / critical finding.** `main_loop` at `0x7103747270` is the **presentation-side frame loop**, not the fighter-simulation dispatcher. It handles `nn::oe` system notifications, dock/handheld mode switches, particle-effect dt advance, per-slot input history recording, scene-state transitions, camera view/projection matrix recomputation, the resource-streaming pump, and 4 async resource-loader `Update` ticks. **None** of the BL targets reached directly from `main_loop` iterate the `FighterManager` / `BattleObject` list or dispatch per-fighter module updates (no +0x38..+0x188 vtable calls on `BattleObjectModuleAccessor*`). The real "advance one fighter frame" call is *not* a direct child of this function — see [§ open questions](#open-questions-for-the-next-pass) below.

---

## 1. Prologue and frame bookkeeping

The function reserves a very large stack frame (`0x20a0` bytes) and saves all callee-saved GPRs + `d8..d15`:

```
7103747270: stp d15,d14,[sp, #-0xa0]!
...
7103747290: stp x20,x19,[sp, #0x80]
7103747294: stp x29,x30,[sp, #0x90]
7103747298: add x29,sp,#0x90
710374729c: sub sp,sp,#0x2, LSL #12        ; +0x2000 locals
```

Early-prologue calls (presentation setup):

| Addr | Target | Purpose |
| --- | --- | --- |
| `71037472bc` | `FinishStartupLogo` (`0x71039c7670`) | `nn::oe` boot-logo teardown |
| `71037472c0` | `GetOperationMode` (`0x71039c7570`) | handheld vs docked query |
| `7103747310` / `7103747510` | `FUN_71037cbb80` (x2) | dock/handheld mode-change notification handler — pops `nn::oe::TryPopNotificationMessage` and on notif `0x1E` swaps the target framebuffer between `1280×720` (handheld) and `1920×1080` (docked). **100% presentation.** |
| `710374755c` | `FUN_710354c720` | locker helper |
| `7103747570..7103747a48` | `GetSystemTick` (`0x71039c0200`), `ConvertToTimeSpan` (`0x71039c06d0`), `lock_*`, `unlock_*`, `je_aligned_alloc`, `free_default` | Elapsed-time sampling + scratch allocation for this frame. |

### Presentation-frame counter (atomic)

```
7103747bc8: ldr w8,[sp, #0x270]      ; delta (ticks since last sample)
7103747bcc: add w8,w8,#0x1
7103747bd0: ldaxr w9,[x20]           ; atomic load from global @ x20
7103747bd4: add w9,w9,w8
7103747bd8: stlxr w10,w9,[x20]       ; release-store back
7103747bdc: cbnz w10,0x7103747bd0
```

`x20` is a global atomic counter set up from the prologue's `adrp` block; the value added is a **tick delta** (not a constant `+1`), so this is an **elapsed-frame-ticks accumulator**, not a simple "one per iteration" counter. It is consistent with the presentation-layer having a dt-weighted counter rather than a fixed-step sim counter.

> **Rollback implication.** This is *not* a safe simulation-frame counter to drive rollback indexing. Look for a fixed-step `+1` counter elsewhere (most likely on the `GameManager`/`FighterManager` singleton). See [§ open questions](#open-questions-for-the-next-pass).

---

## 2. Dispatch skeleton (high level)

Walking the 274 direct `BL` sites (84 unique targets) in execution order, `main_loop` breaks into roughly these phases:

| Phase | Addr range | What runs |
| --- | --- | --- |
| 1. Boot/mode check | `7103747270..71037475xx` | Boot-logo retire, operation-mode query, handheld↔docked handler |
| 2. Frame timing | `7103747570..7103747a50` | `GetSystemTick`, event wait/signal, atomic counter add, scratch alloc |
| 3. Singleton fetch & lua GC | `7103747b0c..7103747bc4` | `luaC_step` (`0x71038fe690`) incremental Lua GC, `notify_all` |
| 4. `Instance` singletons | `7103747f0c..71037491b8` | `Instance` (`0x71002c48f0` ×2, `0x71002c51f0`), `FUN_71002c51f0`, guard fetch |
| 5. Early subsystem locks + updates | `71037493xx..710374a07x` | 5× `lock`/`unlock` pairs around `FUN_7103549170`, 4× `FUN_7103550080` (string-keyed hash map lookups), 2× `FUN_7103593c40`, `FUN_71035763c0` (×12), `FUN_7103575c60` (×2), `FUN_7103575fa0` (×4) |
| 6. Scene/state machine | `710374af50..710374af6c` | `FUN_7103632850` (4268 B — scene/UI panel state transition), `FUN_710361e7e0`, `FUN_71035c13d0` |
| 7. Subsystem block A | `710374b100..710374b124` | `FUN_710361d040` (camera view-matrix update, **pure math**), `FUN_71036186d0`, `FUN_7103864700`, `FUN_7103619080` |
| 8. Rate-limited subsystem | `710374b178..710374b238` | `try_lock`, `FUN_71036f2c00`, `FUN_71036e6e00`, `FUN_71036f2d40` (wrapped in a `60/divisor` rate-limit check — see [§ rate-limited counter](#rate-limited-sub-counter)) |
| 9. ⭐ **Pre-controller big pass** | `710374b4a4` | `FUN_710356d7a0` (10,880 B) — particle/effect-system dt advance (dt accumulator at `[x0+0x268]`, `CreateEmitterSetId`/`KillEmitterSet`) |
| 10. 3× `lock/unlock` | `710374b4f4..710374b5cc` | `FUN_7103549170` ×3 interleaved with `FUN_710354c720` ×3 |
| 11. **Per-slot input history recording** | `710374bd9c..710374bfe8` | `FUN_71037857f0` ×10 — one call per slot index `0..9`, each writes sampled input into a per-slot replay buffer at `param_1 + slot*0x18 + 0x18`. See [§ input recording](#input-recording-11-slots) |
| 12. ⭐ **Post-controller big pass** | `710374bff8` | `FUN_710355b540` (16,424 B) — **resource streaming pump**: 41× `je_aligned_alloc`, 24× `free_default`, 3× `load_file_by_hash40`, `ClearResource`, `UnregisterTextureViewFromDescriptorPool`, resource hash-map eviction |
| 13. Scene-kind dispatch | `710374c028..710374c10c` | `FUN_710354c720`, `FUN_7103549170`, `FUN_7103569c70` (1,320 B — resets 200+ float slots to `0xC2C80000` = sentinel, gated on `param_1+0x568c` byte) |
| 14. **4× async resource-loader `Update` + repoll** | `710374c2dc..710374c74c` | 4 invocations of `FUN_7103724a80` ("`Update`" — an async resource loader state machine: FNV-1a hash + RB-tree lookup by filename + `je_aligned_alloc` grow + vtable dispatch at `+0x38` / `+0x48`). Each Update is bracketed by `get_inputs_for_all_controllers` (`0x71036676e0`) + `deal_with_inputs?` (`0x710375ea70`) — **the inputs are re-sampled up to 4× per main-loop iteration.** |
| 15. Post-update helpers | `710374c7d0..710374c990` | `FUN_71039c21b0` lock, `FUN_710375f650` (3,132 B), `FUN_710007f7d0`, `je_aligned_alloc` ×2 |
| 16. Epilogue + exception paths | `710374caa4..710374d1d4` | `FUN_71003cb050`, `FUN_71000803c0`, `FUN_71036f7410` ×2, 13× `__cxa_guard_acquire`/`release` pairs (first-use static init), 2× `FUN_71037c34c0` + `recursive_mutex` pair, 2× `__cxa_allocate_exception` → `logic_error` → `__cxa_throw` error paths, final `bl 0x71039c20a0` (`abort` — unreachable fault path) |

---

## 3. Sim vs. presentation classification table

The 84 unique BL targets, classified. `sim?` is a best-guess: `sim` = game-state mutation that rollback must re-run; `present` = render/audio/UI/housekeeping that must be skipped on resim; `neutral` = allocator/locking/lib that doesn't need re-evaluation as a unit but may be called from either side; `unknown` = not investigated deeply enough to classify with confidence.

| Addr | Name (CSV or derived) | Size | Calls | Category | Notes |
| --- | --- | --- | --- | --- | --- |
| `0x71039c7670` | `FinishStartupLogo` | 16 | 1 | present | nn::oe SDK |
| `0x71039c7570` | `GetOperationMode` | 16 | 1 | present | nn::oe SDK — docked/handheld |
| `0x71037cbb80` | `handle_nn_oe_notification` (derived) | 312 | 2 | present | mode-switch framebuffer update |
| `0x710354c720` | `FUN_710354c720` | 544 | multiple | unknown | locker/helper utility |
| `0x71039c1490/0x71039c14a0` | `lock_*/unlock_*` | 16 ea | many | neutral | mutex pair |
| `0x71039c0200` | `GetSystemTick` | 16 | many | present | timebase sampling |
| `0x71039c06d0` | `ConvertToTimeSpan` | 16 | many | present | tick→ns |
| `0x71039c06c0` | `WaitEvent` | 16 | 1 | present | vsync/event wait |
| `0x71039c06f0` | `SignalEvent` | 16 | 1 | present | vsync wake |
| `0x710354ce10` | `FUN_710354ce10` | 704 | 1 | unknown | scene helper |
| `0x7103726690` | `FUN_7103726690` | 316 | 1 | unknown | |
| `0x71039c0200/06d0` | `GetSystemTick`+`ConvertToTimeSpan` | 16 | many | present | |
| `0x710372b450` | `FUN_710372b450` | 716 | 1 | unknown | |
| `0x710392e590` | `free_default` (jemalloc) | 220 | many | neutral | allocator |
| `0x710392dce0` | `je_aligned_alloc` | 152 | many | neutral | allocator |
| `0x71039c20c0` | `__release_weak` | 16 | many | neutral | libc++ refcount |
| `0x71038fe690` | `luaC_step` | 420 | 1 | neutral→sim | Lua **incremental GC** — is run per frame but state mutation is deterministic given seed; rollback must re-run only if the Lua heap is part of rollback state. Recommend treating as sim. |
| `0x71002c48f0` | `Instance` (singleton) | 200 | 2 | neutral | singleton accessor |
| `0x71002c51f0` | `FUN_71002c51f0` | 464 | 1 | unknown | singleton ctor path |
| `0x71039c1400` | `VirtualFreeHook` | 16 | 2 | neutral | allocator hook |
| `0x71036eb680` | `FUN_71036eb680` | 520 | 1 | unknown | |
| `0x7103871c90` | `FUN_7103871c90` | 164 | 1 | unknown | |
| `0x71039bfcf0` | `memset` | 16 | 1 | neutral | |
| `0x7103549170` | `FUN_7103549170` | 712 | 5 | unknown | appears inside locked regions |
| `0x7103550080` | `unordered_map::find(string)` (derived) | 496 | 4 | unknown | hash-map lookup — 4 keys resolved |
| `0x7103618ef0` | `FUN_7103618ef0` | 388 | 2 | unknown | |
| `0x7103593c40` | `FUN_7103593c40` | 792 | 1 | unknown | |
| `0x7103575c60` | `FUN_7103575c60` | 824 | 2 | unknown | |
| `0x7103575fa0` | `FUN_7103575fa0` | 960 | 4 | unknown | called 4×, likely per-player |
| `0x71035763c0` | `FUN_71035763c0` | 572 | **12** | unknown | most-called unique site — per-fighter/per-slot update? |
| `0x710361f4a0` | `FUN_710361f4a0` | 728 | 1 | unknown | |
| `0x71039c1410/0x71039c1420` | `lock_*/unlock_*` pair | 16 | many | neutral | |
| `0x7103632850` | `scene_state_machine` (derived) | 4,268 | 1 | present | 3-state (0/1/2) transition setting UI panel `is_active`/`is_valid` flags, walks 4 panel slots, applies FixedString-keyed layout message updates (`VSM_SRV_IPLUG`) |
| `0x710361e7e0` | `FUN_710361e7e0` | 304 | 1 | unknown | |
| `0x71035c13d0` | `FUN_71035c13d0` | 1,048 | 1 | unknown | |
| `0x710361d040` | `camera_view_matrix_update` (derived) | 2,168 | 1 | present | view/projection matrix recompute — pure NEON math over camera list at `param_1+0x490`; calls `FUN_7103554b90` on dirty-flag cameras |
| `0x71036186d0` | `FUN_71036186d0` | 1,188 | 1 | unknown | |
| `0x7103864700` | `FUN_7103864700` | 172 | 1 | unknown | |
| `0x7103619080` | `FUN_7103619080` | 432 | 1 | unknown | |
| `0x71039c5b20` | `try_lock` | 16 | 1 | neutral | |
| `0x71036f2c00` | `FUN_71036f2c00` | 320 | 1 | unknown | rate-limited branch |
| `0x71036e6e00` | `FUN_71036e6e00` | 168 | 1 | unknown | |
| `0x71036f2d40` | `FUN_71036f2d40` | 320 | 1 | unknown | rate-limited branch |
| `0x710356d7a0` | `effect_system_tick` (derived) | 10,880 | 1 | present→sim | **particle effects dt advance**: 332 float ops, `CreateEmitterSetId`/`KillEmitterSet`, dt accumulator at `[x0+0x14]→[x0+0x268]`. In SSBU particles are gameplay-relevant (hit sparks, shields), but effect-system state is not usually rolled back. Recommend skipping on resim. |
| `0x7103618b80` | `FUN_7103618b80` | 368 | 1 | unknown | |
| `0x71037857f0` | `input_history_record_slot` (derived) | 656 | **10** | **sim** | See [§ input recording](#input-recording-11-slots). 10 calls = 10 slot indices 0..9. Rollback needs these buffers in its state capture. |
| `0x710355b540` | `resource_streaming_pump` (derived) | **16,424** | 1 | present | 41× `je_aligned_alloc`, 24× `free_default`, `load_file_by_hash40` ×3, `ClearResource`, `UnregisterTextureViewFromDescriptorPool`, hash-map eviction. Resource streaming is not part of rollback state; skip on resim. |
| `0x710355b540`→`0x7103569c70` | `stat_slots_reset` (derived) | 1,320 | 1 | present | resets ~200 float slots to `-100.0f` sentinel — debug stats / on-screen overlay |
| `0x7103724a80` | `ResourceLoaderTask::Update` (derived) | 1,236 | **4** | present | async resource loader state machine — FNV-1a hash, RB-tree lookup, `je_aligned_alloc` grow, 4 parallel loader instances |
| `0x71036676e0` | `get_inputs_for_all_controllers` | 2,476 | 2 | **sim** | polls HID/npad; this is what rollback needs to override during resim |
| `0x710375ea70` | `input_dispatch_to_consumers` (renamed from `deal_with_inputs?`) | 2,572 | 2 | **sim** | walks registered input consumers, increments `[singleton+0x398]` counter, dispatches input via vtable `+0x1c8`/`+0xf8`/`+0x288`/`+0x178` |
| `0x710375f650` | `FUN_710375f650` | 3,132 | 1 | unknown | |
| `0x710007f7d0` | `FUN_710007f7d0` | 160 | 1 | unknown | |
| `0x71003cb050` | `FUN_71003cb050` | 312 | 1 | unknown | |
| `0x71000803c0` | `FUN_71000803c0` | 296 | 1 | unknown | |
| `0x71036f7410` | `FUN_71036f7410` | 1,952 | 2 | unknown | |
| `0x71039c0100/0x71039c0110` | `__cxa_guard_acquire/release` | 16 ea | 13 pairs | neutral | first-use static init |
| `0x71000001c0` | `FUN_71000001c0` | 8 | 3 | unknown | likely a static-init thunk |
| `0x71037c34c0` | `FUN_71037c34c0` | 428 | 2 | unknown | |
| `0x71039c2160` | `recursive_mutex_ctor` | 16 | 2 | neutral | |
| `0x71039c6690` | `__cxa_allocate_exception` | 16 | 2 | neutral | error path |
| `0x71039c5960` | `logic_error` ctor | 16 | 2 | neutral | error path |
| `0x71039c66a0` | `__cxa_throw` | 16 | 2 | neutral | error path |
| `0x71039c20a0` | `abort` | 16 | 1 | neutral | terminal |
| `0x71039bfac0` | `strlen` | 16 | 1 | neutral | |
| `0x71039bfb30` | `memcpy` | 16 | 1 | neutral | |
| `0x71039bfca0` | `memcmp` | 16 | 1 | neutral | |
| `0x71039c1400` | `VirtualFreeHook` | 16 | 2 | neutral | |
| `0x71039c2100` | `ShowError` | 16 | 2 | present | error UI |
| `0x71039c2150` | `tanf` | 16 | 1 | neutral | libm |
| `0x71039c5d90` | `Initialize_71039c5d90` | 16 | 1 | unknown | |
| `0x71039c67b0` | `notify_all` | 16 | 1 | neutral | condvar |
| `0x71039c6d10` | `Finalize_71039c6d10` | 16 | 1 | unknown | |
| `0x71039c7680` | `SaveAndShareScreenshot` | 16 | 1 | present | |
| `0x71039c7690` | `SaveScreenshotWithUserData` | 16 | 1 | present | |
| `0x71039c76a0` | `SaveScreenshot` | 16 | 1 | present | |
| `0x71039c21b0` | `lock_71039c21b0` | 16 | 1 | neutral | |

**Summary counts** (unique targets): 10 present, 4 sim (borderline), 20 neutral, ~50 unknown. **No direct `FighterManager` / `BattleObject` iteration is visible at this level** — the actual per-fighter frame advance lives below or alongside this function, not inside its direct children.

---

## 4. Tick-advance call: NOT directly in `main_loop`

The assignment asked for "the specific call(s) that constitute advance one frame". **The honest answer is that no direct child of `main_loop` matches the signature of a fighter-sim tick** (i.e., iterate `FighterManager` → per-fighter `StatusModule::exec` → `MotionModule::exec` → `KineticModule::update` → `GroundModule::update` → etc.).

The evidence:

- The two biggest sub-calls — `FUN_710356d7a0` (10 KB) and `FUN_710355b540` (16 KB) — are **particle/effect dt advance** and **resource streaming pump** respectively. Neither calls `FighterManager::update` or per-module `+0x38..+0x188` vtable dispatch on a `BattleObjectModuleAccessor`.
- The 4× `Update` pattern at `710374c2dc..710374c74c` initially looks like a per-fighter update, but `FUN_7103724a80` decompiles to an **async resource-loader state machine** (FNV-1a filename hash, RB-tree lookup, vector grow). The `get_inputs_for_all_controllers` + `deal_with_inputs?` interleaving is **input re-polling for latency reduction**, not per-fighter dispatch.
- `FUN_71037857f0` (the 10× call) is **input history recording** — it takes a slot index 0..9 and writes sampled input into a per-slot replay buffer. This is *input capture*, not sim state advance.
- No sub-call observed iterates a 4- or 8-element container of game entities and calls a common `update` method.

**Working hypothesis.** `main_loop` is the **presentation / video-frame loop**. Simulation likely runs on a **separate worker thread** kicked off by `SignalEvent` at `0x71039c06f0` and waited on with `WaitEvent` at `0x71039c06c0` — both of which are called here. This is the standard Nintendo Switch cross2app pattern: the main thread drives SDK/present/resource streaming while a sim worker thread advances game state under an event-driven contract.

### How to confirm the hypothesis (next-pass work)

1. **Find the sim worker thread entry.** Search `xref_to` on `nn::os::CreateThread` / `StartThread` and look for a thread body that *does* iterate `FighterManager`. See `docs/rollback/` for future files.
2. **Decompile `FUN_71036f2c00` / `FUN_71036f2d40`** (the rate-limited branch wrapped in `60 / divisor`). The divisor pattern suggests one of them may be the 60 Hz fixed-step sim tick gate. If either calls into `BattleObject` iteration, we have our answer.
3. **Decompile `FUN_71035763c0`** (called **12×** — the single most-repeated unique target). 12 calls with different args is suspicious for a per-entity dispatch.
4. **Cross-check `DAT_710593aa90`** (the global singleton referenced by `FUN_710375ea70` at offset `[0x73]` = +0x398, where a counter is incremented). If that singleton is `GameMain` or similar, `[0x398]` is likely a "input dispatch count" frame counter, not a sim-frame counter, but worth verifying.

---

## 5. Frame counter(s)

Three increment sites observed **directly inside `main_loop`**:

| Site | Pattern | What it is |
| --- | --- | --- |
| `7103747bd0..bdc` | atomic `ldaxr`/`add w8+delta`/`stlxr` on global at `x20` | **Elapsed-ticks accumulator** (delta-weighted, not `+1`). Presentation-layer timebase. **Not safe as a rollback index.** |
| `710374afc0..afcc` | `add w8,w8,#1; cmp #4; str w8,[x21, #0x20]` | **Retry counter capped at 4** on a linked-list node removal. Not a frame counter. |
| `710374b270..b278` | `ldr w8,[x25, #0x188]; add w8,w8,#1; str w8,[x25, #0x188]` | **Sub-counter** inside the rate-limited branch at phase 8. Adjacent code at `710374b194` does `orr w9,wzr,#0x3c; sdiv w8,w9,w8` — a `60 / divisor` computation — so `[x25+0x188]` is a sub-tick counter into a rate-limited subsystem, gated by `[x25+0x17c]` (divisor) and `[x25+0x18c]` (denom). Useful for identifying *that* subsystem's tick rate, but this is **not** a fighter-sim frame counter. |

**One indirect counter** observed via `FUN_710375ea70` (`input_dispatch_to_consumers`, called 2× per main_loop iteration):

```c
plVar26 = (long *)*DAT_710593aa90;     // global singleton
plVar26[0x73] = plVar26[0x73] + 1;     // +0x398: input-dispatch counter
```

This is a fixed `+1` per call, and `input_dispatch_to_consumers` is called 2× per `main_loop` iteration → counter advances by 2 per present frame. **Not** safe as a 1:1 sim-frame index, but a candidate anchor for future investigation: if `DAT_710593aa90` is the `InputManager` / `GameMain` singleton, `[+0x398]` is its "frames processed" counter.

### Rate-limited sub-counter

The 60 Hz divisor pattern at `710374b190..b1c8`:

```
710374b190: ldr w8,[x25, #0x17c]        ; tick divisor N
710374b194: orr w9,wzr,#0x3c            ; 60
710374b198: sdiv w8,w9,w8               ; 60 / N
710374b19c: ldr w9,[x25, #0x18c]        ; denominator state
710374b1b4: ldr w10,[x25, #0x188]       ; sub-tick counter
710374b1b8: add w9,w9,#0x1
710374b1bc: mul w8,w9,w8
710374b1c0: udiv w9,w10,w8              ; counter / scaled
710374b1c4: msub w8,w9,w8,w10           ; remainder
710374b1c8: cbz w8,0x710374b238         ; on zero, call FUN_71036f2d40
```

This is "call `FUN_71036f2d40` every `((denom+1) * (60/N))` sub-ticks" — classic rate-limited decoration task. The subsystem `x25` is reached via the prologue's `bl 0x71039c5b20` (`try_lock`) so it is a locked global, likely an audio / voice / subtitle scheduler.

---

## 6. Input recording (11 slots)

`FUN_71037857f0` is called 10 times at `710374bd9c..710374bfe8` with slot index `0..9`. Each call records the current sampled input into a per-slot replay buffer. Relevant decompiler output:

```c
if (9 < param_2) abort();                              // slot index guard 0..9
lVar5 = param_1 + (long)(int)param_2 * 0x18;
if (*(long *)(lVar5 + 0x18) == *(long *)(lVar5 + 0x20)) return;   // buffer empty
...
plVar4 = *(long **)(param_1 + (long)(int)param_2 * 8 + 0x330);
...
// path A (replay-serialize): calls FUN_710363f4a0 with PTR_LAB_710522ed88,
//   then FUN_710381ba20/bde0/bc00/b8a0 on lVar5 and appends to plVar6 via vtable +0x18
// path B (reset): zeroes *(lVar5+0x4a0) and advances lVar5+0x3f0/0x418/0x4a0 to next slot
```

**Derived layout for `InputHistoryManager` (`param_1`)**:

```cpp
struct InputHistoryManager {
    // +0x00..0xef: per-slot headers (10 × 0x18)
    struct PerSlotHeader {
        u64 pad_0x00;             // +0x00 [derived: not touched by FUN_71037857f0]
        u64 pad_0x08;
        u64 pad_0x10;
        // +0x18 / +0x20 = vector::begin / vector::end of input samples for this slot
    } slots[10];                  // +0x00
    // +0xf0..0x2cf: unknown
    u8  unk_0x2d0[0x20];          // +0x2d0 [derived: FUN_710381ba20 reads via lVar5 fields]
    u8  unk_0x2f0[0x20];          // +0x2f0 [derived: FUN_710381bde0 arg]
    u8  unk_0x310[0x20];          // +0x310 [derived: FUN_710381bc00 arg]
    // +0x330: array of 10× u64 pointers — one per slot, the "active writer" object
    void* slot_writer[10];        // +0x330 [derived: param_1 + slot*8 + 0x330 in path A]
};
```

**Rollback implication.** This is the **input history ring** the rollback layer will need to:

1. **Capture** at save-state time (all 10 slots + writers).
2. **Rewrite** during resim (overwrite samples with predicted-then-corrected inputs).
3. **Skip calling** `FUN_71037857f0` during resim (it records the *current* sampled input, not the replayed one).

The slot index range is `0..9` = 10 slots. SSBU supports up to 8 players + 2 spectator/CPU slots, consistent with this layout. Confirm by decompiling the caller of `FUN_71037857f0` (main_loop) at each of the 10 sites — the immediate `mov w1,#N` will expose the slot-index ordering.

---

## 7. Open questions for the next pass

| Question | How to answer |
| --- | --- |
| Where is the fighter-sim advance? | Search `xref_to` on `app::FighterManager` vtable slots; look for a `ProcessBeforeFighterAdvance` / `BattleObjectWorldAdvance` symbol; check if `nn::os::SignalEvent` at `0x71039c06f0` has a matching `WaitEvent` in a worker thread. |
| Is the sim on a separate thread? | Trace `nn::os::CreateThread` xrefs; a sim worker will have a long-running loop with a `WaitEvent` at top and a `SignalEvent` at bottom. |
| Which subsystem is rate-limited at 60/N? | Decompile `FUN_71036f2c00` / `FUN_71036f2d40` and inspect the caller singleton at `x25`. |
| What is `FUN_71035763c0` (called 12×)? | Decompile it. 12 calls is suspicious for per-entity dispatch. |
| Is `DAT_710593aa90[+0x398]` a safe frame anchor? | Decompile the ctor/initializer for `DAT_710593aa90` to identify the singleton type. |
| What are the 4 string keys used by `FUN_7103550080` (hash-map `find`)? | Look at the `BL` callsite xrefs from main_loop at `7103749624`, `7103749670`, `7103749754`, `71037497dc` — the strings are built on the stack just before each call. |

---

## 8. Artifacts saved by this pass

- `data/ghidra_cache/main_loop_disasm.json` — full disassembly copy (not saved — tool output file path documented below instead)
- `data/ghidra_cache/main_loop_bl_unique.txt` — 84 unique `BL` targets, sorted
- `data/ghidra_cache/main_loop_bl_named.txt` — same with `functions.csv` names resolved
- `data/ghidra_cache/pool-b.txt` — append-only Ghidra decompile cache for pool-b (per CLAUDE.md convention)
- Tool-result cache (one-off, not checked in):
  - `mcp-ghidra-disassemble_function-1775847701334.txt` — main_loop disasm
  - `mcp-ghidra-decompile_function_by_address-1775848780624.txt` — FUN_710361d040 (camera)
  - `mcp-ghidra-disassemble_function-1775848944003.txt` — FUN_710356d7a0 (effects)
  - `mcp-ghidra-disassemble_function-1775848948041.txt` — FUN_710355b540 (resource pump)
