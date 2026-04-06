# Worker: pool-e

## Model: Opus

## Task: Paste rewrites with struct access — batch_c + batch_e remaining files

Rewrite Ghidra paste with struct field access and derivation chains.
These are the remaining batch files not yet cleaned up.

### Target Files
- `src/app/fun_batch_c_006.cpp` — 31 funcs (already has BattleObjectModuleAccessor include)
- `src/app/fun_batch_c_009.cpp` — 39 funcs
- `src/app/fun_batch_c_011.cpp` — 57 funcs
- `src/app/fun_batch_e_001.cpp` — 10 funcs
- `src/app/fun_batch_e_002.cpp` — 5 funcs
- `src/app/fun_batch_e2_013.cpp` — 8 funcs

### Approach
1. For functions accessing modules: replace raw offsets with `acc->module_name` + `[derived:]` comments
2. For non-module functions: replace Ghidra variable names, add struct field comments with `[inferred:]` tags
3. Single-file compile, move on. Readable code > matching.

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
- Every named field MUST have [derived:] or [inferred:] tag
- 3-attempt limit per function
