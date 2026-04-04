# Worker: pool-e

## Model: Opus

## Task: Recover FighterManager and FighterInformation full structs

Both already have partial headers in include/app/. Flesh them out into complete struct definitions and rewrite their functions.

### Phase 1: Cross-reference all field accesses in FighterManager.cpp, FighterInformation.cpp, FighterEntry.cpp via Ghidra MCP
### Phase 2: Complete include/app/FighterManager.h, FighterInformation.h, FighterEntry.h
### Phase 3: Rewrite the source files using the structs

### DO NOT use reinterpret_cast for struct members, paste assembly, or use raw hex offsets

### Rules: ONLY edit FighterManager.h, FighterInformation.h, FighterEntry.h and their .cpp files
