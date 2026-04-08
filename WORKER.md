# Worker: pool-d

## Model: Opus

## Task: Continue fighter motion decomp — expand MotionModule coverage

You produced 10 fighter motion functions last round. Keep going — there are 852 undecompiled.

### Approach
Search for named undecompiled MotionModule functions. Focus on small ones (<200B) that use the existing 128 vtable methods in MotionModule.h.

### Target: src/app/fighter_motion.cpp (append to existing)
### Headers: MotionModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
mcp__ghidra__search_functions_by_name("motion")
```
