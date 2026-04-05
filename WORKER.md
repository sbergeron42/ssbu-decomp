# Worker: pool-b

## Model: Opus

## Task: Fix compare_bytes.py regex bug + types-first HARD decomp

### Phase 1 (quick): Fix the regex bug in tools/compare_bytes.py
The regex that extracts addresses from mangled function names fails when the name ends in hex chars and the signature starts with f (float param). Fix and test.

### Phase 2: Types-first HARD decomp — CaptureModule + CatchModule + GrabModule functions
Decomp HARD-tier functions accessing these modules.

### Output: src/app/fun_typed_b_002.cpp onward

### Rules
- Phase 1: CAN edit tools/compare_bytes.py only
- Phase 2: ONLY create src/app/fun_typed_b_*.cpp
- Use struct field access, no raw offsets, no Ghidra paste, no naked asm
- 3-attempt limit per function
