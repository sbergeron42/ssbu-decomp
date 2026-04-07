# Pool Assignments

**Each pool's WORKER.md is the single source of truth for its current task.**

This file exists only as a quick overview. If it conflicts with WORKER.md, WORKER.md wins.

| Pool | Model | Task | File Territory | Status |
|------|-------|------|----------------|--------|
| pool-a | Opus | Resource service — lookup_stream_hash (done) | src/resource/res_stream.cpp | idle |
| pool-b | Opus | Resource service — zstd v1.3.7 ID (done) + NX Clang analysis | src/resource/, lib/zstd/ | idle |
| pool-c | Opus | Resource service — ResServiceNX filesystem funcs | src/resource/res_filesystem.cpp | idle |
| pool-d | Opus | Resource service — process loop sub-functions | src/resource/res_load_helpers.cpp | assigned |
| pool-e | Opus | Resource service — filesystem utils (0x710353xxxx) | src/resource/res_filesystem_utils.cpp | assigned |

## Rules
- **Update WORKER.md in the pool's worktree when assigning work** — that's the only file that matters
- Pools must ONLY write to their designated file territory (specified in WORKER.md)
- Never assign overlapping file patterns across pools
- WORKER.md is tracked in git and survives rebases
