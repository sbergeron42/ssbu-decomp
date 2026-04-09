# Orchestrator Workflow

This document is for the orchestrator session running in the main `SSBU Decomp/` directory.
Workers should NOT need this — their workflow is in CLAUDE.md + WORKER-pool-{letter}.md.

## Commands

```bash
python tools/setup_worktrees.py              # Create all worktrees (pool-a through pool-j)
python tools/setup_worktrees.py --device2    # Create Device 2 pools only (pool-f through pool-j)
bash tools/launch_pools.sh                   # Launch all pools (unattended, --dangerously-skip-permissions)
bash tools/launch_pools.sh a b c             # Launch specific pools
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

## Multi-Device Scaling + Handoff

### Pool Namespacing
```
Device 1 (Desktop, Account 1): pool-a through pool-e
Device 2 (Laptop,  Account 2): pool-f through pool-j
```

Each device has its own orchestrator and pools. No overlap.

### Handoff Protocol (happens multiple times per day)

**Device 1 hitting limit → Device 2 picks up:**
1. Usage monitor signals BACKOFF → pools a-e stop after current work
2. Auto-commit saves all progress to WORKER-pool-{letter}.md
3. `git push` from Device 1
4. Device 2: `git pull` → reads WORKER-pool-{letter}.md from a-e → assigns same work to f-j
5. Device 2: `bash tools/launch_pools.sh f g h i j`

**Device 2 hitting limit → Device 1 picks up (after 5h reset):**
1. Same process in reverse
2. `python tools/usage_monitor.py --reset` on Device 1
3. `bash tools/launch_pools.sh a b c d e`

WORKER-pool-{letter}.md IS the handoff note — it has progress, skip list, file territory, and "continue with" targets.

### Setup on Device 2
```bash
git clone <repo> "SSBU Decomp"
cd "SSBU Decomp"
python tools/setup_worktrees.py --device2    # Creates pool-f through pool-j
bash tools/launch_pools.sh f g h i j
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
