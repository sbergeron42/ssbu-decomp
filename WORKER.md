# Worker: pool-c

## Model: Opus

## Task: VT method replacement — last 4 batch files with VT(mod)[slot]

Replace remaining `VT(mod)[slot]` patterns with named vtable method calls.
All module headers already have vtable methods defined.

### Target Files
- `src/app/fun_batch_c2_017.cpp` — mixed module VT calls
- `src/app/fun_batch_e3_001.cpp` — mixed module VT calls
- `src/app/fun_batch_e3_004.cpp` — mixed module VT calls
- `src/app/fun_batch_e3_005.cpp` — mixed module VT calls

### Approach
1. For each VT(mod)[slot] call, identify the module (check which accessor offset loads it)
2. Look up slot in the module's header (include/app/modules/*.h)
3. Replace with `mod->method_name(args)` + `[derived:]` comment
4. If slot not in header, add it with `[inferred:]` tag

### Example
**BEFORE:**
```cpp
void** mod = reinterpret_cast<void**>(acc->motion_module);
reinterpret_cast<void(*)(void**, u64)>(VT(mod)[0xf0 / 8])(mod, p1);
```
**AFTER:**
```cpp
// [derived: MotionModule__change_motion_inherit_frame_keep_rate_impl (.dynsym) -> slot 30]
MotionModule* mod = static_cast<MotionModule*>(acc->motion_module);
mod->change_motion_inherit_frame_keep_rate(p1);
```

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN edit: fun_batch_c2_017.cpp, fun_batch_e3_001.cpp, fun_batch_e3_004.cpp, fun_batch_e3_005.cpp
- CAN add missing vtable entries to module headers with [inferred:] tags
- 3-attempt limit per function
