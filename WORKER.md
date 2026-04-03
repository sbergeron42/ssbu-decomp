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
- Batches 001-027 complete: ~270 functions committed
- Batches 001-008: 80B HARD (8 batches, ~8-12 funcs each)
- Batches 009-010: 80B HARD (2 batches, ~25 funcs each)
- Batches 011-013: 96B HARD (3 batches, ~15-18 funcs each)
- Batch 014: 96B HARD (12 funcs, dtor/encode/ListBase patterns)
- Batches 015-016: 96B and 80B HARD (nn::nex tree dtors, mutex-guarded patterns)
- Batches 017-019: 80B/96B/48B HARD (Key/Buffer dtors, jemalloc, InkPaintModule)
- Batches 020-021: 112B/128B/144B HARD (node walker, bit-buffer, session auth)
- Batch 022: 80B nn::nex interior functions (String dtor, vector ctor, string-clear)
- Batches 023-025: 64B ctors, StationURL, tree-free variants, singleton dispatch
- Batches 026-027: 160B/176B (formatter, vtable, list callbacks), 112B/128B (RndFloat, vfx, GroundModule)
- Remaining: ~300 96B, ~180 80B, ~140 64B, ~130 112B, ~140 128B, plus larger

### Rules
- ONLY create NEW files named src/app/fun_hard_d_*.cpp
- Do NOT edit existing files
- Do NOT modify tools/ or data/
