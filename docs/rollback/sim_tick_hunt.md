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
