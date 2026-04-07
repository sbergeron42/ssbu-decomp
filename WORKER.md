# Worker: pool-a

## Model: Opus

## Task: Continue ResLoadingThread — Function 3 (directory dispatch, 1,940B) + remaining helpers

### Primary: Function 3 at 0x71035456D0 (1,940 bytes)
Directory dispatch with 4-case switch. Smaller than Function 2 — more tractable.

### Secondary: FUN_7103541AE0 (~284 bytes) — init decompression state
Left over from previous round.

### Ghidra
```
mcp__ghidra-1301__decompile_function_by_address("0x71035456D0")
```

### Headers: include/resource/*.h
### Derivation Chains MANDATORY
### Output: src/resource/ResLoadingThread.cpp or new file
### Do NOT use naked asm.

### Quick Reference
```
/c/llvm-8.0.0/bin/clang++.exe -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections -fno-common -fno-short-enums -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG -Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs -c src/resource/FILE.cpp -o build/FILE.o
```
