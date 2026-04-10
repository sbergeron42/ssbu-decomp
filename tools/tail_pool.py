#!/usr/bin/env python3
"""Human-readable live tail of pool logs (stream-json format).

Usage:
    python tools/tail_pool.py a              # Tail pool-a log
    python tools/tail_pool.py a b c          # Tail multiple pools
    python tools/tail_pool.py --all          # Tail all pools
    python tools/tail_pool.py a --last 50    # Show last 50 events then follow
"""
import json
import os
import sys
import time
import argparse

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.dirname(SCRIPT_DIR)
LOG_DIR = os.path.join(REPO_ROOT, "data", "pool_logs")

# ANSI colors for pool differentiation
COLORS = {
    "a": "\033[36m",   # cyan
    "b": "\033[33m",   # yellow
    "c": "\033[32m",   # green
    "d": "\033[35m",   # magenta
    "e": "\033[34m",   # blue
    "f": "\033[96m",   # bright cyan
    "g": "\033[93m",   # bright yellow
    "h": "\033[92m",   # bright green
    "i": "\033[95m",   # bright magenta
    "j": "\033[94m",   # bright blue
}
RESET = "\033[0m"
DIM = "\033[2m"
BOLD = "\033[1m"


def format_event(line, pool):
    """Parse a stream-json line and return a human-readable string, or None to skip."""
    line = line.strip()
    if not line:
        return None

    # Plain text lines (timestamps, errors)
    if not line.startswith("{"):
        return line

    try:
        data = json.loads(line)
    except json.JSONDecodeError:
        return line

    msg_type = data.get("type", "")
    message = data.get("message", {})
    content = message.get("content", [])

    if msg_type == "assistant":
        parts = []
        for block in content:
            if block.get("type") == "text":
                text = block.get("text", "").strip()
                if text:
                    parts.append(text)
            elif block.get("type") == "tool_use":
                name = block.get("name", "?")
                inp = block.get("input", {})
                # Summarize tool calls concisely
                if name == "Edit":
                    fp = inp.get("file_path", "?")
                    parts.append(f"{DIM}[Edit {os.path.basename(fp)}]{RESET}")
                elif name == "Write":
                    fp = inp.get("file_path", "?")
                    parts.append(f"{DIM}[Write {os.path.basename(fp)}]{RESET}")
                elif name == "Read":
                    fp = inp.get("file_path", "?")
                    parts.append(f"{DIM}[Read {os.path.basename(fp)}]{RESET}")
                elif name == "Bash":
                    cmd = inp.get("command", "?")
                    if len(cmd) > 80:
                        cmd = cmd[:77] + "..."
                    parts.append(f"{DIM}[$ {cmd}]{RESET}")
                elif name == "Grep":
                    pat = inp.get("pattern", "?")
                    parts.append(f"{DIM}[Grep '{pat}']{RESET}")
                elif name == "Glob":
                    pat = inp.get("pattern", "?")
                    parts.append(f"{DIM}[Glob '{pat}']{RESET}")
                elif name.startswith("mcp__ghidra__"):
                    short = name.replace("mcp__ghidra__", "")
                    addr = inp.get("address", inp.get("name", ""))
                    parts.append(f"{DIM}[Ghidra:{short} {addr}]{RESET}")
                elif name == "TaskCreate" or name == "TaskUpdate":
                    parts.append(f"{DIM}[{name}]{RESET}")
                else:
                    parts.append(f"{DIM}[{name}]{RESET}")
        if parts:
            return " ".join(parts)
        return None

    elif msg_type == "user":
        # Tool results — usually very verbose, just show a summary
        for block in content:
            if block.get("type") == "tool_result":
                result = block.get("content", "")
                if isinstance(result, str) and len(result) > 0:
                    # Show first line only
                    first = result.split("\n")[0][:100]
                    if first.strip():
                        return f"{DIM}  → {first}{RESET}"
        return None

    elif msg_type == "result":
        # Final result
        result = data.get("result", "")
        cost = data.get("cost_usd", 0)
        duration = data.get("duration_ms", 0)
        turns = data.get("num_turns", 0)
        if result:
            return f"{BOLD}DONE ({turns} turns, {duration/1000:.0f}s): {result[:200]}{RESET}"
        return None

    return None


def tail_file(path, pool, last_n=0):
    """Generator that yields formatted lines from a log file, following new content."""
    color = COLORS.get(pool, "")
    prefix = f"{color}[pool-{pool}]{RESET} "

    try:
        with open(path, "r", encoding="utf-8", errors="replace") as f:
            if last_n > 0:
                # Read all lines, show last N
                lines = f.readlines()
                start = max(0, len(lines) - last_n)
                for line in lines[start:]:
                    formatted = format_event(line, pool)
                    if formatted:
                        yield prefix + formatted
            else:
                # Seek to end
                f.seek(0, 2)

            # Follow
            while True:
                line = f.readline()
                if line:
                    formatted = format_event(line, pool)
                    if formatted:
                        yield prefix + formatted
                else:
                    yield None  # Signal: no new data


    except FileNotFoundError:
        yield f"{prefix}Log file not found: {path}"


def main():
    parser = argparse.ArgumentParser(description="Human-readable pool log viewer")
    parser.add_argument("pools", nargs="*", help="Pool letters (a-j)")
    parser.add_argument("--all", action="store_true", help="Tail all pools")
    parser.add_argument("--last", type=int, default=20, help="Show last N events then follow (default: 20)")
    args = parser.parse_args()

    if args.all:
        # Auto-detect pool logs that exist in LOG_DIR
        pools = sorted(
            f[5:-4] for f in os.listdir(LOG_DIR)
            if f.startswith("pool-") and f.endswith(".log")
        )
    elif args.pools:
        pools = args.pools
    else:
        print("Usage: python tools/tail_pool.py a [b c ...] | --all")
        sys.exit(1)

    # Set up generators for each pool
    generators = {}
    for pool in pools:
        log_path = os.path.join(LOG_DIR, f"pool-{pool}.log")
        generators[pool] = tail_file(log_path, pool, args.last)

    print(f"{BOLD}Tailing pools: {', '.join(pools)}{RESET}")
    print(f"{DIM}(Ctrl+C to stop){RESET}")
    print()

    # Show initial backlog
    for pool in pools:
        gen = generators[pool]
        while True:
            try:
                line = next(gen)
                if line is None:
                    break
                print(line)
            except StopIteration:
                break

    # Live follow — round-robin across pools
    try:
        while True:
            any_output = False
            for pool in pools:
                gen = generators[pool]
                try:
                    line = next(gen)
                    if line is not None:
                        print(line)
                        any_output = True
                except StopIteration:
                    pass
            if not any_output:
                time.sleep(0.5)
    except KeyboardInterrupt:
        print(f"\n{DIM}Stopped.{RESET}")


if __name__ == "__main__":
    main()
