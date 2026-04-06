# Worker: pool-e

## Model: Opus

## Task: Replace VT calls with named methods — ReflectModule functions

`include/app/modules/ReflectModule.h` already has 17 vtable methods.

### Target Files
- `src/app/fun_batch_e3_025.cpp` — ReflectModule functions ONLY (accessor+0xf8)
  NOTE: Pool D is editing this same file for PostureModule functions. You handle ONLY the ReflectModule ones.

### MANDATORY Example
**BEFORE:**
```cpp
void** mod = reinterpret_cast<void**>(acc->reflect_module);
reinterpret_cast<u64(*)(void**)>(VT(mod)[0x80 / 8])(mod);
```
**AFTER:**
```cpp
// [derived: ReflectModule__method_impl (.dynsym) -> slot 16 (0x80/8)]
ReflectModule* reflect = static_cast<ReflectModule*>(acc->reflect_module);
reflect->method_name();
```

Look up slot in `include/app/modules/ReflectModule.h`. If missing, add with [inferred:] tag.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN edit: fun_batch_e3_025.cpp (ReflectModule functions ONLY), ReflectModule.h (if slots missing)
- Use existing header methods. Add missing slots with [inferred:] tag
- 3-attempt limit per function
