# Worker: pool-c

## Model: Opus

## Task: Decomp nn::ldn game data exchange for rollback

Decomp the game-level LDN functions that handle actual frame data exchange. These are in the 0x710016xxxx-0x710019xxxx range per src/docs/networking.md.

### Target functions
- FUN_710016f400 — post-connect setup after LDN Connect
- FUN_710016da00 — secondary post-connect initialization
- FUN_710016c120 — called during LDN connect flow
- FUN_710016b2f0 — error code translation for LDN
- FUN_710016af60 — gets LDN connection parameter
- online_ldn_initialize @ 0x7100191040
- game_ldn_initialize @ 0x7103741990
- Functions that call nn::ldn::SendData / ReceiveData (find via Ghidra xrefs)

### Approach
- Start with mcp__ghidra__get_xrefs_to on nn::ldn SDK functions to find data send/receive
- Decomp each function with understanding — what data is being sent, how is it framed
- Document the packet format and frame sync protocol
- Write READABLE C++ with meaningful names and comments

### Output
- src/app/networking/ldn_transport.cpp
- include/app/LDNSession.h or similar for session/packet structs
- Update src/docs/networking.md with new findings

### Rules
- ONLY create/edit files in src/app/networking/, include/app/, and src/docs/
- CAN use Ghidra MCP to decompile and cross-reference
- Do NOT edit existing source files outside these directories
- Do NOT modify tools/ or data/
- Prioritize UNDERSTANDING over matching
