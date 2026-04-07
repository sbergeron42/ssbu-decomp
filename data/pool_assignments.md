# Pool Assignments

**Each pool's WORKER.md is the single source of truth for its current task.**

This file exists only as a quick overview. If it conflicts with WORKER.md, WORKER.md wins.

| Pool | Model | Task | File Territory | Status |
|------|-------|------|----------------|--------|
| pool-a | Opus | Resource service — remaining small funcs | src/resource/res_remaining_small.cpp | idle |
| pool-b | Opus | Resource service — remaining medium funcs | src/resource/res_remaining_medium.cpp | idle |
| pool-c | Opus | Resource service — remaining large funcs | src/resource/res_remaining_large.cpp | idle |
| pool-d | Opus | Resource service — post-processing | src/resource/res_post_processing2.cpp | idle |
| pool-e | Opus | Resource service — thread utils | src/resource/res_thread_utils.cpp | idle |

## Rules
- **Update WORKER.md in the pool's worktree when assigning work** — that's the only file that matters
- Pools must ONLY write to their designated file territory (specified in WORKER.md)
- Never assign overlapping file patterns across pools
- WORKER.md is tracked in git and survives rebases
