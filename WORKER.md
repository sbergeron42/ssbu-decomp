# Worker: pool-e

## Model: Opus

## Task: UI/CSS (20 functions) + AI/L2CValue (10 functions) — community showcase

Decomp 30 HARD-tier functions in two high-visibility areas.

### UI/CSS Targets (20 functions, 0x71017xxxxx)
Near character select screen, input mapping, fighter loading code.
CSSState.h (335 lines, 90% complete) already exists for type context.

Addresses:
0x71017118d0, 0x7101711930, 0x7101711b30, 0x7101711b80, 0x7101711be0,
0x7101711c30, 0x7101711c90, 0x71017123a0, 0x71017123e0, 0x7101712e60,
0x7101712ec0, 0x7101714740, 0x71017147a0, 0x7101717d40, 0x7101717d90,
0x710171df30, 0x710171df90, 0x7101758ba0, 0x71017e2840, 0x71017e48e0

### AI/L2CValue Targets (10 functions, 0x71037xxxxx)
L2C is the Lua-to-C bridge modders interact with constantly. High community value.

Addresses:
0x710378e2f0, 0x71037af2c0, 0x71037b0bd0, 0x71037b36d0, 0x71037b3b70,
0x71037b73f0, 0x71037bc630, 0x71037bfdd0, 0x71037c0510, 0x71037c68e0

### Approach
1. Decompile each function in Ghidra
2. Identify the struct/class it operates on (check include/app/ for existing headers)
3. Write clean C++ using struct field access
4. For L2C functions, check if they match known L2CValue patterns from the modding community

### Output: src/app/fun_typed_e_008.cpp (UI/CSS), src/app/fun_typed_e_009.cpp (AI/L2C)

### Rules
- Use struct field access, no raw offsets, no Ghidra paste, no naked asm
- 3-attempt limit per function
- ONLY create src/app/fun_typed_e_*.cpp
- Save Ghidra results to /tmp/ghidra_results.txt
- Build once with tee, grep the file
