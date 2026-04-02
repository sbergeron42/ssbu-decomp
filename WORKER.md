# Worker: pool-a

## Model: Opus

## Task: Fix non-matching functions in fun_batch_a/b files

77 non-matching functions out of 98 compiled. Fix codegen to byte-match original.

### Common fixes
- Wrong types: swap u32/s32, u8/bool, void*/u64
- Wrong return type: void vs u64 vs void*
- Instruction scheduling: reorder independent stores/loads
- Prologue mismatch: use asm("") barrier with MATCHING_HACK_NX_CLANG

### Workflow
1. Run python tools/verify_all.py to get the non-matching list
2. Filter to functions in YOUR files only
3. Use python tools/show_diff.py func_name for instruction-level diff
4. Fix, rebuild (cmd /c build.bat), re-verify, commit in batches

### Rules
- ONLY edit: src/app/fun_batch_a_*.cpp, src/app/fun_batch_b_*.cpp
- Do NOT edit any other files
- Do NOT modify data/functions.csv or tools/
