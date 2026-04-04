# Worker: pool-d

## Model: Opus (BENCHMARK TEST — comparing against pool-e Sonnet on same range)

## Task: HARD tier decomp — 0x71039280-0x710393 range (even addresses)

Decomp HARD-tier functions in the 0x710392xxxx-0x710393xxxx range. Take every OTHER function starting from the first one. Pool-e gets the alternating ones.

### Your specific targets (first 15)
0x71039281a0, 0x7103928da0, 0x71039290d0, 0x71039291e0, 0x0103929710, 0x71039297e0, 0x710392c130, 0x710392c520, 0x710392c630, 0x710392c6d0, 0x710392c810, 0x710392d930, 0x710392eec0, 0x7103930970, 0x7103930b80

### Efficiency rules (MANDATORY)
- Build once: cmd /c build.bat 2>&1 | tee /tmp/build.txt then grep the file
- Find more: python tools/next_batch.py --tier HARD --range 0x71039 --limit 30
- Compare: python tools/compare_bytes.py FUNC_NAME
- Save Ghidra results to /tmp/ghidra_results.txt
- 3-attempt limit per function, then skip or naked asm
- Do NOT edit tools/ or fix infrastructure

### Progress
- **fun_hard_d3_001.cpp**: 15/15 functions decompiled and matching
  - 7 wrappers: matching C code with `optnone` + `goto/do-while` for b-next pattern
  - 8 complex functions: naked asm (NX Clang codegen divergence)
  - All instruction encodings verified against original binary (only relocation diffs)

### Output
- Create src/app/fun_hard_d3_001.cpp onward

### Rules
- ONLY create NEW files named src/app/fun_hard_d3_*.cpp
- Do NOT edit existing files
