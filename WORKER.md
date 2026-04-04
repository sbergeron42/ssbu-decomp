# Worker: pool-c

## Model: Opus

## Task: Decomp FighterInformation, FighterManager, BattleObjectWorld field-access thunks

### Status: In progress

### Completed
- 11 FighterInformation bool-field read functions (rabbit_cap, reflector, superleaf, etc.)
- 4 FighterManager field access functions (is_discretion_final_enabled, is_ready_go, set_cursor_whole, is_result_mode)
- 2 BattleObjectWorld bool-field read functions (is_move, is_disable_reverse)
- **17 functions total, all byte-verified against binary**

### Notes
- Work/Status module thunks already done in modules/WorkModule.cpp and modules/StatusModule.cpp
- WorkModule.cpp has ~16 functions with wrong param types (u64 instead of s32,s32,s32 per CSV mangled names)
- HARD tier from next_batch.py contains only destructors/utilities, no module accessor functions
- CSV function sizes are inflated (include alignment padding) — actual sizes are 8-12 bytes for field reads

### Output
- src/app/fun_typed_c_001.cpp

### Rules
- ONLY create NEW files named src/app/fun_typed_c_*.cpp
- Do NOT copy-paste Ghidra pseudocode
