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

### Results
- FUN_710374d270 — **SKIP**: scene/render update loop (5 object vectors via DAT_710593aa90)
- FUN_7103757290 — **SKIP**: Mii renderer init (nn::mii::Database, MiiModelRenderer)
- FUN_7103758f50 — **SKIP**: Mii model creation (0x388-byte alloc, 4 render passes)
- **Replacement targets found**: FixedString<512> utilities at 0x71037c3f20/4550/4630
  - Struct: char data[514] + u16 length at +0x202
  - Functions throw std::out_of_range (requires -fexceptions)
  - Loop bodies match structurally; NX Clang divergences: post-index load, AND mask

### Additional resource service functions identified (future targets)
- FUN_71037c3db0 (368 bytes) — ResServiceNX singleton path resolution wrapper
- FUN_71037c4010 (1,344 bytes) — ResServiceNX singleton path resolution (4 params)
- FUN_71037c5ff0 (2,288 bytes) — ResServiceNX singleton constructor
- FUN_710353d5e0 (384 bytes) — copy_filepath_vector_from_loaded_directory
- FUN_710353a8f0 (1,280 bytes) — filesystem entry scanner/resolver

### Rules
- Output: src/resource/res_large_funcs.cpp
- Use resource headers with derivation chains
- 3-attempt limit per function
- If a function is NOT resource-related (graphics, Mii, etc.), document what it is and skip
