# Worker: pool-b

## Model: Opus

## Task: Fighter core — continue item utility + fighter functions

## Progress
- get_fighter_id_from_fighter_kind (3,604B) — 100% match
- get_entry_in_fighter_param_kind_struct (15,848B) — 78%
- change_status_lost (108B) — 100%, set_force_flashing (124B) — 100%
- 5 more item utility functions (N-quality)
- Key: asm("") barriers, u32 vs u64 for hash constants, csel vs branch divergence
- is_activate_fighter (72B) — 83% match, ADRP-only diffs
- deactivate_fighter (68B) — 76% match, ADRP-only diffs
- set_fighter_slow (184B) — 80% match, prologue+ADRP diffs
- cancel_fighter_slow (164B) — 80% match, prologue+ADRP diffs
- get_item_kind (140B) — 94% match, ADRP-only diffs
- remove_item_from_id (88B) — 91% match, ADRP-only diffs
- find_active_item_from_id (92B) — 70% match, NX csel epilogue diff
- is_loaded_fighter (68B) — N-quality, NX condition ordering divergence
- is_enable_capture (96B) — 54% match, branch layout + eor/mvn diff
- is_enable_capture_beetle (96B) — 54% match, same pattern

## Continue with
- More small item/fighter utility functions (100-200B, vtable-chain pattern)
- fighter_status.cpp AI functions
- Avoid: switch/if-else-chain functions (csel divergence), guard variable functions

## Skipped (don't retry)
- NEON functions (heal_fighters, chase_fighter, escape_from_fighter)
- Ghidra jump table failures (save_aura_ball_status)
- Global-ref functions (is_boss_battle etc.) — ADRP mismatch
- is_loaded_fighter — NX reorders singleton check before param check
- LINK_LINKBOMB param functions — NX uses branches, upstream uses csel for if/else chains
- get_item_swing_motion_rate — jump table format differs between NX and upstream
- Guard variable functions (cxa_guard_acquire pattern) — complex static init

## File Territory
- src/app/fighter_core.cpp, fighter_status.cpp, fighter_attack.cpp

## Quality Rules
- No naked asm, 3-attempt limit, derivation chains

## FighterEntry struct updates
- +0x591F partner_flags (bit 1 = has partner) [derived: set_fighter_slow]
- +0x5935 is_unloaded (1 = unloaded) [derived: is_loaded_fighter]

## Key matching techniques discovered
- `asm("" ::: "memory")` prevents CSE of vtable fn ptr across blr calls
- Upstream Clang 8 hoists conditions/CSEs more aggressively than NX Clang
- tbz/tbnz branch sense is compiler's choice — can't easily control
