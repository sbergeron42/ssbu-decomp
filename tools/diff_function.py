#!/usr/bin/env python3
"""
Compare compiled object code against expected assembly from the target binary.

Usage:
    python tools/diff_function.py <object_file> <function_name> <expected_asm_file>

The expected asm file should contain one instruction per line (from Ghidra export).
The object file is disassembled with llvm-objdump and compared.
"""

import subprocess
import sys
import re
from pathlib import Path

def disassemble_object(obj_path: str, function_name: str) -> list[str]:
    """Extract function assembly from compiled object file."""
    result = subprocess.run(
        ["llvm-objdump", "-d", "--no-show-raw-insn", obj_path],
        capture_output=True, text=True
    )

    lines = result.stdout.split("\n")
    in_function = False
    asm_lines = []

    for line in lines:
        if function_name in line and ":" in line:
            in_function = True
            continue
        if in_function:
            if line.strip() == "" or (not line.startswith(" ") and ":" in line):
                break
            # Extract just the instruction
            match = re.match(r'\s+[0-9a-f]+:\s+(.*)', line)
            if match:
                asm_lines.append(match.group(1).strip())

    return asm_lines

def load_expected(asm_path: str) -> list[str]:
    """Load expected assembly from Ghidra export."""
    lines = []
    with open(asm_path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#") or line.startswith("//"):
                continue
            # Strip address prefix if present (e.g., "71020ae240: ldr x8,[x0, #0xc0]")
            match = re.match(r'[0-9a-f]+:\s+(.*)', line)
            if match:
                line = match.group(1)
            lines.append(line.strip())
    return lines

def diff_asm(expected: list[str], actual: list[str]) -> None:
    """Print side-by-side diff."""
    max_len = max(len(expected), len(actual))
    max_width = max((len(s) for s in expected), default=0)

    matches = 0
    total = max_len

    print(f"{'Expected':<{max_width+4}} {'Actual'}")
    print("-" * (max_width + 40))

    for i in range(max_len):
        exp = expected[i] if i < len(expected) else "<missing>"
        act = actual[i] if i < len(actual) else "<missing>"

        # Normalize for comparison (collapse whitespace, ignore commas vs spaces)
        exp_norm = re.sub(r'[\s,]+', ' ', exp.lower())
        act_norm = re.sub(r'[\s,]+', ' ', act.lower())

        if exp_norm == act_norm:
            marker = "  OK"
            matches += 1
        else:
            marker = " <<< DIFF"

        print(f"  {exp:<{max_width+2}} {act}{marker}")

    print(f"\n{matches}/{total} instructions match ({100*matches//total}%)")

def main():
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <object_file> <function_name> <expected_asm_file>")
        sys.exit(1)

    obj_path, func_name, asm_path = sys.argv[1], sys.argv[2], sys.argv[3]

    actual = disassemble_object(obj_path, func_name)
    expected = load_expected(asm_path)

    if not actual:
        print(f"ERROR: Could not find function '{func_name}' in {obj_path}")
        sys.exit(1)

    print(f"Function: {func_name}")
    print(f"Expected: {len(expected)} instructions")
    print(f"Actual:   {len(actual)} instructions")
    print()

    diff_asm(expected, actual)

if __name__ == "__main__":
    main()
