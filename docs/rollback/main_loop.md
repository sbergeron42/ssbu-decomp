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

## 6b. FUN_7101344cf0 is NOT the per-frame fighter update (hypothesis rejected)

A follow-up pass investigated the 31 KB function `FUN_7101344cf0` on the suspicion that it might be a 65 KB per-frame fighter update called from `main_loop` (or from one of its children). **The hypothesis is rejected with very high confidence. That function is the static-init constructor for the RNG / subsystem manager singleton rooted at `DAT_71052c25b0`.**

### Evidence summary

- **Not called from `main_loop`.** `grep` on the cached `main_loop` decomp at `asm/ghidra_FUN_7103747270.c` finds zero references to `0x7101344cf0` or `FUN_7101344cf0`.
- **Only 3 callers, all via vtables / constructor chains.**
  - `FUN_71014b2a40` (itself only referenced from data slot `0x7105069c78` — a vtable entry)
  - `FUN_7101523b60` (itself only referenced from data slot `0x710506cce8`)
  - A static-init thunk at `0x710151a5d0`
  - Three additional `DATA` references at `0x7105060680`, `0x710506b0f8`, `0x710506c5b8` (vtable slots)
- **Static-init guard at entry.** `0x7101344d34: ldarb w8,[x28]; tbz w8,#0x0,0x710134b9d4` with `x28 = DAT_71053134d8` — the classic C++ one-shot guard byte.
- **CAS spinlock singleton-create pattern** at `0x7101345220` (`ldaxrb`/`stxrb`/`b.ne` loop), exactly the idiom flagged in CLAUDE.md under "Singleton creation pattern".
- **Publishes freshly-allocated singleton to `DAT_71052c25b0`** at `0x7101344e1c`: `str x20,[x8, #0x5b0]` where `x8 = 0x71052c2000`. This target address is the **RNG state root** already documented in project memory — the xorshift128 channel array lives here.
- **485 direct calls + 163 vtable dispatches, no entity walk.**
  - Top call target `0x710392dce0` × **232** — a 16-byte node allocator wrapper (jemalloc). Every single allocation is exactly 16 bytes → intrusive list nodes for chain registration, never variable-size data.
  - 25 sites of `__cxa_throw`-equivalent at `0x71000001c0`, all with the same fixed args (`x0=RODATA 0x7101763de0`, `x1=exception slab 0x71052c4180`, `x2=typeinfo 0x7104f16000`) — init-failure bailouts.
  - All 163 `blr` indirect calls are `ldr xN,[xM]; ... blr` pairs, consistent with sub-object constructor dispatch, **not** an entity loop (no `for (e : list) e->vt[update]()` skeleton observed).
  - Zero `dt`/time-delta arithmetic, zero fighter-container iterator pattern.
- **Constructs ~5+ inline sub-objects at stride 0x68** in the `0x71013474xx` region, each following the same `str x21; str w28; stur x26=−0x100000000; strh #0x1000; stp xzr,xzr; bl ctor; ldarb sub-guard` template. That is a fixed array of channel/slot structs — structurally compatible with the 9-channel RNG layout already known to live at this singleton.

### Caller `FUN_71014b2a40` corroborates

Decompiled via Ghidra MCP. The caller unconditionally invokes `FUN_7101344cf0()` at entry and then:

1. Allocates a `0x50` object with vtable `PTR_FUN_7105069db0` and stores it to `DAT_71052c26c0` (a sibling singleton).
2. Allocates a `0x20` shared-ptr stub (`PTR_LAB_7105069df0`) + a `0x330` heavy object, then chain-registers into `plVar17[1..2]`.
3. Repeats the pattern with a `0x210` heavy object registered at `plVar17[3..4]`, embedding function-pointer constants `DAT_71014b5580`/`5a60`/`68e0`/`6c30`/`7170`.
4. Creates three more sub-objects via `(*vtable[0x10])(root)` dispatch, each wrapped in a `0x30` sub-holder, using libc++ `__shared_weak_count` refcount (`ExclusiveMonitorPass`/`ExclusiveMonitorsStatus`).

This is a **root-singleton constructor**, not a per-frame update. It only exists in the vtable world (exception-init thunks), runs once per process lifetime, and never reaches the simulation loop.

### Implication for the rollback hunt

The WORKER assignment update suggested the 65 KB `FUN_7101344cf0` might sit between `main_loop` and the real sim tick. That turned out to be wrong — the function is 31 KB (not 65 KB), and it's a constructor, not a dispatcher. **The search for the sim tick advance has to move elsewhere.** Good candidates, in priority order, remain the ones identified in the original pass:

1. The **`SignalEvent`/`WaitEvent` pair** at `0x71039c06f0` / `0x71039c06c0` in `main_loop`'s frame-timing phase (§1). A separate sim worker thread signalled by `main_loop` is still the best hypothesis.
2. The **rate-limited subsystem** at `FUN_71036f2c00` / `FUN_71036f2d40` (`60 / N` divisor branch in §2 phase 8).
3. **`FUN_71035763c0` called 12×** — the single most-repeated direct child.
4. The **consumers of `DAT_71052c25b0`** themselves (RNG clients at `final_rand_create_item`, `get_bgm_kind`, `check_item_provide`, `special_lw_decide_command`, …). If any of those is invoked per-frame from a gameplay thread, its caller is the sim dispatcher.

### Artifacts saved for this pass

- `data/ghidra_cache/pool-b.txt` — session 2026-04-10 section with full evidence, top-10 call targets, consumer sample, and verdict.
- Tool-result cache (not committed): `mcp-ghidra-disassemble_function-1775850785498.txt` (31 137 lines of raw disasm).

---

## 6c. Follow-up decomps of the three open-question candidates

All three of the highest-priority sim-tick candidates flagged in the previous pass were decompiled. **None of them is the sim tick.**

### `FUN_71035763c0` — animation keyframe track sampler (called 12×)

Signature (derived): `int sample_track(vec4 p1, vec4 p2, vec4 p3, TrackDesc* track, float* out12, int frame)`.

- Reads a quantized animation track: format flags at `track[+2]` select u8 / u16 / f32 encoding; data pointer at `track[+0x68]`; per-frame stride at `track[+0x50]`; dequant bias/scale at `track[+0x54]`/`track[+0x58]`/`track[+0x78]`.
- Uses `NEON_ucvtf(..., 4)` (unsigned int → float with 4-bit fixed-point scale) to unpack u8/u16 packed keyframes into 12 floats, applies `*scale + bias`, writes to `out12` (6 × u64 = 12 × f32).
- Called 12× from `main_loop` with a stride of 12 output floats — i.e. the caller samples 12 different tracks for something like a 12-channel animated panel or camera rig.
- **Category: presentation** (animation sampling). Zero game-state mutation. Not the sim tick.

### `FUN_71036f2c00` — audio/stream state-machine transition (to state 6)

```c
if (state != 6 && state in {4, 8}) {   // bitmask 0x150
    if (child_0x68) clear its +0x100 / inner +0x20,+0x28 to -1;
    if (child_0x58) clear its +0xA0 / inner +0x20,+0x28 to -1;
    state = 6;
    SignalEvent(event_0x18);
}
```

- Nine-state state machine guarded by three levels of `recursive_mutex`.
- Transitions to terminal state `6` from states `{4, 8}`, invalidates two child objects (indexed by "track-id" style `-1` fields), and signals an `nn::os::EventType` for waiters.
- **Category: housekeeping.** Looks like an audio / DASH-style streaming-source teardown when the source becomes idle. Not the sim tick.

### `FUN_71036f2d40` — audio/stream state-machine transition (to state 4)

```c
if (state != 4 && state in {3, 6, 8, 9}) {   // bitmask 0x348
    if (obj+0x210) FUN_71036f3710/3820/3930/3820(**obj_0x210);
    if (obj+0x58)  reset its +0xA0=0, +0x94=1;
    if (obj+0x68)  clear its +0xE8,+0xF0 to -1, +0xF8=0, +0x100=0;
    state = 4;
    SignalEvent(event_0x18);
}
```

- Companion transition to the sibling at `FUN_71036f2c00` — same object, different target state and different child-reset pattern. Calls a 4-helper chain (`3710/3820/3930/3820` — open/close/reset/close?) on a deeper child at `+0x210`.
- **Category: housekeeping.** The `60/N` gate in `main_loop` phase 8 is a decoration / teardown task for this subsystem, not a sim-frame gate.

### Net effect on the sim-tick hunt

All three candidates are presentation/housekeeping. Combined with the `FUN_7101344cf0` result, **zero sub-function of `main_loop` that has been investigated mutates game-sim state in a per-frame-relevant way.** The sim dispatcher is definitely not a direct or near-direct child of `main_loop`.

---

## 6d. Signal / Wait handshake in `main_loop`

Re-reading the cached decomp with signal-event tracing in mind reveals **two** handshakes per iteration, not one:

```c
// At ~7103747b80..bf0, between phase-3 (singleton fetch) and phase-4 (subsystem updates):
local_23f0 = 0.0f;
FUN_710386fc30(&local_270, **(lVar57 + 8), &local_23f0);     // computes dt → local_23f0
if (DAT_71053386d0[1][0]) SignalEvent(DAT_71053386d0[1][0]); // KICK event A
if (state_byte == 0) notify_all();                           // wake condvar waiters
else                 FUN_710359ebd0();                       // or call alt-dispatch
// atomic: DAT_710593a440 += (int)local_23f0 + 1;  ← elapsed-ticks + 1-per-iter counter
if (*DAT_710593a528)   WaitEvent(*DAT_710593a528);           // BLOCK on event B
```

- **Event A** at `DAT_71053386d0 + 8` is written during init by `FUN_71036128a0` and read by `FUN_7103619410`, `FUN_71036185d0`, `FUN_710365efd0`, `FUN_71036128a0`, `main_loop`. The readers look like vsync / frame-pacing helpers in the `7103619xxx` / `71036185xx` range.
- **Event B** at `DAT_710593a528` is referenced only from `game_ldn_initialize` (setup) and `main_loop` (wait). No function was found that calls `SignalEvent(DAT_710593a528)` directly, which means it is signaled through an indirect path (likely a pointer field stored in another object). **This is the thing that, if found, would reveal the sim-worker signaling back to `main_loop`.**
- **`DAT_710593a440`** is the real presentation frame counter — delta-weighted (`+= (int)dt + 1` per iteration), confirmed to be the same atomic as the `x20` register used by the `ldaxr/stlxr` CAS loop at `7103747bd0`. This is what the presentation layer considers its "frame counter", so even though it is not fixed-step, it **is** the best candidate we have for a rollback index at the presentation layer.

### Event A is the render command buffer notify (confirmed)

Decompiled two of the Event A readers:

**`FUN_7103619410`** (208 B, simple) — clears a flag at `[DAT_71053386d0 + 0x55]`, obtains a command slot via `(*cmd_alloc[+0x18])(*cmd_queue)` where `cmd_queue = DAT_71053386d0 + 0x38`, writes a **4×4 identity matrix** into the returned slot (16 floats with `1.0f` on the diagonal), obtains a second slot and writes the `+0x55` flag as a `u32` into it, then `SignalEvent(**DAT_71053386d0[+8])`. This is a **"push identity transform + opacity byte" render command**.

**`FUN_71036185d0`** (252 B) — sets `[DAT_71053386d0 + 0x54] = 1`, signals Event A, releases a resource at `[DAT_71053386d0 + 0x10]` via vtable `+0x18` / `+0x8`, then walks a list of `0xA0`-stride structs at `param_1 + 0x528 .. 0x530` and writes sprite-batch fields (`+0x50`/`+0x54` floats, `+0x60/+0x68/+0x70/+0x78/+0x80/+0x88` transform/UV copies, a final `u8` flag at `+0x90 → +0xE0`) into the underlying render nodes at `[item+0x08]` and `[item+0x28]`. This is a **sprite-batch flush**.

**Verdict for Event A: `DAT_71053386d0` is the render command buffer singleton.** `[+0x08]` holds the `EventType*` that wakes the consumer (GPU submission thread or render worker). `[+0x38]` is the command allocator. `[+0x10]` is a current-resource slot. `[+0x54]`/`[+0x55]` are flag bytes. **Event A is pure presentation** — `main_loop` signals it after computing `dt` to kick the render consumer on the freshly updated command buffer.

### Event B is the LDN (network) readiness gate (most likely)

`DAT_710593a528` is referenced from only two call-sites:
- `game_ldn_initialize` at `7103741bb0` (read of the pointer slot) and `7103741c38` (an offset load that happens to alias the same page — may be coincidental, but the symbol context is LDN).
- `main_loop` at `7103747be4` (the `WaitEvent` read).

**No direct `SignalEvent(DAT_710593a528)` caller exists anywhere in the binary.** The event is signaled through an indirect pointer — most plausibly a callback or field stored into an LDN session object during `game_ldn_initialize`. Given that `LDN` is Nintendo's local-wireless stack, this event is almost certainly the **"LDN subsystem has finished its per-frame work (peer discovery tick / packet drain / session poll)"** handshake.

If Event B is the LDN gate, then `main_loop`'s per-iteration `SignalEvent(A) → update atomic counter → WaitEvent(B)` is **not** a sim/present handshake at all — it is **render-push + network-tick gating**, with the actual simulation advance living somewhere unrelated to either event.

### Refined next-pass priorities

1. **Decompile `FUN_71036128a0`** (0x5BAB bytes, the render queue initializer — writes `DAT_71053386d0`) to confirm the render-buffer identity. This is the last direct falsification test for Event A; if it turns out to allocate sim resources instead, the whole Event A theory has to be revisited. **Currently times out via MCP — needs the same cached-file workaround as `main_loop`.**
2. **Confirm Event B = LDN.** Scan `game_ldn_initialize` (and any `nn::ldn::*` xref) for stores that install an event handle into an LDN session object; search the codebase for `SignalEvent` calls inside nn::ldn callback bodies.
3. **Look for the sim loop on a DIFFERENT thread.** `nn::os::CreateThread` xrefs are the canonical entry point; a sim worker will have its own `WaitEvent` at top and `SignalEvent` at bottom, and will call into `FighterManager` / `BattleObjectWorldManager`. The two remaining `WaitEvent(0x71039c06c0)` callers worth smoke-testing are `FUN_7103987890` (SDK-gr neighborhood — probably GPU submission worker, not sim) and `FUN_7103721a40` (unclassified — promising).
4. **Walk xrefs to `FUN_710386fc30`** — this is the `dt`-producer called just before Event A. If it touches `FighterManager`, it becomes the bridge. First-pass evidence (function address in the `71038xxxxx` range) suggests it is an animation / UI time-update helper, but worth a 30-second decomp to falsify.

### All four `WaitEvent(0x71039c06c0)` callers accounted for

Before closing this pass, the remaining `WaitEvent(0x71039c06c0)` callers outside `main_loop` were swept so the search-space is fully exhausted:

| Caller | Size | Purpose |
| --- | --- | --- |
| `main_loop` @ `0x7103747270` | ~24 KB | Presentation frame loop (this document) |
| `FUN_7103987890` @ `0x7103987890` | ~15 KB | SDK-gr neighborhood. Times out via MCP decomp. Very likely a GPU command-submission worker in the `nn::gr` stack — not simulation. |
| `FUN_710013bb20` @ `0x710013bb20` | ~8 B | Tiny utility thunk |
| `FUN_7103721a40` @ `0x7103721a40` | 700 B | **Named-command RPC dispatch worker.** `while (thread_running) { lock; if (queue_empty) WaitEvent else pop + FNV-1a-hash the name (seed 0x811c9dc5, mul 0x89) + look up handler by numeric index in a 0x30-stride vector + vtable dispatch at +0x30 + write result back. }` — a classic debug-console / mod-hook / IPC dispatcher, not a game tick. |

**None of the four is a simulation tick.** Whatever advances fighter state uses a **different synchronization primitive** — either a different `EventType*`, a `condition_variable`, a direct function call from another top-level thread entry point, or a polled spin. The `main_loop`-centric search space is fully exhausted.

### Final takeaway for rollback research

`main_loop` at `0x7103747270` is definitively the **presentation / housekeeping frame loop**. Its signal/wait handshakes are **render-buffer-kick (Event A)** and **LDN-network-tick wait (Event B, hypothesized)**. None of its direct or near-direct children investigated — `FUN_7101344cf0`, `FUN_71035763c0` (×12), `FUN_71036f2c00`, `FUN_71036f2d40`, `FUN_7103619410`, `FUN_71036185d0`, `FUN_7103721a40` — mutate fighter simulation state.

**The sim tick lives outside `main_loop`'s reachable call graph and must be found via a different entry point:**

1. Top-level xrefs to `nn::os::CreateThread` — look for thread bodies that iterate `FighterManager` or `BattleObjectWorldManager`.
2. Direct xrefs to `FighterManager` vtable slots from a top-level function that is NOT reached from `main_loop`.
3. Decompile `FUN_710386fc30` (the `dt` producer called just before Event A) to falsify whether it touches sim.
4. Trace call chains from `game_main_entry` / `NintendoMain` (the process entry point) — they fork threads early, and one of them is the sim thread.

---

## 6e. Thread framework: `pead::` + `nn::pia` confirmed; `main_loop` = `pead::MainThread`

String-table scans turned up the thread framework SSBU uses and the location of `main_loop` in it.

### `pead::` is the game's thread/heap/delegate framework

Strings observed (at `7104968xx` and `7104929xx` RODATA ranges) include:

- `pead::MainThread`
- `pead::ThreadMgr`, `pead::Thread`, `pead::DelegateThread`, `pead::DelegateBase`, `pead::Event`, `pead::Mutex`, `pead::CriticalSection`
- `pead::HeapMgr`, `pead::ExpHeap`, `pead::Heap`, `pead::FixedSafeString<N>`

`pead::` is a small Bandai Namco / internal framework layered on top of `nn::os`. It owns threads, heaps, delegates, and fixed strings. **`pead::MainThread`** is the wrapped identity of the process's initial thread.

### `main_loop` *is* the `pead::MainThread` body

`FUN_710013c570` (the only xref to the `"pead::MainThread"` string at `710428ff04`) is the pead `ThreadMgr::adoptCurrentThread` path. Its body:

```c
pTVar5 = nn::os::GetCurrentThread();
plVar6 = alloc_pead_thread_object(0xf0);   // FUN_7100130810(0xf0, …)
plVar6[4] = &RTTI("pead::Thread");
plVar6[5] = "pead::MainThread";             // ← the string literal
plVar6[0x19..0x1a] = pTVar5;                // wrap the nn::os handle
plVar6[0x1d] = nn::os::GetThreadPriority(pTVar5);
nn::os::SetTlsValue(param_1->tls_slot, plVar6);
```

Because this adopts the current thread (the one already created by `nn::oe` for the process entry) and because `main_loop` is what that thread runs for every presentation frame, **`main_loop` is literally the `pead::MainThread` body**. All sim, render, and housekeeping has to either happen inside this call chain or on a thread spawned from it.

### `nn::pia` is present and owns its own thread family

`pia` (Nintendo's peer-to-peer integration layer — the substrate Smash Ultimate uses for rollback-capable online play) is in the binary with its own dedicated threads:

- `"Pia Send"`, `"Pia Receive"`, `"Pia Send Broadcast"`, `"Pia Send Unicast"`
- `"Pia SendThreadStream"`, `"Pia ReceiveThreadStream"`
- `"Pia BackgroundScheduler"`
- Strings for `nn::pia::common::BackgroundScheduler`, `nn::pia::session::*`, `nn::pia::lan::*`, `nn::pia::nex::*`

These are all **network** threads, not sim threads, but they are the framework the rollback implementation will plug into. `nn::pia::common::BackgroundScheduler` delegates work to `pead::Thread` via `pead::Delegate2<BackgroundScheduler, void(pead::Thread*, long)>` — the sim resim step for rollback would be scheduled through this exact interface when running online.

### `FUN_710386fc30` is `nu::GraphicsModule::BeginFrame` — correcting earlier docs

The function called just before Event A is signalled — previously labelled "the dt producer" on first-pass heuristics — was decompiled and is actually **`nu::GraphicsModule::BeginFrame`** (or the equivalent frame-begin method on `nu::GraphicsModule`). Evidence:

- Three explicit calls to `nu::ModuleInitializer<nu::GraphicsModule, nu::GraphicsModuleDesc>::Instance()`.
- `DAT_7105940878` invoked with timeout `0xffffffffffffffff` on a fence pointer at `[graphics_obj + 0x58] + 0xb8` — classic **GPU fence wait-for-completion** (infinite timeout).
- Error codes `-0xffbbff9` / `-0xffbbffb` follow the `nn::gr::ResultFatalErr` / `ResultTimeout` family (`0x0fbbffX` base).
- Swapchain index rotation: swaps the four fields at `param_2 + 0xf0 .. 0xfc` based on the three `u8` flags at `+0xec / +0xed / +0xee` (double/triple-buffer select).
- Per-frame command-pool rewind: walks the list at `param_2 + 0x110` and calls `FUN_7103813120` on each entry to reset its command buffer.
- Per-frame transient-memory free: iterates `[param_2 + 0x1528]` allocations and frees them via `VirtualFreeHook` + `FUN_710392e590` (jemalloc `free`).

**Critical correction: `local_23f0` is not `dt`.** It is the **retired-GPU-frames delta** — the number of frames the GPU finished since the previous `BeginFrame`. Explicitly set at `*param_3 = lVar8;` where `lVar8 = pending_fences_submitted - pending_fences_retired`. So the `DAT_710593a440 += (int)local_23f0 + 1` atomic at the end of `main_loop`'s frame-timing phase is really **"presentation frames completed = frames-known-retired-by-GPU + 1"**, i.e., a GPU-backpressure counter, **not** a CPU dt. Even less useful as a rollback index than I thought.

### All four `WaitEvent(0x71039c06c0)` callers + all main_loop phases are now classified

With `FUN_710386fc30 = BeginFrame` and all four 0x71039c06c0 waiters cleared, every direct and indirect piece of evidence points the same way: `main_loop` is the CPU-side frame head that runs on `pead::MainThread` and drives render begin → render command build → render submit (Event A) → GPU-completion bookkeeping → LDN gate (Event B). The simulation advance lives **inside** the `main_loop` call chain somewhere — just not along any of the paths checked so far.

### Updated next-pass priorities

1. **Decompile the phase-6/7 children** that were previously left `unknown`: `FUN_71035c13d0` (1,048 B, after scene state machine), `FUN_71036186d0` (1,188 B), `FUN_7103619080` (432 B), and especially `FUN_7103593c40` (792 B, phase 5). At least one of these must be the sim dispatch since `main_loop` *is* the game's main thread and there is no separate sim thread.
2. **Audit the `FUN_71035763c0` call sites** (12 of them in `main_loop`, each with different args). We established the function is a keyframe sampler, but the 12 callers pass different `TrackDesc*` — listing those 12 track descriptors identifies which subsystem runs those tracks.
3. **Decompile `FUN_7103632850`** (scene state machine, 4,268 B). We previously skimmed it as "scene/UI panel state transitions" based on the 0/1/2 state switch, but a match-active case (`DAT_710593a530 == 3` in main_loop) might route into it and do per-fighter work.
4. **Xref `FighterManager` vtable directly**, bottom-up: find the vtable load site, xref to callers, walk up until one of them is reachable from `main_loop`.

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
