# Worker: pool-b

## Model: Opus

## Task: Clean up fighter_motion.cpp + fighter_core.cpp — typed module access

## Priority: QUALITY CLEANUP

## Context
`fighter_motion.cpp` (279 casts, 447 offsets) and `fighter_core.cpp` (143 casts, 565 offsets) are the #2 and #3 dirtiest files. Module headers exist for all the modules they use.

## File Territory
- `src/app/fighter_motion.cpp` (CLEANUP)
- `src/app/fighter_core.cpp` (CLEANUP)
- `include/app/modules/*.h` (extend if needed)
- `include/app/placeholders/` (create placeholders for non-module types)

## What To Do
Same pattern as all cleanup: replace raw casts with typed module access, create placeholder structs for unknown types, keep cast density under 10%.

## Do NOT
- Delete, add, or rename functions — internal cleanup only

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-b
```
