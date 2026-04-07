# Worker: pool-b

## Model: Opus

## Task: Post-processing gap analysis — categorize non-matching patterns

### Goal
Systematically categorize WHY non-matching functions don't match. This enables writing new fix_*.py scripts that could flip hundreds of N→M.

### Method
1. Pick 50 N-quality functions that have CLEAN source (not Ghidra paste). Good candidates:
   - Functions in src/app/modules/*.cpp (typed, struct access, clean code)
   - Functions in src/resource/*.cpp from this session
   - Functions with known names (not FUN_*)
2. For each: compile the single file, compare bytes against original
3. Classify the mismatch into categories:
   - Prologue scheduling (add x29 placement)
   - Register allocation (different register for same value)
   - Branch layout (block ordering differs)
   - Instruction encoding (movz vs orr, cmn vs adds)
   - Relocation-only (bl/adrp diffs that would resolve at link)
   - Missing instructions (wrong instruction count)
4. Output: a CSV or table: function_name, size, category, count_of_differing_instructions

### Deliverable
A report in WORKER.md with the ranked list of patterns and estimated impact.
If a pattern affects 100+ functions, prototype a fix_*.py script for it.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe ... -c src/app/FILE.cpp -o build/FILE.o
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn build/FILE.o > /tmp/compiled.txt
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=ADDR --stop-address=END data/main.elf > /tmp/original.txt
diff /tmp/compiled.txt /tmp/original.txt
```
