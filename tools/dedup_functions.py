#!/usr/bin/env python3
"""
Remove duplicate function definitions across source files.

For each function defined in multiple files, keeps the version in the
highest-priority file (medium > easy > batch_c > batch_d3 > batch_d4 > batch_e)
and removes it from lower-priority files.

Usage:
    python tools/dedup_functions.py              # Dry run
    python tools/dedup_functions.py --apply      # Apply changes
"""

import argparse
import collections
import glob
import os
import re
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIR = os.path.join(PROJECT_ROOT, "src", "app")

# File priority: higher number = keep this version
def file_priority(path):
    base = os.path.basename(path)
    if base.startswith("fun_medium"):
        return 50
    if base.startswith("fun_easy"):
        return 40
    if base.startswith("fun_batch_c"):
        return 30
    if base.startswith("fun_batch_d3"):
        return 20
    if base.startswith("fun_batch_d4"):
        return 15
    if base.startswith("fun_batch_e"):
        return 10
    return 5  # lua_bind or other files


def find_function_spans(filepath):
    """Find all FUN_* definitions with their line ranges (start, end inclusive)."""
    with open(filepath, encoding="utf-8", errors="replace") as f:
        lines = f.readlines()

    spans = []  # (func_name, start_line_0idx, end_line_0idx)
    i = 0
    while i < len(lines):
        line = lines[i]
        # Match function definition (not extern, not comment, not forward decl)
        m = re.match(r'^(?!extern\b)(?!//\s)(?:\[\[[^\]]*\]\]\s*)?[\w][\w *&:]*(FUN_[0-9a-fA-F]+)\s*\(', line)
        if m:
            func_name = m.group(1)
            # Find the opening brace
            start = i
            brace_depth = 0
            found_brace = False
            j = i
            while j < len(lines):
                for ch in lines[j]:
                    if ch == '{':
                        brace_depth += 1
                        found_brace = True
                    elif ch == '}':
                        brace_depth -= 1
                        if found_brace and brace_depth == 0:
                            spans.append((func_name, start, j))
                            i = j + 1
                            break
                else:
                    j += 1
                    continue
                break
            else:
                # Couldn't find matching brace - skip
                i += 1
                continue
            continue
        i += 1

    return spans


def remove_spans_from_file(filepath, spans_to_remove, dry_run=True):
    """Remove the given line spans from a file."""
    with open(filepath, encoding="utf-8", errors="replace") as f:
        lines = f.readlines()

    # Build set of lines to remove
    remove_lines = set()
    for _, start, end in spans_to_remove:
        # Also remove blank lines and comments immediately above the function
        prefix_start = start
        while prefix_start > 0 and lines[prefix_start - 1].strip().startswith("//"):
            prefix_start -= 1
        # Remove one blank line above comments if present
        if prefix_start > 0 and lines[prefix_start - 1].strip() == "":
            prefix_start -= 1
        for l in range(prefix_start, end + 1):
            remove_lines.add(l)
        # Remove trailing blank line too
        if end + 1 < len(lines) and lines[end + 1].strip() == "" and (end + 1) not in remove_lines:
            remove_lines.add(end + 1)

    new_lines = [line for i, line in enumerate(lines) if i not in remove_lines]

    if not dry_run:
        with open(filepath, "w", encoding="utf-8") as f:
            f.writelines(new_lines)

    return len(remove_lines)


def main():
    parser = argparse.ArgumentParser(description="Deduplicate FUN_* definitions")
    parser.add_argument("--apply", action="store_true", help="Apply changes (default: dry run)")
    args = parser.parse_args()

    cpp_files = sorted(glob.glob(os.path.join(SRC_DIR, "*.cpp")))

    # Gather all function definitions
    all_funcs = collections.defaultdict(list)  # func_name -> [(filepath, start, end)]
    for f in cpp_files:
        spans = find_function_spans(f)
        for func_name, start, end in spans:
            all_funcs[func_name].append((f, start, end))

    # Find duplicates
    duplicates = {k: v for k, v in all_funcs.items() if len(v) > 1}
    print(f"Found {len(duplicates)} functions with duplicate definitions")

    # For each duplicate, decide which to keep (highest priority file)
    removals = collections.defaultdict(list)  # filepath -> [(func_name, start, end)]
    kept_count = 0

    for func_name, locations in sorted(duplicates.items()):
        # Sort by file priority descending - keep the highest
        locations.sort(key=lambda x: file_priority(x[0]), reverse=True)
        keep = locations[0]
        for loc in locations[1:]:
            removals[loc[0]].append((func_name, loc[1], loc[2]))
        # Also handle same-file duplicates: if multiple in the same file, keep first
        same_file = collections.defaultdict(list)
        for loc in locations:
            same_file[loc[0]].append(loc)
        for filepath, locs in same_file.items():
            if len(locs) > 1:
                # Keep first, remove rest
                for extra in locs[1:]:
                    if extra not in [r for r in removals.get(filepath, [])]:
                        removals[filepath].append((extra[0] if isinstance(extra[0], str) else func_name, extra[1], extra[2]))
        kept_count += 1

    total_removed = 0
    files_modified = 0
    for filepath, spans in sorted(removals.items()):
        n = len(spans)
        func_names = [s[0] for s in spans]
        basename = os.path.basename(filepath)
        print(f"  {basename}: removing {n} functions")
        if n <= 5:
            for fn in func_names:
                print(f"    - {fn}")

        removed_lines = remove_spans_from_file(filepath, spans, dry_run=not args.apply)
        total_removed += n
        files_modified += 1

    print(f"\n{'Would remove' if not args.apply else 'Removed'} {total_removed} duplicate definitions from {files_modified} files")
    if not args.apply:
        print("Run with --apply to make changes")


if __name__ == "__main__":
    main()
