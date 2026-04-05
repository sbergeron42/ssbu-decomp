# Pool Assignments

**Each pool's WORKER.md is the single source of truth for its current task.**

This file exists only as a quick overview. If it conflicts with WORKER.md, WORKER.md wins.

| Pool | Model | Task | File Territory | Status |
|------|-------|------|----------------|--------|
| pool-a | Opus | jemalloc 5.1.0 lower half (68 funcs) | src/lib/jemalloc_a_*.cpp | assigned |
| pool-b | Opus | jemalloc 5.1.0 upper half (69 funcs) | src/lib/jemalloc_b_*.cpp | assigned |
| pool-c | Opus | Re-decomp Tier 1+2 (ItemKinetic/FighterMgr/MotionModule) | edit existing + src/app/fun_redecomp_c_*.cpp | assigned |
| pool-d | Opus | Re-decomp Tier 1+2 (ItemCamera/Status/Attack/GroundModule) | edit existing + src/app/fun_redecomp_d_*.cpp | assigned |
| pool-e | Opus | UI/CSS (20) + AI/L2CValue (10) showcase | src/app/fun_typed_e_*.cpp | assigned |

## Rules
- **Update WORKER.md in the pool's worktree when assigning work** — that's the only file that matters
- Pools must ONLY write to their designated file territory (specified in WORKER.md)
- Never assign overlapping file patterns across pools
- WORKER.md is tracked in git and survives rebases
