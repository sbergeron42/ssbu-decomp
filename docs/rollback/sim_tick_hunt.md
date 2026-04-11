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

---

## Pool B — BREAKTHROUGH: two indirect dispatchers inside main_loop

Follow-up search after the "nnMain calls main_loop exactly once" framing
update. Grepping the cached main_loop decomp for `DAT_710593a530` turned
up a hit **inside `main_loop` itself** at line 543:

```c
if (DAT_710593a530 == 3) { ... }
```

This is exactly the "match-active branch" the first-pass handoff was
pointing at — but it lives in `main_loop` directly, **not** in the
`FUN_7103632850` scene state machine (which has only 3 states 0/1/2 and
no state-3 branch — a previously-decompiled dead end). Pool B was
looking in the wrong function for the entire lead-2 investigation.

Reading the surrounding code (asm/ghidra_FUN_7103747270.c lines
540..630) reveals **two indirect dispatchers** that have not been
classified by any prior pool, at least one of which has the exact shape
of the sim tick:

### Dispatcher A — match-active vtable walk

Location: `main_loop` lines 543..572, gated on `DAT_710593a530 == 3`.

```c
if (DAT_710593a530 == 3) {
    switch (iVar31) { ... }          // small UI dirty-flag toggle
    lVar48 = *(long *)(**(long **)(&DAT_000024e8 + *DAT_710593a6a0)
                       + 0x2da8);
    std::recursive_mutex::lock();
    for (lVar67 = *(long *)(lVar48 + 0x38);
         lVar48 + 0x30 != lVar67;
         lVar67 = *(long *)(lVar67 + 8))
    {
        uVar35 = (**(code **)(**(long **)(lVar67 + 0x10) + 0x28))();
        if ((uVar35 & 1) != 0) { bVar45 = 1; goto LAB_7103747d0c; }
    }
    bVar45 = 0;
LAB_7103747d0c:
    std::recursive_mutex::unlock();
    bVar45 = bVar45 | iVar31 != 2;
}
```

- Root singleton: `DAT_710593a6a0`, indirected twice through `+0x24e8`
  (PIC-fixup constant in the Ghidra output).
- Sub-object field: `[root]+0x2da8` — a circular-list head with pair
  pointers at `+0x30` (tail/sentinel) and `+0x38` (first node). List
  traversal goes via `node[1]` (field `+0x08` = next).
- Each node dereferences to an object at `[node+0x10]`; its vtable is
  read and slot `+0x28` is called.
- Early-out on the first element whose slot `+0x28` returns non-zero
  (`uVar35 & 1`). That is either "I am the one", "I handled this", or
  "abort further walk".

**Smoking-gun characteristics for sim:**

- Gated on a global state equal to `3` (match active / in-game), which
  *is* how SSBU distinguishes title/CSS/match states.
- Iterates a list of entities, calling a vtable method on each.
- Protected by `recursive_mutex`, consistent with a cross-thread-
  safe game-state mutator.

**Caveats / not-yet-proven:**

- The vtable slot is `+0x28`, not any of the standard
  `BattleObjectModuleAccessor` offsets `+0x38..+0x188`. It could be a
  `SceneTask::exec()`-style root dispatch that THEN walks the fighter
  list, rather than being the fighter list itself.
- The early-out on first truthy return makes this look more like a
  "find first active match" query, not a "per-fighter update" loop —
  a sim dispatcher would want to run the method on EVERY entity, not
  stop at the first one.
- But the list-head split (sentinel at `+0x30`, first node at `+0x38`)
  is the classic STL `std::list` layout, so the walk itself is
  per-element and normal.

Pool B assessment: **probably not the per-fighter dispatch**, but
**likely the scene-root "is match running" / "tick the scene" entry**
that calls into the fighter dispatcher at the next level down. Worth
decompiling the vtable slot `+0x28` target for whatever object type
lives at `[**DAT_710593a6a0 + 0x24e8] + 0x2da8 + 0x38 + 0x10`.

### Dispatcher B — frame-scheduled delegate queue (high-confidence sim-tick candidate)

Location: `main_loop` lines 610..628, immediately after Dispatcher A.

```c
iVar31 = 0;
if (DAT_710522ebe0 != 0) {
    iVar31 = (DAT_7105332050 + 1) / DAT_710522ebe0;
}
DAT_7105332050 = (DAT_7105332050 + 1) - iVar31 * DAT_710522ebe0;
                                          // DAT_7105332050 cycles 0..N-1 per frame
if (0 < (int)DAT_7105331f4c) {
    lVar67 = (long)(int)DAT_7105331f4c;
    do {
        lVar48 = *(long *)((long)&DAT_7105331f4c + (lVar67 + -1) * 8 + 4);
        lVar65 = (long)DAT_7105332050;
        puVar66 = (undefined8 *)(lVar48 + lVar65 * 0x18 + 0x10);
        for (puVar68 = (undefined8 *)*puVar66;
             puVar68 != (undefined8 *)0x0;
             puVar68 = (undefined8 *)puVar68[2])
        {
            (*(code *)puVar68[1])(*puVar68);    // <-- delegate invoke
        }
        // splice the list into a cleanup chain and reset head
        plVar49 = (long *)(lVar48 + lVar65 * 0x18);
        *puVar66 = 0;
        lVar48 = *plVar49;
        plVar49[1] = lVar48;
        *(long *)(lVar48 + 8) = lVar48 + 0x18;
        lVar67 += -1;
    } while (0 < lVar67);
}
```

**Structure.**

- `DAT_7105331f4c` = number of priority buckets (the outer `do ...
  while` iterates from `N-1` down to `0`).
- `DAT_710522ebe0` = frame cycle length (modulo N). Most likely `60` if
  SSBU wants 1-to-60 Hz fractional task scheduling, but could be any
  fixed integer.
- `DAT_7105332050` = current position in the cycle, advanced by 1 per
  frame and wrapped modulo `DAT_710522ebe0`. The post-increment cycling
  is line 609: `DAT_7105332050 = (DAT_7105332050 + 1) - iVar31 *
  DAT_710522ebe0`.
- Each priority-bucket "table" at `&DAT_7105331f4c + (bucket-1)*8 + 4`
  (a misaligned-looking field that is really `bucket_base[bucket-1]`)
  contains `DAT_710522ebe0` linked-list heads, stride `0x18`.
- Each slot's linked list is walked:
  ```
  node[0] = this / context         // first arg to the delegate
  node[1] = function pointer        // invoked as (*fn)(this)
  node[2] = next pointer
  ```
- After invocation, the list head is cleared and the nodes are spliced
  onto a cleanup chain (`plVar49[0]`/`plVar49[1]`) — the tasks are
  one-shots that get torn off and freed elsewhere.

**This is a per-frame delegate queue, scheduled by frame-slot.** A task
that fires every frame registers on the bucket's every slot (or on a
special "always" bucket); a task at 30 Hz registers on every other
slot; a task at 20 Hz registers on every third slot; etc. The
fixed-point `DAT_710522ebe0` modulo is exactly the mechanism that lets
the game schedule "X times per Y frames" tasks with sub-frame
precision.

**Why this is the prime sim-tick candidate:**

1. The function-pointer call `(*(code*)puVar68[1])(*puVar68)` is an
   indirect dispatch that static xref-to analysis on
   `FighterManager::update` or any named sim function would miss
   entirely — which explains why the first-60-xref sweep in
   `docs/rollback/main_loop.md` §6e found zero dispatchers.
2. It lives in `main_loop` directly, immediately after the
   match-active branch (Dispatcher A) and immediately before the
   phase-7 camera / phase-8 rate-limited code blocks. The position
   in the frame is exactly where sim would run: after scene state
   has been latched and before rendering commits camera/projection
   state.
3. The one-shot cleanup chain means tasks are re-installed every
   frame by whatever subsystem owns them — which is exactly the
   pattern you'd get if the sim advance is installed by a
   "RunMatchTick()" caller as `{fighterMgrPtr, &FighterMgr::advanceAll,
   next}`.
4. The `DAT_71052xxxx` address range is the known match/runtime
   singleton-data region (see the memory-map doc), so
   `DAT_7105331f4c` and `DAT_7105332050` sit right in the game-state
   block.

**What's needed to confirm.**

- Xref sweep on `DAT_7105331f4c` to find every WRITER to the linked
  lists. Each writer is either (a) a registration site (installing a
  delegate) or (b) unrelated bookkeeping.
- Xref sweep on `DAT_7105332050` to find anything else that reads or
  resets the frame-slot counter — that might point at a top-level
  reset call.
- Find the registration wrapper function: it will look like a small
  helper taking `(priority, slot_mask, this, fn)` and splicing a new
  node into `DAT_7105331f4c[priority][slot].head`.
- Trace one real registration back to its caller — the caller is the
  subsystem being dispatched, and one of them should be the sim step.

**Blocker encountered in this session.** The `DAT_7105331f4c` xref
sweep returned three references: one READ from `main_loop` at
`0x7103747e04` (the dispatch site in Dispatcher B, already decompiled),
one READ at `0x7103753e4c`, and one WRITE at `0x7103753ee8`. The
latter two sit in **undefined code** between `FUN_710374f360` (which
ends at `0x7103752f07`) and `FUN_7103753fc0` (which starts at
`0x7103753fc0`). Ghidra's auto-analyzer has not carved that ~4 KB gap
into a function, so neither `decompile_function_by_address` nor
`disassemble_function` will yield results at those addresses. The
next-session prerequisite for confirming Dispatcher B is a Ghidra
**auto-analyze / disassemble** pass on the byte range
`0x7103752f08..0x7103753fbf`; once that gap is recovered as a
function, the registrar / companion manager will become
decompilable and the writer site `0x7103753ee8` will reveal how tasks
get installed.

### Follow-up: Dispatcher B is most likely NOT the sim tick

Xref sweep of the related globals returned:

- **`DAT_710522ebe0`** (cycle length N): WRITTEN by `FUN_710374f360`
  at `0x710375082c`, READ by `main_loop` at `0x7103747de0`.
- **`DAT_7105332050`** (frame slot counter): only touched by
  `main_loop` itself (READ at `0x7103747dd8`, WRITE at `0x7103747df8`,
  READ at `0x7103747e28`). No external initializer.
- **`DAT_7105331f4c`** (bucket table): no writer inside any named
  function (the writer at `0x7103753ee8` is in the undefined-code
  gap).

`FUN_710374f360` was decompiled in full (15 KB) and classified: **it
is the Resource Manager / Graphics subsystem boot function**. It
spawns three resource threads (`"ResUpdateThread"`, `"ResLoadingThread"`,
`"ResInflateThread"`) and initializes `nu::GraphicsModule`. It writes
`DAT_710522ebe0` as a **copy from a caller-supplied config struct
field `param_1[0x80]`**, not as a hardcoded `60`. It does NOT touch
`DAT_7105331f4c` or `DAT_7105332050`. It contains ZERO
`pead::`/`Delegate`/`Scheduler`/`Task`/`Tick`/`Sim`/`Battle`/`Fighter`
strings.

**Implications for Dispatcher B's identity.**

1. The "60 Hz fingerprint" is wrong — the cycle length is a tunable,
   not a hardcoded 60.
2. `DAT_710522ebe0`'s writer is the **resource manager** init, which
   spawns three resource worker threads. The cycle length is
   therefore very likely the **resource-streaming tick budget** —
   "how many frames per resource-update pass" — rather than a sim-
   frame divisor.
3. `DAT_7105331f4c` and `DAT_7105332050` live in the same
   `DAT_710533xxxx` block as several other resource-manager globals
   (`DAT_7105331f00`, `DAT_7105331f20`, `DAT_7105331f28`) that ARE
   written by `FUN_710374f360`. This is weak evidence that they
   belong to the resource subsystem too.
4. If Dispatcher B is a resource tick queue, its per-slot function
   pointers are resource-loader callbacks — async file-loaded
   finalizers, descriptor pool rebuilds, texture unloads, etc. —
   not fighter sim advance.

**Revised pool-B confidence ranking:**

- **Dispatcher A** (`DAT_710593a530 == 3` match-active vtable walk
  at main_loop lines 543..572) remains the **strongest remaining
  sim-tick candidate** even with its early-out caveat. It is
  explicitly gated on match-active state, protected by
  `recursive_mutex`, and does per-element vtable dispatch on a list
  rooted in a singleton at `DAT_710593a6a0`. The early-out on
  `slot[+0x28] == truthy` is compatible with a "dispatch one
  eligible scene task and stop" pattern, and the singleton address
  is in the `DAT_710593axxxx` range which is the known **match
  runtime state** block (not the resource-manager block).
- **Dispatcher B** (frame-scheduled queue at main_loop lines
  610..628) is **downgraded** from "pead::Delegate sim scheduler"
  to "probable resource-loader tick queue", pending xref of the
  undefined-code writer at `0x7103753ee8` that will settle the
  question.

### `DAT_710593a6a0` identity — partial classification

Xref sweep ran this session. The singleton is read from **many**
directions simultaneously, which is informative:

- `lua_ai_path_builder` at `0x71017e8a14` / `0x71017e8aa0` (2 reads)
  — Lua-bound AI pathfinding helper.
- `FUN_71014f10c0` reads the singleton **~40 times** — a heavy
  serializer or state-dump function in the gameplay range.
- `FUN_7100d99310` / `FUN_7100d72e80` / `FUN_710067e7d0` /
  `FUN_71014cde40` — gameplay-range readers (`71004x..71017x`).
- `FUN_7103577fd0` at `0x7103578068` / `0x7103578ecc` — decoded this
  session. Reads `*DAT_710593a6a0` and indexes a vector at
  `+0x24d0..0x24d8` of stride-`0x68` entries to look up a per-entry
  shared_ptr. The FNV-hashed string constants embedded in the function
  decode to:
  - `"lib::mii::HeadRenderer (ringed_command_buffer_opaque_)"`
  - `"lib::mii::HeadRenderer (ringed_command_buffer_translucent_)"`
  So this reader is installing **Mii-head render command buffers**
  (opaque + translucent passes) into the singleton's head-renderer
  slot.
- `FUN_7103582b60` reads it 7 times — another graphics-range function.
- Two **WRITE** xrefs: `FUN_71022cd350` at `0x71022cd600` and
  `FUN_71022b7100` at `0x71022c9fb4`. These are the installers —
  large functions (>16 KB each, the first tool-called decomp was 145
  KB of text), not decompiled in full this session.

**Interpretation.** `DAT_710593a6a0` is NOT a resource singleton (the
`DAT_7105331f00` family) and NOT a render-module singleton (the
`DAT_7105336ce8` family). It is a **scene / game-root singleton** that
owns *both* gameplay sub-lists (lua AI paths, 40-field serialization)
*and* render queues (Mii head renderers at `+0x24d0`, and another
sub-list at `+0x24e8..+0x2da8` which is what Dispatcher A walks).

This matches the expected shape of `app::Scene` / `app::GameMain` /
`app::WorldManager`: a hub object that aggregates the match-runtime
sub-managers (fighters, camera, HUD, renderers) under one root.

**Implication for Dispatcher A.** The list at
`[**(DAT_710593a6a0+0x24e8) + 0x2da8]` is one of this scene-root's
sub-manager lists. Walking it with `vtable[+0x28]` gated on
match-active = 3 is consistent with "for each registered sub-manager,
call its per-frame `onTick()` while the match is running". This is
exactly the shape of the `pead::Delegate` pattern the earlier hypothesis
predicted, just implemented via an intrusive manager list instead of a
frame-slot queue. **Dispatcher A remains the strongest sim-tick
candidate.**

### Next concrete steps (pool B, next session)

1. **Decompile the two writers of `DAT_710593a6a0`**: `FUN_71022cd350`
   (at the write site `0x71022cd600`) and `FUN_71022b7100` (at
   `0x71022c9fb4`). These constructors will expose the singleton's
   type, its initial vtable, and the sub-objects installed at
   `+0x24d0`, `+0x24e8`, and `+0x2da8`. That's the single most valuable
   query for identifying what Dispatcher A's list contains. The first
   decomp attempt in this session hit the MCP size limit; next session
   should use the sub-agent file-chunking pattern established for
   `nnMain` and `FUN_710374f360`.
2. **Decompile `FUN_71014f10c0`** — the 40-READ-xref consumer of
   `DAT_710593a6a0`. A function that reads the same singleton 40 times
   in a row is almost certainly a **serializer** — either save-state,
   replay-record, or rollback-capture. If it's rollback-capture, it's
   the single most valuable function for the entire rollback
   implementation: it IS the save-state function. If it's just replay
   save, it still exposes the full scene-root layout.
3. **Xref sweep `DAT_710593a530`** (the match-state global Dispatcher
   A is gated on). Its writer is the thing that sets `3 == match
   active` and is therefore the state-machine transition function for
   entering/leaving a match. Its xrefs across the binary will pin down
   the match-life-cycle API.
4. **Fix the Ghidra DB gap at `0x7103752f08..0x7103753fbf`** (analyst
   action, not decomp) to unblock Dispatcher B's writer-site
   decompile. Low priority now that Dispatcher B has been downgraded
   to "probable resource tick queue", but still worth closing.

### Updated verdict and handoff

`main_loop` directly dispatches two indirect-invoke points: one vtable
walk gated on match-active, and one frame-scheduled delegate queue.
**Neither was on the 84-unique-BL-targets list because both are
function-pointer dispatches through loaded pointers, not direct `BL`
instructions.** This invalidates the "all direct children of main_loop
have been classified" assumption and reopens the sim-tick hunt with
two strong, novel leads.

Pool B's single remaining hypothesis (pead::Delegate queue) is now
concretely located: **it is Dispatcher B, inside `main_loop` at lines
610..628**, using the `DAT_7105331f4c` / `DAT_5105332050` /
`DAT_710522ebe0` globals as its bucket/slot/cycle state. Whether the
dispatched function pointers include the fighter sim advance is the
single remaining question, and it is answerable by xref-sweeping
registrations.

---

<!-- Pool A and Pool C: append your sections below. Please preserve the
     heading style so this doc stays greppable. -->

---

## Pool A — FighterManager vtable approach

### Finding 1 — FighterManager has **no vtable**

The plan was to pull the `FighterManager` vtable, xref tick-shaped slots, and walk up.
That plan fails on first contact: `app::FighterManager` is a **plain data struct**,
not a polymorphic class. Evidence:

1. Every `FighterManager__*_impl` wrapper accesses the manager through a double-pointer:
   `ldr x8,[x0]; ldr w/x …,[x8, #fieldoff]` where `x0` is actually
   `&Singleton<FighterManager>::instance_`, `x8` is the real `FighterManager*`, and
   the second load reads a *field*, not a vtable slot. Example —
   `FighterManager__entry_count_impl` @ `0x7102140d60`:
   ```
   7102140d60: ldr x8,[x0]           ; x8 = *instance_ = FighterManager*
   7102140d64: ldr w0,[x8, #0xa0]    ; entry_count (u32) at +0xa0
   7102140d68: ret
   ```
   If `FighterManager*` had a vtable at offset 0, `[x8,#0xa0]` would read the 20th
   method pointer as a u32 — nonsense. The only consistent reading is that
   offset 0 of `FighterManager` is **data**, not a vfptr.

2. Every non-lua_bind reader in the 150+ `get_xrefs_to 0x71052b84f8` sweep
   (`FUN_710062b830`, `FUN_710082b9e0`, `FUN_710082c560`, `FUN_7100062b830`,
   `final_scene01_exit`, `start_metamon_fighter`, …) uses the singleton by
   `lVar = *lib::Singleton<app::FighterManager>::instance_` and then reads
   named data fields (`+0x20` entries, `+0xa0` entry_count, `+0xe9`, `+0x164`,
   `+0x4150`, `+0x41e4`, `+0x5920`, `+0xae8` observer list, …). **No caller
   dereferences `*(u64*)fighter_manager` as a vtable.** The struct is at
   minimum `~0x5928` bytes of mostly-data.

3. The symbol `lib::Singleton<app::FighterManager>::instance_` is a single
   `FighterManager*` slot in `.bss` (confirmed by the .dynsym export —
   mangled name `_ZN3lib9SingletonIN3app14FighterManagerEE9instance_E` at
   `0x71041c429d`). Ghidra shows only READ xrefs in `.text`; the write that
   populates it is most likely in a `__cxx_global_var_init_*` / relocation
   entry that Ghidra does not xref from `.text`.

**Conclusion:** there is no FighterManager vtable to walk. The per-fighter
polymorphism lives **one level down** inside each `FighterEntry`, at
`entry + 0xf0` / `entry + 0x100`. Those module pointers are the first-class
vtable dispatch in the manager neighborhood — and `FUN_710062b830` proves it
(`(**(code **)(*entry_0xf0 + 0x10))(entry_0xf0)` is a boolean query, and
`plVar6[1] + 0x1a4` reads a float field from the module's inner data).

### FighterEntry layout (derived from readers of the singleton)

| Offset | Type | Purpose (derived from) |
| --- | --- | --- |
| `+0x14` | s32 | entry state / player count (FUN_710062b830 checks `< 2`) |
| `+0x18` | s32 | primary fighter kind (`FighterKind`) — matched against `param_2` in set_final_impl |
| `+0x1c` | s32 | secondary fighter kind (`-1` = none) — second slot for two-character entries (Ice Climbers, Pokémon Trainer, Rosalina, Olimar) |
| `+0xe9` | u8 | disable flag (`FUN_710082b9e0` skips iteration when set under mask 1) |
| `+0xf0` | *FighterSubmodule* | **vtable dispatch** — primary slot, `(*vt[0x10])` is "is present" bool query, data ptr at `+0x8` points to `PostureModule`-like with float `+0x1a4` |
| `+0x100` | *FighterSubmodule* | secondary slot (same shape, used for the 2nd sub-fighter in two-character entries) |

Entry stride = 8 bytes (these are *pointers*). The 8 entries live at
`FighterManager+0x20..+0x58`.

### FighterManager data layout (derived)

| Offset | Type | Purpose (derived from) |
| --- | --- | --- |
| `+0x18` | u32 ref-count | observer recursion guard (`FUN_710082c560` increments puVar9[6] then walks the observer list at +0xae8) |
| `+0x1c` | u32 | observer-list pending-delete flag |
| `+0x20..+0x58` | FighterEntry* [8] | entry array (max 8 simultaneous fighters) |
| `+0xa0` | u32 | **entry_count** (live entry count) — `FighterManager__entry_count_impl` |
| `+0xac` | u32 | `FighterParamAccessor2[+0x50]+0x324` mirror, written on `set_final_impl` success |
| `+0xe9` | u8 | `is_disabled` flag checked by `FUN_710082b9e0` |
| `+0x164` | f32 | scaling factor used in `FUN_710062b830` (camera rumble multiplier?) |
| `+0xae8` | intrusive-list head | observer registry (doubly linked `{next, prev, handler*}`, walked in `FUN_710082c560` on entry events) |
| `+0x4150..` | FighterEntry-like trailer | secondary arrays accessed by `FUN_710082b9e0` via `lVar5 + 0x4150..+0x4168` |

### Redirect — what Pool A found by pivoting

Because the FighterManager-vtable angle is a dead end, Pool A followed the only
per-frame pointer flow the manager exposes: the `FighterEntry +0xf0 / +0x100`
inline smart-ptrs. Chasing a tiny helper `FUN_710062b830` (a rumble-scale
multiplier that reads the entry's primary/secondary smash-slot inline pointer)
led directly to a **status vtable** in read-only data.

### Status vtable discovery @ `0x7104f7f4xx..0x7104f7f568`

`FUN_710062b830` is not called directly from anywhere — its sole xref is from
`FUN_7100614630` @ `0x710061552c`. `FUN_7100614630` is also never called
directly — its sole xref is a **DATA** reference from `0x7104f7f568`. That
means `FUN_7100614630` is a **vtable slot** of some polymorphic class, never
invoked by name, only through vtable dispatch.

Walking backwards from `0x7104f7f568` by 8-byte strides enumerates a contiguous
run of `code*` entries (all `FUN_71006140xx..71006146xx`) — a single vtable.
Partial slot map (offsets are from the lowest enumerated entry @ `0x7104f7f2e8`,
which may or may not be the vtable base — the true base is a few slots lower;
slots `0x7104f7f240..0x7104f7f2e0` still resolve to DATA targets so the walk
is not yet exhausted):

| Offset from `0x7104f7f2e8` | Slot fn | Suspected role |
| --- | --- | --- |
| `+0x00` | `FUN_7100613c00` | on_init / ctor-thunk |
| `+0x08` | `FUN_7100613c60` | on_end / dtor-thunk |
| `+0x10` | `FUN_7100613cc0` |  |
| `+0x18` | `FUN_7100613eb0` |  |
| `+0x20` | `FUN_7100613f70` |  |
| `+0x28` | `FUN_7100614060` |  |
| `+0x30` | `FUN_7100614080` |  |
| `+0x38` | `FUN_71006140c0` |  |
| `+0x40` | `FUN_7100614180` |  |
| `+0x48` | `FUN_7100614270` |  |
| `+0x50` | `FUN_7100614360` |  |
| `+0x58` | `FUN_7100614450` |  |
| `+0x60` | `FUN_71003a7eb0` | **vthunk** (cross-ITable) |
| `+0x68` | `FUN_7100614470` |  |
| `+0x70` | `FUN_7100614570` |  |
| `+0x78` | `FUN_71006145b0` |  |
| `+0x80` | `FUN_7100614630` | **status main_exit / per-fighter handler** |

`FUN_7100614630` decompiled (abridged) shows the shape of a per-status,
per-fighter handler in the canonical Skyline "status module" style:

- Loads `plVar15 = lib::Singleton<app::FighterManager>::instance_`
- Reads `param_1 + 0x10` (u32 entry_id) and `param_1 + 0x0c` (s32 kind),
  looks the entry up in the manager's 8-slot table, follows the primary /
  secondary sub-slot via `+0xf0` / `+0x100` (matching the FighterKind test
  at `entry+0x18` / `entry+0x1c`),
- Calls vt[0x30] on `param_1[0x1f21]` (a `pre_process` hook on the outer
  BattleObject base class),
- Runs a very large status body: reads `plVar16 = param_1[0x86]`
  (status_module, offset `+0x430`) and queries `vt[0x110] = get_status_kind`;
  reads/writes `plVar17 = param_1[0x88]` (work_module, offset `+0x440`) with
  the full Skyline WorkModule surface: `set_int`, `get_int`, `is_flag`,
  `on_flag`, `off_flag`, `get_param_float`, `get_param_int`, `is_excute`,
  `get_float`, `set_float`, `count_down` — matched by slot offsets
  `0xa0/0x98/0x108/0x110/0x120/0x270/0x250/0x78/0x58/0x60/0xc8`
  (these are well-known WorkModule virtual offsets);
- Calls per-slot handlers on cached module pointers on `param_1`,
- Calls vt[0x38] on `param_1[0x1f21]` (matching `post_process` hook).

The `(pre_process, body, post_process)` envelope and the fact that the body
calls `StatusModule::get_status_kind` repeatedly to gate behavior means this
slot is **`FighterStatusBase::sub_on_main_callback` / `on_main_exit`** (or
similar — the precise slot name has to be confirmed against the community
`nro_hook` list, but the shape is unambiguous).

### Fighter / BattleObject layout (derived from `FUN_7100614630`)

| Offset | Type | Evidence |
| --- | --- | --- |
| `+0x0c` | s32 `kind` | `*(int*)(param_1 + 0xc)` compared to primary/secondary entry kind |
| `+0x10` | u32 `entry_id` | `*(uint*)(param_1 + 2)` used as index into FighterManager.entries |
| `+0x3f0` | `BattleObjectModuleAccessor` **(inline)** | `(BattleObjectModuleAccessor*)(param_1 + 0x7e)` passed into `FUN_710068f410`, `FighterUtil::exec_big_small` |
| `+0x430` | `StatusModule*` (accessor +0x40) | `plVar16 = param_1[0x86]`, vt[0x110] get_status_kind, vt[0x168] something |
| `+0x440` | `WorkModule*` (accessor +0x50) | `plVar17 = param_1[0x88]`, full WorkModule surface |
| `+0x480` | `?Module*` (accessor +0x90) | `param_1[0x90]`, vt[0x88] is_pause, vt[0x58] |
| `+0x498` | `DamageModule*` (accessor +0xa8) | `param_1[0x93]`, vt[0xc0] set_damage, vt[0xc8] get_damage |
| `+0x4a0` | `?Module*` (accessor +0xb0) | `param_1[0x94]`, vt[0xd0] / vt[0xe8] |
| `+0x528` | `?Module*` (accessor +0x138) | `param_1[0xa5]`, vt[0x58] |
| `+0x530` | `MotionModule*` (accessor +0x140) | `param_1[0xa6]`, vt[0x238] set_motion, vt[0xb0] |
| `+0x548` | `?Module*` (accessor +0x158) | `param_1[0xa9]`, vt[0x110] |
| `+0x560` | `?Module*` (accessor +0x170) | `param_1[0xac]`, vt[0x80], vt[0xb0], vt[0xe0] |
| `+0x568` | `?Module*` (accessor +0x178) | `param_1[0xad]`, vt[0x68], vt[0x78] |
| `+0xf5a0` | pointer | `param_1[0x1eb4]`, per-stage context (flag at +0x10d, +0x10e) |
| `+0xf5b0` | pointer | `param_1[0x1eb6]`, some curve/timeline object (vt[0x280]) |
| `+0xf700` | pointer | `param_1[0x1ee0]`, post-status cleanup handler (vt[0x50], vt[0x3f0]) |
| `+0xf72c` | s32 | `*piVar1 = (int*)(param_1 + 0xf72c)` — a decrementing per-status counter |
| `+0xf73c..0xf744` | float/int | cleared to `-1.0f, 0` at end |
| `+0xf802..0xf815` | byte flags | various status byte flags toggled at exit |
| `+0xf908` | `?BattleObject*base?` | `param_1[0x1f21]`, vt[0x30] / vt[0x38] pre/post hooks — **the most likely BattleObject-base pointer held by the Fighter** |

**Cached module pointers theory (strong).** The fact that these slots are
accessed with single `ldr x, [param_1, #imm]` in a hot per-frame handler means
the Fighter caches each module pointer at a fixed offset *alongside* (or
*inside*) its embedded `BattleObjectModuleAccessor`. This matches the
"cached pointer in a scene object" pattern the pool-B main_loop doc predicted:
**the sim dispatcher almost certainly walks a list of `param_1`-shaped
Fighters, not the FighterManager entry array**, because the FighterManager
entries don't carry the cached module table.

### Second-pass confirmation — one class, more slots mapped

After the first commit, Pool A decompiled two more slots in the same table:

- Slot `+0x2b8` @ `0x7104f7f578` → `FUN_71006164a0`: reads the module accessor
  via `*(long*)(param_1 + 0x20)` (the pointer form, not the `+0x3f0` inline
  form), calls `status_module->vt[0x1b8]`, `status_module->vt[0x98]`
  (transition-term update), `status_module->vt[0x168]` (get_status_kind),
  then `area_module->vt[0x48]` (set_whole), and finally
  `*(long*)(param_1 + 0xf700)->vt[0x58](param_1)` — the post-status cleanup
  handler. Shape: `Fighter::post_status_update_hook`.

- Slot `+0x340` @ `0x7104f7f600` → `FUN_71006203d0`: takes a `battle_object_id`
  and returns `f32 * f32` — products of two `vt[0x50]`/`vt[0x58]` calls on
  `*(long*)(param_1 + 0xf908)` with a stack visitor `&PTR_FUN_7104f61cc8`.
  Shape: `Fighter::get_relative_scale(u32 target_id)` weight/scale query.

Both slots dereference `param_1 + 0xf908` — the same BattleObject-base pointer
reached via `param_1[0x1f21]` in slot `+0x2a8`. Cross-validation confirms one
class, not adjacent vtables.

**Cached layout upgrade.** The Fighter class therefore holds:

| Offset | Type | Role |
| --- | --- | --- |
| `+0x00` | `vtable*` | own class vtable @ `0x7104f7f2c0` |
| `+0x0c` | s32 | FighterKind |
| `+0x10` | u32 | entry_id |
| `+0x20` | `BattleObjectModuleAccessor*` | pointer alias to `+0x3f0` |
| `+0x3f0` | `BattleObjectModuleAccessor` | inline (0x158 bytes of submodule ptrs) |
| `+0x430..+0x568` | cached module ptrs | fast path for hot-loop readers (see table above) |
| `+0xf5a0` | `StageContext*` | per-stage flags |
| `+0xf700` | `PostStatusHandler*` | cleanup callback object (vt[0x58]) |
| `+0xf908` | `BattleObjectBase*` | outer BattleObject base — vt[0x30/0x38] pre/post, vt[0x50/0x58] scale/weight queries |

The vtable itself runs at least `0x7104f7f2c0..0x7104f7f900+` = ~0x70 slots =
224+ virtual methods. That is consistent with a concrete `FighterKind`
specializer class, not a generic base — the base `FighterBase` has fewer
virtuals.

### Caller chain to `main_loop`

Not yet mapped. The vtable slot is invoked indirectly by whatever drives
`StatusModule::exec_status` on each fighter's current-status object. The next
pass needs to:

1. Find a function that takes a `Fighter*` and calls `status_module->vt[exec]`,
2. Find who calls that function per-frame (the BattleObject-level update), and
3. Find who iterates those BattleObject updates.

Pool C is doing (3) via `BattleObjectWorld` / `BattleObjectManager`, so pool A's
most useful remaining contribution is (1) and (2): the Fighter-level update
bridge that sits between `BattleObjectManager::iterate()` and the status vtable
slot documented above.

### Next-session pickup

1. Read the 8 bytes at `0x7104f7f2b0` (typeinfo ptr slot of this vtable) and
   chase the typeinfo name string to identify the exact FighterKind specializer.
2. Walk the full vtable (~224 slots) looking for a slot whose body calls
   `status_module->vt[exec]` + `motion_module->vt[exec]` — that is the
   Fighter's own `process_fighter` / `update` virtual method.
3. `get_xrefs_to` that slot's address (even if only DATA, that gives the
   vtable base). Then `get_xrefs_to` the vtable base to find *all* Fighter
   classes using it, and trace their update calls.
4. Cross with Pool C's `BattleObjectManager` pool-header array @
   `DAT_71052b7548` iterators — the sim driver probably walks that pool and
   dispatches `obj->vt[update]()`.

### Gotcha — `data/functions.csv` sizes are unreliable in this region

`FUN_71006164a0` is listed in the CSV as 39,760 bytes, which looked like a
very strong "this is the fat update function" signal — but disassembly shows
the function actually ends at `0x7100616570` with a standard epilogue + `ret`,
and a preceding tail-call `br x2` via `[param_1 + 0xf700]->vt[0x58]`. True
size ≈ 208 bytes. Ghidra's analyzer merged this function with several
subsequent functions at the `br x2` indirect branch, inflating the size.
**Do not trust function sizes in `0x71006114xx..0x710062cxxx` without
cross-checking with disassembly** — the whole cluster is affected.

This also means the *actual* fat update function (if it is in this vtable
at all) has to be found by decompiling individual slots and looking at the
true instruction count, not the CSV size. Good candidates to try next:
`FUN_71006140c0`, `FUN_7100614180`, `FUN_7100614270`, `FUN_7100614360`,
`FUN_7100614470`, `FUN_71006145b0` (the cluster between the obvious
query helpers and the known exit handler).

### Verdict
PROGRESS — the FighterManager-vtable angle is disproven outright, but the pivot
through `FighterEntry +0xf0` found a concrete **FighterStatus vtable** at
`0x7104f7f2e8..+0x80` whose `FUN_7100614630` slot is a per-fighter, per-status
handler that fully reveals the Fighter's cached module-pointer layout. That
layout is strong evidence for pool-B/C's "sim driver iterates BattleObjects,
not the FighterManager entry array" prediction. Continuing toward the caller
of the status-exec slot next session.

---

## Pool C — `pead::Delegate` framework approach

### TL;DR — Verdict

**SIM TICK IS NOT A DELEGATE.** The `pead::Delegate` dispatch mechanism exists
in the binary and is used for auxiliary (network) threads, but it is not the
mechanism by which `main_loop` advances the sim. `pead::MainThread`'s message
queue is constructed and sized at 32 slots but **never drained** from inside
`main_loop`'s call chain. The sim tick must therefore be an ordinary `BL`
somewhere in the synchronous `main_loop` call tree.

**Implication for rollback:** do not try to post a "resim step" delegate to
`pead::MainThread` — nothing would ever pop it. Rollback resim must call the
sim tick function directly in a tight loop. The `pead::Delegate` framework
only matters for intercepting Pia network IO, which is an orthogonal concern
(packet capture/replay, not sim re-execution).

### Evidence: the pead::Thread message-queue dispatch loop

| Symbol | Address | Role |
|---|---|---|
| `pead::Thread::run()` | `FUN_710013b5e0` | generic pop-and-dispatch loop |
| `pead::Thread::__trampoline` | `FUN_710013c030` | nn::os::CreateThread entry; calls `run()` |
| `pead::Thread::__init_and_start` | `FUN_710013be00` | ctor that calls `nn::os::CreateThread(..., PTR_FUN_71052a4d28, ...)` |
| `ThreadMgr::adoptCurrentThread` → `pead::MainThread` | `FUN_710013c570` | wraps already-running initial thread (no `CreateThread`) |
| `pead::MessageQueueWrapper::receive(blocking)` | `FUN_710013bcb0` | `nn::os::(Try)ReceiveMessageQueue` wrapper |
| `pead::MessageQueueWrapper::send` | `FUN_710013bc98` | `nn::os::SendMessageQueue` wrapper |
| `pead::MessageQueueWrapper::initialize(cap)` | `FUN_710013bba0` | allocates backing `u64[cap]` and calls `nn::os::InitializeMessageQueue` |
| `pead::Thread` base vtable | `PTR_DAT_71052a4d20` → `0x7104f4dfc8` | |
| `pead::DelegateThread` vtable | `PTR_DAT_71052a4d00` → `0x7104f4ded8` | |
| `pead::MainThread` vtable | `PTR_DAT_71052a4d40` → `0x7104f4e0e8` | |
| `ThreadMgr` singleton instance ptr | `PTR_DAT_71052a3c08` | stores `MainThread*` at `[mgr + 0x80]` |

`pead::Thread::run()` decompiles to a textbook message-queue drain loop:

```c
// FUN_710013b5e0 — pead::Thread::run()
void pead_Thread_run(pead::Thread *self) {
    u64 msg = msgq_receive(&self->msgq, self->blocking_mode);  // +0x30, +0xb8
    while (msg != self->quit_sentinel) {                        // +0xc0
        (*self->vtable[16])(self, msg);                         // slot 16 = onMessage
        msg = msgq_receive(&self->msgq, self->blocking_mode);
    }
}
```

Slot 16 (byte offset `0x80` past the vtable pointer) is the virtual
`onMessage(delegate*)` override. `pead::DelegateThread` installs a version of
this slot that treats `msg` as a `pead::Delegate*` and invokes its operator().
That is the "runDelegates" equivalent the hunt was looking for — it is fused
into `run()` rather than existing as a standalone function.

### Evidence: pead::MainThread does not run the loop

`FUN_710013c570` (the only xref to the `"pead::MainThread"` string) is
`ThreadMgr::adoptCurrentThread`. Key fact: **it never calls
`nn::os::CreateThread`**. It wraps the already-running `nn::oe` initial
thread via `nn::os::GetCurrentThread` and stores the wrapped `pead::Thread`
object at `[ThreadMgr + 0x80]`.

Because `CreateThread` is never called for `MainThread`, the trampoline
`FUN_710013c030` (which is what would call `FUN_710013b5e0`) never runs for
it. The initial thread continues to execute whatever `nn::oe` scheduled as
its entry, which is `main_loop` at `0x7103747270`. The `pead::Thread::run()`
loop is therefore **bypassed** for `MainThread` — the message queue is alive
but no code pops from it unless `main_loop` or one of its children explicitly
calls the receive wrapper.

The MainThread's message queue is initialized at 32 slots:

```c
// excerpt from FUN_710013c570 (adoptCurrentThread)
plVar6[5] = "pead::MainThread";
FUN_710013bb80(plVar6 + 6);          // msgq zero-init
FUN_710013bba0(plVar6 + 6, 0x20, …); // 32-slot capacity
```

### Evidence: nothing drains the MainThread queue from main_loop

Full xref sweep of every `nn::os::*ReceiveMessageQueue` variant:

| NX SDK import | Address | Callers |
|---|---|---|
| `nn::os::TryReceiveMessageQueue` | `0x71039c0750` | `FUN_710013bcb0` only |
| `nn::os::ReceiveMessageQueue` | `0x71039c0760` | `FUN_710013bcb0` only |
| `nn::os::TimedReceiveMessageQueue` | `0x71039c6ed0` | **zero callers** |

And the pead wrapper `FUN_710013bcb0` itself has only three call sites — all
inside `FUN_710013b5e0` (the run loop) or an adjacent helper at `0x710013b6a8`.
**Nothing in `main_loop` or any of its children calls any message-queue
receive primitive.** The MainThread queue is a dead letterbox.

If the sim tick were posted as a delegate to `pead::MainThread`, nothing would
ever dispatch it and the game would deadlock on the first posted delegate.
Since the game runs, no sim-tick delegates are being posted to MainThread.

### Who DOES use the pead::Delegate queue?

The string table documents exactly four concrete `pead::Delegate2` / `IDelegate2`
instantiations in the binary:

| RTTI string | Address | Purpose |
|---|---|---|
| `pead::IDelegate1<const pead::PrintConfig::PrintEventArg&>` | `0x7104492830` | logging/print hook |
| `pead::Delegate2<nn::pia::common::BackgroundScheduler, pead::Thread*, long>` | `0x71044931a0` | posts work to pia background scheduler thread |
| `pead::IDelegate2<pead::Thread*, long>` | `0x7104493260` | base interface for the above |
| `pead::Delegate2<nn::pia::transport::TransportThreadStream, pead::Thread*, long>` | `0x71044981a0` | posts work to pia Send/Receive thread streams |

All of these are **nn::pia network threads** — not sim. They follow the
canonical path: caller calls `FUN_710013bc98` (SendMessageQueue wrapper) to
enqueue a `Delegate*` on the target thread's queue; the target thread's
`run()` (`FUN_710013b5e0`) pops it; `vtable[16]` dispatches. None of these
threads is `MainThread`, and none is involved in per-frame sim advance.

All seven unique callers of `nn::os::SendMessageQueue` were also checked;
they live in the `0x71036eXXXX` / `0x71036fXXXX` range (nn::pia / movie
subsystems) — none route a sim-tick payload.

### Delegates posted from main_loop's call chain

**None.** No call to the send wrapper `FUN_710013bc98` or raw
`nn::os::SendMessageQueue` is reachable from `main_loop` (`FUN_7103747270`)'s
transitive call graph. This was checked by enumerating every xref to the
send wrapper and the raw SDK imports and confirming none of the containing
functions appear in the `main_loop_bl_named.txt` cache.

| Posted from (caller in main_loop chain) | Delegate target | Frequency | Purpose |
|---|---|---|---|
| — | — | — | — |

(Empty — no delegates are posted from inside `main_loop`'s call chain.)

### What this rules out, and what it means for the next pass

Ruled out:
- Sim tick is **not** a posted `pead::Delegate`.
- Sim tick is **not** drained via any `nn::os::*ReceiveMessageQueue` call.
- `pead::MainThread` does **not** use its message queue; the 32-slot buffer
  at `[MainThread + 0x30]` is inert.

What must therefore be true:
- The sim tick is an ordinary synchronous `BL` somewhere inside the static
  call tree rooted at `main_loop` (`FUN_7103747270`).
- It lives on one of the phase children not yet fully decompiled — per
  `main_loop.md` § 6e next-pass priorities, the remaining suspects are
  `FUN_71035c13d0` (phase 6), `FUN_71036186d0` (phase 7), `FUN_7103619080`
  (phase 7), `FUN_7103593c40` (phase 5), and the 4,268-byte scene state
  machine `FUN_7103632850`.

Rollback implication (revised from `main_loop.md` § 6d):
- The earlier hypothesis that "rollback resim plugs into `pead::Delegate`"
  is **incorrect**. There is no delegate pump on MainThread to plug into.
- Rollback resim should call the sim tick function directly in a tight
  `for (i = 0; i < resim_frames; i++)` loop, with rollback-state restore
  before the loop and snapshot at the end.
- The `pead::Delegate` framework is still relevant to rollback, but only
  for intercepting `nn::pia` network IO on the Pia Send/Receive/Background
  threads (packet capture/replay, input ring buffer) — a separate concern
  from re-executing game logic.

### Artifacts this pass added

- Appended Ghidra decompiles to `data/ghidra_cache/pool-c.txt`:
  `FUN_710013c570` (adoptCurrentThread), `FUN_710013b5e0` (Thread::run),
  `FUN_710013be00` (Thread::__init_and_start), `FUN_710013c030` (trampoline),
  `FUN_710013bcb0` (msgq receive), `FUN_710013bc98` (msgq send),
  `FUN_710013bba0` (msgq init), `FUN_710013c200` (Thread::start).

---

## Pool A — FUN_71014f10c0 classification (2026-04-10)

### Identity verdict

**NOT a serializer. This is `app::GameState::finalizeMatch` — the
end-of-match teardown path.** The "40 reads of `DAT_710593a6a0`" lead
was a **false positive**: every one of those reads is the scene root's
fighter-roster `std::vector` being walked to **release** each entry's
`shared_ptr` chain as the match ends. The pattern is
`lock → null ptr slot → __release_weak → unlock`, repeated across the
10 (or 6) fighter slots depending on the match-exit kind.

Evidence that kills every "encoder" hypothesis:
- **Zero** `nn::os::SendMessageQueue`, `nn::ldn::*`, or `nnsocket::*` calls
  → not an LDN sync encoder.
- **Zero** `nn::diag::*`, `nn::dbg::*`, `printf`-family, or string literals
  → not a debug dumper.
- **Zero** `memcpy`/`memmove` writing into any `param_N` buffer; the
  sole parameter `param_1` is the `GameState*` being torn down, not a
  destination buffer → not a state encoder of any kind.
- **No counterpart decoder** because nothing was ever encoded.

Positive evidence for "match-end teardown":
- Calls `nn::oe::SetFocusHandlingMode` (applet focus) early.
- Zeroes ~15 shared_ptr / handle fields on `param_1` directly after.
- Iterates the 8 fighter-info pointers on `FighterManager + 0xE8..0x120`,
  constructs an `nn::mii::CharInfoAccessor` stack-local from each entry's
  CharInfo blob, checks `IsValid()`, then nulls the entry's shared_ptr.
  This is "release each fighter's Mii face data as the match ends."
- Memset-clears a 0x148-byte pad state block to the neutral-stick
  sentinel `0x5000000050000000`.
- Destroys a 0x480-byte effect-handle table at `*DAT_71052b8450`.
- Walks `DAT_71052b8440` calling `FUN_710064b2c0` on 96 slots at stride
  0x2c — handle-reset pattern.
- Destroys `std::__1::mutex`s on a 0x5e × 0x18 table at `DAT_71052bb3a8`.
- Match-exit-kind switch on `(param_1 + 0x60) & 0xfe`:
  - `== 4`: release shared_ptrs at strides 0x60, 0xC8, 0x130, 0x198,
    0x200, 0x268, 0x2D0, 0x338, 0x3A0, 0x408 (10 slots × 0x68 stride).
  - `== 10`: release 6 entries at indices 0x1b..0x20 (offsets 0xAE8,
    0xB50, 0xBB8, 0xC20, 0xC88, 0xCF0) — the biggest block. These are
    the ~30 reads that dominated the `DAT_710593a6a0` xref count.
  - `== 7 | 8`: release only the first 3 entries.
- Tail calls `FUN_71004f0710` to reset `BattleObjectWorld` time-scale
  and drops `lib::EffectManager` caches.

### FighterRosterEntry layout (the useful gift)

`DAT_710593a6a0` is `SceneRoot**`. The scene root has a
`std::vector<FighterRosterEntry>` at `scene_root + 0x24d0` (begin) /
`+ 0x24d8` (end). Ghidra emits the length calc as a multiply by the
magic `0x4ec4ec4ec4ec4ec5`, which is the reciprocal for `/ 0x68`, so
**each entry is 0x68 (104) bytes**. The vector can hold **at least 32
entries** (the Classic-mode branch bounds-checks to index 0x20).

| Offset into entry | Width | Meaning |
|---|---|---|
| +0x00 | 0x58 bytes | `nn::mii::CharInfo` blob (Mii face data) |
| +0x58 | 8 | `shared_ptr<T>::ptr` |
| +0x60 | 8 | `shared_ptr<T>::ctrl` |
| +0x68 | — | **next entry starts here** (stride = 0x68) |

And at the larger per-entry offsets seen in the exit-kind switch
(these are **not** inside one entry — they're indexes into the vector
at entry `n*0x68 + 0x58` / `+0x60`), giving the released-slot schedule
per match type above.

### Reads of DAT_710593a6a0 — corrected tally

Every "read" is actually `*DAT_710593a6a0` followed by `+0x24d0` or
`+0x24d8` to get the vector's begin/end pair, then index arithmetic
into that vector. The singleton itself has only two fields ever
touched by this function:

| Chain | Type | Purpose |
|---|---|---|
| `*DAT_710593a6a0` | `SceneRoot*` | outer ptr-to-ptr deref |
| `→ +0x24d0` | `FighterRosterEntry*` | `std::vector::begin` |
| `→ +0x24d8` | `FighterRosterEntry*` | `std::vector::end` |

Not 40 distinct field reads. Just the same two vector endpoints
reloaded before every per-entry release.

### Notable function calls

- `nn::mii::CharInfoAccessor::CharInfoAccessor` + `::IsValid`
- `nn::oe::SetFocusHandlingMode`
- `std::__1::mutex::{lock, unlock, ~mutex}`,
  `std::__1::recursive_mutex::{lock, unlock}`
- `std::__1::__shared_weak_count::__release_weak`
- `std::__1::__vector_base_common<true>::__throw_out_of_range`
- `ExclusiveMonitorPass` / `ExclusiveMonitorsStatus` (LL/SC refcount CAS)
- `je_aligned_alloc` (jemalloc — small allocs for observer list nodes)
- `memmove` (stage-observer vector compaction after removal)
- `__cxa_guard_acquire` / `__cxa_guard_release` (team-param static init)
- `abort()` (input-state walk guard at index 0x12)
- Many internal `FUN_` helpers: `FUN_7102606a00`, `FUN_710260b9b0`,
  `FUN_710260d050`, `FUN_7102608770`, `FUN_71037759f0`, `FUN_710371da60`,
  `FUN_710064b2c0`, `FUN_7100709a80` (FighterParamAccessor2 teardown),
  `FUN_7103563720` / `FUN_7103563a80` (EffectManager handle release),
  `FUN_71004f0710` (BattleObjectWorld frame reset).

### String constants referenced

**None.** No literal strings anywhere in the body. The `&LAB_*` /
`&PTR_*` addresses that appear in arg lists are vtable / code-pointer
constants (a stage-observer vtable, a loop-type descriptor, a
param-set key) — not strings.

### Implications for rollback walker

**Dead end for "ready-made save-state encoder", useful free gift for
the struct schema.**

The bombshell scenario ("Smash ships a built-in state encoder we can
wrap") is **ruled out by this function**. It is not an encoder.
Rollback save-state must still be hand-written.

However, the walk does hand rollback the exact slot layout of the
master fighter roster on the scene root: a `std::vector<FighterRosterEntry>`
at `scene_root + 0x24d0`, 0x68-byte stride, ≥32 capacity, with Mii
CharInfo at +0x00 and shared_ptr chains at +0x58 onward. These
lifetime-managed handles must appear in any correct snapshot walker.

The **real** 40-read serializer — if one exists at all — is a
different function. The `DAT_710593a6a0` xref count on this one was
inflated by the `shared_ptr`-release pattern reloading the vector
base/end on every iteration. Future xref-driven heuristics should
discount functions that also pattern-match `__release_weak` loops.

### Recommended rename

`FUN_71014f10c0` → `app::GameState::finalizeMatch_71014f10c0` (or
similar) in Ghidra. Pool-a will handle this in the next MCP round if
the server is responsive.

### Artifacts this pass added

- Ghidra decompile cached at
  `data/ghidra_cache/pool-a_FUN_71014f10c0.md` (2120 lines of C
  pseudocode).
- No `src/` changes — documentation-only pass per
  `WORKER-pool-a.md`'s primary deliverable.

---

## Pool A — DAT_710593a6a0 identity CORRECTION (2026-04-10)

**Major revision to pool-B's earlier classification.** The singleton at
`DAT_710593a6a0` is **NOT** the app-wide scene root. It is a
**Mii fighter-face database singleton** — an object that wraps
`nn::mii::Database` plus a per-fighter Mii entry vector and two head-
renderer command buffer shared_ptrs. This changes the interpretation
of almost every earlier pool-B finding on this singleton.

### Evidence chain

1. Pool-a decompiled `FUN_71022cd350` (writer site `0x71022cd600`).
   It is a **4100-line match-shutdown function** that destroys ~130
   battle-time singletons and ends with:
   ```c
   lVar14 = DAT_710593a6a0;
   if (DAT_710593a6a0 != 0) {
       FUN_7103757140(DAT_710593a6a0);   // dtor
       FUN_710392e590(lVar14);            // operator delete
       DAT_710593a6a0 = 0;                // null the global
   }
   ```
   It writes *null*, not a new object. So `FUN_71022cd350` is not the
   constructor we wanted — it's the "delete g_foo; g_foo = nullptr;"
   shutdown path. (Pool-B assumed both write xrefs were installers.
   They are not — at least one is a nuller.)

2. Pool-a then decompiled the destructor that shutdown called:
   **`FUN_7103757140`** (renamed in Ghidra to
   `MiiFighterDatabase_dtor_7103757140`, cached at
   `data/ghidra_cache/pool-a_FUN_7103757140.md`). It's small and
   tractable. The full body reveals:

   ```c
   // Field walk inside the destructor:
   this = (mutex*) *param_1;     // pointer-to-pointer deref
   *param_1 = 0;
   // +0x2500: shared_ptr release (ctrl block at +0x2508)
   // +0x24f0: shared_ptr release (ctrl block at +0x24f8)
   // +0x24d0/+0x24d8: std::vector<FighterMiiEntry>, stride 0x68,
   //                  entry.ctrl at entry+0x60, release then free buffer
   nn::mii::Database::~Database((Database*)(this + 0x20));
   std::__1::mutex::~mutex(this);    // mutex at offset 0
   FUN_710392e590(this);              // free the object
   ```

3. The `nn::mii::Database::~Database` call at offset `+0x20` is the
   smoking gun. `nn::mii::Database` is the NintendoSDK class that
   owns the console's Mii storage. Only a Mii-data singleton would
   embed one.

4. The two shared_ptrs at `+0x24f0` and `+0x2500` match **exactly**
   pool-C's FUN_7103577fd0 finding (that function decoded FNV strings
   `"lib::mii::HeadRenderer (ringed_command_buffer_opaque_)"` and
   `"lib::mii::HeadRenderer (ringed_command_buffer_translucent_)"`).
   Two command buffer shared_ptrs for two render passes — a perfect
   fit. FUN_7103577fd0 installs those two renderers into the Mii
   database singleton.

5. The 0x68-byte entries at `+0x24d0` vector each contain an
   `nn::mii::CharInfo` blob (0x58 bytes) followed by a `shared_ptr`
   pair (+0x58, +0x60). This exactly matches the `FighterRosterEntry`
   layout pool-a derived from `FUN_71014f10c0` — **and also explains
   why the 8 fighter-info pointers in FUN_71014f10c0 read a u16
   "mii index" at `FighterInfo + 0x68` and used it to look up an
   entry in this vector**. The index is a Mii database index, not a
   fighter-roster index.

### Corrected struct layout for DAT_710593a6a0's target

```
struct MiiFighterDatabase {   // size >= 0x2508
    std::mutex       mutex;                  // +0x00 (embedded, no vtable)
    /* +0x18 padding / mutex internals */
    nn::mii::Database db;                    // +0x20 (SDK member)
    /* +0x??..+0x24cf unknown */
    std::vector<FighterMiiEntry> entries;    // +0x24d0 begin, +0x24d8 end
    /* +0x24e0..+0x24ef unknown */
    std::shared_ptr<HeadRendererCmdBuf> opaque_cmd_buf;       // +0x24f0
    std::shared_ptr<HeadRendererCmdBuf> translucent_cmd_buf;  // +0x2500
    /* object total size determined by allocator, not visible in dtor */
};

struct FighterMiiEntry {   // size 0x68
    nn::mii::CharInfo char_info;   // +0x00 (0x58 bytes)
    std::shared_ptr<???> ptr;      // +0x58 / +0x60 (ctrl block)
};
```

This struct has **NO virtual methods** — the first member is a mutex,
not a vtable pointer. It's a plain singleton struct, not a polymorphic
class.

### What this invalidates

1. **Dispatcher A's "sim tick" lead at
   `[**(DAT_710593a6a0+0x24e8)+0x2da8]` is now suspect.** This dtor
   doesn't touch `+0x24e8` or any fields past `+0x2500`, which implies
   either:
   - The field at +0x24e8 isn't owned by this singleton (it's a raw
     back-reference to a sub-object owned elsewhere — consistent with
     "list of registered observers for Mii-data changes"), OR
   - Pool-B misread the offset chain in `main_loop` and the dispatcher
     is rooted in a different singleton entirely.

   Either way, **a Mii face-data singleton is an implausible home
   for the per-frame sim tick dispatcher**. The sim tick hunt should
   stop chasing `DAT_710593a6a0` and move to the other strong lead:
   Dispatcher B (the frame-scheduled queue) and the main_loop children
   `FUN_71035c13d0`, `FUN_71036186d0`, `FUN_7103619080`, `FUN_7103593c40`,
   `FUN_7103632850`.

2. **`FUN_71014f10c0` (renamed `GameState_finalizeMatch_71014f10c0`)
   is still correctly classified** as match-teardown, but its ~40
   reads of `DAT_710593a6a0` are specifically releasing per-fighter
   Mii face data at the end of a match — not fighter *state* and
   definitely not any form of state serialization. The Mii CharInfo
   is effectively constant for a match, so rollback does **not** need
   to snapshot it.

3. **"DAT_710593a6a0 is the scene root" from pool-B's
   "DAT_710593a6a0 identity — partial classification" section
   (2026-xx-xx) is wrong.** It is not a scene/match-runtime block.
   It is a Mii subsystem singleton. The text describing it as
   `app::Scene` / `app::GameMain` / `app::WorldManager` should be
   treated as superseded.

### Still open — FUN_71022b7100 (second writer)

The second WRITE xref at `0x71022c9fb4` (inside `FUN_71022b7100`)
**timed out** on Ghidra MCP. Logged to
`data/ghidra_cache/manual_extraction_needed.md` per the
stop-and-document rule. If it turns out to be the allocator/ctor, it
will either confirm or extend this struct layout. Best guess: it's a
lazy singleton getter that allocates + constructs the object + stores
it into DAT_710593a6a0 the first time it is accessed.

### Recommended renames in Ghidra

- `FUN_7103757140` → `MiiFighterDatabase_dtor_7103757140` **(done)**
- `FUN_71014f10c0` → `GameState_finalizeMatch_71014f10c0` **(done)**
- `DAT_710593a6a0` → `g_mii_fighter_database_710593a6a0` *(not yet —
  pool-B's existing docs all reference the `DAT_` name; leaving it
  unchanged to avoid a documentation stampede)*

### What rollback actually needs now

The rollback team should **stop investing in the 40-read lead**. The
real save-state walker is not discoverable through this singleton's
xrefs. Strong next moves in priority order:

1. Decompile the remaining main_loop phase children
   (`FUN_71035c13d0`, `FUN_71036186d0`, `FUN_7103619080`,
   `FUN_7103593c40`, `FUN_7103632850`) to find where the sim tick
   actually lives.
2. Xref-sweep `DAT_710593a530` (the match-state global Dispatcher A
   is gated on). Its writer is the match-life-cycle transition
   function and should name the true scene/match runtime root.
3. Decompile `FUN_71022b7100` once Ghidra MCP can handle it (or
   extract it manually) to confirm whether it's the Mii database
   ctor or a third unrelated writer.

### Artifacts this pass added

- `data/ghidra_cache/pool-a_FUN_71014f10c0.md` (2120 lines)
- `data/ghidra_cache/pool-a_FUN_71022cd350.md` (4103 lines)
- `data/ghidra_cache/pool-a_FUN_7103757140.md` (the dtor — with
  fully annotated field offsets)
- `data/ghidra_cache/manual_extraction_needed.md` (logs
  `FUN_71022b7100` as timed-out for next session)
- Ghidra renames: `FUN_7103757140` and `FUN_71014f10c0` as noted
  above.

---

## Pool A — FighterManager slot-release helper (2026-04-10, same session)

Decomped `FUN_710066e850` (renamed in Ghidra to
`FighterManager_releaseEightSlotPair_710066e850`). Reached via pool-a's
earlier decomp of the match-shutdown function `FUN_71022cd350`, which
called it on `lib::Singleton<app::FighterManager>::instance_` during
teardown. Full C is short enough to inline:

The function walks **8 paired slots** on its target object:

| Primary slot | Secondary slot | Width |
|---|---|---|
| `+0x20` | `+0x60` | 8 bytes each (pointer) |
| `+0x28` | `+0x68` | 8 bytes each |
| `+0x30` | `+0x70` | 8 bytes each |
| `+0x38` | `+0x78` | 8 bytes each |
| `+0x40` | `+0x80` | 8 bytes each |
| `+0x48` | `+0x88` | 8 bytes each |
| `+0x50` | `+0x90` | 8 bytes each |
| `+0x58` | `+0x98` | 8 bytes each |

Plus a counter field at `+0xA0` (s32, incremented when promoting a
secondary into a primary and decremented on successful release) and a
flag byte at `+0xB20` cleared to 0 at function exit. Object size is
therefore **at least 0xB21 bytes** — big enough to be FighterManager's
primary data block.

**Promotion pattern** (for each of the 8 pairs):
```
if (secondary != null && primary == null) {
    primary = secondary;
    secondary = null;
    counter++;
}
if (primary != null) {
    FUN_7100653490(primary, 1);   // slot release step 1
    FUN_71006524e0(primary);       // slot release step 2
    FUN_7100652160(primary);       // slot release step 3
    FUN_710392e590(primary);       // je_free / operator delete
    primary = null;
    counter--;
}
```

**Interpretation.** The 8 pairs almost certainly encode the **8-player
max SSBU match roster with a two-form-per-fighter slot design**. The
primary/secondary pair smells like "current form / alternate form" for
transforming characters (Zelda↔Sheik, Samus↔ZSS, Pokemon Trainer's 3
pokemon, etc.), where the currently active form sits in the primary
slot and inactive forms park in the secondary slot. The "promote
secondary into primary if primary is empty" logic on teardown confirms
this: if the fighter was in their alternate form at match end, the
teardown still has to release the primary-slot memory of that form.

The `FUN_7100653490` / `FUN_71006524e0` / `FUN_7100652160` /
`FUN_710392e590` chain is the canonical BattleObject destructor
sequence:
1. step 1: mark-for-release / detach from managers
2. step 2: run virtual finalizer
3. step 3: run base-class dtor chain
4. step 4: `je_free`

### Does this prove +0x2da8 lives on FighterManager?

**No.** This helper only touches offsets `0x20`–`0x98`, `0xA0`, and
`0xB20` on its target. It does not reach `0x2da8`. So nothing said here
confirms or denies Pool-B's hypothesis that Dispatcher A's walk list
at `[**(DAT_710593a6a0+0x24e8)+0x2da8]` is a field on FighterManager.

However, **the chain makes sense if `mii_db->field_0x24e8` is a raw
back-reference to FighterManager**:
- Mii database holds a vector of per-fighter CharInfo entries.
- It keeps a back-ref to FighterManager at `+0x24e8` to look up live
  fighter state when installing CharInfos.
- FighterManager at `+0x2da8` has its observer/sub-manager list that
  Dispatcher A iterates each frame.

This would make `FighterManager + 0x2da8` the **actual** sub-manager
tick list Dispatcher A walks. The per-frame method called is slot
`+0x28` on each node's vtable, and the walk has an early-out on first
truthy return — which is still pattern-inconsistent with a sim-tick
dispatcher (sim ticks run ALL entities), but consistent with "find
first active game phase and run its frame hook."

### Where to look next (pool A handoff)

Confirming the hypothesis requires decompiling **FighterManager's full
constructor** (find it by xref-sweeping `lib::Singleton<app::FighterManager>::instance_`
for the WRITE with an allocator) or its **full destructor**
(which is a different function than the helper above — the helper's
caller, visible in FUN_71022cd350 at line ~231 onward). A 0x2da8-sized
object ctor or dtor will enumerate the sub-manager list layout and
prove/disprove +0x2da8.

If the FighterManager ctor is tractable, it also exposes the primary/
secondary slot allocation pattern, which is rollback-useful because
those slots are where per-fighter simulation state actually lives.

### Renames this session

- `FUN_7103757140` → `MiiFighterDatabase_dtor_7103757140`
- `FUN_71014f10c0` → `GameState_finalizeMatch_71014f10c0`
- `FUN_710066e850` → `FighterManager_releaseEightSlotPair_710066e850`

### Cached decomps this session (all gitignored under data/ghidra_cache/)

- `pool-a_FUN_71014f10c0.md` (2120 lines)
- `pool-a_FUN_71022cd350.md` (4103 lines)
- `pool-a_FUN_7103757140.md` (annotated Mii database dtor)
- `manual_extraction_needed.md` now lists `FUN_71022b7100`

No src/ changes — this entire session was research / doc / Ghidra
labeling per WORKER-pool-a.md "Documentation is the primary
deliverable."

---

## Pool A — Correction: FUN_71004f0710 is camera reset, not BattleObjectWorld

The previous pool-a commit (`pool-a: DAT_710593a6a0 is the Mii fighter
database...`) labeled `FUN_71004f0710` as "BattleObjectWorld frame
reset" based on context from the FUN_71022cd350 teardown. That label
was wrong.

Decompilation of `FUN_71004f0710` shows it is a **camera reset to
match-default state**, not BattleObjectWorld-related. Evidence:

- Sets multiple `0x42aa0000` (85.0f — default FOV) fields on a camera
  sub-object at `param_obj + 0x30`.
- Writes `0x3f800000` (1.0f — default scale/zoom), `0xc1200000 /
  0x41200000` (−10.0 / +10.0 — view bounds), `0x7f7fffff` (FLT_MAX
  for an initial distance-to-target search).
- Walks two sub-camera pointers at `param_obj->cam + 0x08` and
  `+ 0x10` and re-initialises their transform matrices to default
  values loaded from `_DAT_71044xxx` RODATA constants.
- Writes identity transform pairs (`0x4218000042180000` = 38.0f)
  for unit scale.
- Ends by building a stack-local `PTR_LAB_7104f73ca0` observer and
  calling the **named** function `change_active_camera(lVar12, 0, 0,
  local_70, 0)`. This is the smoking gun — the function installs a
  new active camera.

**Renamed in Ghidra:** `FUN_71004f0710` → `Camera_resetToMatchDefaults_71004f0710`.

This does not affect the rollback conclusions in the prior commit;
it just cleans up a function label. It does, however, reveal that
the match-shutdown path in `FUN_71022cd350` explicitly resets the
camera back to default state on match end — which, combined with
the fighter roster release and the Mii data release, paints
`FUN_71022cd350` as the broad "exit a match, put everything back to
pre-match defaults" function. A genuine `BattleObjectWorld::reset()`
(if one exists) remains unlocated.

### Session summary — pool A, 2026-04-10

Hours of compute spent: one session. Functions decomped and
classified: five. Committed findings: three (this makes four).
Ghidra renames: four
(`GameState_finalizeMatch_71014f10c0`,
`MiiFighterDatabase_dtor_7103757140`,
`FighterManager_releaseEightSlotPair_710066e850`,
`Camera_resetToMatchDefaults_71004f0710`).

Net effect for the rollback team:
1. Pool-B's "40-read serializer" bombshell lead on `FUN_71014f10c0`
   is **cleared** — it's a match-teardown releasing per-fighter Mii
   face data, not a state encoder.
2. Pool-B's "DAT_710593a6a0 is the scene root" identity is
   **corrected** — it's actually the Mii fighter-face database, not
   any form of scene/world runtime block. Full struct layout derived
   from its destructor.
3. FighterManager's primary/secondary 8-slot pair layout is
   **documented** for the first time — useful for rollback's fighter
   iteration design.
4. The sim tick is **still not located**. Dispatcher A remains the
   most likely candidate, but its walk is rooted in Mii database
   territory, making a sim-tick interpretation implausible. The
   walk's early-out-on-first-truthy-return is also inconsistent with
   a "tick all fighters" dispatcher. Real sim tick is probably
   nested deeper than `main_loop`'s direct children and may require
   decompiling `FighterManager::ctor` or a `BattleObjectWorld::tick`
   yet-to-be-found to locate.
5. `FUN_71022b7100` (the other `DAT_710593a6a0` WRITE xref) timed
   out on Ghidra MCP. Logged to `data/ghidra_cache/manual_extraction_needed.md`
   for orchestrator extraction.

---

## Pool B — DAT_710593a6a0 is NOT the scene root (major course correction)

### Summary

The earlier pool-b classification of `DAT_710593a6a0` as a "scene root"
singleton is **wrong**. Direct evidence from the type's destructor and from
the heaviest client function shows it is a **fighter-Mii manager singleton**
that embeds an `nn::mii::Database` at `+0x20` and a per-fighter-slot vector
of Mii character entries at `+0x24d0`. The Dispatcher-A walk at
`[**(DAT_710593a6a0 + 0x24e8) + 0x2da8]` is therefore **not** walking a
scene-root tickables list — `+0x24e8` is a non-owning back-reference to
some other manager whose own `+0x2da8` field holds the list. Whoever wrote
the Dispatcher-A lead in this document treated `+0x24e8` as if it were a
field owned by the singleton; it is instead a weak/raw pointer to an
unrelated subsystem.

This retires the "FUN_71022cd350/FUN_71022b7100 = scene root constructors"
lead from `WORKER-pool-b.md`. The single most important implication is
that **sim tick is not rooted here at all** and the next-pass priorities
listed above (FUN_71035c13d0, FUN_71036186d0, FUN_7103619080, FUN_7103593c40,
FUN_7103632850) remain the only live candidates.

### Evidence 1 — `FUN_71022cd350` is a global teardown, not a constructor

Ghidra decompile was 145 KB, so the output went to the tool-results dir and
was analyzed via an `Agent` sub-process (see pass notes below). Key line in
the decompile:

```c
lVar14 = DAT_710593a6a0;
if (DAT_710593a6a0 != 0) {
    FUN_7103757140(DAT_710593a6a0);   // explicit destructor of the singleton's type
    FUN_710392e590(lVar14);            // global free (seen ~70× in this fn)
    DAT_710593a6a0 = 0;
}
```

That is a textbook `if (p) { p->~T(); operator delete(p); p = nullptr; }`.
The function contains **no `operator new`, no vtable install, no writes to
`+0x24d0`/`+0x24e8`/`+0x2da8` on any local `this`**, and **no string
literals at all**. The rest of its body is ~50 more back-to-back teardown
blocks that null out sibling singletons in the range
`DAT_710593a3d0 / a3d8 / a438 / a5f0 / a6a0 / a6b0 / ...` — a whole family of
scene-layer singletons that all get torn down together at shutdown / scene
reset.

Cross-check with Ghidra's xref database: the **only** recorded write to
`DAT_710593a6a0` is at `0x71022cd600` inside `FUN_71022cd350` — exactly
the `DAT_710593a6a0 = 0;` null-out shown above. The `WORKER-pool-b.md`
claim that `FUN_71022b7100` also writes it at `0x71022c9fb4` is not
reflected in xrefs; either that write happens through an address-taken
indirection (there is a reader symbol literally named
`clone_write_entry_to_bss` at `0x7101788ec0`, which strongly suggests a
templated "clone a heap object into a bss slot" helper), or the prior pool
confused a read site for a write.

### Evidence 2 — the type's destructor reveals the field layout

`FUN_7103757140` (`0x7103757140 - 0x7103757283`, 0x144 bytes) is the
explicit destructor called on `DAT_710593a6a0`. It is small enough to quote
in full here:

```c
void FUN_7103757140(undefined8 *param_1) {
    this = (mutex *)*param_1;
    *param_1 = 0;
    if (this == 0) return;

    // +0x2500: shared_ptr — release
    plVar6 = *(long **)(this + 0x2500);
    if (plVar6 != 0) { ExclusiveMonitor decrement of plVar6[1]; ... }

    // +0x24f0: shared_ptr — release
    plVar6 = *(long **)(this + 0x24f0);
    if (plVar6 != 0) { ExclusiveMonitor decrement of plVar6[1]; ... }

    // +0x24d0 / +0x24d8: std::vector<T> where sizeof(T) = 0x68
    // walks backwards, releasing a shared_ptr at node[-1] (i.e. entry+0x60)
    lVar4 = *(long *)(this + 0x24d0);           // begin
    lVar7 = *(long *)(this + 0x24d8);           // end
    while (lVar7 != lVar4) {
        lVar7 -= 0x68;
        plVar6 = *(long **)(lVar7 - 8);         // entry's trailing shared_ptr
        if (plVar6) release_weak(plVar6);
    }
    if (lVar4 != 0) FUN_710392e590();           // free the vector's storage

    // +0x20: nn::mii::Database subobject — CALLED BY NAME
    nn::mii::Database::~Database((Database *)(this + 0x20));

    // the singleton itself is a mutex base
    std::__1::mutex::~mutex(this);
    FUN_710392e590(this);                        // free the object
}
```

The smoking gun is `nn::mii::Database::~Database((Database *)(this + 0x20))`
— Ghidra demangled this call automatically, so the symbol comes from RTTI,
not guesswork. `DAT_710593a6a0` embeds an `nn::mii::Database` at `+0x20`.

Fields proven by the destructor:

| Offset    | Kind                                | Notes                                    |
|-----------|-------------------------------------|------------------------------------------|
| `+0x00`   | `std::mutex` base class (4 ptrs)    | fn casts `this` to `mutex*` + destructs  |
| `+0x20`   | `nn::mii::Database` (embedded)      | named by destructor's RTTI call          |
| `+0x24d0` | `std::vector<T>::begin` (`T*`)      | `T` size = 0x68                          |
| `+0x24d8` | `std::vector<T>::end` (`T*`)        |                                          |
| `+0x24e0` | `std::vector<T>::end_of_storage`    | not touched by destructor but implied    |
| `+0x24e8` | **raw pointer (non-owning)**        | *touched by Dispatcher A, NEVER freed*   |
| `+0x24f0` | `std::shared_ptr<X>` (ctrl, data)   | released                                 |
| `+0x2500` | `std::shared_ptr<Y>` (ctrl, data)   | released                                 |

Crucially: **`+0x24e8` is never touched by the destructor.** In libc++ and
any owning smart-pointer idiom you would expect a destruction call here; its
absence is strong evidence that `+0x24e8` holds a **non-owning back-reference**
to some externally-managed object (raw `T*`, not a `shared_ptr` or `unique_ptr`).

### Evidence 3 — the heaviest reader confirms the "fighter-Mii" semantic

`FUN_71014f10c0` (the function with 30+ reads of `DAT_710593a6a0`, more than
any other caller) was decompiled (79 KB, analyzed via `Agent` sub-process).
It is a **match-end / battle-teardown** routine:

- Iterates FighterManager's 8 player slots at `[DAT_7105323680 + 0xe8..+0x120]`
- For each live fighter, reads the entry's `nn::mii::CharInfo` from
  `*DAT_710593a6a0 + 0x24d0 + entry_id*0x68` and releases the shared_ptr at
  entry `+0x58`/`+0x60`
- Calls `nn::mii::CharInfoAccessor::CharInfoAccessor((CharInfoAccessor *)..., (CharInfo *)...)`
  and `nn::mii::CharInfoAccessor::IsValid()` **eight times** — once per
  fighter slot
- Divides (end-begin) by 0x68 using the classic `0x4ec4ec4ec4ec4ec5` magic
  multiplier — confirming `sizeof(entry) == 0x68`

It touches **only** `+0x24d0` and `+0x24d8` on the singleton. It does NOT
touch `+0x20`, `+0x24e8`, `+0x24f0`, `+0x2500`, or `+0x2da8`. Zero string
literals in the function body.

An entry is 0x68 bytes and contains a `nn::mii::CharInfo` (0x58 bytes in
NintendoSDK 8.2.1) plus a `std::shared_ptr` at the trailing 0x10 bytes.
That shared_ptr is per-fighter-slot: it is released during match-end.

### Conclusion on `DAT_710593a6a0` identity

Best-fit type: a match-owned "**fighter Mii manager**" singleton. It embeds
an `nn::mii::Database` (the raw Mii cache) at `+0x20` and a
`std::vector<FighterMiiEntry>` at `+0x24d0`, where each entry holds a
`nn::mii::CharInfo` + a shared_ptr to a rendered Mii asset (likely the
head model or texture). Candidate names in the `app::` namespace:
`app::FighterMiiManager`, `app::MiiCharManager`, `app::CpuMiiManager`.
No string literal proves the name yet; extraction of the mysterious
`FUN_71022b7100` constructor (too large for MCP, see
`data/ghidra_cache/manual_extraction_needed.md`) or of
`clone_write_entry_to_bss` at `0x7101788ec0` would likely clinch it.

### Impact on Dispatcher A

The prior pool-b writeup says Dispatcher A walks
`[**(DAT_710593a6a0 + 0x24e8) + 0x2da8]` and treats that as the scene
tickables list. That walk is **real**; it just doesn't mean what the prior
pass said it means:

- `+0x24e8` is a **non-owning raw pointer** on the Mii manager. It points
  to an external object that the Mii manager does not own. That external
  object has its own `+0x2da8` field which is the list head.
- The external object is therefore **some other subsystem** (FighterManager,
  BattleObjectWorld, GameState, Stage, …) and Dispatcher A is walking
  **that** subsystem's internal list. The Mii manager is just a convenient
  handle to grab from `main_loop` because it is already in scope.
- This reduces Dispatcher A's signal value for the sim-tick hunt: it tells
  us there is *some* cross-subsystem back-reference, not that we have
  located the scene root. The hunt for the true sim tick stays on the
  phase-6/phase-7 candidates in `main_loop.md` § 6e.

### Safety-smoke-test implication for rollback resim

The fallback task in WORKER-pool-b.md asked Pool B to decompile
`vtable[+0x28]` of a node in Dispatcher A's list and check whether it
touches host services (audio/gfx/LDN/fs). That test is still *doable* but
its **interpretation** changes:

- Before: "if `vtable[+0x28]` is dirty, rollback needs a service shim".
- Now: the list isn't necessarily tickables, so a dirty `vtable[+0x28]`
  doesn't indict the sim tick — it only indicts whatever unknown subsystem
  the `+0x24e8` back-reference points at. The test is only meaningful once
  we identify that subsystem.

Pool B recommends the orchestrator **defer the safety smoke test** until a
pool has identified what type lives at `+0x24e8`. That needs one of:

1. Manual export of `FUN_71022b7100` from Ghidra (1.7 MB disassembly) to
   find the *real* construction path of the Mii manager and see what gets
   wired into `+0x24e8`.
2. Decompile of `FUN_7101788ec0` (named `clone_write_entry_to_bss`) —
   likely a helper that the constructor calls with `&DAT_710593a6a0` and
   with the Mii-manager template data; may show how `+0x24e8` gets set.
3. A targeted xref hunt: find every function that writes to
   `*(DAT_710593a6a0) + 0x24e8`. Ghidra does track structure-field xrefs
   if the singleton has a struct type attached, but since
   `DAT_710593a6a0` is still `undefined *`, those xrefs don't exist yet.

### Dispatcher A — the double-deref chain, read literally

Re-reading `asm/ghidra_FUN_7103747270.c` line 558 after the identity rollback:

```c
lVar48 = *(long *)(**(long **)(&DAT_000024e8 + *DAT_710593a6a0) + 0x2da8);
```

Ghidra's `&DAT_000024e8` is a fabricated "cast constant to pointer" artifact; in
real C the expression is:

```c
//   mii    = the Mii manager instance (singleton)
//   P1     = raw pointer stored on the Mii manager at +0x24e8
//   Y      = the object whose address is stored as the FIRST QWORD of P1
//   list   = Y + 0x2da8 (circular list head with sentinel pair at +0x30/+0x38)
app::FighterMiiManager *mii = *DAT_710593a6a0;
void          **P1   = *(void ***)((char *)mii + 0x24e8);
void           *Y    = *P1;                           // load first qword of *P1
list_head_t    *list = (list_head_t *)((char *)Y + 0x2da8);
```

So the chain is **three** loads deep from `DAT_710593a6a0`: (i) load the
singleton pointer, (ii) load `mii->field_0x24e8`, (iii) load `*field_0x24e8`.
That extra indirection level is the giveaway that `+0x24e8` is a
*pointer-to-handle*, not a direct owning pointer:

- Candidate (a): `+0x24e8` holds a `std::shared_ptr<Y>*` — i.e. the Mii
  manager holds a pointer into someone else's shared_ptr (control block +
  data pair). Reading the first qword of a `shared_ptr` returns the
  `data_ptr` (= `Y`).
- Candidate (b): `+0x24e8` holds a `ReferenceWrapper<Y>*` — a thin wrapper
  struct whose first field is `Y*`.
- Candidate (c): `+0x24e8` holds the address of another bss global that
  holds `Y*` (a pointer to a pointer — unusual, but possible if the Mii
  manager caches the address of e.g. `&DAT_710593a530` or a similar globals
  bank).

All three candidates are consistent with the destructor's refusal to touch
`+0x24e8` — in none of them is `+0x24e8` owning the pointee.

The same `main_loop` function only contains **one** read of
`DAT_710593a6a0` (grep of `asm/ghidra_FUN_7103747270.c` shows line 558 is
the sole match). So Dispatcher A is the only place in `main_loop` that
reaches through the Mii manager at all; the rest of `main_loop`'s
subsystems are reached through their own globals.

### Pool B pass notes / artifacts

- Full decompile of `FUN_71022cd350` (145 KB) is cached in the harness
  tool-results dir (path in `data/ghidra_cache/manual_extraction_needed.md`);
  no need to re-extract — the sub-agent pass already mined it.
- Full decompile of `FUN_71014f10c0` (79 KB) similarly cached; same note.
- `FUN_7103757140` (the type destructor) is tiny and quoted in full above.
- `FUN_71022b7100` is 1.7 MB of raw disassembly (body 0x71022b7100 –
  0x71022cd31f ≈ 90 KB of code). Listed in
  `data/ghidra_cache/manual_extraction_needed.md` with LOW priority — the
  destructor plus reader give us enough type information to retire the
  scene-root hypothesis, so the constructor decomp is no longer critical
  to the sim-tick hunt.

---

## Pool C — DAT_710593a530 match-state transition (CRITICAL CORRECTION)

**TL;DR.** Pool C was asked to find the writer of `DAT_710593a530` (the match-state global that Pool B's breakthrough identified as gating Dispatcher A). After a full static sweep of the `.text` segment using direct binary analysis (because Ghidra's xref index misses code regions the auto-analyzer has not carved into functions), the finding is:

- **Only one static writer exists**, and it writes `0` via `STP XZR, XZR`.
- **No static writer of the value `3` exists anywhere in `.text`.**
- **The `== 3` branch in `main_loop` (and in two other readers) is therefore dead under static analysis** — or depends on a runtime write path we cannot see without hardware tracing.

This means Pool B's Dispatcher A lead (still "strongest remaining sim-tick candidate" as of the prior section) is **probably unreachable at runtime**, and the sim-tick hunt should de-prioritize Dispatcher A until dynamic evidence confirms the flag ever holds `3`.

### Why Ghidra's xref said "only 2 reads, no writes"

`mcp__ghidra__get_xrefs_to 0x710593a530` returned only:
- `0x7103747bf8 in FUN_7103747270` (READ) — the `main_loop` site Pool B found
- `0x71036552c8` (READ) — in a Ghidra-undefined code region

Ghidra's xref index was incomplete. A **direct binary scan** of all ADRP-based accesses to page `0x710593a000` in the R+X segment revealed **one more reader** and **one writer** that Ghidra didn't index — all three in code regions Ghidra's auto-analyzer has not carved into functions:

```
READERS (3 total):
  0x7101f17f7c  LDR W8,  [X8, #0x530]  -- in Ghidra-undefined fn at ~0x7101f17ef0, cmp #3, B.EQ
  0x71036552c8  LDR W8,  [X8, #0x530]  -- in Ghidra-undefined fn at ~0x7103655274, cmp #3, B.NE
  0x7103747bf8  LDR W9,  [X8, #0x530]  -- in main_loop FUN_7103747270, cmp #3, B.NE (the known one)

WRITERS (1 total):
  0x71004467ec  STP XZR, XZR, [X1, #0x40]
                X1 = ADRP(0x710593a000) + 0x4f0 = 0x710593a4f0
                --> 8 bytes of zeros at 0x710593a530 and 0x710593a538
                in Ghidra-undefined fn starting at 0x7100446400
```

### The one writer is a BSS zeroing ctor from `.init_array`

The function containing `0x71004467ec` starts at `0x7100446400` (nearest prior `RET` + prologue `SUB SP, SP, #0x20 / STP X29, X30, [SP, #0x10]`). It is **not** in Ghidra's function list but it **is** referenced by a dynamic relocation into `.init_array`:

```
.rela.dyn: reloc at .init_array[0x8a0] -> 0x446400
```

This is slot **276** (`0x8a0 / 8`) of the 306-entry `.init_array` dynamic relocation table. The function runs **once at program startup** as a global constructor, and the STP at `0x71004467ec` is simply zero-init for a BSS struct rooted at `0x710593a4f0`. The same ctor writes `X8` to `[0x710593a528]` (a sub-pointer), zeros at `[0x710593a530..0x710593a540)`, and later writes a `STLRB` to `[0x710593a540]`. Its total footprint is roughly `0x710593a4f0..0x710593a570`.

**Conclusion: the lone static writer of `DAT_710593a530` is a one-shot BSS clear, not a state transition.**

### The value `3` is never stored at this address by static code

Additional search verified no alternative write paths exist:
- No instruction stores a register that holds the literal constant `3` to this address via any ADRP-based or pointer-register-based addressing form (checked: `STR W/X`, `STRB`, `STRH`, `STUR W/X`, `STP W/X` off/pre/post-index, `STLR W/X/B`, `STXR W`).
- No `BL` call passes the address `0x710593a530` in `X0..X7` as an argument register (would indicate a setter helper).
- No code stores the address `0x710593a530` as a pointer literal into another global (would indicate indirect writes via a stored pointer).
- The only `BL` found with an argument register in the nearby range `[0x710593a500, 0x710593a540]` is `BL 0x710353d000` at `0x7103741c90` with `X0 = 0x710593a520` — but `FUN_710353d000` is a `je_aligned_alloc`-backed factory that allocates a 0x260-byte object, writes `3` at **the heap object's `+0x40`** (not at `[X0 + 0x10]`), and stores the heap pointer via `*param_1 = __s` (so `[0x710593a520]` gets a heap pointer, not the value `3`).

### State machine — no state machine

Because no static code writes a non-zero value to `DAT_710593a530`, there is no state diagram to document. The variable is BSS (starts at 0), zeroed once at ctor time, and read in three places that all test `== 3`. All three test sites therefore statically never take the "match-active" branch.

### Atomicity

Moot, since there are no non-zero writers. For completeness: the single writer uses `STP` (plain, non-release). The readers all use plain `LDR W`. No exclusive / release / acquire forms are used against this address.

### Implications for the sim-tick hunt and rollback

1. **Pool B's Dispatcher A should be demoted from "strongest remaining sim-tick candidate".** The per-element vtable walk at `main_loop` lines 543..572 is gated on `DAT_710593a530 == 3`, a branch that under static analysis is never taken. Either:
   - (a) The branch is dead code — plausible; it could be a debug/devkit path left in the retail binary.
   - (b) The variable is written at runtime via a mechanism invisible to static analysis (IPC, devkit override, memory-mapped register, or a code path that composes the address in an unusual way that defeats ADRP-propagation scanning).
2. **The match-active state machine is somewhere else.** Pool C could not find "the writer of 3 on match start" because it does not exist at this address. Candidates for the real match-state flag should be searched among the other `0x710593a___` region globals that DO receive non-zero static writes — e.g. the byte-store cluster around `+0x540..+0x5a0`, or the integer at `+0x534` which receives function-return values at `0x7103741bb4` and `0x71037472d0`.
3. **Rollback arm/disarm signal is still unknown.** This was the "two-for-one" ask in the pool-C assignment; the answer is that `DAT_710593a530` is NOT the signal. A next pass should either (a) run GDB against eden/yuzu, set a watchpoint on `0x710593a530`, and enter/exit a match to see whether it is ever written at runtime, or (b) pick a different candidate for "match-active flag" by enumerating readers of the `0x710593a___` block and filtering for ones that branch on a non-zero comparison AND have writers that store non-zero values.

### Ghidra undefined-code observation

All three access sites that Ghidra's xref missed (`0x7101f17f7c`, `0x71036552c8`, `0x71004467ec`) lie in code regions the auto-analyzer has **not** carved into functions. `mcp__ghidra__get_function_by_address`, `decompile_function_by_address`, and `disassemble_function` all return "no function" at those addresses and at their nearest-prior function starts (`0x7101f17ef0`, `0x7103655274`, `0x7100446400`). This is the same class of Ghidra-DB gap Pool B hit on Dispatcher B's writer at `0x7103752f08..0x7103753fbf`. Logged to `data/ghidra_cache/manual_extraction_needed.md`.

### Methodology note for next pool

The right tool for "who writes this global" when Ghidra's xref index is incomplete is **direct ADRP-propagation scanning on the raw `.text` bytes**. The steps:

1. Parse the ELF program headers to locate the R+X segment.
2. Walk 4 bytes at a time. For each `ADRP` whose computed target page is within ±4 MB of the variable, start a small forward data-flow: track `{ADRP_Rd: page_base}` and propagate through `MOV Xd, Xn`, `ADD Xd, Xn, #imm` (both shifts), `SUB Xd, Xn, #imm`. Stop on `RET` or unconditional `B`.
3. At every memory instruction, check whether its `Rn` is currently tracked and whether `(tracked_val + scaled_imm)` hits the target.
4. Cover all store forms: `STR W/X`, `STRB/H`, `STUR W/X`, `STP W/X` off/pre/post, `STLR W/X/B`, `STXR W/X`, and the matching loads for read-tracking.
5. Also check every `BL` where an argument register `X0..X7` holds the exact target (setter-helper pattern) and every store where the source register currently holds the target (pointer-init pattern).

For the record, Pool C's scanner found 3 reads, 1 write, 0 setter-helper `BL` calls, 0 pointer-init stores, searching the full ~60 MB `.text`. Total scan time ~10 s per query. The script lived in the pool-c scratch buffer (not committed); a next pool that wants a reusable version should write it to `tools/xref_bin_scan.py`.

---

## Pool A — mii_manager+0x24e8 back-reference (DEAD END CONFIRMED)

**TL;DR.** The back-reference at `MiiFighterDatabase + 0x24e8` points to a
`lib::mii::MiiModel_Renderer` — a 0x2db0-byte **graphics/rendering subsystem**
that owns shaders, VSM shadow passes and draw material slots. Its list at
+0x2da8 is a render-node list, not a list of tickable game objects.
Combined with Pool C's finding that `DAT_710593a530 == 3` is never written
statically, Dispatcher A is now **double-dead**: its gate flag never
triggers *and* its list is for Mii rendering. The sim-tick hunt must look
elsewhere. Retire Dispatcher A from the candidate board.

### Methodology

Pool C's ADRP-propagation scan technique was committed as
`tools/xref_bin_scan.py` so future pools can reuse it without rewriting.
A follow-up `tools/scan_mii_24e8.py` layered two hunting modes on top:

1. **External writer** pattern: track every `ADRP 0x710593a000; LDR [.,#0x6a0] -> Rm`
   and look for later `STR [Rm, #0x24e8]`. **Zero hits.** No function in
   the binary loads the Mii manager singleton pointer *from the global*
   and then writes its +0x24e8 field. The writer therefore has to be
   a method that already has the `this` pointer in X0.

2. **Method-form writer** pattern: sweep every `STR Xt, [Xn, #0x24e8]`
   where Rt is not XZR, trace Rn backwards through the function to see
   whether it was initialised from `MOV Rn, X0` at entry. Five raw hits,
   reduced to the single real candidate via caller analysis.

Then used `tools/find_callers.py` to count BL callers of each candidate
function. This is the step that identified the right writer conclusively:
only one of the candidates had a caller that lived inside the Mii manager
constructor body (`0x71022b7100..0x71022cd31f`).

### Writer site

- **Writer instruction**: `0x7103757cd0: STR X20, [X19, #0x24e8]` is the
  actual field store. X19 = Mii manager (the `this` pointer, passed in
  X0 at function entry and copied to the callee-saved X19). X20 = the
  newly-allocated back-referenced object (the MiiModel_Renderer holder).
- **Containing function**: `FUN_71037577a0` — renamed candidate:
  `FighterMiiManager::reserveAndInitMiiModels(this, 0x85 /*count*/)`.
  The function starts at `0x71037577a0` and exits around `0x7103758390`.
- **Caller**: exactly one `BL` site targets `0x71037577a0`, and it is at
  `0x71022ca4d0`, sitting inside `FUN_71022b7100` (the Mii manager
  constructor, verified range). The call is:

```
71022ca4b0  STR XZR, [X20, #0x24e8]          ; zero-init the field first
71022ca4b4..bc STR XZR, [X20, #0x24d0..2500] ; zero-init six adjacent slots
71022ca4c0  STR X20, [X19, #0x0]             ; save this onto enclosing struct
71022ca4c4  STR X19, [X21, #0x6a0]           ; publish DAT_710593a6a0 singleton
71022ca4c8  LDR X0,  [X19, #0x0]             ; X0 = the Mii manager
71022ca4cc  MOVZ W1, #0x85
71022ca4d0  BL  0x71037577a0                 ; reserveAndInitMiiModels(mii, 133)
```

  The `X19` here is the outer owner that holds `DAT_710593a6a0` in its
  +0x6a0 field; the Mii manager itself is at `*(X19)`. `FUN_71037577a0`
  is called with that loaded pointer as its only non-count argument.

### What `FUN_71037577a0` actually does

Ghidra's decompile of `FUN_71037577a0` cleanly resolves to three phases
once the field-offset constants (`DAT_000024d8` etc.) are read as
`this + 0xNN`:

**Phase 1 — Mii database prime (CharInfo vector).**

```c
std::__1::mutex::lock();
nn::mii::Database::Initialize();
nn::mii::Database::Get(pCVar1, &err, this + 0x60, 100);     // fetch up to 100 CharInfo entries
nn::mii::Database::BuildDefault(pCVar1, this + 0x22c0);     // 6 default Mii templates,
nn::mii::Database::BuildDefault(pCVar1, this + 0x2318);     //   stride 0x58, contiguous
nn::mii::Database::BuildDefault(pCVar1, this + 0x2370);     //   at this+0x22c0
nn::mii::Database::BuildDefault(pCVar1, this + 0x23c8);
nn::mii::Database::BuildDefault(pCVar1, this + 0x2420);
nn::mii::Database::BuildDefault(pCVar1, this + 0x2478);
```

This pins two facts about the `FighterMiiManager` struct:

- **+0x20** is an embedded `nn::mii::CharInfo` (the "own" player mii).
- **+0x60** is an array of up to 100 `CharInfo` entries retrieved from
  the console's Mii database (the "pool" of real user miis available
  for CPU opponents / Mii Brawler customisation).
- **+0x22c0..+0x24d0** is 6 × `sizeof(CharInfo) = 0x58` = 0x210 bytes
  of default-built Mii templates.

**Phase 2 — std::vector resize to 133 elements, 0x68 stride.**

Fields at +0x24d0..+0x24e0 form a classic libc++ `vector`:

```
this + 0x24d0  = begin_ptr         (heap)
this + 0x24d8  = end_ptr
this + 0x24e0  = cap_end_ptr
```

The loop body calls `je_aligned_alloc(0x10, count*0x68)`, copies the
existing 0x68-byte elements over, and ref-count-decrements shared_ptrs
via the `ExclusiveMonitorPass` / `__shared_weak_count::__release_weak`
pattern. Element stride 0x68 = size of a `std::shared_ptr<X>` plus a
small embedded payload (likely `std::pair<CharInfo*, std::shared_ptr<MiiModel>>`
or similar — 104 bytes).

**Phase 3 — Allocate the MiiModel_Renderer back-reference.**

This is where `+0x24e8` gets written. The relevant slice:

```c
/* --- allocate a holder (8 bytes: one pointer) --- */
plVar23 = (long *)je_aligned_alloc(0x10, 8);
if (plVar23 == NULL) { /* OOM retry via DAT_7105331f00 */ }

/* --- allocate the MiiModel_Renderer itself (0x2db0 bytes) --- */
lVar28 = je_aligned_alloc(0x10, 0x2db0);     // <--- SIZE 0x2db0 !!!
if (lVar28 == 0) { /* OOM retry */ }

FUN_710357c940(lVar28, &local_c0);           // MiiModel_Renderer::ctor(this, config)
*plVar23 = lVar28;                           // holder->ptr = renderer

/* --- allocate a 0x20-byte std::shared_ptr control block --- */
puVar10 = (undefined8 *)je_aligned_alloc(0x10, 0x20);
*puVar10 = &DAT_710523c3a8;                  // shared_ptr control-block vtable
puVar10[1] = 0;                              // ref_count
puVar10[2] = 0;                              // weak_count
puVar10[3] = plVar23;                        // managed holder

/* --- THE FIELD WRITES --- */
*(long **)(this + 0x24e8) = plVar23;         // <--- raw pointer to holder
                                             // (the "back-reference")
old = *(long **)(this + 0x24f0);
*(undefined8 **)(this + 0x24f0) = puVar10;   // <--- the shared_ptr control block
                                             // (OWNS the holder/renderer)
if (old != NULL) { __release_weak(old); }    // release previous incarnation
```

### Why the destructor "didn't free" +0x24e8

The prior pool-pass concluded that +0x24e8 is "non-owning" because the
Mii manager destructor does not explicitly delete it. That conclusion
was *formally* correct but the framing was wrong: **+0x24e8 is the raw
fast-access pointer; +0x24f0 is the shared_ptr control block that
actually owns the renderer.** The destructor releases via the
shared_ptr at +0x24f0, which transitively frees:

- the 0x20-byte control block (`puVar10` above)
- the 8-byte holder (`plVar23`)
- the 0x2db0-byte `MiiModel_Renderer` (`lVar28`)

So the Mii manager **does** own the renderer; it just owns it through a
shared_ptr slot one field to the right. The raw back-pointer at +0x24e8
is a performance shortcut to skip the control-block indirection — the
same `shared_ptr::get()` caching pattern that libc++ users write by hand
when they need hot-path access.

### Back-referenced subsystem type — lib::mii::MiiModel_Renderer

`FUN_710357c940` is confirmed as the constructor of a rendering class,
not a simulation class, based on its string tables and resource loads.
The full decompile (~117 KB) is cached at
`data/ghidra_cache/FUN_710357c940.txt`. Key evidence:

- **Size**: zeroes a `memset(this+8, 0, 0x5b8)` block and then
  initialises individual fields up through `this[0x5b5]` (= byte
  offset 0x2da8). The allocation size from the caller is exactly
  `0x2db0` bytes, confirming the size Pool B inferred from Dispatcher A's
  access pattern.
- **Shader resource keys** (hashed FNV-1a and passed to material
  loaders): `s_mo_mii_opaque_VS`, `s_mo_mii_opaque_PS`,
  `PTR_s_MiiVS_710522fc68`, `PTR_s_MiiPS_710522fcb8`.
- **VSM (Variance Shadow Map) framebuffers**: `s_FB_VSM_256`,
  `s_FB_VSM_512`, `s_FB_VSM_1024`, and
  `s_FB_FOUR_DIRECTION_SHADOW_GAUSS`.
- **Main vtable**: `PTR_LAB_710522efe0` (stored at offset 0 and at
  several sub-object offsets as re-initialisation markers).
- **Zero references** to fighters, battle objects, physics, frame
  counters, `GlobalParameter`, `FighterManager`, `BattleObjectWorld`,
  or any `situation_kind` field.

The class is therefore confidently identified as
**`lib::mii::MiiModel_Renderer`** (or the `app::` namespace equivalent —
the leading `lib::mii::` strings Pool B found earlier referred to
*sibling* mii shader names, not this class; the class's own string-table
entries use the shader symbols above). Candidate formal names:

- `app::FighterMiiModelRenderer`
- `lib::mii::MiiModelRenderer`
- `app::MiiCharaRenderer`

The exact chosen name is a documentation detail; its *function* is
fully pinned: allocate and issue draw calls for Mii fighter models with
shadow/outline/player-id passes and per-LOD shader variants.

### The list at +0x2da8 — render resource list, NOT tickables

The constructor reaches +0x2da8 late in its init sequence and performs:

```c
this[0x5b5] = 0;                              // initial null (offset 0x2da8)
...
lVar21 = je_aligned_alloc(0x10, 0x88);        // 0x88-byte list node
FUN_7103587930(lVar21, &local_140);           // node init (probably
                                              //   lib::mii::MiiRendererNode::ctor)
this[0x5b5] = lVar21;                         // +0x2da8 = first node
```

So **+0x2da8 holds a pointer to the head of a linked list whose
elements are 0x88 bytes each**. 0x88 bytes is far too small for a
fighter (`BattleObjectFighter` is at least 0x20000), a battle object
(`BattleObject` is at least 0x800), or a scene entity. It sits neatly
in the size range of render resources (materials, draw items, shader
binding slots), which is exactly what the rest of the constructor is
building.

Adjacent fields around +0x2da8 support this read:

- `this[0x5b2]` = `0xffffffffffffffff` (= handle sentinel `~0ull` —
  typical for "invalid resource-handle" in render engines)
- `this[0x5b3]` = `0xffffffffffffffff` (second handle sentinel)
- `this[0x5b4]` (single byte at +0x2da0) = `0` (status flag)
- `this[0x5b5]` (+0x2da8) = the list head pointer

That 4-field cluster {handle, handle, status, list-head} is canonical
"resource entry + its dependent list" layout in engine code, e.g.
`{material_handle, pipeline_handle, dirty_flag, mesh_bind_list_head}`.

### Dispatcher A revisited

Reassembling the chain from `FUN_7103747270` (main_loop), line 558:

```c
app::FighterMiiManager *mii    = *DAT_710593a6a0;
void                  **holder = *(void ***)((char*)mii + 0x24e8);  // +0x24e8
void                   *Y      = *holder;                            // the MiiModel_Renderer
list_node_t           *first   = *(list_node_t **)((char*)Y + 0x2da8);
```

Where `Y` is a `lib::mii::MiiModel_Renderer` and `first` is the head of
its internal render-resource list (0x88-byte nodes).

The per-iteration body at `main_loop` lines 564..572 which prior passes
hypothesised as a "sim tick" is actually traversing that render list.
Specific counter-evidence:

- The list element size is 0x88, not fighter/BO size.
- The owner is `lib::mii::MiiModel_Renderer`, not a tick manager.
- The constructor of the owner does **pure graphics init** (shaders,
  VSM framebuffers, shadow passes) with no sim/physics hooks.
- Dispatcher A's gate flag `DAT_710593a530 == 3` has **zero static
  writers** in the entire .text (Pool C), so the branch is not
  reachable under static analysis.

**Status: STILL DEAD. Dispatcher A is neither a sim tick nor even a
live execution path. It is a (possibly dead) render-pass walk over
Mii draw items, guarded by a flag that no static code sets.**

### Disposition for the rollback roadmap

1. **Retire Dispatcher A from the sim-tick candidate board.** It is now
   contradicted from both directions (gate unreachable + list-type
   wrong). Future passes should not spend compute re-examining this
   dispatcher.
2. **The "safety smoke test" for `vtable[+0x28]` on list elements
   proposed in the pool-b writeup is moot.** Running the test would
   only answer "does the MiiModel_Renderer draw-list touch host
   services", which is interesting for graphics-subsystem research
   but has no bearing on the sim tick.
3. **The +0x24e8/+0x24f0 ownership model is a useful precedent** for
   the Mii manager struct layout work:
   - `FighterMiiManager::+0x0000..+0x0020` — locks / header
   - `+0x0020` — embedded `nn::mii::CharInfo` (self mii)
   - `+0x0060..+0x22c0` — 100 × `CharInfo` pool from console database
   - `+0x22c0..+0x24d0` — 6 × `CharInfo` default templates
   - `+0x24d0..+0x24e0` — `std::vector<SharedPtrPair>` (134-element)
   - `+0x24e8` — raw ptr to MiiModelRendererHolder
   - `+0x24f0` — `std::shared_ptr<MiiModelRendererHolder>` control block
   - `+0x24f8..+0x2508` — another shared_ptr slot (a sibling renderer
     or a secondary sub-object; stored alongside +0x24f0 in the ctor)

   A proper Mii manager header can now be stubbed with these field
   names plus derivation chains pointing back at `FUN_71037577a0` and
   `FUN_710357c940`.
4. **Where the sim tick actually lives** remains the phase-6/phase-7
   candidates in `main_loop.md` §6e. Pool C's and Pool A's scanners
   (`tools/xref_bin_scan.py` and the small helpers in
   `tools/scan_mii_24e8.py`) are now committed and reusable for hunting
   field writers via direct binary scan when Ghidra's xref index falls
   short.

### Scanner delta (committed to tools/)

- `tools/xref_bin_scan.py` — the reusable ADRP-propagation scanner that
  Pool C verbally described but did not commit. Supports:
  - `store-offset <offset> [size]` — all STR/STUR at an immediate offset
  - `adrp-global <page> <off>` — ADRP/ADD/LDR/STR chain writers for a
    specific global
  - `window <addr>` — tiny-disassembler dump of a small window around
    the requested address
- `tools/scan_mii_24e8.py` — two-mode hunter built on top of
  `xref_bin_scan.py` (external-via-singleton plus method-form-via-X0).
- `tools/scan_mii_24e8_v2.py` — improved function-start finder and
  per-register provenance tracer used to disambiguate the five raw
  hits.
- `tools/find_callers.py` — brute BL-target search, one-second run time
  on the full .text.

These four scripts together implemented the "who writes this field"
query in ~20 seconds of scanning. They are the answer to the
methodology note at the bottom of Pool C's section — worth keeping
and extending.

---

## Pool B — match-active flag hunt (next-pass)

**Pool B built its own ADRP-propagation scanner** following Pool C's spec and
ran it over the full `.text` segment of `main.elf` (file offset 0x888, size
0x39c7e90). The scanner tracks `{ Rd: page_base }` through ADRP, ADD/SUB imm,
and MOV (reg), flushes on RET/B/BR/BLR, and reports every `LDR/STR/LDUR/STUR/
LDP/STP/LDAR/STLR` whose `Rn` holds an address in `[0x710593a000,
0x710593b000)`. It also logs BL-with-arg-register-holding-target (setter
helpers) and pointer-init stores. Total: **6,519 access events across 443
distinct bytes** in the 4 KB target page.

Raw scanner and per-address hit list saved to `tmp/scan_a_block.py` and
`tmp/a_block_hits.txt` (pool-b scratch, not committed — see pool-c note).

### `main_loop` extent (measured)

First `RET X30` inside main_loop lands at **`0x710374ee64`**, so main_loop's
body is `0x7103747270..0x710374ee68` (= **0x7bf8 bytes ≈ 31.7 KB**). That is
the largest single function in the sim-tick path. This range was used below
to filter "reads inside main_loop".

### 0x710593axxx block audit — non-zero writer AND main_loop reader

Filtering the 443 accessed bytes by "has at least one static non-zero writer
**and** is read from inside main_loop's body" yields the candidate set below.
(Non-zero = source register is not `xzr`/`wzr`; the one-shot BSS ctor at
`0x7100446400` was kept but flagged as an init-time writer.)

| Address | Size | Non-ctor writers | Static readers | Read from main_loop? | Classification |
|---|---|---|---|---|---|
| 0x710593a448 | 1 | 4 | 2 | YES (main_loop+0x59d0) | byte flag, small cluster |
| 0x710593a44c | 4 | 1 | 4 | YES | state-byte cluster (see below) |
| 0x710593a450 | 4 | 1 | 0 | WRITE-only from main_loop | clear-on-frame |
| 0x710593a454..0x710593a470 | 4/8 | 1–2 | 1 | YES | state-byte cluster (9 fields) |
| 0x710593a4b4 | 4 | 2 | 1 | YES (main_loop+0xab8) | int16 clamp-and-store |
| 0x710593a4b8 | 4 | 1 | 1 | YES | int, read-only in main_loop |
| 0x710593a4c0 | 8 | 1 | 1 | WRITE at main_loop+0x48 | `this` cache (see below) |
| 0x710593a4c8 | 4 | 1 | 1 | YES | w0-return store |
| 0x710593a4cc | 4 | 1 | 1 | YES | load-modify-store counter |
| **0x710593a510** | **8** | **1** | **3** | **YES (LDR x0, cbz)** | **singleton pointer — see §"Match-active signal"** |
| 0x710593a528 | 8 | (ctor only) | 3 | YES (deep chain root) | **scene/mode singleton pointer** |
| 0x710593a530 | 4 | 0 | 3 | YES (the dead ==3 branch) | dead (per Pool C) |
| 0x710593a534 | 4 | 2 | 27 | WRITE at main_loop+0x60 | **cached int frame-state (see below)** |
| 0x710593a540..0x710593a5a0 | byte | — | 0 in main_loop | — | (byte cluster — no main_loop readers, de-prioritized) |
| 0x710593a570 | 8 | many | 0 | — | shared_ptr slot pattern; no main_loop reader |
| 0x710593a580 | 8 | 1 | 107 | YES (one read) | singleton pointer, "get X" service |
| 0x710593a5f0 | 8 | 2 | 28 | NO | singleton pointer, init-only |
| 0x710593a6a0 | 8 | 1 | 138 | YES (one read) | singleton pointer (scene root), init-only |
| 0x710593a740..0x710593a878 | 8 | ~50 | all in main_loop | YES | **main_loop-internal ring of 0x10-byte cells** |
| 0x710593a8d0 | 1 | 1 | 1 | YES | byte flag |
| 0x710593aa90 | 8 | 1 | 13 | YES (13 reads in main_loop) | hot pointer (probably a per-frame object tree) |

Notes on what was eliminated:
- **0x540..0x5a0 byte cluster (Pool C's second candidate).** The scanner sees
  only ADRP-based accesses; the entire byte cluster has **no readers from
  inside `main_loop`'s body** and no writers that stand out as a match-begin
  transition. De-prioritized.
- **0x570 (13r/12w).** The access pattern is "load 8 bytes, clear the same
  8 bytes to zero" repeated in 12 distinct subsystem destructors — a
  `std::shared_ptr::reset()` / service-locator "unregister me" slot. Not
  a tick signal.

### Main_loop's post-prologue fast path is a state-machine dispatch on DAT_710593a534

Literal disassembly (main_loop + 0x60..0x94):

```
0x71037472b0  blr x8                        ; vtable call on this->...
0x71037472b4  adrp x8, 0x710593a000
0x71037472b8  str x21, [x8, #0x4c0]         ; cache `this` pointer at 0x710593a4c0
0x71037472bc  bl  0x71039c7670              ; PLT stub — "begin frame"?
0x71037472c0  bl  0x71039c7570              ; PLT stub — returns int state
0x71037472c4  adrp x9, 0x710593a000
0x71037472c8  add  x9, x9, #0x510
0x71037472cc  mov  w8, w0
0x71037472d0  str  w0, [x9, #0x24]          ; cache state at DAT_710593a534
0x71037472d4  ldr  x0, [x9, #0x00]          ; load DAT_710593a510 (singleton ptr)
0x71037472d8  cbz  x0, 0x7103747304         ; if ptr==0 -> skip per-frame vtable call
0x71037472dc  cbz  w8, 0x71037472f0         ; state==0 -> store 0 to local
0x71037472e0  cmp  w8, #0x1                 ; state==1?
0x71037472e4  b.ne 0x7103747304             ;   no  -> skip per-frame call
0x71037472e8  str  w8, [sp, #0x270]         ;   yes -> store 1 to local
0x71037472ec  b    0x7103747304             ; fall through (actually to 0x72f4)
0x71037472f0  str  wzr, [sp, #0x270]        ; state==0 path stores 0
0x71037472f4  ldr  x8, [x0, #0x00]          ; x0 = DAT_710593a510; vtable fetch
0x71037472f8  ldr  x8, [x8, #0x30]          ; vtable[+0x30]
0x71037472fc  add  x1, sp, #0x270           ; arg1 = &local_state
0x7103747300  blr  x8                       ; ** PER-FRAME VTABLE DISPATCH **
0x7103747304  ...                           ; path taken when ptr==0 or state≥2
```

This is the clearest per-frame entry point yet found inside `main_loop`, and
it is **gated on DAT_710593a510 being non-null** plus `state <= 1`.

### DAT_710593a534 — cached frame-state integer, NOT the match-active flag

`DAT_710593a534` is:

- **Written every frame** from inside main_loop's prologue (insn
  `0x71037472d0: str w0, [x9, #0x24]`) with the return value of PLT stub
  `0x71039c7570`. (Both 0x71039c7570 and 0x71039c7670 are standard 4-insn
  ADRP/LDR/ADD/BR PLT trampolines — they are imported / virtual-dispatch
  wrappers; Ghidra will know the symbol from the dynamic relocation table.)
- **Written a second time** by the helper at `0x7103741988` (specifically at
  `0x7103741bb4`, again from a `w0` return value). That helper is NOT called
  from anywhere Pool B's linear BL scan could find — it is invoked via
  indirect dispatch, consistent with a vtable thunk into main_loop's subtree.
- **Read by 27 distinct functions scattered across the binary**, but **not
  re-read from inside main_loop** itself. Every read is `ldr w?, [x?, #0x534]`
  with no `cmp` / branch guarding it — the readers simply consume the value.

This is the behaviour of a **cached per-frame "phase" or "scene kind"
integer**, not a match-active flag. The value range that main_loop's own
state machine distinguishes is exactly `{0, 1, ≥2}`:

- `state == 0` → store 0 to local, take vtable dispatch at 0x72f4
- `state == 1` → store 1 to local, take vtable dispatch at 0x72f4
- `state >= 2` → skip the vtable dispatch (jump to 0x7303 0304 cleanup path)

So "2+" is the "match not running" case, and "0 or 1" is the "frame should
run the driver" case. 27 unrelated functions cache this value because it's
effectively a cheap read of the game loop's current phase.

### DAT_710593a510 — the match-active signal (**best candidate**)

`DAT_710593a510` is an 8-byte **singleton pointer** with exactly these
static-code accesses:

```
WRITES:
  0x7100446760  STP XZR, XZR, [X8, #0x0]    ; BSS ctor (init to null) — Pool C
  0x7103741a60  STR X0, [X8, #0x510]        ; helper in FUN_7103741988 area
                                            ; stores the return of an indirect
                                            ; call (not a PLT stub)

READS:
  0x7103741a4c  LDR X21, [X19, #0x20]       ; Rn holds 0x710593a4f0 → +0x20 = 0x510
  0x7103741a70  LDR X8,  [X19, #0x20]       ; same function, reload
  0x71037472d4  LDR X0,  [X9, #0x00]        ; main_loop, **right before cbz x0**
```

Interpretation:

- BSS ctor (Pool C's identified `.init_array[0x8a0]` entry) zeroes this slot
  at program load. So it is `null` on boot.
- A helper (sitting in the ~0x7103741988 block of functions right before
  `main_loop`) installs a non-null pointer into the slot. This helper also
  writes `DAT_710593a534` (0x22c bytes later), which is the clinching link:
  **one function owns the install of both the singleton pointer and the
  frame-state integer**. That matches the semantics of a match-begin handler
  that publishes the match runner and primes the cached phase integer.
- `main_loop`'s fast path checks `cbz x0, skip` on exactly this pointer — if
  the slot is null, the per-frame vtable dispatch is skipped entirely. This
  IS the gate on whether the driver runs.

**Verdict:** `DAT_710593a510` is the strongest candidate for the
match-active / rollback-arm signal in the `0x710593a___` block. It is
effectively a `MatchRunner *g_current_match`: non-null ⇒ driver runs this
frame, null ⇒ main_loop skips the driver.

Unknowns that Pool B could **not** confirm statically:

1. **There is only ONE non-init writer of 0x510** (at `0x7103741a60`). We
   did not find a corresponding "store xzr, [x8, #0x510]" to clear the slot
   on match end. Either (a) the same store at 0x7103741a60 can write `null`
   when the match ends (the source register is `x0`, which could hold
   either a new runner or null depending on upstream control flow), or
   (b) the clear path is reached via an indirect/register-computed address
   that the ADRP-propagation scanner misses. This needs Ghidra decomp of
   `FUN_7103741988` (or whatever function contains `0x7103741a60`) to
   verify.
2. **The type of the object at `DAT_710593a510`.** The only thing we know
   statically is that `vtable[+0x30 / 8]` takes `(this, int *frame_state)`
   — the second argument is a pointer to the local at `sp+0x270` holding
   the `DAT_710593a534` value. Candidate C++ prototypes:
   `void (*)(MatchRunner*, int *phase)` or
   `void (*)(SceneRoot*, const int *phase)`. Ghidra should already have
   this vtable's class — finding which class has a method at vtable slot
   0x30 that takes `(this, int*)` would identify the type.

### The dead 0x530 == 3 branch wraps a deeper dispatcher

Pool C's finding that DAT_710593a530 never receives the value `3` under
static analysis is confirmed. The disassembly at the read site
(`0x7103747bf8`) also tells us what the "taken" branch would have done:

```
0x7103747be0  adrp x8, 0x710593a000
0x7103747be4  ldr  x8, [x8, #0x528]   ; x8 = DAT_710593a528 (scene/mode singleton)
0x7103747be8  ldr  x0, [x8, #0x00]    ; deref +0x0
0x7103747bec  cbz  x0, 0x7103747bf4
0x7103747bf0  bl   0x71039c06c0       ; PLT stub (side effect on the scene mgr)
0x7103747bf4  adrp x8, 0x710593a000
0x7103747bf8  ldr  w9, [x8, #0x530]   ; w9 = DAT_710593a530 (the dead flag)
0x7103747bfc  ldr  x8, [sp, #0x268]
0x7103747c00  ldr  x8, [x8, #0x08]
0x7103747c04  ldr  x8, [x8, #0x11b0]
0x7103747c08  ldr  x8, [x8, #0x28]
0x7103747c0c  ldr  w20, [x8, #0xb0]   ; w20 = **real** state key, deep chain
0x7103747c10  cmp  w9, #0x3
0x7103747c14  b.ne 0x7103747c68       ; **if DAT_710593a530 != 3, SKIP the dispatcher**
0x7103747c18  cmp  w20, #0x3
0x7103747c1c  b.hi 0x7103747cac
0x7103747c20  mov  w9, w20
0x7103747c24  adrp x10, 0x7104530000  ; jump table base
0x7103747c28  add  x10, x10, #0xf00
0x7103747c2c  ldrsw x9, [x10, x9, lsl #2]  ; indirect dispatch on w20 in 0..3
```

This reveals that the "match-active dispatch" Pool B previously identified
(Dispatcher A / the element walk at main_loop +0x988) is actually a
**two-level gate**:

1. **Outer gate:** `DAT_710593a530 == 3` (dead under static analysis — Pool C).
2. **Inner dispatch:** a 4-way jump table keyed on `w20`, which is loaded
   from the chain `[sp+0x268] → +0x8 → +0x11b0 → +0x28 → +0xb0`.

The `[sp+0x268]` slot is populated earlier in main_loop — it is some `this`
or cached pointer — and the chain walks all the way into some subsystem
manager's inner state byte. **This inner field is the real per-frame "which
phase of the match are we in" key**; the outer 0x530 test looks very much
like a debug/devkit "dispatch enabled" flag that was left off in retail. On
a live runtime trace (GDB watchpoint at `0x710593a530`), if the flag is
never set to 3, Dispatcher A is genuinely dead code and the element walk
can be retired from the sim-tick hypothesis set.

### DAT_710593a528 — the scene/mode singleton

The chain root `DAT_710593a528` has:

- One writer: the BSS ctor at `0x71004467e8` stores **x8** (a non-null
  pointer) into `[x1 + 0x38]` where `x1 = 0x710593a4f0`, giving target
  `0x710593a528`. This is a **pointer-init** — the ctor allocates or
  references some static object at load time and publishes it at 0x528.
- No other static writer. So the slot value is fixed from program start.
- Three readers, all dereferencing the pointer and walking into it:
  `0x7103741bb0` (inside the helper that also writes 0x510/0x534) and
  `0x7103741c38` (same helper) and `0x7103747be4` (main_loop's inner
  dispatcher gate path).

So `DAT_710593a528` is a **static service-locator slot** for what is almost
certainly the scene manager / game-mode controller — it is populated once
and never re-homed. The real match-state byte is a field deep inside the
object it points to (`+0x8 +0x11b0 +0x28 +0xb0`), NOT a member of the
`0x710593a___` BSS block at all. Pool B's next step for a "find the match-
state byte" pass should therefore be **type recovery on the object rooted
at DAT_710593a528**, not further byte-scanning in the `0x710593a___` range.

### Most promising candidate

- **Address:** `DAT_710593a510` (8-byte singleton pointer, file offset of
  storage bytes unknown — it's BSS).
- **Writers:** two — the one-shot BSS ctor zero (`0x7100446760`, `.init_array`
  slot Pool C found) and `0x7103741a60` (inside a helper near main_loop,
  writes the return value of an indirect call).
- **Readers (main_loop chain):** `0x71037472d4 ldr x0, [x9]` → `cbz x0`
  gate → `ldr x8, [x0]; ldr x8, [x8, #0x30]; blr x8` (per-frame vtable
  dispatch).
- **State machine values:** binary — `null` (no match) vs non-null (match
  active). The paired `DAT_710593a534` integer disambiguates three
  sub-phases (0, 1, ≥2), but it is a cached int, not the arm signal.
- **Verdict:** **STRONG CANDIDATE** for the match-active flag / rollback arm
  signal. Needs (a) Ghidra confirmation of the containing function at
  `0x7103741a60` to find the DISARM (null-store) path, and (b) runtime
  confirmation via a GDB watchpoint on `0x710593a510` across match entry
  and exit.

### Rollback arm signal (tentative)

- **Function:** `FUN_7103741xxx` (container of `0x7103741a60`) — needs to
  be identified by the next pool. It is NOT reachable via linear BL scan,
  so it is called indirectly (likely a vtable thunk from the per-frame
  vtable dispatch above, meaning it re-enters the arm logic as a sub-state
  of its own dispatch).
- **Hook point:** `STR X0, [X8, #0x510]` at `0x7103741a60`, immediately
  after loading/comparing an incoming candidate against a stack local at
  `[sp, #0x370]`.
- **State transition:**
  - **Boot:** BSS ctor writes `null` → slot is null → main_loop skips driver.
  - **Match begin:** helper calls into a factory/getter, gets a non-null
    pointer, stores it at `0x710593a510`.
  - **Match end:** presumably the same store site writes `null` on the
    teardown path (the source register `x0` is loaded from a stack local,
    so it can be zero or non-zero depending on upstream control flow). The
    next pass should confirm this by decompiling the containing function.

### Methodology and artifacts

- The scanner (Pool C's spec, Pool B's implementation) is ~280 lines of
  Python that walks `.text` linearly, tracks `{Rd: page_base}` through
  `ADRP / ADD / SUB / MOV-reg`, flushes on `RET/B/BR/BLR`, and decodes
  `STR/LDR/STUR/LDUR/STP/LDP/STLR/LDAR` as well as `BL`-with-tracked-arg.
  Single pass over the 60 MB `.text` runs in <15 s. Saved in `tmp/` as
  `scan_a_block.py` (not committed — pool-c suggested productizing it as
  `tools/xref_bin_scan.py`, which is pool-c's turf).
- Per-address hit list saved to `tmp/a_block_hits.txt` (6,519 hits in 443
  distinct bytes of the 4 KB page).
- Main_loop extent measured as 0x7bf8 bytes by finding the first `RET X30`
  after `0x7103747270`.
- Ghidra MCP was **not** consulted for this pass — all findings come from
  direct binary scan + inline disassembly in Python. The next pool should
  use Ghidra to:
  1. Confirm the containing function of `0x7103741a60` and dump the
     decomp to find the DISARM (null-store) path.
  2. Resolve the PLT stubs `0x71039c7570` and `0x71039c7670` to their
     symbol names (this tells us what cached integer state DAT_710593a534
     actually represents — probably `SceneManager::getCurrentSceneKind()`
     or similar).
  3. Identify the class of the object at `DAT_710593a510` by searching
     the vtable at offset `+0x30` for a method signature
     `void (Type*, int *)`.

---

## Pool C — Round 3: productized scanner + phase-6/7 indirect-dispatch re-examination

### `tools/xref_bin_scan.py` (productized)

The ADRP-propagation scanner from the previous round is now a committed
tool. Invocation:

```bash
python tools/xref_bin_scan.py 0x710593a530
python tools/xref_bin_scan.py 0x710593a530 --non-zero-writes
python tools/xref_bin_scan.py 0x710593a000-0x710593a600   # range form
python tools/xref_bin_scan.py 0x710593a530 --writers-only
python tools/xref_bin_scan.py 0x710593a530 --called-as-arg
```

Coverage:
- ADRP seeding + `MOV Xd, Xn`, `ADD Xd, Xn, #imm{,<<12}`, `SUB Xd, Xn, #imm{,<<12}` propagation
- Load/store forms: `LDR/STR W/X/B/H/S/D/Q` (unsigned-imm), `LDUR/STUR W/X/B/H`, `LDP/STP W/X/D/S/Q` (offset/pre/post), `LDAR/STLR W/X/B/H`, `LDXR/STXR W/X`
- Setter-helper `BL` detection (target address passed in `X0..X7`)
- Pointer-init store detection (Rt holds the target as a value)
- `RET`/uncond-`B` end a basic block and clear the tracked-register state
- Function attribution via `data/functions.csv` (nearest-prior function)
- `--runtime-base` defaults to `0x7100000000` (SSBU runtime load addr)

**Test result on `0x710593a530`:** 1 writer, 3 readers, 0 BL args, 0 ptr
init — matches Pool C's earlier manual scan byte-for-byte:

```
WRITERS:
  0x71004467ec  STP X (off)     ea=0x710593a530  in fn 0x7100446630
READERS:
  0x7101f17f7c  LDR W           ea=0x710593a530  in fn 0x7101f17bfc
  0x71036552c8  LDR W           ea=0x710593a530  in fn 0x7103654b20
  0x7103747bf8  LDR W           ea=0x710593a530  in fn 0x7103747270 (main_loop)
# summary: W=1 R=3 B=0 P=0
```

(The `in fn ...` column uses `data/functions.csv`'s nearest-prior
entry. The true writer container at `0x7100446400` and the reader
containers at `0x7101f17ef0` / `0x7103655274` are Ghidra-undefined so
they don't appear in the csv — the attribution points at the nearest
named neighbor, which is good enough for human review.)

Pools A and B should switch to `tools/xref_bin_scan.py` next session
instead of reimplementing the inline scanner each time.

### Phase-6/7 dead-end re-examination

Pool B's pass-1 classification used a BL-only sweep, which is blind to
indirect dispatches of the form `LDR Xn, [Xm, #imm]; BLR Xn`. Re-examined
all four candidates by pulling fresh disassembly and grepping for `blr`:

| Function          | Size  | `blr` found | What gets called                                               | Verdict                    |
|-------------------|-------|-------------|----------------------------------------------------------------|----------------------------|
| `FUN_7103593c40`  | 792 B | **2**       | vtable[1] on two shared-ptr-held objects (`+0x3f0`, `+0x418`)  | interesting — shared_ptr release, probably not sim-tick |
| `FUN_71035c13d0`  | 1048 B | **7**      | vtable[3], vtable[2], vtable[7], vtable[8] through weak-ref `lock()` | **STRONG** — observer-pattern dispatch |
| `FUN_71036186d0`  | 1188 B | **0**       | (direct calls only: camera/matrix math)                        | confirmed dead end         |
| `FUN_7103619080`  | 432 B  | **6**      | vtable[6] allocator + vtable[2]/[3] per-element visitor        | **STRONGEST** — visitor with flag-gated dispatch |

**Pool B's BL-only classification missed 15 indirect dispatches across
three of four candidates.** The only one that is genuinely a BL-only
dead end is `FUN_71036186d0` (a pure-math camera/viewport setup with no
virtual calls at all).

Crucial additional fact: **`mcp__ghidra__get_xrefs_to` confirms all three
of the non-dead candidates are called directly from main_loop
(`FUN_7103747270`)**:

- `FUN_7103619080` ← `FUN_7103747270 @ 0x710374b124`
- `FUN_71035c13d0` ← `FUN_7103747270 @ 0x710374af6c`
- `FUN_7103593c40` ← `FUN_7103747270 @ 0x7103749a90`

So every indirect dispatch inside these three functions is reachable
from the same per-frame entry that already hosts Pool B's Dispatcher A.
main_loop's indirect reach is significantly larger than the BL-only
view suggested.

### `FUN_7103619080` — strongest candidate

432-byte visitor loop. Structure (x0 = param1, a subsystem object
loaded at call site via `LDR X0, [X21, #0xce8]`):

```
x22 = [x0, #0x500]        ; vector begin pointer
x23 = [x0, #0x508]         ; vector end pointer
while (x22 != x23) {
    obj = *x22             ; element is an object pointer
    if (obj->flags[0xf1] != 0) {
        subsys = x0->[0x518]
        factory = subsys->[0x50]
        // vtable[6] factory call — allocate + zero + return new node
        new_node = factory->vt[6](factory, &sz, &align)
        new_node->hdr  = &DAT_7105266f80
        new_node->size = 0x60
        // vtable[2] copy of subsys->[0x50] into new_node->[0x30]
        if (cloned = factory->vt[2]()) store at new_node->[0x30]
        // vtable[2] copy of subsys->[0x80] into new_node->[0x60]
        if (cloned = subsys->[0x80]->vt[2]()) store at new_node->[0x60]
        new_node->type_tag = &DAT_7105230f18
        // vtable[3] method call — hand new_node to the element
        obj->vt[3](obj, new_node)
    }
    x22 += 8
}
```

Key observations:
1. The `obj->flags[0xf1]` byte is the per-element "enabled" predicate —
   exactly the kind of boolean you'd expect on a match-active gate.
2. The loop **builds a new heap node per element** (allocator vtable[6]
   + two copy-constructs), populates it with two cloned sub-structures
   from `subsys->[0x50]` and `subsys->[0x80]`, tags it with two static
   type descriptors (`DAT_7105266f80`, `DAT_7105230f18`), then passes it
   to `obj->vt[3]`. **This is a command/visitor packet being dispatched
   per element.** It's the exact shape of a per-tick snapshot or event
   broadcast.
3. Vtable slot [3] is the same slot used by Pool B's Dispatcher A
   (`this->something->vt[3]` at 0x71037475d8). The two dispatchers may
   be driving the same virtual interface on different element lists.
4. The two static tags at `DAT_7105266f80` (= 0x60-byte type) and
   `DAT_7105230f18` (= some descriptor) would uniquely identify this
   command type if resolved. A next pass should dump those two globals
   to see if they name a packet type.

**If Pool B's Dispatcher A ends up unreachable at runtime (because of
the `DAT_710593a530 == 3` dead branch documented above),
`FUN_7103619080` is the best fallback candidate for the per-element
sim-tick broadcast.**

### `FUN_71035c13d0` — second strongest

1048-byte "double observer sweep":

```
if (x19->[0x160] || x19->[0x161]) {
    // refresh a cached "thing" via a global singleton chain:
    //   ldr x8, [adrp(0x7105336000) + 0xce8]   ; global A
    //   ldr x8, [x8 + 0x10]                    ; subsys
    //   ldr x0, [x8 + 0xa8]                    ; target
    //   vt[3](x0, &out)                         ; BLR #1 — getter
    x20 = result
    // copy x19->[0x140..0x160] into *out (16 floats)
    // clear x19->[0x160/161] bytes
    x20->vt[2]() ; BLR — reader
    x20->vt[3]() ; BLR — setter
}

// sweep #1: x19->[0x60..0x68] paired with iterator x19->[0x8..0x10]
foreach pair {
    elem = iter->[0x8]; obj = lock(elem)   // weak_ptr::lock
    if (obj) {
        inst = *iter
        // refcount ++, --
        stream = iter_extra
        stream->vt[7](stream, &outer_buf)   ; BLR — observer.onX(packet)
        refcount-- / dtor if zero
    }
    iter += 0x10
}

// sweep #2: x19->[0x78..0x80] paired with x19->[0x8..0x10]
foreach pair {
    ... same pattern, calls stream->vt[8](stream, w1, <q0, q1>)
}
```

This is **two independent observer broadcasts** over the same
iter-list (x19 + 0x8..+0x10) with two different downstream event
streams (x19 + 0x60..+0x68 and x19 + 0x78..+0x80), calling
`vt[7]` and `vt[8]` respectively. Every element is dereferenced through
`lock()` (`FUN_71039c21b0` — weak_ptr::lock, confirmed by the ldxr/stxr
refcount cmpxchg that follows).

**Interpretation:** this is probably a graphics/audio per-frame "tick
your observers" method — the weak_ptr iteration pattern, the two
streams, and the per-element vector math (q0/q1 passed at the vt[8]
call) are more consistent with render or audio event broadcast than
with rollback sim state. But it is NOT a dead end; the BL-only sweep
hid seven virtual calls worth of reach.

### `FUN_7103593c40` — shared_ptr release, probably not sim-tick

792-byte ring-buffer-advance function. The body is all scalar arithmetic
on `[x0 + 0x502..+0x540]` (two pairs of 16-bit ring cursors plus a
fraction) followed by two near-identical shared_ptr release blocks:

```
x8 = x19->[0x3f8]
if (x8 && *x8 == x19->[0x400] && --x19->[0x408] >= 0) {
    ptr = x19->[0x3f0]
    x19->[0x3f0/3f8/400] = 0
    if (ptr && *x8 == x19->[0x400]) {       // re-check
        dtor = (*ptr)->vt[1]
        dtor(ptr)                             ; BLR — object destructor
    }
}
// identical block for x19->[0x418..+0x430]
```

Both `blr` calls are vtable slot 1 (= destructor), invoked only when a
refcount hits zero. This is standard `std::shared_ptr` release, not a
dispatch to game logic. Classify as "interesting but almost certainly
not sim-tick" — the indirect calls only fire during object teardown.

### `FUN_71036186d0` — confirmed dead end

1188 bytes, **zero `blr` instructions**. Pure matrix/camera setup:
reads a global camera state at `[x21]`, computes viewport derivatives,
writes them to `[x20 + 0x20..+0x298]`, and calls three direct helpers
(`FUN_71035727d0`, `FUN_7103569a80` x3, `FUN_710365c8d0` x2,
`FUN_71039c6040`). Pool B's classification stands: this really is a
BL-only function and the BL-only sweep was sufficient to verify it.

### Most promising (ranked)

1. **`FUN_7103619080` — visitor/command-packet broadcast with per-element
   flag gate.** Strongest pattern match for per-tick element broadcast.
   Reachable from main_loop.
2. **`FUN_71035c13d0` — double observer broadcast over weak_ptr lists.**
   Second strongest; pattern fits render/audio event broadcast but could
   also be a sim observer list depending on what the two stream objects
   are.
3. (Low) `FUN_7103593c40` — ring-buffer advance plus shared_ptr release;
   indirect calls only fire during object teardown.
4. (Dead) `FUN_71036186d0` — camera/viewport math, no virtual dispatch.

### Recommended next pass

1. Resolve the two static type tags stored into the visitor packet in
   `FUN_7103619080` (`DAT_7105266f80` and `DAT_7105230f18`). If either
   is a vtable or a string literal / RTTI name, it will uniquely
   identify the command type and therefore the interface whose `vt[3]`
   is being invoked.
2. Run `tools/xref_bin_scan.py` on `0x7105266f80` and `0x7105230f18` —
   any `LDR` reader of these tags is a consumer of the same packet
   type, which gives you the full set of dispatch targets.
3. Dump the struct at `main_loop`'s `x21 + 0xce8` to identify which
   subsystem owns the x0 parameter passed into `FUN_7103619080` — that
   will tell us what list of objects is being visited.
4. If `FUN_7103619080` turns out to be sim-state related, the `+0xf1`
   gate byte on each element is the real match-active predicate that
   `DAT_710593a530 == 3` was standing in for.

### Methodology lesson

**BL-only sweeps are a systematic blind spot.** Any future "is this
function a sim-tick candidate" classification must look for indirect
dispatch patterns (`LDR Xn, [...]; BLR Xn` and `BR Xn`) before
concluding "dead end". The concrete filter is trivial — grep the
disassembly for `blr` / `br x` — but Pool B's pass-1 did not do it,
and the cost of that omission was three missed live leads from a pool
of four candidates (75% false-negative rate on this set).

## Pool A — Round 4: DAT_710593a510 MatchRunner identification (2026-04-10)

### TL;DR — DAT_710593a510 is **NOT** the match-active signal

`DAT_710593a510` is a lifetime-of-process `std::function<void(int)>` that
holds a fixed **render-phase prologue callback** installed once during
`nnMain`. The callback (`FUN_7103741700`) is called every frame from
`main_loop`, but it is **always non-null** after boot, so its `cbz`
guard in `main_loop` is a defensive no-op, not a per-match gate.

The real per-frame driver that `main_loop` enters is reached via the
prologue callback's **tail-call into main_loop's cached `this` at
`DAT_710593a4c0`, specifically vtable slot 2 (`+0x10`)**. The sim-tick
hunt needs to move off `DAT_710593a510` entirely and onto
`DAT_710593a4c0` (the cached `this`) and its `vtable[+0x10]` method.

**Rollback hook candidates invalidated:** Pool B's Round 3 "best
candidate" `DAT_710593a510` is ruled out. The store at `0x7103741a60`
is a one-shot install inside `nnMain`, not a match-begin event.

### Installer at 0x7103741a60

- **Containing function:** `FUN_7103741990` — labeled `game_ldn_initialize`
  in Ghidra (xref_sdk pass), but the name is **WRONG**. The function is
  actually `app::main_init` or equivalent: it calls `nn::oe::SetPerformanceConfiguration`
  (twice — docked + handheld profiles), `nn::grc::DisableRecording`,
  several other init-only PLT stubs, and has a 0x250-byte stack frame.
  It is called exactly once, from `nnMain @ 0x71002c5964`. There are no
  `nn::ldn::*` calls in its body. The `ldn` in the name is a name-transfer
  artifact from a superficially-similar function in KinokoDecomp-S.
- **Ghidra decompile of this function TIMES OUT** (>120 s, logged in
  `data/ghidra_cache/manual_extraction_needed.md`). All analysis below
  is from raw disassembly (extracted via `mcp__ghidra__disassemble_function`,
  parsed with Python, plus direct ELF/Capstone reads of unanalyzed gaps).

### The installed object: `std::function<void(int)>` layout

At `0x7103741a04..0x7103741a64` the function constructs a 3-pointer
object on the stack and stores it into `DAT_710593a510`:

```
sp[0x320] = &PTR_LAB_710523c100      ; vtable ptr
sp[0x328] = 0x7103741700              ; callable function pointer
sp[0x340] = sp+0x320                  ; self-ptr (SBO marker)
sp[0x370] = sp+0x350                  ; self-ptr (SBO marker, output)
bl 0x7103747220                       ; placement-copy ctor (vtable slot 3)
ldr x0, [sp, #0x370]                  ; x0 = the constructed object
str x0, [x8, #0x510]                  ; DAT_710593a510 = x0
```

The placement-copy helper `FUN_7103747220` (which is itself a vtable
slot — see below) decompiles to:

```c
void __inplace_clone(src *p1, dst *p2) {
    p2[0] = &PTR_LAB_710523c100;   // fresh vtable
    p2[1] = p1[1];                  // copy callable
    p2[2] = p1[2];                  // copy captured data
}
```

### The vtable at 0x710523c100

Ghidra could not find a function at `0x710523c100` because the slots
are populated by **`R_AARCH64_RELATIVE` dynamic relocations** applied
at load time. Extracting the 7 relocations directly from `.rela.dyn`
(entries at file offset `0x39c8070 + …`) yields:

| Slot | Offset | Runtime addr | Role |
|---|---|---|---|
| 0 | +0x00 | `0x7103747180` | `ret` — empty non-delete destructor |
| 1 | +0x08 | `0x7103747190` | `if (this) b operator delete_71039…` |
| 2 | +0x10 | `0x71037471a0` | **heap clone** — alloc 0x18/align 0x10, copy +0x8/+0x10 |
| 3 | +0x18 | `0x7103747220` | **placement clone** — in-place copy, fresh vptr |
| 4 | +0x20 | `0x7103747240` | `ret` — empty (move/assign stub) |
| 5 | +0x28 | `0x7103747250` | `if (this) b operator delete_71039…` |
| 6 | +0x30 | `0x7103747260` | **INVOKE** — `ldr x2,[x0,#8]; ldr w0,[x1]; br x2` |

This is the exact slot layout of **libc++ `std::__function::__base<void(int)>`**:
`{destroy_empty, destroy_deallocating, clone_heap, clone_inplace,
destroy_to_empty, destroy_to_deallocating, invoke}`. The small-buffer
representation is 3 pointers: `{vptr, callable, captured}`. The
captured slot is unused by the invoker (slot 6 only loads `[x0,#8]`),
so this particular specialization wraps a plain function pointer.

### The per-frame callback: `FUN_7103741700`

Ghidra does not have this function analyzed — it sits in the gap
`0x71037416f4..0x7103741990` between `FUN_7103741520` (a language-code
lookup) and `game_ldn_initialize`. Disassembly extracted directly from
the ELF via Capstone. Body summary:

```c
void frame_prologue(int phase) {  // phase arrives in w0, 0 or 1 fast path
    if (phase > 1) goto cleanup;

    DAT_710593a4b4 = 3;             // render-phase marker
    DAT_710593a4b8 = phase;

    void *globalA = DAT_7105336ce8;         // subsystem root A (render?)
    if (!globalA) goto cleanup;

    void *globalB_sub = DAT_7105334480[5];  // at +0x28
    // ^ this is main_loop's "owner of dispatch" handle

    if (phase == 1) {
        if (globalA->byte_0x58d) {
            // tear down a transient frame object
            ManagerC *mc = DAT_71053386d0;
            mc->byte_0x54 = 1;
            virtual_dispose(mc->field_0x08);
            if (mc->field_0x10) {
                mc->field_0x10->vtable[+0x18](&local);
                mc->field_0x10->vtable[+0x08](mc->field_0x10);
                mc->field_0x10 = nullptr;
            }

            if (globalA->byte_0x540) {
                // commit interpolated camera/transforms:
                // iterate [globalA+0x528, globalA+0x530) in 0xa0-byte strides
                // copying per-element fields at
                //   +0xa8/+0xac  (pos?)   +0xc0/+0xc4  (pos?)
                //   +0xd0 (16B quad)      +0xb8/+0xd0 (matrix?)
                //   +0xe0 (byte flag)
                // looks like "publish last-frame transforms to renderer"
                globalA->byte_0x540 = 0;
                globalA->word_0x58d = 0;
            }
        }
        sizes = {w22=0x780, w21=0x438};   // phase-1 viewport
    } else {
        sizes = {w22=0x500, w21=0x2d0};   // phase-0 viewport
    }

    globalB_sub[+0x30] = (w22 << 32) | w21;  // store two int sizes
    local_key = 14;

    // libc++ std::unordered_map::find_or_insert, key=14
    auto it = FUN_71037cbcc0(&globalB_sub->map_at_0x48, &local_key);

    // walk collision bucket, fire each subscriber's vtable[0][0]
    for (auto *n = it; n != it_end; n = n->next) {
        void *obj = n->field_0x10;
        args_struct = {constData_0x7105240f78, key=14, w22, w21};
        obj->vtable[0][0](obj, &args_struct);
    }

cleanup:
    nn::os::LockMutex(&DAT_710523a5c8);

    // render-phase atomic at 0x7107446040 bits 2/4/8
    if (phase >= 2) {
        if (phase == 2) atomic_and(~2);
        flag = (phase >= 3 && phase < 5) ? 4 : ((phase == 2) ? 2 : 8);
        atomic_or(flag);
    }

    nn::os::UnlockMutex(&DAT_710523a5c8);

    // TAIL CALL into main_loop's cached `this`
    void *cached_this = DAT_710593a4c0;
    if (cached_this) {
        void (*driver)(void*, int) = cached_this->vtable[+0x10];  // slot 2
        driver(cached_this, phase);  // tail call
    }
}
```

### What DAT_710593a510 actually is

It is an app-lifetime `std::function<void(int)>` holding `FUN_7103741700`
as its payload. Semantically it is the **frame prologue hook**: it runs
before every frame's real tick, commits render-side interpolated
transforms, dispatches all subscribers under key=14 in a global
`std::unordered_map` (almost certainly "begin-frame events"), twiddles a
render-phase atomic flag, and then **tail-calls** into the real per-frame
driver via `DAT_710593a4c0->vtable[+0x10]`.

Why Pool B's scanner saw only one non-init writer at `0x7103741a60`:
because the slot really is written exactly once in the normal flow, and
never cleared. Pool B correctly observed the write, but the
interpretation ("match-begin installs a runner") was wrong. The right
reading is "`nnMain` installs a permanent render-phase hook". The other
writes to `[x19, #0x20]` in `game_ldn_initialize` (at `0x7103741aa0`,
`0x7103741adc`, `0x7103741b38`, `0x7103741b6c`) are all
sentinel/self-reference stores (`str x19, [x19, #0x20]`) or zeroing
stores (`str xzr, [x19, #0x20]`) inside the swap/error-recovery side
paths of the same install. The normal path is the first store at
`0x7103741a60` and the installed value persists.

### Disarm path

**None exists.** There is no static code anywhere in `.text` that writes
a null or a non-matching value into `DAT_710593a510` after `nnMain`
returns. The slot is permanently installed. This rules out
`DAT_710593a510` as any kind of rollback arm/disarm signal and rules
out the `cbz` in `main_loop` as a match-active gate.

### Runner class

- **Vtable address:** `0x710523c100` (7 slots, `R_AARCH64_RELATIVE`-populated)
- **Class name (if .dynsym):** unnamed — this is a compiler-generated
  `std::__function::__func<T, allocator<T>, void(int)>` specialization,
  not a user-level class. `T` is a plain function pointer wrapper.
- **Vtable slot 6 (+0x30):** `0x7103747260`, a 3-insn tail-call
  trampoline that loads the stored function pointer at `[this+8]` and
  tail-calls it with the `int` loaded from the phase argument.
- **IS THIS THE SIM TICK?** **NO** — it's a render-phase prologue hook.
  The real sim-tick continuation is in `DAT_710593a4c0->vtable[+0x10]`,
  which this callback tail-calls at the end.

### The real target for Round 5: DAT_710593a4c0

`DAT_710593a4c0` was already in Pool B's Round 3 audit table as
"write at main_loop+0x48, this-cache" but was not pursued because it
appeared to be a simple store-back. With the `DAT_710593a510` lead
dead, it is now the strongest candidate for the per-frame driver's
`this` pointer. Specifically:

- `main_loop`'s prologue does `str x21, [x8, #0x4c0]` at
  `0x71037472b8` (Pool B). `x21` is loaded earlier in `main_loop` from
  some parent context — that load is the chain root.
- The render-phase prologue (`FUN_7103741700`) tail-calls
  `DAT_710593a4c0->vtable[+0x10]` — slot 2 — with the phase arg.
- Whatever class that vtable belongs to is the **actual frame driver**.

Round 5 tasks:
1. Dump `main_loop`'s prologue (`0x7103747270..0x71037472c0`) to find
   where `x21` comes from — the value passed into `main_loop` by its
   caller, cached at `DAT_710593a4c0`.
2. Decompile `DAT_710593a4c0->vtable[+0x10]` — the class's "tick" method.
3. Trace the call into that method to find where fighters / sim state
   are actually advanced.

### Supporting data references

- `FUN_71037cbcc0` decompiles cleanly as libc++ `unordered_map::__find_or_insert_unique`
  (uses `std::__1::__next_prime`). This proves the `FUN_7103741700`
  key-14 dispatch is a `std::unordered_map` iteration, not a custom
  container.
- `FUN_7103747220` (placement-copy ctor, vtable slot 3) decompiles to
  the trivial 3-field copy quoted above.
- `FUN_7103741520` (adjacent to 0x7103741700) is `app::GetLanguageIndex`
  — unrelated, ruled out as the payload source.
- Vtable relocations at `.rela.dyn` confirmed by direct ELF parse; all
  7 entries are `R_AARCH64_RELATIVE` (type `0x403`).
- `FUN_7103741990` (the nnMain installer) full decompile is in
  `data/ghidra_cache/manual_extraction_needed.md` — needs orchestrator
  manual extraction. Round 4 analysis used disassembly only.

## Pool A — Round 4 follow-up: main_loop's `this` is a lightweight boot context (2026-04-10)

While finishing Round 4, Pool A started the Round 5 work (investigate
`DAT_710593a4c0`, the `this` cached at main_loop+0x48) and produced the
first layer of evidence. Full Round 5 write-up deferred, but the most
useful facts are captured here so the next pool doesn't re-derive them.

### main_loop is called directly from nnMain with a stack-local object

```c
// nnMain @ 0x71002c5cec (partial, from Ghidra):
undefined1 local_170[0xB8];   // or similar — full size not yet measured
FUN_7103723fa0(local_170);    // construct
local_170[0]  = 0x68;          // set small header bytes
local_170[1]  = 0x52;
local_170[2]  = 0x0b;
uStack_16d    = 0x7105;        // and one 2-byte field overlapping +3
DAT_710593a2d8 = local_170;    // publish stack object to a global (see below)
plVar14 = FUN_7103747270(local_170);    // call main_loop(this=local_170)
plVar20 = *plVar14;                      // deref returned pointer
*(plVar14 + 0x131) = 0xffffffff;         // set +0x988 = -1 (post-exit cleanup)
*(*plVar20 + 0x38) = 0;                  // clear a flag inside the child object
// ... further teardown
```

Consequences:
- `main_loop`'s `this` is **not** a heap-allocated frame driver — it is
  a stack-allocated small object in `nnMain`, lifetime = game session.
- The call is unconditional and singular. `main_loop` returns only when
  the game session ends.
- `nnMain` also publishes `local_170` to `DAT_710593a2d8` before the
  call, which is a second cached handle the sim-tick search should
  audit for readers.

### The class at vtable 0x710523bd38 (the ctor that FUN_7103723fa0 builds)

```c
void FrameContext_ctor(FrameContext *this) {  // FUN_7103723fa0
    this->vptr       = &PTR_FUN_710523bd38;   // vtable
    this->field_0x08 = 0;                     // link.next
    this->field_0x10 = 0;                     // link.prev
    this->field_0x18 = 0;                     // gate flag (see below)
    this->field_0x20 = alloc_0xb8_child();    // child A, 0xb8 bytes
    this->field_0x28 = alloc_0x68_child();    // child B, 0x68 bytes
    this->field_0x30 = 0;
    this->field_0x44 = 0x811c9dc5;            // FNV-1a offset basis
    this->field_0x48 = 0;                     // hash state, zeroed
    // ... more zero-init fields
    // Register `&this->field_0x08` in the global doubly-linked list at
    // PTR_LOOP_710523bd78. The list head is an embedded sentinel; the
    // size counter at DAT_710523bd88 is incremented.
}
```

Key observations:
- The class **embeds an FNV-1a hasher state** at +0x44 (seed = offset
  basis). SSBU uses FNV-1a extensively for `hash40` identifiers, so
  this is a `HashContext` / hash-state field rather than a general
  scratch field.
- The class **registers itself in a global intrusive list** at
  `PTR_LOOP_710523bd78`. This list is almost certainly a "living
  contexts" registry.
- `FUN_7103723fa0` has **exactly one caller (nnMain)** and the vtable
  at `0x710523bd38` has **exactly two xrefs** (ctor + dtor). There is
  **only one instance of this class, ever, for the whole game
  lifetime** — the stack instance in `nnMain`.

### Vtable at 0x710523bd38 — 16 slots, extracted from .rela.dyn

| Slot | Offset | Runtime addr | Role |
|---|---|---|---|
| 0 | +0x00 | `0x7103724110` | destructor (`FUN_7103724110`) |
| 1 | +0x08 | `0x7103724300` | `bl dtor; b operator delete` |
| 2 | +0x10 | `0x7103724340` | **iterate global list, call each member's `vtable[+0x10]`** |
| 3 | +0x18 | `0x71037243b0` | `ret` (empty stub) |
| 4 | +0x20 | `0x71037243c0` | `ret` (empty stub) |
| 5 | +0x28 | `0x71017f4a80` | `ret` (empty stub, in `0x71017xxxxx` text block) |
| 6 | +0x30 | `0x71037243d0` | `ret` (empty stub) |
| 7 | +0x38 | `0x71037243e0` | `ret` (empty stub) |
| 8 | +0x40 | `0x710523bd78` | **DATA pointer** (back-ref to list head — RTTI/typeinfo-ish?) |
| 9 | +0x48 | `0x710523bd78` | **DATA pointer** (same) |
| 13 | +0x68 | `0x7103725a20` | `ret` (empty stub) |
| 14 | +0x70 | `0x7103725a30` | `bl operator delete` |
| 15 | +0x78 | `0x7103725a40` | allocate-0x70 factory (makes a 0x70-byte child) |

(Slots 10, 11, 12 have no relocs and are presumably null or inline
data.)

Of these, **only slot 2 does any per-frame work**, and only via the
global list iteration. Slots 3/4/5/6/7/13 are all `ret` — true no-ops,
not shim thunks. The class is effectively a skeleton with one virtual
method that matters (the list walker) plus utility hooks (dtor,
factory).

### Slot 2's dispatch loop (the tail-call target from FUN_7103741700)

```c
void dispatch_all_enabled(FrameContext *self, int phase) {
    ListNode *head = &PTR_LOOP_710523bd78;   // global sentinel
    ListNode *node = head->next;
    while (node != head) {
        FrameContext *obj = (node != nullptr) ? container_of(node, -8) : nullptr;
        if (obj->field_0x18 != 0) {          // gate check
            obj->vptr[+0x10](obj, phase);    // RECURSIVE: calls slot 2 on the member
        }
        node = node->next;
    }
}
```

Two important properties:
1. The only element in the list is `self` (since there is exactly one
   instance). So the walk finds itself and re-dispatches.
2. The recursive self-dispatch is **gated on `self->field_0x18 != 0`**.
   The constructor writes `field_0x18 = 0`, and no static code has been
   found that sets it.

**Therefore, in static analysis, this per-frame dispatch is a no-op.**
The loop iterates the 1-element list, the gate fails, nothing happens.

### What this means for the sim-tick hunt

1. The chain `main_loop → DAT_710593a510 (std::function) → FUN_7103741700
   (frame prologue) → DAT_710593a4c0->vtable[+0x10] (slot 2 walker)` is
   **NOT the sim tick**. It is a decorator chain that, under current
   static analysis, bottoms out in a no-op gate on `field_0x18`.
2. The **real per-frame work lives inline inside `main_loop`'s body**
   (`0x7103747270..0x710374ee68`, 0x7bf8 bytes = 31.7 KB). The only
   thing `main_loop` needs from its `this` pointer is a handful of
   small flag / counter fields — not virtual dispatch. This is
   consistent with the large stack frame (0x25c0 bytes) and the fact
   that `main_loop` loads game state from ~50+ unrelated globals
   directly.
3. `DAT_710593a2d8` (the second cached handle to the stack instance,
   published by nnMain before the main_loop call) should be audited
   next: it may reveal which code outside `main_loop` also consumes
   this boot-context struct.
4. The `field_0x18` gate is still interesting as an event flag — if
   any runtime code sets it, a GDB watchpoint on
   `&local_170.field_0x18` across a match would reveal when. But
   without a static writer we cannot determine its semantics from
   disassembly alone.

### Still-open questions for Round 5 (deferred)

- Which function writes `field_0x18` on the `nnMain::local_170`
  instance, if any? (Need a watchpoint or a register-indirect scan.)
- What does `main_loop` actually do with its 31.7 KB body besides the
  frame-prologue call and Dispatcher A? Pool B identified only two
  indirect-dispatch sites in the whole body. Is there a third that the
  `DAT_710593a530 == 3` and `field_0x18` gates both refer to?
- `DAT_710593a2d8` readers — static xref scan.
- FUN_7103723fa0 allocates two child objects: a 0xb8-byte object at
  `+0x20` (has two self-refs — libc++ list sentinel pattern) and a
  0x68-byte object at `+0x28` (also two self-refs). These are the
  "living" state containers; auditing their writes across match
  transitions is the most promising next watchpoint target.

### Functions referenced in this section

- `FUN_7103723fa0` (main_loop `this` ctor) — decompiled cleanly, full
  body above.
- `FUN_7103724110` (dtor, vtable slot 0) — not decompiled.
- `FUN_7103724300..71037243e0` (vtable slots 1–7) — disassembled
  directly from ELF via Capstone; written up above.
- `FUN_7103725a20..7103725a40` (vtable slots 13–15) — same.
- `FUN_7103747270` (main_loop itself) — prologue disassembled only.
  Full decompile is too large for a single pool session; next pool
  should request orchestrator manual extraction for the body region
  `0x7103747350..0x7103747be0` (between the frame-prologue call and
  the Dispatcher A entry).

---

---

## Pool B — Round 4: FUN_7103619080 caller + tag identification

### Caller in main_loop @ 0x710374b124

```
710374b0f0: adrp x8, 0x7105336000      ; x8 = 0x7105336000
710374b0f4: ldr  x20, [x8, #0xce8]     ; x20 = *(0x7105336ce8)  [also used for camera setup]
710374b0fc: mov  x21, x8
...
710374b120: ldr  x0, [x21, #0xce8]     ; x0 = *(0x7105336ce8)
710374b124: bl   0x7103619080          ; <- the visitor dispatch
```

- **Subsystem object source:** global singleton at **`[0x7105336ce8]`**.
- **Writer:** `FUN_71035a4130 @ 0x71035a43a0` — called ONLY by
  `game_ldn_initialize @ 0x7103744360`. Singleton installed at ldn-init
  time. (FUN_71035a4130 decompile timed out in Ghidra MCP — logged to
  `manual_extraction_needed.md`.)
- **Named readers** of `[0x7105336ce8]`: `fighter_init`,
  `set_visibility_of_fighter_and_item`, `set_final_stage_disp_status`,
  `update_blink`, `renderer_get_color_rate`, `game_ldn_initialize` —
  plus 50+ internal FUN_*. A **cross-cutting service** used by fighter
  lifecycle, stage display, rendering, AND the ldn path — not a pure
  render manager or pure ldn struct.
- **Vector at `+0x500`/`+0x508`:** holds element pointers to objects
  with a byte flag at `+0xf1` and a vtable whose slot 3 takes
  `(this, Packet*)`. Element class unnamed — NOT confirmed as
  `BattleObject`.
- **Sub-object at `+0x518`:** holds the packet allocator at its own
  `+0x50` (an `std::function`-shaped factory with `vt[6] = invoke`)
  and a second clonable source at `+0x80`. Pool B Round 3 incorrectly
  attributed these to `param_1` directly — they are on the inner
  `param_1->[0x518]` sub-object.

### Type tags — correction to Round 3

Round 3 description (`new_node->type_tag = &DAT_7105230f18`) was
structurally wrong. `DAT_7105230f18` is NOT a separate type tag; it is
the **derived class vtable pointer** overwritten onto `*new_node` at
the end of construction. The visitor follows the canonical C++
constructor-chain:

```c
*new_node       = &PTR_FUN_7105266f80;    // 1. install BASE vtable
new_node->size  = 0x60;                    // 2. size/tag at +0x8
/* clone subsys->[0x50] into new_node[+0x30] via vt[3] */
/* clone subsys->[0x80] into new_node[+0x60] via vt[3] */
new_node->unk70 = 0;                       // u32 at +0x70
*new_node       = &PTR_LAB_7105230f18;    // 3. OVERWRITE with DERIVED vtable
elem->vt[3](elem, new_node);               // 4. dispatch
```

- **`DAT_7105266f80` — base class vtable.** Abstract: slot 0 is
  destructor `FUN_7103812f50`, slot 2 is `__cxa_pure_virtual`.
  Layout: `{vptr, u32 size, [0x20B SBO #1], ptr A @ +0x30, [0x20B SBO #2],
  ptr B @ +0x60, u32 @ +0x68, u32 @ +0x70}`.
- **`DAT_7105230f18` — derived class vtable** specific to the visitor packet
  variant (size `0x60`). Only ever referenced by FUN_7103619080.
- **Sibling derived classes on the same base** (proves a large polymorphic
  hierarchy — 20+ factories):
  - `FUN_71035b91b0` -> `PTR_FUN_71052313f0`, size `0x100`
  - `FUN_7103819bb0` -> `PTR_FUN_7105267be8`, size `0x80`
    (throws `std::bad_function_call` when the allocator is empty —
    confirms libc++ `std::function` erasure is in play)
  - `FUN_710363f4a0` -> `PTR_FUN_71052313b8`, size `0x4000`, stores a
    captured `u64` + `bool` — looks like a snapshot variant
  - `FUN_7103619080` -> `PTR_LAB_7105230f18`, size `0x60` (the visitor)
  - plus the `FUN_710381a*..c*` factory cluster (~20 functions)

**Command packet class name: UNKNOWN** — no mangled name or string tag
recoverable. Structurally it is a polymorphic packet/command class with
two small-buffer-optimized sub-objects of variable type, a size field,
and a trailing `u32` at `+0x70`. Shape of a **command-stream node**
(header + two typed payload blobs).

### The 10-slot sibling path — `FUN_71037857f0`

The hunt turned up a second broadcaster reachable from main_loop:
`FUN_71037857f0` is called **10 times consecutively** in main_loop at
`0x710374bd9c..0x710374bfe8`, once per slot index 0..9. Each call:

1. Loads `x0` via `ldr x8, [x28, #0xa90]; ldr x0, [x8]` — a
   **different** singleton than Pool B base (`x28`-based, not the
   `0x7105336ce8` global).
2. Passes a per-slot config record from the data at
   `[0x710593a7c8 + i*0x40]` — in the **same 4 KB page** as Pool A
   `0x710593a510` target.
3. Passes a local probe struct whose vtable is `0x710522eea0`.
4. Inside `FUN_71037857f0`, when the per-slot flag is set, it builds
   up to five packets via the factories above (`FUN_710363f4a0`,
   `FUN_710381ba20`, `FUN_710381bde0`, `FUN_710381bc00`,
   `FUN_710381b8a0`, `FUN_71035b91b0`) and calls
   `plVar6->vt[3](plVar6, packet)` on each — same slot 3 dispatch as
   `FUN_7103619080`, but on a **single receiver** `plVar6` instead of
   broadcast over a vector.
5. `plVar6 = *(long **)(param_3 + 8)` — the receiver is held by the
   local probe struct.

**Ring-buffer cursors** on the receiver sub-struct (from
`FUN_710363f4a0`): byte flag at `+0x48`, cursor at `+0x3f0` advancing
by `0xe8` per packet, cursor at `+0x418` advancing by `8`, cursor at
`+0x4a0` advancing by `0x10`. Three parallel rings is the classic
layout of a **command stream** (header ring + index ring + payload
ring) — exactly the shape a rollback/replay backing store needs.

The 10-slot structure matches SSBU max player count (8 players + 2
pad) and is a strong signal that this is a **per-slot command
streamer**, not a pure render path.

### Element type (vt[3] receivers)

- **Class:** unnamed.
- **vt[3] signature:** `void (this, Packet*)` where `Packet*` is a
  class derived from the `DAT_7105266f80` abstract base.
- **Per-element flag:** byte at `+0xf1` (active gate).
- **IS THIS A FIGHTER / BATTLE OBJECT?** **INCONCLUSIVE.** Flag offset
  `+0xf1` does not match a well-known BattleObject field, and no named
  fighter struct has a vtable whose slot 3 matches the
  `(this, Packet*)` signature. Could be a `CommandListener` /
  `ReplayWriter` / `NetworkPacketSink` — any observer-interface type.

### Cross-reference with Pool A MatchRunner

- Pool A signal: `[0x710593a510]` — written by `game_ldn_initialize`
  directly (field-init pattern with interleaved READs and WRITEs in
  `0x7103741a4c..0x7103741b6c`).
- Pool B signal: `[0x7105336ce8]` — written by `FUN_71035a4130`,
  which is called ONLY by `game_ldn_initialize @ 0x7103744360`.

**Same object as `*DAT_710593a510`?** **NO — different globals, but
same init function.** The two signals converge on one init path
(`game_ldn_initialize`) and the 10-slot sender in `FUN_71037857f0`
additionally uses config records from the same 4 KB data page
(`0x710593a000`) as Pool A target. The most likely story is:

- **Pool A `[0x710593a510]`** = ldn match state / `MatchRunner`
- **Pool B `[0x7105336ce8]`** = command-stream broadcaster driven by
  the match-runner each tick

i.e. **two cooperating subsystems constructed by the same init
function, not the same object**. Still a convergence — both hunts
landed on the ldn-init code path.

### What the visitor actually is (best current reading)

Not proven, but the shape is tight:

- Per-tick broadcast over a vector of registered receivers.
- Each tick, builds a `0x60`-byte **derived command packet** with two
  cloned sub-objects from a shared source + installs a specific
  derived vtable.
- Dispatches via `elem->vt[3](elem, packet)`.
- The same receivers, via `FUN_71037857f0`, maintain three parallel
  ring-buffer cursors — the backing store of a **replay/command
  stream**.
- All installed by `game_ldn_initialize`, which is also the source of
  Pool A match-runner signal.

**Best reading:** `FUN_7103619080` is the **per-tick commit/flush
broadcast** to a set of command-stream writers — i.e. the moment each
frame where the match-runner tells every recorder to advance by one
tick and here is the per-tick metadata packet. That is the exact role
a sim-tick would have if SSBU rollback is implemented on top of the
replay/command-stream subsystem. But the receivers could also be pure
replay writers (non-rollback), in which case this is the
**replay-recording tick** rather than the **simulation tick** proper.

### Recommended Round 5

1. **Manual-extract `game_ldn_initialize @ 0x7103744360`** (too large
   for Ghidra MCP) — map how `[0x7105336ce8]` and `[0x710593a510]`
   relate, and whether either is stored as a field of the other.
2. **Dump the 0x710593a000 page structure** — the 10-slot config
   records at `[0x710593a7c8 + i*0x40]` are tables that name the
   probe/command type per slot. Resolving one entry (the vtable and
   the three `u64` values loaded per slot) will tell us what each
   slot DOES and therefore what slot means here.
3. **Identify the receiver class** — grep for a vector-of-ptrs field
   at offset `+0x500` of any documented class, or look for a function
   that does `subsys->vector.push_back(receiver)` on
   `[0x7105336ce8]`. That is the `register()` entry point for
   whatever interface this is.
4. **Decide rollback vs. replay-only.** If the receivers are pure
   replay writers, `FUN_7103619080` is the replay-recording tick and
   the real sim tick is elsewhere. If they are rollback-capable
   snapshot recorders, this IS the sim tick. The disambiguator is
   whether there is a rewind/restore entry point that calls the same
   receivers in reverse.

### Methodology note

Round 3 got the structure of `FUN_7103619080` almost right but
mislabeled the final `*new_node = &DAT_7105230f18` write as a
type_tag field. It is actually the standard derived-vtable overwrite
at the end of a C++ constructor chain. The mistake is easy to make
from the visitor alone, but becomes obvious once you compare to
sibling factories (`FUN_71035b91b0`, `FUN_7103819bb0`,
`FUN_710363f4a0`) which all follow the same base/derived vtable
install pattern. **Lesson: when a function writes a `DAT_*` as the
first word of a freshly-allocated object, it is almost always a
vtable install — check for sibling constructors with the same
`DAT_*` before calling it a type tag.**

---

---

## Pool C — Round 4: FUN_71035c13d0 deep dive + cross-validation (2026-04-10)

### FUN_71035c13d0 detailed analysis

Full Ghidra decomp cached at `data/ghidra_cache/pool-c.txt` under
"ROUND 4 — FUN_71035c13d0 (observer double-sweep dispatcher)".

- **Subsystem owner type:** graphics/viewport listener manager rooted at
  `DAT_7105335e10` (NOT the Mii manager, NOT the MatchRunner, NOT the
  main_loop application driver). See caller analysis below.
- **Observer list 1 (event queue A):** `param_1+0x60..+0x68`, stride
  `0x40`. Each event carries a u64 payload at `+0x00/+0x08`, u64 args at
  `+0x10/+0x20`, and a u32 at `+0x30`. Dispatched to listener `vt[0x38]`
  with 5 args `(event.arg1, event.arg2, event.u32_tag, listener, &event_payload)`.
- **Observer list 2 (event queue B):** `param_1+0x78..+0x80`, stride
  `0x30`. Each event is u32 tag + two u64 args. Dispatched to listener
  `vt[0x40]` with 4 args.
- **Shared listener list:** `param_1+0x08..+0x10`, stride `0x10`. Each
  entry is `{obj_ptr, weak_ctrl_ptr}` — classic `std::vector<std::weak_ptr<T>>`.
- **Pre-sweep viewport latch (gated on dirty bits `+0x160`/`+0x161`):**
  allocates a `nu::GraphicsModule` command buffer via
  `(*(DAT_7105336ce8 + 0x10))->[0xa8]->vt[0x18]`, copies two 4×u32 rects
  from `param_1+0x140..+0x14c` and `+0x150..+0x15c` into `buffer+0x80..+0x8c`
  and `buffer+0x90..+0x9c`, then releases the buffer. This is the classic
  window-resize / scissor rect update path.
- **Per-frame fighter state mutation?** **NO.** Zero fighter iteration,
  zero `BattleObjectModuleAccessor` vtable touches, zero FighterManager
  references. Both sweeps are early-out no-ops unless dirty bits are set
  or events have been enqueued.
- **Vtable slots dispatched:** `vt[0x38]` and `vt[0x40]` on the shared
  listener interface. Neither slot is in the
  `BattleObjectModuleAccessor` `+0x38..+0x188` module range.

### Caller in main_loop @ 0x710374af6c

Literal disassembly of the call site:

```
0x710374af5c: bl   0x7103632850             ; scene UI state machine (dead end)
0x710374af60: bl   0x710361e7e0             ; sibling helper (uncategorized)
0x710374af64: adrp x8, 0x7105335000
0x710374af68: ldr  x0, [x8, #0xe10]         ; x0 = *DAT_7105335e10
0x710374af6c: bl   0x71035c13d0             ; <-- OUR TARGET
```

So `param_1` is loaded from a **global singleton at `DAT_7105335e10`**,
not from any field of main_loop's cached `this` pointer (`x21`), not
from `DAT_710593a510` (Pool A/B's MatchRunner), and not from
`DAT_710593a6a0` (Pool A/B's Mii manager).

### Identity of DAT_7105335e10 (subsystem owner)

`tools/xref_bin_scan.py 0x7105335e10` returned:
- **1 writer** at `0x71035a5054` in `FUN_71035a4130` (install path;
  decomp timed out — logged in `manual_extraction_needed.md`)
- **24 readers**, dominated by:
  - `StageBase` @ `0x71025d2dc0` — reads 3× (creation/teardown)
  - `create_stage` @ `0x7102633c90` — reads 3×
  - `FUN_71035b9660`, `FUN_71035b9750`, `FUN_71035bb620`, `FUN_71035c13d0`,
    ~8 more phase-6 graphics-cluster helpers
  - A handful of `FUN_71014xxxx` / `FUN_710133c4a0` Lua-bind readers
  - `main_loop @ 0x710374af68` (the dispatch site above)

The presence of **`StageBase`** and **`create_stage`** as readers is the
smoking gun: `DAT_7105335e10` is a **Stage / scene viewport / surface
listener singleton**, installed once by `FUN_71035a4130` (stage init)
and read throughout the phase-6 graphics cluster for per-frame viewport
dispatch.

Combined with the function's internal use of:
- `DAT_7105336ce8` (the render-singleton family used by camera proj/view
  math and SH-ambient lighting)
- `nu::GraphicsModule::Instance()` (explicit demangled name)
- 4-u32 viewport/scissor rect copies

…the identity lock is tight: **`DAT_7105335e10` is an app-level stage
viewport / window listener manager**, and `FUN_71035c13d0` is its
"dispatch queued viewport events to all registered listeners" method.

**Same subsystem as FUN_7103619080's caller?** **NO.**
`FUN_7103619080`'s caller at `0x710374b120: ldr x0, [x21, #0xce8]`
loads from an offset on the cached main_loop `this` pointer (`x21` set
at `0x71037472ac: mov x21, x0` at main_loop entry). That is a sub-object
of the application driver, NOT a free-standing global. Different
singleton, different subsystem.

**Same subsystem as FUN_7103593c40's caller?** **NO.**
`FUN_7103593c40`'s caller at `0x7103749a64: ldr x0, [x8, #0xb00]`
loads from `DAT_7105334b00` — a third, unrelated singleton. Three
phase-6/7 candidates, three different roots, zero overlap.

### Cross-validation — Pool A and Pool B Round 4 findings

Read via `git log --oneline master..worker/pool-{a,b}`:
- Pool A round 4: "identify the MatchRunner type at `*DAT_710593a510`"
  (commit `e79f481`, WORKER-pool-a.md only — no shared-doc append yet).
- Pool B round 4: "identify what FUN_7103619080 dispatches (caller + tags)"
  (commit `e03c49f`, WORKER-pool-b.md only — no shared-doc append yet).

Both pools are investigating **independent** candidates (the MatchRunner
pointer at `DAT_710593a510` and the visitor loop at `FUN_7103619080`).
Neither shares a root with `FUN_71035c13d0`.

**The main_loop prologue fast path already identifies the real
per-frame dispatcher.** Disassembly of main_loop's first ~0x80 bytes:

```
0x71037472a4: ldr  x8, [x0]                 ; x8 = (*this)->vtable
0x71037472a8: ldr  x8, [x8, #0x18]          ; vt[0x18] = beginFrame hook
0x71037472ac: mov  x21, x0                  ; x21 = cached `this` (app driver)
0x71037472b0: blr  x8                       ; beginFrame() -- installs DAT_710593a510
0x71037472b4: str  x21, [DAT_710593a4c0]    ; publish this
0x71037472bc: bl   0x71039c7670             ; PLT stub (imported)
0x71037472c0: bl   0x71039c7570             ; PLT stub returning int frame phase
0x71037472d0: str  w0, [DAT_710593a534]     ; cache phase integer
0x71037472d4: ldr  x0, [DAT_710593a510]     ; load MatchRunner
0x71037472d8: cbz  x0, 0x7103747304         ; *** GATE: if null, SKIP ***
0x71037472dc..ec:  branch on phase {0, 1, >=2}
0x71037472f4: ldr  x8, [x0]                 ; x8 = MatchRunner->vtable
0x71037472f8: ldr  x8, [x8, #0x30]          ; vt[0x30] = per-frame driver
0x71037472fc: add  x1, sp, #0x270           ; arg1 = &local_phase_int
0x7103747300: blr  x8                       ; *** PER-FRAME DISPATCH ***
```

The sequence is:
1. `main_loop` is called **once** by `nnMain` with `x0 = app_driver`
   (a polymorphic object whose `vtable[0x18]` is a `beginFrame()` hook
   that installs/updates `DAT_710593a510` as a side effect).
2. main_loop caches `this` at `DAT_710593a4c0` and the frame-phase int
   at `DAT_710593a534`.
3. If `DAT_710593a510` is non-null, it invokes `MatchRunner->vt[0x30]`
   with a pointer to the cached phase int as arg1. **This is the real
   per-frame match driver invocation.**
4. The rest of main_loop runs scene/graphics/HUD work including the
   three phase-6 dispatchers FUN_71035c13d0 / FUN_7103593c40 /
   FUN_7103619080 — all rooted in independent singletons unrelated to
   the MatchRunner.

Pool A's MatchRunner lead and Pool B's "DAT_710593a510 is the
match-active signal" lead **converge on the same `blr x8` at
`0x7103747300`**. That is the per-frame sim tick entry point. It is
NOT one of main_loop's direct `BL` children — it is an indirect call
through the MatchRunner's vtable, which is exactly why the 84
direct-child BL sweep missed it.

**Converged? YES.** Pool A + Pool B leads converge. The sim tick lives
inside `(*DAT_710593a510)->vt[0x30]` at `main_loop+0x90`.

### Final ranking (most -> least likely sim tick)

1. **`(*DAT_710593a510)->vt[0x30]` at `main_loop+0x90`** (Pool A/B) —
   **strongest by far**. Only per-frame vtable dispatch in main_loop
   that is *gated on the presence of a non-null MatchRunner* and
   *branches on the cached frame-phase integer*. The 27 external
   readers of `DAT_710593a534` cross-validate that the cached int is
   a "game phase" key, consistent with "match running / in CSS /
   paused". Next step: Pool A should walk the MatchRunner's vtable
   `+0x30` target down to the fighter iteration.

2. **`FUN_7103619080`** (Pool B) — per-element visitor/command-packet
   broadcast with `+0xf1` dirty-flag gate. Rooted in
   `[app_driver + 0xce8]`, a sub-object of main_loop's `this` — so it
   belongs to the **application/UI driver neighborhood**, not the
   match runtime. Likely an input-event or render-command producer.
   Interesting but second-tier — the per-element nature is shape-only
   evidence; the element count and element type haven't been confirmed
   to be fighter-sized.

3. **`FUN_71035c13d0`** (this pass) — graphics viewport change / listener
   broadcast. Rooted in `DAT_7105335e10` (Stage/viewport singleton,
   cross-validated via StageBase + create_stage readers). Confirms
   Pool B's pass-1 "graphics dispatcher" verdict in full. Adds the
   caller singleton identity as new information. **DEAD END for sim.**

4. `FUN_7103593c40` — ring-buffer shared_ptr release from `DAT_7105334b00`.
   Fourth distinct singleton, indirect calls fire only during object
   teardown (vt[1] = destructor). Not a dispatcher.

5. `FUN_71036186d0` — pure camera/viewport math, zero `blr`. Confirmed
   dead end in round 3.

### Recommendation for rollback / sim-tick hunt

**Retire all four phase-6/7 candidates.** They are three independent
graphics/UI subsystems plus one pure math function — not related to
the sim tick.

**The sim tick hunt's next hop is inside `MatchRunner->vt[0x30]`**
(the function at `*(*(DAT_710593a510))+0x30`). Pool A should:
1. Decompile the `FUN_7103741988` area to locate the writer at
   `0x7103741a60` and confirm what type of object is installed into
   `DAT_710593a510` — that identifies the MatchRunner class.
2. Once the class is known, read vtable slot `+0x30` and decompile the
   target. That function is invoked per-frame with `(this, int *phase)`
   and IS the match-active driver.
3. Walk its calls: if it iterates `FighterManager` entries,
   `BattleObjectWorld`, or calls a `tick()`-shaped method on each of
   them, the sim tick is found.

### Artifacts this pass

- `data/ghidra_cache/pool-c.txt` — full Ghidra decomp of `FUN_71035c13d0`
  with annotated field map, sweep structure, and subsystem interpretation.
- `data/ghidra_cache/manual_extraction_needed.md` — `FUN_71035a4130`
  logged (sole writer of `DAT_7105335e10`, timed out after 120s).
- No src/ changes. Documentation-only pass per
  `WORKER-pool-c.md`'s primary deliverable.
- Ghidra renames: **none this session** (all new information is in
  shared docs, not symbols).
---

## Pool A — Round 5: bottom-up RNG-driven sim tick walk (2026-04-10)

### Approach

Rounds 1–4 worked top-down (main_loop → child functions → is it a sim tick?)
and failed: all 56 direct BL children of main_loop were classified as
scene/UI/graphics/housekeeping. The remaining candidate,
`(*DAT_710593a510)->vt[0x30]` at main_loop+0x90, is an indirect dispatch
whose target cannot be resolved statically.

Round 5 flips the direction: start from every callsite of the gameplay RNG
(`app::sv_math::rand`), walk upward through callers, and see if any chain
reaches main_loop. The sim tick MUST call rand transitively (every frame,
AI rolls, attack-SE rolls, Hero crit procs, etc.) so if we walk up from the
leaves we should eventually land in it.

### Step 1 — enumerate rand callsites

Direct `get_xrefs_to` on the six wrapper addresses:

| Wrapper | Address | Ghidra xrefs |
|---|---|---|
| `app::sv_math::rand` | `0x7102275320` | 1 (`FUN_710213a360` lua-bind wrapper) + dynsym |
| `app::sv_math::randf` | `0x71022756c0` | 1 (`0x710213a9f4` lua-bind wrapper) + dynsym |
| `app::random::get_float` | `0x71015cf234` | **NO xrefs** (fully inlined) |
| `app::random::range_int` | `0x71015cf294` | **NO xrefs** (fully inlined) |
| `app::ai_random::range_int` | `0x71003766d4` | **NO xrefs** (fully inlined) |
| `app::ai_random::get_float` | `0x7100376774` | **NO xrefs** (fully inlined) |

Confirms rng.md §4: the named wrappers are fully inlined at every C++ call
site. Ghidra xref enumeration on them is useless.

The only tractable enumeration is `get_xrefs_to 0x71052c25b0` — the
Randomizer singleton global. That returns **~245 READ sites** across
**~117 unique functions**. That is our leaf set for the upward walk.

### Step 2 — intersect leaf set with main_loop's direct-BL set

Extracted from `asm/ghidra_FUN_7103747270.c`:
- main_loop direct BL set: **56** unique functions (0x71000..0x71053 range)
- RNG singleton reader set: **81** unique `FUN_*` identifiers (plus the
  named functions like `change_action`, `play_voice`, `is_percent`, etc.)
- **Intersection: 0 (empty).**

No RNG reader is a direct child of main_loop. Consistent with Round 4's
conclusion that all 56 BL children are phase-6/7 scene dispatchers plus
pead/housekeeping plumbing.

### Step 3 — upward walk from representative readers

For each chosen leaf, `get_function_xrefs` until the chain terminates.
Selected leaves span AI, fighter-internal, item, camera, and module-level
readers to maximize coverage of different dispatch shapes.

| Leaf reader | Chain | Termination |
|---|---|---|
| `FUN_71002f2a00` (AI, 20+ singleton reads, dispatches AI pad cmds) | → `FUN_71002ef000` → `FUN_71002edd30` → `FUN_71002d8ef0` | `change_action`/`change_mode` [dynsym EXTERNAL], `FUN_71003153e0` [NO xrefs], `FUN_7101f83630` [Lua bind region] |
| `FUN_71002ec1a0` (AI behavior) | → `FUN_7101f836e0` → `FUN_7101f87300` → `FUN_7101f45620` → `FUN_71022b7100` → `0x71022dc26c` | orphan + `change_target` [dynsym] |
| `FUN_7100826750` (fighter attack SE roll) | → `FUN_710081f5b0` | `0x7104f90d18` [DATA — vtable slot] |
| `FUN_71006a7100` (crit-hit cut-in) | → `FUN_7100695f20` → `FUN_7100696720` | fan-out to 10+ fighter statuses; `request_critical_hit_cut_in` [dynsym]; `REQ_FINAL_START_CAMERA` via `FUN_7101fc1140` → `FUN_7101fc7f30` [PARAM hub] |
| `final_ready_exec` | → `FUN_710215ddd0` | **NO xrefs** (vtable-only) |
| `FUN_7101008340` (item spawn) | → `FUN_7101008e60` | `0x71050230d0` [DATA — vtable slot] |
| `get_dead_up_camera_hit_first_rand_rot_z` | — | `0x7101f99b80` [orphan] + dynsym |
| `get_dead_up_camera_hit_first_rand_offset_x` | — | `0x7101f99b30` [orphan] + dynsym |
| `FUN_71009a4190` (large module reader) | — | `0x7104faa5e8` [DATA — vtable slot] |
| `FUN_71005b4720` (large module reader) | — | `0x7104f7a048` [DATA — vtable slot] |
| `FUN_71034df9e0` | — | `0x710043fe40` [DATA — vtable slot] |
| `FUN_71034fde10` | — | `0x710521d130` [DATA — vtable slot] |
| `FUN_71035357c4` | — | jump table (`UNCONDITIONAL_JUMP` from 6 sites in the same function) |
| `FUN_7102602ec0` | — | `FUN_7101344cf0` (Randomizer **constructor**, boot-only) |
| `FUN_71003fb290` → `FUN_71003fd0b0` | — | 4x orphan addresses (0x710057e0c4, 0x71033bea54, 0x71033e9824, 0x71034e7648) |
| `FUN_7101325880`, `FUN_71015490a0`, `FUN_7101548d50` (item/AT) | — | all DATA slots in `0x710505d*`/`0x710506e*` range |
| `FUN_7101008e60` (item subsys) | — | `0x71050230d0` [DATA vtable slot] |
| `call_final_module`, `play_voice` | — | dynsym + `FUN_7101f45620`/`FUN_71021afd70` [PARAM hub] |

### Step 4 — common hub: `FUN_7101f45620`

Five of the walks converged on `FUN_7101f45620` as the penultimate hop, each
via a `[PARAM]` reference (i.e. the reader's address is passed as a callback,
not called directly). FUN_7101f45620 lives in the `0x7101fxxxxx..0x71022xxxxx`
lua_bind region and is the **Lua binding function-pointer registration
machine** — it takes a C++ function pointer and installs it as a Lua metatable
method. This is not a per-frame dispatcher; it runs once at script load.

### Step 5 — termination classification

Every upward walk I ran bottomed out at one of five patterns:

1. **dynsym `From Entry Point [EXTERNAL]`** — the function is a Lua export
   called from a script VM, not from native C++. (change_action, change_mode,
   change_target, play_voice, call_final_module, final_ready_exec, all the
   `get_dead_up_camera_*`, all `REQ_*_CAMERA`, etc.)
2. **`[DATA]` reference** to a vtable slot in `0x7104f*`/`0x710505*`/`0x710506*`/
   `0x71052*` (FighterStatus, ItemModule, and related modules). The caller is
   whatever iterates the matching module list and invokes that slot — which
   is exactly the invisible indirect dispatch the hunt is trying to find.
3. **`[PARAM]` reference** into the `FUN_7101f45620`-family Lua-binding
   registration hubs. The function is a C++ callback registered once at
   script load; actual invocation happens from the Lua VM.
4. **Orphan addresses** (`From 710xxxxxxx [UNCONDITIONAL_CALL]` where the
   address is not inside any Ghidra-recognized function). These are thunk
   islands, switch-statement tails, or PLT stubs Ghidra hasn't split.
5. **`FUN_7101344cf0`** — the Randomizer constructor itself (~32 KB). This
   is boot-time, not per-frame — it initializes the singleton.

### Sim tick verdict — STATIC ANALYSIS EXHAUSTED

The bottom-up walk produces the exact same wall as the top-down walk:

- **Top-down (Rounds 1–4):** main_loop's 56 direct BL children are all
  phase-6/7 scene/UI/graphics/housekeeping dispatchers. The only remaining
  candidate is `(*DAT_710593a510)->vt[0x30]` at main_loop+0x90, which is
  an **indirect dispatch** whose target is unknown until runtime.
- **Bottom-up (Round 5):** 100% of RNG reader chains terminate at dynsym
  exports, vtable DATA slots, Lua-bind PARAM callbacks, or orphan thunks.
  **Zero** chains reach a direct BL child of main_loop.

The two walks converge on the same conclusion: the sim tick is only
invoked via **indirect dispatch**. Specifically, the dispatch graph is:

```
main_loop @ 0x7103747270
  -> (direct BL into phase-6/7 scene drivers, all retired in Rounds 1-4)
  -> (indirect BLR into MatchRunner->vt[0x30] at main_loop+0x90)   <-- sim tick lives here
        -> (indirect BLR into FighterManager->iterate_and_tick)
            -> (indirect BLR into FighterStatus vt slot per fighter)
                -> AI/status/motion code reads singleton 0x71052c25b0
                  (rand calls, fully inlined so the singleton-read pattern
                   is the only static trace)
```

Every arrow in that chain except the first is an **indirect dispatch** —
invisible to `get_function_xrefs` because the target is loaded from memory
at runtime, not baked into a BL immediate.

**Recommendation: retire static analysis for this hunt and switch to dynamic.**

### Dynamic analysis plan (Round 6 is NOT a static walk)

The cheapest dynamic approach:

1. Launch SSBU in Eden/Ryujinx with GDB attached.
2. Start a local match (so the Randomizer singleton is populated and all
   three pointers in the 3-deref chain from `0x71052c25b0` are valid).
3. Resolve the 180-byte channels pointer: three loads from `0x71052c25b0`
   per rng.md §2. Cache the resulting address.
4. Set a **write** watchpoint on any 20-byte slot inside the 180-byte
   buffer (e.g. channel `+0x78` = `app::random` main gameplay channel).
5. Continue execution. When the watchpoint fires, dump the backtrace.
6. The backtrace's leaf frame is the inlined rand site. Walking the
   backtrace upward reveals:
    - the fighter/AI function that rolled (leaf)
    - the FighterStatus slot that invoked it (1-2 frames up)
    - the FighterManager iterator (2-3 frames up)
    - **the sim tick entry point** (3-4 frames up)
    - the vtable dispatch inside main_loop (4-5 frames up)
    - `main_loop @ 0x7103747270` (5-6 frames up)
7. Record the addresses at each frame, rebase to the Ghidra image, and
   look them up. We now have the sim tick with zero guessing.

The MCP server already has GDB support (`mcp__gdb-multiarch__*`). The
orchestrator should assign this to a pool with an emulator set up, OR the
pool running with a Windows build + emulator snapshot should drive it.

**Estimated cost:** ~1 hour of dynamic analysis vs. the ~5 rounds × multiple
pools of static analysis we've burned so far. Round 5 is the signal to stop
spending static-analysis budget on this hunt.

### Artifacts this pass

- `data/ghidra_cache/pool-a.txt` — appended full Round 5 walk notes,
  reader classifications, and raw xref outputs.
- No `src/` changes. Documentation-only pass per the WORKER-pool-a.md
  "Documentation is the primary deliverable" rule.

### Cross-validation against Rounds 1–4

- Round 2 (Pool B): main_loop has two indirect dispatchers — one is the
  `MatchRunner->vt[0x30]` at main_loop+0x90, the other is a graphics-cluster
  dispatcher. **Consistent.** Round 5 confirms the non-match-runner indirect
  dispatchers are all graphics/UI.
- Round 3 (Pool A): `DAT_710593a510` was thought to be a "match-active gate".
  Round 4 corrected that to "MatchRunner pointer, non-null gate". **Round 5
  adds nothing new about that pointer itself** — it only confirms that
  nothing else in main_loop's static call graph can be the sim tick.
- Round 4 (Pool A): `this` passed to main_loop is a lightweight boot context,
  NOT the match driver. The match driver is reached via the MatchRunner
  singleton, not via main_loop's `this`. **Consistent with Round 5:** the
  sim tick is not reachable from main_loop's `this->...` object graph either,
  because `this` doesn't own the MatchRunner — the global `DAT_710593a510` does.
- Round 4 (Pool B): `FUN_7103619080` is a per-element visitor rooted in
  `[app_driver + 0xce8]`. **Consistent:** Round 5 never encountered
  `FUN_7103619080` as a parent of any RNG reader, confirming it is a
  UI/input event broadcast, not sim.
- Round 4 (Pool C): `FUN_71035c13d0` is a graphics viewport listener.
  **Consistent:** Round 5 never encountered it either.

All five rounds converge on: the sim tick is
`(*DAT_710593a510)->vt[0x30]`, and the vtable slot cannot be resolved
statically. Dynamic analysis is the next hop.

---

## Pool B — Round 5: FUN_71037857f0 deep dive (2026-04-10)

**TL;DR — NOT THE SIM TICK.** The "10-slot broadcaster" that Round 4
flagged as the strongest tick-shaped lead is the per-frame dispatch
into a `LayoutManager` render-layer command stream. The 10 slots are
10 **named layout layers**, not 8 players + 2 pads. The receiver is a
graphics / UI-layout command recorder; its `vt[3]` appends `Packet*`
nodes to a triple-cursor ring buffer. No fighter-state iteration, no
`BattleObject` or `FighterManager` access, no module-accessor traffic.

Round 5 was supposed to disambiguate "replay-recording tick vs sim
tick proper". The actual answer is **neither** — it is a layout
subsystem command-stream flush, fully in the render-path family, not
on the sim/replay path at all. Round 4 over-read the "10 slots"
coincidence.

### Function structure — FUN_71037857f0(container*, uint slot, probe*, uint flags)

Full decomp cached in `data/ghidra_cache/pool-b.txt` under
"ROUND 5: FUN_71037857f0". Key points:

```c
void dispatch_layout_slot(LayoutMgr* ctr, uint slot, LocalProbe* pr, uint flags) {
    if (slot > 9) abort();

    // Early-exit: slot has nothing to emit (begin==end on per-slot sub-vector)
    LayoutSlot* s = &ctr->slots[slot];   // slots stride 0x18 at container+0
    if (s->range_begin == s->range_end) return;

    // Resolve global current-frame stamp (only consumed when flags.0 is set).
    GlobalFrameCtx* g = *(GlobalFrameCtx**)(DAT_7105334480 + 0x68);
    LayoutSink* sink = pr->sink;          // = *(LayoutSink**)(pr + 8)

    // ... frame-stamp plumbing into locals puStack_50 / local_48 ...

    CmdStream* cs = *(CmdStream**)(&ctr->per_slot_cs[slot]);
                    //   = ctr->per_slot_cs[slot]   (array of 10 CmdStream* at ctr+0x330)

    if ((flags & 1) == 0) {
        // ===== ADVANCE-ONLY (no packet build) =====
        // Finalise the currently-open entry (if cs->open_flag == 1),
        // then walk three parallel ring cursors forward:
        //   header ring  at +0x3f0   stride 0xe8   backing region +0x50
        //   index  ring  at +0x418   stride 0x08   backing region +0x3f8
        //   payload ring at +0x4a0   stride 0x10   backing region +0x420
        // Wraps by pointer equality (ring_base + stride -> back to ring_base).
    } else {
        // ===== BUILD + DISPATCH =====
        Packet* hdr = make_header_packet(cs, &local_probe, 1);
        if (hdr) {
            Packet* p1 = clone_block_A(cs, &ctr->src_block_0x2d0);
            sink->vt[3](sink, p1);
            Packet* p2 = clone_block_B(cs, &ctr->src_block_0x2f0);
            sink->vt[3](sink, p2);
            Packet* p3 = clone_block_C(cs, &ctr->src_block_0x310);
            sink->vt[3](sink, p3);
            Packet* p4 = clone_block_D(cs);
            sink->vt[3](sink, p4);
            sink->vt[3](sink, hdr);
            // Trailing synthesized packet derived from cs+0x50 region:
            uint64_t sz = 0x80, align = 0x10;
            void* buf = (*cs->ring_block)->vt[0x30](cs->ring_block, &sz, &align);
            FUN_71035b91b0(buf, cs+0x30, cs+0x60);
            sink->vt[3](sink, buf);
        }
    }
}
```

Every call site in `main_loop` passes `container = *(void**)0x710593aa90`
(a singleton pointer — see below), a per-call **stack-local probe**
loaded from `0x710593a748 + i*0x20` (stride 0x20, slot ordering
`{4,3,0,1,2,5,6,7,8,9}`), and a shared `flags` dword from `[sp+0x258]`.
Each probe is `{ vtable=0x710522eea0, cs=[config+0x00], u64_1=[config+0x08], u64_2=[config+0x10] }`.

**Round 4 misread the stride as 0x40 and called this a per-player loop
(8 + 2 pad). The actual stride is 0x20 and the base is 0x710593a748,
not 0x710593a7c8. The 10 slots are layout layers.**

### The "10 slots" are the 10 LayoutManager render-layer categories

The receivers at `0x710593a748 + i*0x20` are **named services** resolved
at startup by string-keyed `std::map` lookup from a `LayoutManager`
registry — not fighters, not LDN peers, not network connections.

`FUN_710375a630` is the sole writer of `DAT_710593aa90`. It is a lazy
singleton installer that allocates a 0x448-byte `LayoutManager`
object, zero-inits it, then runs a 10-iteration loop over a static
table at `&PTR_s_LayoutManager__Normal__710523cb40` — an array of 10
C-strings passed through FNV-1a hashing and registered into the
container's slot table. The 10 names (from `list_strings`, all with
`"LayoutManager (...)"` prefix) are:

| # | Name | Address |
|---|---|---|
| 0 | `LayoutManager (Normal)`          | `0x710439abe5` |
| 1 | `LayoutManager (EffectBG)`        | `0x710425cdaf` |
| 2 | `LayoutManager (Final)`           | `0x710427e513` |
| 3 | `LayoutManager (Mirror Main)`     | `0x71042c28a3` |
| 4 | `LayoutManager (AuroraVision)`    | `0x710430607d` |
| 5 | `LayoutManager (3D BG)`           | `0x71043279aa` |
| 6 | `LayoutManager (OffScreen/Model)` | `0x7104347cff` |
| 7 | `LayoutManager (MovieEditWork)`   | `0x7104430b1b` |
| 8 | `LayoutManager (Sharp)`           | `0x7104452365` |
| 9 | `LayoutManager (OffScreen)`       | `0x710445237b` |

(Slot-to-name mapping is approximate — the exact permutation depends
on which index each name gets during the FNV registration loop. The
call-site slot ordering `{4,3,0,1,2,5,6,7,8,9}` in main_loop is the
order the render pass is walked, not the registration order.)

The memcmp jump table at `0x710374b680..b830` in main_loop dispatches
on the SSO string length of each registry key and routes short-name
variants (`"IU_SHARP"`, `"IU_FINAL"`, `"IU_FG_3D"`, `"M_E_WORK"`, and
a length-6 name compared against `0x710439abd3`) to their matching
slot in `0x710593a748..+0x140`. These short names are the
**composition-shader / image-unit sub-targets** referenced by the
LayoutManager (`IU_*` = Image Unit = post-process compositor pass,
`M_E_*` = Mesh Effect work buffer). They are render targets, not
fighters.

### Receiver vt[3] body

Not decompiled in full — unnecessary. The call-site `sink->vt[3]` is
a `void (this, Packet*)` that appends `Packet*` to the sink's own
triple-cursor ring. From Round 4's factory walk:

- header ring  at `+0x3f0` stride `0xe8` — fixed-size command header
- index  ring  at `+0x418` stride `0x08` — packet offset into header ring
- payload ring at `+0x4a0` stride `0x10` — 16-byte payload descriptor

Three parallel rings with pointer-equality wrap is the canonical
shape of a **GPU command buffer / display list recorder**, exactly
the shape NVN/GX2/DirectX-style render-layer command streams use.

### Per-slot source data

The three 0x20-byte source blocks at `container+0x2d0`, `+0x2f0`,
`+0x310` are **cloned into every packet the container emits** — they
are NOT per-slot data, they are per-*frame* constants inherited by
all 10 packets (camera/view matrices, viewport rect, render-state
snapshot — the usual per-frame render constants). No element of this
data path touches `FighterManager`, `BattleObject`, or
`BattleObjectModuleAccessor`.

### VERDICT — RENDER / LAYOUT SYSTEM, NOT A TICK

**This is not the simulation tick. It is not the replay-recording
tick either.** It is the per-frame flush of the 10-layer
`LayoutManager` render-command stream. Each of main_loop's 10 calls
to `FUN_71037857f0` submits one render-layer's accumulated packets
(per-frame constants + 1 synthesized trailer) into the backing GPU
command buffer, or walks the ring cursors forward when there is
nothing to emit. The ring-buffer / 10-slot / per-frame signature that
made Round 4 flag this as tick-shaped is real, but the "tick" it
represents is a **graphics frame**, not a sim/replay frame.

Confidence: **high**.

- Sole writer of the container singleton is a `LayoutManager`
  installer with 10 literal `LayoutManager (...)` strings, one per
  slot.
- Short-key route table matches classic image-unit / mesh-effect
  render target names.
- Packet factories clone per-frame camera/view state, not fighter
  state. No offset on the receiver or container matches a known
  fighter or BattleObject struct layout.
- `vt[3]` signature `(this, Packet*)` with a 3-cursor ring sink is
  the standard GX2/NVN command-stream recorder shape.

### Cross-reference impact on earlier rounds

- **Pool A's `[0x710593a510]` (MatchRunner) lead is unaffected.**
  It lives in the same 4 KB page (`0x710593a000`) as the LayoutManager
  globals but is a different object. The Round 4 "same 4 KB page"
  convergence was a packaging coincidence, not a structural one —
  this page holds multiple unrelated renderer-side singletons.
- **Pool B Round 4's `FUN_7103619080` verdict needs re-reading.** The
  Round 4 "best reading" was "per-tick commit/flush broadcast to a
  set of command-stream writers" and speculated it might be the
  replay-recording tick. That structural reading is correct; only the
  "maybe sim/replay" label is wrong. `FUN_7103619080` is structurally
  identical to `FUN_71037857f0` (factory + ring-push via `vt[3]`)
  and is almost certainly **another renderer command-stream
  broadcaster** for a different subsystem — not sim, not replay.
  The receivers (element flag at `+0xf1`, vtable slot 3
  `(this, Packet*)`) match the LayoutManager sink class shape.
- The `game_ldn_initialize` convergence (both globals initialised
  from the same function) is **still interesting** but downgraded —
  it's LDN calling through to install renderer-side snapshot
  recorders at init, not "LDN + sim are the same subsystem". LDN
  can push display/recording state into the layout manager at init
  without making the layout manager a sim driver.

### Recommendation — pivot to dynamic analysis

Rounds 1..5 have now ruled out every static-analysis lead reachable
from `main_loop` via the "child-function shape" heuristic. The four
Pool-B phase-5/6/7 children are all render/housekeeping, the Pool-C
observer dispatcher is graphics, the Pool-A MatchRunner is the
active-match driver at the boot-context level (not a per-frame tick),
and the 10-slot broadcaster is a render-pass stream flush. None of
them iterate `FighterManager` or mutate `BattleObject` state.

**Static analysis of `main_loop`'s direct and 2-deep children has been
exhausted.** The sim tick is either (a) further nested than anyone has
gone yet (3+ deep, inside what Round 1 labelled a pure-graphics or
pure-input call), or (b) driven by a callback registered at startup
and invoked from a context that does not textually appear as a `bl`
from main_loop (e.g. `nn::os::EventHandler`, a graphics VSYNC
callback, or the LDN match-runner vt slot).

**Switch to dynamic analysis.** The cheapest next step is a GDB
hardware watchpoint on a well-known per-frame fighter field — e.g.
`FighterStatus::situation_kind` of the first `BattleObject` in a
loaded match — and let the CPU tell us which function's `bl` frame
is hot when that field is written. Round 6 should set that up and
read back the call stack from a running 13.0.4 instance rather than
guessing further from static decomp.

### Methodology note

Round 4 made one avoidable error: treating "10 slots x per-frame call"
as structurally identifying a per-player tick without verifying that
any per-slot datum belonged to a fighter. The LayoutManager's 10
layers are a coincidence with SSBU's 8+2 player cap; shape-matching
on headcount is not sufficient, the per-slot source data has to be
traced to a known fighter type before committing. The corrective
rule: **before calling a 10-slot loop a "per-player tick", find one
per-slot load that resolves to a FighterManager entry or a
BattleObject pointer.** If you can't produce that chain, the 10-slot
shape is not evidence.

Round 4 also misread the call-site stride (0x40 vs the actual 0x20)
because it only skimmed the first two call sites. The first two sites
pass base addresses 0x710593a7a8 and 0x710593a7c8 which are +0x20
apart, not +0x40 — Round 4 doubled the stride. All 10 sites dumped
here: slot 0->0x748, 1->0x768, 2->0x788, 3->0x7a8, 4->0x7c8,
5->0x7e8, 6->0x808, 7->0x828, 8->0x848, 9->0x868.

### Artifacts this pass

- `data/ghidra_cache/pool-b.txt` — appended Round 5 decomp of
  `FUN_71037857f0` with per-path annotation and ring-buffer offsets.
- No `src/` or `include/` changes. Documentation-only pass per
  `WORKER-pool-b.md`'s primary deliverable.
- No Ghidra renames this session — the involved classes
  (`LayoutManager`, `LayoutSink`, `CmdStream`) are worth naming but
  only after the full renderer subsystem decomp, which is out of
  scope for sim-tick hunt.