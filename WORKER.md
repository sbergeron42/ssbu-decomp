# Worker: pool-a

## Model: Opus

## Task: SIZE_DIFF investigation — why are 1,743 functions truncated but matching?

### Background
Pool B's gap analysis found 1,743 functions where every compiled byte matches the original binary perfectly, but the compiled function is SHORTER than the CSV expects. If we can figure out why, one build/tooling fix could add ~1,700 verified.

### Investigation steps
1. Pick 10 SIZE_DIFF functions from different source files
2. For each: compare the .o symbol size vs the CSV expected size
3. Examine what bytes follow our function in the original binary — are they:
   a. Another function that should be in the same compilation unit?
   b. An inlined function body?
   c. Padding/alignment?
   d. Part of the same function that our source doesn't capture?
4. Check if the "missing" bytes are compiled elsewhere in another .o file
5. Look for patterns: are these all lua_bind wrappers followed by impl bodies?

### Tools
```
# Check a specific function's sizes:
python tools/compare_bytes.py FUN_name

# Disassemble the original to see what follows:
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=ADDR --stop-address=END data/main.elf

# Check CSV entry:
grep FUN_name data/functions.csv
```

### Deliverable
A report in WORKER.md: what causes SIZE_DIFF, and a proposed fix (script, build change, or linker config).
