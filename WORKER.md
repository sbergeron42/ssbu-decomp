# Worker: pool-d

## Model: Opus

## Task: Continue fighter motion + kinetic energy decomp

101 functions so far. Keep expanding — focus on remaining kinetic energy slots and motion helpers.

### Target: src/app/fighter_motion.cpp (append)
### Focus: KineticModule energy slots, MotionModule helpers, AttackModule accessors
### Headers: MotionModule.h, KineticModule.h, AttackModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
