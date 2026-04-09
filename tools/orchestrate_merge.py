#!/usr/bin/env python3
"""
Orchestrator lambda: merge a worker pool, rebuild, verify, reassign work.

Called by notify_done.sh when a worker finishes. Runs as a one-shot
Claude session via `claude -p`.

Usage:
    python tools/orchestrate_merge.py pool-a
"""

import csv
import os
import re
import subprocess
import sys
from pathlib import Path
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
PARENT_DIR = PROJECT_ROOT.parent
ALL_POOLS = ['pool-a', 'pool-b', 'pool-c', 'pool-d', 'pool-e']
LLD = r"C:\llvm-8.0.0\bin\ld.lld.exe"
OBJDUMP = r"C:\llvm-8.0.0\bin\llvm-objdump.exe"

PROLOGUE_TARGETS = [
    "PostureModule", "KineticEnergy", "CameraModule", "GroundModule",
    "KineticModule", "LinkModule", "FighterControlModuleImpl", "BattleObjectManager",
    "BossManager",
]


def run(cmd, check=False, **kwargs):
    print(f"  $ {cmd}")
    return subprocess.run(cmd, shell=True, capture_output=True, text=True,
                         cwd=str(PROJECT_ROOT), **kwargs)


def merge_worker_branch(pool):
    """Merge worker/pool-X into master."""
    branch = f"worker/{pool}"
    print(f"\n=== Merging {branch} ===")

    # Check for commits
    r = run(f'git log master..{branch} --oneline')
    commits = [l for l in r.stdout.strip().split('\n') if l.strip()]
    if not commits:
        print("  No new commits. Skipping merge.")
        return False

    print(f"  {len(commits)} commit(s):")
    print(r.stdout)

    # Merge
    r = run(f'git merge {branch} --no-edit')
    if r.returncode != 0:
        print("  MERGE CONFLICT — attempting auto-resolve...")
        # Try resolving: ours for data files, theirs for source
        run('git checkout --ours data/ WORKER-pool-*.md')
        run('git checkout --theirs src/')
        r = run('git add -A && git commit --no-edit -m "Auto-resolve merge conflict"')
        if r.returncode != 0:
            print("  FAILED to auto-resolve. Aborting merge.")
            run('git merge --abort')
            return False

    print("  Merged OK")
    return True


def rebuild_and_verify():
    """Build, fix prologues, link, verify."""
    print("\n=== Rebuilding ===")

    # Build
    r = run('cmd /c build.bat', timeout=180)
    errors = r.stdout.count('error:') if r.stdout else 0
    if errors > 0:
        print(f"  Build had {errors} error(s)")

    # Fix prologues
    fix_script = PROJECT_ROOT / "tools" / "fix_prologue_sched.py"
    if fix_script.exists():
        objs = [f"build/{t}.o" for t in PROLOGUE_TARGETS
                if (PROJECT_ROOT / "build" / f"{t}.o").exists()]
        if objs:
            run(f'python "{fix_script}" {" ".join(objs)}')

    # Link
    obj_files = ' '.join(str(o) for o in (PROJECT_ROOT / "build").glob("*.o"))
    run(f'"{LLD}" --shared -o build/ssbu-decomp.elf '
        f'--unresolved-symbols=ignore-all -Bsymbolic-functions '
        f'--no-undefined-version -nostdlib --noinhibit-exec {obj_files}')

    # Verify
    r = run('python tools/verify_all.py --update --summary')
    print(r.stdout)

    return r.stdout


def git_push():
    """Push to remote."""
    r = run('git push')
    if r.returncode == 0:
        print("  Pushed OK")
    else:
        print(f"  Push issue: {r.stderr[:200]}")


def get_compiled_functions():
    """Get set of compiled function short names from ELF."""
    r = run(f'"{OBJDUMP}" -t build/ssbu-decomp.elf')
    compiled = set()
    for line in r.stdout.split('\n'):
        if 'F .text' in line:
            name = line.split()[-1]
            if name.startswith('_ZN3app8lua_bind'):
                rest = name[16:]
                i = 0
                while i < len(rest) and rest[i].isdigit():
                    i += 1
                if i > 0:
                    length = int(rest[:i])
                    compiled.add(rest[i:i + length])
    return compiled


def get_remaining_work(compiled):
    """Get remaining named uncompiled functions grouped by module."""
    remaining = {}
    with open(PROJECT_ROOT / 'data' / 'functions.csv') as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            if row[1] != 'U':
                continue
            name = row[3]
            if name in compiled or name.startswith('FUN_') or name.startswith('__'):
                continue
            if '__' not in name:
                continue
            module = name.split('__')[0]
            if module in ('', '~'):
                continue
            remaining.setdefault(module, []).append(name)
    return remaining


def get_non_matching_modules(verify_output):
    """Parse verify output to find non-matching function modules."""
    non_matching = {}
    for line in verify_output.split('\n'):
        line = line.strip()
        if '/' in line and 'strict' in line:
            func_name = line.split(':')[0].strip()
            if '__' in func_name:
                module = func_name.split('__')[0]
                non_matching.setdefault(module, []).append(func_name)
    return non_matching


def is_pool_active(pool):
    """Check if a pool has uncommitted work or pending commits (i.e., actively working)."""
    worktree = PARENT_DIR / f"SSBU Decomp-{pool}"
    if not worktree.exists():
        return False
    # Check for uncommitted changes
    r = subprocess.run('git status --porcelain', shell=True, capture_output=True,
                      text=True, cwd=str(worktree))
    has_changes = bool(r.stdout.strip())
    # Check for unpushed commits ahead of master
    r = subprocess.run(f'git log master..worker/{pool} --oneline', shell=True,
                      capture_output=True, text=True, cwd=str(PROJECT_ROOT))
    has_commits = bool(r.stdout.strip())
    return has_changes or has_commits


def get_claimed_modules(exclude_pool):
    """Read ACTIVE pools' WORKER-pool-*.md to find claimed modules.

    Only counts modules from pools that are actively working (have uncommitted
    changes or pending commits). Idle pools don't claim anything.
    """
    claimed = set()
    for pool in ALL_POOLS:
        if pool == exclude_pool:
            continue
        if not is_pool_active(pool):
            continue

        worktree = PARENT_DIR / f"SSBU Decomp-{pool}"
        worker_md = worktree / f"WORKER-{pool}.md"
        if not worker_md.exists():
            continue

        content = worker_md.read_text()
        # Parse module names from backtick-wrapped entries
        for match in re.finditer(r'`(\w+)`', content):
            mod = match.group(1)
            # Filter out non-module keywords
            if mod in ('worker', 'pool', 'WORKER', 'NEVER', 'ONLY', 'bash', 'python',
                       'git', 'src', 'app', 'modules', 'data', 'build', 'tools',
                       'csv', 'POOL_NAME', 'true', 'false', 'void', 'bool', 'u64',
                       'u8', 'f32', 'LargeRet', 'v4sf', 'VT', 'VTABLE'):
                continue
            if '__' in mod or mod.startswith('FUN_'):
                continue
            claimed.add(mod)

    return claimed


def pick_assignment(available_uncompiled, available_nonmatching, target=30):
    """Pick modules to assign, prioritizing non-matching fixes then uncompiled."""
    assignment = {'fix_nonmatching': {}, 'new_decomp': {}}
    count = 0

    # Priority 1: non-matching fixes (highest value)
    for mod in sorted(available_nonmatching, key=lambda m: -len(available_nonmatching[m])):
        if count >= target:
            break
        funcs = available_nonmatching[mod]
        assignment['fix_nonmatching'][mod] = funcs
        count += len(funcs)

    # Priority 2: remaining uncompiled
    for mod in sorted(available_uncompiled, key=lambda m: -len(available_uncompiled[m])):
        if count >= target:
            break
        funcs = available_uncompiled[mod]
        assignment['new_decomp'][mod] = funcs
        count += len(funcs)

    return assignment


def write_worker_md(pool, assignment):
    """Write updated WORKER-pool-*.md for the pool."""
    worktree = PARENT_DIR / f"SSBU Decomp-{pool}"
    worker_md = worktree / f"WORKER-{pool}.md"

    lines = [f"# Worker: {pool} (auto-assigned)\n"]
    lines.append("## Assignment\n")

    if assignment['fix_nonmatching']:
        lines.append("### Fix non-matching functions\n")
        for mod, funcs in sorted(assignment['fix_nonmatching'].items()):
            lines.append(f"- `{mod}` ({len(funcs)} non-matching)")
            for f in funcs[:5]:
                lines.append(f"  - {f}")
            if len(funcs) > 5:
                lines.append(f"  - ... +{len(funcs)-5} more")
        lines.append("")

    if assignment['new_decomp']:
        lines.append("### New functions to decompile\n")
        for mod, funcs in sorted(assignment['new_decomp'].items()):
            lines.append(f"- `{mod}` ({len(funcs)} remaining)")
        lines.append("")

    all_modules = set(assignment['fix_nonmatching'].keys()) | set(assignment['new_decomp'].keys())
    if not all_modules:
        lines.append("**No more work available — all named functions are compiled!**\n")

    lines.append("## Rules")
    lines.append(f"1. ONLY edit .cpp files for: {', '.join(sorted(all_modules))}")
    lines.append("2. **NEVER modify data/functions.csv**")
    lines.append(f"3. Commit to branch `worker/{pool}`")
    lines.append("")
    lines.append("## Workflow")
    lines.append("```bash")
    if all_modules:
        mods_str = ' '.join(sorted(all_modules)[:5])
        lines.append(f"python tools/verify_local.py --build --modules {mods_str}")
    lines.append("git add src/")
    lines.append('git commit -m "description"')
    lines.append("```")
    lines.append("")
    lines.append("## When done")
    lines.append(f'```bash\nbash tools/notify_done.sh {pool} "description"\n```')

    worker_md.write_text('\n'.join(lines))
    print(f"  Wrote {worker_md}")


def rebase_pool(pool):
    """Rebase the pool's branch onto master."""
    worktree = PARENT_DIR / f"SSBU Decomp-{pool}"
    r = subprocess.run('git rebase master', shell=True, capture_output=True,
                      text=True, cwd=str(worktree))
    if r.returncode != 0:
        print(f"  Rebase failed for {pool} — resetting to master")
        subprocess.run('git rebase --abort', shell=True, capture_output=True,
                      cwd=str(worktree))
        subprocess.run('git reset --hard master', shell=True, capture_output=True,
                      cwd=str(worktree))
    else:
        print(f"  Rebased {pool} onto master")


def main():
    if len(sys.argv) < 2:
        print("Usage: python tools/orchestrate_merge.py <pool-name>")
        sys.exit(1)

    pool = sys.argv[1]
    print(f"{'='*60}")
    print(f"  ORCHESTRATOR: Processing {pool}")
    print(f"{'='*60}")

    # 1. Merge
    merged = merge_worker_branch(pool)

    # 2. Rebuild + verify
    verify_output = rebuild_and_verify()

    # 3. Update README with current progress
    run('python tools/update_readme.py')
    run('git add README.md')
    r = run('git diff --cached --quiet README.md')
    if r.returncode != 0:
        run('git commit -m "Auto-update README progress"')

    # 4. Push
    git_push()

    # 4. Get claimed modules from other active pools
    claimed = get_claimed_modules(exclude_pool=pool)
    print(f"\n=== Module ownership ===")
    print(f"  Claimed by other pools: {len(claimed)} modules")

    # 5. Get remaining work
    compiled = get_compiled_functions()
    remaining_uncompiled = get_remaining_work(compiled)
    non_matching = get_non_matching_modules(verify_output or '')

    # 6. Filter to unclaimed
    avail_uncompiled = {m: f for m, f in remaining_uncompiled.items() if m not in claimed}
    avail_nonmatching = {m: f for m, f in non_matching.items() if m not in claimed}

    total_avail = sum(len(f) for f in avail_uncompiled.values()) + \
                  sum(len(f) for f in avail_nonmatching.values())
    print(f"  Available unclaimed: {total_avail} functions")

    # 7. Assign
    assignment = pick_assignment(avail_uncompiled, avail_nonmatching)
    total_assigned = sum(len(f) for f in assignment['fix_nonmatching'].values()) + \
                     sum(len(f) for f in assignment['new_decomp'].values())
    print(f"\n=== New assignment for {pool}: {total_assigned} functions ===")
    for cat, mods in assignment.items():
        for mod, funcs in mods.items():
            print(f"  [{cat}] {mod}: {len(funcs)}")

    # 8. Write WORKER-pool-*.md
    write_worker_md(pool, assignment)

    # 9. Rebase
    rebase_pool(pool)

    print(f"\n{'='*60}")
    print(f"  DONE — {pool} ready for next round")
    print(f"{'='*60}")


if __name__ == '__main__':
    main()
