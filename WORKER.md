# Worker: pool-b

## Model: Opus

## Task: Fix non-matching functions in fun_batch_b, fun_batch_c, and fun_batch_d files

~1,992 functions compile but do not byte-match. Fix codegen in your assigned files.

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
- ONLY edit: src/app/fun_batch_c_*.cpp, src/app/fun_batch_d_*.cpp
- Do NOT edit any other files
- Do NOT modify data/functions.csv or tools/
