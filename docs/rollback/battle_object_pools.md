# BattleObject pool layout — rollback walker reference

**Status**: static analysis complete as of 2026-04-11. Ready to wire into the
rollback walker; needs dynamic verification of per-match steady-state counts.

## TL;DR

Five object pools, all reached via `*DAT_71052b7548 → BattleObjectManager body`.
All pool storage is embedded in or pointed at from a single 0x40000-byte
BattleObjectManager allocation. Fighters, Weapons, Enemies/Bosses, Gimmicks,
and Items all share one freelist-based allocator design.

- **Worst-case total pool storage: ~8.0 MB** (6.15 MB of that is the Weapon
  pool — the dominant cost).
- **Live-slot identification**: MUST walk the pool's freelist stack. Stale
  `obj->id` values survive freeing and cannot be used as a liveness predicate.
- **Category identity is encoded in the top 4 bits of every BattleObject
  id**, so walking by category is trivial once the PoolHeaders are resolved.

## Pool header struct (0x40 B — embedded at 5 fixed offsets in the BOM body)

| Offset | Type    | Field                 | Derivation |
|--------|---------|-----------------------|------------|
| +0x00  | `void*` | `vtable_ptr`          | `(**(code **)(*plVar10 + 0x50))` in FUN_71003aeb50 — destructor slot at vt+0x50 (slot 10) |
| +0x08  | `void*` | `obj_array_base`      | `*(long*)(lVar2 + 8)` in get_battle_object_from_id case-0, used as `base + idx*stride` |
| +0x10  | `u16*`  | `freelist_index_array`| `*(long*)(lVar2 + 0x10) + uVar1*2` in remove_battle_object_from_pool |
| +0x18  | `u32`   | `capacity`            | bound check `*(uint*)(hdr + 0x18) <= idx → return NULL` in get_battle_object_from_id |
| +0x1C  | `u16`   | `freelist_head`       | `*(ushort*)(hdr + 0x1c)`; sentinel `0xFFFF` = exhausted |
| +0x1E  | `s16`   | `live_count`          | `*(short*)(hdr + 0x1e) += 1` on alloc (FUN_71003ae080), `-= 1` on free (FUN_71003aee20) |
| +0x20..+0x40 | — | mutex + sub-object fields | `std::__1::recursive_mutex::lock()` call following the +0x1c reads in FUN_71003ae080 |

The five PoolHeaders are NOT individually allocated. They are 5 × 0x40-byte
slices of the larger BattleObjectManager body, at offsets **+0xA0, +0xE0,
+0x120, +0x160, +0x1A0** (stride 0x40). The `DAT_71052b7548` global points at a
40-byte BOM root struct, and **`*DAT_71052b7548 + {0xA0, 0xE0, 0x120, 0x160, 0x1A0}`**
gives you the per-category pool header addresses directly.

## BattleObjectManager body access

```c
// From get_battle_object_from_id @ 0x71003ac560 disassembly:
BOM* bom = *DAT_71052b7548;           // single-ptr deref, ~0x40000 bytes total
PoolHeader* cat_n_pool = (PoolHeader*)((u8*)bom + pool_offsets[n]);
// pool_offsets[] = {0xA0, 0xE0, 0x120, 0x160, 0x1A0}

// id encoding (confirmed via get_battle_object_from_id switch):
// bits 31..28 : category (0..4); bit 5.. is the "never allocated" sentinel
// bits 27..16 : slot index within pool (12 bits → cap 4096, but actual caps are much lower)
// bits 15..0  : generation counter + extra
```

## Per-category layout

### Category 0 — Fighter (`app::Fighter`)

- Stride: **0xF940** (63 744 B / 62.25 KiB)
- Capacity: **24**
- obj_array_base allocation: `je_aligned_alloc(0x10, 0x175E10)` — 1.50 MiB
  (24 × 0xF940 + 16 B pad)
- Freelist allocation: `je_aligned_alloc(0x10, 0x30)` — 48 B (24 × u16)
- Per-object class: matches base BattleObject vtable at **0x7104f617a0**
- LUT size evidence: 118 fighter kinds (`DAT_710453b1c0`) in FUN_71003ae080
  case 0 — matches SSBU roster count (89 fighters + echoes and variants).
- 1v1 steady-state count: **2** (player 1, player 2). Pichu + Rosalina-type
  pet-slot fighters can push this to ~4; 8-player mode hits 16+ for some
  character combos.
- Live predicate: walk freelist (see below). Do NOT rely on `obj->id` — stale
  after free (confirmed by reading the destructor path in FUN_71003aeb50).

### Category 1 — Weapon (`app::Weapon`)

- Stride: **0x3C30** (15 408 B / ~15 KiB)
- Capacity: **400**
- obj_array_base allocation: `je_aligned_alloc(0x10, 0x5E0B10)` — 6.15 MiB
  (400 × 0x3C30 + 16 B pad)
- Freelist allocation: `je_aligned_alloc(0x10, 0x320)` — 800 B (400 × u16)
- Per-object class: derived vtable at **0x71051853b8** (destructor is
  FUN_71033a37d0; it cycles through multiple base class vtables, ending at
  0x7104f617a0)
- LUT size evidence: 615 weapon kinds (`DAT_710455e650`) — matches the ~hundreds
  of distinct projectile classes in SSBU (one per attack that spawns a hitbox).
- 1v1 steady-state count: usually **5–30** depending on fighters. Samus charge
  shots, Link arrows, Mario fireballs, etc. — each spawned projectile is one
  Weapon slot. Hazardous-stage variants spike higher.
- Weapons are the **dominant per-frame rollback cost** — 6 MB worst case, but
  typical 30–50 active × 15 KB ≈ 500–750 KB of live bytes per frame.

### Category 2 — Enemy / Boss (probable)

- Stride: **0x60C0** (24 768 B / ~24 KiB)
- Capacity: **4**
- obj_array_base allocation: `je_aligned_alloc(0x10, 0x18310)` — 99 KiB
  (4 × 0x60C0 + 16 B pad)
- Freelist allocation: `je_aligned_alloc(0x10, 0x8)` — 8 B (4 × u16)
- Per-object class: constructed by **FUN_710056ecf0** (per-pool ctor); vtable
  at **0x7104f75bb0** with base vtable 0x7104f617a0.
- LUT size evidence: exactly **5 kinds** hard-coded in FUN_71003ae080 case 2
  (Hash40 values at DAT_710453a868 + 16 * kind). 5 kinds with 4 max
  simultaneous fits **Master Hand + Crazy Hand + 3 other bosses** — World of
  Light, Classic Mode, and Boss Rush all cap at 2–4 simultaneous bosses.
- 1v1 steady-state count: **0** in normal matches. Only non-zero in classic
  mode / WoL boss encounters / Great Cave Offensive etc.
- Rollback impact: negligible in competitive matches; sized appropriately
  for single-player modes.

### Category 3 — Gimmick / Area (probable)

- Stride: **0x300** (768 B)
- Capacity: **256**
- obj_array_base allocation: `je_aligned_alloc(0x10, 0x30010)` — 192 KiB
  (256 × 0x300 + 16 B pad)
- Freelist allocation: `je_aligned_alloc(0x10, 0x200)` — 512 B (256 × u16)
- Per-object class: constructed by **FUN_710313c9f0** (256 ctor calls in
  FUN_71014f3ba0 init loop). Vtable **0x71051774b0**. Body is small (~768 B),
  consistent with stage gimmicks / hurt-box zones / trigger volumes.
- LUT size evidence: only **2 kinds** (2 Hash40 literals in FUN_71003ae080
  case 3). Very narrow kind variety.
- 1v1 steady-state count: highly stage-dependent. Fast-moving stages (Delfino,
  Pokémon Stadium transforming tiles) use many; plain stages (Final Destination)
  may use 0–4.
- The high capacity (256) + low struct size (768 B) profile fits an "area /
  trigger volume" allocator — hitbox/catch-box zones spawn and despawn rapidly
  during attacks.

### Category 4 — Item (probable)

- Stride: **0x2B0** (688 B)
- Capacity: **64**
- obj_array_base allocation: `je_aligned_alloc(0x10, 0xAC10)` — 43 KiB
  (64 × 0x2B0 + 16 B pad)
- Freelist allocation: `je_aligned_alloc(0x10, 0x80)` — 128 B (64 × u16)
- Per-object class: constructed by **FUN_71015a01a0** (64 ctor calls). Vtable
  **0x7105070488**. The ctor itself allocates a 0x2B0-byte **sub-object**
  (same size as the stride!) and stores it at `this[+0x98]` — suggests a
  wrapper pattern with a separately-heap-allocated payload.
- LUT size evidence: **432 kinds** via a linear-scan lookup over a 108-entry
  table with 4 subfields each (DAT_710453e7b8 block, 0x40 B per entry). This
  is the largest dispatch table, consistent with the item / pickup variety
  in Smash Ultimate (Apple, Hammer, Beam Sword, Assist Trophies, Poké Balls,
  Final Smash Balls, etc.).
- 1v1 steady-state count: 0 with items off, up to ~16 with items on high.

## Live-slot identification (rollback walker code)

**Do not use `obj->id` as a liveness predicate.** The free path never clears
`obj[+0x08]`, so freed slots retain syntactically-valid stale IDs. This was
verified by reading `FUN_71003aeb50 (remove_battle_object)` and its delegate
`FUN_71003aee20 (remove_battle_object_from_pool)` — neither touches the
object's own id field; only the pool header freelist + live_count are updated.

The correct approach: walk the freelist stack.

```c
// Per-category walker:
static const size_t POOL_OFFSETS[5] = {0xA0, 0xE0, 0x120, 0x160, 0x1A0};
static const size_t STRIDES[5]      = {0xF940, 0x3C30, 0x60C0, 0x300, 0x2B0};

void walk_battle_object_pool(int cat, void (*visit)(void* obj, size_t bytes)) {
    BOM* bom = *(BOM**)0x71052b7548;
    PoolHeader* hdr = (PoolHeader*)((u8*)bom + POOL_OFFSETS[cat]);

    u32 capacity = hdr->capacity;          // +0x18
    u8* obj_base = hdr->obj_array_base;    // +0x08
    u16* freelist = hdr->freelist_index;   // +0x10

    // Walk freelist stack to mark free slots:
    bool is_free[capacity];
    memset(is_free, 0, sizeof(is_free));
    for (u16 idx = hdr->freelist_head; idx != 0xFFFF; idx = freelist[idx]) {
        is_free[idx] = true;
    }

    // Sanity check: freelist walk vs. live_count (invariant)
    int free_count = 0;
    for (int i = 0; i < capacity; i++) if (is_free[i]) free_count++;
    assert((capacity - free_count) == (int)(i16)hdr->live_count);

    // Visit live slots:
    size_t stride = STRIDES[cat];
    for (u32 i = 0; i < capacity; i++) {
        if (is_free[i]) continue;
        visit(obj_base + i * stride, stride);
    }
}
```

Alternatives considered and rejected:

- **`obj->id != 0x50000000` as liveness flag**: False positives for any slot
  that's been allocated at least once (the id is only set to 0x50000000 by
  the base ctor before first-ever alloc; `remove_battle_object` does not
  reset it).
- **`obj->id >> 28 == cat` as liveness flag**: Same problem — stale ids
  retain their category bits forever.
- **Iterate `[0, live_count)`**: Doesn't work. Freelist is a LIFO stack, so
  live slots are NOT necessarily contiguous at the low end after the first
  free/alloc cycle.
- **Copy the full pool unconditionally**: Correct but wastes 7.6 MB per
  savestate in the empty-weapon-pool case — not acceptable for rollback
  at 60 Hz.

The freelist walk is O(capacity) in the worst case but typically O(free_count).
For 1v1 matches the freelist is long (many free) and the live set is short
(few live), so this cost is bounded by `2 × capacity × 2 bytes ≈ 2.8 KB` of
bitmap allocation per walker pass — trivial.

## Per-object internal walking (the bigger problem)

For each live BattleObject, the walker must NOT copy the full stride blindly
— much of that is const template data copied from `.arc` files at spawn time
and never written again. Per-module dirty analysis is a separate task; see
`docs/rollback/memory_map.md § 5` for the module layout reference.

Minimal state for a determinism-breaking savestate (to be refined):

- `obj->+0x00` vtable  (const, skip)
- `obj->+0x08` id       (mutable only at spawn/destroy)
- `obj->+0x10..0x30`    misc small fields (TBD)
- `obj->kinetic_module` positions, velocities (MUST snapshot)
- `obj->status_module`  current status + timers (MUST snapshot)
- `obj->work_module`    the scratch KV store that ACMD scripts write to
                        (MUST snapshot — the biggest mutable surface per obj)
- `obj->posture_module` scale/facing (MUST snapshot)
- ...many more modules, see include/app/BattleObjectModuleAccessor.h

Out of scope for this document; follow-up task.

## Walker integration notes

The walker's dependency chain is:

1. `rollback_snapshot_begin()` reads `*DAT_71052b7548` — **nullable**, must
   check. BOM is null outside of an active match (allocated by FUN_71014f3ba0
   at match start, freed via counterpart teardown at match end).
2. For each category 0..4:
   - Read the PoolHeader at `BOM + POOL_OFFSETS[cat]`.
   - Walk the freelist to build the live-slot bitmap.
   - Assert `live_count == capacity - free_count` (if it fails, log and
     trust `live_count` — the game is mid-write under our feet).
   - For each live slot, snapshot the object's mutable subset.

## Relationship to the freelist stack

```
PoolHeader.freelist_head (+0x1C)
    ↓
freelist_index_array[head] → next free index
    ↓
freelist_index_array[next] → ...
    ↓
0xFFFF sentinel (initialized in FUN_71014f3ba0 at the tail of each init loop)
```

The init pattern (from the cat 3 init at 0x71014f541c..0x71014f5478) is:

```
freelist[0] = 1; freelist[1] = 2; ... freelist[capacity-2] = capacity-1;
freelist[capacity-1] = 0xFFFF;
head = 0; live_count = 0;
```

So at match start, head = 0 and the entire pool is free. Every allocation
pops the head: `head = freelist[head]`. Every free pushes the old head and
sets the new head to the freed slot. This is a standard LIFO stack and the
walker can rely on it to be a clean singly-linked list unless there's
corruption.

## Reference — sources used to build this document

- `get_battle_object_from_id @ 0x71003ac560` (Ghidra decompile + disasm)
  — 5-category switch; confirms strides and id encoding; confirms live
  predicate uses `*(u32*)(obj + 0x08) == query_id`.
- `FUN_71003ae080 @ 0x71003ae080` (Ghidra decompile) — pool_allocate path;
  proves `+0x1C head`, `+0x1E live_count`, freelist LIFO semantics, 0x50000000
  sentinel, and per-category kind dispatch LUTs.
- `remove_battle_object @ 0x71003aeb50` (Ghidra decompile) — free path;
  proves no clearing of obj->id.
- `remove_battle_object_from_pool @ 0x71003aee20` (Ghidra decompile) —
  inner free path; proves freelist push semantics.
- `FUN_71014f3ba0` (Ghidra decompile + disasm — 73 KB decompile cached at
  `data/ghidra_cache/FUN_71014f3ba0_full.txt`) — the pool populator that
  allocates the BOM body, all 5 obj_arrays, all 5 freelists; contains
  per-pool init loops whose per-object stride constants (0xF940, 0x3C30,
  0x60C0, 0x300, 0x2B0) each appear exactly once and delimit the 5 loops.
- `xref_bin_scan.py` targeting 0x71052b7548 — identified the two writer
  sites in FUN_7101344cf0 (which only allocates the 0x28-byte BOM root
  pointer slot, NOT the body — memory_map.md was wrong about this) and the
  actual body+pool allocation in FUN_71014f3ba0 at store line 1212-1217.
- Per-pool capacity confirmation via register-tracing simulation of
  `mov/movk/add/sub` up to each `je_aligned_alloc` call in FUN_71014f3ba0:
  Fighter 0x175E10, Weapon 0x5E0B10, Enemy 0x18310, Gimmick 0x30010, Item
  0xAC10. Each decomposes cleanly as `capacity * stride + 16` padding.
- Per-pool `str wN, [x26, #hdr_offset + 0x18]` capacity stores, traced to
  match the explicit capacities 24, 400, 4, 256, 64.

## Open questions (for dynamic confirmation or further static work)

1. **Exact class names for categories 2, 3, 4.** Vtables are located but
   Ghidra's symbol table doesn't name them. Candidates:
   - Cat 2 = `app::BossEnemy` or `app::Enemy` (5 kinds, 4 max — matches
     SSBU boss mode).
   - Cat 3 = `app::Gimmick` or `app::Area` (256 small objects — matches
     hitbox/trigger zones).
   - Cat 4 = `app::Item` (64 mid-size + 432 kinds — matches item variety).
   - Resolution path: dump the C++ RTTI type_info strings at vtable - 0x10
     (standard Itanium ABI layout).
2. **Per-match steady-state counts** for each pool. Static bounds are
   known; typical-play measurements need an in-game hook (Eden gdb
   watchpoint on `live_count` fields is the straightforward approach).
3. **Mutable-vs-const byte analysis per module** — required to shrink the
   per-object snapshot from the full ~63 KB fighter stride to something
   tractable. Each module in `include/app/BattleObjectModuleAccessor.h`
   has its own answer; start with WorkModule (the scratch KV store used
   by ACMD scripts — probably the biggest mutable surface).
4. **Does the destructor at vtable[+0x50] reset `obj->id`?** Static reading
   of FUN_71033a37d0 (cat 1 destructor) says no, but other cat destructors
   weren't read. If any cat destructor DOES clear id, a walker could skip
   its freelist walk and use `id != 0x50000000` as its predicate. Low
   priority; the freelist walk is cheap anyway.

## Walker test plan

1. Launch Eden, attach gdb, start 1v1 vs. training-mode CPU on FD.
2. Read `*DAT_71052b7548` → verify non-null.
3. For each cat, read PoolHeader at BOM+offset and dump
   `{obj_array_base, freelist_index_array, capacity, freelist_head, live_count}`.
4. Expected 1v1 steady state:
   - Cat 0 Fighter: `live_count == 2`
   - Cat 1 Weapon: `live_count` fluctuates with attacks; 0 between neutrals
   - Cat 2 Enemy: `live_count == 0`
   - Cat 3 Gimmick: `live_count` stage-dependent; 0 on FD
   - Cat 4 Item: `live_count == 0` with items off
5. Walk each freelist; verify the assertion
   `live_count == capacity - free_count`.
6. If any assertion fails, step 7 and iterate; otherwise walker is correct.
