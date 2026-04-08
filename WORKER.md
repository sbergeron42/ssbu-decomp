# Worker: pool-b

## Model: Opus

## Task: SIZE_DIFF investigation — second sample set

Same task as pool-a but with a different sample. Compare notes.

### Investigation steps
1. Pick 10 SIZE_DIFF functions — prioritize DIFFERENT source file types than pool-a:
   - fun_batch_c_* functions
   - fun_medium_* functions
   - fun_hard_* functions
   - Named module functions (StatusModule, WorkModule, etc.)
2. For each: what's in the original binary after our function ends?
3. Document the pattern. Is it always the same cause?

### Tools
```
python tools/compare_bytes.py FUN_name
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=ADDR --stop-address=END data/main.elf
grep FUN_name data/functions.csv
```

### Deliverable
A report: what causes SIZE_DIFF for YOUR samples, proposed fix.
