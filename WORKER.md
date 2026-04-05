# Worker: pool-b

## Model: Opus

## Task: Types-first HARD decomp — LinkModule + PhysicsModule functions

Decomp HARD-tier functions that access LinkModule (+0xD0) or PhysicsModule (+0x80).

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. Filter to functions touching your modules via Ghidra
3. Write idiomatic C++ using struct dispatch
4. Build and verify

### Output: src/app/fun_typed_b_001.cpp onward

### Rules
- Use struct field access, no raw offsets
- No Ghidra paste, no naked asm
- 3-attempt limit
- ONLY create src/app/fun_typed_b_*.cpp
