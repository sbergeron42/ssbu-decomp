# Worker: pool-b

## Model: Opus

## Task: jemalloc 5.1.0 decomp — upper half (ctl, stats, tcache, tsd, mutex)

Match 69 HARD-tier jemalloc functions against upstream source (lib/jemalloc/).

### Upstream Reference
- jemalloc 5.1.0 (tag `5.1.0`, commit `61efbda7098de6fe64c362d309824864308c36d4`)
- Nintendo's build: `5.1.0-2-g97d9c2105f87d2490f707a4daecc3baac5c170ed` (2 private patches on top)
- Upstream source cloned at `lib/jemalloc/` in the main repo
- Version string at 0x710426ddf8, config: `percpu_arena:percpu,dirty_decay_ms:1`

### Address Range
0x71039498e0 — 0x710395f6d0 (69 functions)

### Approach
1. For each target address, decompile in Ghidra
2. Match the decompiled code against the upstream jemalloc 5.1.0 source in `lib/jemalloc/src/`
3. Write C that matches the upstream source, adapted for the NX build config
4. Add a comment on each function: `// jemalloc 5.1.0: <source_file>.c:<line_number>`
5. If a function doesn't match upstream exactly, note the Nintendo delta

### Key jemalloc source files (likely matches for this range)
- `src/ctl.c` — mallctl interface (ctl_bymib, ctl handlers)
- `src/stats.c` — stats_print, stats formatting
- `src/tcache.c` — thread cache
- `src/tsd.c` — thread-specific data
- `src/mutex.c` — mutex wrappers
- `src/prof.c` — profiling

### Output: src/lib/jemalloc_b_001.cpp onward

### Rules
- Use upstream jemalloc field names and types — these are KNOWN, not inferred
- Every function gets a `// jemalloc 5.1.0: file.c:line` provenance comment
- Note any Nintendo-specific deltas from upstream
- 3-attempt limit per function
- ONLY create src/lib/jemalloc_b_*.cpp
- Save Ghidra results to /tmp/ghidra_results.txt
- Build once with tee, grep the file
