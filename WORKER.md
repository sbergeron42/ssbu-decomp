# Worker: pool-a

## Model: Opus

## Task: Build PLT post-processor tool and replace 2,073 naked asm PLT stubs with real C++

The 2,073 functions in fun_region_039.cpp are currently naked asm because the compiler emits GOT-relative indirect calls instead of the NX ADRP+LDR+ADD+BR pattern. Build a post-processing tool that patches the compiler output to match.

### Phase 1: Build tools/fix_plt_stubs.py
A post-processing script (like fix_movz_to_orr.py) that:
1. Scans .o files for GOT-relative call sequences (adrp+ldr via GOT, then br)
2. Rewrites them to the NX pattern: ADRP+LDR+ADD+BR using x16/x17
3. The target address is known from the relocation entries in the .o file

Reference existing tools: fix_movz_to_orr.py, fix_prologue.py for the pattern.

### Phase 2: Replace naked asm in fun_region_039.cpp
Once the post-processor works:
1. Replace the 2,073 naked asm functions with real C++ (extern global + function pointer call)
2. Add fix_plt_stubs.py to build.bat post-processing pipeline
3. Verify the post-processed .o bytes match the original

### Rules
- ONLY edit: tools/fix_plt_stubs.py (new), src/app/fun_region_039.cpp, build.bat
- Do NOT edit any other source files
- Do NOT modify data/functions.csv
- Test with cmd /c build.bat && python tools/verify_all.py --summary
