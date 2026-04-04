# Worker: pool-e

## Model: Opus

## Task: Recover ShieldModule (+0x100), HitModule (+0xB0), and ComboModule (+0xB8) structs

Three smaller modules. ShieldModule has 38 raw casts. HitModule has 26. ComboModule has 5 functions.

### Workflow per module
1. Use Ghidra MCP: decompile functions that access the module
2. Record every offset accessed, type, and usage
3. Build struct header with confidence-tagged names
4. Rewrite .cpp idiomatically
5. Build and verify

### Rules
- CAN edit: include/app/modules/ShieldModule.h, HitModule.h, ComboModule.h and their .cpp files
- Do NOT edit other files
- Do NOT copy-paste Ghidra pseudocode
