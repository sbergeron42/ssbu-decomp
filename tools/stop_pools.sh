#!/bin/bash
# Gracefully stop running pool sessions.
#
# Usage:
#   bash tools/stop_pools.sh              # Stop all pools
#   bash tools/stop_pools.sh a c          # Stop specific pools
#   TIMEOUT=120 bash tools/stop_pools.sh  # Custom wait before SIGKILL

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"
PARENT_DIR="$(dirname "$REPO_ROOT")"
SIGNAL_DIR="$REPO_ROOT/data/pool_signals"
LOCK_DIR="$REPO_ROOT/data/pool_locks"
LOG_DIR="$REPO_ROOT/data/pool_logs"
TIMEOUT="${TIMEOUT:-300}"

if [ $# -eq 0 ]; then
    POOLS="a b c d e f g h i j"
else
    POOLS="$@"
fi

echo "========================================"
echo "  Stopping pools: $POOLS"
echo "  Timeout: ${TIMEOUT}s"
echo "========================================"

# Step 1: Write WRAPUP signal files and send SIGINT
PIDS_TO_WAIT=()
for POOL in $POOLS; do
    # Write WRAPUP signal so Claude checks it at next break point
    touch "$SIGNAL_DIR/WRAPUP-pool-$POOL"
    echo "  [pool-$POOL] WRAPUP signal written"

    PID_FILE="$SIGNAL_DIR/pid-pool-$POOL"
    if [ -f "$PID_FILE" ]; then
        PID=$(cat "$PID_FILE")
        if kill -0 "$PID" 2>/dev/null; then
            kill -INT "$PID" 2>/dev/null
            echo "  [pool-$POOL] SIGINT sent to PID $PID"
            PIDS_TO_WAIT+=("$POOL:$PID")
        else
            echo "  [pool-$POOL] PID $PID already dead"
            rm -f "$PID_FILE"
        fi
    else
        echo "  [pool-$POOL] No PID file found"
    fi
done

# Also write global WRAPUP (catches any pool that checks the generic file)
touch "$SIGNAL_DIR/WRAPUP"

if [ ${#PIDS_TO_WAIT[@]} -eq 0 ]; then
    echo ""
    echo "No running pools found. Cleaning up signal files."
    rm -f "$SIGNAL_DIR"/WRAPUP "$SIGNAL_DIR"/WRAPUP-pool-*
    exit 0
fi

# Step 2: Wait for graceful exit
echo ""
echo "Waiting up to ${TIMEOUT}s for graceful shutdown..."
ELAPSED=0
while [ $ELAPSED -lt $TIMEOUT ] && [ ${#PIDS_TO_WAIT[@]} -gt 0 ]; do
    sleep 5
    ELAPSED=$((ELAPSED + 5))
    STILL_ALIVE=()
    for ENTRY in "${PIDS_TO_WAIT[@]}"; do
        POOL="${ENTRY%%:*}"
        PID="${ENTRY##*:}"
        if kill -0 "$PID" 2>/dev/null; then
            STILL_ALIVE+=("$ENTRY")
        else
            echo "  [pool-$POOL] Exited cleanly (${ELAPSED}s)"
            rm -f "$SIGNAL_DIR/pid-pool-$POOL"
        fi
    done
    PIDS_TO_WAIT=("${STILL_ALIVE[@]}")
    if [ ${#PIDS_TO_WAIT[@]} -gt 0 ]; then
        NAMES=$(printf "%s " "${PIDS_TO_WAIT[@]}" | sed 's/:[0-9]*//g')
        echo "  Still alive (${ELAPSED}s): $NAMES"
    fi
done

# Step 3: SIGKILL anything still alive
if [ ${#PIDS_TO_WAIT[@]} -gt 0 ]; then
    echo ""
    echo "Timeout reached. Sending SIGKILL..."
    for ENTRY in "${PIDS_TO_WAIT[@]}"; do
        POOL="${ENTRY%%:*}"
        PID="${ENTRY##*:}"
        if kill -0 "$PID" 2>/dev/null; then
            kill -9 "$PID" 2>/dev/null
            echo "  [pool-$POOL] SIGKILL sent to PID $PID"
        fi
        rm -f "$SIGNAL_DIR/pid-pool-$POOL"
    done
fi

# Step 4: Auto-recover uncommitted work
echo ""
echo "Checking for uncommitted work..."
for POOL in $POOLS; do
    WORKTREE="$PARENT_DIR/SSBU Decomp-pool-$POOL"
    if [ -d "$WORKTREE" ]; then
        cd "$WORKTREE"
        UNCOMMITTED=$(git diff --stat HEAD 2>/dev/null | tail -1)
        if [ -n "$UNCOMMITTED" ]; then
            echo "  [pool-$POOL] Recovering: $UNCOMMITTED"
            git add -A
            git commit -m "pool-$POOL: auto-recover uncommitted work (stop_pools)" \
                >> "$LOG_DIR/pool-$POOL.log" 2>&1 || true
        else
            echo "  [pool-$POOL] Clean"
        fi
    fi
done

# Step 5: Clean up signal and lock files
rm -f "$SIGNAL_DIR"/WRAPUP "$SIGNAL_DIR"/WRAPUP-pool-*
for POOL in $POOLS; do
    rm -f "$LOCK_DIR/LOCK-pool-$POOL"
done

echo ""
echo "All pools stopped."
