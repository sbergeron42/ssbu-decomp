# SVC resim fix — IPC chain identification and intercept strategy

## The SVC sequence is nn::audio::AudioRenderer::RequestUpdate

The pattern `WaitSync → ClearEvent → SendSync → SendSync → SignalPWK → Break`
matches **nn::audio::AudioRenderer::RequestUpdate** exactly:

1. **SVC 0x18** (WaitSynchronization) — wait for the audio render completion event
2. **SVC 0x12** (ClearEvent) — clear the event for the next cycle
3. **SVC 0x21** (SendSyncRequest #1) — send the "update my mix state" command
4. **SVC 0x21** (SendSyncRequest #2) — send the "here's my parameter buffer" data
5. **SVC 0x1d** (SignalProcessWideKey) — wake the audio mixing thread (`nus3::audio update` at `DAT_7106dd4cc0`)
6. **SVC 0x26** (Break) — assertion fired because the faked IPC responses left the audio service in an inconsistent state

The two back-to-back `SendSyncRequest` calls with the same LR (`SDK+0x367684`)
are the hallmark of `nn::audio`'s two-phase IPC protocol: first message sends
the command, second sends the updated audio parameter buffer. No other SDK
service uses two consecutive `SendSyncRequest` calls at the same call site.

## Why it fires during the sim tick

The sim tick calls fighter-action code, which calls SoundModule vtable
methods to trigger attack SFX, voice clips, hit sounds, etc. SoundModule
dispatches into the `nus3` audio library, which submits the audio parameter
update to the nn::audio service via IPC.

The entry from game code into the audio IPC is through `SoundModule::*`
virtual methods on `BattleObjectModuleAccessor->sound_module` (`+0x148`).
Multiple different fighter-action code paths can trigger this — any attack,
hit, KO, voice line, or ambient SE.

## Recommended fix: fake ALL SVCs during resim, no exceptions

The current approach (fake most SVCs, passthrough SVC 0x21) is fundamentally
broken because:

1. **Paused cores can't respond to IPC** — the server thread for `nn::audio`
   is `nus3::audio update`, which runs on a separate core. If that core is
   paused, `SendSyncRequest` blocks forever.
2. **Faking SVC 0x21 individually causes kernel state drift** — the guest
   believes the IPC succeeded, but the kernel's session state didn't advance.
   Subsequent SVCs that depend on kernel-side state (wait lists, event
   signal counts) become inconsistent.
3. **The Break at SVC 0x26 confirms drift** — the audio service got a faked
   "success" response with zeroed data, tried to use it, and hit an
   assertion. Even zeroing TLS cleanly isn't enough because the audio service
   has internal state that expected the real parameter buffer.

### The correct approach

**During resim, fake ALL SVCs unconditionally — including 0x21.**

```cpp
if (resim_mode) {
    // Every SVC returns 0 (success). No kernel interaction at all.
    // TLS is saved/restored at trampoline boundary (you already do this).
    // Audio, IPC, waits, signals — all no-ops during resim.
    return fake_svc_result(svc_id);
}
```

This works because:

1. **Audio state doesn't affect gameplay determinism.** Whether a sound
   played or not doesn't change fighter positions, damage, or knockback.
   The SoundModule's internal bookkeeping may get stale, but it's not
   part of the rollback snapshot — we don't restore it, so it drifts
   harmlessly and self-corrects on the next real (non-resim) frame.

2. **No sim-state mutation depends on an IPC response.** The sim tick's
   determinism comes from input + RNG + BattleObject state. None of these
   are written by IPC responses. The audio IPC is fire-and-forget from
   the sim's perspective.

3. **The PLT-stub fault net catches anything unexpected.** If some
   undiscovered IPC path DOES write to sim state, the PLT fault (from
   `sim_tick_safety.md` recommendation #3) catches it.

### Why passthrough on 0x21 was wrong

The original rationale for passing through SVC 0x21 was "the IPC response
buffer at TLS needs to be filled." But during resim, **nothing in the sim
tick reads TLS IPC response data to make gameplay decisions**. The only
consumer of the response is the audio service wrapper itself, which uses
it to update audio mixer state — which is presentation, not sim.

The TLS save/restore at trampoline entry/exit already isolates the resim
from corrupting the real IPC buffer state. With all SVCs faked, the
resim completes without touching the kernel, and the next real frame
starts with the original TLS state intact.

## The "1 fps after rollback" symptom

This is **kernel wait-list drift** from the `SignalProcessWideKey` fake.
The guest code called `pthread_cond_signal` (SVC 0x1d) during resim, but
the fake didn't actually wake any kernel waiters. After resim completes
and the game resumes normal execution, a thread that expected to be woken
is still sleeping in the kernel. The main loop hits a synchronization
point that waits for that thread, and stalls.

**Fix**: with ALL SVCs faked (including 0x1d), the guest code doesn't
believe it signaled anyone, so it doesn't expect anyone to have woken up.
The resim completes without creating any expectation of kernel-side state
change. After resim, the real kernel state is exactly as it was before
the resim started — no drift.

## Summary of recommended SVC policy during resim

| SVC | Name | Policy | Reason |
|-----|------|--------|--------|
| 0x01 | SetHeapSize | FAKE | no heap resize during sim tick |
| 0x08 | CreateThread | FAKE | sim tick doesn't spawn threads |
| 0x12 | ClearEvent | FAKE | audio event — no-op during resim |
| 0x18 | WaitSynchronization | FAKE | would block — always fake |
| 0x1a | ArbitrateLock | FAKE | mutex acquire — CAS on guest memory only |
| 0x1b | ArbitrateUnlock | FAKE | mutex release — same |
| 0x1d | SignalProcessWideKey | FAKE | condvar signal — no kernel interaction |
| 0x1e | WaitProcessWideKey | FAKE | condvar wait — would block |
| 0x21 | SendSyncRequest | **FAKE** | IPC — no kernel interaction during resim |
| 0x26 | Break | FAKE (log + return) | assertion — log the PC for debugging |
| * | anything else | FAKE | conservative default |

## Main-NSO entry points for audio IPC (for future targeted intercept)

If you later want Option B (NOP the game-side caller instead of faking SVCs),
the entry points are any `SoundModule::*` virtual method dispatch:

- `BattleObjectModuleAccessor->sound_module` is at accessor `+0x148`
- SoundModule vtable methods include `play_se`, `play_se3d`, `stop_se`,
  `play_voice`, `stop_voice`, etc. (52 methods in `include/app/modules/SoundModule.h`)
- Each of these eventually calls into `nus3` library code which does the IPC

There is no single function to NOP — any of ~52 SoundModule methods can
trigger the IPC. Faking SVCs is the cleaner approach.

## Cross-references

- `docs/rollback/sim_tick_safety.md` — outer shell audit (clean; this IPC is from inner vtable dispatches)
- `docs/rollback/sim_tick_FOUND.md` — backtrace showing FUN_710135f570 in the sim path
- `include/app/modules/SoundModule.h` — 52 typed SoundModule vtable wrappers
- `src/lib/audio_dsp_identified.cpp` — nus3/XDSP audio library identification
- `docs/rollback/sim_tick_hunt.md` Round 7 — `nus3::audio update` thread identified at DAT_7106dd4cc0
