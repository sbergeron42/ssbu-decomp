# Gameplay RNG — Rollback Capture / Restore

Primary deliverable for the rollback netcode effort. This document describes where the
deterministic gameplay RNG lives in SSBU 13.0.4, how it advances, and exactly which
bytes a rollback fork of Eden must capture and restore each frame.

## TL;DR for the Eden fork

- The "sync" gameplay RNG is **9 independent xorshift128 streams** (Marsaglia 2003),
  selected by a `phx::Hash40` channel argument.
- The 9 streams live contiguously in a 180-byte (0xb4) buffer owned by a singleton
  reachable at `[[0x71052c25b0]]` (two pointer dereferences from a fixed BSS slot).
- **Snapshot / restore exactly those 180 bytes each frame.** That is sufficient to
  re-simulate deterministically, regardless of which fighter/item/effect asks for a roll.
- Per-call, each stream writes all 4 state words + 1 u32 counter (20 bytes), so there is
  no way to do a smaller per-channel delta without parsing calls.
- There is a **separate "no-sync" RNG** (date/clock-seeded). Do not snapshot it; it is
  intentionally allowed to diverge across rollbacks and is only used for cosmetic/menu
  things. Libc `srand`/`rand` is also seeded from the no-sync path.

## 1. The RNG functions

### `app::sv_math::rand(phx::Hash40 channel, int max) -> u32`
- Address: `0x7102275320`
- Mangled: `_ZN3app7sv_math4randEN3phx6Hash40Ei` (`0x7104239f14`)
- Returns `max > 0 ? (w % max) : w` where `w` is the full xorshift output.
- Exported to Lua scripts via a binding wrapper at `FUN_710213a360` — that is the only
  direct native caller (plus the dynsym entry). In practice the compiler **aggressively
  inlined this function at every C++ call site** because the `Hash40` argument is a
  compile-time constant, so the Ghidra xref list on this address dramatically undercounts
  real callers. See §4.

### `app::sv_math::randf(phx::Hash40 channel, float scale) -> float`
- Address: `0x71022756c0`
- Mangled: `_ZN3app7sv_math5randfEN3phx6Hash40Ef` (`0x7104239f38`)
- Returns `(float)w * scale * DAT_7104472710`. The constant at `0x7104472710` is
  `1.0f / 2^32 ≈ 2.3283064e-10`, yielding a uniform `[0, scale)`.
- Same 9-way channel dispatch, same inlining, same Lua-binding wrapper
  (`FUN_710213a9f4`).

### Namespaced convenience wrappers (inlined callers)
Thin forwarders that bind a fixed channel and add range / percent semantics. Each
corresponds to a single `Xorshift128` slot in the singleton.

| Function | Address | Channel offset | Channel hash |
|---|---|---|---|
| `app::random::get_float()` | `0x71015cf234` | `+0x78` | `0x41f1b251e` |
| `app::random::range_int(int,int)` | `0x71015cf294` | `+0x78` | `0x41f1b251e` |
| `app::random::range_float(float,float)` | `0x71015cf2f4` | `+0x78` | `0x41f1b251e` |
| `app::random::is_percent(float)` | `0x71015cf354` | `+0x78` | `0x41f1b251e` |
| `app::ai_random::get_float()` | `0x7100376774` | `+0x50` | `0x2095191e5` |
| `app::ai_random::range_int(int,int)` | `0x71003766d4` | `+0x50` | `0x2095191e5` |
| `app::ai_random::range_float(float,float)` | `0x71003767d4` | `+0x50` | `0x2095191e5` |
| `app::ai_random::is_percent(float)` | `0x7100376834` | `+0x50` | `0x2095191e5` |

These are the two "named" channels we can identify by symbol. The other seven channel
offsets (default / `+0x14` / `+0x28` / `+0x3c` / `+0x64` / `+0x8c` / `+0xa0`) are only
reachable via `sv_math::rand` with a literal Hash40 or via inlined copies.

## 2. The RNG state

### Algorithm — xorshift128 (Marsaglia 2003)

Every decompiled call site implements the same advance (paraphrased from
`sv_math::rand`):

```c
u32 w_old = ch->w;
ch->call_count += 1;
u32 t = ch->x ^ (ch->x << 11);
ch->x = ch->y;
t ^= (t >> 8) ^ w_old ^ (w_old >> 19);
ch->y = ch->z;
ch->z = w_old;
ch->w = t;
// return value is `t` (then %max for rand, *scale for randf)
```

This is the classic `(11, 8, 19)` Marsaglia xorshift128. Note the reshuffle:
`x <- y, y <- z, z <- w_old, w <- t`. A bare `Xorshift128*` advance helper exists at
`FUN_7100138620` (identical arithmetic, takes a raw `uint*`), used by a few call sites
that do not care about the channel indirection; this is what MEMORY.md refers to as
`xorshift128_7100138620`.

### Channel struct `app::Xorshift128` — 20 bytes

```
+0x00  u32 x            // state[0]
+0x04  u32 y            // state[1]
+0x08  u32 z            // state[2]
+0x0c  u32 w            // state[3] (return value lives here)
+0x10  u32 call_count   // monotonically incremented every advance
```

Header: `include/app/Randomizer.h`.

The `call_count` field is updated on every roll but is never read by the RNG itself. It
exists for telemetry / replay validation. It **must** be captured alongside the state
otherwise replay diagnostics will diverge even when the state matches.

### Channel array layout — 180 bytes (0xb4)

`sv_math::rand` dispatches on a `phx::Hash40` to a fixed channel offset. The mapping
is exhaustive — there is no hash-table lookup, just a binary-search tree of compile-time
constants. Any hash that does not match any case uses the default slot at offset 0.

| Channel index | Offset | Hash40 | Known use |
|---|---|---|---|
| 0 | `+0x00` | *(default / unmatched)* | fallback; e.g. `FighterSpecializer_Brave::lot_critical` and one of the `switch_*_motion` SE randomizers inlined here |
| 1 | `+0x14` | `0x77a08c3fc` | attack-SE swap (seen in `FUN_7100826750`), Hero crit |
| 2 | `+0x28` | `0x66933a7e6` | (unnamed) |
| 3 | `+0x3c` | `0x5c27c9369` | (unnamed) |
| 4 | `+0x50` | `0x2095191e5` | `app::ai_random` namespace |
| 5 | `+0x64` | `0x5fb9f5aa9` | (unnamed) |
| 6 | `+0x78` | `0x41f1b251e` | `app::random` namespace — **main gameplay RNG** |
| 7 | `+0x8c` | `0x5f88ec384` | (unnamed) |
| 8 | `+0xa0` | `0x63b1cee05` | (unnamed) |

Total: 9 × 0x14 = **0xb4 bytes**. Header: `app::RandomizerChannels` in
`include/app/Randomizer.h`.

Note that the unnamed channels likely have meaningful community names once Lua scripts
are inspected — a grep through the Lua script dump for the literal hash values (e.g.
`0x77a08c3fc`) will reveal them. This is a follow-up task; for rollback it does not
matter which channel is which, only that all 180 bytes are captured together.

### Global accessor — `[[0x71052c25b0]]`

Every decompiled reader uses the same two-deref pattern:

```c
// in rand / namespaced wrappers / inlined copies:
long state_base = *(long *)*DAT_71052c25b0;
// then access (state_base + channel_offset + field)
```

In AArch64 asm (from `sv_math::rand`):

```
adrp x8, 0x71052c2000
ldr  x0, [x8, #0x5b0]      ; x0 = Randomizer*     (singleton ptr)
ldr  x1, [x0]              ; x1 = channels base   (= &RandomizerChannels)
; x1 + offset is the selected Xorshift128
```

So the sequence of dereferences for Eden is:

1. Read `u64 singleton = *(u64*)0x71052c25b0;` — stable across frames after init.
2. Read `u64 channels = *(u64*)singleton;` — stable across frames after the state
   buffer is allocated (the `Randomizer` constructor heap-allocates the channel array
   during boot and never reallocates; see §3).
3. Snapshot `memcpy(snapshot, (void*)channels, 0xb4);` — this is the rollback payload.
4. Restore: `memcpy((void*)channels, snapshot, 0xb4);`

**Important:** `singleton` and `channels` are themselves stable pointers after game
boot. Eden can cache them once when the match begins; they are NOT part of the
per-frame snapshot.

## 3. Seed init

The `Randomizer` singleton is initialized deep inside a large boot routine
(`FUN_7101344cf0`, ~32 KB). The relevant sequence starts at `0x710134545c` and performs
two things: seeding the sync RNG and calling the no-sync seed helper.

### Sync seed derivation (`0x71013454b0`..`0x7101345534`)

```
ldr  w19, [x21, #0xf8]      ; w19 = u32 seed from parent object
str  w19, [x21, #0x50]      ; copy seed to a neighbouring field (for later read)
adrp x8,  0x71052c2000
ldr  x20, [x8, #0x5b0]      ; x20 = Randomizer* singleton
ldr  x8,  [x20]             ; x8  = channels buffer base
str  w19, [x8, #0x18]       ; stash seed at channels+0x18 (inside slot 1)
bl   0x710366d110           ; setup_no_sync_seed_from_date(seed)
ldr  x9,  [x20]             ; reload buffer base (BL may have clobbered)
ldp  x8,  x9, [x9]          ; x8 = begin, x9 = end   (vector header at +0x00 / +0x08)
cmp  x9, x8
b.eq skip_loop

; derive 4 state words from the single u32 seed using the MT19937 init_genrand LCG
eor  w10, w19, w19, LSR #30
mov  w13, #0x6c078965       ; MT19937 multiplier
mul  w10, w10, w13          ; state[0] = (seed ^ (seed>>30)) * 0x6c078965
eor  w11, w10, w10, LSR #30
madd w11, w11, w13, w12     ; state[1] = (state[0] ^ state[0]>>30) * 0x6c078965 + 1
...
madd w12, ..., w13, #2      ; state[2] = ... + 2
madd w13, ..., w13, #3      ; state[3] = ... + 3

loop:                       ; 0x710134551c
  stp  w13, wzr, [x8, #0xc] ; write state[3] and zero call_count
  stp  w10, w11, [x8]       ; write state[0..1]
  str  w12, [x8, #0x8]      ; write state[2]
  add  x8, x8, #0x14        ; advance to next 20-byte channel
  cmp  x9, x8
  b.ne loop
```

Key observations:

- The **single u32 seed** comes from `*(u32*)(parent + 0xf8)` on an object already
  resident in `x21`. That parent is set up earlier in the same boot routine and is
  almost certainly the global "match params" / `GameSetupData` struct that also holds
  stage id, rule set, and stock count. Identifying `x21` precisely is future work, but
  any rollback fork can simply capture the sync RNG state *after* boot completes — there
  is no need to re-run the seed derivation.
- Every one of the 9 channels is seeded with the **same** `(state[0..3], 0)` tuple
  derived from the single seed. So at frame 0 of a match, all 9 xorshift streams are
  identical. They diverge purely by different call frequencies across the match. This
  is useful for sanity-checking a rollback capture: at `call_count == 0` for all
  channels, the state must be identical across all 9 slots.
- The seed-derivation constants (`0x6c078965`, `x ^ (x>>30)`) are Matsumoto & Nishimura's
  MT19937 `init_genrand` recurrence, repurposed here to seed xorshift instead of the
  Mersenne Twister state vector.
- The loop header load `ldp x8, x9, [x9]` treats the first 16 bytes of the buffer as
  `(begin, end)` pointers. This strongly suggests the buffer is actually an inline
  `std::vector<Xorshift128>` where the vector header overlaps slot 0's x/y at init
  time; once the seed loop writes through those addresses, the header is clobbered and
  the data reader interpretation takes over. We have not fully nailed down the vector
  vs. flat array distinction because the inline access pattern in readers is what
  matters for rollback. The 180-byte snapshot is what you want regardless.

### `setup_no_sync_seed_from_date` (`0x710366d110`)

This is the **no-sync** RNG initializer. Do not confuse it with the gameplay RNG. It:

1. Derives 4 u32s at `DAT_71052381b0..bc` from the caller-provided seed using the same
   MT19937 LCG chain.
2. `je_aligned_alloc(0x10, 0x30)` + constructs an `nn::time::PosixTime` helper (vtable
   at `PTR_DAT_710522ea38`).
3. `nn::time::StandardUserSystemClock::GetCurrentTime` → millisecond-of-day via
   `ms + s*1000 + m*60000 + h*3600000`.
4. Derives another 4 u32s at `DAT_71052381c0..cc` from that millisecond value.
5. Advances the first xorshift once, then calls `srand(result)` to seed the NX libc
   random as well.

So the no-sync RNG has its own 32-byte state (`DAT_71052381b0..cf`, two back-to-back
xorshift128 blocks) and is re-seeded from wall-clock time. This is where the
Lua-scriptable `Randomizer.setup_no_sync_seed_from_date()` / `no_sync_get()` /
`no_sync_getf()` metatable methods land (registered in `FUN_7103370ce0`). Cosmetic
effects, menu animations, and similar use this path so that rollback does not fight
wall-clock re-rolls.

**For the rollback fork: ignore this path entirely.** It is intentionally not part of
the deterministic state.

## 4. Call sites

The direct xref list on `sv_math::rand` has exactly two entries — the Lua binding
wrapper `FUN_710213a360` and the `.dynsym` export entry point. This is misleading.

**Why:** NX Clang inlines the entire `sv_math::rand` body (including the 9-way Hash40
dispatch) at every native C++ call site because the channel argument is almost always
a compile-time `Hash40("foo_bar"_h)` literal. The inliner constant-folds the binary
search and drops the dispatch, leaving only the xorshift arithmetic for the chosen
channel. As a result, every native caller looks like a freestanding copy of the
xorshift advance against the same singleton pointer.

The correct way to enumerate real call sites is to **follow xrefs to the singleton
global `0x71052c25b0`** and filter for the reader pattern
`ldr xN, [x?, #0x5b0]; ldr xM, [xN]; ... xorshift arithmetic`. Ghidra already reports
over 200 such xrefs; the pool-a cache (`data/ghidra_cache/pool-a.txt`) has the raw
list. A pragmatic categorization of the ones we sampled:

### Gameplay (sync-critical — must be under rollback)

| Address | Function | What it rolls |
|---|---|---|
| `0x7100855d24` | `app::FighterSpecializer_Brave::lot_critical` | Hero crit proc (channel `+0x14`) |
| `0x7100826750` | `FUN_7100826750` (fighter attack) | 3-way attack SE randomizer (channel `+0x14`) |
| `0x71003766d4` | `app::ai_random::range_int` | CPU behavior rolls (channel `+0x50`) |
| `0x71003767d4` | `app::ai_random::range_float` | CPU behavior rolls (channel `+0x50`) |
| `0x7100376774` | `app::ai_random::get_float` | CPU behavior rolls (channel `+0x50`) |
| `0x7100376834` | `app::ai_random::is_percent` | CPU behavior rolls (channel `+0x50`) |
| `0x71015cf294` | `app::random::range_int` | general gameplay rolls (channel `+0x78`) |
| `0x71015cf2f4` | `app::random::range_float` | general gameplay rolls (channel `+0x78`) |
| `0x71015cf234` | `app::random::get_float` | general gameplay rolls (channel `+0x78`) |
| `0x71015cf354` | `app::random::is_percent` | general gameplay rolls (channel `+0x78`) |
| `0x7100e8aef0` | `final_rand_create_item` | Final Smash item spawn roll |
| `0x710164b874` | `check_item_provide` | item spawn eligibility roll |
| `0x710082f150` | `FUN_710082f150` | hit-related roll (still unnamed) |
| `0x71008584a0` | `FUN_71008584a0` | still unnamed |
| `0x7100a4c488` | `app::final_end_exec` | Final Smash cleanup |
| `0x7100a48aa8` | `app::final_ready_exec` | Final Smash startup |
| `0x7100a49e4c` | `app::final_ready_exit` | Final Smash exit |
| `0x7100957640` | `app::final_decide_target_dir` | Final Smash targeting |
| `0x7100957e88` | `app::final_finish_attack_dir` | Final Smash direction |
| `0x7100a65c8c` | `app::final_ready_exec` | Final Smash startup (duplicate entry from different reader) |
| `0x7100a6712c` | `app::final_ready_exit` |  |
| `0x7101326260..0x71013265bd` | `FUN_7101326260` (several reads) | item / AT pickup |
| `0x71022817a4` | `get_dead_up_camera_hit_first_rand_rot_z` | camera shake — gameplay-visible, **must** be sync |
| `0x7102281190` | `get_dead_up_camera_hit_first_rand_offset_x` | camera shake — **must** be sync |
| `0x7101008340..0x7101087df0` | several stage-hazard fns | stage event rolls |
| `0x71002ec1a0`, `0x71002eed6c`, `0x71002ef000`, `0x71002f0[0-f]xx`, `0x71002f2a00`, `0x71002f[4-7]xxx` | big cluster in `71002e.–71002f.` — one function (`FUN_71002f2a00`) reads the singleton **20+ times** meaning it advances multiple channels per call | believed to be the main BGM / match flow module (next to `get_bgm_kind`), will need per-function triage to confirm |

(The list above is representative, not exhaustive. The full Ghidra xref dump lives in
`data/ghidra_cache/pool-a.txt`; there are on the order of 200 distinct reader sites
across the binary.)

### Cosmetic / no-sync (not captured by rollback)

These go through the `DAT_71052381b0` / `DAT_71052381cc` no-sync path, `srand/rand`
libc, or the `Randomizer.no_sync_get` Lua metatable:

- Menu background shuffle
- CSS character portrait idle animations
- Replay-mode UI effects
- Any Lua script that calls `Randomizer.no_sync_get()` / `no_sync_getf()`

### How to be sure a new function is sync vs. no-sync

Check which global it reads:

- Reads from `[0x71052c25b0]` (two derefs) → **sync, capture under rollback**.
- Reads from `[0x71052381b0]` / `[0x71052381bc]` / `[0x71052381c0]` / `[0x71052381cc]`,
  or calls `rand()` / `srand()` → **no-sync, ignore**.
- Reads from `BattleObjectWorld + 0x20` (`get_world_move_seed`) → this is a
  per-match-seeded u64 that is the **parent** of the sync RNG's seed material; it
  itself is set once at match start and is implicitly covered by the rollback
  snapshot of `BattleObjectWorld`. Do not conflate it with the per-frame RNG state.

## 5. Rollback integration recipe for Eden

```cpp
// Once, when the match has started (after app::GameSetupData::finalize returns):
const uintptr_t kRandomizerSingletonGlobal = 0x71052c25b0;
auto* singleton = *reinterpret_cast<app::Randomizer**>(kRandomizerSingletonGlobal);
auto* channels  = singleton->channels;  // 180 bytes, 9 x Xorshift128

// Per frame (before advancing the simulation):
u8 rng_snapshot[0xb4];
std::memcpy(rng_snapshot, channels, 0xb4);
// ... save alongside the rest of the rollback state bundle ...

// On rollback:
std::memcpy(channels, rng_snapshot, 0xb4);
// simulation re-runs deterministically
```

Do **not** snapshot `DAT_71052381b0..cf`, do **not** re-seed libc `srand()`, and do
**not** touch the `Randomizer.no_sync_*` Lua entries. Those are intentionally divergent
across rollbacks and resimulating over them will only hurt visual continuity without
affecting gameplay outcomes.

## 6. Open follow-ups (not rollback-blocking)

- Name the remaining 7 channels by grepping Lua scripts for the literal hash constants.
- Nail down the parent object at `x21 + 0xf8` that holds the sync seed; this is
  interesting for "force a known seed" dev modes.
- Decompile the `Randomizer` constructor cleanly so the `singleton->channels` field
  layout can be nailed down past offset `+0x00` (currently the rest of the singleton
  is opaque in `app::Randomizer`).
- Sweep the ~200 singleton-reader xrefs and build a full gameplay-vs-cosmetic
  classification table. Useful for desync auditing after rollback ships but not
  required for the capture/restore path.

## Source map

- Function addresses come from Ghidra on the SSBU 13.0.4 build
  (`search_functions_by_name rand`).
- The disassembly of the seed-init path was pulled via
  `disassemble_function 0x7101344cf0` (cached at
  `.claude/.../tool-results/mcp-ghidra-disassemble_function-1775848823189.txt`).
- The decompiled bodies of `sv_math::rand`, `sv_math::randf`, the two `*::random*`
  namespaces, `lot_critical`, `FUN_7100826750`, and `setup_no_sync_seed_from_date`
  are cached in `data/ghidra_cache/pool-a.txt`.
- Struct definitions: `include/app/Randomizer.h`.
