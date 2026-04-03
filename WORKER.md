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

### Progress (2026-04-03)
- Batches 001-014 complete: 213 functions committed
- Batches 001-008: 80B HARD (8 batches, ~8-12 funcs each)
- Batches 009-010: 80B HARD (2 batches, ~25 funcs each)
- Batches 011-013: 96B HARD (3 batches, ~15-18 funcs each)
- Batch 014: 96B HARD (12 funcs, dtor/encode/ListBase patterns)
- Remaining: 320 96B, 222 80B, plus larger sizes

### Rules
- ONLY create NEW files named src/app/fun_hard_d_*.cpp
- Do NOT edit existing files
- Do NOT modify tools/ or data/
