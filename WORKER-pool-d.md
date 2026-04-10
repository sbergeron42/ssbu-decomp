# Worker: pool-d

## Model: Opus

## Task: Fix Phase 3 REJECT — reduce reinterpret_cast density from 13% to under 10%

## Priority: FIX REVIEW REJECTIONS

## Context
Your Phase 3 diff was rejected because reinterpret_cast density is 13% (limit: 10%). BossManager struct was created correctly. The remaining casts are in other functions that need placeholder structs.

## What To Do

### Step 1: Run the reviewer to see the density
```bash
python tools/review_diff.py pool-d
```

### Step 2: Find the remaining reinterpret_casts
```bash
git diff master -- src/ | grep '+.*reinterpret_cast'
```

### Step 3: For each cast, create a placeholder struct
If the cast is `reinterpret_cast<SomeType*>(ptr + 0xNN)`, that pointer needs a struct:
1. Create `include/app/placeholders/UnkType_ADDR.h` with the known fields
2. Replace the cast with struct field access
3. Log in `data/undefined_types.md`

### Step 4: Re-run reviewer
```bash
python tools/review_diff.py pool-d
```
Must show cast density under 10% and zero REJECT violations.

## Rules
- Cast density MUST be under 10% — this is the one thing blocking your merge
- Placeholder structs with `unk_0xNN` are fine — they just need to exist
- Log all new placeholders in `data/undefined_types.md`

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
