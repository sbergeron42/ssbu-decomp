# Gameplay RNG — Rollback Capture / Restore

Primary deliverable for the rollback netcode effort. This document describes where the
deterministic gameplay RNG lives in SSBU 13.0.4, how it advances, and exactly which
bytes a rollback fork of Eden must capture and restore each frame.

## TL;DR for the Eden fork

- The "sync" gameplay RNG is **9 independent xorshift128 streams** (Marsaglia 2003),
  selected by a `phx::Hash40` channel argument.
- The 9 streams live contiguously in a 180-byte (0xb4) heap buffer owned (at two
  levels of indirection) by a singleton whose pointer lives at `0x71052c25b0`.
  Reaching the 180 bytes takes **three** pointer dereferences from that address, not
  two. See §2 for the exact chain — getting the deref count wrong corrupts the game.
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

`sv_math::rand` dispatches on a `phx::Hash40` to a fixed channel offset within a
180-byte heap buffer. The mapping is exhaustive — there is no hash-table lookup,
just a binary-search tree of compile-time constants. Any hash that does not match
any case uses the default slot at offset 0.

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

Total: 9 × 0x14 = **0xb4 bytes**. Struct: `app::RandomizerChannels` in
`include/app/Randomizer.h`.

Note that the unnamed channels likely have meaningful community names once Lua scripts
are inspected — a grep through the Lua script dump for the literal hash values (e.g.
`0x77a08c3fc`) will reveal them. This is a follow-up task; for rollback it does not
matter which channel is which, only that all 180 bytes are captured together.

### The owning `RandomizerChannelVec` (std::vector<Xorshift128>)

The 180-byte channel array does **not** sit inside the singleton. It is the
backing storage of a **libc++ `std::vector<app::Xorshift128>`** whose 32-byte
header is the middle link in the indirection chain. The constructor
(`FUN_7101344cf0` at `0x7101344d50..0x7101344e28`) allocates everything in
sequence:

```
je_aligned_alloc(16, 8)     → Randomizer*             (the singleton value itself)
je_aligned_alloc(16, 32)    → RandomizerChannelVec*   (the vector header)
vec.resize(9)               → inside std_vector_Xorshift128_resize_710143ab00:
                              je_aligned_alloc(16, 180) for the T* buffer and
                              writes __begin_/__end_/__end_cap_ into the header
```

The vec header layout is the standard libc++ one:

```
+0x00  Xorshift128* __begin_         // points at the 180-byte channel buffer
+0x08  Xorshift128* __end_           // __begin_ + 9
+0x10  Xorshift128* __end_cap_       // = __end_ here (size == capacity)
+0x18  <allocator>   __alloc_ (8 B)  // empty allocator EBO slack; reused as a
                                     //   u32 slot: 0x87654321 placeholder at
                                     //   construction, overwritten with the
                                     //   u32 match seed by 0x71013454c8.
```

Two confirmations that this really is `std::vector`:

1. `std_vector_Xorshift128_resize_710143ab00` uses the libc++ capacity-overflow
   constant `0xccccccccccccccc` (= floor(2^64 / sizeof(Xorshift128))) and calls
   `std::__1::__vector_base_common<true>::__throw_length_error` on overflow.
2. New elements are default-constructed with `(0x075bcd15, 0x159a55e5, 0x1f123bb5,
   0x05491333, 0)` — the canonical Marsaglia 2003 xorshift128 initial state
   (123456789 / 362436069 / 521288629 / 88675123). These are overwritten the
   moment the seed-init loop at `0x710134551c` runs, but they are what the
   default constructor leaves behind before seeding.

The `0x87654321` value written at construction is a placeholder, not a
persistent sentinel — once the match-start seed-init code runs, the slot at
+0x18 holds the u32 seed that was used to derive all 9 channels. Capturing
the 180-byte channel buffer under rollback does **not** need to include this
slot; it is written once per match and stays constant for the entire match.

### Global accessor — three loads from `0x71052c25b0`

Every decompiled reader uses the same three-deref pattern. In AArch64 asm
(`sv_math::rand` at 0x7102275374 — identical sequence in every inlined reader):

```
adrp x8, 0x71052c2000
ldr  x8, [x8, #0x5b0]      ; load 1 → Randomizer*            (singleton)
ldr  x8, [x8]              ; load 2 → RandomizerChannelVec*  (vec header)
ldr  x8, [x8]              ; load 3 → RandomizerChannels*    (180-byte buffer)
; x8 + channel_offset + field_offset is the target
```

Ghidra decompile output is easy to misread here. The expression

```c
lVar4 = *(long *)*DAT_71052c25b0;
```

represents **three** loads, not two: `DAT_71052c25b0` is the Ghidra symbol for the
*value loaded from* 0x71052c25b0 (load 1 = Randomizer*), the bare `*` adds another
load (load 2 = ChannelVec*), and the `*(long*)` cast-and-deref adds the third load
(load 3 = channel array begin). The earlier version of this document claimed two
loads and that is incorrect.

So the sequence Eden must follow is:

1. `Randomizer* r = *(Randomizer**)0x71052c25b0;`  — load 1.
2. `RandomizerChannelVec* v = r->vec;`             — load 2 (i.e. `*(u64*)r`).
3. `RandomizerChannels* channels = v->channels;`   — load 3 (i.e. `*(u64*)v`).
4. `memcpy(snapshot, channels, 0xb4);`             — the rollback payload.
5. On rollback: `memcpy(channels, snapshot, 0xb4);`.

**Important:** All three pointers (`r`, `v`, `channels`) are stable across frames
after match start. The constructor never reallocates the 180-byte buffer and
nothing else writes through the chain. Eden can cache `channels` once when the
match begins; it is **not** part of the per-frame snapshot.

**Do not** `memcpy(v, snapshot, 0xb4)` — that would overwrite the vec header's
`begin`/`end` pointers with RNG state bytes, corrupting the heap. This is the
bug that the previous two-deref description of this path would have produced.

## 3. Seed init

The `Randomizer` singleton is initialized deep inside a large boot routine
(`FUN_7101344cf0`, ~32 KB). The relevant sequence starts at `0x710134545c` and performs
two things: seeding the sync RNG and calling the no-sync seed helper.

### Sync seed derivation (`0x71013454b0`..`0x7101345534`)

```
ldr  w19, [x21, #0xf8]      ; w19 = u32 seed from parent object
str  w19, [x21, #0x50]      ; copy seed to a neighbouring field (for later read)
adrp x8,  0x71052c2000
ldr  x20, [x8, #0x5b0]      ; x20 = Randomizer* singleton             (load 1)
ldr  x8,  [x20]             ; x8  = RandomizerChannelVec*              (load 2)
str  w19, [x8, #0x18]       ; stash seed at vec+0x18 (overwrites 0x87654321 marker)
bl   0x710366d110           ; setup_no_sync_seed_from_date(seed)
ldr  x9,  [x20]             ; reload vec ptr (BL may have clobbered)
ldp  x8,  x9, [x9]          ; x8 = vec->channels (begin), x9 = vec->end (load 3+4)
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
- The `ldp x8, x9, [x9]` load reads the first 16 bytes of the 32-byte
  `RandomizerChannelVec` as a `(begin, end)` pair. The 180 bytes of state are a
  separately-allocated buffer pointed at by `begin`, **not** an inline extension of
  the vec header. See §2 "The owning `RandomizerChannelVec` (32 bytes)" for the full
  layout and the allocator chain that constructs it (FUN_7101344cf0 @ 0x7101344d50).
- The seed loop writes every channel (`stp w13, wzr, [x8, #0xc]` etc.) through the
  `begin..end` range. The vec header itself is untouched by the loop body; what the
  previous version of this document described as "header overlapping slot 0" was
  wrong — they live in separate allocations.

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
| `0x71002ec1a0` .. `0x71002f5900` | AI input generator cluster (~8 large functions) including `FUN_71002f2a00`, `FUN_71002ef000`, `FUN_71002f09b0`, `FUN_71002f04f0`, `FUN_71002f49e0`, `FUN_71002f5900`, `FUN_71002eeb20`, `FUN_71002ec1a0`. `FUN_71002f2a00` alone reads the singleton 20+ times per call through 40+ switch cases dispatching on a fighter-state-kind field. Every roll uses the `ai_random` channel (+0x50) and compares against `frames_remaining / 60.0` (DAT_7104471e0c == 60.0f). On success the function calls `FUN_71002f46a0(param_1, cmd)` with `cmd` in the `0x6030..0x6080` range — AI pad-command enum values. | **sync-critical**: this is the CPU opponent decision layer. Every AI button press must be deterministic for replay / rollback, so every one of these singleton reads belongs under the rollback snapshot. |

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

- Reads from `[0x71052c25b0]` (three derefs — see §2) → **sync, capture under rollback**.
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
auto* vec       = singleton->vec;        // 32-byte vec header
auto* channels  = vec->channels;         // 180 bytes, 9 x Xorshift128  (THIRD deref)

// Per frame (before advancing the simulation):
u8 rng_snapshot[0xb4];
std::memcpy(rng_snapshot, channels, 0xb4);
// ... save alongside the rest of the rollback state bundle ...

// On rollback:
std::memcpy(channels, rng_snapshot, 0xb4);
// simulation re-runs deterministically
```

If you ever get a crash on rollback restore that looks like a heap corruption with
begin/end pointers replaced by plausible-looking u32 values, double-check the deref
count: you almost certainly `memcpy`'d into `vec` (the 32-byte header) instead of
`channels` (the 180-byte data buffer).

Do **not** snapshot `DAT_71052381b0..cf`, do **not** re-seed libc `srand()`, and do
**not** touch the `Randomizer.no_sync_*` Lua entries. Those are intentionally divergent
across rollbacks and resimulating over them will only hurt visual continuity without
affecting gameplay outcomes.

## 6. Open follow-ups (not rollback-blocking)

- Name the remaining 7 channels by grepping Lua scripts for the literal hash constants.
- Nail down the parent object at `x21 + 0xf8` that holds the sync seed; this is
  interesting for "force a known seed" dev modes.
- ~~Identify `FUN_710143ab00`~~ — done. It is libc++
  `std::vector<app::Xorshift128>::resize`, renamed to
  `std_vector_Xorshift128_resize_710143ab00` in Ghidra.
- Sweep the ~200 singleton-reader xrefs and build a full gameplay-vs-cosmetic
  classification table. Useful for desync auditing after rollback ships but not
  required for the capture/restore path.

## Source map

- Function addresses come from Ghidra on the SSBU 13.0.4 build
  (`search_functions_by_name rand`).
- The disassembly of the seed-init path and the constructor allocation sequence
  at `0x7101344d50..0x7101344e28` was pulled via `disassemble_function 0x7101344cf0`.
  The three-deref reader pattern was verified against the full disassembly of
  `sv_math::rand` at `0x7102275374..0x7102275380` (see `decompile_function_by_address
  0x7102275320` output in the session tool-results cache).
- The decompiled bodies of `sv_math::rand`, `sv_math::randf`, the two `*::random*`
  namespaces, `lot_critical`, `FUN_7100826750`, and `setup_no_sync_seed_from_date`
  are cached in `data/ghidra_cache/pool-a.txt`.
- Struct definitions: `include/app/Randomizer.h`.
