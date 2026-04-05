# Worker: pool-d

## Model: Opus

## Task: Types-first HARD decomp — SoundModule + CameraModule + KineticModule functions

Decomp HARD-tier functions that access SoundModule (+0x148), CameraModule (+0x60), or KineticModule (+0x68).

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. Filter to functions touching your modules via Ghidra
3. Write idiomatic C++ using struct dispatch
4. Build and verify

### Output: src/app/fun_typed_d_002.cpp onward (continue numbering)

### Rules
- Use struct field access, no raw offsets
- No Ghidra paste, no naked asm
- 3-attempt limit
- ONLY create src/app/fun_typed_d_*.cpp
