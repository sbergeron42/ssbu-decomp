#!/usr/bin/env python3
"""
Set up git worktrees for parallel multi-agent decomp work.

Creates worker worktrees (pool-a through pool-j) with:
- Separate branches based on current master
- Symlinked original ELFs (saves ~250MB)
- Warm build directories (copies existing .o files)
- Per-worker WORKER.md with module assignments (only if not already present)

Usage:
    python tools/setup_worktrees.py               # Create all worktrees
    python tools/setup_worktrees.py a b c          # Create specific pools only
    python tools/setup_worktrees.py --device2       # Create pool-f through pool-j only
    python tools/setup_worktrees.py --clean         # Remove all worktrees
"""

import os
import sys
import shutil
import subprocess
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
PARENT_DIR = PROJECT_ROOT.parent

WORKERS = {
    'pool-a': {
        'branch': 'worker/pool-a',
        'modules': [
            # Fix the 87 non-matching compiled functions (highest value)
            'ALL_NON_MATCHING',
        ],
        'desc': 'FIX non-matching functions — compiler tricks, register allocation, prologue scheduling. Use verify_all.py to list them, viking check for debugging.',
    },
    'pool-b': {
        'branch': 'worker/pool-b',
        'modules': [
            # Item ecosystem
            'Item', 'ItemKineticModuleImpl', 'ItemCameraModuleImpl', 'ItemParamAccessor',
            'ItemDamageModuleImpl', 'ItemManager', 'ItemInkPaintModuleImpl',
            # Weapon kinetic
            'WeaponKineticEnergyGravity', 'WeaponSnakeNikitaMissileKineticEnergyNormal',
            'WeaponSnakeMissileKineticEnergyNormal',
        ],
        'desc': 'Item + Weapon ecosystem — struct accessors, SIMD, vtable dispatch',
    },
    'pool-c': {
        'branch': 'worker/pool-c',
        'modules': [
            # Fighter subsystems
            'FighterManager', 'FighterInformation', 'FighterEntry',
            'FighterControlModuleImpl', 'FighterMotionModuleImpl',
            'FighterStatusModuleImpl', 'FighterStopModuleImpl', 'FighterWorkModuleImpl',
            'FighterCutInManager',
        ],
        'desc': 'Fighter subsystems — complex game logic, external branches, struct access',
    },
    'pool-d': {
        'branch': 'worker/pool-d',
        'modules': [
            # New modules that need source files created
            'FighterBayonettaFinalModule', 'FighterKineticEnergyController',
            'FighterKineticEnergyGravity', 'FighterKineticEnergyMotion',
            'FighterPitBFinalModule', 'FighterParamAccessor2',
            'BossManager', 'StageManager', 'KineticEnergyNormal', 'KineticEnergy',
        ],
        'desc': 'Fighter kinetic/final modules + managers — new source files needed',
    },
    'pool-e': {
        'branch': 'worker/pool-e',
        'modules': [
            # Serialization (store_l2c_table large variants) + data structs
            'AreaContactLog', 'AttackAbsoluteData', 'AttackData', 'DamageInfo',
            'DamageLog', 'stWaterAreaInfo', 'Rhombus2', 'Circle', 'lib',
            # Remaining event store_l2c_table large functions
            'GimmickEvent*', 'LinkEvent*', 'FighterPikmin*', 'FighterCloud*',
            'FighterInkling*', 'FighterPokemon*', 'FighterRidley*', 'FighterRyu*',
            'WeaponRobotHominglaserLinkEvent*', 'WeaponShizueFishingrodLinkEvent*',
            'OnCalcParam*', 'GimmickEventPresenter',
            # Remaining misc
            'AttackModule', 'StatusModule', 'BattleObjectWorld', 'BattleObjectSlow',
        ],
        'desc': 'Serialization functions (store/load_l2c_table) + data structs + misc remaining',
    },
    # Extra pools (f-j) — assigned dynamically by orchestrator via WORKER.md
    'pool-f': {
        'branch': 'worker/pool-f',
        'modules': ['UNASSIGNED'],
        'desc': 'Unassigned — assign work via WORKER-pool-{letter}.md, then run sync_assignments.py',
    },
    'pool-g': {
        'branch': 'worker/pool-g',
        'modules': ['UNASSIGNED'],
        'desc': 'Unassigned — assign work via WORKER-pool-{letter}.md, then run sync_assignments.py',
    },
    'pool-h': {
        'branch': 'worker/pool-h',
        'modules': ['UNASSIGNED'],
        'desc': 'Unassigned — assign work via WORKER-pool-{letter}.md, then run sync_assignments.py',
    },
    'pool-i': {
        'branch': 'worker/pool-i',
        'modules': ['UNASSIGNED'],
        'desc': 'Unassigned — assign work via WORKER-pool-{letter}.md, then run sync_assignments.py',
    },
    'pool-j': {
        'branch': 'worker/pool-j',
        'modules': ['UNASSIGNED'],
        'desc': 'Unassigned — assign work via WORKER-pool-{letter}.md, then run sync_assignments.py',
    },
}


def run(cmd, **kwargs):
    print(f"  $ {cmd}")
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True, **kwargs)
    if result.returncode != 0 and result.stderr:
        print(f"    stderr: {result.stderr[:200]}")
    return result


def setup_worktree(name, config):
    branch = config['branch']
    worktree_dir = PARENT_DIR / f"SSBU Decomp-{name}"

    print(f"\n{'='*60}")
    print(f"Setting up {name}: {worktree_dir}")
    print(f"{'='*60}")

    if worktree_dir.exists():
        print(f"  Worktree already exists at {worktree_dir}")
        return

    # Create branch from current HEAD
    run(f'git branch "{branch}" HEAD 2>nul', cwd=str(PROJECT_ROOT))

    # Create worktree
    result = run(f'git worktree add "{worktree_dir}" "{branch}"', cwd=str(PROJECT_ROOT))
    if result.returncode != 0:
        print(f"  FAILED to create worktree: {result.stderr}")
        return

    # Create build directory
    (worktree_dir / "build").mkdir(exist_ok=True)

    # Symlink or copy original ELFs
    data_dir = worktree_dir / "data"
    orig_dir = worktree_dir / "original"
    data_dir.mkdir(exist_ok=True)
    orig_dir.mkdir(exist_ok=True)

    for src, dst in [
        (PROJECT_ROOT / "data" / "main.elf", data_dir / "main.elf"),
        (PROJECT_ROOT / "original" / "main.elf", orig_dir / "main.elf"),
    ]:
        if src.exists() and not dst.exists():
            try:
                os.symlink(str(src), str(dst))
                print(f"  Symlinked {dst.name}")
            except OSError:
                # Symlinks need admin on Windows, fall back to hardlink or copy
                try:
                    os.link(str(src), str(dst))
                    print(f"  Hardlinked {dst.name}")
                except OSError:
                    shutil.copy2(str(src), str(dst))
                    print(f"  Copied {dst.name} (no symlink/hardlink support)")

    # Copy existing .o files for warm start
    src_build = PROJECT_ROOT / "build"
    dst_build = worktree_dir / "build"
    if src_build.exists():
        copied = 0
        for obj in src_build.glob("*.o"):
            dst_obj = dst_build / obj.name
            if not dst_obj.exists():
                shutil.copy2(str(obj), str(dst_obj))
                copied += 1
        if copied:
            print(f"  Copied {copied} .o files for warm start")

    # Write WORKER.md only if it doesn't exist (preserve manually curated assignments)
    worker_md = worktree_dir / f"WORKER-{name}.md"
    if worker_md.exists():
        print(f"  {worker_md.name} already exists — preserving")
    else:
        modules_list = '\n'.join(f'- `{m}`' for m in config['modules'])
        safe_modules = ' '.join(m for m in config['modules'] if '*' not in m and m != 'UNASSIGNED')[:5]
        worker_md.write_text(f"""# Worker: {name}

## Model: Opus

## Task: {config['desc']}

## Progress
- (no work done yet)

## Continue with
- (orchestrator will assign targets)

## Skipped (don't retry)
- (none yet)

## File Territory
- (assign via orchestrator)

## Quality Rules
- No naked asm, 3-attempt limit, derivation chains

## Quick Reference
- Single-file compile: `C:/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -c src/app/FILE.cpp -o build/FILE.o`
- Compare bytes: `python tools/compare_bytes.py FUNCTION_NAME` (takes function name, NOT address)
- Full build+verify: `python tools/build.py && python tools/verify_local.py --build` (only after batch is done)
- Progress: `python tools/progress.py`
- Use `run_in_background` for any build that takes >10 seconds
- **WARNING:** Do NOT use `build.bat` — it runs deprecated post-processors that inflate match counts

## Ghidra Cache
- Save ALL Ghidra decompilation results to `data/ghidra_cache/{name}.txt` (NOT /tmp — survives reboots)
- On session start, check if this file exists and read it to recover previous Ghidra work

## Commit Cadence
- Commit every 15-20 functions or every 30 minutes, whichever comes first
- Use descriptive commit messages: `{name}: decomp MODULE functions (N new, M matching)`
""")
    print(f"  Created WORKER.md")


def clean_worktrees():
    print("Cleaning up worktrees...")
    for name in WORKERS:
        worktree_dir = PARENT_DIR / f"SSBU Decomp-{name}"
        branch = WORKERS[name]['branch']
        if worktree_dir.exists():
            run(f'git worktree remove "{worktree_dir}" --force', cwd=str(PROJECT_ROOT))
            print(f"  Removed {worktree_dir}")
        run(f'git branch -D "{branch}" 2>nul', cwd=str(PROJECT_ROOT))
    print("Done.")


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    flags = [a for a in sys.argv[1:] if a.startswith('-')]

    if '--clean' in flags:
        clean_worktrees()
        return

    # Determine which pools to set up
    if '--device2' in flags:
        selected = {k: v for k, v in WORKERS.items() if k in ('pool-f', 'pool-g', 'pool-h', 'pool-i', 'pool-j')}
    elif args:
        # e.g., "python setup_worktrees.py f g h"
        selected = {}
        for a in args:
            key = f"pool-{a}" if not a.startswith("pool-") else a
            if key in WORKERS:
                selected[key] = WORKERS[key]
            else:
                print(f"Unknown pool: {a}")
        if not selected:
            sys.exit(1)
    else:
        selected = WORKERS

    print("SSBU Decomp — Parallel Worker Setup")
    print(f"Project root: {PROJECT_ROOT}")
    print(f"Worktrees will be created in: {PARENT_DIR}")
    print(f"Pools: {', '.join(selected.keys())}")

    for name, config in selected.items():
        setup_worktree(name, config)

    print("\n" + "=" * 60)
    print("Setup complete! Worker directories:")
    for name in selected:
        d = PARENT_DIR / f"SSBU Decomp-{name}"
        print(f"  {d}")
    print()
    print("To launch pools:")
    print('  bash tools/launch_pools.sh')
    print()
    print("Orchestrator commands (run from main repo):")
    print("  git log master..worker/pool-a --oneline  # check worker progress")
    print("  bash tools/merge_worker.sh pool-a         # merge a worker")
    print("  python tools/usage_monitor.py --status    # check token usage")
    print("  python tools/sync_assignments.py          # sync WORKER.md -> pool_assignments.md")


if __name__ == '__main__':
    main()
