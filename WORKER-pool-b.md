# Worker: pool-b

## Model: Opus

## Task: Phase 2 — Rewrite res_pipeline_medium.cpp with typed struct access

## Priority: QUALITY REWRITE (not new decomp)

## Context
This file is 1,876 lines of Ghidra paste with 1,378 default variable names. It compiles but has zero verified matches and zero structural value. Your job is to rewrite it using the existing resource service types in `include/resource/`.

## File Territory
- `src/resource/res_pipeline_medium.cpp` (REWRITE)
- `include/resource/` (extend existing headers as needed)

## Available Struct Headers
- `include/resource/ResServiceNX.h` — resource service singleton, file loading
- `include/resource/LoadedArc.h` — ARC archive structures (ARCropolis-derived names)
- `include/resource/PathResolver.h` — filepath/directory handle resolution
- `include/resource/containers.h` — FixedString, vector-like containers
- `include/resource/FixedString.h` — FixedString<N> template
- `include/resource/Fiber.h` — fiber/coroutine context
- `include/resource/LZ4Frame.h` — LZ4 frame decompression

## What To Do

### Step 1: Read and understand the existing headers
Read ALL headers in `include/resource/` first. Understand what types are already available before touching the source.

### Step 2: Identify the functions
The file has ~50-80 functions. For each one:
1. Read the Ghidra paste version
2. Identify which struct types are being accessed (by offset patterns)
3. Rewrite using struct field access from the headers
4. If a needed struct doesn't exist, define it in the appropriate header with `unk_0xNN` for unknown fields

### Step 3: Rename Ghidra variables
After struct access is in place, rename `uVar1`, `lVar2` etc. to meaningful names.

### Step 4: Delete functions you can't properly type
If a function is too opaque to rewrite with struct access (no recognizable patterns), DELETE it rather than keeping the paste. An honest gap is better than fake progress.

## Rules
- **Every named field needs a `[derived:]` or `[inferred:]` comment**
- **Use ARCropolis community names** where available (tag with `[derived: ARCropolis]`)
- **0xFFFFFF sentinel** = invalid index, use named constant
- **OOM retry pattern**: `alloc(); if (!ptr && handler) { handler->retry(); alloc(); }` — factor into helper
- **NO Ghidra variable names** in final code (uVar, lVar, plVar = auto-REJECT)
- **NO raw vtable dispatch** — use typed wrappers or add them to headers

## Self-Check (MANDATORY before committing)
```bash
python tools/review_diff.py pool-b
```
Must have zero REJECT violations. The reviewer now rejects raw vtable dispatch too.

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
