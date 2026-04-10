# SSBU Memory Map for Rollback Savestating

Status: **initial survey**. Scope: identify the mutable regions that rollback savestate snapshotting must capture, plus the persistent/read-only regions that can be excluded. Based on static analysis of the 13.0.4 NSO, cross-referenced with decompiled singleton accessors in `src/app/`.

## TL;DR — Why This Matters

Slippi snapshots ~few MB per frame of Melee's 24 MB RAM only because Melee's mutable regions are known and contiguous. For SSBU, "everything" is currently the only safe answer, and "everything" is too slow.

**The bad news from this survey: SSBU does NOT use per-subsystem arenas.** All game managers allocate via `je_aligned_alloc` (jemalloc 5.1.0, Nintendo fork) directly into the process-wide heap. There is no `BattleObjectArena` base+size we can read off a header. Each singleton owns a small fixed root object; its real state is reached through pointer chains scattered across the jemalloc heap.

**The good news:** the root singleton set is small (≤ 10 pointers), and each root struct has a bounded, knowable layout. A rollback savestate can be built as a **reachability walk** from those roots, not as a contiguous arena copy.

## Allocator Strategy

| Function | Address | Purpose |
|---|---|---|
| `je_aligned_alloc` | `0x710392dce0` | **Sole runtime allocator** called by every manager init observed so far. jemalloc 5.1.0 (Nintendo fork). Takes `(alignment, size)`. |
| OOM-retry handler | `DAT_7105331f00` (vtable slot +0x30) | Called if first `je_aligned_alloc` returns null. Issues a purge request and retries once. Pattern: `alloc(); if (!p && h) { h->vt[0x30](h, &err, &size); alloc(); }`. See `CLAUDE.md § Resource Service Guidelines → alloc_with_oom_retry`. |
| `malloc` wrapper | `0x7100228110` | Tail-calls `DAT_71052b4450` if non-null (redirects to jemalloc), else libc `malloc`. |
| `free` wrapper | `0x7100228130` | Mirror of above via `DAT_71052b4458`. |

No per-subsystem jemalloc arenas are used (no `je_mallocx` + `MALLOCX_ARENA` symbol surfaces). No `nn::os::SetMemoryHeapSize` call is reachable from the manager inits inspected. This rules out the "snapshot arena N" shortcut.

**Implication for rollback:** snapshotting requires either (a) a reachability walk from singleton roots, or (b) jemalloc hook instrumentation to tag allocations by subsystem, or (c) MMU dirty-page tracking on the whole heap region. Option (a) is the only one that needs no runtime hook and is what this document is scoped to enable.

## Singleton Root Set

These are the entry points a rollback walker traverses. Every address is the `.data`/`.bss` slot holding a `T*`; dereference once to reach the manager struct.

| Singleton | Address | Reached via | Root struct size (min known) | Notes |
|---|---|---|---|---|
| `lib::Singleton<app::FighterManager>::instance_` | `0x71052b84f8` | `FighterManager__*_impl` .dynsym all deref `mgr+0` | `FighterManagerData` ≥ 0xB88 B | See `include/app/FighterManager.h`. Reaches up to 8 `FighterEntry*` at `+0x20..+0x60` plus `finalbg_ptr`, `movie_ptr` sub-objects. |
| `lib::Singleton<app::StageManager>::instance_` | `0x71053299d8` | `StageManager__*_impl`, `src/app/StageManager.cpp:9` | `StageManagerData` ≥ 0x180 B | 3 stage-mode `entries[]` at `+0x110`, embedded `stage_info_vt` sub-object at `+0x128`. |
| `lib::Singleton<app::ItemManager>::instance_` | **`0x71052c3070`** | `find_active_item_from_id @ 0x71015ca930` disassembly: `adrp x8, 0x71052c3000; ldr x9, [x8, #0x70]` | Manages `ItemEntry**` active/pending lists at `+0x10..+0x30` | Already used correctly in `src/app/fighter_status.cpp`, `fun_batch_e3_001.cpp`, `ItemHelpers.cpp`, `gameplay_functions.cpp`. **Latent bug**: `src/app/FighterManager.cpp:33,391` declares and reads `DAT_71052c2b88` as the ItemManager singleton — this is wrong; that address is the `.begin` pointer of a `std::vector<u32>{0xe3}` inside the item-kind lookup table. The wrong dereference reads bytes past the end of a 4-byte allocation. Should be fixed to `DAT_71052c3070` in a future FighterManager-territory pass. |
| `lib::Singleton<lib::EffectManager>::instance_` | `0x7105333920` | `src/app/fighter_effects.cpp:133` | unknown | Particle pool manager. |
| BattleObjectManager pool-header array | `DAT_71052b7548` (**not** `DAT_71052b7ef8` as in `WORKER-pool-c.md`) | `get_battle_object_from_id @ 0x71003ac560` | Array of 5 `PoolHeader*` (one per category) | The task file listed `DAT_71052b7ef8`; xrefs confirm that address is the BossManager singleton, not BattleObjectManager. Correction below. |
| Game global / RNG + (unknown) | `DAT_71052c25b0` | Dereferenced by `app::sv_math::rand` @ `0x7102275400` and every module's get-random impl | struct body ≥ 0xC0 B | Holds ≥ 9 independent XorShift128 streams (per-namespace RNG). **Rollback-critical**. See "RNG" below. |

### Correction: `DAT_71052b7ef8`

The `WORKER-pool-c.md` task brief lists `0x71052b7ef8` as the BattleObjectManager singleton. xrefs disagree:

```
0x71052b7ef8 is read by: is_boss_stop, is_boss_no_dead, is_stoppable_se,
  send_event_on_boss_defeat, send_event_on_boss_keyoff_bgm,
  send_event_on_boss_finish, send_event_on_boss_dead,
  start_boss_finish, ...
```

→ `0x71052b7ef8` is the **BossManager** singleton. The BattleObjectManager lookup root is `DAT_71052b7548`, proven by `get_battle_object_from_id` reading `*DAT_71052b7548[category]` and dispatching on the high 4 bits of the object ID.

### Correction: `DAT_71052c2b88`

`src/app/FighterManager.cpp:33` declares:

```cpp
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052c2b88;  // lib::Singleton<app::ItemManager>::instance_
```

and line 391 reads from `DAT_71052c2b88 + 0xa0`. **Both are wrong.** Decompilation of `FUN_7100417d10` (the static initializer for item-kind classification tables) shows:

```c
puVar5 = (u32 *)je_aligned_alloc(0x10, 4);
...
DAT_71052c2b90 = puVar5 + 1;
DAT_71052c2b98 = DAT_71052c2b90;
*puVar5 = 0xe3;
DAT_71052c2b88 = puVar5;   // .begin of a std::vector<u32> holding one kind id
FUN_71000001c0(&LAB_710068df00, &DAT_71052c2b88, &PTR_LOOP_7104f16000);
```

→ `0x71052c2b88` is the `.begin` field of `vector<u32>{0xe3}`, one of 65 static lookup tables built in `FUN_7100417d10`.

Disassembly of the binary confirms the real singleton is elsewhere. `app::item_manager::find_active_item_from_id @ 0x71015ca930` begins:

```
71015ca93c: adrp x8, 0x71052c3000
71015ca940: ldr  x9, [x8, #0x70]     ; x9 = *0x71052c3070 = ItemManager*
71015ca944: ldp  x8, x9, [x9, #0x28] ; active_begin/active_end
```

→ **real `lib::Singleton<app::ItemManager>::instance_` is at `DAT_71052c3070`.** Four other source files (`fighter_status.cpp`, `fun_batch_e3_001.cpp`, `ItemHelpers.cpp`, `gameplay_functions.cpp`) already use the correct address. Only `src/app/FighterManager.cpp` has the stale wrong value.

The mismatch almost certainly originated because Ghidra's symbol labeling applied `lib::Singleton<app::ItemManager>::instance_` to both the real singleton and the lookup-table vector's .begin pointer (the two addresses are in the same ~0x500-byte region). Anyone who saw the symbol in the decompile and read the address from Ghidra's .data view could have picked the wrong one.

## BattleObject Pool Sizes (the largest per-match region)

`get_battle_object_from_id @ 0x71003ac560` reveals the per-category object sizes hard-coded in the dispatch switch. Each category has a `PoolHeader` with `+0x08: obj_array_base`, `+0x18: obj_count`. Object lookup is `base + (id_low12 * obj_stride)`.

| Cat | Dispatch bits (id >> 28 & 0xF) | Object stride | Dominant usage | Max per-match instances (estimated) |
|---|---|---|---|---|
| 0 | 0x0 | **0xF940 = 62,784 B** (~61 KB) | `BattleObject` (Fighter) | 8 |
| 1 | 0x1 | **0x3C30 = 15,408 B** (~15 KB) | `BattleObject` (Weapon / projectile) | ~64 (guess) |
| 2 | 0x2 | **0x60C0 = 24,768 B** (~24 KB) | `BattleObject` (Item) | ~32 (guess) |
| 3 | 0x3 | 0x300 = 768 B | unknown (possibly Enemy) | ? |
| 4 | 0x4 | 0x2B0 = 688 B | unknown (possibly Gimmick/Area) | ? |

Concrete instance counts were NOT recoverable from the init function inspected (`FUN_7101344cf0`, 31 KB). The `+0x18` count field is set somewhere in that function or its callees; extracting it is a follow-up task.

**Upper-bound worst case for a local 8-player match**, using the strides above and rough counts:
- Fighter pool: 8 × 61 KB = **488 KB**
- Weapon pool: 64 × 15 KB = **960 KB**
- Item pool: 32 × 24 KB = **768 KB**
- Cat 3 + Cat 4: negligible
- **Total per-category storage ≈ 2.2 MB**

Not all of those bytes are *mutable* per frame — each BattleObject's 60-odd-KB struct contains a lot of const template data copied from `.arc` resources at spawn and never written again. A per-module dirty analysis could shrink the savestate by 5–10×.

## Per-Match Mutable State (rollback-critical)

Listed in decreasing order of dynamism.

### 1. BattleObject pools (see above, ~2 MB worst case)
- Accessor: `*DAT_71052b7548[cat_id]` → PoolHeader → `+0x08` base, `+0x18` count.
- Each object is 61–24 KB; most of that is module sub-struct state already catalogued in `src/docs/game_state.md § 5`.
- Strategy: walk module list per object, snapshot only the mutable-bounded subset of each module.

### 2. RNG streams in `*DAT_71052c25b0` (per-namespace XorShift128)
Confirmed by `app::sv_math::rand @ 0x7102275400`:

```c
// struct body at *DAT_71052c25b0 (a GameGlobal* of some kind):
// +0x00  default xorshift state (16 B state + 4 B counter)
// +0x14  stream for Hash40 0x77a08c3fc  (16 + 4)
// +0x28  stream for Hash40 0x66933a7e6
// +0x3C  stream for Hash40 0x5c27c9369
// +0x50  stream for Hash40 0x2095191e5
// +0x64  stream for Hash40 0x5fb9f5aa9
// +0x78  stream for Hash40 0x41f1b251e
// +0x8C  stream for Hash40 0x5f88ec384
// +0xA0  stream for Hash40 0x63b1cee05
```

Each stream is 20 bytes (16 B state + 4 B call counter). **At least 9 streams**; more may exist at higher offsets not yet dispatched to. Minimum RNG payload to snapshot: **~200 bytes**.

**If any single RNG stream is missed from the savestate, rollback will desync on item spawns, critical hits, stage gimmicks, and ambient variation.** The rand dispatcher is hash-keyed specifically so different gameplay systems can't desync each other — which is exactly why every stream matters.

### 3. FighterManager state (`*DAT_71052b84f8`, ≥ 0xB88 B known fields)
Per-match mutable fields extracted so far (see `include/app/FighterManager.h`):
- `entries[8]` at `+0x20` (pointers into Fighter pool; persistent-by-identity but the targets are mutable)
- `entry_count` at `+0xA0`
- `final_actor_entry_id`, `no_discretion_final_beat_count` at `+0xA8..+0xAC`
- `melee_mode`, `hp_mode_global` at `+0xC0..+0xC3`
- `discretion_final_enabled`, `handi_enabled` at `+0xCC..+0xCD`
- `ready_go` at `+0xD2`, `cursor_whole` at `+0xD6`, `result_mode` at `+0xE9`, `ko_camera_enabled` at `+0xEE`
- `one_on_one_ratio` at `+0xF0` (f32)
- `fear_face_entry_id` at `+0x160`
- `finalbg_ptr`, `movie_ptr` at `+0xB78..+0xB80` (sub-objects; walk required)

Of the known fields, `entry_count`, `ready_go`, `ko_camera_enabled`, `final_actor_entry_id`, `no_discretion_final_beat_count`, `fear_face_entry_id` and `one_on_one_ratio` are the frame-mutable ones. `melee_mode`/`hp_mode_global`/`handi_enabled`/`result_mode` are set at match start and then constant.

### 4. StageManager state (`*DAT_71053299d8`, ≥ 0x180 B known fields)
- `entries[3]` at `+0x110` — per-stage-mode sub-object pointers
- `stage_info_vt` at `+0x128` — embedded stage sub-object with its own vtable (dynamic stage data lives behind this pointer chain)
- `mode` at `+0x17C` (s32; `-1` = all-modes, `0..2` = current mode)

Dynamic stage data (transforming platforms, hazard state) is reached through the `entries[mode]` pointer → sub-object vtable. Scope of this traversal is not yet mapped.

### 5. EffectManager particle pool (`*DAT_7105333920`)
Unknown layout. Likely significant: particle pools in 60 fps fighting games run hundreds of instances per frame. Needs its own investigation.

### 6. Per-fighter Lua VM state
`camera_functions.cpp` shows that `lua_state - 8` yields a wrapper struct whose `+0x1A0` field is the owning `BattleObject`. This means **each fighter owns a Lua VM instance** — not a shared global VM. The Lua stack of every active fighter is per-frame mutable and must be snapshotted. Memory size per VM is unknown; Lua 5.x with typical ACMD script depth is usually 8–64 KB per instance. **8 fighters × say 32 KB ≈ 256 KB Lua state per frame**.

This is likely the single biggest surprise cost in an SSBU rollback. Needs follow-up.

### 7. BossManager (`*DAT_71052b7ef8`)
Mis-identified in the worker brief. Probably small (boss-only modes). Rollback-relevant only in Stadium/Classic modes.

## Persistent / Read-Only Regions (savestate CAN exclude)

Things I confirmed are built once at startup or match-load and then never written:

- **Item-kind classification tables** at `DAT_71052c2960..DAT_71052c2f90` (~1.8 KB, 65 small `std::vector<u32>` lookup tables). Built by `FUN_7100417d10`, registered with a static destructor sentinel. Verdict: **static .data-equivalent, exclude from savestate**.
- **`.arc` resource blobs** (fighter model/animation/hitbox data) loaded at match start, never mutated. Tracked through the resource service, not directly via one of the manager singletons above. Size: tens of MB per match but fully persistent.
- **jemalloc metadata** (chunk headers, arena bookkeeping). Rollback must NOT snapshot jemalloc internals — it would break the allocator on restore. This is a hard constraint: the walker must copy logical object contents, not raw heap pages.

## Open Questions

1. ~~**Where is the actual `app::ItemManager` singleton slot?**~~ **Resolved**: `DAT_71052c3070`, see the correction above. Latent bug in `src/app/FighterManager.cpp:33,391` should be fixed by the next pool assigned FighterManager territory.
2. **Exact BattleObject pool instance counts**: `+0x18` count fields of the 5 PoolHeaders are set somewhere in `FUN_7101344cf0` (BattleObjectManager init, 31 KB). Extracting them gives us exact worst-case pool sizes.
3. **EffectManager layout**: no decomp yet. Particle pool count and per-particle size are unknowns.
4. **Lua VM size per fighter**: need to trace `FighterEntry → lua_state` allocation. Candidate starting point: `lua_state - 8 → +0x1A0` reverse lookup (`camera_functions.cpp:266`).
5. **Sound system mutable state**: not investigated. Some rollback implementations explicitly *do not* rewind audio, trading a minor audio blip for a huge state reduction. Worth documenting as an opt-out.
6. **Physics / kinetic world state**: mostly per-BattleObject via `KineticModule` (already catalogued in `src/docs/game_state.md`). But `BattleObjectWorld` global state (`gravity_pos_impl` et al. at `0x7101fca220..`) also exists and needs a root address. Not found yet.
7. **Higher RNG stream offsets in `*DAT_71052c25b0`**: only 9 Hash40 namespaces were proven by the `rand` dispatcher; the struct body may contain more streams beyond `+0xC0`.

## Persistent vs Per-Match Summary

| Region | Type | Snapshot? | Bytes (estimate) |
|---|---|---|---|
| Fighter pool (cat 0) | per-match | **YES** | ≤ 488 KB (8 × 61 KB) |
| Weapon pool (cat 1) | per-match | **YES** | ≤ ~960 KB (64 × 15 KB est.) |
| Item pool (cat 2) | per-match | **YES** | ≤ ~768 KB (32 × 24 KB est.) |
| Cat 3 / Cat 4 pools | per-match | YES | ≤ ~few KB |
| FighterManager body | per-match | YES | ~3 KB |
| StageManager body | per-match | YES | unknown, likely tens of KB |
| StageManager dynamic stage entries[3] | per-match | YES | unknown, per-stage |
| RNG streams in `*DAT_71052c25b0` | per-match | **YES (critical)** | ~200 B (9 streams × 20 B) |
| EffectManager particles | per-match | YES | **unknown — investigate** |
| Per-fighter Lua VM × 8 | per-match | **YES (expensive)** | ~256 KB estimated |
| BossManager | per-match (boss modes only) | YES if mode active | unknown |
| Sound manager | per-match | maybe-opt-out | unknown |
| Item-kind lookup tables `DAT_71052c2960..2f90` | persistent | NO | ~1.8 KB |
| `.arc` resource blobs | persistent (per match load) | NO | tens of MB |
| jemalloc internal metadata | persistent | **NO — never touch** | — |
| Global config (SDK heap setup) | persistent | NO | — |

**Current lower-bound estimate for a per-frame savestate: ~2.5 MB raw** (~2 MB BattleObject pools + ~256 KB Lua state + ~40 KB manager bodies + ~0.2 KB RNG + effect/sound unknowns). With module-level dirty tracking this can plausibly be brought down to the **200–500 KB** range, which is where rollback starts being viable at 60 fps.

## Recommended Next Steps

1. Write a root-walker spike in `tools/` that reads the binary's `.data` symbols for the 6 known roots above and validates each dereferences to a non-null struct in a test dump.
2. Resolve ItemManager and BattleObjectWorld singleton addresses (Open Questions #1 and #6).
3. Decompile `FUN_7101344cf0` (BattleObjectManager init) in chunks via the agent-summarization pattern to extract exact pool counts.
4. Decide between "reachability walk" and "jemalloc tagging hook" as the snapshot primitive. Reachability walk is lower-risk (no runtime hook), higher-cost (pointer-chase per frame). Jemalloc tagging is higher-risk (requires patching the allocator) but gives O(1) per-frame snapshotting of just the tagged allocations.
5. Measure Lua VM size per fighter empirically — this is the single biggest unknown.

## Sources

- `get_battle_object_from_id @ 0x71003ac560` — BattleObject pool strides and category count
- `app::sv_math::rand @ 0x7102275400` — RNG stream layout in `*DAT_71052c25b0`
- `FUN_7100417d10` — item-kind lookup table static init (confirmed persistent)
- `include/app/FighterManager.h`, `include/app/ItemManager.h`, `src/app/StageManager.cpp` — singleton struct layouts
- `src/docs/game_state.md` — companion document on per-object module state
- `CLAUDE.md § Resource Service Guidelines` — OOM-retry pattern
- Memory `project_jemalloc.md` — jemalloc 5.1.0 Nintendo fork confirmation
