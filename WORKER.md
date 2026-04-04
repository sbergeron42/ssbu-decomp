# Worker: pool-b

## Model: Sonnet

## Task: HARD tier decomp (0x7100-0x7101 range)

Decomp HARD-tier functions (30-100+ instructions) using Ghidra MCP.

### Efficiency rules (MANDATORY)
- Build once: cmd /c build.bat 2>&1 | tee /tmp/build.txt then grep the file
- Find targets: python tools/next_batch.py --tier HARD --range 0x7100 --limit 30
- Compare bytes: python tools/compare_bytes.py FUNC_NAME
- Save Ghidra results to /tmp/ghidra_results.txt
- 3-attempt limit per function, then skip or naked asm
- Do NOT edit tools/ or fix infrastructure — report issues and move on

### Output
- Create src/app/fun_hard_b_001.cpp onward
- Use struct headers from include/app/
- Add // 0x71XXXXXXXX address comments

### Rules
- ONLY create NEW files named src/app/fun_hard_b_*.cpp
- Do NOT edit existing files
