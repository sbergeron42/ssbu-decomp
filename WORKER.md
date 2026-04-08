# Worker: pool-d

## Model: Opus

## Task: New decomp — fighter motion/animation functions

### Context
852 undecompiled motion/animation functions with community names. MotionModule.h already has 128 vtable methods. The animation system is heavily used by moveset modders.

### Approach
1. Start with small named MotionModule functions (under 200 bytes)
2. Use `mcp__ghidra__search_functions_by_name("motion")` to find targets
3. Decompile in Ghidra, write C++ using MotionModule.h
4. Use existing vtable method wrappers

### Target Area
Functions with names containing: motion_, change_motion, set_rate, set_frame, is_end, is_loop, add_motion_partial

### Headers: include/app/modules/MotionModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Output: src/app/fighter_motion.cpp
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
mcp__ghidra__search_functions_by_name("motion")
```
