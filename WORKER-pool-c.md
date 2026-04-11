# Worker: pool-c

## Model: Opus

## Task: ROLLBACK — productize binary xref scanner + re-examine phase-6/7 dead-end candidates

## Priority: HIGH — infrastructure work that unblocks future hunts + parallel angle on the sim tick

## Context
Read `docs/rollback/sim_tick_hunt.md` first for full context. Last session you built an inline ADRP-propagation scanner that found a writer Ghidra's xref index missed (the `.init_array` BSS clearer for `DAT_710593a530`). Pools A and B both need this tool now and are reimplementing it inline.

You ALSO have ground-truth reason to revisit the phase-6/7 candidates Pool B classified as dead ends in pass 1 — Pool B's first-pass classification used a BL-only sweep, which is the same blind spot that hid the indirect dispatchers in main_loop itself. Some of those "dead end" classifications may have missed indirect dispatches.

## What To Do

### Part 1 — Productize the binary xref scanner (`tools/xref_bin_scan.py`)

Write a reusable Python tool that takes:
- An address or address range to find readers/writers for
- An optional ELF path (default: `data/main.elf`)
- An optional filter (`--writers-only`, `--readers-only`, `--non-zero-writes`, `--called-as-arg`)

The tool should:
1. Parse the ELF program headers to locate the R+X segment
2. Walk 4 bytes at a time
3. For each `ADRP` whose computed target page is within ±4 MB of the variable, start a small forward data-flow:
   - Track `{ADRP_Rd: page_base}`
   - Propagate through `MOV Xd, Xn`, `ADD Xd, Xn, #imm` (both shifts), `SUB Xd, Xn, #imm`
   - Stop on `RET` or unconditional `B`
4. At every memory instruction, check whether its `Rn` is currently tracked and whether `(tracked_val + scaled_imm)` hits the target
5. Cover all store forms: `STR W/X`, `STRB/H`, `STUR W/X`, `STP W/X` off/pre/post, `STLR W/X/B`, `STXR W/X`, and matching loads
6. Also check every `BL` where an argument register `X0..X7` holds the exact target (setter-helper pattern) and every store where the source register holds the target (pointer-init pattern)

Output format:
```
WRITERS:
  0xADDRESS  STORE_FORM  in fn 0xFN_START  (FUN_NAME or undefined)
  ...
READERS:
  0xADDRESS  LOAD_FORM   in fn 0xFN_START  (FUN_NAME or undefined)
  ...
SETTER-HELPER BL CALLS:
  0xADDRESS  callee=0xCALLEE  arg=Xn
  ...
POINTER-INIT STORES:
  0xADDRESS  source register held target
  ...
```

Test it against `0x710593a530` and verify it produces the same results Pool C found last session (3 reads, 1 writer in `.init_array`).

### Part 2 — Re-examine the four phase-6/7 candidates

Pool B's pass 1 classified these as dead ends using BL-only sweeps:
- `FUN_7103593c40` (792 B, ring buffer advance)
- `FUN_71035c13d0` (1,048 B, graphics observer pattern)
- `FUN_71036186d0` (1,188 B)
- `FUN_7103619080` (432 B)

Re-examine each one specifically for **indirect function-pointer dispatches** (the same blind spot that hid Dispatcher A in main_loop):
- Look for `LDR Xn, [Xm, #imm]; BLR Xn` patterns (vtable dispatch through a loaded pointer)
- Look for `LDR Xn, [pointer]; BLR Xn` patterns (function pointer through a global)
- For each indirect dispatch, document what's being called and on what

If any of the four was misclassified due to indirect dispatch, that's the breakthrough.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

1. New tool: `tools/xref_bin_scan.py`
2. Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool C — phase-6/7 indirect-dispatch re-examination (next-pass)

### tools/xref_bin_scan.py
Documented and tested. Pools A and B should switch to using it next session.
Test result on 0x710593a530: matches manual scan from previous session.

### Phase-6/7 indirect dispatch sweep
| Function | Indirect dispatches found | What gets called | Verdict |
|----------|---------------------------|------------------|---------|
| FUN_7103593c40 | N | ... | dead end / interesting |
| FUN_71035c13d0 | N | ... | dead end / interesting |
| FUN_71036186d0 | N | ... | dead end / interesting |
| FUN_7103619080 | N | ... | dead end / interesting |

### Most promising
[function address + reason]
```

## Quality Rules
- `tools/xref_bin_scan.py` should be a clean Python script (no shell pipes)
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable for the research portion

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
