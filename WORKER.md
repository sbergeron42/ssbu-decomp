# Worker: pool-e

## Model: Opus

## Task: Fix in_x10 lua_bind pattern — batch_e3 + batch_d5 + batch_e2 files

Same register-asm fix pattern proven by pool-c on batch_c_007/008.

### The Pattern
**BEFORE:**
```cpp
u64 FUN_...(s64 param_1, s64 param_2) {
    u64 in_x10;
    *(u64 *)(param_1 + 0x10) = in_x10;
    app::SomeFunc(param_2);
    return 0;
}
```
**AFTER:**
```cpp
u32 FUN_...(app::BattleObjectModuleAccessor* acc, s64 ctx) {
    register u64 x10 asm("x10");
    asm volatile("" : "=r"(x10));
    *(u64 *)((u8*)acc + 0x10) = x10;
    app::SomeFunc(acc);
    return 0;
}
```

### Target Files
- `src/app/fun_batch_e3_001.cpp` — 15 occurrences
- `src/app/fun_batch_e3_003.cpp` — 3 occurrences
- `src/app/fun_batch_e3_004.cpp` — 15 occurrences
- `src/app/fun_batch_e3_005.cpp` — 3 occurrences
- `src/app/fun_batch_d5_007.cpp` — 4 occurrences
- `src/app/fun_batch_d5_008.cpp` — 8 occurrences
- `src/app/fun_batch_d5_009.cpp` — 11 occurrences
- `src/app/fun_batch_d5_017.cpp` — 8 occurrences
- `src/app/fun_batch_d5_042.cpp` — 11 occurrences
- `src/app/fun_batch_e2_001.cpp` — 3 occurrences

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN ONLY edit the files listed above
