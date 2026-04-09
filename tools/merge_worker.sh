#!/bin/bash
# Orchestrator script: merge a worker branch into master, rebuild, verify, rebase others.
#
# Usage: bash tools/merge_worker.sh pool-a
#        bash tools/merge_worker.sh pool-b --no-rebase

set -e

POOL="$1"
NO_REBASE="$2"

if [ -z "$POOL" ]; then
    echo "Usage: bash tools/merge_worker.sh <pool-name> [--no-rebase]"
    echo "  e.g. bash tools/merge_worker.sh pool-a"
    exit 1
fi

BRANCH="worker/$POOL"
CLANG="C:/llvm-8.0.0/bin/clang++.exe"
LLD="C:/llvm-8.0.0/bin/ld.lld.exe"
OBJDUMP="C:/llvm-8.0.0/bin/llvm-objdump.exe"

echo "=========================================="
echo "  Merging $BRANCH into master"
echo "=========================================="

# Ensure we're on master
git checkout master

# Check for pending commits
COMMITS=$(git log "master..$BRANCH" --oneline 2>/dev/null | wc -l)
if [ "$COMMITS" -eq 0 ]; then
    echo "No new commits on $BRANCH. Nothing to merge."
    exit 0
fi

echo "  $COMMITS new commit(s) on $BRANCH"
git log "master..$BRANCH" --oneline

# Merge
echo ""
echo "Merging..."
git merge "$BRANCH" --no-edit

# Rebuild (single build, save output)
echo ""
echo "Rebuilding..."
python tools/build.py 2>&1 | tee /tmp/merge_build_output.txt
ERRORS=$(grep -ci "error:" /tmp/merge_build_output.txt 2>/dev/null || echo 0)
if [ "$ERRORS" -gt 0 ]; then
    echo "BUILD FAILED with $ERRORS error(s). Aborting."
    echo "Fix the errors, then run: git merge --continue"
    exit 1
fi

# Run prologue fix if available
if [ -f tools/fix_prologue_sched.py ]; then
    python tools/fix_prologue_sched.py \
        build/PostureModule.o build/KineticEnergy.o build/CameraModule.o \
        build/GroundModule.o build/KineticModule.o build/LinkModule.o 2>/dev/null
fi

# Link
echo "Linking..."
"$LLD" --shared -o build/ssbu-decomp.elf \
    --unresolved-symbols=ignore-all -Bsymbolic-functions \
    --no-undefined-version -nostdlib build/*.o

# Verify
echo ""
echo "Verifying..."
python tools/verify_all.py --update --summary

# Count symbols
NSYM=$("$OBJDUMP" -t build/ssbu-decomp.elf | grep 'F .text' | wc -l)
echo "  Total compiled symbols: $NSYM"

# Commit CSV update
if git diff --quiet data/functions.csv; then
    echo "  No CSV changes."
else
    git add data/functions.csv
    git commit -m "Update functions.csv after merging $BRANCH"
fi

# Rebase other workers
if [ "$NO_REBASE" != "--no-rebase" ]; then
    echo ""
    echo "Rebasing other worker branches..."
    ALL_POOLS="pool-a pool-b pool-c pool-d pool-e"
    for P in $ALL_POOLS; do
        if [ "$P" != "$POOL" ]; then
            if git rev-parse --verify "worker/$P" >/dev/null 2>&1; then
                echo "  Rebasing worker/$P..."
                git checkout "worker/$P"
                git rebase master || {
                    echo "  CONFLICT rebasing worker/$P. Resolve manually."
                    git rebase --abort
                }
            fi
        fi
    done
    git checkout master
fi

echo ""
echo "=========================================="
echo "  Merge complete!"
echo "=========================================="
