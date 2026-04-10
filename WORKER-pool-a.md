# Worker: pool-a

## Model: Opus

## Task: Decomp new functions — conditional logic, copy constructors

## Priority: NEW FUNCTION DECOMP

## Status: COMPLETE — ready for merge

## Completed Work

### FUN_7103974820 — conditional field clearing (100 bytes)
- **Match: 22/26 (85%)** — 1 BL relocation + 3 return-width diffs (handled by fix_return_width.py + linker)
- Effectively matching. Shrink-wrapped, no frame pointer in param_2==0 path.
- Created placeholder struct: `include/app/placeholders/UnkType_7103974820.h`

### FUN_71032db1c0, FUN_71032e5c20, FUN_7103378c00 — struct copy constructors (32 bytes each)
- **Match: 4/8 each** — 2 ADRP relocations + 2 store-pairing order diffs (fundamental NX Clang divergence in STP pairing heuristic)
- Structurally correct: loads and stores are to the right fields, just paired differently.
- NX Clang pairs (dst[1],dst[2]) as STP, upstream Clang pairs (dst[2],dst[3]).

## Skipped Targets (with reasons)

| Target | Reason |
|--------|--------|
| 22x 4-byte nop functions (0x7100407e0c..0x710044793c) | Single `nop` instruction, unmatchable without banned `naked` asm |
| FUN_71001b0fd0 (switch decoder, 544 bytes) | NX Clang uses `adr` + base register jump table format; upstream uses table-relative. Fundamental codegen divergence. |
| FUN_7100018910 (bitmask extractor, 192 bytes) | Register allocation divergence: NX uses x8 scratch, upstream uses x9. Cascades through entire function. |
| 6x vtable dispatch (7102027170 etc.) | Parameter in x8 (non-standard calling convention), compiler-generated thunks |
| 9x __throw_out_of_range wrappers | Parameter in x8/x9, compiler-outlined cold paths |

## Analysis Notes

- **All existing near-miss functions (19/20, 17/18, etc.) are already effectively matching** — their only diffs are BL relocations resolved by the linker.
- Most remaining EASY/MEDIUM targets in next_batch.py have fundamental NX Clang codegen divergences (x8 params, jump tables, store pairing).
- The store-pairing heuristic is a new documented divergence: NX Clang pairs lower-address stores, upstream pairs higher-address stores.

## File Territory
- `src/app/fun_easy_final_004.cpp` (new file — 4 functions)
- `include/app/placeholders/UnkType_7103974820.h` (new)
- `include/app/placeholders/UnkType_7100018910.h` (new, unused now — can remove)
- `data/ghidra_cache/pool-a.txt` (appended analysis results)
