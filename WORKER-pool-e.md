# Worker: pool-e

## Model: Opus

## Task: Delete or rewrite Ghidra paste files (fun_med_final_*, fun_batch_d_001, fun_batch_c_016)

## Priority: QUALITY CLEANUP — remove paste, keep only typed code

## Context
These files are Ghidra paste with high default variable counts and zero structural value. Same treatment as Phase 2: delete functions that are pure paste, rewrite ones that can be typed.

## File Territory
- `src/app/fun_med_final_c_002.cpp` (546 Ghidra vars, 123 offsets)
- `src/app/fun_med_final_c_001.cpp` (308 Ghidra vars, 129 offsets)
- `src/app/fun_batch_c_016.cpp` (283 Ghidra vars, 81 offsets)
- `src/app/fun_batch_d_001.cpp` (313 Ghidra vars, 39 offsets)
- `src/app/res_medium_helpers.cpp` (292 Ghidra vars, 110 offsets)
- `src/app/fun_med_final_b_012.cpp` (196 Ghidra vars, 150 offsets)

## What To Do
For each file:
1. Check `data/functions.csv` — are ANY functions in this file verified (quality=M)?
2. If zero verified: **delete the entire file** (same as Phase 2 paste deletion)
3. If some verified: keep those functions, delete the rest, rewrite kept functions with struct access
4. For functions worth keeping: identify the struct types, create placeholders, rewrite with typed access
5. NO Ghidra variable names in any kept code

## Self-Check
```bash
python tools/review_diff.py pool-e
python tools/progress.py  # verify no regression in matched count
```

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
