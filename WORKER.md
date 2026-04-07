# Worker: pool-a

## Model: Opus

## Task: ResLoadingThread — Function 2 (inflate/processing, 4,608 bytes)

Function 1 is at 98.3%. Move to Function 2: the inflate/processing loop at 0x71035444C0 (binary offset 0x35444C0), 4,608 bytes.

### How to decompile
```
mcp__ghidra-1301__decompile_function_by_address("0x71035444C0")
```
If Ghidra merges it with the parent, extract the section from 0x35444C0 to 0x35456C0 in the disassembly.

### Binary disassembly
```
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=0x35444C0 --stop-address=0x35456C0 data/main.elf
```

### Context
This is the inflate/decompress dispatch — handles zlib/zstd decompression of ARC file data. ARCropolis hooks `inflate`, `inflate_dir_file`, `memcpy_1/2/3` all land in this function.

### Headers: include/resource/*.h, include/zlib/zlib_nx.h
### Derivation Chains MANDATORY
### Output: Add to src/resource/ResLoadingThread.cpp or new file
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o
```
