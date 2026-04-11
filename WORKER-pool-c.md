# Worker: pool-c

## Model: Opus

## Task: ROLLBACK Round 8 — identify DAT_71053346d0 (the sibling indirect dispatch root)

## Priority: HIGH — identifies the second per-frame subsystem main_loop runs

## Context
Read `docs/rollback/sim_tick_FOUND.md` first. The sim tick entry at `main_loop + 0x5384` is **preceded** by an indirect dispatch at `main_loop + 0x5378`:

```
0x710374c608:  adrp x8, 0x7105334000               ; singleton page
0x710374c60c:  ldr  x0, [x8, #0x6d0]              ; x0 = *DAT_71053346d0
0x710374c610:  cbz  x0, 0x710374c620              ; skip if null
0x710374c614:  ldr  x8, [x0]                      ; x8 = x0->vtable
0x710374c618:  ldr  x8, [x8, #48]                 ; vt[+0x30] = slot 6
0x710374c61c:  blr  x8                            ; *** indirect dispatch ***
0x710374c620:  mov  x0, x24                      ; next call setup
0x710374c624:  bl   0x7103724a80                  ; the direct sim BL
```

`DAT_71053346d0` is a new singleton we haven't identified. It runs its `vt[+0x30]` per frame, immediately before the direct sim BL. It's a sibling subsystem — possibly:
- The stage tick
- The effect tick
- The fighter tick itself (meaning the direct BL is something else)
- Some other per-frame subsystem

Identifying it tells the rollback team what else has to be driven during resim (besides the direct BL).

## What To Do

### 1. Find writers of DAT_71053346d0
Use `tools/xref_bin_scan.py` (built by Pool C in Round 3):
```bash
python tools/xref_bin_scan.py store-offset 0x71053346d0
```

OR if that format doesn't work, use the ADRP-propagation scanner form:
```bash
python tools/xref_bin_scan.py adrp-global 0x7105334000 0x6d0
```

The writer(s) are the install path(s). Usually:
- One writer in `.init_array` (BSS zeroing — ignore this)
- One or two writers in a real constructor function (these are what we want)

### 2. Find the constructor
For each real writer, identify the containing function. It's likely a subsystem initializer called from boot / match start.

### 3. Decompile the constructor
`mcp__ghidra__decompile_function_by_address` on the constructor. It will:
- Allocate the object (via `je_aligned_alloc` or similar)
- Store the vtable pointer as the first field
- Initialize other fields
- Store the object pointer into `DAT_71053346d0`

Document:
- The object's class (if the vtable has a `.dynsym` name)
- The object's size
- The vtable address

### 4. Decompile vt[+0x30]
This is the per-frame method main_loop calls on this singleton. Slot index 6 (byte offset 0x30).

Once you have the vtable address, slot 6 is at `vtable + 0x30`. Look up the `.rela.dyn` entry for that address to find the runtime target (Pool A's technique from Round 4/5).

Decompile the target function. Does it:
- Iterate fighters? → also a sim tick (parallel to the direct BL)
- Update graphics state? → renderer
- Run stage hazards? → stage
- Something else?

### 5. Classify
Is this indirect dispatch sim-safe or sim-unsafe for resim?
- If it's a pure sim advance (like the direct BL): Eden needs to call both each resim tick
- If it's presentation (render/audio): Eden must skip it during resim
- If it's a mix: Eden needs a partial-call shim

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_FOUND.md` (new `## DAT_71053346d0 identity` section):

```markdown
## DAT_71053346d0 — Round 8

### Writer
- Function: `FUN_XXXX` at `0x710XXXX`
- Containing subsystem: [name]

### Object type
- Class: [name or "unknown"]
- Vtable: `0x710XXXX`
- Size: `0xNNN` bytes

### vt[+0x30] target
- Function: `FUN_XXXX`
- Decomp summary: [what it does]

### Sim-safe for resim?
[SIM-SAFE — Eden calls it each resim tick / PRESENTATION — Eden skips during resim / MIXED — partial shim]
```

## Quality Rules
- Documentation is the primary deliverable
- `tools/xref_bin_scan.py` is your friend for scanning globals

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
