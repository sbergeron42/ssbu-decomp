# Worker: pool-d

## Model: Opus

## Task: Test types-first HARD decomp — AttackModule + MotionModule functions

Now that structs are recovered, test HARD decomp with types.
Target functions that access AttackModule (+0xA0) or MotionModule (+0x88).

### Approach
1. python tools/next_batch.py --tier HARD --limit 30
2. Filter to functions that access AttackModule or MotionModule
3. Write idiomatic C++ using the struct headers
4. Track throughput: functions per hour, match rate, build cycles per function

### Output
- src/app/fun_typed_d_001.cpp onward
- Report throughput numbers in commit messages

### Rules
- ONLY create NEW files named src/app/fun_typed_d_*.cpp
- Use struct field access from include/app/modules/
- Do NOT copy-paste Ghidra pseudocode
- Do NOT use naked asm
