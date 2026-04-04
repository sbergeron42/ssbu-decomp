# Worker: pool-c

## Model: Opus

## Task: Types-first HARD decomp — WorkModule + StatusModule + FighterInfo functions

Continue decomping HARD-tier functions that access WorkModule (+0x50), StatusModule (+0x40), or FighterInformation.

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. Filter to functions touching your modules via Ghidra
3. Write idiomatic C++ using struct dispatch
4. Build and verify

### Output: src/app/fun_typed_c_002.cpp onward (continue numbering)

### Rules
- Use struct field access, no raw offsets
- No Ghidra paste, no naked asm
- 3-attempt limit
- ONLY create src/app/fun_typed_c_*.cpp
