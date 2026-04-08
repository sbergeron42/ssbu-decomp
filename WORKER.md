# Worker: pool-e

## Model: Opus

## Task: New decomp — EffectModule + SoundModule functions

### Context
327 undecompiled effect functions, 198 undecompiled sound functions. EffectModule.h has 91 vtable methods.

### Approach
1. Search for named undecompiled EffectModule/SoundModule functions
2. Decompile in Ghidra, write C++ using module headers
3. Focus on small functions (<200B) first

### Target: src/app/fighter_effects.cpp (new file)
### Headers: EffectModule.h, SoundModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
mcp__ghidra__search_functions_by_name("effect")
mcp__ghidra__search_functions_by_name("sound")
```
