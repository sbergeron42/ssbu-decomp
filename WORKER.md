# Worker: pool-e

## Model: Opus

## Task: Decomp remaining EASY + HARD tree-delete functions

### Completed
- All DamageModule/GroundModule lua_bind wrappers were already compiled (CSV stale)
- MEDIUM tier: 0 remaining (all compiled)
- Compiled 36 functions across 3 files:
  - `src/app/fun_typed_e_001.cpp` — 6 EASY stubs (noop, memset_s, field accessor, tail calls)
  - `src/app/fun_typed_e_002.cpp` — 8 HARD tree deletes (patterns A/B/C)
  - `src/app/fun_typed_e_003.cpp` — 22 HARD tree deletes (patterns A/B/D)
- All 36 verified against binary (only branch relocations differ, expected for .o)

### Notes
- HARD tier is ~9000 destructor/tree-delete functions, not module accessor functions
- Tree-delete Pattern A (recurse left/right + delete) is the most common 64-byte HARD pattern
- Pattern D (two-param tree delete) uses alternate delete function FUN_71001b1870
- 47 EASY targets remain but most are 4-byte NOPs or complex internal functions

### Rules
- ONLY create NEW files named src/app/fun_typed_e_*.cpp
- Use struct field access from include/app/modules/
- Do NOT copy-paste Ghidra pseudocode
- Do NOT use naked asm
