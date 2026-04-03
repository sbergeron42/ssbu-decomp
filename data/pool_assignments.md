# Pool Assignments

**Each pool's WORKER.md is the single source of truth for its current task.**

This file exists only as a quick overview. If it conflicts with WORKER.md, WORKER.md wins.

| Pool | Model | Status |
|------|-------|--------|
| pool-a | see WORKER.md | idle |
| pool-b | see WORKER.md | running |
| pool-c | see WORKER.md | idle |
| pool-d | see WORKER.md | running |
| pool-e | see WORKER.md | idle |

## Rules
- **Update WORKER.md in the pool's worktree when assigning work** — that's the only file that matters
- Pools must ONLY write to their designated file territory (specified in WORKER.md)
- Never assign overlapping file patterns across pools
- WORKER.md is tracked in git and survives rebases
