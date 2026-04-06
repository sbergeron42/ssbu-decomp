# Worker: pool-b

## Model: Opus

## Task: Replace VT(mod)[slot] with named vtable methods — MotionModule + MotionAnimcmd

Headers already have named vtable methods:
- `include/app/modules/MotionModule.h` — 128 methods
- `include/app/modules/MotionAnimcmdModule.h` — 15 methods

### Target Files
- `src/app/fun_batch_e3_023.cpp` — 20 MotionModule + 13 MotionAnimcmdModule functions

### MANDATORY Example
**BEFORE:**
```cpp
void FUN_...(app::BattleObjectModuleAccessor* acc, u64 p1) {
    void** mod = reinterpret_cast<void**>(acc->motion_module);
    reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0xf0 / 8])(mod, p1);
}
```
**AFTER:**
```cpp
// [derived: MotionModule__change_motion_inherit_frame_keep_rate_impl (.dynsym) -> slot 30 (0xf0/8)]
void FUN_...(app::BattleObjectModuleAccessor* acc, u64 hash) {
    MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
    mod->change_motion_inherit_frame_keep_rate(hash);
}
```

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN ONLY edit: fun_batch_e3_023.cpp
- Use MotionModule.h and MotionAnimcmdModule.h method wrappers
- If slot NOT in header, add with [inferred:] tag
- 3-attempt limit per function
