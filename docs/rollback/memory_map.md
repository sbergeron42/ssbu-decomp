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
| `lib::Singleton<app::ItemManager>::instance_` | **`0x71052c3070`** | `find_active_item_from_id @ 0x71015ca930` disassembly: `adrp x8, 0x71052c3000; ldr x9, [x8, #0x70]` | **0xD8 B (216 B)** — root struct only, follow pointers for sub-state | Root struct size confirmed **Round 10** from `FUN_7101344cf0 @ 0x71013494d4..0x710134953c`: `je_aligned_alloc(0x10, 0xd8)` → ctor (`0x71015d2260`) → store to slot. Known fields in `include/app/ItemManager.h` reach only +0x30 (active_end pointer); the remaining ~0xA8 B are unmapped sub-state pointers. Already used correctly in `src/app/fighter_status.cpp`, `fun_batch_e3_001.cpp`, `ItemHelpers.cpp`, `gameplay_functions.cpp`. **Latent bug**: `src/app/FighterManager.cpp:33,391` declares and reads `DAT_71052c2b88` as the ItemManager singleton — this is wrong; that address is the `.begin` pointer of a `std::vector<u32>{0xe3}` inside the item-kind lookup table. The wrong dereference reads bytes past the end of a 4-byte allocation. Should be fixed to `DAT_71052c3070` in a future FighterManager-territory pass. |
| `lib::Singleton<lib::EffectManager>::instance_` | `0x7105333920` | `src/app/fighter_effects.cpp:133`; `FUN_710260b9b0` disassembly @ `0x710260bc2c..0x710260bc34` (`adrp x10, 0x7105333000; ldr x10, [x10, #0x920]`) | Pool record stride **0x300 B** (see EffectManager section below) | Particle pool manager. Double-deref: `*instance_ = EffectManager*` which points to a flat array of 768-byte particle records. Max index is top byte of a u32 id (≤256 entries). |
| `lib::Singleton<app::BattleObjectWorld>::instance_` | **`0x71052b7558`** | `app::stage::get_gravity_position @ 0x71015ce700` disassembly: `adrp x8, 0x71052b7000; ldr x8, [x8, #0x558]`; also `BattleObjectWorld__*_impl` family pass the pointer through .dynsym | `BattleObjectWorld` ≥ 0x60 B | **NEW (Q6 resolved).** Not a per-BattleObject struct despite the name — holds global physics-world overrides (gravity pos/coeff, scale_z, move_speed, reverse/move flags). Small, but per-match mutable. See BattleObjectWorld section below. |
| BattleObjectManager pool-header array | `DAT_71052b7548` (**not** `DAT_71052b7ef8` as in `WORKER-pool-c.md`) | `get_battle_object_from_id @ 0x71003ac560` | Array of 5 `PoolHeader*` (one per category) | The task file listed `DAT_71052b7ef8`; xrefs confirm that address is the BossManager singleton, not BattleObjectManager. Correction below. |
| `lib::Singleton<app::BossManager>::instance_` | `0x71052b7ef8` | `is_boss_stop`, `is_boss_no_dead`, `send_event_on_boss_*` all deref this slot; constructor in `FUN_7101344cf0 @ 0x710134b16c..0x710134b440` | **0x10 B outer wrapper** → `inner` at `+0x8` → **0x238 B inner** → kind-id sub at inner+0x10 (0x30 B) | Root-set confirmed **Round 10** from `FUN_7101344cf0`. Outer wrapper is `je_aligned_alloc(0x10, 0x10)` (just `{ u8[8]; BossManagerInner*; }`). Inner state is `je_aligned_alloc(0x10, 0x238)`, zero-initialized then populated with vtable ptrs and four linked-list head/tail pairs. Existing `include/app/BossManager.h` documented fields to +0x164; real alloc is 0x238 so there is ~0xC8 B of uncharted state past the last named field (field writes observed up to +0x230 during ctor). |
| Game global / RNG + (unknown) | `DAT_71052c25b0` | Dereferenced by `app::sv_math::rand` @ `0x7102275400` and every module's get-random impl | state body = **0xB4 B** (9 streams × 20 B, confirmed — no higher streams reached by dispatcher) | Holds 9 independent XorShift128 streams (per-namespace RNG). **Rollback-critical**. See "RNG" below. |

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

**FULL MAPPING: see `docs/rollback/battle_object_pools.md` (2026-04-11).** The
summary below is kept for quick reference; the dedicated doc has the walker
pseudocode, alloc proofs, and per-field derivations.

`get_battle_object_from_id @ 0x71003ac560` defines the 5-category dispatch
by `id >> 0x1c & 0xf`. Each category's PoolHeader is **embedded at a fixed
offset inside the BattleObjectManager body** (0x40000-byte allocation pointed
to by `*DAT_71052b7548`), NOT a separate allocation:

```
BOM body (0x40000 B, allocated in FUN_71014f3ba0)
 +0xA0  PoolHeader cat 0 (Fighter)
 +0xE0  PoolHeader cat 1 (Weapon)
 +0x120 PoolHeader cat 2 (Enemy/Boss)
 +0x160 PoolHeader cat 3 (Gimmick/Area)
 +0x1A0 PoolHeader cat 4 (Item)
 ...rest is sub-object state
```

Each PoolHeader is **0x40 bytes** (stride between slots). Earlier guess of
0x28 B was wrong — it was reading the BOM **root pointer allocation** (a
separate 0x28-byte struct allocated in FUN_7101344cf0 that holds the single
ptr to the BOM body), not a PoolHeader.

### PoolHeader layout (0x40 B, proven)

```
+0x00  void*  vtable_ptr            (destructor at vt slot +0x50)
+0x08  T*     obj_array_base        (flat array, stride = category stride)
+0x10  u16*   freelist_index_array  (u16[capacity] singly-linked freelist stack)
+0x18  u32    capacity              (max object count, immutable after init)
+0x1c  u16    freelist_head         (index of next free slot; 0xFFFF = exhausted)
+0x1e  s16    live_count            (++ on allocate, -- on free — THE live count)
+0x20..+0x40  mutex + sub-object fields (varies by category)
```

`+0x1e` is `live_count` (incremented in FUN_71003ae080 allocate path,
decremented in FUN_71003aee20 free path) — NOT a decrement-only "free count".
It is the direct count of currently-live objects in the pool.

### Per-category sizes — EXTRACTED from FUN_71014f3ba0 (pool populator)

| Cat | Class (probable) | Stride | Capacity | obj_array alloc | Live @ 1v1 |
|---|---|---|---|---|---|
| 0 | Fighter | 0xF940 (62.25 KiB) | **24**  | 0x175E10 (1.50 MiB) | 2 |
| 1 | Weapon  | 0x3C30 (15.05 KiB) | **400** | 0x5E0B10 (6.15 MiB) | 5–30 |
| 2 | Enemy/Boss| 0x60C0 (24.19 KiB)| **4**   | 0x18310 (99 KiB)    | 0  |
| 3 | Gimmick/Area| 0x300 (768 B)  | **256** | 0x30010 (192 KiB)   | 0–N stage |
| 4 | Item    | 0x2B0 (688 B)      | **64**  | 0xAC10 (43 KiB)     | 0 (no items) |

**Worst-case total BattleObject pool storage ≈ 8.0 MB** (the prior 2.2 MB
estimate was off by ~4× because it undercounted the Weapon pool). Weapons
are the dominant cost: 6.15 MiB of address space for 400 slots × 15 KB each.

Capacities were proven by register-tracing the `je_aligned_alloc` size
arguments in FUN_71014f3ba0's per-pool init loops, cross-checked against the
immediate capacity stores `str w9, [x26, #<pool_hdr_offset>+0x18]`:

- `str w9=0x18, [x26, #0xB8]`  → cat 0 capacity 24
- `str w9=0x190, [x26, #0xF8]` → cat 1 capacity 400
- `str w9=0x4, [x26, #0x138]`  → cat 2 capacity 4
- `str w9=0x100, [x26, #0x178]`→ cat 3 capacity 256
- `str w9=0x40, [x26, #0x1B8]` → cat 4 capacity 64

### Live predicate — walk the freelist

**Do NOT use `obj->id != 0x50000000` as liveness.** The free path does NOT
clear `obj[+0x08]`; freed slots retain their last allocated id value. Walker
MUST walk the freelist stack (head → freelist[head] → … → 0xFFFF) to identify
free slots, then iterate all non-free slots. See `battle_object_pools.md`
for the complete pseudocode and the rejected-alternative analysis.

Not all bytes in a live object are mutable per frame — each BattleObject's
struct contains template data copied from `.arc` resources at spawn and
never written again. A per-module dirty analysis could shrink the savestate
by 5–10×; see `include/app/BattleObjectModuleAccessor.h` for the module
layout and `battle_object_pools.md` for the proposed next steps.

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

**Layout recovered (2026-04-10)** from `FUN_710260b9b0` disassembly (particle-deactivation path called during BattleObject teardown):

```
lVar9 = *lib::Singleton<lib::EffectManager>::instance_;  // EffectManager base
entry  = lVar9 + (effect_id >> 0x18) * 0x300;            // flat array, 768 B stride
if (entry->id == effect_id && entry->flag_0x2d7 == 0) {
    entry->flag_0x2d2 = ...;  // vis bit
    entry->flag_0x2d4 = ...;  // full-mask bit
}
```

- **Record stride: 0x300 = 768 B** per particle.
- **Index encoding**: high byte of a 32-bit effect handle (`id >> 24`), so **max 256 entries**.
- **Validation**: `*(entry + 4) == effect_id` full u32 — stale handles fail this check, so the pool is a classic generational slab.
- **Known fields per entry** (incomplete):
  - `+0x00` (u32) status/type tag (set to `1` at teardown)
  - `+0x04` (u32) full handle id (validation key)
  - `+0x2d2` (u8) visibility flag
  - `+0x2d4` (u8) active-mask-full flag
  - `+0x2d7` (u8) teardown-in-progress flag

**Upper-bound pool size: 256 × 0x300 = 786,432 B ≈ 768 KB worst case.** Realistic mid-match usage is probably 30–80 active particles, i.e. 23–60 KB of *active* records, but the whole 768 KB slab is the addressable region a rollback snapshot must handle if we choose to copy the slab wholesale. Selective snapshotting using the generation key lets us skip dead entries cheaply.

There is a separate, small **fixed-5-entry secondary effect table at `DAT_7105333948`** (stride 0x1b0, hard cap `idx <= 4`, total **2,160 B**) that lives directly in `.data` — no double-deref. Same validation pattern (`*(entry+0) == id`) and similar flag fields. Likely a reserved slot pool for stage/HUD effects; negligible for rollback but include it for completeness.

**Still unknown**: EffectManager body layout at `*DAT_7105333920` *before* the particle array — whether the first field is just the array base or whether the manager has a head struct of its own; whether there are secondary arrays (sound FX, trail meshes) behind adjacent singleton slots `DAT_71053339xx`.

### 6. Per-fighter Lua VM state
`camera_functions.cpp` shows that `lua_state - 8` yields a wrapper struct whose `+0x1A0` field is the owning `BattleObject`. This means **each fighter owns a Lua VM instance** — not a shared global VM. The Lua stack of every active fighter is per-frame mutable and must be snapshotted. Memory size per VM is unknown; Lua 5.x with typical ACMD script depth is usually 8–64 KB per instance. **8 fighters × say 32 KB ≈ 256 KB Lua state per frame**.

This is likely the single biggest surprise cost in an SSBU rollback. Needs follow-up.

### 7. BossManager (`*DAT_71052b7ef8`)

**Size confirmed (2026-04-11, Round 10)** from the constructor in `FUN_7101344cf0 @ 0x710134b16c..0x710134b440`. The manager is a two-level split:

| Layer | Alloc | Size | Purpose |
|---|---|---|---|
| Outer wrapper at `*DAT_71052b7ef8` | `je_aligned_alloc(0x10, 0x10)` | **0x10 B** | `{ vtable* = 0x7104f73b60; BossManagerInner* inner; }` |
| Inner state at `(*DAT_71052b7ef8)->inner` | `je_aligned_alloc(0x10, 0x238)` | **0x238 B** | All per-match boss state: `state`, entity list head/tail, `boss_kind_id`, `boss_target_id`, `no_dead_flag`, `stop_count`, four linked-list heads, finish-event params |
| Kind-id sub at `inner+0x10` | `je_aligned_alloc(0x10, 0x30)` | **0x30 B** | Three pairs of s32 ids `{0x18e,0x16f / 0x188,0x180 / 0x175,0x172}` — static lookup, **not per-frame mutable** |

Walker snapshot policy:
```
outer = *(void**) 0x71052b7ef8
snapshot(outer, 0x10)
inner = outer->inner                        // outer + 0x8
snapshot(inner, 0x238)
// inner+0x10 points to a 0x30 B static lookup — safe to EXCLUDE
// from per-frame snapshot (build-once, never mutated after ctor).
```

**Per-frame bytes to snapshot: 0x10 + 0x238 = 0x248 = 584 B.**

Rollback-relevant only in Classic / Adventure / Stadium modes. In a 1v1 smash match `inner->state == 0` and the entity list is empty, so **the snapshot may be skipped entirely in competitive game modes** — a walker can gate snapshotting on `outer->inner->state != 0 || inner->entity_list_begin != inner->entity_list_end` and save the 584 B per frame. For sim/resim in Eden this is noise either way; the conservative option is to always snapshot since the size is tiny.

Known field coverage: `include/app/BossManager.h` documents BossManagerInner fields up to +0x164. The real alloc is 0x238 and the ctor writes as high as +0x230, so ~0xC8 B of uncharted fields remain past the last named one. For rollback correctness this doesn't matter (we snapshot the full 0x238 B opaque-wise); for future reverse-engineering, those 0xC8 bytes are a follow-up.

### 7b. ItemManager (`*DAT_71052c3070`)

**Size confirmed (2026-04-11, Round 10)** from the constructor in `FUN_7101344cf0 @ 0x71013494c8..0x7101349538`:

```
0x71013494d4  mov w1, #0xd8       ; size = 0xd8
0x71013494d8  mov w0, #0x10       ; align = 0x10
0x71013494dc  bl  je_aligned_alloc
... standard OOM-retry via DAT_7105331f00 vt[+0x30] ...
0x7101349534  bl  0x71015d2260    ; ItemManager ctor
0x7101349538  str x19, [x20, #0x70]   ; *DAT_71052c3070 = mgr
```

**Root struct size: 0xD8 = 216 B** (single flat allocation, align 16).

Walker snapshot policy:
```
mgr = *(void**) 0x71052c3070
snapshot(mgr, 0xD8)
// Then follow the two ItemEntry** pointer pairs at +0x10..+0x18 and
// +0x28..+0x30 into the item pool; each item is a BattleObject in
// category 2 (pool stride 0x60C0 B, see BattleObject Pool Sizes above).
```

**Per-frame bytes to snapshot (root only): 216 B.** The expensive part is the item-pool walk: the `ItemEntry**` lists at +0x10/+0x28 are begin/end pointers into an `std::vector<ItemEntry*>`-style array; each entry resolves to a category-2 BattleObject in the pool already accounted for in §1.

Known field coverage: `include/app/ItemManager.h` documents fields to +0x30 (active list end). 0xD8 − 0x38 = 0xA0 B of uncharted post-list state remains. The ctor helper at `0x71015d2260` probably populates these (additional list heads, allocator context, or lua-state hooks) — follow-up reverse-engineering target.

Before this root alloc, the ctor path (still in `FUN_7101344cf0`) loops over any pre-existing items by iterating the prior ItemManager's active list and calling `item->vt[0x520](item, 0)` on every `w_kind == 0x1a6` entry — this is the remove-item-kind-0x1a6 cleanup from a previous match. Match setup therefore cleans up one item kind *before* reallocating the manager itself; any rollback snapshot taken during that window (match boundary) will see a transient state.

### 8a. Match-runtime entry list (`*DAT_71052c26c0`)

**NEW (2026-04-10).** Found while tracing `FUN_7101344cf0` callers. `FUN_71014b2a40` is the match-setup wrapper; it calls `FUN_7101344cf0()` first (the BattleObject pool init) and then lazy-creates a 0x50-byte root container at `*DAT_71052c26c0` that holds doubly-linked list head/tail pairs for 4 registered "match-setup entries":

- Entry A: 0x330-byte payload (fighter-setup config — Hash40 keys `0x2c844e173b`, `0x33731d4b56`, float defaults, 0x104 B memset region)
- Entry B: 0x210-byte payload (stage/info setup — vtable `&PTR_LAB_7104f72d30`, multiple `&DAT_71014b55XX` static-table refs)
- Entry C: 0x50-byte payload + three 0x30-byte sub-items (pipeline stages, shared_ptr-refcounted)
- Entry D: 0x18-byte payload (minimal flag store)

Total new per-match allocation from this wrapper: ~**1,520 bytes** on top of whatever `FUN_7101344cf0` itself allocates. All per-match mutable; must be snapshotted. Container layout:

```
*DAT_71052c26c0 → u64* (lazy-inited, 8 B slot)
 └ *slot → 0x50-byte container (vtable &PTR_FUN_7105069db0)
    +0x08..+0x48: four {head, tail, head, tail} linked-list pointer pairs
                  (one pair per registered entry category)
```

Rollback verdict: **YES to snapshot**, cost ~1.5 KB. Shallow structure — entries
are task/callback registration slots, not bulk gameplay state.

### 8a.2. Extra match-state singletons (`DAT_71052c2800`, `DAT_71052c2860`, `DAT_71052c2858`)

**NEW (2026-04-10).** Found in `FUN_7101523b60`, a second match-setup wrapper that also calls `FUN_7101344cf0()` first. Three more lazy-allocated singletons:

| Address | Size chain | Purpose (inferred from defaults) | Rollback |
|---|---|---|---|
| `*DAT_71052c2800` | 0x10 wrapper → 0x270 root + sub-allocs (0x40, 0x2e0, 0x80, 0xc8). Total **~1,752 B** | Main match-state root. `+0x100` chains to a 0x2e0-byte sub (Hash40 `0x26e5f4cf48`, many `1.0f` defaults — scoring / timer?). `+0x118` chains to a 0x80 B object with 4 empty linked-list heads (task queues). `+0x258` chains to a 0xc8 B task table with `&PTR_LAB_710506cd48`. | YES, per-match |
| `*DAT_71052c2860` | 0x10 wrapper → 0x48 payload. **~88 B** | Small score/stats struct (`+0x20` = `1.0f` default, rest zero-init) | YES, per-match |
| `*DAT_71052c2858` | 0x08 wrapper → 0x10 payload. **~24 B** | Minimal state slot (u64 ptr + u32 = 0xFFFFFFFF sentinel) | YES, per-match |

Combined cost for this wrapper: **~1,880 B** on top of `FUN_71014b2a40`'s 1,520 B. Together, ~**3.4 KB of shallow "match runtime" state** that a rollback walker must traverse and snapshot before it gets to the 2 MB BattleObject-pool bulk. Trivial cost; mostly useful as a list of root addresses the walker needs.



### 8b. BattleObjectWorld (`*DAT_71052b7558`) — physics-world overrides
**NEW (2026-04-10, Q6 resolved.)** Despite the name suggesting "per-BattleObject" state, this is a singleton holding **per-match global physics overrides** that stage scripts can mutate. Recovered from `app::stage::get_gravity_position @ 0x71015ce700` disassembly and the `BattleObjectWorld__*_impl` .dynsym family.

Struct layout (minimum known, ≥ 0x60 B):

| Offset | Type | Name | Source |
|---|---|---|---|
| `+0x04` | f32 | `gravity_speed_coefficient` | `gravity_speed_coefficient_impl @ 0x7101fca1f0` returns `*(f32*)(world+4)` |
| `+0x08` | f32 | `scale_z` | `scale_z_impl @ 0x7101fca200` returns `*(f32*)(world+8)` if override flag 0 |
| `+0x0c` | u8 | `scale_z_use_default` | `scale_z_impl`: if `world[0xc]` non-zero, return hard-coded `1.0f` |
| `+0x10` | vec4 | `gravity_pos` | `gravity_pos_impl @ 0x7101fca220`, 16-byte load via `ldr q0` |
| `+0x20` | vec4 | `move_speed` | `move_speed_impl @ 0x7101fca2e0` returns `world + 0x20` |
| `+0x5c` | u8 | `gravity_pos_use_default` | `gravity_pos_impl`: if `world[0x5c]` non-zero, falls back to guarded constant `DAT_71052b7610` |

Unobserved offsets (`+0x30..+0x5b`, `+0x5d..`): likely additional override flags and boolean state for `is_gravity_normal_impl`, `is_move_impl`, `move_speed_impl`, `is_disable_reverse_impl` (all at `0x7101fca2b0..0x7101fca2f0`). Conservative upper bound: **≤ 0x100 bytes**.

**Rollback verdict**: small mutable region, **YES to snapshot** (a few hundred bytes at most). Stage scripts mutate these during transforming stages (Kongo Falls water, New Pork City UFO) so skipping the snapshot would desync physics on any dynamic-gravity stage.

**Static default constant**: `DAT_71052b7610` (16 B) is constructed once via `__cxa_guard_acquire(DAT_71052b7608)` and holds a copy of `*PTR_ConstantZero_71052a7a80` — this is read-only reference data, not per-match state, **exclude from snapshot**.

## Persistent / Read-Only Regions (savestate CAN exclude)

Things I confirmed are built once at startup or match-load and then never written:

- **Item-kind classification tables** at `DAT_71052c2960..DAT_71052c2f90` (~1.8 KB, 65 small `std::vector<u32>` lookup tables). Built by `FUN_7100417d10`, registered with a static destructor sentinel. Verdict: **static .data-equivalent, exclude from savestate**.
- **`.arc` resource blobs** (fighter model/animation/hitbox data) loaded at match start, never mutated. Tracked through the resource service, not directly via one of the manager singletons above. Size: tens of MB per match but fully persistent.
- **jemalloc metadata** (chunk headers, arena bookkeeping). Rollback must NOT snapshot jemalloc internals — it would break the allocator on restore. This is a hard constraint: the walker must copy logical object contents, not raw heap pages.

## Open Questions

1. ~~**Where is the actual `app::ItemManager` singleton slot?**~~ **Resolved**: `DAT_71052c3070`, see the correction above. Latent bug in `src/app/FighterManager.cpp:33,391` should be fixed by the next pool assigned FighterManager territory.
2. ~~**Exact BattleObject pool instance counts**~~ **Resolved (2026-04-11)**: all 5 pools sized in `docs/rollback/battle_object_pools.md`. The populator is `FUN_71014f3ba0`, not `FUN_7101344cf0` (the latter only allocates the BOM root ptr slot). Capacities: Fighter 24, Weapon 400, Enemy 4, Gimmick 256, Item 64. Worst-case total ≈ 8.0 MB, of which 6.15 MB is the Weapon pool.
3. ~~**EffectManager layout**~~ **Resolved (2026-04-10)**: record stride 0x300 B, max 256 entries, top-byte generational indexing. Worst case 768 KB. See §5 above. Still unknown: whether adjacent `.data` slots at `DAT_71053339xx` hold parallel pools (sound FX, trail meshes).
4. **Lua VM size per fighter**: the wrapper struct at `lua_state - 8` is a `lib::L2CAgent` (`include/lib/L2CAgent.h`, sizeof=0x38), which holds the `lua_State*` at `+0x08` and the owning `BattleObject*` at `+0x1A0` of an outer struct. The `lua_State` itself (jemalloc-allocated in `lua_newstate`) is opaque; empirical sizing is the only realistic path (allocate a VM, instrument `je_aligned_alloc`, count reachable bytes). Estimate budget remains ~32 KB/fighter × 8 = **~256 KB** pending measurement.
5. **Sound system mutable state**: no `app::SoundManager` or `lib::SoundManager` singleton exists in the .dynsym; every sound accessor is a `SoundModule__*_impl` (see `0x7102081940..0x7102081ce0`) operating on the per-BattleObject `SoundModule` sub-object (module accessor offset `+0x148`). This means **there is no top-level sound state to snapshot separately** — all per-fighter sound state is already inside the BattleObject pool, captured by §1. The only open cost is the *audio engine's* playing-voice table, which lives behind the NintendoSDK `nn::atk` library and is likely impractical to rewind. Recommended default: **do not rewind audio**, advance it monotonically. This is the same trade-off Slippi makes for Melee's DSP state.
6. ~~**`BattleObjectWorld` global state root address**~~ **Resolved (2026-04-10)**: `lib::Singleton<app::BattleObjectWorld>::instance_` = `0x71052b7558`. Struct ≥ 0x60 B, ≤ 0x100 B conservative. See §8 above.
7. ~~**Higher RNG stream offsets in `*DAT_71052c25b0`**~~ **Resolved (2026-04-10)**: full decompile of `app::sv_math::rand @ 0x7102275400` dispatcher confirms exactly **9 streams, highest offset +0xb0**. Minimum snapshot body = 180 B. No further streams reachable from the rand path.
8. ~~**ItemManager / BossManager root struct sizes**~~ **Resolved (2026-04-11, Round 10)** from `FUN_7101344cf0` disassembly. ItemManager = **0xD8 B** (single alloc), BossManager = **0x10 B outer + 0x238 B inner + 0x30 B kind-id sub** (three-level split; kind-id sub is static and can be excluded from per-frame snapshot). See §7 and §7b. The remaining unknown for both is the last ~0xA0/0xC8 B of field contents past the currently-named fields — doesn't block rollback walker design, which snapshots opaquely.

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
| EffectManager particles | per-match | YES | ≤ 768 KB worst case (256 × 0x300, see §5); realistic 20–60 KB active |
| Secondary effect table `DAT_7105333948` | per-match | YES | 2,160 B (5 × 0x1b0) |
| BattleObjectWorld overrides `*0x71052b7558` | per-match | YES | ≤ 0x100 B (see §8) |
| Per-fighter Lua VM × 8 | per-match | **YES (expensive)** | ~256 KB estimated |
| ItemManager body `*0x71052c3070` | per-match | YES | 216 B root (§7b) + item-pool entries already in cat 2 pool |
| BossManager chain `*0x71052b7ef8` | per-match (always allocated, active in boss modes only) | YES | 584 B (0x10 outer + 0x238 inner, see §7). Ignorable in 1v1 smash if gated on `inner->state != 0`. |
| Sound manager | per-match | maybe-opt-out | unknown |
| Item-kind lookup tables `DAT_71052c2960..2f90` | persistent | NO | ~1.8 KB |
| `.arc` resource blobs | persistent (per match load) | NO | tens of MB |
| jemalloc internal metadata | persistent | **NO — never touch** | — |
| Global config (SDK heap setup) | persistent | NO | — |

**Current lower-bound estimate for a per-frame savestate: ~3.3 MB raw worst case** (~2.2 MB BattleObject pools + ~0.77 MB EffectManager particle slab + ~0.26 MB Lua state (estimated) + ~0.04 MB manager bodies + ~0.2 KB RNG + small odds-and-ends). With the EffectManager generational key used to skip dead slots and module-level dirty tracking on BattleObjects, this can plausibly be brought down to the **250–600 KB** range. The biggest remaining unknown is the Lua VM size — if it turns out to be the textbook 32 KB/fighter figure we stay in budget, if it's closer to 100 KB/fighter rollback becomes harder.

## Recommended Next Steps

1. Write a root-walker spike in `tools/` that reads the binary's `.data` symbols for the 6 known roots above and validates each dereferences to a non-null struct in a test dump.
2. Resolve ItemManager and BattleObjectWorld singleton addresses (Open Questions #1 and #6).
3. Decompile `FUN_7101344cf0` (BattleObjectManager init) in chunks via the agent-summarization pattern to extract exact pool counts.
4. Decide between "reachability walk" and "jemalloc tagging hook" as the snapshot primitive. Reachability walk is lower-risk (no runtime hook), higher-cost (pointer-chase per frame). Jemalloc tagging is higher-risk (requires patching the allocator) but gives O(1) per-frame snapshotting of just the tagged allocations.
5. Measure Lua VM size per fighter empirically — this is the single biggest unknown.

## Sources

- `get_battle_object_from_id @ 0x71003ac560` — BattleObject pool strides and category count
- `app::sv_math::rand @ 0x7102275400` — RNG stream layout in `*DAT_71052c25b0` (9 streams confirmed, no more)
- `FUN_7100417d10` — item-kind lookup table static init (confirmed persistent)
- `FUN_710260b9b0` (disassembly, not decompile) — EffectManager singleton @ `0x7105333920`, pool stride `0x300`, top-byte generational index, secondary 5-slot table @ `0x7105333948` stride `0x1b0`
- `app::stage::get_gravity_position @ 0x71015ce700` — `BattleObjectWorld` singleton @ `0x71052b7558`
- `BattleObjectWorld__*_impl` family @ `0x7101fca1f0..0x7101fca2f0` — struct layout (`+0x04..+0x5c`)
- `include/app/FighterManager.h`, `include/app/ItemManager.h`, `src/app/StageManager.cpp`, `include/lib/L2CAgent.h` — singleton / wrapper struct layouts
- `src/docs/game_state.md` — companion document on per-object module state
- `CLAUDE.md § Resource Service Guidelines` — OOM-retry pattern
- Memory `project_jemalloc.md` — jemalloc 5.1.0 Nintendo fork confirmation
