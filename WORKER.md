# Worker: pool-b

## Model: Opus

## Task: Fix in_x10 lua_bind pattern — batch_c_001 + batch_c_003 + batch_c_004

### Goal: Fix the broken `in_x10` / `in_w8` pattern in lua_bind wrappers to achieve ~88% match rate

Pool-c already proved this pattern on batch_c_007/008 — 68/77 functions matched. Apply the SAME fix to these files.

### The Pattern (MANDATORY — follow exactly)

**BEFORE (broken Ghidra paste):**
```cpp
u64 FUN_...(s64 param_1, s64 param_2) {
    u64 in_x10;                          // ← uninitialized, UB
    *(u64 *)(param_1 + 0x10) = in_x10;   // ← wrong target (should be param_1, not param_2)
    app::SomeFunc(param_2);
    return 0;
}
```

**AFTER (correct register-asm dispatch):**
```cpp
u32 FUN_...(app::BattleObjectModuleAccessor* acc, s64 ctx) {
    register u64 x10 asm("x10");
    asm volatile("" : "=r"(x10));        // capture x10 without clobbering
    *(u64 *)((u8*)acc + 0x10) = x10;     // store to acc (first param), not ctx
    app::SomeFunc(acc);                   // dispatch uses acc
    return 0;                             // u32 return (mov w0, wzr)
}
```

### Key fixes in every function:
1. `u64 in_x10` → `register u64 x10 asm("x10"); asm volatile("" : "=r"(x10));`
2. Store target: `*(u64*)(param_2 + 0x10)` → `*(u64*)((u8*)acc + 0x10)` (first param, not second)
3. Return type: `u64` → `u32` (binary uses `mov w0, wzr`)
4. First param type: `s64` → `app::BattleObjectModuleAccessor*` where applicable

### Target Files
- `src/app/fun_batch_c_001.cpp` — 72 occurrences
- `src/app/fun_batch_c_003.cpp` — 87 occurrences  
- `src/app/fun_batch_c_004.cpp` — 58 occurrences

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN ONLY edit: fun_batch_c_001.cpp, fun_batch_c_003.cpp, fun_batch_c_004.cpp
- Apply the register-asm pattern to EVERY in_x10/in_w8 occurrence
- Derivation chains on any new offset tags
