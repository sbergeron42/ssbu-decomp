# Worker: pool-e

## Model: Opus

## Task: Paste rewrites with derivation chains — batch_c + batch_e files (redo)

Rewrite these files with proper confidence tags. Not every function has module accessor access — that's fine. The requirement is that every named field/offset gets a derivation comment.

### Target Files
- `src/app/fun_batch_c_006.cpp` — 31 funcs (already has BattleObjectModuleAccessor include)
- `src/app/fun_batch_c_009.cpp` — 39 funcs
- `src/app/fun_batch_c_011.cpp` — 57 funcs
- `src/app/fun_batch_e_001.cpp` — 10 funcs
- `src/app/fun_batch_e_002.cpp` — 5 funcs
- `src/app/fun_batch_e2_013.cpp` — 8 funcs

### What "done" looks like for EACH function type

**Module accessor function (has BattleObjectModuleAccessor*):**
```cpp
// [derived: +0x58 is ground_module per GroundModule__*_impl (.dynsym)]
GroundModule* ground = static_cast<GroundModule*>(acc->ground_module);
ground->method_name(args);
```

**Non-module struct function (raw struct pointer, no accessor):**
```cpp
// self [inferred: animation state struct, 0x90 bytes]
//   +0x08 [inferred: sub-object pointer, passed to size query]
//   +0x68 [inferred: enable flag, bool]
s64 FUN_...(s64 self) {
    // +0x08 [inferred: sub-object A, passed to FUN_7100039590 which returns size]
    s64 size_a = FUN_7100039590(*(u64*)(self + 8));
```

**Forwarding wrapper (just passes args through):**
```cpp
// 0x710219a420 — lua_bind forwarding wrapper, dispatches to FUN_710082a290
u64 FUN_710219a420(s64 ctx) {
    // +0x10 [inferred: lua return value slot, set by x10 register convention]
    u64 in_x10;
    *(u64*)(ctx + 0x10) = in_x10;
    FUN_710082a290();
    return 0;
}
```

### Key rule
If a function has NO struct offsets at all (just a pass-through call), a one-line description comment is sufficient. But if ANY offset like `+0x10`, `+0x68`, `+0x90` appears, it MUST get a confidence tag.

### Checklist per function (mental check before moving on)
- [ ] Any raw offset `+0xNN` in the function? → needs `[derived:]` or `[inferred:]` tag
- [ ] Is it a module accessor function? → use `acc->module_name` from the struct header
- [ ] Is it a vtable call? → can we use the module header's method wrapper?
- [ ] Is it a pure forwarding wrapper with no offsets? → one-line comment is fine, move on

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name

# Module offsets: +0x38 posture, +0x40 status, +0x48 control, +0x50 work, +0x58 ground
# +0x60 camera, +0x68 kinetic, +0x88 motion, +0xA0 attack, +0xA8 damage
# +0xC0 area, +0x140 effect, +0x148 sound
```

### Rules
- CAN ONLY edit the files listed above
- 3-attempt limit per function for matching
