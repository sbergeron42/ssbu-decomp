# Worker: pool-a

## Model: Opus

## Task: Replace VT(mod)[slot] with named vtable methods — MotionModule files

The MotionModule header at `include/app/modules/MotionModule.h` already has 128 named vtable methods.
Replace every `reinterpret_cast<...>(VT(mod)[slot])(mod, ...)` with `mod->method_name(args)`.

### Target Files
- `src/app/fun_batch_e3_021.cpp` — 26 MotionModule functions
- `src/app/fun_batch_e3_022.cpp` — 42 MotionModule functions

### MANDATORY Example

**BEFORE (reinterpret_cast slop):**
```cpp
void FUN_710205cb70(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0xf0 / 8])(mod, p1);
}
```

**AFTER (clean named method call):**
```cpp
// [derived: MotionModule__change_motion_inherit_frame_keep_rate_impl (.dynsym) -> slot 30 (0xf0/8)]
void FUN_710205cb70(app::BattleObjectModuleAccessor* acc, u64 hash) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->change_motion_inherit_frame_keep_rate(hash);
}
```

**How to map:** slot = byte_offset / 8, look up in MotionModule.h, use method name.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN ONLY edit: fun_batch_e3_021.cpp, fun_batch_e3_022.cpp
- Must #include "app/modules/MotionModule.h" and use its method wrappers
- If a vtable slot is NOT in the header, add it with [inferred:] tag
- 3-attempt limit per function
