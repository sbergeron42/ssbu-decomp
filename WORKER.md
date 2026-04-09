# Worker: pool-b

## Model: Opus

## Task: Fighter core medium functions — continue

## Progress from last session
- get_fighter_id_from_fighter_kind (3,604B) — 100% match
- get_entry_in_fighter_param_kind_struct (15,848B) — 78% (ADRP + branch ordering)
- Hash-to-value switch pattern matches well with Clang 8 binary search tree generation

## Progress from current session
- change_status_lost (108B, 0x71015cb330) — **100% byte match**
- set_force_flashing (124B, 0x71015c29f0) — **100% byte match**
- set_bomb_countdown (100B, 0x71015c12a0) — 64% (prologue scheduling only)
- pos_2d (108B, 0x71015c6c10) — 66% (prologue scheduling only)
- add_damage (132B, 0x71015c1600) — 66% (prologue scheduling only)
- Key technique: asm("") barriers prevent vtable caching + tail call, u32 vs u64 for hash constants

## Continue with
- More small item utility functions (100-200B range, vtable-chain pattern)
- Link event struct layout investigation (send_link_event_disable_clatter etc.)
- fighter_status.cpp AI functions (smaller, consistent output)

## Skipped (don't retry)
- save_aura_ball_status — Ghidra can't recover jump table
- load_fighter — Too complex (mutexes, Mii accessor)
- NEON intrinsic functions — Can't reproduce from standard C++
- heal_fighters, chase_fighter, escape_from_fighter — All NEON-heavy (frsqrte/frsqrts)
- attack_interval_* cluster — app::ai_koopag namespace, outside file territory
- is_boss_battle etc. — __cxa_guard_acquire + global refs, ADRP mismatch

## File Territory
- src/app/fighter_core.cpp (continue)
- src/app/fighter_status.cpp
- src/app/fighter_attack.cpp

## Quality Rules
- No naked asm
- Document derivation chains
- 3-attempt limit
