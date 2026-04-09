# Worker: pool-b

## Model: Opus

## Task: Fighter core — continue item/fighter utility functions

## Progress
- get_fighter_id_from_fighter_kind (3,604B) — 100%, get_entry_in_fighter_param_kind_struct (15,848B) — 78%
- change_status_lost (108B) — 100%, set_force_flashing (124B) — 100%
- 10 item/fighter utility functions (get_item_kind 94%, remove_item_from_id 91%, etc.)
- FighterEntry struct: +0x591F partner_flags, +0x5935 is_unloaded
- Key: asm("") barriers, u32 vs u64, csel vs branch divergence

## Continue with
- More small item/fighter utility functions (100-200B, vtable-chain pattern)
- is_fighter_enabled (88B), get_fighter_entry_id (172B), item_throw (136B)
- fighter_status.cpp AI functions
- Hash-to-value switch pattern functions (match well)

## Skipped (don't retry)
- NEON functions, Ghidra jump table failures, global-ref ADRP mismatches
- is_loaded_fighter — NX reorders singleton check

## File Territory
- src/app/fighter_core.cpp, fighter_status.cpp, fighter_attack.cpp

## Quality Rules
- No naked asm, 3-attempt limit, derivation chains
