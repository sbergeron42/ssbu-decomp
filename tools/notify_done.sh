#!/bin/bash
# Worker notification: signal the orchestrator that this pool is done.
# Usage: bash tools/notify_done.sh pool-a "Fixed 5 functions"
#
# Workers should run this after their final commit.

POOL="$1"
MSG="${2:-done}"
BUS_DIR="$(dirname "$0")/../.claude_bus"

mkdir -p "$BUS_DIR"
echo "$(date +%H:%M:%S) $MSG" > "$BUS_DIR/$POOL.done"
echo "Notified orchestrator: $POOL is done ($MSG)"
