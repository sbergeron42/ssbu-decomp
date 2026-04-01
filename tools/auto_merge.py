#!/usr/bin/env python3
"""
Auto-merge watcher: polls worker branches for new commits and merges them.

Run this in the orchestrator session:
    python tools/auto_merge.py              # Poll every 60s
    python tools/auto_merge.py --interval 30  # Poll every 30s
    python tools/auto_merge.py --once        # Check once and exit
"""

import subprocess
import sys
import time
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
POOLS = ['pool-a', 'pool-b', 'pool-c', 'pool-d', 'pool-e']
LLD = r"C:\llvm-8.0.0\bin\ld.lld.exe"


def run(cmd, **kwargs):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True,
                         cwd=str(PROJECT_ROOT), **kwargs)


def check_pool(pool):
    """Check if a worker branch has new commits. Returns commit count."""
    branch = f"worker/{pool}"
    result = run(f'git log master..{branch} --oneline 2>nul')
    if result.returncode != 0:
        return 0
    commits = [l for l in result.stdout.strip().split('\n') if l.strip()]
    return len(commits)


def merge_pool(pool):
    """Merge a worker branch into master, rebuild, verify."""
    branch = f"worker/{pool}"
    print(f"\n{'='*60}")
    print(f"  Merging {branch}")
    print(f"{'='*60}")

    # Show what's coming
    result = run(f'git log master..{branch} --oneline')
    print(result.stdout)

    # Merge
    result = run(f'git merge {branch} --no-edit')
    if result.returncode != 0:
        print(f"  MERGE CONFLICT! Skipping {pool}.")
        print(result.stderr[:500])
        run('git merge --abort')
        return False

    print("  Merged OK")

    # Build
    result = run('cmd /c build.bat', timeout=120)
    errors = result.stdout.count('error:') if result.stdout else 0
    if errors > 0:
        print(f"  BUILD ERRORS: {errors}")
        # Don't abort merge — it's already committed
    else:
        print("  Build clean")

    # Fix prologues
    prologue_targets = ["PostureModule", "KineticEnergy", "CameraModule",
                       "GroundModule", "KineticModule", "LinkModule",
                       "FighterControlModuleImpl", "BattleObjectManager", "BossManager"]
    objs = [f"build/{t}.o" for t in prologue_targets
            if (PROJECT_ROOT / "build" / f"{t}.o").exists()]
    fix_script = PROJECT_ROOT / "tools" / "fix_prologue_sched.py"
    if fix_script.exists() and objs:
        run(f'python {fix_script} {" ".join(objs)}')

    # Link
    obj_files = ' '.join(str(o) for o in (PROJECT_ROOT / "build").glob("*.o"))
    result = run(f'"{LLD}" --shared -o build/ssbu-decomp.elf '
                f'--unresolved-symbols=ignore-all -Bsymbolic-functions '
                f'--no-undefined-version -nostdlib --noinhibit-exec {obj_files}')

    # Verify
    result = run('python tools/verify_all.py --update --summary')
    print(result.stdout)

    # Push
    result = run('git push')
    if result.returncode == 0:
        print("  Pushed to GitHub")
    else:
        print(f"  Push failed: {result.stderr[:200]}")

    return True


def main():
    interval = 60
    once = False

    args = sys.argv[1:]
    i = 0
    while i < len(args):
        if args[i] == '--interval' and i + 1 < len(args):
            interval = int(args[i + 1])
            i += 2
        elif args[i] == '--once':
            once = True
            i += 1
        else:
            i += 1

    print("Auto-merge watcher started")
    print(f"  Polling interval: {interval}s")
    print(f"  Watching branches: {', '.join('worker/' + p for p in POOLS)}")
    print()

    while True:
        # Check each pool
        for pool in POOLS:
            n = check_pool(pool)
            if n > 0:
                print(f"[{time.strftime('%H:%M:%S')}] {pool}: {n} new commit(s) — merging...")
                merge_pool(pool)

        if once:
            break

        # Wait
        try:
            time.sleep(interval)
        except KeyboardInterrupt:
            print("\nStopped.")
            break


if __name__ == '__main__':
    main()
