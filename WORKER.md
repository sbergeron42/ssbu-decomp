# Worker: pool-c

## Model: Opus

## Task: Fix 2,395 non-matching functions using auto_fix_nonmatching.py + manual fixes

2,395 functions compile but do not byte-match. Use the auto-fixer tool first, then manually fix what it cannot.

### Step 1: Run the auto-fixer
    python tools/auto_fix_nonmatching.py --apply --limit 100
Review what it changed, rebuild, verify. If it works, run with higher limits.

### Step 2: Manual fixes for remaining
For functions the auto-fixer cannot handle:
1. Run python tools/verify_all.py to get the non-matching list
2. Use python tools/show_diff.py func_name for instruction-level diff
3. Common fixes: swap u32/s32, u8/bool, void*/u64, add asm("") barriers
4. Rebuild and verify after each batch

### Rules
- Edit any src/app/*.cpp file EXCEPT modules/ (pool-a and pool-b territory)
- Can edit tools/auto_fix_nonmatching.py to improve it
- Do NOT modify data/functions.csv
- Do NOT edit include/ headers
- NEVER reduce verified count
