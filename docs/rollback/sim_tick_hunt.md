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