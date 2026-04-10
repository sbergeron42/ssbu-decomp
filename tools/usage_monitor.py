#!/usr/bin/env python3
"""Monitor pool token usage and signal backoff when approaching limits.

Parses stream-json pool logs to track output token burn rate.
When cumulative usage in the current window exceeds the threshold,
writes a BACKOFF signal file that launch_pools.sh checks before restarting.

Usage:
    python tools/usage_monitor.py                    # Monitor, signal at 90%
    python tools/usage_monitor.py --threshold 0.85   # Signal at 85%
    python tools/usage_monitor.py --status            # Show current usage, no monitoring
    python tools/usage_monitor.py --reset             # Clear backoff signal

The budget window is 5 hours (Claude Max session reset interval).
Budget is set via POOL_TOKEN_BUDGET env var or --budget flag.
"""
import json
import os
import sys
import time
import argparse
from datetime import datetime, timedelta
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent
REPO_ROOT = SCRIPT_DIR.parent
LOG_DIR = REPO_ROOT / "data" / "pool_logs"
SIGNAL_DIR = REPO_ROOT / "data" / "pool_signals"
BACKOFF_FILE = SIGNAL_DIR / "BACKOFF"

# Default budget: conservative estimate for Claude Max 20x per 5-hour window.
# Adjust based on observed limits. This is OUTPUT tokens only (most expensive).
DEFAULT_BUDGET = 5_000_000  # 5M output tokens per 5-hour window
WINDOW_HOURS = 5


def ensure_dirs():
    LOG_DIR.mkdir(parents=True, exist_ok=True)
    SIGNAL_DIR.mkdir(parents=True, exist_ok=True)


def parse_log_usage(log_path, since=None):
    """Sum output tokens from a pool's stream-json log since a given time."""
    total_output = 0
    total_input = 0
    total_cache_read = 0
    total_cache_write = 0
    message_count = 0

    try:
        with open(log_path, "r", encoding="utf-8", errors="replace") as f:
            for line in f:
                line = line.strip()
                if not line.startswith("{"):
                    continue
                try:
                    data = json.loads(line)
                except json.JSONDecodeError:
                    continue

                # Check timestamp if filtering by time
                if since:
                    ts = data.get("timestamp")
                    if ts:
                        try:
                            msg_time = datetime.fromisoformat(ts.replace("Z", "+00:00"))
                            if msg_time.replace(tzinfo=None) < since:
                                continue
                        except (ValueError, TypeError):
                            pass

                # Extract usage from assistant messages
                msg = data.get("message", {})
                usage = msg.get("usage", {})
                if usage:
                    total_output += usage.get("output_tokens", 0)
                    total_input += usage.get("input_tokens", 0)
                    total_cache_read += usage.get("cache_read_input_tokens", 0)
                    total_cache_write += usage.get("cache_creation_input_tokens", 0)
                    if usage.get("output_tokens", 0) > 0:
                        message_count += 1

    except FileNotFoundError:
        pass

    return {
        "output": total_output,
        "input": total_input,
        "cache_read": total_cache_read,
        "cache_write": total_cache_write,
        "messages": message_count,
    }


def get_all_usage(since=None):
    """Get usage across all pool logs."""
    totals = {"output": 0, "input": 0, "cache_read": 0, "cache_write": 0, "messages": 0}
    per_pool = {}

    for log_file in sorted(LOG_DIR.glob("pool-*.log")):
        pool = log_file.stem.replace("pool-", "")
        usage = parse_log_usage(log_file, since)
        per_pool[pool] = usage
        for k in totals:
            totals[k] += usage[k]

    return totals, per_pool


def format_tokens(n):
    if n >= 1_000_000:
        return f"{n/1_000_000:.1f}M"
    elif n >= 1_000:
        return f"{n/1_000:.0f}K"
    return str(n)


def print_status(budget, since):
    totals, per_pool = get_all_usage(since)
    pct = (totals["output"] / budget * 100) if budget > 0 else 0
    backoff_active = BACKOFF_FILE.exists()

    print(f"Window start: {since.strftime('%H:%M:%S')} ({WINDOW_HOURS}h window)")
    print(f"Budget: {format_tokens(budget)} output tokens")
    print(f"Backoff signal: {'ACTIVE' if backoff_active else 'clear'}")
    print()
    print(f"{'Pool':<8} {'Output':>10} {'Input':>10} {'Cache R':>10} {'Cache W':>10} {'Msgs':>6}")
    print("-" * 60)
    for pool in sorted(per_pool.keys()):
        u = per_pool[pool]
        print(f"pool-{pool:<3} {format_tokens(u['output']):>10} {format_tokens(u['input']):>10} "
              f"{format_tokens(u['cache_read']):>10} {format_tokens(u['cache_write']):>10} {u['messages']:>6}")
    print("-" * 60)
    print(f"{'TOTAL':<8} {format_tokens(totals['output']):>10} {format_tokens(totals['input']):>10} "
          f"{format_tokens(totals['cache_read']):>10} {format_tokens(totals['cache_write']):>10} {totals['messages']:>6}")
    print()
    print(f"Usage: {format_tokens(totals['output'])} / {format_tokens(budget)} ({pct:.1f}%)")

    return totals, pct


def signal_backoff(reason):
    """Write the BACKOFF signal file."""
    SIGNAL_DIR.mkdir(parents=True, exist_ok=True)
    with open(BACKOFF_FILE, "w") as f:
        f.write(f"{datetime.now().isoformat()}\n{reason}\n")
    print(f"\n*** BACKOFF SIGNAL WRITTEN: {reason} ***")


def clear_backoff():
    if BACKOFF_FILE.exists():
        BACKOFF_FILE.unlink()
        print("Backoff signal cleared.")
    else:
        print("No backoff signal active.")


def monitor_loop(budget, threshold, interval, since):
    """Continuously monitor usage and signal backoff."""
    print(f"Monitoring every {interval}s | Threshold: {threshold*100:.0f}% of {format_tokens(budget)}")
    print(f"Window: {since.strftime('%H:%M:%S')} + {WINDOW_HOURS}h")
    print("Press Ctrl+C to stop.\n")

    try:
        while True:
            totals, pct = print_status(budget, since)

            if pct >= threshold * 100 and not BACKOFF_FILE.exists():
                signal_backoff(
                    f"Usage at {pct:.1f}% ({format_tokens(totals['output'])} / {format_tokens(budget)})"
                )

            # Check if window has expired → reset
            if datetime.now() > since + timedelta(hours=WINDOW_HOURS):
                new_since = datetime.now()
                print(f"\n--- Window reset at {new_since.strftime('%H:%M:%S')} ---\n")
                if BACKOFF_FILE.exists():
                    clear_backoff()
                since = new_since

            time.sleep(interval)
            # Clear screen for readability
            print("\n" + "=" * 60 + "\n")

    except KeyboardInterrupt:
        print("\nMonitor stopped.")


def main():
    parser = argparse.ArgumentParser(description="Pool usage monitor")
    parser.add_argument("--budget", type=int, default=None,
                        help=f"Output token budget per {WINDOW_HOURS}h window (default: {DEFAULT_BUDGET})")
    parser.add_argument("--threshold", type=float, default=0.90,
                        help="Backoff threshold as fraction (default: 0.90)")
    parser.add_argument("--interval", type=int, default=60,
                        help="Check interval in seconds (default: 60)")
    parser.add_argument("--status", action="store_true",
                        help="Show current usage and exit")
    parser.add_argument("--reset", action="store_true",
                        help="Clear backoff signal and exit")
    args = parser.parse_args()

    ensure_dirs()

    budget = args.budget or int(os.environ.get("POOL_TOKEN_BUDGET", DEFAULT_BUDGET))
    since = datetime.now() - timedelta(hours=WINDOW_HOURS)

    if args.reset:
        clear_backoff()
        return

    if args.status:
        print_status(budget, since)
        return

    monitor_loop(budget, args.threshold, args.interval, since)


if __name__ == "__main__":
    main()
