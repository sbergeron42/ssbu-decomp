# Worker: pool-a

## Model: Opus

## Task: Finish remaining module structs (batch 1: 12 modules)

Recover the remaining empty module structs. Same workflow as previous rounds.

### Your modules
AbsorberModule, AreaModule, ArticleModule, CancelModule, CaptureModule, CatchModule,
ColorBlendModule, GrabModule, InkPaintModule, ItemModule, JostleModule, ModelModule

### Workflow per module
1. Ghidra MCP: decompile functions accessing the module
2. Map vtable entries with confidence-tagged names
3. Build the .h header with void** _vt + inline methods
4. Rewrite the .cpp using clean dispatch
5. Build and verify

### Rules
- CAN edit: include/app/modules/ and src/app/modules/ for your 12 modules only
- Use [confirmed: lua_bind API name] for names from lua_bind
- Use [inferred: ...] for guesses
- Do NOT copy-paste Ghidra pseudocode
