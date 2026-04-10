# Worker: pool-a

## Model: Opus

## Task: ROLLBACK CRITICAL PATH — RNG hunt (sv_math::rand + state + call sites)

## Priority: HIGHEST — blocks downstream rollback netcode work

## Context
A rollback netcode fork of Eden (Yuzu) intercepting Smash's LDN traffic needs to capture/restore RNG state every frame. Without this, every rollback resimulation desyncs on frame 1.

## IMPORTANT: Pre-cached decomps
**Two huge functions have already been decompiled to disk** (Ghidra MCP times out on them):
- `data/ghidra_cache/main_loop_7103747270.txt` (24KB function, 3947 lines)
- `data/ghidra_cache/FUN_7101344cf0.txt` (65KB function, 5891 lines — likely per-frame fighter update)

**Read these files with `Read` instead of calling Ghidra MCP for those addresses.** Both files contain Ghidra decompiler output (with Ghidra default variable names — that's expected, you're reading reference material, not committing it).

## What To Find

### 1. The RNG function itself
- Search Ghidra for `app::sv_math::rand` (or `sv_math::rand`, or `rand` in `app` namespace)
- Use `mcp__ghidra__search_functions_by_name` with terms like `rand`, `random`, `sv_math`
- Document the function signature, address, and what it returns
- We already know `xorshift128_7100138620` exists. Check if it IS the gameplay RNG or separate.

### 2. The RNG state
- Find where RNG state is stored (likely a global or singleton)
- Document the struct layout
- Find the seed init function

### 3. Every call site
- Use `mcp__ghidra__get_function_xrefs` on the RNG function(s)
- Categorize each: gameplay (item spawns, hitlag shake, tripping) vs cosmetic (UI, menus)
- **Both `main_loop` and `FUN_7101344cf0` likely call rand many times — search the cached files for "rand" or for the RNG address you find**

## Output

Create `docs/rollback/rng.md` with:
1. RNG function(s): signature, address, return semantics
2. State struct: layout with `[derived:]` provenance
3. Seed init function: where and when
4. All call sites: table of `address | function | category | notes`

Define a proper `RngState` struct in `include/app/RngState.h` (not placeholders/) since `sv_math::rand` is `.dynsym`-confirmed.

## Quality Rules
- Cast density under 10%
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch in committed code
- The cached files contain Ghidra paste — that's reference material, NOT something to commit

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
