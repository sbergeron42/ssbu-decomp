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
| `lib::Singleton<lib::EffectManager>::instance_` | `0x7105333920` | `src/app/fighter_effects.cpp:133`; `FUN_710260b9b0` disassembly @ `0x710260bc2c..0x710260bc34` (`adrp x10, 0x7105333000; ldr x10, [x10, #0x920]`) | Pool record stride **0x300 B** (see EffectManager section below) | Particle pool manager. Double-deref: `*instance_ = EffectManager*` which points to a flat array of 768-byte particle records. Max index is top byte of a u32 id (≤256 entries). |
| `lib::Singleton<app::BattleObjectWorld>::instance_` | **`0x71052b7558`** | `app::stage::get_gravity_position @ 0x71015ce700` disassembly: `adrp x8, 0x71052b7000; ldr x8, [x8, #0x558]`; also `BattleObjectWorld__*_impl` family pass the pointer through .dynsym | `BattleObjectWorld` ≥ 0x60 B | **NEW (Q6 resolved).** Not a per-BattleObject struct despite the name — holds global physics-world overrides (gravity pos/coeff, scale_z, move_speed, reverse/move flags). Small, but per-match mutable. See BattleObjectWorld section below. |
| BattleObjectManager pool-header array | `DAT_71052b7548` (**not** `DAT_71052b7ef8` as in `WORKER-pool-c.md`) | `get_battle_object_from_id @ 0x71003ac560` | Array of 5 `PoolHeader*` (one per category) | The task file listed `DAT_71052b7ef8`; xrefs confirm that address is the BossManager singleton, not BattleObjectManager. Correction below. |
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

`get_battle_object_from_id @ 0x71003ac560` reveals the per-category object sizes hard-coded in the dispatch switch. Each category has a `PoolHeader` with the layout recovered below. Object lookup is `base + (id_low12 * obj_stride)`.

### PoolHeader layout (≥ 0x20 B)

Recovered from `FUN_71003aeb50` (the "return object to pool" path called when a BattleObject dies). Each of the 5 `PoolHeader*` slots in `DAT_71052b7548[]` points to one of these:

```
+0x00  vtable_ptr            (dispatch to category-specific destroy in slot +0x50)
+0x08  obj_array_base        (pointer to the flat obj[] array, stride = category stride)
+0x10  freelist_index_array  (pointer to a u16[] — free-slot indices, LIFO stack)
+0x18  obj_count (u32)       // THE number we actually need — capacity of the pool
+0x1c  freelist_head (u16)   // top-of-stack index for next free slot
+0x1e  freelist_count (s16)  // decremented on free, so alive_count = obj_count - freelist_count
```

The `+0x18` obj_count field is what determines worst-case pool bytes. Extraction status: **still not directly read** (would require decoding `FUN_7101344cf0`, 31 KB). However, the dispatcher math constants in `FUN_71003aeb50` give us an indirect clue: cases 0 and 2 divide a byte offset by `0xf940`/`0x60c0` via magic-number reciprocal multiplication (respectively `0x41bbb2f80a4553f7` shifted 0xe, `0xa957fab5402a55ff` shifted 0xe, etc.) and the result is masked to 16 bits → `uVar9 & 0xffff`. This proves **obj_count per category < 65536**, which is weak but consistent with our ≤ 256 guesstimates.

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
- **Pool capacity: 128 entries** (corrected 2026-04-11). Previous "max 256" estimate was derived from index encoding only (`id >> 0x18` spans 0..255); the actual allocation inside `FUN_710055d080` is 128 × 0x300 = 0x18000 B backed by a single `memset(base, 0, 0x18000)`.
- **Index encoding**: high byte of a 32-bit effect handle (`id >> 24`). Runtime bounds-check must reject indices ≥ 128 (not yet located, but the array itself only holds 128 slots).
- **Validation**: `*(entry + 4) == effect_id` full u32 — stale handles fail this check, so the pool is a classic generational slab.
- **Known fields per entry** (refined 2026-04-11 from ctor per-record init loop in `FUN_710055d080 @ 0x710055d27c..0x710055d450`):
  - `+0x00`  u32 status/type tag (zero at init, set to `1` at teardown)
  - `+0x04`  u32 full handle id (validation key; zero at init)
  - `+0x10`  u64 (zero at init — likely ptr)
  - `+0x18`  u64 (zero at init)
  - `+0x20`  u64 (zero at init — likely ptr)
  - `+0x38`  u64 pair (stp xzr,xzr) — two ptrs
  - `+0x50`  s32 × 2 = `-1, -1` (two sentinel ids/indices)
  - `+0x58`  u64
  - `+0x60`  u64 pair (stp xzr,xzr)
  - `+0x80..0x9f` vec4 loaded from static default (`&DAT_7104467ca0`)
  - `+0x90..0xaf` vec4 loaded from static default (`&DAT_7104469360`)
  - `+0x190` u64
  - `+0x1d8` s32 = `-1`
  - `+0x1e0, +0x1e8` (u64 ptr, s32 = `-1`) pair — start of 5-slot sub-table
  - `+0x1f0, +0x1f8` same pair
  - `+0x200, +0x208` same pair
  - `+0x210, +0x218` same pair
  - `+0x220, +0x228` same pair (ends at +0x230)
  - `+0x2c4`  u32 (zero at init)
  - `+0x2d2`  u8 visibility flag (set during teardown in `FUN_710260b9b0`)
  - `+0x2d4`  u8 active-mask-full flag
  - `+0x2d7`  u8 teardown-in-progress flag
  - `+0x2e0`  u64 self-ref? Stored as `x20 + 0x2e8` each iteration
  - `+0x2e8..+0x2f0` u64 pair
  - `+0x2f0`  u64 (zero at init)
  - Record ends at `+0x300`.

**Pool footprint: 128 × 0x300 = 0x18000 = 98,304 B ≈ 96 KB.** Realistic mid-match usage is probably 30–80 active particles. Selective snapshotting using the generation key in `+0x04` lets us skip dead entries cheaply. Whole-slab copy is 96 KB, not 768 KB as previously feared.

### EffectManager head struct — Round 10 (2026-04-11)

**Recovered** from the ctor at `FUN_710055d080` (sole non-shutdown writer of `DAT_7105333920`; second writer at `FUN_71022cd350 @ 0x71022d1ef0` not inspected but is likely a re-init or null-out path).

**Singleton indirection is two-level** — previous "single deref" comment was wrong. The ctor allocates an 8-byte heap slot and stores the slot's address into `DAT_7105333920`:

```
710055d140: mov  w0, #0x10          ; align = 16
710055d144: mov  w1, #0x8           ; size  = 8
710055d148: bl   je_aligned_alloc   ; x0 = slot (8 B pointer holder)
... stored at [sp, #0x68] then below: [x8, #0x920] = slot ...
710055d1a0: mov  w0, #0x10          ; align = 16
710055d1a4: mov  x1, #0x19890       ; size  = 104,592 B
710055d1a8: bl   je_aligned_alloc   ; x27 = EffectManager*
...
710055da70: str  x27, [x9]          ; *slot = EffectManager*
710055da74: str  x9,  [x8, #0x920]  ; DAT_7105333920 = &slot
```

Access pattern is therefore `(*(EffectManager**)*DAT_7105333920)`. Existing code that writes `lVar9 = *lib::Singleton::instance_` is reading the 8-byte slot (one deref); a second deref gives the EffectManager body. The particle-teardown code in `FUN_710260b9b0` uses only one deref — **which means `lib::Singleton::instance_` labels the slot allocation itself, and one deref of the slot gives the EffectManager body**. Rollback walker must chase both pointers.

**Body layout — the bookkeeping is a TRAILER, not a header.** The 0x19890-byte allocation is organized as:

| Offset | Size | Region | Contents |
|--------|------|--------|----------|
| `+0x00000` | `0x18000` (96 KB) | **primary particle pool** | 128 × 0x300 records. First `memset(base,0,0x18000)` zeros the whole region; per-record init loop writes default fields described in §5 above. |
| `+0x18000` | `0x013b0` (5040 B) | **secondary record array** | 30 × `0xa8` records. Zeroed by `memset(base+0x18000,0,0x13b0)` then initialized by a second per-record loop at `0x710055d4dc..0x710055d53c` using stride `0xa8` and counter `-0x13b0 += 0xa8` (30 iters). Only one store inside the loop uses a nonzero value (`x14 = 0xffffff00ffffff`, a mask constant) — the rest are `str xzr`, so these are mostly pointer/state slots. **Purpose unknown** — candidates: emitter table, GPU command buffer list, or trail-mesh handles. |
| `+0x193b0` | `0x004e0` (1248 B) | **global head struct** | Scattered non-zero field stores at explicit offsets `0x193b0..0x19880`. Includes at least one f32 default `1.0f` (`orr w8, wzr, #0x3f800000`), several u64 pointer loads from `.rodata` static tables (`adrp 0x7103570000/0x7103571000 + offsets`), and two `q0` (16-byte vector) stores at `+0x19880`. |

**First particle offset: `0x00000`** — particles start at the base of the allocation, not after a header.
**Head struct offset: `0x18000..0x19890`** — head is a trailing region of 0x1890 B total (secondary array + global head).
**Total EffectManager allocation: `0x19890` B = 104,592 B ≈ 102 KB**.

The global head (`0x193b0..0x19890`) is the snapshot-critical region the rollback walker must capture verbatim — it holds phase counters, free-list heads, current-frame emitter caches, etc. (exact fields not yet named, but the 1248-byte range is small enough that whole-range snapshotting is acceptable).

The secondary 30×0xa8 array (`0x18000..0x193b0`) is also per-match mutable and should be snapshotted; its contents are not yet understood but the total 5040 B is cheap.

**Revised EffectManager snapshot cost: ≤ 104,592 B worst case** (whole slab), or ~30 KB with generation-key filtering on dead particles + mandatory copy of the 6 KB trailer.

### Adjacent .data slots (`0x7105333900..0x710533398f`) — Round 10

Enumerated via `tools/xref_bin_scan.py 0x7105333900-0x7105333990 --writers-only`. **None of the adjacent slots are parallel effect pools.** The region is a mixed grab-bag of unrelated singletons:

| Offset | Writer fn | Purpose (inferred) | Rollback relevant? |
|--------|-----------|--------------------|---------------------|
| `+0x900..0x910` | `FUN_7100450e20` (2× `STP Q`) | 32-byte vtable+ptrs blob, one-shot ctor | Unknown — low priority |
| `+0x920` | `FUN_710055d080` | **EffectManager singleton slot** (this §) | **YES** |
| `+0x930..0x940` | `FUN_7103642e50`, `FUN_71036435b0`, `FUN_71036514bc` (repeated `STP X`) | Repeatedly mutated 16-byte state from sound/voice path (6+ writers) — some kind of current-voice or current-BGM handle | Probably audio — see §5 comment on `nn::atk`, skip |
| `+0x948` | `FUN_710055d080` (0x710055f124 + 0x71005618f8), `FUN_71022cd350` (0x71022d16ec) | Allocated `je_aligned_alloc(0x10, 0x1370) = 4976 B` by the SAME outer init function as EffectManager; passed through ctor `0x7103564910`. **Not** a 5-entry 0x1b0-stride table as previously stated in §5 — that note was wrong. Still a separate singleton of some kind, co-initialized alongside EffectManager. | Likely YES (same init fn suggests related subsystem) — ~5 KB. Walker should chase this pointer. |
| `+0x950..0x970` | `FUN_71004407f0` | Separate singleton init (STR W + STP X block) | Unknown |
| `+0x978..0x98c` | `FUN_710356a1e0` | Small 24-byte struct with one `STRB` flag | Unknown, low priority |

**Key correction to §5**: the "fixed-5-entry secondary effect table at `DAT_7105333948`, stride 0x1b0, total 2160 B" claim was wrong. `DAT_7105333948` is actually a pointer slot that holds a heap-allocated `0x1370` B singleton initialized by the same outer ctor function — not an inline 5-entry table. The "5 × 0x1b0 inline" interpretation was likely a misread of a Ghidra pseudocode loop that happened to reference that address as an array base.

### 6. Per-fighter Lua VM state
`camera_functions.cpp` shows that `lua_state - 8` yields a wrapper struct whose `+0x1A0` field is the owning `BattleObject`. This means **each fighter owns a Lua VM instance** — not a shared global VM. The Lua stack of every active fighter is per-frame mutable and must be snapshotted. Memory size per VM is unknown; Lua 5.x with typical ACMD script depth is usually 8–64 KB per instance. **8 fighters × say 32 KB ≈ 256 KB Lua state per frame**.

This is likely the single biggest surprise cost in an SSBU rollback. Needs follow-up.

### 7. BossManager (`*DAT_71052b7ef8`)
Mis-identified in the worker brief. Probably small (boss-only modes). Rollback-relevant only in Stadium/Classic modes.

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

### Match-runtime sub-allocation sizes — Round 10 (2026-04-11)

**Full decompile** of the two match-setup wrappers `FUN_71014b2a40` (owns `DAT_71052c26c0`) and `FUN_7101523b60` (owns `DAT_71052c2800..2860`) produces an exact sub-allocation list. Earlier notes in §8a and §8a.2 estimated totals by inspecting partial traces; these numbers are now verified against every `je_aligned_alloc` call in each ctor.

#### `DAT_71052c26c0` (match-setup entry list) — `FUN_71014b2a40`

| # | Size | Role (inferred) |
|---|------|-----|
| 1 | 0x08 | singleton pointer slot holder |
| 2 | 0x50 | root container (vtable `&PTR_FUN_7105069db0`, 4 head/tail linked-list pairs at `+0x08..0x48`) |
| 3 | 0x20 | Entry A list-node wrapper (shared_ptr control block) |
| 4 | 0x330 | Entry A payload (Hash40 keys `0x2c844e173b`, `0x33731d4b56`, 0x104 B memset region) |
| 5 | 0x20 | Entry B list-node wrapper |
| 6 | 0x210 | Entry B payload (vtable `&PTR_LAB_7104f72d30`, static table refs `DAT_71014b5580/5a60/68e0/6c30/7170`) |
| 7 | 0x20 | Entry C list-node wrapper |
| 8 | 0x50 | Entry C container (vtable `&PTR_LAB_7105069e60`) |
| 9 | 0x30 | Entry C sub-item 1 (vtable `&PTR_LAB_7105069ed0`, ctor `FUN_71014c1840`) |
| 10 | 0x30 | Entry C sub-item 2 (vtable `&PTR_LAB_7105069f08`, ctor `FUN_71014c0c60`) |
| 11 | 0x30 | Entry C sub-item 3 (vtable `&PTR_LAB_7105069f40`, ctor `FUN_71014c1240`) |
| 12 | 0x20 | Entry C intrusive list-node 1 (inserted between head/tail) |
| 13 | 0x20 | Entry C intrusive list-node 2 |
| 14 | 0x20 | Entry C intrusive list-node 3 |
| 15 | 0x20 | Entry D list-node wrapper |
| 16 | 0x18 | Entry D payload (minimal: vtable + u64 + u32) |

**Total `*DAT_71052c26c0` reachable state: 0x8 + 0x50 + (4× Entry wrappers = 0x80) + 0x330 + 0x210 + (0x50 + 3×0x30 + 3×0x20 = 0x170) + 0x18 = 0x7a0 = 1,952 B.**

Revised estimate: **1,952 B** (previous guess 1,520 B missed Entry C's 3 intrusive list-nodes of 0x20 and the 0x8 singleton slot holder). Entry C is a 3-stage task pipeline with shared_ptr refcounting, not a flat 0x50 container.

#### `DAT_71052c2800` (main match-state root) — `FUN_7101523b60`

| # | Size | Role |
|---|------|-----|
| 1 | 0x10 | singleton wrapper (vtable `&PTR_LAB_710506cd68` + inner ptr) |
| 2 | 0x270 | root struct (initialized with many 0's and self-ref `*lVar5 = lVar5`) |
| 3 | 0x40 | Hash40 lookup cache at `root+0xf8` (Hash40 keys `0x1750629f16`, `0x9edd2b0fd` via `FUN_71035407a0`) |
| 4 | 0x2e0 | Sub-object A at `root+0x100` (Hash40 `0x26e5f4cf48`, many `1.0f` defaults at offsets 0x78/0x110/0x150/0x158/0x1b0/0x1b8/0x210/0x214/0x21c/0x260, 0x120-byte memset region at `+0x120`) |
| 5 | 0x80 | Sub-object B at `root+0x118` (vtable `&PTR_LAB_7105180b40`, 4 intrusive linked-list head/sentinel pairs, u32=2 init count) |
| 6 | 0xc8 | Sub-object C at `root+0x258` (vtable `&PTR_LAB_710506cd48`, 3 `FUN_71015260xx` callback slot ptrs, 3 `DAT_71015287xx` data ptrs) |

**Total `*DAT_71052c2800` reachable state: 0x10 + 0x270 + 0x40 + 0x2e0 + 0x80 + 0xc8 = 0x768 = 1,896 B.**

Revised estimate: **1,896 B** (previous guess 1,752 B was close — the extra 144 B comes from the 0x40 Hash40 lookup cache at `+0xf8` which wasn't listed separately before).

#### `DAT_71052c2860` (small score/stats singleton) — `FUN_7101523b60`

| # | Size | Role |
|---|------|-----|
| 1 | 0x10 | wrapper (vtable `&PTR_LAB_710506deb0`) |
| 2 | 0x48 | payload (`+0x20` = f32 `1.0f` default, rest zero) |

**Total: 0x58 = 88 B.** ✓ Matches previous estimate exactly.

#### `DAT_71052c2858` (minimal flag store) — `FUN_7101523b60`

| # | Size | Role |
|---|------|-----|
| 1 | 0x08 | pointer slot holder |
| 2 | 0x10 | payload (u64=0 + u32 sentinel `0xFFFFFFFF`) |

**Total: 0x18 = 24 B.** ✓ Matches previous estimate exactly.

#### `DAT_710593a6a0` (Mii fighter database)

**Not extracted this round.** Writer `FUN_71022b7100` is 90,656 bytes of code — already flagged in `data/ghidra_cache/manual_extraction_needed.md` as low-priority manual-extraction candidate. Earlier rounds (Round 4/6/7) recovered some size information; this round did not add to it. Walker integrator can use prior-round sizes for now.

#### Aggregate match-runtime snapshot (rollback walker target)

| Singleton | Total bytes | `je_aligned_alloc` calls |
|---|---|---|
| `*DAT_71052c26c0` (entry list) | 1,952 B | 16 |
| `*DAT_71052c2800` (match-state root) | 1,896 B | 6 |
| `*DAT_71052c2860` (score/stats) | 88 B | 2 |
| `*DAT_71052c2858` (minimal state) | 24 B | 2 |
| `*DAT_710593a6a0` (Mii DB) | TBD (see above) | TBD |
| **Subtotal (excluding Mii)** | **3,960 B ≈ 3.9 KB** | **26** |

Aggregate match-runtime snapshot ex-BattleObject-pools and ex-Mii: **≈ 3.9 KB**. Negligible against the 2 MB BattleObject bulk; value is in confirming the walker must chase 26 heap pointers from the 4 singleton roots, and the sub-objects are all `je_aligned_alloc`'d (heap-tracked, not inline) so each needs a separate copy.

All 26 sub-allocations use the same OOM-retry pattern via `DAT_7105331f00 + vtable[0x30]`, confirming they're all behind the resource service's standard `alloc_with_oom_retry()` helper (see `CLAUDE.md § Resource Service Guidelines`).

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
2. **Exact BattleObject pool instance counts**: `+0x18` count fields of the 5 PoolHeaders are set somewhere in `FUN_7101344cf0` (BattleObjectManager init, 31 KB). Extracting them gives us exact worst-case pool sizes.
3. ~~**EffectManager layout**~~ **Resolved (2026-04-10)**: record stride 0x300 B, max 256 entries, top-byte generational indexing. Worst case 768 KB. See §5 above. Still unknown: whether adjacent `.data` slots at `DAT_71053339xx` hold parallel pools (sound FX, trail meshes).
4. **Lua VM size per fighter**: the wrapper struct at `lua_state - 8` is a `lib::L2CAgent` (`include/lib/L2CAgent.h`, sizeof=0x38), which holds the `lua_State*` at `+0x08` and the owning `BattleObject*` at `+0x1A0` of an outer struct. The `lua_State` itself (jemalloc-allocated in `lua_newstate`) is opaque; empirical sizing is the only realistic path (allocate a VM, instrument `je_aligned_alloc`, count reachable bytes). Estimate budget remains ~32 KB/fighter × 8 = **~256 KB** pending measurement.
5. **Sound system mutable state**: no `app::SoundManager` or `lib::SoundManager` singleton exists in the .dynsym; every sound accessor is a `SoundModule__*_impl` (see `0x7102081940..0x7102081ce0`) operating on the per-BattleObject `SoundModule` sub-object (module accessor offset `+0x148`). This means **there is no top-level sound state to snapshot separately** — all per-fighter sound state is already inside the BattleObject pool, captured by §1. The only open cost is the *audio engine's* playing-voice table, which lives behind the NintendoSDK `nn::atk` library and is likely impractical to rewind. Recommended default: **do not rewind audio**, advance it monotonically. This is the same trade-off Slippi makes for Melee's DSP state.
6. ~~**`BattleObjectWorld` global state root address**~~ **Resolved (2026-04-10)**: `lib::Singleton<app::BattleObjectWorld>::instance_` = `0x71052b7558`. Struct ≥ 0x60 B, ≤ 0x100 B conservative. See §8 above.
7. ~~**Higher RNG stream offsets in `*DAT_71052c25b0`**~~ **Resolved (2026-04-10)**: full decompile of `app::sv_math::rand @ 0x7102275400` dispatcher confirms exactly **9 streams, highest offset +0xb0**. Minimum snapshot body = 180 B. No further streams reachable from the rand path.

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
| EffectManager particles (primary) | per-match | YES | 96 KB worst case (128 × 0x300, see §5 — corrected Round 10); realistic 20–60 KB active |
| EffectManager secondary array (in same alloc) | per-match | YES | 5,040 B (30 × 0xa8, trailer region) |
| EffectManager global head (in same alloc) | per-match | YES | 1,248 B (trailer region) |
| Secondary singleton `*DAT_7105333948` | per-match | YES | ~4,976 B (`je_aligned_alloc(0x10, 0x1370)` — not an inline table as previously stated) |
| BattleObjectWorld overrides `*0x71052b7558` | per-match | YES | ≤ 0x100 B (see §8) |
| Per-fighter Lua VM × 8 | per-match | **YES (expensive)** | ~256 KB estimated |
| BossManager | per-match (boss modes only) | YES if mode active | unknown |
| Sound manager | per-match | maybe-opt-out | unknown |
| Item-kind lookup tables `DAT_71052c2960..2f90` | persistent | NO | ~1.8 KB |
| `.arc` resource blobs | persistent (per match load) | NO | tens of MB |
| jemalloc internal metadata | persistent | **NO — never touch** | — |
| Global config (SDK heap setup) | persistent | NO | — |

**Current lower-bound estimate for a per-frame savestate: ~2.6 MB raw worst case** (~2.2 MB BattleObject pools + ~102 KB EffectManager primary allocation + ~5 KB secondary singleton `*DAT_7105333948` + ~0.26 MB Lua state (estimated) + ~0.04 MB manager bodies + ~0.2 KB RNG + small odds-and-ends). The EffectManager slab is ~670 KB smaller than the previous "768 KB" figure after Round 10 recovery (actual cap is 128 particles, not 256). With the generational key used to skip dead slots and module-level dirty tracking on BattleObjects, this can plausibly be brought down to the **250–600 KB** range. The biggest remaining unknown is the Lua VM size — if it turns out to be the textbook 32 KB/fighter figure we stay in budget, if it's closer to 100 KB/fighter rollback becomes harder.

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
- `FUN_710260b9b0` (disassembly, not decompile) — EffectManager singleton @ `0x7105333920`, pool stride `0x300`, top-byte generational index
- `FUN_710055d080` (disassembly, not decompile — function too large for Ghidra MCP decomp) — EffectManager ctor. Two `je_aligned_alloc` calls (8 B slot + 0x19890 B body), per-record init loops, trailer layout. Second writer `FUN_71022cd350 @ 0x71022d1ef0` not inspected.
- `tools/xref_bin_scan.py 0x7105333900-0x7105333990 --writers-only` — adjacent .data slot enumeration (Round 10)
- `app::stage::get_gravity_position @ 0x71015ce700` — `BattleObjectWorld` singleton @ `0x71052b7558`
- `BattleObjectWorld__*_impl` family @ `0x7101fca1f0..0x7101fca2f0` — struct layout (`+0x04..+0x5c`)
- `include/app/FighterManager.h`, `include/app/ItemManager.h`, `src/app/StageManager.cpp`, `include/lib/L2CAgent.h` — singleton / wrapper struct layouts
- `src/docs/game_state.md` — companion document on per-object module state
- `CLAUDE.md § Resource Service Guidelines` — OOM-retry pattern
- Memory `project_jemalloc.md` — jemalloc 5.1.0 Nintendo fork confirmation
