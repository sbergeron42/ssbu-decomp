# Worker: pool-d

## Model: Sonnet

## Task: HARD tier decomp via Ghidra (0x7100-0x7101 range)

Decomp HARD-tier functions (30-100+ instructions) using Ghidra MCP. These are real game logic — take time to understand them.

### Approach
1. Read data/fun_triage.csv for HARD-tier functions in 0x7100-0x7101 range
2. Use mcp__ghidra__decompile_function_by_address
3. Apply type fixups and use struct headers from include/app/
4. Write readable code with comments where possible
5. Build, verify, commit in batches

### Output files
- Create src/app/fun_hard_d_001.cpp, fun_hard_d_002.cpp, etc.
- Use struct field access (include the headers)
- Add address comments above each function

### Rules
- ONLY create NEW files named src/app/fun_hard_d_*.cpp
- Do NOT edit existing files
- Do NOT modify tools/ or data/
