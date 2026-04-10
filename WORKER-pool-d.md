# Worker: pool-d

## Model: Opus

## Task: Phase 2 — Rewrite net_frame_exchange.cpp with typed struct access

## Priority: QUALITY REWRITE (not new decomp)

## Context
This file is 1,338 lines of Ghidra paste with 847 default variable names. It compiles but has zero verified matches and zero structural value. Your job is to rewrite it using the existing networking types.

## File Territory
- `src/app/networking/net_frame_exchange.cpp` (REWRITE)
- `include/app/LDNSession.h` (extend as needed)
- `include/app/CSSState.h` (extend as needed)
- Create new headers in `include/app/networking/` if needed

## Available Struct Headers
- `include/app/LDNSession.h` — LDN transport session, enums (~15 fields)
- `include/app/CSSState.h` — CSS player name, serialize buffer, related types

## What To Do

### Step 1: Read the existing networking headers
Read `include/app/LDNSession.h` and `include/app/CSSState.h` first. Also read `src/app/networking/net_session.cpp` and `src/app/networking/state_serialize.cpp` to understand how other networking files are structured.

### Step 2: Identify the frame exchange structs
The net_frame_exchange file deals with per-frame game state synchronization. Key patterns to look for:
- Frame counters, sequence numbers
- Input buffers, controller state serialization
- Rollback/resync state
- Player slot indexing

Define structs for the data types this file operates on.

### Step 3: Rewrite with struct access
For each function:
1. Identify which struct type is the first parameter
2. Map the offset accesses to struct fields
3. Rewrite with typed field access
4. Name fields based on usage patterns (frame counts, input data, sync flags)

### Step 4: Delete functions you can't properly type
DELETE opaque paste rather than keeping it. Honest gaps > fake progress.

## Rules
- **Every named field needs a `[derived:]` or `[inferred:]` comment**
- **NO Ghidra variable names** in final code (auto-REJECT)
- **NO raw vtable dispatch** (auto-REJECT)
- **Tag confidence levels**: `[confirmed]` for .dynsym-derived, `[inferred]` for usage-pattern-derived
- **Cross-reference with other networking files** for consistent struct definitions

## Self-Check (MANDATORY before committing)
```bash
python tools/review_diff.py pool-d
```
Must have zero REJECT violations.

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
