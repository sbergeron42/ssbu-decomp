# SIZE_DIFF Investigation Report — Pool B

## Summary

**2,286 functions** have a size mismatch between our decomp output and the original binary. They fall into 6 root causes, with **3 dominant patterns** accounting for 72% of all cases.

## Root Cause Classification

| Root Cause | Count | % | Fixable? |
|---|---|---|---|
| WRONG_CODE | 829 | 36% | Rewrite from Ghidra |
| WRONG_STUB | 550 | 24% | Rewrite from Ghidra |
| O0_MISMATCH | 277 | 12% | `__attribute__((optnone))` |
| STUB_TRUNCATED | 257 | 11% | CSV size fix or decomp body |
| PARTIAL_MATCH | 219 | 9% | Extend source code |
| DECOMP_LONGER | 154 | 6% | Linker thunk artifacts |

## Detailed Analysis

### 1. WRONG_CODE (829 functions, 36%)

Our source compiles to **different AND shorter** code than the original. The overlapping bytes don't match — our source is fundamentally wrong for these addresses.

**Example**: `ControlModule__reset_down_stand_fb_kind_impl` at 0x7102000e80
- Our decomp: 4 instructions — simple vtable dispatch (`ldr; ldr; ldr; br`)
- Original: 408 bytes — complex function with L2C argument parsing, string lookups, assertion calls

**Root cause**: Many lua_bind `_impl` functions were decomped as simple vtable forwards, but the originals include L2C argument validation/conversion before the actual module call. Our source only has the dispatch, missing the validation body.

**Fix**: Rewrite from Ghidra decompilation. These need actual function bodies, not one-liner stubs.

### 2. WRONG_STUB (550 functions, 24%)

Our source produces a tiny stub (<=16 bytes) that doesn't match even the first few bytes of the original. Our code is completely wrong.

**Example**: `FUN_710003bc80` at 0x710003bc80
- Our decomp: 16 bytes
- Original: 32 bytes, different code entirely

**Root cause**: Batch-generated stubs that were guesses at the function behavior, never verified against the binary.

**Fix**: Rewrite from Ghidra. These should be removed from the codebase or replaced with correct implementations.

### 3. O0_MISMATCH (277 functions, 12%)

Our -O2 code is **logically correct** (same operations) but the original was compiled at **-O0**. The -O0 pattern is unmistakable: explicit stack frame allocation, store parameters to stack, then reload them.

**Example**: `FUN_7103930140` — simple getter `return *ptr;`
- Our -O2: `ldr x0, [x0]; ret` (8 bytes)
- Original -O0: `sub sp,#16; str x0,[sp,#8]; ldr x8,[sp,#8]; ldr x0,[x8]; add sp,#16; ret` (24 bytes)

**Example**: `FUN_710395d8d0` — wrapper `FUN_710395cc80(p, 0, 1);`
- Our -O2: `mov w1,wzr; orr w2,#1; b target` (12 bytes, tail call)
- Original -O0: Full stack frame with store-reload pattern, `bl` instead of `b` (108 bytes)

**Location**: Concentrated in the **0x71039xxxxx** region (53% of SIZE_DIFF functions there). This is fighter-specific code compiled with debug flags.

**Fix**: Apply `__attribute__((optnone))` to these functions. This is already proven to work for -O0 stubs (per `feedback_optnone_technique.md`). The 277 functions are a quick win — same source code, just needs the attribute.

### 4. STUB_TRUNCATED (257 functions, 11%)

Our stub is correct (bytes match!) but the CSV size includes extra bytes beyond our function. Two sub-patterns:

**A. Ghidra over-sized the function**: `GetFileFast` at 0x7100042bf0 — original is just `ret` (4 bytes), but CSV says 1380. Ghidra lumped padding + the next function into this one's size.

**B. Thunk + target lumped together**: `AttackAbsoluteData__store_l2c_table_impl` — our 16-byte thunk matches, but Ghidra counts the entire target function body (168 more bytes) as part of this function.

**Fix**: For type A, fix CSV sizes. For type B, this may be correct Ghidra behavior (the thunk IS a different entry point into the same function body), meaning our source needs to include the body, not just forward.

### 5. PARTIAL_MATCH (219 functions, 9%)

Our code matches the start of the original but is incomplete — we're only decomping part of the function.

**Example**: `BossManager__notify_on_boss_dead_impl` — our 220-byte output matches the first 220 bytes perfectly, but the original has 3248 bytes total.

**Fix**: Extend the source code. These are partially correct — the matching prefix proves our approach is right, we just need to finish the implementation.

### 6. DECOMP_LONGER (154 functions, 6%)

Our decomp is **larger** than the original. Two sub-patterns:

**A. Linker thunks**: Our build generates `__AArch64AbsLongThunk_*` entries (16 bytes: `ldr x16,#8; br x16; .quad addr`) alongside our function, inflating the symbol size.

**B. Codegen difference**: `FUN_71000c0790` — we use 4 instructions (GOT indirection: `adrp; ldr; ldrb; ret`) but original uses 3 (direct: `adrp; ldrb; ret`). Our PIC code adds an extra load.

**Fix**: Type A is a build system artifact — filter thunks from size comparison. Type B needs source-level fixes (e.g., direct global access instead of pointer indirection).

## Key Metrics

- **Total SIZE_DIFF bytes missing**: 1,857,780 bytes (our 100,772 vs original 1,958,552)
- **Coverage of SIZE_DIFF original bytes**: 5.1%
- **50% of SIZE_DIFF functions** have decomp output <= 16 bytes (tiny stubs)
- **Largest single gap**: `pthread_cond_destroy` — 1,048,552 bytes (CSV error — clearly wrong size)

## Proposed Actions (Priority Order)

1. **O0_MISMATCH (277 funcs)** — Quickest win. Add `__attribute__((optnone))` to functions in the 0x71039x region. Same source code, just different compilation flags. Could be done in bulk.

2. **STUB_TRUNCATED type A (CSV errors)** — Fix function sizes in `functions.csv` where Ghidra clearly over-estimated. Write a script to detect: if original function has a `ret` instruction before the CSV-reported end, and after the `ret` there's padding (zeros) or a new prologue, the CSV size is wrong.

3. **PARTIAL_MATCH (219 funcs)** — Low-hanging fruit. Our code is partially correct. Extend from Ghidra decompilation.

4. **WRONG_CODE + WRONG_STUB (1,379 funcs)** — Largest category but most work. Requires full rewrite from Ghidra. Consider batch-processing with better Ghidra codegen.

5. **DECOMP_LONGER (154 funcs)** — Filter linker thunks from gap analysis to get accurate counts. Investigate PIC codegen differences.

## Address Region Correlation

| Region | SIZE_DIFF Count | Dominant Pattern |
|---|---|---|
| 0x7100xxxxxxxx | 622 | WRONG_CODE/WRONG_STUB (62%) |
| 0x7101xxxxxxxx | 79 | WRONG_CODE (82%) |
| 0x7102xxxxxxxx | 907 | WRONG_STUB (95%) — lua_bind area |
| 0x7103xxxxxxxx | 518 | O0_MISMATCH (53%) — fighter code |
