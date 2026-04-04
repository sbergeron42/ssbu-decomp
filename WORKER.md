# Worker: pool-a

## Model: Opus

## Task: Recover WorkModule struct (+0x50)

WorkModule is accessed by 56+ functions. It stores all fighter flags and state variables. Recover its full struct layout, then decompile its functions using proper field access.

### Phase 1: Cross-reference all WorkModule accesses
1. Use Ghidra MCP: search for functions that access BattleObjectModuleAccessor offset +0x50
2. For each function, record: which offset INTO WorkModule is accessed, the type (s32, u64, bool, etc.), and how it is used
3. Save findings to /tmp/ghidra_results.txt

### Phase 2: Build the struct header
Write include/app/modules/WorkModule.h with real field types at verified offsets. Use conservative names (field_0xD8 if unsure).

### Phase 3: Decompile WorkModule functions
Rewrite src/app/modules/WorkModule.cpp using the struct. Write C++ that a developer would write, not reinterpret_cast soup.

### DO NOT use reinterpret_cast for struct members, paste assembly, or use raw hex offsets

### Rules: ONLY edit include/app/modules/WorkModule.h and src/app/modules/WorkModule.cpp
