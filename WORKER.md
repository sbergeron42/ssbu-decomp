# Worker: pool-d

## Model: Opus

## Task: Ghidra paste rewrite — fun_batch_d series (Track 2)

Rewrite Ghidra paste functions with struct field access and derivation chains.

### Target Files
- `src/app/fun_batch_d_003.cpp` — 14 funcs
- `src/app/fun_batch_d_004.cpp` — 12 funcs
- `src/app/fun_batch_d_009.cpp` — 47 funcs
- `src/app/fun_batch_d_011.cpp` — 33 funcs

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
- CAN ONLY edit the files listed above
- Derivation chains MANDATORY on every offset
- Do NOT use naked asm. Do NOT do shallow renames.
