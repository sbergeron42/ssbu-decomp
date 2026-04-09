# Worker: pool-b

## Model: Opus

## Task: Fighter core — continue item utility + fighter functions

## Progress
- get_fighter_id_from_fighter_kind (3,604B) — 100% match
- get_entry_in_fighter_param_kind_struct (15,848B) — 78%
- change_status_lost (108B) — 100%, set_force_flashing (124B) — 100%
- 5 more item utility functions (N-quality)
- Key: asm("") barriers, u32 vs u64 for hash constants, csel vs branch divergence

## Continue with
- More small item/fighter utility functions (100-200B, vtable-chain pattern)
- fighter_status.cpp AI functions
- Look for hash-to-value switch pattern functions (these match well)

## Skipped (don't retry)
- NEON functions (heal_fighters, chase_fighter, escape_from_fighter)
- Ghidra jump table failures (save_aura_ball_status)
- Global-ref functions (is_boss_battle etc.) — ADRP mismatch

## File Territory
- src/app/fighter_core.cpp, fighter_status.cpp, fighter_attack.cpp

## Quality Rules
- No naked asm, 3-attempt limit, derivation chains
