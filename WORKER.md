# Worker: pool-d

## Model: Opus

## Task: Fix non-matching functions in fun_medium*, fun_region*, and fun_easy* files

5,101 non-matching functions need codegen fixes. This pool handles medium, region, and easy files.

### Workflow
1. Run python tools/verify_all.py to get the non-matching list
2. Filter to functions in YOUR files only
3. Use python tools/show_diff.py func_name for instruction-level diff
4. Common fixes: swap u32/s32, u8/bool, void*/u64, add asm("") barriers
5. Rebuild (cmd /c build.bat), re-verify, commit in batches of 10-20

### Rules
- ONLY edit: src/app/fun_medium_*.cpp, src/app/fun_region_*.cpp, src/app/fun_easy_*.cpp
- Do NOT edit any other files
