# Pool Assignments

**Each pool's WORKER.md is the single source of truth for its current task.**

This file exists only as a quick overview. If it conflicts with WORKER.md, WORKER.md wins.

| Pool | Model | Task | File Territory | Status |
|------|-------|------|----------------|--------|
| pool-a | Opus | Rewrite Ghidra-paste batch_c files | fun_batch_c_010 through c_017 | assigned |
| pool-b | Opus | Rewrite Ghidra-paste batch_d + d2 files | fun_batch_d_001, fun_batch_d2_001-008 | assigned |
| pool-c | Opus | Rewrite Ghidra-paste batch_d3 + d4 lower files | fun_batch_d3_001-008, fun_batch_d4_001-010 | assigned |
| pool-d | Opus | Rewrite Ghidra-paste batch_d4 upper files | fun_batch_d4_011 through d4_026 | assigned |
| pool-e | Opus | Rewrite Ghidra-paste batch_b + d5 files | fun_batch_b_001-005, fun_batch_d5_042-054 | assigned |

## Rules
- **Update WORKER.md in the pool's worktree when assigning work** — that's the only file that matters
- Pools must ONLY write to their designated file territory (specified in WORKER.md)
- Never assign overlapping file patterns across pools
- WORKER.md is tracked in git and survives rebases
