# Worker: pool-d

## Model: Sonnet

## Task: Mop up remaining ~800 MEDIUM-tier functions

~800 MEDIUM-tier functions remain uncompiled. Finish them off.

### Efficiency rules (MANDATORY)
- Build once: cmd /c build.bat 2>&1 | tee /tmp/build.txt then grep the file
- Find targets: python tools/next_batch.py --tier MEDIUM --limit 50
- Compare bytes: python tools/compare_bytes.py FUNC_NAME
- Save Ghidra results to /tmp/ghidra_results.txt
- 3-attempt limit per function, then skip or naked asm
- Do NOT edit tools/ or fix infrastructure — report issues and move on

### Output
- Create src/app/fun_med_final_d_001.cpp onward
- Use struct headers from include/app/

### Rules
- ONLY create NEW files named src/app/fun_med_final_d_*.cpp
- Do NOT edit existing files
