# Worker: pool-a

## Model: Opus

## Task: Library identification — name and type jemalloc, zstd, Lua, curl, SDK functions

## Strategy
This is an IDENTIFICATION task, not a matching task. NX Clang diverges too much from upstream Clang 8.0.0 for byte-matching library code. The goal is to name functions and import struct types.

## Approach
1. Use Ghidra MCP to decompile unnamed functions in known library address ranges
2. Compare Ghidra output against upstream library source to identify which function it is
3. Use size matching as a hint: compile upstream source, compare function sizes
4. Name identified functions in source file comments (orchestrator updates CSV)
5. Import upstream struct definitions into include/ headers

## Targets (prioritized)
1. **zstd v1.3.7** — Source at lib/zstd/. Known functions near 0x71039a3xxx. ~264 functions compiled from upstream, use size matching + Ghidra to identify binary counterparts.
2. **jemalloc 5.1.0** — Source at lib/jemalloc/. Known at 0x710392dxxx+. ~145 functions estimated.
3. **curl** — 99 named functions at 0x7100000xxx-0x7100028xxx, already identified. Import curl struct types.
4. **NintendoSDK** — xref_sdk.py found 97 functions. Cross-reference with KinokoDecomp-S headers.

## Output
- New header files: include/lib/zstd_types.h, include/lib/jemalloc_types.h etc.
- Source files with identified functions: src/lib/zstd_identified.cpp, etc.
- Each function gets: address comment, upstream function name, N-quality (non-matching) code

## File Territory
- include/lib/
- src/lib/
- Do NOT modify data/functions.csv (orchestrator only)

## Tools
- Ghidra MCP (mcp__ghidra__decompile_function_by_address)
- Compiled library .o files in build/libmatch/ for size reference
- tools/match_library.py --extra-flags="..." for compilation
