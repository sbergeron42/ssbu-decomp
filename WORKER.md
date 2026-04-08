# Worker: pool-c

## Model: Opus

## Task: New decomp — fighter state machine functions (StatusModule area)

### Context
1,151 undecompiled fighter state machine functions with community names. The Skyline/HDR modding community has deep knowledge of fighter status kinds. Our StatusModule, WorkModule, and MotionModule headers are already built with vtable methods.

### Approach
1. Start with small named StatusModule functions (under 200 bytes)
2. Use `mcp__ghidra__search_functions_by_name("status")` to find targets
3. Decompile in Ghidra, write C++ using StatusModule.h/WorkModule.h/MotionModule.h
4. Use the existing vtable method wrappers — `mod->method_name()` not `VT(mod)[slot]`

### Target Area
Functions in the 0x71020xxxxx range with names containing: status_, StatusKind, change_status, is_situation, get_status

### Headers: include/app/modules/StatusModule.h, WorkModule.h, MotionModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Output: src/app/fighter_status.cpp
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
mcp__ghidra__search_functions_by_name("status")
```
