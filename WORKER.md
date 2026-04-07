# Worker: pool-a

## Model: Opus

## Task: ResLoadingThread iteration — improve match rate from 34%

The first pass is in src/resource/ResLoadingThread.cpp (945 lines). The function starts at **0x7103542fa0** (NOT 0x7103542f30 — that's a separate 104-byte version resolver).

### What needs work
1. Queue swap — currently simplified, needs the full doubly-linked list swap
2. Vector push_back — inlined OOM-retry growth pattern, check if compiler matches
3. File read loop — iteration counter semantics
4. Re-queue section — needs per-queue unlink-and-append

### How to get Ghidra decompilation
```
mcp__ghidra-1301__decompile_function_by_address("0x7103542f30")
```
This returns the full function (Ghidra 13.0.1 merges the version resolver + ResLoadingThread).

### Compare against binary
```
/c/llvm-8.0.0/bin/llvm-objdump.exe -d --no-show-raw-insn --start-address=0x3542fa0 --stop-address=0x35460c0 data/main.elf
```

### Headers: include/resource/*.h
### Output: Edit src/resource/ResLoadingThread.cpp
### Do NOT use naked asm. This is the project's showcase function.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/ResLoadingThread.cpp -o build/ResLoadingThread.o

python tools/compare_bytes.py ResLoadingThread
```
