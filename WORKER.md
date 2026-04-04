# Worker: pool-e

## Model: Opus

## Task: Types-first HARD decomp — ShieldModule + DamageModule + HitModule functions

Decomp HARD-tier functions that access ShieldModule (+0x100), DamageModule (+0xA8), or HitModule (+0xB0).

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. Filter to functions touching your modules via Ghidra
3. Write idiomatic C++ using struct dispatch
4. Build and verify

### Output: src/app/fun_typed_e_004.cpp onward (continue numbering)

### Rules
- Use struct field access, no raw offsets
- No Ghidra paste, no naked asm
- 3-attempt limit
- ONLY create src/app/fun_typed_e_*.cpp
