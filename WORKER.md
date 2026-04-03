# Worker: pool-b

## Model: Opus

## Task: Decomp CSS state serialization trio for rollback

Decomp the save/restore state functions identified in src/docs/game_state.md. These are the model for battle state rollback — they show exactly what state the game considers important to serialize.

### Target functions
- css_serialize_state_to_buffer (5.7KB) — serializes CSS state to flat buffer
- css_restore_state_from_save (4.9KB) — restores from buffer to globals
- css_read_state_to_compact_buffer (560B) — compact form for network transmission
- Also: any related state structs these functions reveal

### Approach
- Use mcp__ghidra__decompile_function_by_address for each function
- These are large functions — work through them methodically
- Document every field being serialized — this tells us what rollback needs to save
- Define proper structs for the state buffers
- Write READABLE C++ with comments on every serialized field

### Output
- src/app/networking/state_serialize.cpp
- include/app/CSSState.h or similar for the state struct
- Comments mapping each serialized field to its game meaning

### Rules
- ONLY create/edit files in src/app/networking/ and include/app/
- CAN use Ghidra MCP to decompile and cross-reference
- Do NOT edit existing source files outside networking/
- Do NOT modify tools/ or data/
- Prioritize READABILITY and DOCUMENTATION over matching
