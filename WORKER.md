# Worker: pool-c

## Model: Opus

## Task: Trace input handling path for rollback

For rollback netplay, we need to understand how inputs flow from controller to game state. Map the input pipeline.

### What to look for
- Controller polling functions (nn::hid usage)
- Input buffering / input delay logic
- How inputs are transmitted over network (input packets)
- Where inputs get consumed by the game simulation
- Input prediction logic (if any exists for online play)

### Approach
1. Search Ghidra for nn::hid references (controller input SDK)
2. Find functions with "input", "controller", "pad", "button", "stick" in names
3. Trace from SDK input polling → game input consumption
4. Look for the network input send/receive path (inputs sent to opponent)

### Output
- src/docs/input_handling.md with the input pipeline architecture
- Key function addresses and data flow

### Rules
- CAN create: src/docs/input_handling.md
- CAN use Ghidra MCP to search and decompile
- Do NOT edit existing source files
- Do NOT modify data/functions.csv or tools/
