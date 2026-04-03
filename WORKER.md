# Worker: pool-a

## Model: Opus

## Task: Decomp input mapping + override system for rollback

Decomp the core input pipeline functions identified in src/docs/input_handling.md. These are rollback-critical — the override slots are where remote/predicted inputs get injected.

### Target functions
- final_input_mapping @ 0x7101750f70 — core function, maps raw buttons/sticks to 8-byte game input
- FUN_71017547f0 — per-frame loop for all 8 player slots, checks override slots
- Input override mechanism at offsets 0x540-0x578 in the input struct

### Approach
- Use mcp__ghidra__decompile_function_by_address for each function
- Write READABLE C++ — use struct field names, meaningful variable names, comments explaining game logic
- Use the struct headers in include/app/ where applicable
- Add new struct definitions if needed (InputState, etc.)
- This is NOT batch pipeline work — take time to understand what each function does

### Output
- src/app/networking/input_mapping.cpp
- include/app/InputState.h (if needed for input struct definition)
- Comments explaining the rollback-relevant parts (override slots, determinism)

### Rules
- ONLY create/edit files in src/app/networking/ and include/app/
- CAN use Ghidra MCP to decompile and cross-reference
- Do NOT edit existing source files outside networking/
- Do NOT modify tools/ or data/
- Prioritize READABILITY over matching — comments and naming matter more than byte-identical
