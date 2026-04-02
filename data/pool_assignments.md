# Pool Assignments

**IMPORTANT: Check this file before assigning work to any pool.**
**Update this file when changing assignments.**

| Pool | Model | Task | File Territory | Status |
|------|-------|------|---------------|--------|
| pool-a | Opus | Fix non-matching in fun_batch_a/b files | `src/app/fun_batch_a_*.cpp`, `src/app/fun_batch_b_*.cpp` | assigned |
| pool-b | Opus | Fix non-matching in fun_batch_c/d files | `src/app/fun_batch_c_*.cpp`, `src/app/fun_batch_d_*.cpp` | assigned |
| pool-c | Sonnet | Batch MEDIUM decomp (0x7102 range) | `src/app/fun_batch_c2_*.cpp` (new files only) | assigned |
| pool-d | Sonnet | Batch MEDIUM decomp (0x7103 range) | `src/app/fun_batch_d2_*.cpp` (new files only) | assigned |
| pool-e | Sonnet | Batch MEDIUM decomp (0x7100 range) | `src/app/fun_batch_e_*.cpp` (new files only) | assigned |

## Rules
- Pools must ONLY write to their designated file territory
- Never assign overlapping address ranges or file patterns
- Update this file AND the pool's WORKER.md when changing assignments
- WORKER.md is now tracked in git (not .gitignored) — both files are sources of truth
- Pool-a/b EDIT existing files; pool-c/d/e CREATE new files only
