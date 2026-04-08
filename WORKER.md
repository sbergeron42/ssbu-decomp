# Worker: pool-a

## Model: Opus

## Task: SIZE_DIFF investigation — why are 1,743 functions truncated but matching?

### Background
Pool B's gap analysis found 1,743 functions where every compiled byte matches the original binary perfectly, but the compiled function is SHORTER than the CSV expects. If we can figure out why, one build/tooling fix could add ~1,700 verified.

### Investigation steps
1. Pick 10 SIZE_DIFF functions from different source files
2. For each: compare the .o symbol size vs the CSV expected size
3. Examine what bytes follow our function in the original binary — are they:
   a. Another function that should be in the same compilation unit?
   b. An inlined function body?
   c. Padding/alignment?
   d. Part of the same function that our source doesn't capture?
4. Check if the "missing" bytes are compiled elsewhere in another .o file
5. Look for patterns: are these all lua_bind wrappers followed by impl bodies?

### Tools
```
# Check a specific function's sizes:
python tools/compare_bytes.py FUN_name

# Disassemble the original to see what follows:
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=ADDR --stop-address=END data/main.elf

# Check CSV entry:
grep FUN_name data/functions.csv
```

### Deliverable
A report in WORKER.md: what causes SIZE_DIFF, and a proposed fix (script, build change, or linker config).

---

## SIZE_DIFF Investigation Report

### Executive Summary

**Root cause: Ghidra overestimates function sizes.** 15,289 of 39,635 CSV entries (38.6%) have inflated sizes, totaling ~39 MB of over-counted bytes out of ~60 MB .text. Ghidra's function boundary analysis merges alignment padding and adjacent function code into the preceding function.

**Impact on verification:**
- 616 compiled functions have all bytes matching but CSV says they're bigger
- 548 of those are **already verified** by verify_all.py (which uses decomp size, not CSV size)
- Only 68 would become newly verified by fixing CSV sizes
- The original "~1,700" estimate was from an older build state; current number is 616

**The real win is data quality, not verification count.** Fixing CSV sizes gives accurate function boundaries for the entire binary — essential for future decomp targeting, progress tracking, and gap analysis accuracy.

### Evidence

#### 1. What the "extra" bytes contain

For the 616 SIZE_DIFF functions where all decomp bytes match:

| Pattern | Count | Description |
|---------|-------|-------------|
| zeros_then_code | 422 | Alignment padding (0x00000000) followed by unrelated function body |
| immediate_code | 194 | Adjacent function code starts immediately after |
| all_zeros | 0 | No function is entirely padding |

#### 2. The extra bytes are NOT other known functions

**0 out of 616** SIZE_DIFF functions have another CSV entry within their "gap" bytes. The extra code is completely unclaimed — Ghidra merged it into the preceding function.

#### 3. Decomp functions are complete

| Last instruction | Count | Meaning |
|------------------|-------|---------|
| `ret` | 491 | Function returns — nothing after is reachable |
| `br Xn` (indirect) | 71 | Tail call via register (vtable dispatch) — complete |
| `b` (unconditional) | 20 | Tail call — complete |
| Other (incomplete) | 34 | Some genuinely incomplete decomps |

Only **18 out of 616** have any branch from the decomp portion into the "extra" bytes — meaning 598 are provably complete functions with wrong CSV sizes.

#### 4. Scale of the problem

Control flow analysis on ALL 39,635 CSV entries:
- **15,289 functions** have sizes larger than their reachable code
- **39,387,000 bytes** over-counted (~39 MB, or 65% of .text)
- Median decomp/CSV ratio for "shorter" functions: **4.4%** (typical function is ~20x smaller than CSV says)

Distribution of decomp size as fraction of CSV size (for the 6,184 shorter functions):
- <10% of CSV size: 4,087 functions (Ghidra wildly overestimates)
- 10-30%: 883
- 30-50%: 408
- 50-70%: 329
- 70-90%: 330
- 90-100%: 147

#### 5. Why verify_all.py already handles most of these

`verify_all.py` compares using the **decomp's** compiled size, not the CSV size. So a 40-byte function that matches 40/40 bytes is marked verified even if the CSV says 2000. The SIZE_DIFF is invisible to verify_all.py but visible to gap_analysis.py.

### Root Cause Detail

Ghidra's auto-analysis has a known tendency to merge functions when:
1. **No clear function boundary**: The next function doesn't start with a recognizable prologue (e.g., `stp x29, x30, [sp, #-N]!`)
2. **Fall-through after tail call**: Ghidra doesn't always recognize `b`/`br` as function-ending and considers subsequent code as part of the same function
3. **Alignment padding**: Zeros between functions are included in the preceding function's size
4. **Cold code placement**: Compiler-separated cold paths placed after the hot path but belonging to a different function

The NX compiler uses 16-byte function alignment. Between a 4-byte `ret` and the next function at a 16-byte boundary, there are 12 bytes of zero padding. Ghidra includes this padding in the function size.

### Proposed Fix

**`tools/fix_csv_sizes.py` — CFG-based function boundary correction**

Algorithm:
1. For each CSV entry, read the function bytes from the original binary
2. Walk control flow from instruction 0 using basic block analysis
3. Track all reachable instructions via branches, fall-through, and conditional jumps
4. New size = (last reachable instruction index + 1) × 4
5. If new_size < csv_size, update the CSV

This handles:
- Trailing alignment padding (zeros)
- Adjacent function code merged by Ghidra
- Functions ending with `ret`, `b`, or `br`
- Complex control flow (loops, conditionals)

Limitations:
- Cannot follow indirect branches (`br Xn` to register) — conservatively treats as function end
- Switch tables (jump tables via `br Xn`) may cause under-counting — needs jump table detection
- Exception landing pads may be missed

**Safety:** Functions containing `br Xn` (potential switch table dispatch) are skipped, since case handlers are unreachable from simple CFG. This affects 1,815 functions.

**Expected results:** 13,474 CSV entries safely corrected, 34.4 MB of over-counting eliminated.

### Validation Results

Tested CFG analysis against 5,945 known-verified functions (decomp bytes match original):
- **99.4% agreement** (5,912/5,945) — CFG size matches decomp size
- 29 cases CFG < decomp: .o file alignment padding (not a CFG bug)
- 4 cases CFG > decomp: incomplete decomps

The safe fix (skipping `br Xn` functions):
- **2,755 M functions** would get correct sizes (cosmetic — already verified)
- **1,872 N functions** would get correct sizes (won't auto-verify, need code fixes)
- **0 functions** would have verification broken

### What this DOESN'T fix

The original estimate of "~1,700 new verifications" was optimistic. The current state:
- verify_all.py already uses decomp size (not CSV size) for comparison
- 548 of the 616 "matching but truncated" are already verified
- Only ~68 could become newly verified from size fixes alone
- The real value is **data quality**: accurate function boundaries for 13,474 entries
