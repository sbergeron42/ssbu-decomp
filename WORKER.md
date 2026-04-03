# Worker: pool-d

## Model: Sonnet

## Task: Batch decomp MEDIUM FUN_* (all ranges, continued) via Ghidra pipeline

Continue batch-decompiling MEDIUM-tier functions across all address ranges.

### Batch pipeline workflow
1. Pick 20-30 uncompiled MEDIUM functions from data/fun_triage.csv
2. For each, call mcp__ghidra__decompile_function_by_address(address)
3. Apply type fixups: undefined8->u64, undefined4->u32, undefined2->u16, byte->u8, uint->u32, int->s32, long->s64, ulong->u64, bool->u8
4. Skip functions with WARNING comments or broken decompilation
5. Write to a single .cpp file with // 0x71XXXXXXXX address comments
6. Build and verify, fix compile errors, commit, repeat

### Output files
- Create src/app/fun_batch_d4_001.cpp, fun_batch_d4_002.cpp, etc.
- Do NOT put functions in any namespace (global functions)
- Forward-declare unknown called functions as extern "C" void FUNCNAME();

### Rules
- ONLY create NEW files named src/app/fun_batch_d4_*.cpp
- Do NOT edit any existing files
- Do NOT modify data/functions.csv or tools/

### Progress
- d4-001: 19 functions, 0x71002bb310–0x710031367c
- d4-002: 6 functions, 0x71002f0f70–0x7100314d50
- d4-003: 14 functions, 0x7100325e50–0x71003cb1b0
- d4-004: 2 functions, 0x71003a0a20–0x71003abd60
- d4-005: 18 functions, 0x71003cfc50–0x7100421d10
- d4-006: 12 functions, 0x7100422720–0x71004af3f0
- d4-007: 10 functions, 0x71004f5750–0x710067e650
- d4-008: 10 functions, 0x7100837d1c–0x7100d12af0
- d4-009: 26 functions, 0x7100000250–0x710013bd08
- d4-010: 24 functions, 0x710007a9d0–0x71000b3d10
- d4-011: 28 functions, 0x7100145ec0–0x71001578e0
- d4-012: 25 functions, 0x7100158070–0x7100194e60
- d4-013: 24 functions, 0x710003a790–0x7100358c20
- d4-014: 22 functions, 0x7100031330–0x7100489e80
- d4-015: 23 functions, 0x710003a4e0–0x7100066040
- d4-016: 21 functions, 0x7100078b00–0x710013c200
- d4-017: 14 functions, 0x7100156720–0x710068d530
- d4-018: 21 functions, 0x710064b730–0x710107dae0
- d4-019: 19 functions, 0x710116b7f0–0x7101d2c6b0
- d4-020: 29 functions, 0x7102000e40–0x7102009f70
- d4-021: 27 functions, 0x710200a300–0x710202c290
- d4-022: 27 functions, 0x710202c4d0–0x710203bdd0
- d4-023: 25 functions, 0x710203dcf0–0x71020628f0
- d4-024: 25 functions, 0x7102065690–0x710206cb80
- d4-025: 20 functions, 0x710202f870–0x7102077ae0
- d4-026: 25 functions, 0x7102077d10–0x7102087140
