# Worker: pool-a

## Model: Opus

## Task: Types-first HARD decomp — AbsorberModule + AreaModule + ArticleModule functions

Decomp HARD-tier functions that access these modules. All structs are recovered in include/app/modules/.

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. Filter to functions touching your modules via Ghidra
3. Write idiomatic C++ using struct dispatch — write code a developer would write
4. Build and verify
5. Use confidence-tagged derivation chains on any new struct fields discovered

### Output: src/app/fun_typed_a_002.cpp onward

### Rules
- Use struct field access, no raw offsets, no Ghidra paste, no naked asm
- 3-attempt limit per function
- ONLY create src/app/fun_typed_a_*.cpp
- Save Ghidra results to /tmp/ghidra_results.txt
- Build once with tee, grep the file
