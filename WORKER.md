# Worker: pool-b

## Model: Opus

## Task: ResLoadingThread support — callees and sub-functions

Pool-a is decomping ResLoadingThread itself. Your job is to decomp the functions IT CALLS that aren't done yet.

### How to find callees
Decompile ResLoadingThread via 13.0.1 Ghidra:
```
mcp__ghidra-1301__decompile_function_by_address("0x7103542f30")
```
Then identify every `FUN_` or named function called from within, cross-reference with data/functions.csv to find which are still U (uncompiled), and decomp those.

### Known callees NOT yet decomped
- `FUN_7103544ca0` — called 4+ times in the loop (directory processing dispatch)
- `FUN_7103540960` — file info lookup
- `FUN_71037c58c0` — file read wrapper
- `func_0x007103541e30` — directory state update
- Any other uncompiled callees you discover

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/res_loading_callees.cpp
### Do NOT use naked asm. 3-attempt limit.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o
```
