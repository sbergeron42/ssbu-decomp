# Worker: pool-c

## Model: Opus

## Task: Fix in_x10 lua_bind pattern — batch_c_005 + batch_c_006 + batch_c_009

Same pattern you proved on batch_c_007/008. Apply to these files.

### The Pattern (you already know this — same as your previous session)
- `u64 in_x10` → `register u64 x10 asm("x10"); asm volatile("" : "=r"(x10));`
- Store target: first param (acc), not second param (ctx)
- Return type: `u64` → `u32`
- Add `asm volatile("" ::: "x29")` for prologue scheduling where needed

### Target Files
- `src/app/fun_batch_c_005.cpp` — 58 occurrences
- `src/app/fun_batch_c_006.cpp` — 64 occurrences
- `src/app/fun_batch_c_009.cpp` — 78 occurrences

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN ONLY edit: fun_batch_c_005.cpp, fun_batch_c_006.cpp, fun_batch_c_009.cpp
