# Worker: pool-c

## Model: Opus

## Task: Build KineticModule vtable struct + replace VT calls

### Phase 1: Build KineticModule vtable struct
`include/app/modules/KineticModule.h` currently has NO vtable methods.
`src/app/fun_batch_c_012.cpp` and `fun_batch_c_013.cpp` have 69 functions that call vtable methods on KineticModule (accessor+0x68).

1. Read both files and catalog every VT(mod)[slot] call with its argument signature
2. Cross-reference slot indices with .dynsym: search Ghidra for KineticModule__*_impl
3. Add method wrappers to KineticModule.h with derivation chains

### Phase 2: Replace VT calls with method names
**BEFORE:**
```cpp
void** mod = reinterpret_cast<void**>(acc->item_kinetic_module);
(*reinterpret_cast<s64(*)(void**, s64)>(VT(mod)[0x60/8]))(mod, 0xc);
```
**AFTER:**
```cpp
// [derived: KineticModule__get_energy_impl (.dynsym) -> slot 12 (0x60/8)]
KineticModule* kinetic = static_cast<KineticModule*>(acc->item_kinetic_module);
kinetic->get_energy(0xc);
```

### Target Files
- `include/app/modules/KineticModule.h` (add vtable methods)
- `src/app/fun_batch_c_012.cpp` (replace VT calls)
- `src/app/fun_batch_c_013.cpp` (replace VT calls)

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN edit: KineticModule.h, fun_batch_c_012.cpp, fun_batch_c_013.cpp
- Every new vtable entry MUST have [derived:] or [inferred:] tag
- 3-attempt limit per function
