# Worker: pool-d

## Model: Sonnet

## Task: Batch decomp MEDIUM FUN_* (0x7100-0x7101 range) via Ghidra pipeline

Batch-decompile MEDIUM-tier functions in address range 0x7100000000-0x7101FFFFFF.

### Batch pipeline workflow
1. Pick 20-30 uncompiled MEDIUM functions from data/fun_triage.csv in your address range
2. For each, call mcp__ghidra__decompile_function_by_address(address)
3. Apply type fixups: undefined8->u64, undefined4->u32, undefined2->u16, byte->u8, uint->u32, int->s32, long->s64, ulong->u64, bool->u8
4. Skip functions with WARNING comments or broken decompilation
5. Write to a single .cpp file with // 0x71XXXXXXXX address comments
6. Build and verify, fix compile errors, commit, repeat

### Output files
- Create src/app/fun_batch_d3_001.cpp, fun_batch_d3_002.cpp, etc.
- Do NOT put functions in any namespace (global functions)
- Forward-declare unknown called functions as extern "C" void FUNCNAME();

### Progress (as of 2026-04-02)
Completed batches d3-001 through d3-023.
Last compiled address: 0x7100255b60
Next range to scan: 0x7100255b70 onwards (0x71002b35xx dense cluster is next in CSV)

### Rules
- ONLY create NEW files named src/app/fun_batch_d3_*.cpp
- Do NOT edit any existing files
- Do NOT modify data/functions.csv or tools/
