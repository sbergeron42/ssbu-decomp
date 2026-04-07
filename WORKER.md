# Worker: pool-b

## Model: Opus

## Task: Post-processing gap analysis -- categorize non-matching patterns

## Status: COMPLETE

---

## CRITICAL FINDING: CSV Size Inflation (+1,246 matches)

**21,425 functions** (54% of all 39,635) have inflated sizes in functions.csv
because Ghidra includes `udf #0` alignment padding in the function size.

Stripping trailing UDF padding from CSV sizes flips **1,246 functions from
non-matching to perfect match** in one pass. No code changes needed.

| Metric | Before | After | Delta |
|--------|--------|-------|-------|
| Perfect matches | 3,962 | 5,208 | **+1,246** |
| Still mismatching | 3,845 | 2,599 | -1,246 |

**Script:** `tools/fix_csv_sizes.py` (dry-run with `--dry-run`)
**Action needed:** Orchestrator must run this on master (workers can't touch CSV)

### Root Cause
The original binary uses `udf #0` (0x00000000) as inter-function alignment
padding. Ghidra's auto-analysis includes this padding in function sizes.
The decomp generates correct function bodies but doesn't emit the padding,
so the size comparison fails even though the code matches perfectly.

### Remaining 137 functions with real missing code
7% of the truncated-but-matching population (137 functions) have actual code
after the decomp function ends. These are real missing code paths that need
source-level fixes.

---

## Gap Analysis Report

**Date:** 2026-04-07
**Scope:** All 9,532 decomp symbols in build/ssbu-decomp.elf vs data/main.elf
**Method:** Address-based byte comparison at matching virtual addresses

### High-Level Numbers

| Metric | Count |
|--------|-------|
| Total decomp symbols | 9,532 |
| Placed at original address | 7,807 (81%) |
| Placed at wrong address (skipped) | 1,725 (19%) |
| **Perfect byte match** | **3,962 (50.7% of placed)** |
| **Non-matching** | **3,845 (49.3% of placed)** |
| Non-matching: reloc-only | 6 |
| Non-matching: size differs | 3,713 |
| Non-matching: real codegen | 3,839 |

### Current Project Status

| Quality | Count | Percent |
|---------|-------|---------|
| M (matching) | 7,432 | 18.8% |
| N (non-matching) | 5,793 | 14.6% |
| U (undecompiled) | 26,410 | 66.6% |

---

### Pattern #1: SIZE_DIFF (3,713 functions) -- BIGGEST ISSUE

The decomp compiles to a **different size** than the original. In 3,710 cases,
the decomp is SHORTER (fewer instructions than original). 

**Breakdown:**
- 1,743 functions: overlapping bytes match 100%, just truncated
- 1,970 functions: overlapping bytes also differ

**Root cause:** Many decomp entries compile only the lua_bind tail-call wrapper
(4 instructions / 16 bytes) while the CSV records a larger function at the
same address. The wrapper is correct but the full function body is missing
or compiled separately to a different address.

**Impact:** This is NOT fixable by post-processing. The source code needs to
either include the full function body, or the linker script needs to ensure
the wrapper and impl are placed contiguously.

**Recommendation:** Investigate why 1,743 wrapper functions match perfectly but
are truncated. These may represent easy wins if the impl functions just need
to be linked adjacently.

---

### Pattern #2: CODEGEN_DIFF (10,573 instructions across 1,496 functions, 49%)

Completely different instruction encodings. The decomp generates a different
opcode than the original at the same position.

**Root cause:** Source-level differences. The C++ code compiles to different
machine code than the original. This includes:
- Wrong arithmetic operations (different ALU instructions)
- Different memory access patterns (different load/store sequences)
- Wrong control flow (different comparison or branch logic)

**Impact:** Not fixable by post-processing. Requires source-level rewrites.

**Recommendation:** These functions need manual decomp review. The source code
doesn't match the original's compiled output.

---

### Pattern #3: REORDER_WITH_BRANCH (6,789 instructions across 849 functions, 31%)

Instructions are reordered, with at least one branch/ADRP mixed in.
fix_insn_reorder.py is already applied but doesn't catch all cases.

**Root cause:** NX Clang schedules instructions differently around branches.
The existing fix_insn_reorder.py handles same-instruction reordering, but
when a branch instruction is involved, the rewrite requires understanding
branch target semantics (can't naively swap a branch with a data op).

**Impact:** Partially addressable. 103 functions have clean SWAP_PAIRS
(adjacent instructions simply swapped). The fix_insn_reorder.py script
should already handle these; the remaining cases involve non-adjacent swaps
or swaps crossing branch boundaries.

**Recommendation:** Investigate why fix_insn_reorder.py misses these.
Possible improvements:
1. Allow swaps across branch instructions when the branch target doesn't
   change (the instruction after a branch is the fall-through target)
2. Handle window sizes > 2 for multi-instruction permutations
3. Expand the match database with more original binary patterns

---

### Pattern #4: REG_ALLOC (2,399 instructions across 877 functions, 11%)

Correct instructions, but different register choices. Same opcode class
(e.g., both are `ldr`), but different Rd/Rn/Rm fields.

**Root cause:** Upstream Clang 8.0.0 and NX Clang make different register
allocation decisions. fix_x8_regalloc.py handles the specific x8/x9 vtable
dispatch pattern, but general register allocation differences are not
patchable.

**Impact:** Not fixable by post-processing (except the x8/x9 special case).
Would require a register renaming pass that understands liveness, which is
essentially a decompiler.

**Recommendation:** Accept as a fundamental compiler divergence. Focus effort
on source-level matching instead.

---

### Pattern #5: RELOC (1,410 instructions across 893 functions, 6%)

Different branch/ADRP offsets. The decomp generates the same instruction type
(e.g., both are `bl`) but to a different target address.

**Root cause:** Linker places functions/data at different offsets than original.
PLT stubs may also differ.

**Note:** fix_plt_stubs.py is currently only applied to fun_region_039.o.
Expanding it to all .o files may fix many RELOC mismatches.

**Impact:** Partially fixable.

**Recommendation:**
1. **Expand fix_plt_stubs.py to all .o files** (currently one file only)
2. Fix linker script to place functions at original addresses (addresses
   the 1,725 mis-placed functions too)

---

### Pattern #6: MOVZ_ORR (29 instructions across 13 functions, <1%)

movz vs orr-with-wzr encoding mismatch. fix_movz_to_orr.py is applied to
all .o files but 13 functions still have this pattern.

**Root cause:** Edge cases that fix_movz_to_orr.py doesn't handle. Possibly:
- 64-bit movz (X-register variant)
- Different immediate encodings
- Interactions with other post-processing scripts

**Impact:** Small but trivially fixable.

**Recommendation:** Debug the 13 remaining functions to find the edge case.
Likely a width or shift-amount check in fix_movz_to_orr.py.

---

### Pattern #7: PROLOGUE_REORDER (74 functions)

Prologue instructions are the SAME set but in different order.
fix_prologue_sched.py is applied but these 74 survive.

**Root cause:** Edge cases in prologue scheduling. Possibly non-standard
prologue patterns that fix_prologue_sched.py doesn't recognize.

**Recommendation:** Check if these 74 functions have non-standard prologues
(e.g., 3+ callee-saved register pairs, mixed int/float saves).

---

## Existing Fix Script Coverage

| Script | Applied To | Pattern | Still Remaining |
|--------|-----------|---------|-----------------|
| fix_movz_to_orr.py | all .o | movz/orr encoding | 13 funcs |
| fix_prologue_sched.py | all .o | prologue scheduling | 74 funcs |
| fix_epilogue.py | batch .o only | epilogue scheduling | unknown |
| fix_return_width.py | all .o | w0/x0 return width | unknown |
| fix_x8_regalloc.py | all .o | x8/x9 vtable scratch | 877 funcs (general) |
| fix_insn_reorder.py | all .o | instruction reorder | 849 funcs |
| fix_plt_stubs.py | **fun_region_039.o ONLY** | PLT stub format | 893 funcs |

---

## Top Actionable Recommendations (ranked by impact)

### 1. Expand fix_plt_stubs.py to ALL .o files (est. 100-500 flips)
Currently only applied to one file. RELOC is 6% of all mismatched
instructions and 893 functions have relocation differences. Many may be
PLT stub mismatches that would be fixed by wider application.

**Effort:** Change one line in build.bat
**Risk:** Low (script already proven on one file)

### 2. Expand fix_epilogue.py to ALL .o files (est. 50-200 flips)
Currently only applied to batch files. Non-batch source files likely have
the same epilogue scheduling issues.

**Effort:** Change one line in build.bat
**Risk:** Low

### 3. Fix linker script for 1,725 mis-placed functions (est. 200-500 flips)
19% of decomp symbols are placed at wrong addresses. If they match bytes
but are at the wrong address, fixing placement converts them to M instantly.

**Effort:** Medium (linker script work)
**Risk:** Medium

### 4. Debug 13 MOVZ_ORR survivors (est. 13 flips)
Small count but trivially fixable by finding the edge case in
fix_movz_to_orr.py.

**Effort:** Small (debug one script)
**Risk:** Low

### 5. Investigate 74 prologue survivors
Check if fix_prologue_sched.py misses specific patterns.

**Effort:** Small-medium
**Risk:** Low

---

## Tool Created

`tools/gap_analysis.py` -- Address-based comparison tool that:
1. Extracts all symbols from decomp ELF
2. Matches them to CSV entries by address
3. Compares bytes against original ELF
4. Classifies each mismatch instruction into categories
5. Produces ranked pattern report

Run with: `python tools/gap_analysis.py`

---

## Key Bug Found: categorize_mismatches.py Address Lookup

The existing `tools/categorize_mismatches.py` has a name-matching bug where
short function names (extracted from mangled names) map to the wrong CSV entry.
For example, `AbsorberModule__is_turn_impl` (the lua_bind wrapper) gets mapped
to the implementation function's address (1,344 bytes), producing nonsense
byte comparisons. The address-based approach in gap_analysis.py avoids this.
