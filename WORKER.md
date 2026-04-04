# Worker: pool-a

## Model: Opus

## Task: Recover LinkModule (+0xD0) and PhysicsModule (+0x80) structs

LinkModule has 88 functions / 209 raw casts. PhysicsModule has 45 functions / 105 raw casts.

### Workflow per module
1. Use Ghidra MCP: decompile functions that access the module
2. Record every offset accessed, its type, and how it is used
3. Build the struct header with confidence-tagged names:
   - [confirmed: lua_bind API name] for names from the Lua API
   - [inferred: read as s32 by N functions] for AI guesses
   - unk_0xXX for unknown padding
4. Rewrite the .cpp using the struct — write idiomatic C++ a developer would write
5. Build and verify after each file change

### Rules
- CAN edit: include/app/modules/LinkModule.h, PhysicsModule.h, src/app/modules/LinkModule.cpp, PhysicsModule.cpp
- Do NOT edit other files
- Do NOT copy-paste Ghidra pseudocode — understand and reimplement
