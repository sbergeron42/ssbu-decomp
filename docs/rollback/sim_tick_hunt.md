# Sim tick hunt — pool notes

Bottom-up hunt for the "advance one fighter frame" dispatcher. Every pool writes a
labelled section; do not overwrite another pool's section.

Shared prerequisites (already proven by earlier work):
- `main_loop` @ `0x7103747270` is the **presentation frame loop**, not the sim dispatcher.
  See `docs/rollback/main_loop.md`.
- `Singleton<app::FighterManager>::instance_` @ `0x71052b84f8`
- `Singleton<app::BattleObjectWorld>::instance_` @ `0x71052b7558` (pool-c)
- `BattleObjectManager` pool-header array base @ `DAT_71052b7548` (pool-c)
- Every direct reader of the `FighterManager` singleton pulls single scalar fields
  (hp, entry_id, pos, mode flags), never iterates the 8-entry array as a per-frame
  update loop.

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

### Verdict
PROGRESS — the FighterManager-vtable angle is disproven outright, but the pivot
through `FighterEntry +0xf0` found a concrete **FighterStatus vtable** at
`0x7104f7f2e8..+0x80` whose `FUN_7100614630` slot is a per-fighter, per-status
handler that fully reveals the Fighter's cached module-pointer layout. That
layout is strong evidence for pool-B/C's "sim driver iterates BattleObjects,
not the FighterManager entry array" prediction. Continuing toward the caller
of the status-exec slot next session.
