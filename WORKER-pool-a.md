# Worker: pool-a

## Model: Opus

## Task: ROLLBACK CRITICAL PATH — RNG hunt (sv_math::rand + state + call sites)

## Priority: HIGHEST — blocks downstream rollback netcode work

## Context
A rollback netcode fork of Eden (Yuzu) intercepting Smash's LDN traffic needs to capture/restore RNG state every frame. Without this, every rollback resimulation desyncs on frame 1. This is THE largest blocker for the rollback effort.

## What To Find

### 1. The RNG function itself
- **Search Ghidra** for `app::sv_math::rand` (or `sv_math::rand`, or just `rand` in the `app` namespace)
- Use `mcp__ghidra__search_functions_by_name` with terms like `rand`, `random`, `sv_math`
- Document the function signature, address, and what it returns (uniform u32? float? bounded int?)
- There may be multiple — `rand_int`, `rand_float`, `rand_range` etc. Find them all.

### 2. The RNG state
- Find where RNG state is stored. Likely a global or singleton.
- Look for the seed initialization — `srand`, `seed`, or wherever the function reads/writes its state
- Document the struct layout: is it a single u64? An xorshift state? A Mersenne Twister?
- Hint: We already know `xorshift128_7100138620` exists (4 u32 state, classic xorshift128). It might BE the gameplay RNG, or there may be a separate one.

### 3. Every call site
- Use `mcp__ghidra__get_function_xrefs` on the RNG function(s) to find all callers
- Document them in a list: address, calling function name, what it's doing with the result
- Categorize: gameplay (item spawns, hitlag shake, tripping, Peach turnips, G&W hammer) vs. cosmetic (UI animations, menu effects)

## Output

Create `docs/rollback/rng.md` with:
1. RNG function(s): signature, address, return semantics
2. State struct: layout with `[derived:]` provenance
3. Seed init function: where and when it's called
4. All call sites: table of `address | function | category | notes`

Also define a proper `RngState` struct in `include/app/` (not placeholders/) since the name is essentially confirmed by the `sv_math::rand` symbol in `.dynsym`.

## Approach Hints
- Try `mcp__ghidra__list_strings` for "rand" or "seed" — debug strings sometimes exist
- Cross-reference with KnokoDecomp-S — Captain Toad uses the same SDK, may have a similar RNG
- Item spawn code is a good entry point — `app::ItemManager` functions that determine which item drops will call rand
- If you find `xorshift128_7100138620` IS the gameplay RNG, rename it to `rng_advance_7100138620` or similar and document accordingly

## Quality Rules
- This is research first, decomp second. Documenting findings is the primary deliverable.
- If you decomp the rand function itself, do it cleanly with the typed RngState struct.
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch
- Cast density under 10%

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-a
```
