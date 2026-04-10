# Worker: pool-b

## Model: Opus

## Task: Decomp remaining EASY targets — leaf functions and small stage/camera functions

## Priority: NORMAL

## Context
Phase 3 REJECT fix is COMPLETE (score 100/100, 0 violations). Now working through
remaining EASY-tier uncompiled functions — mostly 12-16 byte leaf functions (getters,
setters, tail-calls) plus a few 200-600 byte functions.

## File Territory
- `src/app/camera_functions.cpp` — camera/stage leaf functions
- `include/app/placeholders/Stage*.h` — stage subclass structs

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
