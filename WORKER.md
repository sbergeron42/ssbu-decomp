# Worker: pool-a

## Model: Opus

## Task: Map networking SDK calls and find game-level netcode functions

Trace the networking code path from SDK layer upward to find all game-level networking functions. This is targeted RE for rollback netplay support.

### Step 1: Find all nn::socket usage
Use Ghidra MCP to find functions that call networking SDK functions:
- mcp__ghidra__search_functions_by_name for nn::socket, nn::nifm, nn::ssl, nn::nex
- mcp__ghidra__get_xrefs_to on each SDK function to find callers

### Step 2: Walk up the call graph
For each game function that calls SDK networking:
- mcp__ghidra__get_xrefs_to to find who calls IT
- mcp__ghidra__decompile_function_by_address to understand what it does
- Name the function based on what it does (packet_send_wrapper, session_create, etc.)
- Use mcp__ghidra__rename_function_by_address to update Ghidra

### Step 3: Document the networking architecture
Write findings to src/docs/networking.md (create this file):
- Layer diagram: SDK → packet framing → game sync → session management
- Key function addresses and names
- Data structures used for packets/state

### Output
- src/docs/networking.md with the call graph and architecture notes
- Renamed functions in Ghidra via MCP
- Any decomped networking functions go in src/app/networking/ (new directory)

### Rules
- CAN create: src/docs/networking.md, src/app/networking/*.cpp
- CAN use Ghidra MCP to rename functions and read decompilations
- Do NOT edit existing source files
- Do NOT modify data/functions.csv or tools/
