#!/bin/bash
# Worker notification: triggers orchestrator lambda to merge + reassign.
# Usage: bash tools/notify_done.sh pool-a "Fixed 5 functions"

POOL="$1"
MSG="${2:-done}"
REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"

echo "[$POOL] Triggering orchestrator lambda..."
echo "[$POOL] Message: $MSG"

# Invoke Claude as a one-shot orchestrator lambda with full permissions
claude -p "Run: python tools/orchestrate_merge.py $POOL" \
  --cwd "$REPO_ROOT" \
  --model sonnet \
  --dangerously-skip-permissions \
  2>&1

echo ""
echo "[$POOL] Orchestrator complete. Check WORKER.md for your next assignment."
echo "[$POOL] Run: cat WORKER.md"
