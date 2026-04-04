# Worker: pool-c

## Model: Opus

## Task: Recover DamageModule (+0xA8) and KineticModule (+0x68) structs

DamageModule has 33 functions / 54 raw casts. KineticModule has 27 functions / 74 raw casts.

### Workflow per module
1. Use Ghidra MCP: decompile functions that access the module
2. Record every offset accessed, type, and usage
3. Build struct header with confidence-tagged names
4. Rewrite .cpp idiomatically
5. Build and verify

### Rules
- CAN edit: include/app/modules/DamageModule.h, KineticModule.h, src/app/modules/DamageModule.cpp, KineticModule.cpp
- Do NOT edit other files
- Do NOT copy-paste Ghidra pseudocode
