# Pool Assignments

**IMPORTANT: Check this file before assigning work to any pool.**
**Update this file when changing assignments.**

| Pool | Model | Task | File Territory | Status |
|------|-------|------|---------------|--------|
| pool-a | Opus | Build PLT post-processor tool + replace 2,073 naked asm with real C++ | `tools/fix_plt_stubs.py` (new), `src/app/fun_region_039.cpp` | assigned |
| pool-b | Opus | Convert non-PLT naked asm to C++ with asm barriers (files A-L) | `src/app/A*` through `src/app/L*`, `src/app/fun_batch_a*`, `src/app/fun_batch_b*` | assigned |
| pool-c | Opus | Convert non-PLT naked asm to C++ with asm barriers (files M-Z) | `src/app/M*` through `src/app/Z*`, `src/app/fun_batch_c*`, `src/app/fun_batch_d*`, `src/app/fun_batch_e*` | assigned |
| pool-d | Sonnet | Batch MEDIUM decomp (0x7100-0x7101 range) | `src/app/fun_batch_d3_*.cpp` (new files only) | assigned |
| pool-e | Sonnet | Batch MEDIUM decomp (0x7102-0x7103 range) | `src/app/fun_batch_e2_*.cpp` (new files only) | assigned |

## Rules
- Pools must ONLY write to their designated file territory
- Never assign overlapping address ranges or file patterns
- Update this file AND the pool's WORKER.md when changing assignments
- WORKER.md is tracked in git — both files are sources of truth
