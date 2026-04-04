# Worker: pool-a

## Model: Opus

## Task: Types-first HARD decomp — ControlModule + EffectModule functions

Decomp HARD-tier functions that access ControlModule (+0x48) or EffectModule (+0x140).
Use the recovered struct headers for clean idiomatic code.

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. For each, check Ghidra decompilation — filter to functions touching your modules
3. Write idiomatic C++ using acc->control_module->method() dispatch
4. Build and verify

### Output: src/app/fun_typed_a_001.cpp onward

### Rules
- Use struct field access, no raw offsets
- Write C++ a developer would write, not Ghidra paste
- No naked asm
- 3-attempt limit per function
- ONLY create src/app/fun_typed_a_*.cpp
