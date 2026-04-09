# Worker: pool-b

## Model: Opus

## Task: Fighter core medium functions — continue

## Progress from last session
- get_fighter_id_from_fighter_kind (3,604B) — 100% match
- get_entry_in_fighter_param_kind_struct (15,848B) — 78% (ADRP + branch ordering)
- Hash-to-value switch pattern matches well with Clang 8 binary search tree generation

## Continue with
- Remaining fighter targets: heal_fighters (3,644B), chase_fighter (3,148B), escape_from_fighter (2,700B)
- Look for more hash-to-value switch pattern functions
- fighter_status.cpp AI functions (smaller, consistent output)

## Skipped (don't retry)
- save_aura_ball_status — Ghidra can't recover jump table
- load_fighter — Too complex (mutexes, Mii accessor)
- NEON intrinsic functions — Can't reproduce from standard C++

## File Territory
- src/app/fighter_core.cpp (continue)
- src/app/fighter_status.cpp
- src/app/fighter_attack.cpp

## Quality Rules
- No naked asm
- Document derivation chains
- 3-attempt limit
