# Worker: pool-d

## Model: Opus

## Task: Recover MotionModule (+0x88) and AttackModule (+0xA0) structs

MotionModule handles animation frame data (25+ accesses). AttackModule handles hitbox state (25+ accesses).

### Phase 1: Cross-reference accesses for both modules via Ghidra MCP
### Phase 2: Build include/app/modules/MotionModule.h and AttackModule.h
### Phase 3: Rewrite src/app/modules/MotionModule.cpp and AttackModule.cpp using the structs

### DO NOT use reinterpret_cast for struct members, paste assembly, or use raw hex offsets

### Rules: ONLY edit MotionModule.h, AttackModule.h, MotionModule.cpp, AttackModule.cpp in their respective dirs
