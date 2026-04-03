# Worker: pool-d

## Model: Sonnet

## Task: Batch MEDIUM decomp (0x7100-0x7101 range, continued)

Continue batch-decompiling MEDIUM-tier functions. Now use the struct headers in include/app/ for better readability.

### Status: Deduplication complete (2025-04-03)
Fixed 600+ duplicate symbol definitions across the following files:
- Deleted: fun_batch_d4_009.cpp, fun_batch_d5_043-045.cpp (100% redundant)
- Cleaned: fun_batch_d4_010-017, d4_020-026, fun_batch_e_002-006
- Cleaned: fun_batch_test, fun_easy_000, fun_easy_004
- Cleaned: fun_medium_000-022, fun_medium_abort
- Fixed: gen_linker_script.py (removed 0x7200000000 metadata placement)
- Fixed: verify_local.py (fallback flat layout for Windows mmap limit)
Build now: 2217/2461 checked functions byte-identical (90.1%)

### Batch pipeline workflow
1. Pick 20-30 uncompiled MEDIUM functions from data/fun_triage.csv in 0x7100-0x7101 range
2. For each, call mcp__ghidra__decompile_function_by_address(address)
3. Apply type fixups (undefined8->u64, uint->u32, etc.)
4. Where possible, use BattleObjectModuleAccessor fields instead of raw offsets
5. Write to src/app/fun_batch_d5_NNN.cpp with // 0x71XXXXXXXX address comments
6. Build, verify, commit, repeat

### Using structs
If a function takes BattleObjectModuleAccessor* as first param:
    #include "app/BattleObjectModuleAccessor.h"
    void func(app::BattleObjectModuleAccessor* acc) {
        auto* m = acc->camera_module;  // instead of *(void**)((u8*)acc + 0x60)
    }

### Rules
- ONLY create NEW files named src/app/fun_batch_d5_*.cpp
- Do NOT edit any existing files (exception: cleanup of duplicates as done above)
- Do NOT modify data/functions.csv
