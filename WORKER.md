# Worker: pool-c

## Model: Opus

## Task: Recover PostureModule (+0x38) and GroundModule (+0x58) structs

PostureModule handles position/rotation/scale (31+ accesses). GroundModule handles ground collision (20+ accesses).

### Phase 1: Cross-reference accesses for both modules via Ghidra MCP
### Phase 2: Build include/app/modules/PostureModule.h and GroundModule.h
### Phase 3: Rewrite src/app/modules/PostureModule.cpp and GroundModule.cpp using the structs

### DO NOT use reinterpret_cast for struct members, paste assembly, or use raw hex offsets

### Rules: ONLY edit PostureModule.h, GroundModule.h, PostureModule.cpp, GroundModule.cpp in their respective dirs
