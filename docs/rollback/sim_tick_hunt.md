# Sim-tick hunt — cross-pool consolidated log

**Purpose.** Three parallel investigations (pool A, B, C) are converging on the
single question "where does SSBU advance one fighter-simulation tick?". This
file is the shared scratchpad where each pool writes verdicts so the other two
can avoid redoing the same elimination.

Pool B owns this file's initial draft; pools A and C may append their own
sections.

Background and methodology for pool B's angle of attack lives in
`docs/rollback/main_loop.md`. The TL;DR of that document is:

- `main_loop` at `0x7103747270` **is** `pead::MainThread`'s body (confirmed
  via `"pead::MainThread"` string xref through `FUN_710013c570`).
- There is therefore **no separate sim worker thread** — the sim tick must
  live inside `main_loop`'s call chain, however deeply nested.
- The function's direct-child classification is almost entirely
  presentation / housekeeping / input / resource-streaming. The four
  phase-5/6/7 sub-calls listed below were the last children still labelled
  "unknown" on the first pass. The orchestrator asked pool B to clear them
  so the "sim tick is in one of these four" hypothesis could be confirmed
  or eliminated.

---

## Pool B — phase-5/6/7 child decomps

All four candidates decompiled via Ghidra MCP. Full raw evidence is in
`data/ghidra_cache/pool-b.txt`. Verdicts below.

### `FUN_7103593c40` — 792 B, phase 5

- **Iterates fighters:** NO
- **Touches BattleObject vtable:** NO
- **Per-match state mutation:** NO (mutates its own subsystem state only)
- **Verdict:** **DEAD END** — 4-slot ring-buffer advance helper.

**Evidence.**

- Two 4-slot ring-buffer index cycles: `(idx+1)&3` at `param_1+0x502..+0x510`
  and again at `param_1+0x69fc6..+0x69fd4`. These are producer-advance
  pointers into fixed-4 slot arrays — classic double/triple/quad-buffered
  subsystem output.
- Two `std::mutex`-guarded `shared_ptr` refcount releases at
  `param_1+0x3f0..0x408` and `param_1+0x418..0x430`, each gated on a
  dirty-flag byte at `+0x3e0` / `+0x3e1`.
- Sets a large state byte `param_1+0x4dcab8 = 1` and writes the magic
  sentinel `0x700000003` to `param_1+0x4dcda4`.
- Calls 4 helpers on the mutex object at `param_1+0x68` and references
  `PTR_LAB_710522ed48`.
- No loop walks a fighter container; no vtable slot in the
  `BattleObjectModuleAccessor` `+0x38..+0x188` range is touched.

**Classification.** Looks like a batch-dispatch or audio / animation /
effect buffer rotate helper for a subsystem whose root object starts at
`param_1`. The sheer size of the root (offsets up to `+0x4dcda4` = ~5 MB)
rules out a fighter struct; this is a global subsystem-pool struct.

### `FUN_71035c13d0` — 1,048 B, phase 6 (after scene state machine)

- **Iterates fighters:** NO (iterates graphics listeners instead)
- **Touches BattleObject vtable:** NO
- **Per-match state mutation:** NO (mutates graphics listener state only)
- **Verdict:** **DEAD END** — graphics event dispatcher (observer pattern).

**Evidence.**

- Gated on dirty flags at `[param_1+0x160]` / `[param_1+0x161]`; if set,
  acquires an `nu::GraphicsModule` buffer and copies a 4-`u32` rect from
  `[param_1+0x140..+0x15c]` into `buffer[+0x80..+0x9c]`. This looks like a
  **viewport / scissor rect update**.
- Core shape is a nested observer-pattern dispatcher:

  ```c
  for (event in queue_A at [param_1+0x60..+0x68], stride 0x40) {
      for (listener in list at [param_1+0x08..+0x10], stride 0x10) {
          shared_ptr::lock(listener_weak);
          (*listener->vt[+0x38])(event.data[0..3], listener, &ev);
      }
  }
  for (event in queue_B at [param_1+0x78..+0x80], stride 0x30) {
      for (listener in same list) {
          shared_ptr::lock(listener_weak);
          (*listener->vt[+0x40])(event.f0, event.f1, listener, event.f2);
      }
  }
  ```

- Optional one-time flush gated on `[param_1+0x130]` calls `FUN_71035bda90`
  per subscriber.
- Resets both queues at end: `[+0x68] = [+0x60]`, `[+0x80] = [+0x78]`.

**Classification.** The nested "for event, for listener" iteration is
structurally identical to what a sim advance would look like — which is
what made it a candidate — but the vtable slots `+0x38` / `+0x40` belong
to **graphics listeners**, and the `nu::GraphicsModule::Instance()` call
plus viewport/scissor rect copy at entry pin it firmly as a graphics
event dispatcher (window resize / surface change / display-mode change).
The stride-0x40 and stride-0x30 event descriptors are not fighter-state
struct sizes.

### `FUN_71036186d0` — 1,188 B, phase 7

- **Iterates fighters:** NO
- **Touches BattleObject vtable:** NO
- **Per-match state mutation:** NO (writes camera matrices only)
- **Verdict:** **DEAD END** — camera projection-matrix build.

**Evidence.**

- Reads resolution `[plVar9[1]+0x1c0]` / `[plVar9[1]+0x1c4]` (width × height
  as floats). Computes inverse scale `(1/scale_x, 1/scale_y)` and an offset
  bias, storing to camera output slots `plVar3[0x81a..0x81e]` and a sub-
  object at `*plVar3 + 0x230..+0x254`.
- Copies 4 × 16-byte NEON matrices from `lVar4+0x40`, `+0x50`, `+0x60`,
  `+0x70` into `pfVar6+0x98..+0xa6` with NEON_ext rotations — these are the
  **view / projection / view-projection / inverse-view-projection** matrix
  slots.
- Calls `nn::pl::IsVrMode()` to pick `0.5` vs `1.0` as a scale factor,
  writing to `pfVar6[0xd1]` — VR-mode half-width scaling.
- NEON `sqrt` + reciprocal-`sqrt` chain with `fcmeq` zero-guard computing
  a normalized ray/look-direction vector.
- Calls `FUN_710365c8d0` twice (likely shader-constant push),
  `FUN_7103619950`, `FUN_71035727d0`, `FUN_7103569a80`.
- Uses `DAT_7105336ce8` (render singleton) at `+0x490`, `+0xd8`, `+0xe0`
  for the camera-state pointer.

**Classification.** Pure presentation math — camera projection-matrix
recomputation including VR-mode scaling and a ray-direction normalize. It
pairs with the previously-classified `FUN_710361d040` (2,168 B, camera
view-matrix update) as the **phase-7 camera recompute duo**. No fighter
state touched.

### `FUN_7103619080` — 432 B, phase 7 (Event A neighborhood)

- **Iterates fighters:** NO (iterates render-command targets)
- **Touches BattleObject vtable:** NO
- **Per-match state mutation:** NO
- **Verdict:** **DEAD END** — render-command enqueue loop.

**Evidence.**

```c
for (item in [param_1+0x500..+0x508], stride 8) {
    if ((*item)[+0xf1] != 0) {               // per-item dirty flag
        cmd = alloc([param_1+0x518+0x50], 0x80, 0x10);
        cmd[0]   = &PTR_FUN_7105266f80;      // command vtable
        cmd[1]   = 0x60;                     // command type/flag
        // clone two sub-buffers from root ([param_1+0x518]+0x30 / +0x60)
        // via vtable[+0x10] into cmd[+0x10] and cmd[+0x60]
        cmd[0xe] = 0;
        cmd[0]   = &PTR_LAB_7105230f18;      // finalize vtable swap
        (*((*item)->vt[+0x18]))(item, cmd);  // dispatch command to item
    }
}
```

**Classification.** Classic render-command-enqueue producer. The 0x80-byte
command size plus two cloned sub-buffers matches a bind-resource command
shape (e.g. `BindTexture` / `SetConstantBuffer`). Lives in the phase-7
Event-A neighborhood, which is where `main_loop` signals the render-buffer
consumer, so this belongs squarely to the graphics pipeline.

### Final verdict (pool B)

**ALL FOUR DEAD** — none of the four phase-5/6/7 candidates constitutes
the per-fighter sim tick. Zero of them iterate `FighterManager`, walk a
`BattleObject*` container, or call into the `+0x38..+0x188` vtable slots
on a `BattleObjectModuleAccessor`.

Combined with prior clearings inside `main_loop.md` sections 6c / 6d / 6e
(`FUN_7101344cf0`, `FUN_71035763c0` ×12, `FUN_71036f2c00`, `FUN_71036f2d40`,
`FUN_7103619410`, `FUN_71036185d0`, `FUN_7103721a40`, `FUN_710386fc30` =
`nu::GraphicsModule::BeginFrame`), **every direct child of `main_loop`
that has been investigated is presentation / housekeeping / input /
resource-streaming.**

### Handoff notes — where pool B thinks the sim tick actually lives

Since `main_loop` **is** `pead::MainThread` (no separate sim worker
thread), the sim tick *must* be reachable from it. Three remaining leads,
in descending priority:

1. **`pead::Delegate` queue, processed somewhere inside `main_loop`.** The
   `FighterManager` singleton bottom-up xref sweep (docs/rollback/main_loop.md
   §6e, also cache entry "FighterManager singleton bottom-up xref sweep")
   found **zero** per-frame entity-iteration dispatchers among the first 60
   READ xrefs of `DAT_71052b84f8`. Every reader is a Lua-bound fighter-
   field query. If the sim step is installed as a `pead::Delegate2<...>`
   function pointer, static xref-to-body analysis will never find it — the
   delegate body is reached only via an indirect call through the delegate
   object's function-pointer field. Next pass should:
   - Find `pead::Thread::runDelegates()` / `pead::DelegateBase::operator()`
     in the binary (string table has `pead::DelegateBase` already).
   - Look for a call to the delegate-dispatch method from inside
     `main_loop`'s call chain at a call site not yet investigated.
   - xref the install sites (`pead::Delegate2` constructor) and see what
     function-pointer constants are passed to them.
2. ~~**`FUN_7103632850` scene state machine, branch `DAT_710593a530 == 3`.**~~
   ~~The 4,268-byte scene state machine was skimmed in the first pass as~~
   ~~"scene / UI panel state transition with 3-state 0/1/2 switch". The~~
   ~~**match-active state** is `DAT_710593a530 == 3`, which was not~~
   ~~investigated.~~
   **Cleared — FALSIFIED.** Full MCP decomp shows the function has **only
   three states** (0, 1, 2). There is no state-3 branch; when the current
   or target state is anything other than 0/1/2, the function falls
   through and returns immediately. The 4,268 bytes are all UI-panel
   state transition: (a) dirty-flag vectors at `param_1+{0x178,0x198,
   0x1b8,0x1d8}` of stride-`0x40` panel subscribers whose `+0x14` byte is
   toggled on state enter/exit, (b) 5 object dirty bytes at
   `param_1+{0x78,0x98,0xb8,0xd8,0xf8}+0xf0`, (c) on enter state 2, a
   linked-list walk over `[param_1+0x18]+0x128` that builds a `0x1a`-byte
   fixed string containing `"VSM_SRV_IPLUG"` (literal at
   `s_VSM_SRV_IPLUG_71043fedc5`) and calls the layout-message lookup
   `FUN_7103856280` + push `FUN_710386c530`, and (d) a subscriber-notify
   pass over `param_1+{0x260..0x268}` that calls `FUN_71035fb010` on 4
   indexed channels (on enter state 2) or 1 channel (on enter state 1).
   Zero fighter iteration, zero `BattleObjectModuleAccessor` vtable
   touches. The "VSM_SRV_IPLUG" key identifies this unambiguously as a
   scene UI state machine (View State Machine / Service Registry IPLUG
   subscriber). **DEAD END.** Full audit in
   `data/ghidra_cache/pool-b.txt` under
   "FUN_7103632850 full branch audit".
3. ~~**Auditing the 12 distinct `TrackDesc*` arguments to `FUN_71035763c0`.**~~
   **Cleared — FALSIFIED.** Direct read of the cached main_loop
   decomp at `asm/ghidra_FUN_7103747270.c` lines 2520–2920 shows the
   "12 calls" are actually **four animation-blend evaluations**, not
   12 distinct track descriptors. Each evaluation emits a "triplet" of
   callsites (`len==1` / `len>1 cur-frame` / `len>1 next-frame`), at
   most 2 of which fire per evaluation — giving the 12 grep-matched
   sites. The channel struct is `{u32 keyframe_count @ +0x08, data[] @
   +0x28, f32 weight @ +0x38, i32 cur_index @ +0x44, f32 lerp_fraction
   @ +0x48}`. Triplets 3 and 4 write their blended output into the
   render singleton `DAT_7105336ce8` at `**(+8)+0x390..+0x3b8` — the
   **same render singleton** used by `FUN_71036186d0` (camera
   projection) and `FUN_710361d040` (camera view-matrix update).
   Triplets 1 and 2 post-scale their output by `0.32573497` and
   `0.28209478` — the classic `1/(2√π)` spherical-harmonic band
   constants — and hand the result to the render module via
   `vtable[+0x128]`/`vtable[+0x130]`. This is animation-blended
   scene-lighting / shader-constant evaluation (probably SH ambient
   lighting driven by a scene animation clip). No fighter data, no
   entity iteration. **DEAD END.** Full audit in
   `data/ghidra_cache/pool-b.txt` under
   "12x FUN_71035763c0 in main_loop".

**Recommendation for pools A and C:** deprioritize anything reachable
only through the four DEAD functions above. Leads 2 and 3 have now also
been cleared (see strikethroughs above), leaving **lead 1 (pead::Delegate
queue)** as the single remaining hypothesis on pool B's angle.

### Pool B — next-pass single remaining lead

All static xref analysis has been exhausted against the `main_loop`
direct children, the `FighterManager` singleton readers (first 60 READ
xrefs were all single-field queries), and the two promising indirect
leads (the scene state machine and the 12 animation-blend callsites).
The remaining hypothesis is that the per-fighter sim step is installed
as a **`pead::Delegate` function pointer** which is invoked somewhere
inside `main_loop`'s direct-call graph at a call site already classified
as "neutral" or "unknown" — most likely via `pead::Thread::runDelegates`
or similar.

### `main_loop` contains its own internal frame loop (new finding)

Decompiling the only xref-to-`main_loop` caller — `nnMain` at
`0x71002c48f0`, call site `0x71002c5cec` — proved a subtle but
important structural point. **`nnMain` calls `main_loop` exactly once.**
It is not wrapped in a `while`, `for`, or `do-while`. The pre-call work
is argv/LDN/ResourceService init plus a 1 ms polling wait for a
resource-ready flag; the post-call work is a ~2,400-line C++ destructor
cascade that tears down ~93 refcounted resources held by the
application root pointer that `main_loop` returns. There is **no**
`nn::os::CreateThread` / `StartThread` anywhere in `nnMain`, **no**
`pead::` / `Delegate` / `Scheduler` / `Fighter` string, and **no**
`FighterManager` or `BattleObject` vtable touches.

This means:

- **`main_loop` is not a "one frame" function that some outer loop
  calls per frame. It is itself the per-frame loop.** Its 84 unique BL
  targets are therefore all called per frame (except any gated behind
  first-use guards, which are explicitly `__cxa_guard_acquire`/`release`
  pairs).
- The sim-tick dispatcher lives **inside** `main_loop`. It is not above
  it and it is not on a separate worker thread. (Recall: `main_loop` is
  `pead::MainThread`'s body, which is the process's initial thread, and
  `nnMain` never spawns a second thread.)
- The sim dispatcher either (a) lives inside the body of one of the BL
  targets already classified as "unknown" / "neutral" but not yet
  audited deeply enough, or (b) is reached through an **indirect
  dispatch** — a vtable call, a function-pointer field invoked inside a
  BL target whose body doesn't statically show `FighterManager` access.

The `pead::Delegate` hypothesis remains the best single explanation for
(b): a delegate object with a stored function pointer, invoked from
inside `main_loop` via a vtable slot on `pead::Thread*` or similar. The
first static xref sweep on `FighterManager` found zero per-frame
dispatchers, which is exactly what we'd expect if the dispatcher is
reached via a delegate's function-pointer field rather than by name.

Additionally, `nnMain` sets a global pointer `DAT_710593a2d8` to a
stack-allocated 16-byte context blob `{0x68, 0x52, 0x0b, 0x7105, ...}`
immediately before calling `main_loop`. **This is the only context
hand-off from `nnMain` to `main_loop`.** If `main_loop` reads
`DAT_710593a2d8` to find a subsystem root (e.g. the pead::ThreadMgr, or
a delegate queue head), that is a very high-value xref to sweep in the
next pass.

### Next concrete steps (pool B, next session)

1. **Xref sweep on `DAT_710593a2d8`.** Find every read of it in the
   binary. Any reader inside `main_loop`'s call graph that dispatches a
   vtable call on it is a direct candidate for the sim tick.
2. **Find `pead::Thread::runDelegates` / `pead::Delegate::operator()`.**
   The `pead::DelegateBase` string literal in the binary's RODATA at
   ~`0x71049` is the anchor. Disassemble its xrefs and walk into the
   vtable slot that invokes the delegate's stored function pointer.
3. **Classify the `pead::MainThread` vtable at `PTR_DAT_71052a4d40 +
   0x10`.** `FUN_710013c570` installs this vtable on the wrapped
   current thread. Its slots should include a `run()` / `onRun()` /
   `update()` method. If any slot points at a function that iterates
   `FighterManager` or runs delegates, that is the sim dispatcher.
4. **Audit every currently-"unknown" BL target in `main_loop`'s
   classification table in `main_loop.md` §3** — stop deferring them.
   In particular, the `FUN_71036eb680` / `FUN_7103871c90` / `FUN_71035727d0`
   / `FUN_710354c720` tier has not been touched and could hide the
   dispatcher behind a "helper" name.

---

<!-- Pool A and Pool C: append your sections below. Please preserve the
     heading style so this doc stays greppable. -->
