# Worker: pool-a

## Model: Sonnet

## Status: COMPLETE — All EASY-tier batches compiled (001–006)

## Task: Decomp remaining 241 EASY-tier functions (DONE)

241 EASY-tier functions remain uncompiled. Use Ghidra MCP to decomp them. These are 1-7 instruction functions.

### Finding targets
```python
import csv
with open('data/fun_triage.csv') as f:
    reader = csv.DictReader(f)
    for row in reader:
        if row['Tier'] == 'EASY':
            print(row['Address'], row['Size'])
```
Then check which are already compiled by grepping build/*.o symbols.

### Approach
- Use mcp__ghidra__decompile_function_by_address for each
- Use struct headers from include/app/ where applicable
- Add // 0x71XXXXXXXX address comment above each function
- These are simple — field reads, stores, noops, dispatchers

### Output files
- Create src/app/fun_easy_final_001.cpp, fun_easy_final_002.cpp, etc.
- Build, verify, commit in batches

### Rules
- ONLY create NEW files named src/app/fun_easy_final_*.cpp
- Do NOT edit existing files
- Do NOT modify tools/ or data/
