# Worker: pool-c

## Model: Opus

## Task: Continue fighter status decomp — next 100+ functions

You produced 121 fighter status functions last round. Keep going.

### Approach
Same as last session — search for named undecompiled functions related to fighter status, AI stat, params, ACMD. Decompile in Ghidra, write C++ with module headers.

### Target: src/app/fighter_status.cpp (append to existing)
### Headers: StatusModule.h, WorkModule.h, MotionModule.h, BattleObjectModuleAccessor.h
### Derivation Chains MANDATORY
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
mcp__ghidra__search_functions_by_name("status")
```
