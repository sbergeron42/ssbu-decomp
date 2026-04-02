# Worker: pool-e

## Model: Sonnet

## Task: Batch decomp MEDIUM FUN_* (0x7102-0x7103 range) via Ghidra pipeline

Batch-decompile MEDIUM-tier functions in address range 0x7102000000-0x7103FFFFFF.

### Batch pipeline workflow
1. Pick 20-30 uncompiled MEDIUM functions from data/fun_triage.csv in your address range
2. For each, call mcp__ghidra__decompile_function_by_address(address)
3. Apply type fixups: undefined8->u64, undefined4->u32, undefined2->u16, byte->u8, uint->u32, int->s32, long->s64, ulong->u64, bool->u8
4. Skip functions with WARNING comments or broken decompilation
5. Write to a single .cpp file with // 0x71XXXXXXXX address comments
6. Build and verify, fix compile errors, commit, repeat

### Output files
- Create src/app/fun_batch_e2_001.cpp, fun_batch_e2_002.cpp, etc.
- Do NOT put functions in any namespace (global functions)
- Forward-declare unknown called functions as extern "C" void FUNCNAME();

### Rules
- ONLY create NEW files named src/app/fun_batch_e2_*.cpp
- Do NOT edit any existing files
- Do NOT modify data/functions.csv or tools/
