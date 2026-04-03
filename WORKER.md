# Worker: pool-a

## Model: Opus

## Task: Build auto-fixer tool for non-matching functions

2,008 functions compile but do not byte-match. Most fail for predictable reasons. Build a tool that reads the instruction diff and auto-applies fixes.

### Tool: tools/auto_fix_nonmatching.py

The tool should:
1. Run verify_all.py to get the non-matching function list
2. For each non-matching function, compare decomp bytes vs original bytes
3. Detect the mismatch pattern and apply the appropriate fix to the .cpp source
4. Rebuild and verify to confirm the fix worked

### Patterns to detect and fix (in priority order)

1. **Register width mismatch (w0 vs x0)**: decomp uses 32-bit where original uses 64-bit or vice versa. Fix: swap u32/s32 with u64/s64 in the param or return type.

2. **Bool truncation (and w0, w0, #1)**: decomp has extra bool truncation. Fix: swap bool with u8 in the param type.

3. **Return type mismatch**: different register used for return. Fix: try void, u32, u64, void* for the return type.

4. **Instruction reordering**: same instructions but different order. Fix: insert asm("") barriers between independent operations, guarded by MATCHING_HACK_NX_CLANG.

### Workflow
1. Start with pattern 1 (register width) — likely fixes the most functions
2. For each pattern, test on 10 functions manually first
3. Then automate: read source, apply regex fix, rebuild, check if verified
4. If fix breaks compilation or makes it worse, revert automatically

### Key resources
- tools/show_diff.py — shows instruction-level diff for a function
- tools/verify_all.py — the verifier (read_o_file_functions gives you decomp bytes)
- data/main.elf — original binary bytes

### Rules
- ONLY create/edit: tools/auto_fix_nonmatching.py (new tool)
- Do NOT manually edit any .cpp source files
- Do NOT modify data/functions.csv
- The tool should be non-destructive: revert any fix that does not improve the match
