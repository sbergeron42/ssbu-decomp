# Orchestrator Workflow

This document is for the orchestrator session running in the main `SSBU Decomp/` directory.
Workers should NOT need this — their workflow is in CLAUDE.md + WORKER-pool-{letter}.md.

## Commands

```bash
python tools/setup_worktrees.py              # Create all worktrees (pool-a through pool-j)
python tools/setup_worktrees.py --device2    # Create Device 2 pools only (pool-f through pool-j)
bash tools/launch_pools.sh                   # Launch all pools (unattended, --dangerously-skip-permissions)
bash tools/launch_pools.sh a b c             # Launch specific pools
bash tools/stop_pools.sh                     # Gracefully stop all pools
bash tools/stop_pools.sh a c                 # Stop specific pools
python tools/review_diff.py pool-a           # *** Review code quality BEFORE merge ***
python tools/review_diff.py pool-a --strict  # Strict mode: warnings also cause rejection
bash tools/merge_worker.sh pool-a            # Merge a worker branch (AFTER review passes)
python tools/verify_all.py --update          # Global verify + CSV update
python tools/sync_assignments.py             # Sync WORKER-pool-{letter}.md → pool_assignments.md
python tools/usage_monitor.py --status       # Check token usage across pools
python tools/usage_monitor.py                # Live monitor — auto-signals BACKOFF at 90%
python tools/usage_monitor.py --reset        # Clear BACKOFF signal after limit resets
python tools/tail_pool.py --all              # Human-readable live log viewer
```

## Autonomous Loop

The orchestrator runs a periodic check cycle — no separate monitor process needed.

```
1. Launch pools:     Bash("bash tools/launch_pools.sh", run_in_background=true)
2. Wait ~15-20 min
3. Check usage:      python tools/usage_monitor.py --status
4. If usage > 90%:   python tools/usage_monitor.py --budget X --threshold 0.01
                     (writes BACKOFF — pools stop on next restart)
                     git add -A && git commit && git push  (handoff)
                     STOP — wait for 5h reset or hand to Device 2
5. Check commits:    git log master..worker/pool-X --oneline (for each pool)
6. If commits:       bash tools/merge_worker.sh pool-X
7. If pool exhausted: update WORKER-pool-{letter}.md → python tools/sync_assignments.py
8. Go to step 2
```

## Usage Monitoring

Claude Max 20x session limits reset every **5 hours**.

```bash
python tools/usage_monitor.py --status       # One-shot: show current burn rate
python tools/usage_monitor.py --reset        # Clear BACKOFF signal after limit resets
```

The orchestrator checks `--status` as part of its merge cycle. If nearing limit, it writes BACKOFF:
- `launch_pools.sh` stops restarting crashed/finished pools
- Pools finish their current session and auto-commit
- Handoff to Device 2 via git push (WORKER-pool-{letter}.md carries all state)

## Multi-Device Scaling

### Shared Pool Model
All 10 pools (a-j) are shared across devices. Lock files in `data/pool_locks/` prevent
two devices from running the same pool simultaneously.

- `launch_pools.sh` acquires a lock before starting each pool, skips pools locked by another device
- `stop_pools.sh` releases locks on cleanup
- Stale locks (>1 hour with no activity) are auto-broken
- Set `DEVICE_ID=mydevice` to override hostname-based device identification

### Handoff Protocol
1. Device 1 stops: `bash tools/stop_pools.sh` (commits work, releases locks)
2. Device 1 pushes: `git push`
3. Device 2 pulls: `git pull`
4. Device 2 launches: `bash tools/launch_pools.sh` (skips pools without WORKER.md or worktrees)

### Setup on a new device
```bash
git clone <repo> "SSBU Decomp"
cd "SSBU Decomp"
python tools/setup_worktrees.py              # Creates all 10 pool worktrees
bash tools/launch_pools.sh                   # Launches all assigned pools (skips locked/unassigned)
```

## Merge Protocol

1. Check worker progress: `git log master..worker/pool-a --oneline`
2. **Run code review**: `python tools/review_diff.py pool-a`
   - If REJECT: do NOT merge. Note the violations, reassign the pool to fix them.
   - If PASS with warnings: merge is OK, but note warnings for future assignment guidance.
   - If PASS clean: merge immediately.
3. Merge: `bash tools/merge_worker.sh pool-a`
   - Merges branch, rebuilds with build.py, verifies, updates CSV, rebases other workers
4. After merge, check if pool needs reassignment — read its WORKER-pool-{letter}.md

**NEVER skip the review step.** The whole point is to catch raw-offset slop before it lands on master. A rejected pool should get its WORKER-pool-{letter}.md updated with the specific violations to fix.

## Assignment Protocol

1. **READ `data/pool_assignments.md`** for current state across all pools
2. **READ the target pool's WORKER-pool-{letter}.md** to check if it's doing useful work
3. **WRITE the pool's WORKER-pool-{letter}.md** with the new assignment (use standardized template)
4. **RUN `python tools/sync_assignments.py`** to update pool_assignments.md
5. Pre-filter targets: skip x8-dispatch thunks, adrp-locked stubs, SIMD/NEON functions

## Linking Infrastructure

### Stub Generator
`tools/gen_stubs.py` generates `extern "C"` stub declarations for all U-quality functions.
Status: Built, generates 26,327 stubs.

### Milestones
- **Now (~41% compiled):** Focus on decomp volume and match quality
- **50% compiled:** Attempt first full link, identify section ordering issues
- **60%+ compiled:** Maintain working linked binary as CI
- **80%+ compiled:** Target shiftable link for modding
