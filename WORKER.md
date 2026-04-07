# Worker: pool-c

## Model: Opus

## Task: Ghidra paste rewrite — fun_batch_c series (Track 2)

Rewrite Ghidra paste functions with struct field access and derivation chains. The goal is READABLE CODE, not just matching. Commit improvements even if they don't match.

### Target Files (highest remaining paste density)
- `src/app/fun_batch_c_007.cpp` — ~160 funcs
- `src/app/fun_batch_c_008.cpp` — ~148 funcs
- Start with the functions that access BattleObjectModuleAccessor modules

### What "done" looks like
```cpp
// BEFORE (Ghidra paste):
void FUN_...(s64 param_1) {
    *(u8*)(*(s64*)(param_1 + 0x40) + 0x30) = 1;
}

// AFTER (struct access + derivation):
// [derived: +0x40 is status_module per StatusModule__*_impl (.dynsym)]
void FUN_...(app::BattleObjectModuleAccessor* acc) {
    StatusModule* status = static_cast<StatusModule*>(acc->status_module);
    // +0x30 [inferred: enable flag, set in 12 functions]
    *(u8*)((u8*)status + 0x30) = 1;
}
```

### Checklist per function
- [ ] Any raw offset `+0xNN`? → needs `[derived:]` or `[inferred:]` tag
- [ ] Module accessor function? → use `acc->module_name`
- [ ] Vtable call? → use module header method wrapper
- [ ] Pure forwarding wrapper? → one-line comment is fine

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/app/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- CAN ONLY edit: fun_batch_c_007.cpp, fun_batch_c_008.cpp
- Derivation chains MANDATORY on every offset
- Do NOT use naked asm. Do NOT do shallow renames.
