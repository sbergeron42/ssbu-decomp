# Worker: pool-e

## Model: Opus

## Task: Continue effect/sound decomp + expand to AttackModule

20 effect/sound functions so far. Keep going, and expand into AttackModule (195 vtable methods available).

### Target Files
- `src/app/fighter_effects.cpp` (append — effects + sound)
- `src/app/fighter_attack.cpp` (new file — AttackModule functions)

### Headers: EffectModule.h, SoundModule.h, AttackModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
mcp__ghidra__search_functions_by_name("effect")
mcp__ghidra__search_functions_by_name("attack")
```
