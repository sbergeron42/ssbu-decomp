# Worker: pool-a

## Model: Opus

## Task: Fix non-matching functions + find new post-processing patterns

4,621 non-matching functions remain. Analyze the most common patterns and either fix them manually or build new post-processing tools.

### Approach
1. Run python tools/analyze_regalloc.py to categorize all non-matching by divergence type
2. For the largest unfixed categories, determine if a post-processor can handle them
3. Build new tools/fix_*.py scripts for automatable patterns
4. Manually fix functions where type swaps or barriers work
5. Add new tools to build.bat post-processing pipeline

### Priority
- Focus on patterns that affect 50+ functions (biggest bang for buck)
- Existing tools already handle: prologue scheduling, epilogue swap, movz/orr, return width, x8 dispatch
- Look for: scratch register choice, store ordering, branch layout, frame size

### Rules
- CAN create/edit files in tools/
- CAN edit build.bat to add post-processing steps
- Do NOT edit source files (except to test fixes, then revert)
- Do NOT modify data/functions.csv
- Test thoroughly before committing
