# Worker: pool-b

## Model: Opus

## Task: Recover EffectModule (+0x140) and ControlModule (+0x48) structs

EffectModule has 24 functions / 239 raw casts. ControlModule has 24 functions / 211 raw casts.

### Workflow per module
1. Use Ghidra MCP: decompile functions that access the module
2. Record every offset accessed, type, and usage
3. Build struct header with confidence-tagged names
4. Rewrite .cpp idiomatically
5. Build and verify

### Rules
- CAN edit: include/app/modules/EffectModule.h, ControlModule.h, src/app/modules/EffectModule.cpp, ControlModule.cpp
- Do NOT edit other files
- Do NOT copy-paste Ghidra pseudocode
