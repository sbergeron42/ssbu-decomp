# Worker: pool-d

## Model: Opus

## Task: Paste rewrites with struct access — batch_d remaining files

Rewrite Ghidra paste with struct field access and derivation chains.
These are the remaining batch_d files not yet cleaned up.

### Target Files (highest paste density remaining)
- `src/app/fun_batch_d_006.cpp` — 12 funcs
- `src/app/fun_batch_d_007.cpp` — 52 funcs
- `src/app/fun_batch_d_009.cpp` — 47 funcs
- `src/app/fun_batch_d_010.cpp` — 36 funcs
- `src/app/fun_batch_d_011.cpp` — 33 funcs
- `src/app/fun_batch_d_017.cpp` — 12 funcs
- `src/app/fun_batch_d_018.cpp` — 7 funcs
- `src/app/fun_batch_d_019.cpp` — 5 funcs
- `src/app/fun_batch_d_020.cpp` — 4 funcs

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
