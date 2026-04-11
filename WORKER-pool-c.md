# Worker: pool-c

## Model: Opus

## Task: ROLLBACK Round 5 — investigate main_loop's `this->vtable[0x18]` BeginFrame hook

## Priority: HIGHEST — runs BEFORE the prologue and may BE the per-frame entry

## Context
Read `docs/rollback/sim_tick_hunt.md` first. Pool A's Round 4 disassembly of main_loop's prologue revealed:

```
0x71037472a4: ldr  x8, [x0]                 ; x8 = (*this)->vtable
0x71037472a8: ldr  x8, [x8, #0x18]          ; vt[0x18] = beginFrame hook
0x71037472ac: mov  x21, x0                  ; x21 = cached `this` (app driver)
0x71037472b0: blr  x8                       ; *** beginFrame() *** -- runs FIRST
0x71037472b4: str  x21, [DAT_710593a4c0]    ; publish this
```

The very first thing main_loop does after caching `this` is invoke `vt[0x18]` on its `this` pointer. This call:
- Runs BEFORE the prologue installer (`DAT_710593a510` is set as a side effect of THIS call)
- Is an indirect dispatch through `this`'s vtable
- The vtable belongs to the class constructed by `FUN_7103723fa0` at vtable address `0x710523bd38` (Pool A's Round 4 work — they extracted 16 vtable slots, but slot `0x18 / 8 = 3` was listed as "ret (empty stub)")

**WAIT — Pool A said slot 3 is empty. But the prologue clearly calls slot 0x18 (= slot 3 if /8) and gets back a function pointer that does work.** Either:
- Pool A's slot extraction was wrong (the .rela.dyn parse missed slot 3)
- The "this" passed to main_loop is NOT the class constructed by FUN_7103723fa0
- The vtable layout is different in the running binary than what static parsing showed

**This is the lead.** Resolve the contradiction.

## What To Do

### 1. Verify the vtable address being used at runtime
- main_loop's prologue at `0x71037472a4` does `ldr x8, [x0]` — load the vtable pointer from the `this` object
- The `this` is whatever `nnMain` constructs and passes — Pool A says it's `FUN_7103723fa0`'s output (vtable at `0x710523bd38`)
- Re-verify: is the vtable at `0x710523bd38` actually slot-0x18-empty? Or did Pool A miss a relocation?
- Use `tools/xref_bin_scan.py` to dump every relocation that points into `0x710523bd38..0x710523bdc0`
- If slot 3 IS populated, what does it point to?

### 2. If slot 0x18 is genuinely a function, decompile it
- Whatever it is, it's the FIRST per-frame call. It writes `DAT_710593a510` as a side effect (we know this from Pool A's prologue analysis).
- What ELSE does it do?
- Does it call into `FighterManager`? `BattleObjectWorld`? Iterate fighter slots?
- Look for any vtable dispatch on a `BattleObjectModuleAccessor*` pointer or any of the known module headers

### 3. If slot 0x18 is genuinely empty
- Then `nnMain` is NOT passing `FUN_7103723fa0`'s output. Pool A's chain is broken at the FIRST step.
- Re-decompile `nnMain` (or read the cached version if Pool A logged it) and find the EXACT object passed to main_loop
- That object's vtable is what we need

### 4. Investigate `DAT_710593a4c0` and `DAT_710593a534`
While you're at it, audit these two cached handles main_loop publishes:
- `DAT_710593a4c0` = cached `this` (the application driver)
- `DAT_710593a534` = cached frame phase int (Pool C's Round 3 noted 27 readers)
- Use `tools/xref_bin_scan.py` to find readers/writers
- Are any of the readers in the `0x71036xxxxx` (sim driver suspect) range?
- Are any readers' callees on a per-frame path?

## CRITICAL — Stop and ask if this round dies
This is round 5. If `vt[0x18]` is empty AND the cached handles have no sim-shaped readers, **STOP** and write a clear "static analysis is exhausted" verdict.

## Stop-and-document rule
If `mcp__ghidra__*` errors/timeouts:
1. Append to `data/ghidra_cache/manual_extraction_needed.md`
2. **Do NOT retry.** Move on.

## Output

Append to `docs/rollback/sim_tick_hunt.md`:

```markdown
## Pool C — Round 5: BeginFrame hook (vt[0x18]) investigation

### Vtable resolution
- Pool A claimed vtable[0x18] = empty stub at 0x710523bd38+0x18
- Re-verification: [confirmed empty / Pool A missed slot — actual target is 0xXXXX / wrong vtable entirely]

### vt[0x18] body (if found)
[what it does — does it iterate fighters?]

### Cached handle audit
- DAT_710593a4c0 readers: [N — list interesting ones]
- DAT_710593a534 readers: [N — list interesting ones]
- Any sim-shaped readers? [details]

### VERDICT
[SIM TICK FOUND at 0xXXXX]
[OR: BeginFrame hook is empty / does only X — sim tick is elsewhere]
[OR: STATIC ANALYSIS EXHAUSTED — recommend GDB watchpoint approach]
```

## Quality Rules
- NO `FUN_` names in committed src/ code
- Documentation is the primary deliverable

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-c
```
