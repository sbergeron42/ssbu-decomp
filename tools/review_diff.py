#!/usr/bin/env python3
"""
review_diff.py — Automated code quality reviewer for worker pool diffs.

Runs against a worker branch diff and reports violations of the struct-first
coding rules. Returns exit code 1 if any HARD violations are found (merge
should be rejected), exit code 0 if clean or only warnings.

Usage:
    python tools/review_diff.py pool-a          # Review pool-a vs master
    python tools/review_diff.py pool-c --strict # Also fail on warnings
    python tools/review_diff.py --diff file.patch  # Review a patch file
"""

import argparse
import re
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from typing import List


@dataclass
class Violation:
    file: str
    line: int
    rule: str
    severity: str  # "REJECT" or "WARN"
    snippet: str
    suggestion: str = ""


@dataclass
class FileReport:
    path: str
    violations: List[Violation] = field(default_factory=list)
    new_lines: int = 0
    reinterpret_casts: int = 0
    raw_offsets: int = 0
    naked_asm: int = 0
    new_structs: int = 0
    vtable_wrappers_used: int = 0


def get_diff(pool_name: str) -> str:
    """Get the diff between master and the worker branch."""
    branch = f"worker/{pool_name}"
    result = subprocess.run(
        ["git", "diff", f"master...{branch}", "--", "src/", "include/"],
        capture_output=True, encoding="utf-8", errors="replace"
    )
    if result.returncode != 0:
        print(f"Error: could not diff master...{branch}: {result.stderr}")
        sys.exit(2)
    return result.stdout


def parse_diff(diff_text: str) -> dict:
    """Parse unified diff into {filepath: [(line_no, line_text), ...]} for added lines only."""
    files = {}
    current_file = None
    current_line = 0

    for line in diff_text.splitlines():
        if line.startswith("+++ b/"):
            current_file = line[6:]
            files[current_file] = []
        elif line.startswith("@@ "):
            # Parse hunk header: @@ -old,count +new,count @@
            m = re.search(r'\+(\d+)', line)
            if m:
                current_line = int(m.group(1)) - 1
        elif line.startswith("+") and not line.startswith("+++"):
            current_line += 1
            if current_file:
                files[current_file].append((current_line, line[1:]))
        elif not line.startswith("-"):
            current_line += 1

    return files


# ── Pattern definitions ──

# Raw hex offset on untyped pointer: *(type*)(ptr + 0xNN) or ptr[0xNN]
RE_RAW_OFFSET = re.compile(
    r'(?:'
    r'\*\s*(?:reinterpret_cast\s*<[^>]+>\s*\(|(?:\([^)]*\*\)\s*\())[^)]*\+\s*0x[0-9a-fA-F]{2,}'  # *(cast)(ptr + 0xNN)
    r'|'
    r'\*\s*\([^)]*\*\)\s*\([^)]*\+\s*0x[0-9a-fA-F]{2,}'  # *(type*)(ptr + 0xNN)
    r'|'
    r'\w+\[0x[0-9a-fA-F]{2,}\s*/\s*\d+\]'  # param_1[0xe7 / 8] style
    r'|'
    r'\w+\[0x[0-9a-fA-F]{2,}\]'  # param_1[0xe7] style
    r')'
)

# reinterpret_cast (any usage)
RE_REINTERPRET = re.compile(r'reinterpret_cast\s*<')

# __attribute__((naked))
RE_NAKED = re.compile(r'__attribute__\s*\(\s*\(\s*naked\s*\)\s*\)')

# Vtable dispatch via raw cast: reinterpret_cast<type>(VT(x)[N]) or (*(void***)ptr)[N]
RE_RAW_VTABLE = re.compile(
    r'reinterpret_cast\s*<[^>]*\(\*\)[^>]*>\s*\('
    r'(?:'
    r'VT\s*\([^)]+\)\s*\[\d+'
    r'|'
    r'\(\s*\*\s*(?:reinterpret_cast\s*<\s*void\s*\*\*\*\s*>|(?:\(void\s*\*\*\*\)))[^)]*\)\s*\[\d+'
    r'|'
    r'vt\s*\[\s*(?:0x)?[0-9a-fA-F]+'
    r')'
)

# New struct/class definition in include/
RE_STRUCT_DEF = re.compile(r'^\s*(?:struct|class)\s+\w+\s*(?:\{|:)')

# Module method wrapper usage (e.g., mod->some_method(...))
RE_METHOD_CALL = re.compile(r'\w+_module\s*->\s*\w+\s*\(')

# Ghidra paste indicators
RE_GHIDRA_VARS = re.compile(r'\b(?:uVar\d+|lVar\d+|plVar\d+|iVar\d+|bVar\d+|param_\d+)\b')

# ITEM_DATA-style nested cast macros
RE_NESTED_CAST_MACRO = re.compile(
    r'reinterpret_cast[^(]*\(\s*'
    r'reinterpret_cast[^(]*\(\s*'
    r'reinterpret_cast'
)


def analyze_file(filepath: str, lines: list) -> FileReport:
    """Analyze added lines in a single file for violations."""
    report = FileReport(path=filepath, new_lines=len(lines))

    # Track distinct offsets per pointer base to detect 3+ offset rule
    # Simple heuristic: count unique hex offsets in the file
    offsets_per_function = defaultdict(set)
    current_func = "unknown"

    for line_no, text in lines:
        stripped = text.strip()

        # Track function boundaries
        func_match = re.match(r'(?:extern\s+"C"\s+)?\w[\w:*&\s]*\s+(\w+)\s*\(', stripped)
        if func_match and not stripped.startswith("//"):
            current_func = func_match.group(1)

        # Skip comments and preprocessor
        if stripped.startswith("//") or stripped.startswith("#") or stripped.startswith("*"):
            continue

        # ── REJECT: naked asm ──
        if RE_NAKED.search(text):
            report.naked_asm += 1
            report.violations.append(Violation(
                file=filepath, line=line_no, rule="NO_NAKED_ASM",
                severity="REJECT", snippet=stripped,
                suggestion="Decomp the function properly or skip it entirely."
            ))

        # ── REJECT: Ghidra variable names in new code ──
        ghidra_matches = RE_GHIDRA_VARS.findall(text)
        if ghidra_matches and "param_1" not in stripped:  # param_1 sometimes used intentionally
            for var in ghidra_matches:
                if var.startswith("param_"):
                    continue  # allow param_N for now
                report.violations.append(Violation(
                    file=filepath, line=line_no, rule="NO_GHIDRA_VARS",
                    severity="REJECT", snippet=stripped,
                    suggestion=f"Rename '{var}' to something meaningful. "
                               "Ghidra default names indicate unprocessed paste."
                ))

        # ── REJECT: nested reinterpret_cast macros (3+ deep) ──
        if RE_NESTED_CAST_MACRO.search(text):
            report.violations.append(Violation(
                file=filepath, line=line_no, rule="NO_NESTED_CASTS",
                severity="REJECT", snippet=stripped[:120],
                suggestion="Define a struct for the pointer chain instead of "
                           "nesting 3+ reinterpret_casts."
            ))

        # ── Count reinterpret_casts ──
        rc_count = len(RE_REINTERPRET.findall(text))
        report.reinterpret_casts += rc_count

        # ── Count raw offsets ──
        offset_matches = RE_RAW_OFFSET.findall(text)
        if offset_matches:
            report.raw_offsets += len(offset_matches)
            # Extract hex offsets for the 3+ rule
            for m in re.finditer(r'0x([0-9a-fA-F]{2,})', text):
                offsets_per_function[current_func].add(m.group(1))

        # ── WARN: raw vtable dispatch ──
        if RE_RAW_VTABLE.search(text):
            report.violations.append(Violation(
                file=filepath, line=line_no, rule="USE_VTABLE_WRAPPERS",
                severity="WARN", snippet=stripped[:120],
                suggestion="Check include/app/modules/ for a typed wrapper method."
            ))

        # ── Count positive signals ──
        if RE_STRUCT_DEF.search(text) and "include/" in filepath:
            report.new_structs += 1
        if RE_METHOD_CALL.search(text):
            report.vtable_wrappers_used += 1

    # ── REJECT: functions with 3+ distinct offsets and no struct ──
    for func_name, offsets in offsets_per_function.items():
        if len(offsets) >= 3 and "include/" not in filepath:
            report.violations.append(Violation(
                file=filepath, line=0, rule="STRUCT_REQUIRED",
                severity="REJECT",
                snippet=f"Function '{func_name}' accesses {len(offsets)} distinct "
                        f"offsets: {', '.join('0x'+o for o in sorted(offsets)[:6])}",
                suggestion="Define or extend a struct in include/ before writing "
                           "this function. Raw offset access on 3+ fields means "
                           "the struct layout is known enough to type."
            ))

    return report


def print_report(reports: list, strict: bool = False) -> int:
    """Print the review report and return exit code."""
    total_violations = 0
    reject_count = 0
    warn_count = 0
    total_reinterpret = 0
    total_raw_offsets = 0
    total_naked = 0
    total_new_structs = 0
    total_new_lines = 0

    file_reports = []

    for report in reports:
        if not report.new_lines:
            continue
        total_new_lines += report.new_lines
        total_reinterpret += report.reinterpret_casts
        total_raw_offsets += report.raw_offsets
        total_naked += report.naked_asm
        total_new_structs += report.new_structs

        rejects = [v for v in report.violations if v.severity == "REJECT"]
        warns = [v for v in report.violations if v.severity == "WARN"]
        reject_count += len(rejects)
        warn_count += len(warns)

        if report.violations:
            file_reports.append(report)

    # ── Header ──
    print("=" * 70)
    print("  WORKER POOL CODE REVIEW")
    print("=" * 70)
    print()

    # ── Summary metrics ──
    print(f"  New lines:          {total_new_lines}")
    print(f"  reinterpret_cast:   {total_reinterpret}", end="")
    if total_new_lines > 0:
        density = total_reinterpret / total_new_lines * 100
        print(f"  ({density:.1f}% of new lines)")
    else:
        print()
    print(f"  Raw hex offsets:    {total_raw_offsets}", end="")
    if total_new_lines > 0:
        density = total_raw_offsets / total_new_lines * 100
        print(f"  ({density:.1f}% of new lines)")
    else:
        print()
    print(f"  naked asm:          {total_naked}")
    print(f"  New structs:        {total_new_structs}")
    print()

    # ── Quality score ──
    if total_new_lines > 0:
        # Penalty-based score: start at 100, lose points for bad patterns
        score = 100
        score -= min(40, total_reinterpret * 2)  # -2 per cast, cap 40
        score -= min(30, total_raw_offsets * 0.5) # -0.5 per offset, cap 30
        score -= total_naked * 20                  # -20 per naked
        score += total_new_structs * 10            # +10 per new struct
        score = max(0, min(100, score))

        if score >= 80:
            grade = "GOOD"
        elif score >= 50:
            grade = "NEEDS WORK"
        else:
            grade = "REJECT"
        print(f"  Quality score:      {score:.0f}/100 ({grade})")
    print()

    # ── Violations ──
    if reject_count > 0:
        print(f"  REJECTIONS: {reject_count}")
        print("-" * 70)
        for report in file_reports:
            rejects = [v for v in report.violations if v.severity == "REJECT"]
            if not rejects:
                continue
            print(f"\n  {report.path}:")
            for v in rejects:
                loc = f":{v.line}" if v.line else ""
                print(f"    [{v.rule}]{loc}")
                print(f"      {v.snippet[:100]}")
                if v.suggestion:
                    print(f"      -> {v.suggestion}")
        print()

    if warn_count > 0:
        print(f"  WARNINGS: {warn_count}")
        print("-" * 70)
        for report in file_reports:
            warns = [v for v in report.violations if v.severity == "WARN"]
            if not warns:
                continue
            print(f"\n  {report.path}:")
            for v in warns:
                print(f"    [{v.rule}]:{v.line}  {v.snippet[:80]}")
        print()

    # ── Verdict ──
    print("=" * 70)
    if reject_count > 0:
        print("  VERDICT: REJECT — fix the above violations before merging")
        print("=" * 70)
        return 1
    elif warn_count > 0 and strict:
        print("  VERDICT: REJECT (--strict) — warnings treated as errors")
        print("=" * 70)
        return 1
    elif warn_count > 0:
        print(f"  VERDICT: PASS with {warn_count} warnings")
        print("=" * 70)
        return 0
    else:
        print("  VERDICT: PASS — clean diff")
        print("=" * 70)
        return 0


def main():
    parser = argparse.ArgumentParser(description="Review worker pool diff for code quality")
    parser.add_argument("pool", nargs="?", help="Pool name (e.g., pool-a)")
    parser.add_argument("--diff", help="Path to a patch file instead of git diff")
    parser.add_argument("--strict", action="store_true", help="Treat warnings as errors")
    args = parser.parse_args()

    if args.diff:
        with open(args.diff) as f:
            diff_text = f.read()
    elif args.pool:
        diff_text = get_diff(args.pool)
    else:
        parser.error("Provide a pool name or --diff file")
        return 1

    if not diff_text.strip():
        print("No diff found — nothing to review.")
        return 0

    parsed = parse_diff(diff_text)
    reports = []
    for filepath, lines in parsed.items():
        # Only review source and header files
        if filepath.endswith((".cpp", ".h", ".c")):
            reports.append(analyze_file(filepath, lines))

    if not reports:
        print("No source files in diff — nothing to review.")
        return 0

    return print_report(reports, strict=args.strict)


if __name__ == "__main__":
    sys.exit(main())
