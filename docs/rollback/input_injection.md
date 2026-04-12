# InputPollStruct singleton for rollback input injection

## TL;DR

```cpp
// Read the InputPollStruct pointer (one deref):
InputPollStruct* input = *(InputPollStruct**)(main_base + 0x52C40F0);

// Write override inputs before each resim tick:
for (int i = 0; i < 8; i++) {
    input->override_inputs[i] = predicted_inputs[i];  // +0x540 + i*8
    input->override_enable[i] = 1;                     // +0x580 + i
}

// Then call the sim tick:
dynarmic_call_guest(0x7103724a80, sim_root);
```

## Singleton address

**`DAT_71052C40F0`** (ELF address `0x71052C40F0`, runtime = `main_base + 0x52C40F0`)

Holds an `InputPollStruct*`. One pointer dereference to reach the struct body.

### Evidence

`FUN_710135f570` (the per-frame task that calls `input_poll_all_players`) reads:
```c
lVar39 = DAT_71052c40f0;    // line 172 of Ghidra decompile
// then accesses lVar39+0x14, lVar39+0x11, lVar39+0x590, etc.
```

The field offsets `+0x540` (override_inputs), `+0x580` (override_enable), `+0x590`,
`+0x5C0` all match `InputState.h`'s `InputPollStruct` layout exactly.

## Stability

**YES — stable for match lifetime.**

`DAT_71052C40F0` is in the `.bss` section (`0x52A8570..0x7446FFF`), same region
as all the other match-runtime singletons (`DAT_710593A4C0` sim_root,
`DAT_71052B7548` BattleObjectManager, etc.). The InputPollStruct instance is
allocated once at match start and the pointer doesn't change during the match.

Eden can cache it once at match start:
```cpp
void* input_poll_struct = *(void**)(guest_memory + 0x52C40F0);
```

## Calling context — INSIDE the sim tick

**`input_poll_all_players` runs INSIDE the sim tick's call tree, not outside it.**

Evidence: the sim tick backtrace captured via RNG watchpoint (from
`sim_tick_FOUND.md`) includes:

```
0x135f76c  L2C / ACMD layer
```

`0x710135f76c` is **inside** `FUN_710135f570` (which spans `0x710135f570..~0x71013608xx`).
`FUN_710135f570` is the function that calls `FUN_71017547f0` (`input_poll_all_players`).
Therefore `input_poll_all_players` is invoked as part of the per-frame sim tick.

### Timing implication for rollback

**Write override inputs BEFORE calling `dynarmic_call_guest(0x7103724a80, sim_root)`.**

Since input polling runs inside the sim tick, the sequence is:

1. Eden writes `override_inputs[0..7]` and sets `override_enable[0..7] = 1`
2. Eden calls `dynarmic_call_guest(0x7103724a80, sim_root)` — one sim tick
3. Inside the sim tick, `input_poll_all_players` runs:
   - Reads hardware inputs (stale/irrelevant during resim)
   - Checks `override_enable[i]`
   - If enabled: uses `override_inputs[i]` instead of hardware → correct!
4. The fighter logic runs with the overridden inputs
5. RNG advances, positions update, etc.

This is the cleanest possible design — Eden doesn't need to hook a separate
input-polling call before the sim; the override mechanism is built into the
polling function itself.

## Pointer chain summary

| What | Address | Depth | Notes |
|------|---------|-------|-------|
| InputPollStruct* slot | `0x71052C40F0` | .bss global | single `u64` |
| InputPollStruct body | `*0x71052C40F0` | 1 deref | ~0x5C8 bytes |
| override_inputs[8] | body + 0x540 | 8 × `MappedInput` (8 B each) | 64 bytes total |
| override_enable[8] | body + 0x580 | 8 × `u8` | 8 bytes total |
| mapped_inputs[8] | body + 0x2B8 | 8 × `MappedInput` (output) | read-only for rollback |

## Cross-references

- `InputState.h` — full struct layout with all field offsets
- `src/app/networking/input_mapping.cpp` — decomped `input_poll_all_players`
- `docs/rollback/sim_tick_FOUND.md` — backtrace proving `FUN_710135f570` is in the sim tick path
- `src/docs/input_handling.md` — input pipeline documentation
