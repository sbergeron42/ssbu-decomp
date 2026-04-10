#!/usr/bin/env python3
"""Extract key pass dumps for a specific function from -print-after-all output."""
import re, sys, os

dump_file = sys.argv[1] if len(sys.argv) > 1 else "C:/Users/seanb/AppData/Local/Temp/pass_dump.txt"
target = sys.argv[2] if len(sys.argv) > 2 else "_ZN3app4item21change_partial_motionEPhyy"

current_pass = None
in_func = False
func_lines = []
results = {}

with open(dump_file, "r", errors="replace") as f:
    for line in f:
        m = re.match(r"# \*\*\* IR Dump After (.+?) \*\*\*", line)
        if m:
            if current_pass and func_lines:
                results[current_pass] = func_lines[:]
            current_pass = m.group(1).strip()
            in_func = False
            func_lines = []
            continue
        if "Machine code for function" in line and target in line:
            in_func = True
            func_lines = []
            continue
        if in_func and "End machine code for function" in line:
            if current_pass:
                results[current_pass] = func_lines[:]
            in_func = False
            continue
        if in_func:
            func_lines.append(line.rstrip())

key_passes = [
    "Prologue/Epilogue Insertion",
    "Control Flow Optimizer",
    "Post-RA pseudo instruction expansion",
    "AArch64 pseudo instruction expansion",
    "AArch64 load / store optimization pass",
    "PostRA Machine Instruction Scheduler",
]

for p in key_passes:
    matching = [k for k in results if p in k]
    if matching:
        k = matching[-1]
        print("=== %s ===" % k)
        for line in results[k]:
            stripped = line.strip()
            if stripped and not stripped.startswith(";"):
                if any(x in stripped for x in ["$w", "$x", "$s", "$d", "bb.", "BB#",
                                                "RET", "BLR", "dead", "renamable",
                                                "killed", "FMOV", "ORR", "MOV",
                                                "LDR", "STR", "STP", "LDP", "ADD",
                                                "frame"]):
                    print("  %s" % stripped[:130])
        print()
    else:
        print("=== %s === (not found)" % p)
        print()

print("Total passes with data for %s: %d" % (target, len(results)))
