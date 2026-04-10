#!/bin/bash
# Launch Claude Code worker pools with crash recovery.
#
# Usage:
#   bash tools/launch_pools.sh                    # Launch all pools (a-e)
#   bash tools/launch_pools.sh a b c              # Launch specific pools
#   CLAUDE_FLAGS="--model opus" bash tools/launch_pools.sh  # Custom flags
#
# Each pool runs in its own background process. If a session crashes (segfault,
# context limit), uncommitted work is auto-recovered and the session relaunches.
#
# Requires: claude CLI installed

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"
PARENT_DIR="$(dirname "$REPO_ROOT")"

# Find claude executable — check PATH, then known locations (Git Bash + WSL paths)
if command -v claude &>/dev/null; then
    CLAUDE_BIN="claude"
elif [ -f "$HOME/.local/bin/claude" ]; then
    CLAUDE_BIN="$HOME/.local/bin/claude"
elif [ -f "/c/Users/seanb/.local/bin/claude" ]; then
    CLAUDE_BIN="/c/Users/seanb/.local/bin/claude"
elif [ -f "/mnt/c/Users/seanb/.local/bin/claude" ]; then
    CLAUDE_BIN="/mnt/c/Users/seanb/.local/bin/claude"
elif [ -f "C:/Users/seanb/.local/bin/claude" ]; then
    CLAUDE_BIN="C:/Users/seanb/.local/bin/claude"
elif [ -n "${CLAUDE_BIN:-}" ] && [ -f "$CLAUDE_BIN" ]; then
    : # user-provided CLAUDE_BIN via env var
else
    echo "ERROR: claude executable not found."
    echo "Try: CLAUDE_BIN=/path/to/claude bash tools/launch_pools.sh"
    exit 1
fi
echo "Using claude at: $CLAUDE_BIN"
LOG_DIR="$REPO_ROOT/data/pool_logs"
SIGNAL_DIR="$REPO_ROOT/data/pool_signals"
LOCK_DIR="$REPO_ROOT/data/pool_locks"
BACKOFF_FILE="$SIGNAL_DIR/BACKOFF"
DEVICE_ID="${DEVICE_ID:-$(hostname)}"
mkdir -p "$LOG_DIR" "$SIGNAL_DIR" "$LOCK_DIR"

# Default pools or from args
if [ $# -eq 0 ]; then
    POOLS="a b c d e f g h i j"
else
    POOLS="$@"
fi

# --dangerously-skip-permissions is ALWAYS included so pools run unattended.
# EXTRA_CLAUDE_FLAGS can add more flags (e.g., --model opus) without removing the skip.
EXTRA_CLAUDE_FLAGS="${EXTRA_CLAUDE_FLAGS:-}"

is_locked_by_other() {
    local POOL="$1"
    local LOCK_FILE="$LOCK_DIR/LOCK-pool-$POOL"
    if [ ! -f "$LOCK_FILE" ]; then
        return 1  # not locked
    fi
    local LOCK_DEVICE=$(head -1 "$LOCK_FILE" 2>/dev/null)
    if [ "$LOCK_DEVICE" = "$DEVICE_ID" ]; then
        return 1  # locked by us (stale from previous run)
    fi
    # Check if lock is stale (>1 hour old)
    local LOCK_AGE=$(( $(date +%s) - $(date -r "$LOCK_FILE" +%s 2>/dev/null || echo 0) ))
    if [ "$LOCK_AGE" -gt 3600 ]; then
        echo "  [pool-$POOL] Breaking stale lock from $LOCK_DEVICE (${LOCK_AGE}s old)"
        rm -f "$LOCK_FILE"
        return 1  # stale, treat as unlocked
    fi
    return 0  # locked by another device
}

acquire_lock() {
    local POOL="$1"
    local LOCK_FILE="$LOCK_DIR/LOCK-pool-$POOL"
    echo "$DEVICE_ID" > "$LOCK_FILE"
    echo "$(date +%s)" >> "$LOCK_FILE"
}

release_lock() {
    local POOL="$1"
    rm -f "$LOCK_DIR/LOCK-pool-$POOL"
}

launch_pool() {
    local POOL="$1"
    local WORKTREE="$PARENT_DIR/SSBU Decomp-pool-$POOL"
    local LOG="$LOG_DIR/pool-$POOL.log"
    local WORKER_MD="$WORKTREE/WORKER-pool-$POOL.md"

    if [ ! -d "$WORKTREE" ]; then
        echo "  [pool-$POOL] Worktree not found: $WORKTREE — skipping"
        return 0
    fi

    if [ ! -f "$WORKER_MD" ]; then
        echo "  [pool-$POOL] No WORKER-pool-$POOL.md — skipping (unassigned)"
        return 0
    fi

    if is_locked_by_other "$POOL"; then
        local LOCK_DEVICE=$(head -1 "$LOCK_DIR/LOCK-pool-$POOL" 2>/dev/null)
        echo "  [pool-$POOL] Locked by $LOCK_DEVICE — skipping"
        return 0
    fi

    acquire_lock "$POOL"
    echo "  [pool-$POOL] Launching in $WORKTREE"
    echo "  [pool-$POOL] Log: $LOG"

    (
        # Release lock when this subshell exits (clean or crash)
        trap "release_lock $POOL" EXIT

        while true; do
            echo "$(date): Starting pool-$POOL session" >> "$LOG"

            # Run Claude Code (--dangerously-skip-permissions always on for unattended operation)
            cd "$WORKTREE"
            "$CLAUDE_BIN" --dangerously-skip-permissions $EXTRA_CLAUDE_FLAGS \
                --output-format stream-json \
                -p "Read WORKER-pool-${POOL}.md and continue decomp work. Commit every 15-20 functions or every 30 minutes. Save Ghidra results to data/ghidra_cache/pool-${POOL}.txt. IMPORTANT: Before starting each new function, check if the file data/pool_signals/WRAPUP or data/pool_signals/WRAPUP-pool-${POOL} exists. If it does, commit all current work immediately and exit." \
                >> "$LOG" 2>&1 &
            CLAUDE_PID=$!
            echo "$CLAUDE_PID" > "$SIGNAL_DIR/pid-pool-$POOL"
            wait $CLAUDE_PID
            EXIT_CODE=$?
            rm -f "$SIGNAL_DIR/pid-pool-$POOL"

            echo "$(date): pool-$POOL exited with code $EXIT_CODE" >> "$LOG"

            # Check for uncommitted work
            cd "$WORKTREE"
            UNCOMMITTED=$(git diff --stat HEAD 2>/dev/null | tail -1)
            if [ -n "$UNCOMMITTED" ]; then
                echo "$(date): Recovering uncommitted work: $UNCOMMITTED" >> "$LOG"
                git add -A
                git commit -m "pool-$POOL: auto-recover uncommitted work after crash" \
                    >> "$LOG" 2>&1 || true
            fi

            # If clean exit (user quit), don't restart
            if [ $EXIT_CODE -eq 0 ]; then
                echo "$(date): pool-$POOL exited cleanly, not restarting" >> "$LOG"
                break
            fi

            # Check for WRAPUP or BACKOFF signal before restarting
            if [ -f "$SIGNAL_DIR/WRAPUP" ] || [ -f "$SIGNAL_DIR/WRAPUP-pool-$POOL" ]; then
                echo "$(date): WRAPUP signal detected — pool-$POOL stopping" >> "$LOG"
                break
            fi
            if [ -f "$BACKOFF_FILE" ]; then
                echo "$(date): BACKOFF signal detected — pool-$POOL stopping ($(cat "$BACKOFF_FILE" | head -2 | tr '\n' ' '))" >> "$LOG"
                break
            fi

            # Crash: wait briefly then restart
            echo "$(date): pool-$POOL crashed (code $EXIT_CODE), restarting in 10s..." >> "$LOG"
            sleep 10
        done
    ) &

    echo "  [pool-$POOL] PID: $!"
}

echo "========================================"
echo "  SSBU Decomp Pool Launcher"
echo "  Pools: $POOLS"
echo "  Mode: --dangerously-skip-permissions (unattended)"
echo "  Extra flags: ${EXTRA_CLAUDE_FLAGS:-none}"
echo "========================================"

for POOL in $POOLS; do
    launch_pool "$POOL"
done

echo ""
echo "All pools launched. Monitor with:"
echo "  tail -f $LOG_DIR/pool-*.log"
echo ""
echo "Stop all pools:"
echo "  kill \$(jobs -p)"

# Wait for all background jobs
wait
