# Worker: pool-c

## Model: Opus

## Task: Near-miss function fixes — struct offsets, asm volatile, visibility

### Completed fixes (this session)
1. **FUN_71001b7b90** (fun_med_final_b_005.cpp): wrong struct offset `param_1[2]` → `param_1[1]` — 88%→100%
2. **FUN_71001b7bb0** (fun_med_final_b_005.cpp): same offset fix — 88%→100%
3. **FighterInformation__hit_point_impl**: non-volatile `asm("fmax")` silently compiled to `fmaxnm`; `asm volatile` fixes both encoding AND instruction ordering — 85%→100%
4. **BossManager__notify_on_boss_defeat_impl**: `DAT_7104f73b70` missing `visibility("hidden")` caused ADRP+LDR(GOT) instead of ADRP+ADD — +2 instructions matched

### Findings — batch_d5 files are ceiling-limited
The original task files (d5_021, d5_023, d5_016) contain **only** 12-byte `bl __throw_out_of_range` thunks at 67% (BL relocation is the sole diff). CSV sizes (264/352/224) are wrong. No further improvement possible.

### Techniques that work
- `asm volatile` prevents Clang 8 from silently replacing inline fmax with fmaxnm
- `visibility("hidden")` on data externs → ADRP+ADD instead of ADRP+LDR(GOT)
- Struct field offset corrections (binary decode → verify → fix)

### What doesn't work
- `visibility("hidden")` on `DAT_710593a3a8` (store_l2c_table files) — makes things worse (47/49→44/49). Original uses ADRP+LDR direct page access, not ADRP+ADD.
- Changing `>= 5` to `> 4` equivalent — disrupts prologue scheduling
- Moving asm barriers to influence register order in add — disrupts scheduling

### Remaining near-miss analysis
Most 1-instruction-off functions are BL relocation diffs (unfixable at .o level).
Register allocation diffs (add operand order, comparison order) are NX Clang fork divergences.
