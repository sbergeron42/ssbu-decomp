# Worker: pool-d

## Model: Opus

## Task: Build PostureModule vtable struct + replace VT calls

### Phase 1: Build PostureModule vtable struct
`include/app/modules/PostureModule.h` currently has NO vtable methods.
`src/app/fun_batch_e3_025.cpp` has 20 PostureModule functions (accessor+0x38).

1. Read the file and catalog every VT(mod)[slot] call with signature
2. Search Ghidra for PostureModule__*_impl to get .dynsym names
3. Add method wrappers to PostureModule.h with derivation chains

### Phase 2: Replace VT calls
**BEFORE:**
```cpp
void** mod = reinterpret_cast<void**>(acc->posture_module);
reinterpret_cast<u64(*)(void**)>(VT(mod)[0x80/8])(mod);
```
**AFTER:**
```cpp
// [derived: PostureModule__pos_impl (.dynsym) -> slot 16 (0x80/8)]
PostureModule* posture = static_cast<PostureModule*>(acc->posture_module);
posture->pos();
```

### Target Files
- `include/app/modules/PostureModule.h` (add vtable methods)
- `src/app/fun_batch_e3_025.cpp` (PostureModule VT calls ONLY — ReflectModule is pool-e territory)

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN edit: PostureModule.h, fun_batch_e3_025.cpp (PostureModule functions ONLY)
- Every new vtable entry MUST have [derived:] or [inferred:] tag
- 3-attempt limit per function
