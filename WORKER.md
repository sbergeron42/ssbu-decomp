# Worker: pool-a

## Model: Opus

## Task: Convert networking reference code to compilable decomp, then HARD tier networking

### Phase 1: Fix reference/networking_src/ files
The 3 networking files (input_mapping.cpp, state_serialize.cpp, ldn_transport.cpp) were moved to reference/ because they don't compile. Fix them and move back to src/app/networking/:
- Replace #include <cstdlib>, <cmath> with extern "C" declarations
- Fix function signature mismatches
- Remove or stub functions that reference unknown types
- Goal: compile without errors, verify what matches

### Phase 2: Decomp HARD tier networking functions
Functions in the 0x710016xxxx-0x710019xxxx range (game LDN data exchange) and 0x71037xxxxx (session management). Use src/docs/networking.md as reference.

### Efficiency rules (MANDATORY)
- Build once: cmd /c build.bat 2>&1 | tee /tmp/build.txt then grep the file
- Find targets: python tools/next_batch.py --tier HARD --range 0x710016 --limit 30
- Compare bytes: python tools/compare_bytes.py FUNC_NAME
- Save Ghidra results to /tmp/ghidra_results.txt
- 3-attempt limit per function, then skip or naked asm
- Do NOT edit tools/ or fix infrastructure — report issues and move on

### Rules
- CAN edit: reference/networking_src/*.cpp, src/app/networking/*.cpp (create dir if needed), include/app/*.h
- Do NOT edit other source files, tools/, or data/
