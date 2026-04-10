# Worker: pool-b

## Model: Opus

## Task: Fix Phase 3 REJECT — resolve 18 STRUCT_REQUIRED violations in StageBase work

## Priority: FIX REVIEW REJECTIONS

## Context
Your Phase 3 diff was rejected (40/100) with 18 STRUCT_REQUIRED violations. The StageBase struct was created but consumer functions still access 3+ offsets via raw hex. Fix by extending StageBase or creating sub-type placeholders.

## What To Do

### Step 1: Run the reviewer to see exact violations
```bash
python tools/review_diff.py pool-b
```

### Step 2: For each STRUCT_REQUIRED violation
The function accesses 3+ offsets on a pointer without a struct. Fix by:
1. Identifying which struct the pointer is (StageBase? A sub-object? A new type?)
2. Adding the missing fields to `include/app/placeholders/StageBase.h` or creating a new placeholder
3. Rewriting the function to use struct field access

### Step 3: Check cast density
Your cast density was 4.1% (fine). Focus on the STRUCT_REQUIRED violations.

### Step 4: Re-run reviewer
```bash
python tools/review_diff.py pool-b
```
Must have zero REJECT violations before committing.

## Rules
- Cast density must stay under 10%
- Create placeholder structs for any unknown types in `include/app/placeholders/`
- Log new placeholders in `data/undefined_types.md`

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
