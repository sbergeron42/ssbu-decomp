# Worker: pool-a

## Model: Opus

## Task: jemalloc 5.1.0 decomp — lower half (arena, extent, base, bin, bitmap, ctl internals)

Match 68 HARD-tier jemalloc functions against upstream source (lib/jemalloc/).

### Upstream Reference
- jemalloc 5.1.0 (tag `5.1.0`, commit `61efbda7098de6fe64c362d309824864308c36d4`)
- Nintendo's build: `5.1.0-2-g97d9c2105f87d2490f707a4daecc3baac5c170ed` (2 private patches on top)
- Upstream source cloned at `lib/jemalloc/` in the main repo
- Version string at 0x710426ddf8, config: `percpu_arena:percpu,dirty_decay_ms:1`

### Address Range
0x71039278b0 — 0x71039494f0 (68 functions)

### Approach
1. For each target address, decompile in Ghidra
2. Match the decompiled code against the upstream jemalloc 5.1.0 source in `lib/jemalloc/src/`
3. Write C that matches the upstream source, adapted for the NX build config
4. Add a comment on each function: `// jemalloc 5.1.0: <source_file>.c:<line_number>`
5. If a function doesn't match upstream exactly, note the Nintendo delta

### Key jemalloc source files (likely matches for this range)
- `src/arena.c` — arena management
- `src/extent.c` — extent allocation/deallocation
- `src/base.c` — base allocation
- `src/bin.c` — bin/slab management
- `src/ctl.c` — mallctl interface
- `src/large.c` — large allocation
- `src/sz.c` — size class utilities

### Output: src/lib/jemalloc_a_001.cpp onward

### Rules
- Use upstream jemalloc field names and types — these are KNOWN, not inferred
- Every function gets a `// jemalloc 5.1.0: file.c:line` provenance comment
- Note any Nintendo-specific deltas from upstream
- 3-attempt limit per function
- ONLY create src/lib/jemalloc_a_*.cpp
- Save Ghidra results to /tmp/ghidra_results.txt
- Build once with tee, grep the file
