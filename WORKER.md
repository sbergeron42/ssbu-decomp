# Worker: pool-c

## Model: Opus

## Task: Resource service — large functions from Ghidra exports

The mega-functions can't be decompiled via MCP, but Ghidra exports exist as .txt files.

### Target Functions
- `FUN_710374d270` — 8,432 bytes (called from main_loop)
- `FUN_7103757290` — 7,056 bytes (Mii renderer or resource related — identify first)
- `FUN_7103758f50` — 5,520 bytes

### Available Ghidra Exports
Check the project root for .txt files:
- `FUN_710374f360.txt` (already exists — 2,627 lines of decompiled C)
- Other exports may be in asm/ directory

If a function doesn't have a Ghidra export, try decompiling via MCP first. If MCP fails, decompile from raw disassembly (use llvm-objdump).

### Headers
- `include/resource/ResServiceNX.h`, `include/resource/LoadedArc.h`, `include/resource/containers.h`

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o

python tools/compare_bytes.py FUN_name
```

### Rules
- Output: src/resource/res_large_funcs.cpp
- Use resource headers with derivation chains
- 3-attempt limit per function
- If a function is NOT resource-related (graphics, Mii, etc.), document what it is and skip
