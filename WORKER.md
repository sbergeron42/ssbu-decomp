# Worker: pool-b

## Model: Opus

## Task: Trace game state serialization for rollback

For rollback netplay, we need to know what game state must be saved and restored each frame. Find the state serialization functions.

### What to look for
- Functions that snapshot game state (position, velocity, damage, stocks, frame counter)
- Functions that restore/load state from a buffer
- The main game loop tick function (what runs each frame)
- BattleObject state save/load patterns
- Fighter state that changes per frame

### Approach
1. Search Ghidra for functions with "save", "load", "serialize", "snapshot", "state" in names
2. Look at store_l2c_table / load_from_l2c_table patterns — these serialize struct fields
3. Trace what BattleObjectModuleAccessor stores per frame
4. Find the main game update loop (the function called 60 times per second)

### Output
- src/docs/game_state.md with findings on state management
- Key function addresses, what state they manage, data flow

### Rules
- CAN create: src/docs/game_state.md
- CAN use Ghidra MCP to search and decompile
- Do NOT edit existing source files
- Do NOT modify data/functions.csv or tools/
