# Worker: pool-b

## Model: Opus

## Task: Recover StatusModule struct (+0x40)

StatusModule is accessed by 73+ functions. Controls fighter state transitions. Recover its struct layout and decompile its functions.

### Phase 1: Cross-reference all StatusModule accesses via Ghidra MCP
### Phase 2: Build include/app/modules/StatusModule.h
### Phase 3: Rewrite src/app/modules/StatusModule.cpp using the struct

### DO NOT use reinterpret_cast for struct members, paste assembly, or use raw hex offsets

### Rules: ONLY edit include/app/modules/StatusModule.h and src/app/modules/StatusModule.cpp
