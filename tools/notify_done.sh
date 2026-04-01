#!/bin/bash
# Worker loop: orchestrate merge + reassign + auto-start next round.
# Creates a self-sustaining loop: worker → merge → reassign → worker → ...
#
# Usage: bash tools/notify_done.sh pool-a "Fixed 5 functions"

POOL="$1"
MSG="${2:-done}"
REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
WORKTREE="$(cd "$REPO_ROOT/.." && pwd)/SSBU Decomp-$POOL"

echo ""
echo "============================================"
echo "  [$POOL] Round complete: $MSG"
echo "============================================"
echo ""

# --- Step 1: Orchestrator lambda (merge + reassign) ---
echo "[$POOL] Step 1: Running orchestrator lambda..."
claude -p "Run this exact command and show its output: python tools/orchestrate_merge.py $POOL" \
  --cwd "$REPO_ROOT" \
  --model sonnet \
  --dangerously-skip-permissions \
  2>&1

echo ""

# --- Step 2: Check if new work was assigned ---
if [ ! -f "$WORKTREE/WORKER.md" ]; then
  echo "[$POOL] ERROR: WORKER.md not found at $WORKTREE"
  exit 1
fi

if grep -q "No more work available" "$WORKTREE/WORKER.md"; then
  echo "============================================"
  echo "  [$POOL] No more work available. Stopping."
  echo "============================================"
  exit 0
fi

echo "[$POOL] Step 2: New work assigned. Starting next round..."
echo ""

# --- Step 3: Spawn worker lambda for next round ---
claude -p "You are a decomp worker. Read WORKER.md for your assignment. Decompile ALL assigned functions using Ghidra MCP to disassemble originals, write matching C++, compile with 'cmd /c build.bat', and verify with 'python tools/verify_local.py --build'. Commit all changes to your branch with 'git add src/ && git commit -m \"description\"'. When ALL assigned work is done, run: bash tools/notify_done.sh $POOL \"description of what you did\"" \
  --cwd "$WORKTREE" \
  --model sonnet \
  --dangerously-skip-permissions \
  2>&1

# If we get here, the worker lambda exited without calling notify_done.sh
echo "[$POOL] Worker lambda exited. Check $WORKTREE for results."
