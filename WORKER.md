# Worker: pool-c

## Model: Opus

## Task: Continue fighter status + weapon params decomp

You've produced 298 fighter status + 69 weapon param functions. Keep going.

### Target Files
- `src/app/fighter_status.cpp` (append)
- `src/app/weapon_params.cpp` (append)

### Focus: Named undecompiled functions related to fighter status, AI, params, weapons
### Headers: StatusModule.h, WorkModule.h, MotionModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```
