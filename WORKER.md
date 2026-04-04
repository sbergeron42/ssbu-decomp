# Worker: pool-d

## Model: Opus

## Task: Recover SoundModule (+0x148) and CameraModule (+0x60) structs

SoundModule has 20 functions / 54 raw casts. CameraModule has 39 functions / 68 raw casts.

### Workflow per module
1. Use Ghidra MCP: decompile functions that access the module
2. Record every offset accessed, type, and usage
3. Build struct header with confidence-tagged names
4. Rewrite .cpp idiomatically
5. Build and verify

### Rules
- CAN edit: include/app/modules/SoundModule.h, CameraModule.h, src/app/modules/SoundModule.cpp, CameraModule.cpp
- Do NOT edit other files
- Do NOT copy-paste Ghidra pseudocode
