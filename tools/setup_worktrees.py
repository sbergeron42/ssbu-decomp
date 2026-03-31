#!/usr/bin/env python3
"""
Set up git worktrees for parallel multi-agent decomp work.

Creates 3 worker worktrees (pool-a, pool-b, pool-c) with:
- Separate branches based on current master
- Symlinked original ELFs (saves ~250MB)
- Warm build directories (copies existing .o files)
- Per-worker WORKER.md with module assignments

Usage:
    python tools/setup_worktrees.py           # Create all 3 worktrees
    python tools/setup_worktrees.py --clean   # Remove all worktrees
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
            'GroundModule', 'ItemModule', 'LinkModule', 'PhysicsModule', 'AttackModule',
            'HitModule', 'ShieldModule', 'CaptureModule', 'GrabModule', 'ReflectModule',
            'ReflectorModule', 'AbsorberModule', 'SearchModule',
        ],
        'desc': 'Large accessor modules — vtable dispatchers + complex patterns',
    },
    'pool-b': {
        'branch': 'worker/pool-b',
        'modules': [
            'FighterManager', 'FighterInformation', 'FighterMotionModuleImpl',
            'FighterControlModuleImpl', 'FighterWorkModuleImpl', 'FighterStatusModuleImpl',
            'FighterAreaModuleImpl', 'ItemKineticModuleImpl', 'ItemCameraModuleImpl',
            'KineticEnergy', 'KineticEnergyNormal', 'KineticEnergyRotNormal',
            'ControlModule', 'StatusModule', 'WorkModule', 'KineticModule',
            'BattleObjectManager', 'BattleObjectSlow', 'BattleObjectWorld',
            'FighterEntry', 'Article',
        ],
        'desc': 'Struct/manager modules — field access + vtable dispatch',
    },
    'pool-c': {
        'branch': 'worker/pool-c',
        'modules': [
            'CameraModule', 'EffectModule', 'SoundModule', 'DamageModule', 'ModelModule',
            'PostureModule', 'MotionModule', 'MotionAnimcmdModule', 'JostleModule',
            'ShadowModule', 'ShakeModule', 'SlowModule', 'StopModule', 'TurnModule',
            'TeamModule', 'CancelModule', 'VisibilityModule', 'InkPaintModule',
            'ColorBlendModule', 'ComboModule', 'AreaModule', 'ArticleModule',
            'LuaModule', 'SlopeModule',
            # All event/weapon types
            'GimmickEvent*', 'LinkEvent*', 'FighterPikmin*', 'FighterCloud*',
            'FighterInkling*', 'FighterPokemon*', 'FighterRidley*', 'FighterRyu*',
            'FighterSpirits*', 'FighterBayonetta*', 'Weapon*',
            'OnCalcParam*', 'Item', 'Weapon', 'lib',
        ],
        'desc': 'Small modules + events — boilerplate files + effects/audio',
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

    # Write WORKER.md
    worker_md = worktree_dir / "WORKER.md"
    modules_list = '\n'.join(f'- `{m}`' for m in config['modules'])
    worker_md.write_text(f"""# Worker: {name}

## Assignment
{config['desc']}

## Assigned Modules
{modules_list}

## Rules
1. **ONLY edit .cpp files for your assigned modules** (in src/app/ or src/app/modules/)
2. **NEVER modify data/functions.csv** — the orchestrator handles this
3. **NEVER edit modules assigned to other workers**
4. Commit to your branch (`{branch}`), never push to master

## Workflow
```bash
# 1. Edit source files for your assigned modules
# 2. Build and verify:
python tools/verify_local.py --build --modules {' '.join(m for m in config['modules'] if '*' not in m)[:5]}

# 3. Or build manually:
cmd /c build.bat
python tools/verify_local.py --modules YourModule

# 4. Commit when functions match:
git add src/app/modules/YourModule.cpp
git commit -m "Match N functions in YourModule"

# 5. The orchestrator will merge your branch to master
```

## Checking your progress
```bash
python tools/verify_local.py --modules YourModule
```

## Using viking for per-function debugging
```bash
tools/common/nx-decomp-tools/viking/target/release/check.exe FunctionName
```
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
    if '--clean' in sys.argv:
        clean_worktrees()
        return

    print("SSBU Decomp — Parallel Worker Setup")
    print(f"Project root: {PROJECT_ROOT}")
    print(f"Worktrees will be created in: {PARENT_DIR}")

    for name, config in WORKERS.items():
        setup_worktree(name, config)

    print("\n" + "=" * 60)
    print("Setup complete! Worker directories:")
    for name in WORKERS:
        d = PARENT_DIR / f"SSBU Decomp-{name}"
        print(f"  {d}")
    print()
    print("To start a worker session:")
    print('  cd "SSBU Decomp-pool-a"')
    print("  claude")
    print()
    print("Orchestrator commands (run from main repo):")
    print("  git log master..worker/pool-a --oneline  # check worker progress")
    print("  bash tools/merge_worker.sh pool-a         # merge a worker")


if __name__ == '__main__':
    main()
