# Worker: pool-b

## Model: Opus

## Task: Finish remaining module structs (batch 2: 11 modules)

Recover the remaining empty module structs.

### Your modules
MotionAnimcmdModule, ReflectModule, ReflectorModule, SearchModule, ShadowModule,
ShakeModule, SlowModule, StopModule, TeamModule, TurnModule, VisibilityModule

### Workflow per module
1. Ghidra MCP: decompile functions accessing the module
2. Map vtable entries with confidence-tagged names
3. Build the .h header with void** _vt + inline methods
4. Rewrite the .cpp using clean dispatch
5. Build and verify

### Rules
- CAN edit: include/app/modules/ and src/app/modules/ for your 11 modules only
- Use [confirmed: lua_bind API name] for names from lua_bind
- Use [inferred: ...] for guesses
- Do NOT copy-paste Ghidra pseudocode
